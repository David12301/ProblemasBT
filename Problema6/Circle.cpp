#include "Circle.h"
#include "Segment.h"

Circle::Circle() 
{
    radius = 0;
    center.x = 0.0f;
    center.y = 0.0f;
}
Circle::Circle(float x, float y, float r) {
    center.x = x;
    center.y = y;
    radius = r;
}

bool Circle::collidesWith(const Shape* s, Vector2f* tangent) const {
    return s->collidesWith(this, tangent);
}

bool Circle::collidesWith(const Circle* c, Vector2f* tangent) const {
    float dx = this->center.x - c->center.x;
    float dy = this->center.y - c->center.y;
    float length = sqrt( ((double)dx * dx) + ((double)dy * dy));

    if (length <= this->radius + c->radius) {
        if (tangent != nullptr) {
            float _m = -dx / dy; // pendiente perpendicular a la pendiente original
            float a = atan(_m);
            tangent->x = cos(a);
            tangent->y = sin(a);
        }
        return true;
    }
    return false;
}

bool Circle::collidesWith(const Segment* s, Vector2f* tangent) const {
    return s->collidesWith(this, tangent);
}

bool Circle::pointInside(const Vector2f point) const {
    float dx = this->center.x - point.x;
    float dy = this->center.y - point.y;
    float length = sqrt(((double)dx * dx) + ((double)dy * dy));
    return length <= this->radius;
}