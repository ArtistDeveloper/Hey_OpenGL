#include "texture.h"

TextureUPtr Texture::CreateFromImage(const Image *image)
{
    auto texture = TextureUPtr(new Texture());
    texture->CreateTexture();
    texture->SetTextureFromImage(image);
    return std::move(texture);
}

Texture::~Texture()
{
    if (m_texture)
    {
        glDeleteTextures(1, &m_texture);
    }
}

void Texture::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, m_texture); // 앞으로 이용할 2D 텍스처는 m_texture에 저장된 핸들이 가리키는 텍스처
}

void Texture::SetFilter(uint32_t minFilter, uint32_t magFilter) const
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
}

void Texture::SetWrap(uint32_t sWrap, uint32_t tWrap) const
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sWrap); // S: X축에 해당
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tWrap); // T: Y축에 해당
}

void Texture::CreateTexture()
{
    glGenTextures(1, &m_texture); // 텍스처 오브젝트 1개 생성
    // bind and set default filter and wrap option
    Bind(); 
    SetFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    SetWrap(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
}

void Texture::SetTextureFromImage(const Image *image)
{
    GLenum format = GL_RGBA;
    switch (image->GetChannelCount())
    {
    default:
        break;
    case 1:
        format = GL_RED;
        break;
    case 2:
        format = GL_RG;
        break;
    case 3:
        format = GL_RGB;
        break;
    }

    // CPU에 로딩된 이미지를 GPU에 복사
    // 첫 번째: target. 대상이 될 바인딩 텍스처
    // 두 번째: mipmap에 사용되는 "레벨 값" (0 레벨이란 기본 이미지 사이즈. 커질수록 이미지 사이즈가 줄어듬)
    // 세 번째: 텍스처의 픽셀 포맷 (GPU에서 유지하려 하는 텍스처의 채널 타입)
    // 여섯번째: 텍스처 외곽의 border 크기
    // 일곱번째: 입력하는 이미지의 픽셀 포맷
    // 여덟번째: 입력하는 이미지의 채널별 데이터 타입
    // 아홉번쨰: 실제 이미지 데이터가 기록된 메모리 주소
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                 image->GetWidth(), image->GetHeight(), 0,
                 format, GL_UNSIGNED_BYTE,
                 image->GetData());

    // GPU에 복사된 이미지를 바탕으로 자동으로 1번, 2번 레벨의 이미지 등을 자동으로 생성해줌
    glGenerateMipmap(GL_TEXTURE_2D);
}