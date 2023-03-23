#include "vlmpch.h"

#include "OpenGLVertexArray.h"

#include <glad/gl.h>

namespace Volum
{
	static GLenum ShaderDataTypeToOGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:    return GL_FLOAT;
			case ShaderDataType::Float2:   return GL_FLOAT;
			case ShaderDataType::Float3:   return GL_FLOAT;
			case ShaderDataType::Float4:   return GL_FLOAT;

			case ShaderDataType::Mat3:     return GL_FLOAT;
			case ShaderDataType::Mat4:     return GL_FLOAT;

			case ShaderDataType::Int:      return GL_INT;
			case ShaderDataType::Int2:     return GL_INT;
			case ShaderDataType::Int3:     return GL_INT;
			case ShaderDataType::Int4:     return GL_INT;

			case ShaderDataType::Bool:     return GL_BOOL;
		}

		VLM_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		VLM_RENDERER_PROFILE_FUNCTION();

		glCreateVertexArrays(1, &m_rendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		VLM_RENDERER_PROFILE_FUNCTION();

		glDeleteVertexArrays(1, &m_rendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		VLM_RENDERER_PROFILE_FUNCTION();

		glBindVertexArray(m_rendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		VLM_RENDERER_PROFILE_FUNCTION();

		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer> vertexBuffer)
	{
		VLM_RENDERER_PROFILE_FUNCTION();

		VLM_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size() != 0, "Vertex Buffer has no layout!");
		
		glBindVertexArray(m_rendererID);
		vertexBuffer->Bind();

		auto const& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			switch (element.Type)
			{
				case ShaderDataType::Float:
				case ShaderDataType::Float2:
				case ShaderDataType::Float3:
				case ShaderDataType::Float4:
				case ShaderDataType::Int:
				case ShaderDataType::Int2:
				case ShaderDataType::Int3:
				case ShaderDataType::Int4:
				case ShaderDataType::Bool:
				{
					glEnableVertexAttribArray(m_vertexBufferIndex);
					glVertexAttribPointer(m_vertexBufferIndex, element.GetComponentCount(), ShaderDataTypeToOGLBaseType(element.Type),
						element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.Offset);

					m_vertexBufferIndex++;
					break;
				}
				case ShaderDataType::Mat3:
				case ShaderDataType::Mat4:
				{
					uint8_t count = element.GetComponentCount();
					for (uint8_t i = 0; i < count; i++)
					{
						glEnableVertexAttribArray(m_vertexBufferIndex);
						glVertexAttribPointer(m_vertexBufferIndex, count, ShaderDataTypeToOGLBaseType(element.Type),
							element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)(element.Offset + sizeof(float) * count * i));
						glVertexAttribDivisor(m_vertexBufferIndex, 1);
						m_vertexBufferIndex++;
					}
					break;
				}
				default:
					VLM_CORE_ASSERT(false, "Unknown ShaderDataType!");
			}
		}

		m_vertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer> indexBuffer)
	{
		VLM_RENDERER_PROFILE_FUNCTION();

		glBindVertexArray(m_rendererID);
		indexBuffer->Bind();

		m_indexBuffer = indexBuffer;
	}
}
