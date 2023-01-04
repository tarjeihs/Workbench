#pragma once

#include "Engine/Renderer/Object.h"

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

namespace Workbench
{
	class Shader : public Object
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetInt(const std::string& name, int value) = 0;
		virtual void SetIntArray(const std::string& name, int* value, uint32_t count) = 0;
		virtual void SetFloat(const std::string& name, float value) = 0;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;

		virtual const std::string& GetName() const = 0;

		static std::shared_ptr<Shader> Create(const std::string& sourcePath);
	private:
		uint32_t m_RendererID = 0;
	};

	class ShaderLibrary
	{
	public:
		void Add(const std::string& name, const std::shared_ptr<Shader>& shader);
		void Add(const std::shared_ptr<Shader>& shader);
		
		std::shared_ptr<Shader> Load(const std::string& sourcePath);
		std::shared_ptr<Shader> Load(const std::string& name, const std::string& sourcePath);

		std::shared_ptr<Shader> Get(const std::string& name);
		bool Exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, std::shared_ptr<Shader>> m_Shaders;
	};
}