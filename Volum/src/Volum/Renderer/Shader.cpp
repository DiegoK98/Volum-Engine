#include "vlmpch.h"

#include "Shader.h"

#include "Volum/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Volum
{
	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				VLM_CORE_ASSERT(false, "RendererAPI::None is not supported!");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return CreateRef<OpenGLShader>(filepath);
		}

		VLM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			VLM_CORE_ASSERT(false, "RendererAPI::None is not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}

		VLM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader, const std::string& name)
	{
		auto& shaderName = name == "" ? shader->GetName() : name;
		VLM_CORE_ASSERT(!Exists(name), "Shader already exists!");
		m_shaders[shaderName] = shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath, const std::string& name)
	{
		auto shader = Shader::Create(filepath);
		Add(shader, name);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		VLM_CORE_ASSERT(Exists(name), "Shader not found!");

		return m_shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_shaders.find(name) != m_shaders.end();
	}
}