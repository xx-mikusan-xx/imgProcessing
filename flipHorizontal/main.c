#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    char str[1000];
    int img[1024][768]; // 画像サイズにあわせて調節が必要
    int w, h; // 画像の大きさ
    int d;   // 画像の階調
    int x, y; // 画素を配列imgに読み込むためのループカウンタ:
    FILE *fp1, *fp2;

    if ((fp1 = fopen(argv[1], "r")) == NULL) {
        perror(argv[1]);
        exit(1);
    }
    if ((fp2 = fopen(argv[2], "w")) == NULL) {
        perror(argv[2]);
        exit(1);
    }
    // ヘッダの読み込み
    fscanf(fp1, "%s", str); // マジックナンバーの読込み
    fscanf(fp1, "%d %d", &w, &h); // 画像の大きさの読み込み
    fscanf(fp1, "%d", &d); // 画像の階調の読み込み

    // 画像部分を読み込む
    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            fscanf(fp1, "%d", &(img[x][y]));
        }
    }

    // 左右反転処理
    for (y = 0; y < h; y++) {
        for (x = 0; x < w / 2; x++) {
            int temp = img[x][y];
            img[x][y] = img[w - x - 1][y];
            img[w - x - 1][y] = temp;
        }
    }

    // 出力
    fprintf(fp2, "%s\n%d %d\n%d\n", str, w, h, d); // ヘッダ出力
    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            fprintf(fp2, "%d ", img[x][y]);
        }
        fprintf(fp2, "\n");
    }

    fclose(fp1);
    fclose(fp2);

    return 0;
}
