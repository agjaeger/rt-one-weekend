
#include <iostream>
#include "Image.h"

int main() {
    Image render (640, 480);

    for (int y = 0; y < render.height(); ++y) {
        for (int x = 0; x < render.width(); ++x) {
            Color c;
            c.r = x / float(render.width());
            c.g = y / float(render.height());
            c.b = 0;

            render.setPixel(x, y, c);
        }
    }

    render.write("render.png");
    return 0;
}
