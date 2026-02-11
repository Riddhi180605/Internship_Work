#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>

using namespace std;

/* move cursor */
void gotoxy(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

/* hide cursor */
void hideCursor() {
    CONSOLE_CURSOR_INFO ci;
    ci.dwSize = 25;
    ci.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);
}

int main() {
    const int width = 40;
    const int height = 20;
    const int basketWidth = 7;

    int basketX = width / 2 - basketWidth / 2;
    int candyX, candyY;

    int score = 0;
    int life = 5;

    int fallDelay = 200; // candy speed (ms)

    srand(time(0));
    hideCursor();

    while (life > 0) {

        candyX = rand() % (width - 2) + 1;
        candyY = 1;

        DWORD lastFall = GetTickCount();

        while (candyY <= height) {

            /* fast input */
            if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
                if (basketX > 1) basketX--;
            }
            if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
                if (basketX + basketWidth < width)
                    basketX++;
            }

            /* candy movement by time */
            if (GetTickCount() - lastFall >= fallDelay) {
                candyY++;
                lastFall = GetTickCount();
            }

            gotoxy(0, 0);

            /* draw game */
            for (int y = 1; y <= height; y++) {
                for (int x = 1; x <= width; x++) {

                    if (x == candyX && y == candyY)
                        cout << "O";
                    else if (y == height &&
                             x >= basketX && x < basketX + basketWidth)
                        cout << "#";
                    else
                        cout << " ";
                }
                cout << "\n";
            }

            cout << "Score: " << score << "   Life: " << life << "\n";
            cout << "Controls: LEFT and RIGHT arrow keys\n";

            Sleep(10); // smooth refresh
        }

        /* check catch */
        if (candyX >= basketX && candyX < basketX + basketWidth) {
            score++;
            if (fallDelay > 60)
                fallDelay -= 10;   // increase difficulty
        } else {
            life--;
        }
    }

    system("cls");
    cout << "\n\n   GAME OVER\n";
    cout << "   Final Score: " << score << endl;

    return 0;
}
