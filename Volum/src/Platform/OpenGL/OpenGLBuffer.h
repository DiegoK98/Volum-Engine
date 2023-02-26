#pragma once

#include "Renderer/Buffer.h"

namespace Volum
{
	////////// Vertex Buffer //////////

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetLayout(const BufferLayout& layout) override { m_layout = layout; }
		virtual const BufferLayout& GetLayout() const override { return m_layout; }

	private:
		uint32_t m_rendererID;
		BufferLayout m_layout;
	};

	////////// Index Buffer //////////

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual uint32_t GetCount() const override { return m_count; }
	private:
		uint32_t m_rendererID;
		uint32_t m_count;
	};
}