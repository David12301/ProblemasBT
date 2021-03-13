#include "Segment.h"
#include "Circle.h"

Segment::Segment(float x1, float y1, float x2, float y2) {
    p1.x = x1;
    p1.y = y1;
    p2.x = x2;
    p2.y = y2;
}

float Segment::length() const {
    float dx = p2.x - p1.x;
    float dy = p2.y - p2.y;
    return sqrt(((double)dx * dx) + ((double)dy * dy));
}

Vector2f Segment::toVector() const {
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    float slope = dy / dx;
    float angle = atan(slope);
    return Vector2f(cos(angle), sin(angle));

}

bool Segment::collidesWith(const Shape* s, Vector2f* tangent) const {
    return s->collidesWith(this, tangent);
}

bool Segment::collidesWith(const Circle* c, Vector2f* tangent) const {

    if (c->pointInside(Vector2f(this->p1.x, this->p1.y)) || c->pointInside(Vector2f(this->p2.x, this->p2.y))) {
        //cout << "true" << endl;
        return true;
    }

    Vector2f v1(c->center.x - this->p1.x, c->center.y - this->p1.y);
    //cout << "v1(" << v1.x << ", " << v1.y << ")" << endl;
    Vector2f s1 = this->toVector();

    // onto es el vector proyectado
    Vector2f onto = v1.onto(s1);
    // Este vector proyectado desde el origen del segmento nos dará las 
    // coordenadas de una perpendicular hacia al centro del circulo
    Vector2f onto_point(this->p1.x + onto.x, this->p1.y + onto.y);
    //cout << "onto_point(" << onto_point.x << ", " << onto_point.y << ")" << endl;

    // Luego solo debemos preguntar si el tamaño de esa perpendicular es menor al radio
    float dx = c->center.x - onto_point.x;
    float dy = c->center.y - onto_point.y;
    float distance = sqrt(((double)dx * dx) + ((double)dy * dy));

    //cout << "distance with c.center(" << c.center.x << ", " << c.center.y << "): " << distance << endl;


    Vector2f vproyected(onto_point.x - this->p1.x, onto_point.y - this->p1.y);
    float segment_length = this->length();
    float proyected_length = vproyected.magnitude(); //en este caso es equivalente a la longitud del segmento

    Vector2f vsegment(p2.x - p1.x, p2.y - p1.y);

    // podemos usar el punto producto (w), si es que el angulo del segmento Vector (vsegment)
    // con el vector proyectado es mayor o igual a 90°, w será >= 0. Como vproyected apunta
    // al centro del circulo si w < 0 significa que el circulo aún está a la izquierda de vsegment
    // (angulo mayor a 90°) y no hay colisión.
    float w = vproyected * vsegment;

    //cout << "s1:(" << vsegment.x << ", " << vsegment.y << ")" << endl;
    //cout << "vproyected:(" << vproyected.x << ", " << vproyected.y << ")" << endl;
    //cout << "w: " << w << endl;
    //cout << "pry len: " << proyected_length << endl;
    //cout << "seg len: " << segment_length << endl;

    if (distance <= c->radius && segment_length >= proyected_length && w >= 0) {
        if (tangent != nullptr) {
            tangent->x = s1.x;
            tangent->y = s1.y;
        }
        return true;
    }
    
    return false;
}

bool Segment::collidesWith(const Segment* s, Vector2f* tangent) const {
    //Usando vectores direccionales como ecuaciones parametricas de cada segmento
    Vector2f v1(this->p2.x - this->p1.x, this->p2.y - this->p1.y);
    Vector2f v2(s->p2.x - s->p1.x, s->p2.y - s->p1.y);

    //cout << "v1: " << "(" << v1.x << ", " << v1.y << ")" << endl;
    //cout << "v2: " << "(" << v2.x << ", " << v2.y << ")" << endl;

    float det = v1.x * v2.y - v1.y * v2.x;
    //cout << "det: " << det << endl;
    // Si la determinante es 0, no puede haber colision
    if (det == 0) {
        //cout << "false" << endl;
        return false;
    }


    // Vector direccional apartir de los puntos de origen de los dos segmentos
    // el segmento 2 como punto final
    Vector2f directionalVector(s->p1.x - this->p1.x, s->p1.y - this->p1.y);
    //cout << "directionalVector: " << "(" << directionalVector.x << ", " << directionalVector.y << ")" << endl;

    float t1 = v2.y * directionalVector.x - v2.x * directionalVector.y;
    t1 /= det;
    //cout << "t1: " << t1 << endl;
    // No pueden intersecar si t1 NO esta entre 0 y 1
    if (0 > t1 || t1 > 1) {
        //cout << "false" << endl;
        return false;
    }

    // Recalcular el vector dirección. segmento 1 como punto final
    directionalVector.x = this->p1.x - s->p1.x;
    directionalVector.y = this->p1.y - s->p1.y;
    //cout << "directionalVector: " << "(" << directionalVector.x << ", " << directionalVector.y << ")" << endl;
    float t2 = -v1.y * directionalVector.x + v1.x * directionalVector.y;
    t2 /= det;

    //cout << "t2: " << t2 << endl;
    // No pueden intersecar si t2 NO esta entre 0 y 1
    if (0 > t2 || t2 > 1) {
        //cout << "false" << endl;
        return false;
    }

    if (tangent != nullptr) {
        tangent->x = t1;
        tangent->y = t2;
    }
    //cout << "true" << endl;

    return true;
}