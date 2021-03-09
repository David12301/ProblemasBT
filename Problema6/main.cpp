#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Window.h"
using namespace std;

int main()
{
    Window* mwindow = new Window(800, 600);
    mwindow->loop();
    delete mwindow;
    return 0;
}


