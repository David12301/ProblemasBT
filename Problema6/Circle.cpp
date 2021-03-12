#include "Circle.h"
#include "Segment.h"

Circle::Circle(float x, float y, float r) {
    center.x = x;
    center.y = y;
    radius = r;
}

bool Circle::collidesWith(const Circle& c) const {
    float dx = this->center.x - c.center.x;
    float dy = this->center.y - c.center.y;
    float length = sqrt( ((double)dx * dx) + ((double)dy * dy));
    return length <= this->radius + c.radius;
}

bool Circle::collidesWith(const Segment& s) const {
    return s.collidesWith(*this);
}

bool Circle::pointInside(const Vector2f point) const {
    float dx = this->center.x - point.x;
    float dy = this->center.y - point.y;
    float length = sqrt(((double)dx * dx) + ((double)dy * dy));
    return length <= this->radius;
}