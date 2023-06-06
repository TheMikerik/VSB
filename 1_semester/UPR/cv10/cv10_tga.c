#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef unsigned char byte;

typedef struct {
    byte id_length;
    byte color_map_type;
    byte image_type;
    byte color_map[5];
    byte x_origin[2];
    byte y_origin[2];
    byte width[2];
    byte height[2];
    byte depth;
    byte descriptor;
} TGAHeader;

typedef struct {
    byte red;
    byte blue;
    byte green;
} PIXEL;

int get_widht(TGAHeader* header){ // widht a height je dvojrozmerne pole, proto jej timto zpusobem musime
    short widht;                  // prevest na jednorozmerne pole
    memcpy(&widht, header->width, sizeof(short)); // 1. kam chceme kopirovat (na jakou adresu - proto &) 2. odkud 3. kolik
    return widht;
}

int get_height(TGAHeader* header){
    short height;
    memcpy(&height, header->height, sizeof(short));
    return height;
}

void set_width(TGAHeader* header, short width){
    memcpy(header->width, &width, sizeof(short));
}

void set_height(TGAHeader*header, short height){
    memcpy(header->height, &height, sizeof(short));
}

int get_pixel_index(TGAHeader* header, int x, int y){
    return y * get_widht(header) + x;
}

void set_pixel(TGAHeader* header, PIXEL* pixels, int x, int y, byte red, byte blue, byte green){
    
    int index = get_pixel_index(header, x, y);
    pixels[index].blue = blue;
    pixels[index].red = red;
    pixels[index].green = green; 
    }

void tga_write(char* file_name){
    int widght = 100;
    int height = 100;

    TGAHeader header;
    header.id_length = 0; // neřešíme, tak ji nasstavíme na nuklu
    header.color_map_type = 0;
    header.image_type = 2; // viz skripta --> znací RBG obrazek
    header.color_map[5];
    header.x_origin[2] = 0; header.x_origin[1] = 0;
    
    header.y_origin[2] = 0; header.y_origin[1] = 0;
    set_width(&header, widght);
    set_height(&header, height);
    header.depth = 24;
    header.descriptor = 0;

    int pixels_count = widght * height;
    PIXEL* pixels = (PIXEL*)malloc(pixels_count*sizeof(pixels));
    for (int i = 0; i < widght; i++){
        for (int j = 0; j < height; j++){
            set_pixel(&header, pixels, i, j, 144, 200, 200);
        }
    }


    FILE *file = fopen(file_name, "wb");
    fwrite(&header, sizeof(TGAHeader), 1, file);
    fwrite(pixels, sizeof(PIXEL), pixels_count, file);

    fclose(file);
}

int main (){
    
    tga_write("obr.tga");

    return 0;
}