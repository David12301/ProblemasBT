#pragma once
#include "Shape.h"

class Segment : public Shape {
public:
    Vector2f p1;
    Vector2f p2;
    Segment();
    Segment(float x1, float y1, float x2, float y2);
    float length() const;
    Vector2f toVector() const;
    bool collidesWith(const Shape* s, Vector2f* tangent) const ;
    bool collidesWith(const Circle* c, Vector2f* tangent) const;
    bool collidesWith(const Segment* s, Vector2f* tangent) const;
};