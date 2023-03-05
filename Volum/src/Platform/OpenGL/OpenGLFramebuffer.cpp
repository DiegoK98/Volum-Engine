#include "vlmpch.h"

#include "OpenGLFramebuffer.h"

#include <glad/gl.h>

namespace Volum
{
	// TODO: Should be taken from device capabilities
	static const uint32_t s_maxFramebufferSize = 8192;

	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& spec)
		: m_specification(spec)
	{
		VLM_RENDERER_PROFILE_FUNCTION();

		Recreate();
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		VLM_RENDERER_PROFILE_FUNCTION();

		glDeleteFramebuffers(1, &m_rendererID);
		glDeleteTextures(1, &m_colorAttachment);
		glDeleteTextures(1, &m_depthAttachment);
	}

	void OpenGLFramebuffer::Recreate()
	{
		VLM_RENDERER_PROFILE_FUNCTION();

		if (m_rendererID)
		{
			glDeleteFramebuffers(1, &m_rendererID);
			glDeleteTextures(1, &m_colorAttachment);
			glDeleteTextures(1, &m_depthAttachment);
		}

		glCreateFramebuffers(1, &m_rendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_rendererID);
		
		// Color attachment
		glCreateTextures(GL_TEXTURE_2D, 1, &m_colorAttachment);
		glBindTexture(GL_TEXTURE_2D, m_colorAttachment);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_specification.Width, m_specification.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorAttachment, 0);

		// Depth attachment
		glCreateTextures(GL_TEXTURE_2D, 1, &m_depthAttachment);
		glBindTexture(GL_TEXTURE_2D, m_depthAttachment);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_specification.Width, m_specification.Height);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depthAttachment, 0);

		VLM_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::Bind()
	{
		VLM_RENDERER_PROFILE_FUNCTION();

		glBindFramebuffer(GL_FRAMEBUFFER, m_rendererID);
		glViewport(0, 0, m_specification.Width, m_specification.Height);
	}

	void OpenGLFramebuffer::Unbind()
	{
		VLM_RENDERER_PROFILE_FUNCTION();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::Resize(const uint32_t width, const uint32_t height)
	{
		VLM_RENDERER_PROFILE_FUNCTION();

		if (width == 0 || height == 0 || width > s_maxFramebufferSize || height > s_maxFramebufferSize)
		{
			VLM_CORE_WARN("Attempted to resize framebuffer to {0}x{1}", width, height);

			return;
		}
		m_specification.Width = width;
		m_specification.Height = height;

		Recreate();
	}
}