#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "image.h"

CLASS_PTR(Texture)
class Texture
{
public:
    // 왜 스마트포인터가 아닌 일반포인터를 선택한 것인가?
    // ImageUPtr: 이미지 인스턴스의 소유권이 함수 안으로 넘어오게 됨
    // ImagePtr: 이미지 인스턴스 소유권을 공유함
    // Image* 소유권과 상관없이 인스턴스에 접근 (선택).
    // - glTexImage2D 함수 호출을 제외하고는 Image 객체르 소유를 할 필요가 없기 때문에 일반 포인터 사용
    static TextureUPtr CreateFromImage(const Image *image);
    ~Texture();

    const uint32_t Get() const { return m_texture; }
    void Bind() const;
    void SetFilter(uint32_t minFilter, uint32_t magFilter) const;
    void SetWrap(uint32_t sWrap, uint32_t tWrap) const;

private:
    Texture() {}
    void CreateTexture();
    void SetTextureFromImage(const Image *image);

    uint32_t m_texture{0}; // 텍스처 오브젝트의 ID값
};

#endif // __TEXTURE_H__