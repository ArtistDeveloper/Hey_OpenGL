#include "buffer.h"

/* 
    GL_ARRAY_BUFFER: vertex buffer object임. 
        position, color등이 들어가는 buffer라고 명시해서 바인딩해주는 것 
*/


BufferUPtr Buffer::CreateWithData(
    uint32_t bufferType, uint32_t usage,
    const void* data, size_t dataSize) {
    auto buffer = BufferUPtr(new Buffer());
    if (!buffer->Init(bufferType, usage, data, dataSize))
        return nullptr;
    return std::move(buffer);
}

Buffer::~Buffer() {
    if (m_buffer) {
        glDeleteBuffers(1, &m_buffer);
    }
}

void Buffer::Bind() const {
    glBindBuffer(m_bufferType, m_buffer);
}

bool Buffer::Init(
    uint32_t bufferType, uint32_t usage,
    const void* data, size_t dataSize) {
    m_bufferType = bufferType;
    m_usage = usage;
    glGenBuffers(1, &m_buffer);
    Bind();
    glBufferData(m_bufferType, dataSize, data, usage); // 바인딩되어 있는 버퍼에 데이터를 복사. 즉, 무조건 먼저 바인딩 해줘야 함.
    return true;
}