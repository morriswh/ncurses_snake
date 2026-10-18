#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

// #define COLOR_BG    "\033[48;2;0;0;0m"
// #define COLOR_FG      "\033[38;2;128;128;128m"
#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[48;2;128;0;0m"
#define COLOR_GREEN   "\033[48;2;0;128;0m"

char *getColor(uint8_t du) {
    char *color = (char*)malloc(30 * sizeof(char));;
    sprintf(color, "\033[48;2;%d;%d;%dm", du, du, du);
    return color;
}

void drawPixel(char *color, int *coords) {
    // char *color = getColor(du);
    printf("%s  " COLOR_RESET, color);
    // free(color);
}

// void showImage(int xDim, int yDim, int imageNumber, void *data, uint8_t dataType) {
// void showImage(images_t *images, int imageNumber) {
//     if (images->dataType != 8) {
//         printf("Data type not supported!\n");
//         exit(EXIT_FAILURE);
//     }
//
//     int imageStride = (int)images->dimensions[1] * (int)images->dimensions[2];
//
//     uint8_t *typedData = images->data;
//
//     for (int j = 0; j < images->dimensions[1]; j++) {
//         for (int i = 0; i < images->dimensions[2]; i++) {
//             drawPixel(typedData[imageStride * imageNumber 
//                       + i + images->dimensions[2] * j]);
//         }
//         printf("\n");
//     }
// }

// main for testing
int main() {

    // void *data = malloc(3 * 3 * sizeof(uint8_t));
    // uint8_t dummyData[] = {0, 32, 64, 96, 128, 160, 192, 224, 0};
    // memcpy(data, dummyData, 3 * 3 * sizeof(uint8_t));
    //
    // showImage(3,3,data,3);
    //
    // free(data);
    drawPixel(COLOR_GREEN);

    return 0;
}
