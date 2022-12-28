#pragma once

#include "Engine/Renderer/Shader.h"

#include <string>
#include <glm/glm.hpp>

// TODO: REMOVE!
typedef unsigned int GLenum;

namespace Workbench
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& sourcePath);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetInt(const std::string& name, int value) override;
		virtual void SetIntArray(const std::string& name, int* values, uint32_t coun) override;
		virtual void SetFloat(const std::string& name, float value) override;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) override;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) override;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) override;

		virtual const std::string& GetName() const override { return m_Name; }

		virtual void UploadUniformFloat(const std::string& name, const float value);
		virtual void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
		virtual void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
		virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

		virtual void UploadUniformInt(const std::string& name, const int value);
		virtual void UploadUniformIntArray(const std::string& name, int* values, uint32_t count);

		virtual void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		std::string CacheGLSLContent(const std::string& filepath);
		std::unordered_map<GLenum, std::string> TokenizeGLSLContent(const std::string& source);
		void Compile(std::unordered_map<GLenum, std::string>& sources);
	private:
		uint32_t m_RendererID;
		std::string m_Name;
	};
}