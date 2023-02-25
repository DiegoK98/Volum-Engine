#include "vlmpch.h"

#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/gl.h>

namespace Volum
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_windowHandle(windowHandle)
	{
		VLM_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_windowHandle);
		int status = gladLoadGL((GLADloadfunc)glfwGetProcAddress);
		VLM_CORE_ASSERT(status, "Failed to initialize Glad!");

		VLM_CORE_INFO("OpenGL Info:");
		VLM_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		VLM_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		VLM_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_windowHandle);
	}
}