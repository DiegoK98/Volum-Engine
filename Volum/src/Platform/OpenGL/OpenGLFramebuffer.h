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

		void Invalidate();

		void Bind() override;
		void Unbind() override;

		virtual const uint32_t GetColorAttachmentRendererID() const override { return m_colorAttachment; }
	private:
		uint32_t m_rendererID;
		uint32_t m_colorAttachment, m_depthAttachment;
		FramebufferSpecification m_specification;
	};
}