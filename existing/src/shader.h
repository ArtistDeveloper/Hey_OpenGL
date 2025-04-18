#ifndef __SHADER_H__
#define __SHADER_H__

#include "common.h"

// --CLASS_PTR(Shader)를 호출하면 이와 같은 형태가 나온다.-- //
// class Shader;
// using ShaderUPtr = std::unique_ptr<Shader>;
// using ShaderPtr = std::shared_ptr<Shader>;
// using ShaderWPtr = std::weak_ptr<Shader>;

CLASS_PTR(Shader);
class Shader {
public:
// https://rinthel.github.io/opengl_course/04_graphics_pipeline_and_shader_01#/43
// Shader클래스의 생성자를 호출하는 방법은 static 함수외에는 없게 하겠다.
  static ShaderUPtr CreateFromFile(const std::string& filename, GLenum shaderType); 

  ~Shader();
  uint32_t Get() const { return m_shader; }    
private:
  Shader() {}
  bool LoadFile(const std::string& filename, GLenum shaderType);
  uint32_t m_shader { 0 }; // OpenGL Shader Object ID
};

#endif // __SHADER_H__