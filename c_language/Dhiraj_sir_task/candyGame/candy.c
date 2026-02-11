#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

/* move cursor to x,y */
void gotoxy(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

int main() {
    int width = 40;
    int height = 20;
    int basketWidth = 7;
    int basketX = width / 2 - basketWidth / 2;

    int candyX, candyY;
    int score = 0, life = 5;

    srand(time(NULL));

    /* hide cursor */
    CONSOLE_CURSOR_INFO ci;
    ci.dwSize = 25;
    ci.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);

    while (life > 0) {

        candyX = (rand() % (width - 2)) + 2;
        candyY = 1;

        while (candyY <= height) {

            /* keyboard input */
            if (GetAsyncKeyState('A') & 0x8000) {
                if (basketX > 1) basketX--;
            }
            if (GetAsyncKeyState('D') & 0x8000) {
                if (basketX + basketWidth < width) basketX++;
            }

            gotoxy(0, 0);   // redraw screen (NO clear)

            /* draw game */
            for (int y = 1; y <= height; y++) {
                for (int x = 1; x <= width; x++) {

                    if (x == candyX && y == candyY) {
                        printf("0");   // candy
                    }
                    else if (y == height - 1 &&
                            (x == basketX || x == basketX + basketWidth - 1)) {
                        printf("#");   // basket top
                    }
                    else if (y == height &&
                            x >= basketX && x < basketX + basketWidth) {
                        printf("#");   // basket bottom
                    }
                    else {
                        printf(" ");
                    }
                }
                printf("\n");
            }

            printf("Score : %d   Life : %d   \n", score, life);

            candyY++;
            Sleep(120);
        }

        /* check catch */
        if (candyX >= basketX && candyX < basketX + basketWidth)
            score++;
        else
            life--;
    }

    gotoxy(0, height + 3);
    printf("GAME OVER\n");
    printf("Final Score : %d\n", score);

    return 0;
}
