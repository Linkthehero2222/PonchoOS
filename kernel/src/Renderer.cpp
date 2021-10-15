#include "Renderer.hpp"

Renderer::Renderer(Framebuffer* fbuffer, PSF1_FONT* font) {
    framebuffer = fbuffer;
    psf1_font = font;
    Colour = 0xffffffff;
    CursorPosition = {0, 0};
}

void Renderer::Print(const char* str) {
    char* chr = (char*)str;
    while(*chr != 0) {
        putChar(*chr, CursorPosition.X, CursorPosition.Y);
        CursorPosition.X+=8;
        if(CursorPosition.X + 8 > framebuffer->Width) {
            CursorPosition.X = 0;
            CursorPosition.Y += 16;
        }
        chr++;
    }
}

void Renderer::putChar(char chr, unsigned int xOff, unsigned int yOff)
{
    unsigned int* pixPtr = (unsigned int*)framebuffer->BaseAddress;
    char* fontPtr = (char*)psf1_font->glyphBuffer + (chr * psf1_font->psf1_Header->charsize);
    for (unsigned long y = yOff; y < yOff + 16; y++) {
        for(unsigned long x = xOff; x < xOff+8; x++) {
            if((*fontPtr & (0b10000000 >> (x - xOff))) > 0) {
                *(unsigned int*)(pixPtr + x + (y * framebuffer->PixelsPerScanLine)) = Colour;
            }
        }
        fontPtr++;
    }
}