#pragma once

namespace Volum
{
	enum class RendererAPI
	{
		None = 0, OpenGL = 1
	};

	class Renderer
	{
	public:
		static inline RendererAPI GetAPI() { return s_rendererAPI; };

	private:
		static RendererAPI s_rendererAPI;
	};
}