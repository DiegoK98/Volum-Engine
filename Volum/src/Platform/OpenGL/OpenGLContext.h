#pragma once
#include "Volum/Renderer/GraphicsContext.h"

// Forw decl
struct GLFWwindow;

namespace Volum
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_windowHandle;
	};
}