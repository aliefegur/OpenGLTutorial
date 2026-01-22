#pragma once

#include <string>

class ShaderProgram
{
public:
    ShaderProgram(const std::string& vsFile, const std::string& fsFile);
    ~ShaderProgram();

    void Use() const;

    unsigned int GetID() const;
    operator unsigned int() const;

private:
    void AttachShader(const std::string& file, unsigned int type) const;
    void LinkProgram() const;

    unsigned int m_Id;
};
