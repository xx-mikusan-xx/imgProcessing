#include <stdio.h>
#include <stdlib.h>

void rotate_270(int **input_image, int **output_image, int width, int height) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            output_image[width - 1 - x][y] = input_image[y][x];
        }
    }
}

int main(int argc, char **argv) {
    char str[1000];
    int **img, **rotated_img;
    int w, h;
    int d;
    int x, y;
    FILE *fp1, *fp2;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input.pgm> <output.pgm>\n", argv[0]);
        exit(1);
    }

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
    rotated_img = (int **)malloc(w * sizeof(int *));
    for (y = 0; y < h; y++) {
        img[y] = (int *)malloc(w * sizeof(int));
    }
    for (x = 0; x < w; x++) {
        rotated_img[x] = (int *)malloc(h * sizeof(int));
    }

    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            fscanf(fp1, "%d", &img[y][x]);
        }
    }
    fclose(fp1);

    rotate_270(img, rotated_img, w, h);

    fprintf(fp2, "%s\n%d %d\n%d\n", str, h, w, d);
    for (x = 0; x < w; x++) {
        for (y = 0; y < h; y++) {
            fprintf(fp2, "%d ", rotated_img[x][y]);
        }
        fprintf(fp2, "\n");
    }
    fclose(fp2);

    for (y = 0; y < h; y++) {
        free(img[y]);
    }
    free(img);

    for (x = 0; x < w; x++) {
        free(rotated_img[x]);
    }
    free(rotated_img);

    return 0;
}
