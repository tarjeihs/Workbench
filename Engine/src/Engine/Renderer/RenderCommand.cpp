#include "wbpch.h"
#include "Engine/Renderer/RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Workbench
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}