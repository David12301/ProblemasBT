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
#include <math.h>
#include "Segment.h"


static float a = 90.0f;

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

    window = glfwCreateWindow(w, h, "Problema 6", NULL, NULL);

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
    ResourceManager::LoadTexture("img/tank.png", true, "tank");
    ResourceManager::LoadTexture("img/gun.png", true, "gun");
    ResourceManager::LoadTexture("img/ball.png", true, "ball");
    ResourceManager::LoadTexture("img/arrow.png", true, "arrow");
    ResourceManager::LoadTexture("img/line.png", true, "line");

    Effects = new PostProcessor(ResourceManager::GetShader("postprocessing"), this->width, this->height);
    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

    pworld = new PhysicsWorld;
    loadObjects();

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
    
    this->drawObjects();

    Effects->EndRender();
    
    Effects->Render(glfwGetTime());

}

void Window::loop() 
{
    double time = 0.0f;
    double count_sec = glfwGetTime();
    size_t frames = 0;
    while (!glfwWindowShouldClose(window))
    {
        time = glfwGetTime();
        processInput(window);
        updateObjects();
        render();
        glfwSwapBuffers(window);
        glfwPollEvents();

        //while ((glfwGetTime() - time) < 0.016);
        frames++;
        
        if ((glfwGetTime() - count_sec) >= 1.0) {
            count_sec = glfwGetTime();
            std::cout << "1 sec. Frames: " << frames << std::endl;
            frames = 0;
        }

    }
}

Window::~Window() 
{
    glfwTerminate();
    delete Renderer;
    delete Effects;
    for (int i = 0; i < mObjects.size(); i++) {
        delete mObjects[i];
    }
    delete pworld;
    std::cout << "Program terminated" << std::endl;
}   


void Window::loadObjects() 
{
    glm::vec2 pos = glm::vec2(64.0f, 64.0f);
    glm::vec2 size = glm::vec2(50.0f, 20.0);
    tank = new Tank(glm::vec2(0.0f, height-size.y), size, ResourceManager::GetTexture("tank"),
        ResourceManager::GetTexture("gun"), ResourceManager::GetTexture("arrow"), ResourceManager::GetTexture("ball"));

    

    tank->setPhysicsWorld(this->pworld);

    size = glm::vec2(800.0f, 2.0f);
    GameObject* line1 = new GameObject(glm::vec2(0.0f, height - size.y), size, ResourceManager::GetTexture("line"));
    line1->phys.Mass = 1.0f;
    line1->phys.affectedByGravity = false;
    float x1 = line1->phys.Position.x;
    float y1 = line1->phys.Position.y;
    float x2 = x1 + size.x;
    line1->phys.collisionObjectType = PhysicsObject::CollisionObjectType::SEGMENT;
    line1->phys.collisionInfo.x1 = x1;
    line1->phys.collisionInfo.x2 = x2;
    line1->phys.collisionInfo.y1 = y1;
    line1->phys.collisionInfo.y2 = y1;
    line1->phys.collisionResponse = false;
    line1->phys.Friction.x = 0.1f;
    line1->phys.Friction.y = 0.1f;
    line1->phys.ElasticK = 0.9f;


    size = glm::vec2(2.0f, 800.0f);
    GameObject* line2 = new GameObject(glm::vec2(0.0f, 0.0f), size, ResourceManager::GetTexture("line"));
    line2->phys.Mass = 1.0f;
    line2->phys.affectedByGravity = false;
    line2->phys.collisionObjectType = PhysicsObject::CollisionObjectType::SEGMENT;
    line2->phys.collisionInfo.x1 = 0.0f;
    line2->phys.collisionInfo.x2 = 0.0f;
    line2->phys.collisionInfo.y1 = 0.0f;
    line2->phys.collisionInfo.y2 = size.y;
    line2->phys.collisionResponse = false;
    line2->phys.Friction.x = 0.1f;
    line2->phys.Friction.y = 0.1f;
    line2->phys.ElasticK = 0.9f;


    float x3 = 798.0f;
    GameObject* line3 = new GameObject(glm::vec2(x3, 0.0f), size, ResourceManager::GetTexture("line"));
    line3->phys.Mass = 1.0f;
    line3->phys.affectedByGravity = false;
    line3->phys.collisionObjectType = PhysicsObject::CollisionObjectType::SEGMENT;
    line3->phys.collisionInfo.x1 = x3;
    line3->phys.collisionInfo.x2 = x3;
    line3->phys.collisionInfo.y1 = 0.0f;
    line3->phys.collisionInfo.y2 = size.y;
    line3->phys.collisionResponse = false;
    line3->phys.Friction.x = 0.1f;
    line3->phys.Friction.y = 0.1f;
    line3->phys.ElasticK = 0.9f;

    //size = glm::vec2(20.0f, 80.0f);
    //gun = new GameObject(glm::vec2(tank->Position.x + tank->Size.x/2 - size.x/2, 
    //    tank->Position.y - size.y), size, ResourceManager::GetTexture("gun"));
    //
    //size = glm::vec2(20.0f, 75.0f);
    //arrow = new GameObject(glm::vec2(tank->Position.x + tank->Size.x / 2 - size.x / 2,
    //    tank->Position.y - size.y), size, ResourceManager::GetTexture("arrow"));

    //// Para que giren del extremo inferior en vez del centro de la imagen
    //gun->RotationCenter.y = 1.0f;
    //arrow->RotationCenter.y = 1.0f;

    //tank->gun = gun;
    //tank->arrow = arrow;

    pworld->Objects.push_back(&line1->phys);
    pworld->Objects.push_back(&line2->phys);
    pworld->Objects.push_back(&line3->phys);

    mObjects.push_back(tank);
    mObjects.push_back(line1);
    mObjects.push_back(line2);
    mObjects.push_back(line3);
    //mObjects.push_back(gun);
    //mObjects.push_back(arrow);

}

void Window::updateObjects() 
{
    pworld->Update();
    tank->update(window);
    
}

void Window::drawObjects() 
{
    for (int i = 0; i < mObjects.size(); i++)
    {
        mObjects[i]->Draw(*Renderer);
    }
}