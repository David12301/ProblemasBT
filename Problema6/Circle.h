#pragma once
#include "Shape.h"

class Circle : public Shape {
public:
    Vector2f center;
    float radius;

    Circle();
    Circle(float x, float y, float r);
    bool pointInside(const Vector2f point) const;
    bool collidesWith(const Shape* s, Vector2f* tangent) const;
    bool collidesWith(const Circle* c, Vector2f* tangent) const;
    bool collidesWith(const Segment* s, Vector2f* tangent) const;
};