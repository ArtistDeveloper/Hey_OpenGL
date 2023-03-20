#include "vertex_layout.h"

VertexLayoutUPtr VertexLayout::Create()
{
    auto vertexLayout = VertexLayoutUPtr(new VertexLayout());
    vertexLayout->Init();
    return std::move(vertexLayout);
}

VertexLayout::~VertexLayout()
{
    if (m_vertexArrayObject)
    {
        glDeleteVertexArrays(1, &m_vertexArrayObject);
    }
}

void VertexLayout::Bind() const
{
    glBindVertexArray(m_vertexArrayObject);
}

void VertexLayout::SetAttrib(
        uint32_t attribIndex, int count,
        uint32_t type, bool normalized,
        size_t stride, uint64_t offset
    ) const
{
    glEnableVertexAttribArray(attribIndex); // 0번 arrtribute 사용
    glVertexAttribPointer(attribIndex, count, type, normalized, stride, (const void*)offset);
    // 0번, arrtibute는 값이 3개고, float값이고, normalizing 할 필요없고, stride의 크기 설정하고, offset은 0부터 시작한다.
}

void VertexLayout::Init()
{
    glGenVertexArrays(1, &m_vertexArrayObject);
    Bind();
}
