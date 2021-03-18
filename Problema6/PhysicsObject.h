#pragma once
#include "Vector2f.h"
#include "Shape.h"
#include <math.h>

struct CollisionInfo {
	float cx, cy;
	float radius;
	//
	float x1, y1, x2, y2;
};

class PhysicsObject
{
public:
	Vector2f Position, Velocity, Force, Friction;
	Vector2f DPosition;
	float Mass;
	float ElasticK;
	bool affectedByGravity;
	bool collisionResponse;
	enum CollisionObjectType {CIRCLE, SEGMENT};
	int collisionObjectType;
	CollisionInfo collisionInfo;


	PhysicsObject() {
		Mass = 0.0f;
		ElasticK = 1.0f;
		Friction.x = 0.1f;
		Friction.y = 0.0f;
		affectedByGravity = true;
		collisionResponse = true;
		collisionObjectType = 0;
		//objCollision = nullptr;
	}

	~PhysicsObject() {
		//delete objCollision;
	}

	PhysicsObject(Vector2f initial) {
		PhysicsObject::PhysicsObject();
		Position = initial;
	}

};

