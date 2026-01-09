#pragma once

#include <string>

class ShaderProgram
{
public:
    ShaderProgram(const std::string& vsFile, const std::string& fsFile);
    ~ShaderProgram();

    void Use() const;

private:
    void AttachShader(const std::string& file, unsigned int type) const;
    void LinkProgram() const;

    unsigned int m_Id;
};
