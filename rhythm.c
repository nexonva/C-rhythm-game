#include <stdio.h>
#include <stdlib.h>
#include <windows.h>  // Header for SetConsoleCursorPosition and COORD structure
#include <conio.h>    // Header for kbhit() and getch() functions

void GotoXY(int x, int y) {
    COORD Pos;
    Pos.X = x;   // Set x coordinate
    Pos.Y = y;   // Set y coordinate
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);  // Move cursor to the specified position
}

void hideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// Function to check random position for the objects
int randomPosition() {
    return rand() % 4;  // Return a random value from 0 to 3, representing 4 possible positions
}

void game() {
    int Score = 0;
    int objectY[4] = {-1, -1, -1, -1};  // Y coordinates for 4 objects
    char input;
    int position;  // X position of the object
    int speed = 300; // Initial speed in ms

    hideCursor();  // Hide the cursor

    while (1) {
        // Clear the screen
        system("cls");

        // Display the score
        GotoXY(0, 0);  // Move cursor to (0,0) position
        printf("Score: %d\n", Score);

        // Display the objects
        for (int i = 0; i < 4; i++) {
            if (objectY[i] != -1) {
                GotoXY(i * 10, objectY[i]);  // Print object at its position
                printf("|");
            }
        }

        // Display the keys at the bottom (A, S, D, F)
        GotoXY(0, 18);  printf("A");
        GotoXY(10, 18); printf("S");
        GotoXY(20, 18); printf("D");
        GotoXY(30, 18); printf("F");

        // Check for user input
        if (kbhit()) {
            input = getch();
            if (input == 'a' && objectY[0] >= 18) {  // Hit object at first position
                Score++;  
                objectY[0] = -1;  // Remove object
            } else if (input == 's' && objectY[1] >= 18) {
                Score++;  
                objectY[1] = -1;  
            } else if (input == 'd' && objectY[2] >= 18) {
                Score++;  
                objectY[2] = -1;  
            } else if (input == 'f' && objectY[3] >= 18) {
                Score++;  
                objectY[3] = -1;  
            }
        }

        // Move the objects down
        for (int i = 0; i < 4; i++) {
            if (objectY[i] != -1) {
                objectY[i]++;  // Move the object down
                if (objectY[i] >= 20) {
                    objectY[i] = -1;  // Remove the object if it reaches the bottom
                    Score--;  // Subtract score
                }
            }
        }

        // Create new objects (20% chance) at random positions
        for (int i = 0; i < 4; i++) {
            if (objectY[i] == -1) {
                if (rand() % 5 == 0) {  // 20% chance to create a new object
                    objectY[i] = 3;  // Start the object at the top (y = 3)
                    position = randomPosition();
                    if (position == 0) {
                        GotoXY(0, objectY[i]);
                    } else if (position == 1) {
                        GotoXY(10, objectY[i]);
                    } else if (position == 2) {
                        GotoXY(20, objectY[i]);
                    } else {
                        GotoXY(30, objectY[i]);
                    }
                }
            }
        }

        // Adjust speed based on score
        if (Score > 5) speed = 250;
        if (Score > 10) speed = 200;
        if (Score > 20) speed = 150;

        // Set the speed of object movement (300ms delay)
        Sleep(speed);
    }
}

int main() {
    game();
    return 0;
}
