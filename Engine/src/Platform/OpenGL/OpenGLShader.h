#pragma once

#include "Base/Renderer/Shader.h"

#include <string>
#include <glm/glm.hpp>

namespace Workbench
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void UploadUniformFloat(const char* name, const float value);
		virtual void UploadUniformFloat2(const char* name, const glm::vec2& value);
		virtual void UploadUniformFloat3(const char* name, const glm::vec3& value);
		virtual void UploadUniformFloat4(const char* name, const glm::vec4& value);

		virtual void UploadUniformInt(const char* name, const int value);
		virtual void UploadUniformInt2(const char* name, const glm::vec2& value);
		virtual void UploadUniformInt3(const char* name, const glm::vec3& value);
		virtual void UploadUniformInt4(const char* name, const glm::vec4& value);

		virtual void UploadUniformMat3(const char* name, const glm::mat3& matrix);
		virtual void UploadUniformMat4(const char* name, const glm::mat4& matrix);
	private:
		uint32_t m_RendererID;
	};
}