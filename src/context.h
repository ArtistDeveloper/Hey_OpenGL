#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include "common.h"
#include "shader.h"
#include "program.h"
#include "buffer.h"
#include "vertex_layout.h"

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
    VertexLayoutUPtr m_vertexLayout;
	BufferUPtr m_vertexBuffer;
    BufferUPtr m_indexBuffer;
};

#endif