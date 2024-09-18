#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int bilinear_interpolation(int **image, int width, int height, float x, float y) {
    int x1 = floor(x);
    int y1 = floor(y);
    int x2 = x1 + 1;
    int y2 = y1 + 1;

    if (x1 < 0 || x2 >= width || y1 < 0 || y2 >= height) {
        return 0; 
    }

    float a = x - x1;
    float b = y - y1;

    int I1 = (1 - a) * image[y1][x1] + a * image[y1][x2];
    int I2 = (1 - a) * image[y2][x1] + a * image[y2][x2];
    return (1 - b) * I1 + b * I2;
}

void rotate_image(int **input_image, int **output_image, int width, int height, float angle) {
    float radians = angle * M_PI / 180.0;
    float cos_angle = cos(radians);
    float sin_angle = sin(radians);

    int x_center = width / 2;
    int y_center = height / 2;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            float original_x = cos_angle * (x - x_center) + sin_angle * (y - y_center) + x_center;
            float original_y = -sin_angle * (x - x_center) + cos_angle * (y - y_center) + y_center;

            output_image[y][x] = bilinear_interpolation(input_image, width, height, original_x, original_y);
        }
    }
}

int main(int argc, char **argv) {
    char str[1000];
    int **img, **rotated_img;
    int w, h;
    int d;
    int x, y;
    float angle;
    FILE *fp1, *fp2;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <input.pgm> <output.pgm> <angle>\n", argv[0]);
        exit(1);
    }

    angle = atof(argv[3]);

    if ((fp1 = fopen(argv[1], "r")) == NULL) {
        perror(argv[1]);
        exit(1);
    }
    if ((fp2 = fopen(argv[2], "w")) == NULL) {
        perror(argv[2]);
        exit(1);
    }

    fscanf(fp1, "%s", str);
    fscanf(fp1, "%d %d", &w, &h);
    fscanf(fp1, "%d", &d);

    img = (int **)malloc(h * sizeof(int *));
    rotated_img = (int **)malloc(h * sizeof(int *));
    for (y = 0; y < h; y++) {
        img[y] = (int *)malloc(w * sizeof(int));
        rotated_img[y] = (int *)malloc(w * sizeof(int));
    }

    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            fscanf(fp1, "%d", &img[y][x]);
        }
    }
    fclose(fp1);

    rotate_image(img, rotated_img, w, h, angle);

    fprintf(fp2, "%s\n%d %d\n%d\n", str, w, h, d);
    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            fprintf(fp2, "%d ", rotated_img[y][x]);
        }
        fprintf(fp2, "\n");
    }

    fclose(fp2);

    for (y = 0; y < h; y++) {
        free(img[y]);
        free(rotated_img[y]);
    }
    free(img);
    free(rotated_img);

    return 0;
}
