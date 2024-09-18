#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    char str[1000];
    int **img1, **img2, **combined;
    int w1, h1, w2, h2;
    int d;
    int x, y;
    FILE *fp1, *fp2, *fp3;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <input1> <input2> <output>\n", argv[0]);
        exit(1);
    }

    if ((fp1 = fopen(argv[1], "r")) == NULL) {
        perror(argv[1]);
        exit(1);
    }
    if ((fp2 = fopen(argv[2], "r")) == NULL) {
        perror(argv[2]);
        exit(1);
    }
    if ((fp3 = fopen(argv[3], "w")) == NULL) {
        perror(argv[3]);
        exit(1);
    }
    
    fscanf(fp1, "%s", str);
    fscanf(fp1, "%d %d", &w1, &h1);
    fscanf(fp1, "%d", &d);

    img1 = (int **)malloc(h1 * sizeof(int *));
    for (y = 0; y < h1; y++) {
        img1[y] = (int *)malloc(w1 * sizeof(int));
    }

    for (y = 0; y < h1; y++) {
        for (x = 0; x < w1; x++) {
            fscanf(fp1, "%d", &(img1[y][x]));
        }
    }
    fclose(fp1);

    fscanf(fp2, "%s", str);
    fscanf(fp2, "%d %d", &w2, &h2);
    fscanf(fp2, "%d", &d);

    img2 = (int **)malloc(h2 * sizeof(int *));
    for (y = 0; y < h2; y++) {
        img2[y] = (int *)malloc(w2 * sizeof(int));
    }

    for (y = 0; y < h2; y++) {
        for (x = 0; x < w2; x++) {
            fscanf(fp2, "%d", &(img2[y][x]));
        }
    }
    fclose(fp2);

    int new_width = w1 + w2;
    int new_height = (h1 > h2) ? h1 : h2;

    combined = (int **)malloc(new_height * sizeof(int *));
    for (y = 0; y < new_height; y++) {
        combined[y] = (int *)malloc(new_width * sizeof(int));
    }

    for (y = 0; y < new_height; y++) {
        for (x = 0; x < new_width; x++) {
            if (x < w1 && y < h1) {
                combined[y][x] = img1[y][x];
            } else if (x >= w1 && y < h2) {
                combined[y][x] = img2[y][x - w1];
            } else {
                combined[y][x] = 255; 
            }
        }
    }

    fprintf(fp3, "%s\n%d %d\n%d\n", str, new_width, new_height, d);
    for (y = 0; y < new_height; y++) {
        for (x = 0; x < new_width; x++) {
            fprintf(fp3, "%d ", combined[y][x]);
        }
        fprintf(fp3, "\n");
    }
    fclose(fp3);

    for (y = 0; y < h1; y++) {
        free(img1[y]);
    }
    free(img1);

    for (y = 0; y < h2; y++) {
        free(img2[y]);
    }
    free(img2);

    for (y = 0; y < new_height; y++) {
        free(combined[y]);
    }
    free(combined);

    return 0;
}
