#include "vlmpch.h"

#include "Renderer2D.h"

#include "Volum/Renderer/RenderCommand.h"
#include "Volum/Renderer/VertexArray.h"
#include "Volum/Renderer/Shader.h"

#include <glm/ext/matrix_transform.hpp>

namespace Volum
{
	struct Renderer2DStorage
	{
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;
	};

	static Renderer2DStorage* s_data;

	void Renderer2D::Init()
	{
		VLM_PROFILE_FUNCTION();

		s_data = new Renderer2DStorage();

		s_data->QuadVertexArray = VertexArray::Create();

		float squareVertices[4 * 5] = {
			-0.75f, -0.75f, 0.0f,		0.0f, 0.0f,
			 0.75f, -0.75f, 0.0f,		1.0f, 0.0f,
			 0.75f,  0.75f, 0.0f,		1.0f, 1.0f,
			-0.75f,  0.75f, 0.0f,		0.0f, 1.0f,
		};

		Ref<VertexBuffer> squareVB = VertexBuffer::Create(squareVertices, sizeof(squareVertices));

		squareVB->SetLayout({
			{ ShaderDataType::Float3, "a_position" },
			{ ShaderDataType::Float2, "a_texCoords" },
		});

		s_data->QuadVertexArray->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = {
			0, 1, 2,
			2, 3, 0
		};

		Ref<IndexBuffer> squareIB = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		s_data->QuadVertexArray->SetIndexBuffer(squareIB);

		s_data->WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTexData = 0xffffffff;
		s_data->WhiteTexture->SetData(&whiteTexData, sizeof(uint32_t));

		s_data->TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		s_data->TextureShader->Bind();
		s_data->TextureShader->SetInt("u_texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		VLM_PROFILE_FUNCTION();

		delete s_data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		VLM_PROFILE_FUNCTION();

		s_data->TextureShader->Bind();
		s_data->TextureShader->SetMat4("u_viewProjMat", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{
		VLM_PROFILE_FUNCTION();
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad(glm::vec3(position, 0.0f), size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		VLM_PROFILE_FUNCTION();

		//s_data->TextureShader->Bind(); // Single shader, so it's already bound
		s_data->TextureShader->SetFloat4("u_color", color);
		s_data->TextureShader->SetFloat("u_tilingFactor", 1.0f);
		s_data->WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));
		s_data->TextureShader->SetMat4("u_modelMat", transform);

		s_data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_data->QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, glm::vec4 tintColor)
	{
		DrawQuad(glm::vec3(position, 0.0f), size, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, glm::vec4 tintColor)
	{
		VLM_PROFILE_FUNCTION();

		//s_data->TextureShader->Bind(); // Single shader, so it's already bound
		s_data->TextureShader->SetFloat4("u_color", tintColor);
		s_data->TextureShader->SetFloat("u_tilingFactor", tilingFactor);
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));
		s_data->TextureShader->SetMat4("u_modelMat", transform);

		s_data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_data->QuadVertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const float rotation, const glm::vec2& size, const glm::vec4& color)
	{
		DrawRotatedQuad(glm::vec3(position, 0.0f), rotation, size, color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const float rotation, const glm::vec2& size, const glm::vec4& color)
	{
		VLM_PROFILE_FUNCTION();

		//s_data->TextureShader->Bind(); // Single shader, so it's already bound
		s_data->TextureShader->SetFloat4("u_color", color);
		s_data->TextureShader->SetFloat("u_tilingFactor", 1.0f);
		s_data->WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 0.0f, 1.0f))
			* glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));
		s_data->TextureShader->SetMat4("u_modelMat", transform);

		s_data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_data->QuadVertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const float rotation, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, glm::vec4 tintColor)
	{
		DrawRotatedQuad(glm::vec3(position, 0.0f), rotation, size, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const float rotation, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, glm::vec4 tintColor)
	{
		VLM_PROFILE_FUNCTION();

		//s_data->TextureShader->Bind(); // Single shader, so it's already bound
		s_data->TextureShader->SetFloat4("u_color", tintColor);
		s_data->TextureShader->SetFloat("u_tilingFactor", tilingFactor);
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) 
			* glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 0.0f, 1.0f))
			* glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));
		s_data->TextureShader->SetMat4("u_modelMat", transform);

		s_data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_data->QuadVertexArray);
	}

}