#ifndef __VERTEX_LAYOUT_H__
#define __VERTEX_LAYOUT_H__

#include "common.h"

CLASS_PTR(VertexLayout)
class VertexLayout
{
public:
    static VertexLayoutUPtr Create();
    ~VertexLayout();

    uint32_t Get() const { return m_vertexArrayObject; }
    void Bind() const;
    void SetAttrib(
        uint32_t attribIndex, int count,
        uint32_t type, bool normalized,
        size_t stride, uint64_t offset) const;
    void DisableAttrib(int attribIndex) const;

private:
    VertexLayout() {}
    void Init(); // VertexLayout의 초기화는 무조건 성공하기에 return 값이 존재하지 않음
    uint32_t m_vertexArrayObject{0};
};

#endif // __VERTEX_LAYOUT_H__