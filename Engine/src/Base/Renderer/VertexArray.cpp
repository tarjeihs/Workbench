#include "wbpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Workbench
{
	VertexArray* VertexArray::Create()
	{
		switch (RendererAPI::GetAPIType())
		{
			case RendererAPI::APIType::OpenGL: return new OpenGLVertexArray();
		}
	}
}