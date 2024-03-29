#pragma once

#include "Volum/Renderer/Camera.h"
#include "Volum/Renderer/OrthographicCamera.h"
#include "Volum/Renderer/Texture.h"

namespace Volum
{
	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const Camera& camera, glm::mat4& transform);
		static void BeginScene(const OrthographicCamera& camera); // TODO: Remove
		static void EndScene();
		static void Flush();

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float textureTilingFactor = 1.0f, glm::vec4 tintColor = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float textureTilingFactor = 1.0f, glm::vec4 tintColor = glm::vec4(1.0f));
		static void DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, float textureTilingFactor = 1.0f, glm::vec4 tintColor = glm::vec4(1.0f));

		static void DrawRotatedQuad(const glm::vec2& position, const float rotation, const glm::vec2& size, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec3& position, const float rotation, const glm::vec2& size, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec2& position, const float rotation, const glm::vec2& size, const Ref<Texture2D>& texture, float textureTilingFactor = 1.0f, glm::vec4 tintColor = glm::vec4(1.0f));
		static void DrawRotatedQuad(const glm::vec3& position, const float rotation, const glm::vec2& size, const Ref<Texture2D>& texture, float textureTilingFactor = 1.0f, glm::vec4 tintColor = glm::vec4(1.0f));
		
		// Stats
		struct Statistics
		{
			uint32_t DrawCallsCount = 0;
			uint32_t QuadCount = 0;

			uint32_t GetTotalVertexCount() { return QuadCount * 4; }
			uint32_t GetTotalIndexCount() { return QuadCount * 6; }
		};

		static void ResetStats();
		static Statistics GetStats();

	private:
		static void FlushAndReset();
		static void ResetData();
	};
}