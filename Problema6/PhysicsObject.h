#pragma once
#include "Vector2f.h"
#include <math.h>

class PhysicsObject 
{
public:
	Vector2f Position, Velocity, Force, Friction;
	float Mass;
	float ElasticK;
	

	PhysicsObject() {
		Mass = 0.0f;
		ElasticK = 1.0f;
		Friction.x = 0.1f;
		Friction.y = 0.0f;
	}

	PhysicsObject(Vector2f initial) {
		PhysicsObject::PhysicsObject();
		Position = initial;
	}

};

