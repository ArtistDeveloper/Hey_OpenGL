#include "shader.h"

ShaderUPtr Shader::CreateFromFile(const std::string &filename, GLenum shaderType)
{
    auto shader = std::unique_ptr<Shader>(new Shader());
    if (!shader->LoadFile(filename, shaderType))
        return nullptr;
    return std::move(shader);
}

Shader::~Shader()
{
    if (m_shader)
    {
        glDeleteShader(m_shader);
    }
}

bool Shader::LoadFile(const std::string &filename, GLenum shaderType)
{
    auto result = LoadTextFile(filename);
    if (!result.has_value())
        return false;

    // result 안의 string이 길다면 레퍼런스로 받는게 좋다
    auto &code = result.value();
    const char *codePtr = code.c_str();
    int32_t codeLength = (int32_t)code.length();

    // 셰이더 생성 및 컴파일
    m_shader = glCreateShader(shaderType);                                     // 생성된 셰이더는 정수 번호로 반환된다
    glShaderSource(m_shader, 1, (const GLchar *const *)&codePtr, &codeLength); // 셰이더에 코드를 넣어 세팅
    glCompileShader(m_shader);                                                 // 컴파일

    // 컴파일 에러 체크
    int success = 0;
    // i:int, v:vector(포인터라고 생각)
    glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success); // 셰이더의 컴파일 상태를 받아옴
    if (!success)
    {
        char infoLog[1024]; // 에러 로그를 받아올 버퍼
        glGetShaderInfoLog(m_shader, 1024, nullptr, infoLog);
        SPDLOG_ERROR("failed to compile shader: \"{}\"", filename);
        SPDLOG_ERROR("reason: {}", infoLog);
        return false;
    }
    return true;
}