/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "game_object.h"


GameObject::GameObject()
    : Size(1.0f, 1.0f), Color(1.0f), Rotation(0.0f), Sprite(), IsSolid(false), Destroyed(false) { 
    RotationCenter.x = 0.5f;
    RotationCenter.y = 0.5f;
    phys.Position.x = 0.0f;
    phys.Position.y = 0.0f;
    //Initial.x = Initial.y = 0.0f;
    //Force.x = Force.y = 0.0f;
}

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec2 velocity)
    : Size(size), Color(color), Rotation(0.0f), Sprite(sprite), IsSolid(false), Destroyed(false) { 
    RotationCenter.x = 0.5f;
    RotationCenter.y = 0.5f;
    phys.Position.x = pos.x;
    phys.Position.y = pos.y;
    //Initial.x = Initial.y = 0.0f;
    //Force.x = Force.y = 0.0f;
}

void GameObject::Draw(SpriteRenderer& renderer)
{
    renderer.DrawSprite(this->Sprite, this->phys, this->Size, this->Rotation, this->Color, this->RotationCenter);
    //renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color, this->RotationCenter);
}