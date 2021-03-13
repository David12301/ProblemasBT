#pragma once
#include <vector>
#include "game_object.h"

class PhysicsWorld {
public:
	std::vector<PhysicsObject*> Objects;
	float G, dt, t;

	PhysicsWorld();
	void Update();
	void CheckCollisions(PhysicsObject* object);
	void Round(Vector2f* v);
};