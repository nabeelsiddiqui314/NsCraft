#pragma once
#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <unordered_map>

class Shader
{
public:
	Shader() = default;
	Shader(const char* vertexPath, const char* fragmentPath);
public:
	void loadShader(const char* vertexPath, const char* fragmentPath);
	void bind();
	void unbind();
	void setUniformMat4(const std::string& name, const glm::mat4& val);
	void setUniform3f(const std::string& name, const glm::vec3& val);
	void setUniform1i(const std::string& name, int val);
	void setUniform1f(const std::string& name, float val);
	void setUniform4f(const std::string& name, const glm::vec4& val);
	GLint getUniformLocation(const std::string& name);
private:
	void CheckCompileErrors(GLuint shader, std::string type);
private:
	GLuint m_program;
	std::string m_vertexCode, m_fragmentCode;
	std::unordered_map<std::string, GLint> m_uniformCache;
};
