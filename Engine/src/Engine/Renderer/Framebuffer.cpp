#include "wbpch.h"
#include "Engine/Renderer/Framebuffer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Workbench
{
	std::shared_ptr<Framebuffer> Framebuffer::Create(const FramebufferSpecification& specification)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::APIType::OpenGL: return std::make_shared<OpenGLFramebuffer>(specification);
		}

		WB_ENGINE_ASSERT(false, "APIType is out of scope.");
		return nullptr;
	}
}