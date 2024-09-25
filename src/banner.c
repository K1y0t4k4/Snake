#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "banner.h"

void Pos(int x, int y)
{
    COORD pos;
    pos.X = x;
    pos.Y = y;

    HANDLE handleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(handleOutput, pos);
}

int** getColor(const int beginColor[], const int endColor[])
{
    int** colors = (int**)malloc(8 * sizeof(int*));
    for (int i=0; i<8; i++)
    {
        colors[i] = (int*)malloc(3 * sizeof(int));
    }
    
    float steps[8] = {0};
    for (int i=0; i<3; i++)
    {
        steps[i] = (endColor - beginColor) / 7;
    }
    for (int i=0; i<8; i++)
    {
        for (int j=0; j<3; j++)
        {
            colors[i][j] = beginColor[j] + (int)steps[j] * i;
        }
    }
    return colors;
}

void banner(void)
{
    char ban[8][100] = {
        "\e[38;2;200;0;0m _______  _        _______  _        _______ ",
        "\e[38;2;171;0;28m(  ____ \\( (    /|(  ___  )| \\    /\\(  ____ \\",
        "\e[38;2;142;0;57m| (    \\/|  \\  ( || (   ) ||  \\  / /| (    \\/",
        "\e[38;2;114;0;85m| (_____ |   \\ | || (___) ||  (_/ / | (__    ",
        "\e[38;2;85;0;114m(_____  )| (\\ \\) ||  ___  ||   _ (  |  __)   ",
        "\e[38;2;57;0;142m      ) || | \\   || (   ) ||  ( \\ \\ | (      ",
        "\e[38;2;28;0;171m/\\____) || )  \\  || )   ( ||  /  \\ \\| (____/\\",
        "\e[38;2;0;0;200m\\_______)|/    )_)|/     \\||_/    \\/(_______/\e[0m"
    };
    for (int i=0; i<8; i++)
    {
        Pos(73, 5+i);
        printf("%s", ban[i]);
    }
}