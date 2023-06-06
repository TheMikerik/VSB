#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct{
    uint8_t idlength;
    uint8_t colormaptype;
    uint8_t datatypecode;      // Znaceni pro jednobitovy struct
    uint16_t colourmaporigin;  // Znaceni pro dvoubitovy struct
    uint16_t colourmaplength;
    uint8_t  colourmapdepth;
    uint16_t x_origin;
    uint16_t y_origin;
    uint16_t width;
    uint16_t height;
    uint8_t bitsperpixel;
    uint8_t imagedescriptor;
} TGA_Header;

int main(int argc, char* argv []){
    TGA_Header header = {0, 0, 2, 0, 0, 0, 0, 0, 1, 1, 24, 0};

    FILE* tga_out = fopen("image.tga", "wb");

    fwrite(&header.idlength, sizeof(header.idlength), 1, tga_out);
    fwrite(&header.colormaptype, sizeof(header.colormaptype), 1, tga_out);
    fwrite(&header.datatypecode, sizeof(header.datatypecode), 1, tga_out);
    fwrite(&header.colourmaporigin, sizeof(header.colourmaporigin), 1, tga_out);
    fwrite(&header.colourmaplength, sizeof(header.colourmaplength), 1, tga_out);
    fwrite(&header.colourmapdepth, sizeof(header.colourmapdepth), 1, tga_out);
    fwrite(&header.x_origin, sizeof(header.x_origin), 1, tga_out);
    fwrite(&header.y_origin, sizeof(header.y_origin), 1, tga_out);
    fwrite(&header.width, sizeof(header.width), 1, tga_out);
    fwrite(&header.height, sizeof(header.height), 1, tga_out);
    fwrite(&header.bitsperpixel, sizeof(header.bitsperpixel), 1, tga_out);
    fwrite(&header.imagedescriptor, sizeof(header.imagedescriptor), 1, tga_out);

    fclose(tga_out);

    return 0;
}