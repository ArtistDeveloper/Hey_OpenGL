#include "program.h"

ProgramUPtr Program::Create(const std::vector<ShaderPtr> &shaders)
{
    auto program = ProgramUPtr(new Program());
    if (!program->Link(shaders))
        return nullptr;

    return std::move(program);
}

bool Program::Link(const std::vector<ShaderPtr> &shaders)
{
    m_program = glCreateProgram();

    // vertex, fragment shader가 attach된 후에 link를 시도함
    for (auto &shader : shaders)
        glAttachShader(m_program, shader->Get()); 
    glLinkProgram(m_program);

    // glGetProgramiv를 통해 LINK_SATUS의 성공실패를 받아올 수 있음
    int success = 0;
    glGetProgramiv(m_program, GL_LINK_STATUS, &success); 
    if (!success)
    {
        char infoLog[1024];
        glGetProgramInfoLog(m_program, 1024, nullptr, infoLog);
        SPDLOG_ERROR("failed to link program: {}", infoLog);
        return false;
    }
    return true;
}