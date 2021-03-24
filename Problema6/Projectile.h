#pragma once
#include "game_object.h"

class Projectile : public GameObject {
public: 
	float Life;
	float Decay;
	bool StartDecaying;
	Projectile() {
		Life = 1.0f;
		Decay = 0.05f;
		StartDecaying = false;
	}


	Projectile(glm::vec2 pos, glm::vec2 size, Texture2D sprite) : GameObject(pos, size, sprite)
	{
		Life = 1.0f;
		Decay = 0.01f;
		StartDecaying = false;
	}

	void Update() {
		if (StartDecaying) {
			Life = Life < 0.0f ? 0.0f : Life - Decay;
		}
		
	}

};