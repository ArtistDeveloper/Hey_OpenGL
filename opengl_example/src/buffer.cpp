#include "buffer.h"

BufferUPtr Buffer::CreateWithData(uint32_t bufferType, uint32_t usage,
                                  const void *data, size_t dataSize)
{
    auto buffer = BufferUPtr(new Buffer());
    if (!buffer->Init(bufferType, usage, data, dataSize))
        return nullptr;
    return std::move(buffer);
}

Buffer::~Buffer()
{
    if (m_buffer)
    {
        glDeleteBuffers(1, &m_buffer);
    }
}

void Buffer::Bind() const
{
    // GL_STATIC_DRAW: GPU 버퍼에 값을 세팅하고 다시는 변경하지 않을 것임을 명시
    // GL_DYANMIC_DRAW: 값을 변경할 여지가 있음을 명시
    // GL_STREAM:DRAW: 값을 한 번 사용한 뒤 바로 버릴 예정임을 명시
    glBindBuffer(m_bufferType, m_buffer); // buffer object 지정 및 용도 지정
}

bool Buffer::Init(uint32_t bufferType, uint32_t usage,
                  const void *data, size_t dataSize)
{
    m_bufferType = bufferType;
    m_usage = usage;
    glGenBuffers(1, &m_buffer); // Buffer Object를 생성
    Bind();
    glBufferData(m_bufferType, dataSize, data, usage); // 바인딩한 버퍼 오브젝트에 실제로 데이터를 복사
    return true;
}