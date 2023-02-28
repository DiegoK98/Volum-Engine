#pragma once

#include "Volum/Renderer/Shader.h"

#include <glm/glm.hpp>

// Forw decl (TODO: Remove)
typedef unsigned int GLenum;

namespace Volum
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const std::string& GetName() const override { return m_name; }

		virtual void UploadUniformInt(const std::string& name, const int value) override;

		virtual void UploadUniformFloat(const std::string& name, const float value) override;
		virtual void UploadUniformFloat2(const std::string& name, const glm::vec2& values) override;
		virtual void UploadUniformFloat3(const std::string& name, const glm::vec3& values) override;
		virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& values) override;

		virtual void UploadUniformMat3(const std::string& name, const glm::mat3& matrix) override;
		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) override;
	
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

		uint32_t m_rendererID;
		std::string m_name;
	};
}