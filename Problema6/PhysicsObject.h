#pragma once
#include "Vector2f.h"
#include "Shape.h"
#include <math.h>

class PhysicsObject 
{
public:
	Vector2f Position, Velocity, Force, Friction;
	float Mass;
	float ElasticK;
	bool affectedByGravity;
	Shape* objCollision;
	
	PhysicsObject() {
		Mass = 0.0f;
		ElasticK = 1.0f;
		Friction.x = 0.1f;
		Friction.y = 0.0f;
		affectedByGravity = true;
		objCollision = nullptr;
	}

	PhysicsObject(Vector2f initial) {
		PhysicsObject::PhysicsObject();
		Position = initial;
	}

};

