#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    char str[1000];
    int big_img[1536][2048] = {0};  // 配列の順序を修正 (y, x)
    int small_img[768][1024] = {0}; // 0で初期化
    int big_w, big_h, small_w, small_h;
    int d;
    int x, y;
    FILE *fp1, *fp2, *fp3;

    if (argc != 4) {
        printf("Usage: %s <big_image.pgm> <small_image.pgm> <output.pgm>\n", argv[0]);
        return 1;
    }

    // 大きい画像ファイルのオープン
    if ((fp1 = fopen(argv[1], "r")) == NULL) {
        perror(argv[1]);
        exit(1);
    }
    // 小さい画像ファイルのオープン
    if ((fp2 = fopen(argv[2], "r")) == NULL) {
        perror(argv[2]);
        fclose(fp1);
        exit(1);
    }
    // 出力ファイルのオープン
    if ((fp3 = fopen(argv[3], "w")) == NULL) {
        perror(argv[3]);
        fclose(fp1);
        fclose(fp2);
        exit(1);
    }
    
    // ヘッダの読み込み (大きい画像)
    fscanf(fp1, "%s", str);
    fscanf(fp1, "%d %d", &big_w, &big_h);
    fscanf(fp1, "%d", &d);

    // 配列の範囲外アクセスを防ぐチェック
    if (big_w > 2048 || big_h > 1536) {
        printf("Error: Big image dimensions exceed array size (2048x1536).\n");
        fclose(fp1);
        fclose(fp2);
        fclose(fp3);
        return 1;
    }

    // 画像部分を読み込む (大きい画像)
    for (y = 0; y < big_h; y++) {
        for (x = 0; x < big_w; x++) {
            if (fscanf(fp1, "%d", &(big_img[x][y])) != 1) {
                printf("Error reading big image at (%d, %d)\n", x, y);
                fclose(fp1);
                fclose(fp2);
                fclose(fp3);
                return 1;
            }
        }
    }
    fclose(fp1);

    // ヘッダの読み込み (小さい画像)
    fscanf(fp2, "%s", str);
    fscanf(fp2, "%d %d", &small_w, &small_h);
    fscanf(fp2, "%d", &d);

    // 配列の範囲外アクセスを防ぐチェック
    if (small_w > 1024 || small_h > 768) {
        printf("Error: Small image dimensions exceed array size (1024x768).\n");
        fclose(fp2);
        fclose(fp3);
        return 1;
    }

    // 画像部分を読み込む (小さい画像)
    for (y = 0; y < small_h; y++) {
        for (x = 0; x < small_w; x++) {
            if (fscanf(fp2, "%d", &(small_img[x][y])) != 1) {
                printf("Error reading small image at (%d, %d)\n", x, y);
                fclose(fp2);
                fclose(fp3);
                return 1;
            }
        }
    }
    fclose(fp2);

    // 小さい画像を大きい画像にはめ込む
    int offset_x = 5, offset_y = 5; // はめ込む位置を調整
    for (y = 0; y < small_h; y++) {
        for (x = 0; x < small_w; x++) {
            if ((y + offset_y) < big_h && (x + offset_x) < big_w) {
                big_img[x + offset_x][y + offset_y] = small_img[x][y];
            }
        }
    }

    // 出力
    fprintf(fp3, "P2\n%d %d\n%d\n", big_w, big_h, d);
    for (y = 0; y < big_h; y++) {
        for (x = 0; x < big_w; x++) {
            fprintf(fp3, "%d ", big_img[x][y]);
        }
        fprintf(fp3, "\n");
    }
    fclose(fp3);

    return 0;
}
