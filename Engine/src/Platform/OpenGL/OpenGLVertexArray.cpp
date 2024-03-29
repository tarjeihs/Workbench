#include "wbpch.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

#include "glad/glad.h"

namespace Workbench
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:    return GL_FLOAT;
			case ShaderDataType::Float2:   return GL_FLOAT;
			case ShaderDataType::Float3:   return GL_FLOAT;
			case ShaderDataType::Float4:   return GL_FLOAT;

			case ShaderDataType::Int:      return GL_INT;
			case ShaderDataType::Int2:     return GL_INT;
			case ShaderDataType::Int3:     return GL_INT;
			case ShaderDataType::Int4:     return GL_INT;

			case ShaderDataType::Mat3:     return GL_FLOAT;
			case ShaderDataType::Mat4:     return GL_FLOAT;

			case ShaderDataType::Bool:     return GL_BOOL;
		}

		WB_ENGINE_ASSERT(false, "Unknown specifier for ShaderDataType passed.");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		WB_ENGINE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "VertexBuffer has no layout.")

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& vertexLayout = vertexBuffer->GetLayout();
		for (const auto& element : vertexLayout)
		{
			switch (element.Type)
			{
				case ShaderDataType::Float:
				case ShaderDataType::Float2:
				case ShaderDataType::Float3:
				case ShaderDataType::Float4:
				{
					glEnableVertexAttribArray(index);
					glVertexAttribPointer(index,
						element.GetElementCount(),
						ShaderDataTypeToOpenGLBaseType(element.Type),
						element.Normalized ? GL_TRUE : GL_FALSE,
						vertexLayout.GetStride(),
						(const void*)element.Offset);
					index++;
					break;
				}
				case ShaderDataType::Int:
				case ShaderDataType::Int2:
				case ShaderDataType::Int3:
				case ShaderDataType::Int4:
				case ShaderDataType::Bool:
				{
					glEnableVertexAttribArray(index);
					glVertexAttribPointer(index,
						element.GetElementCount(),
						ShaderDataTypeToOpenGLBaseType(element.Type),
						element.Normalized ? GL_TRUE : GL_FALSE,
						vertexLayout.GetStride(),
						(const void*)element.Offset);
					index++;
					break;
				}
				case ShaderDataType::Mat3:
				case ShaderDataType::Mat4:
				{
					uint8_t count = element.GetElementCount();
					for (uint8_t i = 0; i < count; i++)
					{
						glEnableVertexAttribArray(index);
						glVertexAttribPointer(index,
							count,
							ShaderDataTypeToOpenGLBaseType(element.Type),
							element.Normalized ? GL_TRUE : GL_FALSE,
							vertexLayout.GetStride(),
							(const void*)(element.Offset + sizeof(float) * count * i));
						glVertexAttribDivisor(index, 1);
						index++;
					}
					break;
				}
				default:
					WB_ENGINE_ASSERT(false, "Type is out of scope.");
			}
		}

		m_VertexBufferVect.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::AddIndexBuffer(std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}
}