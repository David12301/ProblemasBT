#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Window.h"
using namespace std;

const char* FILE_NAME = "chess.txt";

int main()
{
    Window* mwindow = new Window(800, 600);
    mwindow->loadChessBoard(FILE_NAME);
    mwindow->loop();
    delete mwindow;
    return 0;
}


