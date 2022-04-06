#include "wbpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Workbench
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}