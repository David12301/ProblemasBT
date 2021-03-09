#pragma once
#include <vector>
#include "game_object.h"

class PhysicsWorld {
public:
	std::vector<GameObject*> Objects;
	float G, dt, t;

	PhysicsWorld();
	void Update();
	void Round(Vector2f* v);
};