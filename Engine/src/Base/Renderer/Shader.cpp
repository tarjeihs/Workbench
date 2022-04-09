#include "wbpch.h"
#include "Shader.h"

#include "RendererAPI.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Workbench
{
	Shader* Shader::Create(const std::string& vertexSource, const std::string& fragmentSource)
	{
		switch (RendererAPI::GetAPIType())
		{
			case RendererAPI::APIType::OpenGL: return new OpenGLShader(vertexSource, fragmentSource);
		}

		return nullptr;
	}
}