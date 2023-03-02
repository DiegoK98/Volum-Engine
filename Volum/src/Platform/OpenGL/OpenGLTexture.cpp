#include "vlmpch.h"

#include "OpenGLTexture.h"

#include <glad/gl.h>
#include <stb_image.h>

namespace Volum
{
	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
		: m_width(width), m_height(height), m_internalFormat(GL_RGBA8), m_dataFormat(GL_RGBA)
	{
		VLM_RENDERER_PROFILE_FUNCTION();

		glCreateTextures(GL_TEXTURE_2D, 1, &m_rendererID);
		glTextureStorage2D(m_rendererID, 1, m_internalFormat, m_width, m_height);

		glTexParameteri(m_rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(m_rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexParameteri(m_rendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(m_rendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		: m_path(path)
	{
		VLM_RENDERER_PROFILE_FUNCTION();

		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data;
		{
			VLM_RENDERER_PROFILE_SCOPE("stbi_load - OpenGLTexture2D::OpenGLTexture2D(const std::string&)");
			data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		}
		VLM_CORE_ASSERT(data, "Failed to load image!");

		GLenum internalFormat = 0, dataFormat = 0;
		switch (channels)
		{
			case 3:
				internalFormat = GL_RGB8;
				dataFormat = GL_RGB;
				break;
			case 4:
				internalFormat = GL_RGBA8;
				dataFormat = GL_RGBA;
				break;
			default:
				VLM_CORE_ASSERT(false, "Unexpected format in texture!");
		}

		m_width = width;
		m_height = height;

		m_internalFormat = internalFormat;
		m_dataFormat = dataFormat;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_rendererID);
		glTextureStorage2D(m_rendererID, 1, internalFormat, m_width, m_height);

		glTexParameteri(m_rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(m_rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexParameteri(m_rendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(m_rendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_rendererID, 0, 0, 0, m_width, m_height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		VLM_RENDERER_PROFILE_FUNCTION();

		glDeleteTextures(1, &m_rendererID);
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		VLM_RENDERER_PROFILE_FUNCTION();

		uint32_t channelSize = m_dataFormat == GL_RGBA ? 4 : 3;

		VLM_CORE_ASSERT(size == m_width * m_height * channelSize, "Data must be entire texture");
		glTextureSubImage2D(m_rendererID, 0, 0, 0, m_width, m_height, m_dataFormat, GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		VLM_RENDERER_PROFILE_FUNCTION();

		glBindTextureUnit(slot, m_rendererID);
	}
}