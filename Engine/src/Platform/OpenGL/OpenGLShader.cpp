#include "wbpch.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include "Engine/Core/Timer.h"

#include <fstream>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Workbench
{
	namespace Utils
	{
		static std::string CacheGLSLContent(const char* filepath)
		{
			std::string content;
			std::ifstream fileStream(filepath, std::ios::in);

			WB_ENGINE_ASSERT(fileStream.is_open(), "Unable to read file.");

			std::string line = "";
			while (!fileStream.eof())
			{
				std::getline(fileStream, line);
				content.append(line + "\n");
			}

			fileStream.close();
			return content;
		}

		static uint32_t GLSLTypeFromString(const std::string& type)
		{
			if (type == "vertex") return GL_VERTEX_SHADER;
			if (type == "fragment") return GL_FRAGMENT_SHADER;
			if (type == "pixel") return GL_FRAGMENT_SHADER;

			WB_ENGINE_ASSERT(false, "Specified GLSL shader type does not exist.");
			return 0;
		}
	}

	OpenGLShader::OpenGLShader(const std::string& sourcePath)
	{
		std::string source = CacheGLSLContent(sourcePath);
		auto sourceTokens = TokenizeGLSLContent(source);
		Compile(sourceTokens);

		auto lastSlash = sourcePath.find_last_of("/\\");
		auto lastDot = sourcePath.rfind(".");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto count = lastDot == std::string::npos ? sourcePath.size() - lastSlash : lastDot - lastSlash;
		m_Name = sourcePath.substr(lastSlash, count);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		UploadUniformInt(name.c_str(), value);
	}

	void OpenGLShader::SetIntArray(const std::string& name, int* value, uint32_t count)
	{
		UploadUniformIntArray(name, value, count);
	}

	void OpenGLShader::SetFloat(const std::string& name, float value)
	{
		UploadUniformFloat(name, value);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
		UploadUniformFloat3(name, value);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
		UploadUniformFloat4(name, value);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
	{
		UploadUniformMat4(name, value);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, const float value)
	{
		GLint uniformLocation = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(uniformLocation, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value)
	{
		GLint uniformLocation = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(uniformLocation, value.x, value.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
	{
		GLint uniformLocation = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(uniformLocation, value.x, value.y, value.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value)
	{
		GLint uniformLocation = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(uniformLocation, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, const int value)
	{
		GLint uniformLocation = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(uniformLocation, value);
	}

	void OpenGLShader::UploadUniformIntArray(const std::string& name, int* values, uint32_t count)
	{
		GLint uniformLocation = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1iv(uniformLocation, count, values);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		GLint uniformLocation = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint uniformLocation = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	// Utils

	std::string OpenGLShader::CacheGLSLContent(const std::string& sourcePath)
	{
		auto lastSlash = sourcePath.find_last_of("/\\");
		auto lastDot = sourcePath.rfind(".");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto count = lastDot == std::string::npos ? sourcePath.size() - lastSlash : lastDot - lastSlash;
		m_Name = sourcePath.substr(lastSlash, count);

		return Utils::CacheGLSLContent(sourcePath.c_str());
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::TokenizeGLSLContent(const std::string& source)
	{
		const char* token = "#type";
		size_t tokenLength = strlen(token);
		size_t offset = source.find(token, 0);

		std::unordered_map<GLuint, std::string> result;

		while (offset != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", offset);
			size_t begin = offset + tokenLength + 1;
			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			
			std::string type = source.substr(begin, eol - begin);

			WB_ENGINE_ASSERT(eol != std::string::npos, "Shader tokenize syntax error.");
			WB_ENGINE_ASSERT(Utils::GLSLTypeFromString(type), "Failed to specify valid shader type.");
			WB_ENGINE_ASSERT(nextLinePos != std::string::npos, "Shader tokenize syntax error.");

			offset = source.find(token, nextLinePos);
			
			result[Utils::GLSLTypeFromString(type)] =
				(offset == std::string::npos) ? source.substr(nextLinePos) :
				source.substr(nextLinePos, offset - nextLinePos);
		}
		return result;
	}

	void OpenGLShader::Compile(std::unordered_map<GLenum, std::string>& sources)
	{
		Timer timer;

		GLuint program = glCreateProgram();

		std::array<GLuint, 2> glShaderId;
		int glShaderIndex = 0;

		for (auto& kv : sources)
		{
			GLuint id = kv.first;
			const std::string& source = kv.second;

			GLuint shader = glCreateShader(id);
		
			// Send the vertex shader source code to GL
			// Note that std::string's .c_str is NULL character terminated.
			const char* sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);
		
			// Compile the vertex shader
			glCompileShader(shader);

			int compileStatus = 0;

			glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
			if (compileStatus == GL_FALSE)
			{
				int maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shader anymore.
				glDeleteShader(shader);

				WB_ENGINE_ERROR("{0}", infoLog.data());
				WB_ENGINE_ASSERT(false, "Shader compilation failure.");

				return;
			}

			glAttachShader(program, shader);
			glShaderId[glShaderIndex++] = shader;
		}
		
		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.

		m_RendererID = program;

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		int linkStatus = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
		if (linkStatus == GL_FALSE)
		{
			int maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
			
			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteProgram(program);

			// Don't leak shaders either.
			for (auto id : glShaderId) 
				glDeleteShader(id);

			WB_ENGINE_ERROR("{0}", infoLog.data());
			WB_ENGINE_ASSERT(false, "Shader compilation failure.");

			return;
		}

		// Always detach shaders after a successful link.
		for (auto id : glShaderId)
			glDetachShader(program, id);

		WB_ENGINE_INFO("Shader compilation time: {0} ms", timer.ElapsedMilliseconds());
	}
}