#ifndef __SHADER_H__
#define __SHADER_H__

#include "common.h"

CLASS_PTR(Shader);
class Shader
{
public:
    // CreateFromFile로만 Shader 객체를 생성할 수 있게 만들도록, 생성자를 private으로 선언
    // 그리고 UPtr형태로 강제하기 위함
    static ShaderUPtr CreateFromFile(const std::string &filename, GLenum shaderType);

    ~Shader();
    uint32_t Get() const { return m_shader; }

private:
    Shader() {}
    bool LoadFile(const std::string &filename, GLenum shaderType);
    uint32_t m_shader{0}; // OpenGL에서 반환 해주는 shader 오브젝트의 id
};

#endif // __SHADER_H__