#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned char b;
    unsigned char g;
    unsigned char r;
} Pixel;

typedef struct {
    unsigned char header[54];
    int width;
    int height;
    Pixel *pixels;
} BMPImage;

BMPImage* read_bmp(const char* filename);
void write_bmp(const char* filename, BMPImage* image);
void encode_message(BMPImage* image, const char* message);
char* decode_message(BMPImage* image, int message_length);

int main() {
    const char* bmp_file_path = "D:\\2nd Semester\\Algorithm and Programming Practicum\\MODUL 3 try\\input.bmp";
    const char* text_file_path = "D:\\2nd Semester\\Algorithm and Programming Practicum\\MODUL 3 try\\message.txt";
    const char* output_file_path = "D:\\2nd Semester\\Algorithm and Programming Practicum\\MODUL 3 try\\output.bmp";

    BMPImage* image = read_bmp(bmp_file_path);
    if (image == NULL) {
        printf("Error reading BMP file from %s\n", bmp_file_path);
        return 1;
    }

    FILE *textFile = fopen(text_file_path, "r");
    if (textFile == NULL) {
        printf("Error opening text file from %s\n", text_file_path);
        free(image->pixels);
        free(image);
        return 1;
    }

    fseek(textFile, 0, SEEK_END);
    long message_length = ftell(textFile);
    fseek(textFile, 0, SEEK_SET);

    char *message = (char*)malloc(message_length + 1);
    fread(message, 1, message_length, textFile);
    message[message_length] = '\0';

    fclose(textFile);

    encode_message(image, message);
    write_bmp(output_file_path, image);

    BMPImage* encoded_image = read_bmp(output_file_path);
    if (encoded_image == NULL) {
        printf("Error reading encoded BMP file from %s\n", output_file_path);
        free(message);
        free(image->pixels);
        free(image);
        return 1;
    }

    char* decoded_message = decode_message(encoded_image, message_length);

    printf("Decoded message: %s\n", decoded_message);

    free(message);
    free(decoded_message);
    free(image->pixels);
    free(image);
    free(encoded_image->pixels);
    free(encoded_image);

    return 0;
}

BMPImage* read_bmp(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening BMP file");
        return NULL;
    }

    BMPImage* image = (BMPImage*)malloc(sizeof(BMPImage));
    if (fread(image->header, sizeof(unsigned char), 54, file) != 54) {
        printf("Error reading BMP header.\n");
        fclose(file);
        free(image);
        return NULL;
    }

    
    if (image->header[0] != 'B' || image->header[1] != 'M') {
        printf("Not a valid BMP file.\n");
        fclose(file);
        free(image);
        return NULL;
    }

    image->width = *(int*)&image->header[18];
    image->height = *(int*)&image->header[22];
    int size = image->width * image->height;

    image->pixels = (Pixel*)malloc(size * sizeof(Pixel));
    if (image->pixels == NULL) {
        printf("Error allocating memory for BMP pixels.\n");
        fclose(file);
        free(image);
        return NULL;
    }

    if (fread(image->pixels, sizeof(Pixel), size, file) != size) {
        printf("Error reading BMP pixel data.\n");
        fclose(file);
        free(image->pixels);
        free(image);
        return NULL;
    }

    fclose(file);
    return image;
}

void write_bmp(const char* filename, BMPImage* image) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }
    fwrite(image->header, sizeof(unsigned char), 54, file);
    fwrite(image->pixels, sizeof(Pixel), image->width * image->height, file);
    fclose(file);
}

void encode_message(BMPImage* image, const char* message) {
    int message_length = strlen(message);
    int bit_index = 0;

    for (int i = 0; i < message_length; i++) {
        for (int bit = 0; bit < 8; bit++) {
            int pixel_index = bit_index / 3;
            int color_index = bit_index % 3;

            unsigned char* color;
            switch (color_index) {
                case 0: color = &image->pixels[pixel_index].r; break;
                case 1: color = &image->pixels[pixel_index].g; break;
                case 2: color = &image->pixels[pixel_index].b; break;
            }

            *color = (*color & 0xFE) | ((message[i] >> bit) & 1);
            bit_index++;
        }
    }
}

char* decode_message(BMPImage* image, int message_length) {
    char* message = (char*)malloc(message_length + 1);
    int bit_index = 0;

    for (int i = 0; i < message_length; i++) {
        message[i] = 0;
        for (int bit = 0; bit < 8; bit++) {
            int pixel_index = bit_index / 3;
            int color_index = bit_index % 3;

            unsigned char color;
            switch (color_index) {
                case 0: color = image->pixels[pixel_index].r; break;
                case 1: color = image->pixels[pixel_index].g; break;
                case 2: color = image->pixels[pixel_index].b; break;
            }

            message[i] |= (color & 1) << bit;
            bit_index++;
        }
    }

    message[message_length] = '\0';
    return message;
}
