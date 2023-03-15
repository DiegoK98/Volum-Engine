#include "vlmpch.h"

#include "Renderer3D.h"

#include "Volum/Renderer/RenderCommand.h"
#include "Volum/Renderer/VertexArray.h"
#include "Volum/Renderer/Shader.h"

#include <glm/ext/matrix_transform.hpp>

namespace Volum
{
	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoords;
		float TexIndex;
		float TexTilingFactor;
	};

	struct Renderer3DData
	{
		static const uint32_t MaxQuadsPerDraw = 10000;
		static const uint32_t MaxVerticesPerDraw = MaxQuadsPerDraw * 4;
		static const uint32_t MaxIndicesPerDraw = MaxQuadsPerDraw * 6;
		static const uint32_t MaxTextureSlotsPerDraw = 32; // TODO: RenderCaps

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		std::array<Ref<Texture2D>, MaxTextureSlotsPerDraw> TextureSlots;
		uint32_t TextureSlotIndex = 1; // 0 = white texture

		glm::vec4 QuadVertexPositions[4];

		Renderer3D::Statistics Stats;
	};

	static Renderer3DData s_data;

	void Renderer3D::Init()
	{
		VLM_PROFILE_FUNCTION();

		s_data.QuadVertexArray = VertexArray::Create();

		s_data.QuadVertexBuffer = VertexBuffer::Create(s_data.MaxVerticesPerDraw * sizeof(QuadVertex));
		s_data.QuadVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_position" },
			{ ShaderDataType::Float4, "a_color" },
			{ ShaderDataType::Float2, "a_texCoords" },
			{ ShaderDataType::Float, "a_texIndex" },
			{ ShaderDataType::Float, "a_texTilingFactor" },
		});
		s_data.QuadVertexArray->AddVertexBuffer(s_data.QuadVertexBuffer);

		s_data.QuadVertexBufferBase = new QuadVertex[s_data.MaxVerticesPerDraw];

		uint32_t* quadIndices = new uint32_t[s_data.MaxIndicesPerDraw];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_data.MaxIndicesPerDraw; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, s_data.MaxIndicesPerDraw);
		s_data.QuadVertexArray->SetIndexBuffer(quadIB);
		delete[] quadIndices;

		s_data.WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTexData = 0xffffffff;
		s_data.WhiteTexture->SetData(&whiteTexData, sizeof(uint32_t));

		int32_t samplers[s_data.MaxTextureSlotsPerDraw];
		for (uint32_t i = 0; i < s_data.MaxTextureSlotsPerDraw; i++)
			samplers[i] = i;

		s_data.TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		s_data.TextureShader->Bind();
		s_data.TextureShader->SetIntArray("u_textures", samplers, s_data.MaxTextureSlotsPerDraw);

		s_data.TextureSlots[0] = s_data.WhiteTexture;

		s_data.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f};
		s_data.QuadVertexPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f};
		s_data.QuadVertexPositions[2] = {  0.5f,  0.5f, 0.0f, 1.0f};
		s_data.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f};
	}

	void Renderer3D::Shutdown()
	{
		VLM_PROFILE_FUNCTION();

		delete[] s_data.QuadVertexBufferBase;
	}

	void Renderer3D::BeginScene(const OrthographicCamera& camera)
	{
		VLM_PROFILE_FUNCTION();

		s_data.TextureShader->Bind();
		s_data.TextureShader->SetMat4("u_viewProjMat", camera.GetViewProjectionMatrix());

		ResetData();
	}

	void Renderer3D::EndScene()
	{
		VLM_PROFILE_FUNCTION();

		Flush();
	}

	void Renderer3D::Flush()
	{
		VLM_PROFILE_FUNCTION();

		if (s_data.QuadIndexCount == 0)
			return; // Nothing to draw

		uint32_t dataSize = (uint32_t)((uint8_t*)s_data.QuadVertexBufferPtr - (uint8_t*)s_data.QuadVertexBufferBase); // cast to 1 byte type to get size in bytes
		s_data.QuadVertexBuffer->SetData(s_data.QuadVertexBufferBase, dataSize);

		for (uint32_t i = 0; i < s_data.TextureSlotIndex; i++)
			s_data.TextureSlots[i]->Bind(i);

		RenderCommand::DrawIndexed(s_data.QuadVertexArray, s_data.QuadIndexCount);

		s_data.Stats.DrawCallsCount++;
	}

	void Renderer3D::ResetData()
	{
		s_data.QuadIndexCount = 0;
		s_data.TextureSlotIndex = 1;
		s_data.QuadVertexBufferPtr = s_data.QuadVertexBufferBase;
	}

	void Renderer3D::FlushAndReset()
	{
		Flush();
		ResetData();
	}

	void Renderer3D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		VLM_PROFILE_FUNCTION();

		constexpr size_t quadVertexCount = 4;
		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
		const float textureIndex = 0.0f;
		const float textureTilingFactor = 1.0f;

		if (s_data.QuadIndexCount >= Renderer3DData::MaxIndicesPerDraw)
			FlushAndReset();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		for (size_t i = 0; i < quadVertexCount; i++)
		{
			s_data.QuadVertexBufferPtr->Position = transform * s_data.QuadVertexPositions[i];
			s_data.QuadVertexBufferPtr->Color = color;
			s_data.QuadVertexBufferPtr->TexCoords = textureCoords[i];
			s_data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_data.QuadVertexBufferPtr->TexTilingFactor = textureTilingFactor;
			s_data.QuadVertexBufferPtr++;
		}

		s_data.QuadIndexCount += 6;
		s_data.Stats.QuadCount++;
	}

	void Renderer3D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float textureTilingFactor, glm::vec4 tintColor)
	{
		VLM_PROFILE_FUNCTION();

		constexpr size_t quadVertexCount = 4;
		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

		if (s_data.QuadIndexCount >= Renderer3DData::MaxIndicesPerDraw)
			FlushAndReset();

		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < s_data.TextureSlotIndex; i++)
		{
			if (*s_data.TextureSlots[i].get() == *texture.get())
			{
				textureIndex = (float)i;
			}
		}

		if (textureIndex == 0.0f)
		{
			if (s_data.TextureSlotIndex >= Renderer3DData::MaxTextureSlotsPerDraw)
				FlushAndReset();

			textureIndex = (float)s_data.TextureSlotIndex;
			s_data.TextureSlots[s_data.TextureSlotIndex] = texture;
			s_data.TextureSlotIndex++;
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		for (size_t i = 0; i < quadVertexCount; i++)
		{
			s_data.QuadVertexBufferPtr->Position = transform * s_data.QuadVertexPositions[i];
			s_data.QuadVertexBufferPtr->Color = tintColor;
			s_data.QuadVertexBufferPtr->TexCoords = textureCoords[i];
			s_data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_data.QuadVertexBufferPtr->TexTilingFactor = textureTilingFactor;
			s_data.QuadVertexBufferPtr++;
		}

		s_data.QuadIndexCount += 6;
		s_data.Stats.QuadCount++;
	}

	void Renderer3D::DrawRotatedQuad(const glm::vec3& position, const glm::vec3& rotation, const glm::vec2& size, const glm::vec4& color)
	{
		VLM_PROFILE_FUNCTION();

		if (s_data.QuadIndexCount >= Renderer3DData::MaxIndicesPerDraw)
			FlushAndReset();

		constexpr size_t quadVertexCount = 4;
		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
		const float textureIndex = 0.0f;
		const float textureTilingFactor = 1.0f;

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation.x, { 1.0f, 0.0f, 0.0f }) // x
			* glm::rotate(glm::mat4(1.0f), rotation.y, { 0.0f, 1.0f, 0.0f }) // y
			* glm::rotate(glm::mat4(1.0f), rotation.z, { 0.0f, 0.0f, 1.0f }) // z
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		for (size_t i = 0; i < quadVertexCount; i++)
		{
			s_data.QuadVertexBufferPtr->Position = transform * s_data.QuadVertexPositions[i];
			s_data.QuadVertexBufferPtr->Color = color;
			s_data.QuadVertexBufferPtr->TexCoords = textureCoords[i];
			s_data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_data.QuadVertexBufferPtr->TexTilingFactor = textureTilingFactor;
			s_data.QuadVertexBufferPtr++;
		}

		s_data.QuadIndexCount += 6;
		s_data.Stats.QuadCount++;
	}

	void Renderer3D::DrawRotatedQuad(const glm::vec3& position, const glm::vec3& rotation, const glm::vec2& size, const Ref<Texture2D>& texture, float textureTilingFactor, glm::vec4 tintColor)
	{
		VLM_PROFILE_FUNCTION();

		constexpr size_t quadVertexCount = 4;
		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

		if (s_data.QuadIndexCount >= Renderer3DData::MaxIndicesPerDraw)
			FlushAndReset();

		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < s_data.TextureSlotIndex; i++)
		{
			if (*s_data.TextureSlots[i].get() == *texture.get())
			{
				textureIndex = (float)i;
			}
		}

		if (textureIndex == 0.0f)
		{
			if (s_data.TextureSlotIndex >= Renderer3DData::MaxTextureSlotsPerDraw)
				FlushAndReset();

			textureIndex = (float)s_data.TextureSlotIndex;
			s_data.TextureSlots[s_data.TextureSlotIndex] = texture;
			s_data.TextureSlotIndex++;
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation.x, { 1.0f, 0.0f, 0.0f }) // x
			* glm::rotate(glm::mat4(1.0f), rotation.y, { 0.0f, 1.0f, 0.0f }) // y
			* glm::rotate(glm::mat4(1.0f), rotation.z, { 0.0f, 0.0f, 1.0f }) // z
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		for (size_t i = 0; i < quadVertexCount; i++)
		{
			s_data.QuadVertexBufferPtr->Position = transform * s_data.QuadVertexPositions[i];
			s_data.QuadVertexBufferPtr->Color = tintColor;
			s_data.QuadVertexBufferPtr->TexCoords = textureCoords[i];
			s_data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_data.QuadVertexBufferPtr->TexTilingFactor = textureTilingFactor;
			s_data.QuadVertexBufferPtr++;
		}

		s_data.QuadIndexCount += 6;
		s_data.Stats.QuadCount++;
	}

	void Renderer3D::ResetStats()
	{
		memset(&s_data.Stats, 0, sizeof(Statistics));
	}

	Renderer3D::Statistics Renderer3D::GetStats()
	{
		return s_data.Stats;
	}
}