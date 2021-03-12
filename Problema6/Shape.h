#pragma once
#include "Vector2f.h"

class Circle;
class Segment;

class Shape {
public:
    virtual bool collidesWith(const Circle& c) const = 0;
    virtual bool collidesWith(const Segment& s) const = 0;
};

