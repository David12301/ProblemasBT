#pragma once
#include "Shape.h"

class Circle : Shape {
public:
    Vector2f center;
    float radius;

    Circle(float x, float y, float r);
    bool pointInside(const Vector2f point) const;
    bool collidesWith(const Circle& c) const;
    bool collidesWith(const Segment& s) const;
};