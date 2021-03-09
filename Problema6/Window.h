#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "sprite_renderer.h"
#include "post_processor.h"
#include "game_object.h"
#include <vector>
#include "Tank.h"
#include "PhysicsWorld.h"

class Window {
private:
	GLFWwindow* window;
	SpriteRenderer* Renderer;
	PostProcessor* Effects;
	int width, height;
	std::vector<GameObject*> mObjects;

	/**/
	Tank* tank;
	PhysicsWorld* pworld;

public:
	Window(int w, int h);
	~Window();
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void processInput(GLFWwindow* window);
	void render();
	void loop();
	void loadObjects();
	void drawObjects();
	void updateObjects();
};