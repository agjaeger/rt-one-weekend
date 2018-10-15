
#include "Image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

rtow::render::Image::Image (
    int p_width, 
    int p_height
) {
    m_width = p_width;
    m_height = p_height;
    m_pixels = std::unique_ptr<unsigned char[]>(new unsigned char[p_width * p_height * m_numChannels]);
}

void
rtow::render::Image::setPixel (
    uint p_x,
    uint p_y,
    rtow::math::Vector3 p_c
) {
    assert(p_x < m_width);
    assert(p_y < m_height);

    unsigned int arrayPosition = (m_width * m_numChannels) * (m_height - 1 - p_y) + m_numChannels * p_x;

    m_pixels[arrayPosition + 0] = (unsigned char)(p_c.r() * 255.99);
    m_pixels[arrayPosition + 1] = (unsigned char)(p_c.g() * 255.99);
    m_pixels[arrayPosition + 2] = (unsigned char)(p_c.b() * 255.99);
}

void
rtow::render::Image::write (
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
rtow::render::Image::height () {
    return m_height;
}

int
rtow::render::Image::width () {
    return m_width;
}