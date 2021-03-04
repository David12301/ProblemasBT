#pragma once
#include "Window.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "resource_manager.h"

#include <iostream>
#include <sstream>
#include <fstream>


Window::Window(int w, int h) 
{
    this->width = w;
    this->height = h;
    this->window = nullptr;

    
     

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // para macos

    window = glfwCreateWindow(w, h, "Problema 2", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, this->framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    // load shaders
    ResourceManager::LoadShader("sprite.vs", "sprite.fs", nullptr, "sprite");
    //ResourceManager::LoadShader("particle.vs", "particle.fs", nullptr, "particle");
    ResourceManager::LoadShader("post_processing.vs", "post_processing.fs", nullptr, "postprocessing");
    // configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->width), static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    // load textures
    ResourceManager::LoadTexture("img/board.jpg", false, "board");

    ResourceManager::LoadTexture("img/k.png", true, "K");
    ResourceManager::LoadTexture("img/q.png", true, "Q");
    ResourceManager::LoadTexture("img/b.png", true, "B");
    ResourceManager::LoadTexture("img/n.png", true, "N");
    ResourceManager::LoadTexture("img/r.png", true, "R");
    ResourceManager::LoadTexture("img/p.png", true, "P");


    ResourceManager::LoadTexture("img/_k.png", true, "k");
    ResourceManager::LoadTexture("img/_q.png", true, "q");
    ResourceManager::LoadTexture("img/_b.png", true, "b");
    ResourceManager::LoadTexture("img/_n.png", true, "n");
    ResourceManager::LoadTexture("img/_r.png", true, "r");
    ResourceManager::LoadTexture("img/_p.png", true, "p");

    Effects = new PostProcessor(ResourceManager::GetShader("postprocessing"), this->width, this->height);
    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

    glViewport(0, 0, w, h);
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Window::processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void Window::render()
{
    Effects->BeginRender();
    
    Renderer->DrawSprite(ResourceManager::GetTexture("board"), glm::vec2(0.0f, 0.0f), glm::vec2(this->width, this->height), 0.0f);
    
    this->drawChessBoard(glm::vec2(68.0f, 35.0f));

    Effects->EndRender();
    
    Effects->Render(glfwGetTime());

}

void Window::loop() 
{
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

Window::~Window() 
{
    glfwTerminate();
    delete Renderer;
    delete Effects;
    for (int i = 0; i < mPieces.size(); i++) {
        delete mPieces[i];
    }
    std::cout << "Program terminated" << std::endl;
}


void Window::loadChessBoard(const char* fname) 
{
    std::ifstream mFile(fname);
    std::stringstream mSS;

    mSS << mFile.rdbuf();
    mFile.close();

    std::string strData = mSS.str();

    if (strData.length() == 0) {
        std::cout << "No se encontraron datos para cargar. Cree un archivo llamado chess.txt para cargar los datos." << std::endl;
        //Por default es la posición inicial de ajedrez
        strData = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
    }

    //strData = "7Q/2Rp4/2pN4/p2rp3/P2N4/B1k5/2PpRb2/3K2n1";

    const glm::vec2 PIECE_SIZE(30.0f, 55.0f);
    const glm::vec2 espacio_extra(90.0f, 67.5f);
    int len = strData.length();

    for (int i = 0, x = 0, y = 0; i < len; i++) {

        if (strData[i] == '/') {
            x = 0;
            y++;
        }
        else {

            if (isdigit(strData[i])) {
                int n = atoi(&strData[i]);
                x += n;
            }
            else {
                glm::vec2 pos = glm::vec2(x * espacio_extra.x, y * espacio_extra.y);
                std::string texture_name(1, strData[i]);
                GameObject* p = new GameObject(glm::vec2(0.0f, 0.0f), PIECE_SIZE, ResourceManager::GetTexture(texture_name));
                p->Initial = pos;
                this->mPieces.push_back(p);
                x++;
            }
        }
    }
}

void Window::drawChessBoard(glm::vec2 initPosition) 
{
    for (int i = 0; i < mPieces.size(); i++)
    {
        mPieces[i]->Position = initPosition + mPieces[i]->Initial;
        mPieces[i]->Draw(*Renderer);
    }
}