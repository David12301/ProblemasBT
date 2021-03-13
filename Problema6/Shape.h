#pragma once
#include "Vector2f.h"

class Circle;
class Segment;

class Shape {
public:
    virtual bool collidesWith(const Shape* s, Vector2f* tangent) const = 0;
    virtual bool collidesWith(const Circle* c, Vector2f* tangent) const = 0;
    virtual bool collidesWith(const Segment* s, Vector2f* tangent) const = 0;
};

