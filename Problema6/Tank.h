#pragma once


//#include <GLFW/glfw3.h>
#include "game_object.h"
#include <GLFW\glfw3.h>
#include "PhysicsWorld.h"
#include <vector>
#include "Projectile.h"

class Tank : public GameObject
{
	//using GameObject::GameObject;
public:

	GameObject* gun;
	GameObject* arrow;
	std::vector<Projectile*> projectiles;

	PhysicsWorld* mWorldRef;
	Texture2D ptexture;

	float angle_shot, rad_angle_shot;
	float move_speed;
	float initial_shot_speed;
	
	Tank(glm::vec2 pos, glm::vec2 size, Texture2D sprite, const Texture2D& gun_texture, const Texture2D& arrow_texture, const Texture2D& projectile_texture, 
		glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
	~Tank();
	void update(GLFWwindow* window);
	void Draw(SpriteRenderer& renderer);
	void shootBall();
	void setPhysicsWorld(PhysicsWorld* ref);
		
};