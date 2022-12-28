#pragma once

#include "Engine/Core/Base.h"
#include "Engine/Renderer/Renderer.h"

namespace Workbench
{
	struct FramebufferSpecification
	{
		uint32_t Width = 0;
		uint32_t Height = 0;
		uint32_t Sample = 1;

		bool SwapChainTarget = false;
	};

	class Framebuffer
	{
	public:
		virtual ~Framebuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;

		virtual uint32_t GetColorAttachmentRendererID() const = 0;

		virtual inline const FramebufferSpecification& GetSpecification() const = 0;

		static std::shared_ptr<Framebuffer> Create(const FramebufferSpecification& specification);
	};
}