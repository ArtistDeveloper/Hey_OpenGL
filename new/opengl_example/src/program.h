#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#include "common.h"
#include "shader.h"

// Program: 각각의 Shader를 연결한 파이프라인을 의미
CLASS_PTR(Program)
class Program
{
public:
    static ProgramUPtr Create(const std::vector<ShaderPtr> &shaders);
    ~Program();
    uint32_t Get() const { return m_program; }

private:
    Program() {}
    bool Link(const std::vector<ShaderPtr> &shaders);
    uint32_t m_program{0};
};

#endif __PROGRAM_H__