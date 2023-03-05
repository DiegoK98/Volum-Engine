#pragma once

#include "Volum/Renderer/Framebuffer.h"

namespace Volum
{
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecification& spec);
		virtual ~OpenGLFramebuffer();

		virtual const FramebufferSpecification& GetSpecification() const override { return m_specification; }

		void Recreate();

		void Bind() override;
		void Unbind() override;

		virtual void Resize(const uint32_t width, const uint32_t height) override;

		virtual const uint32_t GetColorAttachmentRendererID() const override { return m_colorAttachment; }
	private:
		uint32_t m_rendererID = 0;
		uint32_t m_colorAttachment = 0, m_depthAttachment = 0;
		FramebufferSpecification m_specification;
	};
}