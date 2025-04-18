#include "shader.h"

ShaderUPtr Shader::CreateFromFile(const std::string& filename, GLenum shaderType) {
    auto shader = ShaderUPtr(new Shader());
    if (!shader->LoadFile(filename, shaderType))
        return nullptr;
    return std::move(shader);
}

Shader::~Shader() {
    if (m_shader) { // 정수값이 들어가있다면 셰이더가 만들어져 있다는 소리이다. 
        glDeleteShader(m_shader);
    }
}

bool Shader::LoadFile(const std::string& filename, GLenum shaderType) {
    auto result = LoadTextFile(filename);
    if (!result.has_value())
        return false;
    
    auto& code = result.value();
    const char* codePtr = code.c_str();
    int32_t codeLength = (int32_t)code.length();

    // create and compile shader
    m_shader = glCreateShader(shaderType); // 셰이더를 생성하고 정수로 셰이더 핸들 번호를 받음.
    // shaderCode를 여러개 가질 수 있다. 우선 여기선 하나니까 code와 code의 길이를 &를 통해 넘겨줌.
    glShaderSource(m_shader, 1, (const GLchar* const*)&codePtr, &codeLength); // 생성한 셰이더에 방금 로드한 코드를 집어넣는 과정. 
    glCompileShader(m_shader);

    // check compile error
    int success = 0;
    // i: int, v: vector => 즉 v가 붙으면 포인터를 붙여주어야 한다.
    glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[1024];
        glGetShaderInfoLog(m_shader, 1024, nullptr, infoLog);
        SPDLOG_ERROR("failed to compile shader: \"{}\"", filename);
        SPDLOG_ERROR("reason: {}", infoLog);
        return false;
    }
    return true;
}