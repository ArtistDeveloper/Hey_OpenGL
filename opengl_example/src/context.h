#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include "common.h"
#include "shader.h"
#include "program.h"

// 프로그램이 완전 종료가 되기 직전 메모리를 한 번에 정리하는게 좋음
// 이를 위해 Context 클래스에서 한 번에 묶어 관리
CLASS_PTR(Context)
class Context
{
public:
    static ContextUPtr Create();
    void Render();

private:
    Context() {}
    bool Init();
    ProgramUPtr m_program;

    uint32_t m_vertexArrayObject;
    uint32_t m_vertexBuffer;
    uint32_t m_indexBuffer;
};

#endif // __CONTEXT_H__