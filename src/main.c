/*
 Date: 2024.9.25
 Author: Kiyotaka
 Compiler: minGw-gcc
*/

#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

#include "banner.h"

typedef struct Node {
    int x;
    int y;
    struct Node* next;
} Node;

const int speed = 125;
const int initalX = 3;
const int initalY = 24;
const int HorizontalLength = 90;
const int VerticalLength = 39;

// Global variables
Node* head = NULL;
Node food = {0};
int failed = 0;
int started = 0;
int score = 0;
int direction = 3;
int directionX[4] = {0, 0, -1, 1};
int directionY[4] = {-1, 1, 0, 0};

void updataScore() 
{
    Pos(HorizontalLength + 1, 0);
    printf("Score: %d", score);
}

void text(void)
{
    if (started) {
        system("cls");
        updataScore();
        Pos(121, 4);
        printf("\t\t Use the \"w\", \"s\", \"a\" and \"d\" keys");
        Pos(121, 5);
        printf("\t\t\tto control the snake.");
    }
    else {
        system("cls");
        banner();
        Pos(85, 25);
        printf("Press \"ENTER\" to start");
        Pos(88, 27);
        printf("Press \"x\" to exit");
        Pos(81, 29);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED); // red
        printf("Note: Turn off capitalization");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }

    if (failed) {
        system("cls");
        
        for (int i = 0; i < 3; i++) {
            Pos(90, 25);
            printf("GAME OVER");
            Sleep(400);
            Pos(90, 25);
            printf("         ");
            Sleep(400);
        }

        Pos(89, 25);
        printf("GAME OVER");
    }
}

void box(void)
{   
    char charX = '-';
    char charY = '|';

    for (int i=0; i<HorizontalLength; i++) {
        charX = i == 0 || i == (HorizontalLength - 1) ? '+' : '-';
        Pos(i, 0);
        printf("%c", charX);
        Pos(i, VerticalLength - 1);
        printf("%c", charX);
    }

    for (int i=1; i<(VerticalLength - 1); i++) {
        Pos(0, i);
        printf("%c", charY);
        Pos(HorizontalLength - 1, i);
        printf("%c", charY);
    }
}

Node* snakeInit()
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->x = initalX;
    node->y = initalY;
    node->next = NULL;
}

int getDirection()
{
    int d;
    char ch = _getch();
    switch (ch) {
        case 'w':
            if (direction != 1) {
                d = 0;
            }
            break;
        case 's':
            if (direction != 0) {
                d = 1;
            }
            break;
        case 'a':
            if (direction != 3) {
                d = 2;
            }
            break;
        case 'd':
            if (direction != 2) {
                d = 3;
            }
            break;
        default:
            break;
    }
    return d;
}

int isInSnake()
{
    Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
        if (temp->x == head->x && temp->y == head->y) {
            return 1;
        }
    }
    return 0;
}

void createFood()
{
    int x = rand() % (HorizontalLength - 2) + 1;
    int y = rand() % (VerticalLength - 2) + 1;
    
    Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
        if (temp->x == x && temp->y == y) {
            createFood();
        }
    }
    
    food.x = x;
    food.y = y;
    Pos(food.x, food.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
    printf("@");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void snakeMove()
{
    Node* newHead = (Node*)malloc(sizeof(Node));
    newHead->x = head->x + directionX[direction];
    newHead->y = head->y + directionY[direction];
    newHead->next = head;
    head = newHead;

    Node* temp = head;

    if (head->x == food.x && head->y == food.y) {
        Pos(head->x, head->y);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
        printf("#");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

        score += 10;
        updataScore();
        createFood();
    }
    else {
        Pos(head->x, head->y);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
        printf("#");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        while (temp->next->next) {
            temp = temp->next;
        }
        Pos(temp->next->x, temp->next->y);
        printf(" ");
        free(temp->next);
        temp->next = NULL;
    }
    
    if (
        isInSnake() ||
        head->x == 0 ||
        head->x == (HorizontalLength - 1) ||
        head->y == 0 ||
        head->y == (VerticalLength - 1)
    ) {
        failed = 1;
    }

}


int main(void)
{
    SetConsoleTitle("Snake");
    srand((unsigned int)time(NULL));
    
    HANDLE handleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info = {1, 0};
    SetConsoleCursorInfo(handleOutput, &info);

    HWND handleWindows = GetConsoleWindow();
    ShowWindow(handleWindows, SW_MAXIMIZE);
    
    system("mode con cols=188 lines=52");
    text();
    char ch = _getch();
    switch (ch) {
        case 13:
            started = 1;
            break;
        case 'x':
            return 0;
            break;
        default:
            return 0;
            break;
    }
    setlocale(LC_ALL, "");
    head = snakeInit();
    text();
    box();

    Node* temp = head;
    createFood();
    while (!(failed)) {
        if (_kbhit()) {
            direction = getDirection();
        }
        snakeMove();
        Sleep(speed);
    }
    text();
    
    Pos(0, 52);
    printf("\n\n");
    return 0;
}