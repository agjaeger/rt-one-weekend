
#include "Image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

Image::Image (
    int p_width, 
    int p_height
) {
    m_width = p_width;
    m_height = p_height;
    
    m_pixels = std::unique_ptr<unsigned char[]>(new unsigned char[p_width * p_height * m_numChannels]);
}

void
Image::setPixel (
    uint p_x,
    uint p_y,
    Color p_c
) {
    assert(p_x < m_width);
    assert(p_y < m_height);

    unsigned int arrayPosition = (m_width * m_numChannels) * (m_height - 1 - p_y) + m_numChannels * p_x;

    unsigned char r = p_c.r * 255;
    unsigned char g = p_c.g * 255;
    unsigned char b = p_c.b * 255;

    m_pixels[arrayPosition + 0] = r;
    m_pixels[arrayPosition + 1] = g;
    m_pixels[arrayPosition + 2] = b;
}

void
Image::write (
    std::string p_filename
) {
    stbi_write_png (
        p_filename.c_str(), 
        m_width, m_height, m_numChannels, 
        m_pixels.get(),
        m_width * m_numChannels
    );
}

int
Image::height () {
    return m_height;
}

int
Image::width () {
    return m_width;
}