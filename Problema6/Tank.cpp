#include "Tank.h"
#include <iostream>

Tank::Tank(glm::vec2 pos, glm::vec2 size, Texture2D sprite, const Texture2D& gun_texture, const Texture2D& arrow_texture, const Texture2D& projectile_texture, 
    glm::vec3 color, glm::vec2 velocity) :
	GameObject(pos, size, sprite, color, velocity) {
	angle_shot = 0.0f;
	initial_shot_speed = 0.0f;
    move_speed = 2.0f;

    size = glm::vec2(10.0f, 40.0f);
    gun = new GameObject(glm::vec2(this->phys.Position.x + this->Size.x / 2 - size.x / 2,
        this->phys.Position.y - size.y), size, gun_texture);

    size = glm::vec2(10.0f, 37.5f);
    arrow = new GameObject(glm::vec2(this->phys.Position.x + this->Size.x / 2 - size.x / 2,
        this->phys.Position.y - size.y), size, arrow_texture);

    
    ptexture = projectile_texture;

    rad_angle_shot = 3.1415f / 2.0f;
    

    // Para que giren del extremo inferior en vez del centro de la imagen
    gun->RotationCenter.y = 1.0f;
    arrow->RotationCenter.y = 1.0f;

    mWorldRef = nullptr;

}



void Tank::update(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        angle_shot = angle_shot < -90.0f ? -90.0f : angle_shot - 0.5f;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        angle_shot = angle_shot > 90.0f ? 90.0f : angle_shot + 0.5f;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        phys.Position.x -= move_speed;
        this->gun->phys.Position.x -= move_speed;
        this->arrow->phys.Position.x -= move_speed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        phys.Position.x += move_speed;
        this->gun->phys.Position.x += move_speed;
        this->arrow->phys.Position.x += move_speed;
    }

    static bool pressed = false;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        initial_shot_speed += 0.5f;
        pressed = true;
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
        if (pressed) {
            shootBall();
            pressed = false;
        }
    }

   
    
    gun->Rotation = angle_shot;
    arrow->Rotation = angle_shot;

    
}

void Tank::Draw(SpriteRenderer& renderer) 
{
    GameObject::Draw(renderer);
    gun->Draw(renderer);
    arrow->Draw(renderer);

    size_t size = projectiles.size();
    for (int i = 0; i < size; i++) {
        projectiles[i]->Draw(renderer);
    }
    

}

void Tank::shootBall() 
{
    glm::vec2 size = glm::vec2(10.0f, 10.0f);
    GameObject* projectile = new GameObject(glm::vec2(0.0f, 0.0f), size, ptexture);

    projectile->phys.Mass = 0.1f;
    //projectile->t = mWorldRef->t;
    rad_angle_shot = (90 - angle_shot) * 3.1415f / 180.0f;

    projectile->phys.Position.x = this->phys.Position.x + this->Size.x / 2 - projectile->Size.x / 2 + (cos(rad_angle_shot) * gun->Size.y);
    projectile->phys.Position.y = this->phys.Position.y - this->Size.y + gun->Size.y/2 - (sin(rad_angle_shot) * gun->Size.y);

    //projectile->Position = projectile->Initial;
    projectile->phys.Velocity = Vector2f(0.0f, 0.0f);

    std::cout << "INITIAL_SPEED = " << initial_shot_speed << std::endl;
    
    projectile->phys.Force.x = initial_shot_speed * cos(rad_angle_shot);
    projectile->phys.Force.y = -initial_shot_speed * sin(rad_angle_shot);
    projectile->phys.Force.y *= 1.5;
    initial_shot_speed = 0.0f;

    projectiles.push_back(projectile);

    if(mWorldRef != nullptr)
        mWorldRef->Objects.push_back(projectile);
}

void Tank::setPhysicsWorld(PhysicsWorld* ref) 
{
    this->mWorldRef = ref;
}

Tank::~Tank() {
    size_t size = projectiles.size();
    for (int i = 0; i < size; i++) {
        delete projectiles[i];
    }
}