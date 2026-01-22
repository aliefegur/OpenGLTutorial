#include "ShaderProgram.h"

#include <glad/glad.h>
#include <iostream>

#include "../Utils/File.h"

ShaderProgram::ShaderProgram(const std::string& vsFile, const std::string& fsFile)
{
    m_Id = glCreateProgram();
    AttachShader(vsFile, GL_VERTEX_SHADER);
    AttachShader(fsFile, GL_FRAGMENT_SHADER);
    LinkProgram();
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(m_Id);
}

void ShaderProgram::Use() const
{
    glUseProgram(m_Id);
}

unsigned int ShaderProgram::GetID() const
{
    return m_Id;
}

ShaderProgram::operator unsigned int() const
{
	return m_Id;
}

void ShaderProgram::AttachShader(const std::string& file, unsigned int type) const
{
    unsigned int shader = glCreateShader(type);
    std::string srcStr = File::Read(file);
    const char* src = srcStr.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    int isCompiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if (!isCompiled)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "Failed to compile shader!" << std::endl
            << "Shader File: " << file << std::endl
            << infoLog << std::endl;

        throw "Failed to compile shader!";
    }

    glAttachShader(m_Id, shader);
    glDeleteShader(shader);
}

void ShaderProgram::LinkProgram() const
{
    glLinkProgram(m_Id);

    int isLinked;
    glGetProgramiv(m_Id, GL_LINK_STATUS, &isLinked);
    if (!isLinked)
    {
        char infoLog[512];
        glGetProgramInfoLog(m_Id, 512, nullptr, infoLog);
        std::cout << "Failed to link shader program!" << std::endl
            << "Shader Program ID: 0x" << std::hex << m_Id << std::endl
            << infoLog << std::endl;

        throw "Failed to link shader program!";
    }
}
