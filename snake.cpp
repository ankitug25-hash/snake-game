#include<iostream>
#include<vector>
#include<algorithm>
#include<conio.h>
#include<windows.h>
using namespace std;
// height and weidth of the border
const int width = 20;
const int height = 10;
int x = (width - 2) / 2;  // snake head position
int y = (height - 2) / 2; // snake head position
int fruitx, fruity; // fruit position
int score = 0; // score of the game
// ----update : add snake body position and length here ----
vector<int> tailX; // vector to store x positions of snake body
vector<int> tailY; // vector to store y positions of snake body
int nTail = 0; // length of the snake body

enum direction {STOP =0, LEFT, RIGHT, UP, DOWN};
enum direction dir;
bool gameover;
void drawborder() {
    // clear all screen
    system("cls");
    // draw top border
    for(int i=0; i<width; i++) {
        cout << "█";
    }
    cout << endl;
    // draw left and right border
    for(int i=0; i<height-2; i++) {
        cout << "█"; // left border
        for(int j=0; j<width-2; j++) {
            // ----update : the snake head position and body position here ----
            if(i == y && j == x) {
                cout << "ö"; // snake head
            }
            else if(i == fruity && j == fruitx) {
                cout << "■"; // fruit
            }
            else {
                bool isTailPrinted = false;
                for(int k =0; k<nTail; k++) {
                    if(tailX[k] == j && tailY[k] == i) {
                        cout << "o";
                        isTailPrinted = true;
                        break;
                    }
                
                }
                if(!isTailPrinted) {
                    cout << " "; // space inside the border
                }   
            }
        }
        cout << "█"; // right border
        cout << endl;
    }
    // draw bottom border
    for(int i=0; i< width; i++) {
        cout << "█";
    }
    cout << endl;
    cout << "Score: " << score << endl;
}
void setup() {
    gameover = false;
    dir = STOP;
    x = (width - 2) / 2;
    y = (height - 2) / 2;
    // generate random fruit position
    fruitx = rand() % (width - 2);
    fruity = rand() % (height - 2);
    score = 0;
    // ----update : initialize the snake body position and length here ----
    nTail = 0;
    tailX.clear();
    tailY.clear();

}
void input() {
    if(_kbhit()) {
        switch(_getch()) {
            case 'a': dir = LEFT; break;
            case 'd': dir = RIGHT; break;
            case 'w': dir = UP; break;
            case 's': dir = DOWN; break;
            case 'x': gameover = true; break;
        }
    }
}
void logic() {
    // ----update : update the snake head position based on the direction here ----
    switch(dir) {
        case LEFT: x--; break;
        case RIGHT: x++; break;
        case UP: y--; break;
        case DOWN: y++; break;
    }
}

void checkcollision() {
    // ----update : check for collisoin with border or self here ----
    if(x < 0 || x >= width-2 || y <0 || y >= height -2) {
        gameover = true;

    }
    for(int i=0; i<nTail; i++) {
        if(tailX[i] == x && tailY[i] == y) {
            gameover = true;
            break;
        }
    }
    
}
void checkfruit() {
    // ----update : check if the snake eats the fruit here ----
    if(x == fruitx && y == fruity) {
        score += 10;
        nTail++; // increase the length of the snake body
        tailX.push_back(0); // add new position for the new tail segment
        tailY.push_back(0); // add new position for the new tail segment
        // generate new fruit position
        fruitx = rand() % (width - 2);
        fruity = rand() % (height - 2);
    }
}
void snakebody() {
    if(dir != STOP) {
       
    for(int i = nTail - 1; i > 0; i--) {
        tailX[i] = tailX[i-1];
        tailY[i] = tailY[i-1];
    }
    if(nTail > 0) {
        tailX[0] = x;
        tailY[0] = y;
    }
    }
}


int main() {
    setup(); // initialize the game
    while(!gameover) {
        drawborder(); // draw the game border and elements
        input(); // get user input and update the snake direction here
        logic(); // update the snake head position based on the direction here
        checkcollision(); // ----update : check for collision with border or self here ----
        checkfruit(); // ----update : check if the snake eats the fruit here ----
        snakebody(); // ----update : update the snake body position here ----   
        _sleep  (100); // delay to control the game speed
    }
    system("cls");
   cout << "=======================" << endl;
   cout << "      Game Over!       " << endl;
    cout << "=======================" << endl;
    cout << "Your final score is: " << score << endl;
    cout << "=======================" << endl;
    return 0;
}