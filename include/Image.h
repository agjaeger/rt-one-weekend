
#pragma once

#include <string>
#include <memory>
#include <cassert>

#include "Vector3.h"

namespace rtow {
    namespace render {
        class Image {
            public:
                Image(int width, int height);               // Object constructor
                ~Image() = default;                         // Object destructor    

                Image(const Image&) = delete;               // Copy constructor
                Image& operator=(const Image&) = delete;    // Copy assignment operator

                Image(Image&&) = delete;                    // Move constructor
                Image& operator=(Image&&) = delete;         // Move assignment operator

                void setPixel(uint x, uint y, rtow::math::Vector3 c);
                void write(std::string filename);
                
                int height();
                int width();
                
            private:
                int m_width;
                int m_height;
                const int m_numChannels = 3;
                
                std::unique_ptr<unsigned char[]> m_pixels;
        };
    };
};