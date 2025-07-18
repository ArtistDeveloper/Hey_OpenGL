#include "image.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

// 파일을 읽음
ImageUPtr Image::Load(const std::string &filepath)
{
    auto image = ImageUPtr(new Image());
    if (!image->LoadWithStb(filepath))
        return nullptr;
    return std::move(image);
}

Image::~Image()
{
    if (m_data)
    {
        stbi_image_free(m_data);
    }
}

bool Image::LoadWithStb(const std::string &filepath)
{
    stbi_set_flip_vertically_on_load(true);
    m_data = stbi_load(filepath.c_str(), &m_width, &m_height, &m_channelCount, 0);
    if (!m_data)
    {
        SPDLOG_ERROR("failed to load image: {}", filepath);
        return false;
    }
    return true;
}

ImageUPtr Image::Create(int width, int height, int channelCount)
{
    auto image = ImageUPtr(new Image());
    if (!image->Allocate(width, height, channelCount))
        return nullptr;
    return std::move(image);
}

bool Image::Allocate(int width, int height, int channelCount)
{
    m_width = width;
    m_height = height;
    m_channelCount = channelCount;
    m_data = (uint8_t *)malloc(m_width * m_height * m_channelCount);
    return m_data ? true : false;
}

void Image::SetCheckImage(int gridX, int gridY)
{
    for (int j = 0; j < m_height; j++)
    {
        for (int i = 0; i < m_width; i++)
        {
            int pos = (j * m_width + i) * m_channelCount; // 픽셀의 위치. 한 픽셀마다 channelCount만큼 사용하니 이를 곱함
            bool even = ((i / gridX) + (j / gridY)) % 2 == 0;
            uint8_t value = even ? 255 : 0;
            for (int k = 0; k < m_channelCount; k++)
                m_data[pos + k] = value;
            if (m_channelCount > 3)
                m_data[3] = 255;
        }
    }
}