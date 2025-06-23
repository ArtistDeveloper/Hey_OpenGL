#include "program.h"

ProgramUPtr Program::Create(const std::vector<ShaderPtr> &shaders)
{
    auto program = ProgramUPtr(new Program());
    if (!program->Link(shaders))
        return nullptr;
    return std::move(program);
}

Program::~Program()
{
    if (m_program)
    {
        glDeleteProgram(m_program);
    }
}

bool Program::Link(const std::vector<ShaderPtr> &shaders)
{
    m_program = glCreateProgram();
    for (auto &shader : shaders)
        glAttachShader(m_program, shader->Get());
    glLinkProgram(m_program); // vertex, fragment 셰이더의 링크 시도

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

void Program::Use() const
{
    glUseProgram(m_program);
}

void Program::SetUniform(const std::string &name, int value) const
{
    auto loc = glGetUniformLocation(m_program, name.c_str());
    // unifrom 변수의 id를 unifrom에 전달하는 것이 아님. 슬롯 번호를 전달
    glUniform1i(loc, value); // value 번째 슬롯을 사용할 것이라 명시
}

void Program::SetUniform(const std::string &name, const glm::mat4 &value) const
{
    auto loc = glGetUniformLocation(m_program, name.c_str());
    // 첫 번째: location 번호, 두 번째: 매트릭스가 몇 개 들어갈지(배열도 들어갈 수 있어서)
    // 세 번째: 전치가 되어 있는지 아닌지,
    // 네 번째: 매트릭스의 첫 번째 위치를 value_ptr을 통해 주소값을 전달
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
}