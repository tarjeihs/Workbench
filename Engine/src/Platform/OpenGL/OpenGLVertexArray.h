#pragma once

#include "Base/Renderer/VertexArray.h"

namespace Workbench
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		virtual void AddIndexBuffer(std::shared_ptr<IndexBuffer>& indexBuffer) override;

		virtual inline const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBufferVect() const { return m_VertexBufferVect; }
		virtual inline const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; };
	private:
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBufferVect;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;

		uint32_t m_RendererID;
	};
}