#pragma once

#include "math.hpp"
#include "Framebuffer.hpp"
#include "Fonts.hpp"

class Renderer {
    public:
    Renderer(Framebuffer* fbuffer, PSF1_FONT* font);
    void Print(const char* str);
    void putChar(char chr, unsigned int xOff, unsigned int yOff);
    Point CursorPosition;
    Framebuffer* framebuffer;
    PSF1_FONT* psf1_font;
    unsigned int Colour;
};