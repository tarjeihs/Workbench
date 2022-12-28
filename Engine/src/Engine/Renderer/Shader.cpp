#include "wbpch.h"
#include "Engine/Renderer/Shader.h"

#include "Engine/Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Workbench
{
	std::shared_ptr<Shader> Shader::Create(const std::string& sourcePath)
	{
		switch (RendererAPI::GetAPIType())
		{
			case RendererAPI::APIType::OpenGL: return std::make_shared<OpenGLShader>(sourcePath);
		}

		return nullptr;
	}

	void ShaderLibrary::Add(const std::string& name, const std::shared_ptr<Shader>& shader)
	{
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const std::shared_ptr<Shader>& shader)
	{
		auto name = shader->GetName();
		Add(name, shader);
	}

	std::shared_ptr<Shader> ShaderLibrary::Load(const std::string& sourcePath)
	{
		auto shader = Shader::Create(sourcePath);
		Add(shader);
		return shader;
	}

	std::shared_ptr<Shader> ShaderLibrary::Load(const std::string& name, const std::string& sourcePath)
	{
		auto shader = Shader::Create(sourcePath);
		Add(shader);
		return shader;
	}

	std::shared_ptr<Shader> ShaderLibrary::Get(const std::string& name)
	{
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}
}