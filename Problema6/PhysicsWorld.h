#pragma once
#include <vector>
#include "game_object.h"
#include "Shape.h"
#include "Circle.h"
#include "Segment.h"

class PhysicsWorld {
public:
	std::vector<PhysicsObject*> Objects;
	float G, dt, t;


	Shape* objCollider1;
	Shape* objCollider2;
	Circle circleCollider1, circleCollider2;
	Segment segmentCollider1, segmentCollider2;

	PhysicsWorld();
	void Update();
	void CheckCollisions(PhysicsObject* object);
	void Round(Vector2f* v);
};