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
		VLM_RENDERER_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_windowHandle);
		int status = gladLoadGL((GLADloadfunc)glfwGetProcAddress);
		VLM_CORE_ASSERT(status, "Failed to initialize Glad!");

		VLM_CORE_INFO("OpenGL Info:");
		VLM_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		VLM_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		VLM_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));

#ifdef VLM_ENABLE_ASSERTS
		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

		VLM_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Volum requires at least OpenGL version 4.5!");
#endif
	}

	void OpenGLContext::SwapBuffers()
	{
		VLM_RENDERER_PROFILE_FUNCTION();

		glfwSwapBuffers(m_windowHandle);
	}
}