#pragma once
#include "Shape.h"

class Segment : Shape {
public:
    Vector2f p1;
    Vector2f p2;
    Segment(float x1, float y1, float x2, float y2);
    float length() const;
    Vector2f toVector() const;
    bool collidesWith(const Circle& c) const;
    bool collidesWith(const Segment& s) const;
};