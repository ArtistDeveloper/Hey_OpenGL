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
    size_t stride, uint64_t offset) const
{
    // attribIndex번째 버텍스 어레이를 사용
    glEnableVertexAttribArray(attribIndex);
    // attribIndex번째 어트리뷰트는 vertex shader의 location = attribInde와 연결됨
    // attribIndex번째 어트리뷰트가 생긴 형태는 해당 type의 값이 count개이고 (e.g. 0, 3, GL_FLOAT)
    // normalizing 안해도 되고 (GL_FALSE)
    // STRIDE의 크기 설정
    // offset이 나타내는 지점부터 시작한다
    glVertexAttribPointer(attribIndex, count,
                          type, normalized, stride, (const void *)offset);
}

void VertexLayout::Init()
{
    glGenVertexArrays(1, &m_vertexArrayObject);
    Bind();
}