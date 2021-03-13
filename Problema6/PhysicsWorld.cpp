#include "PhysicsWorld.h"

PhysicsWorld::PhysicsWorld() {
	t = 0.0f;
	dt = 0.016f;
	G = 9.81f;
}

void PhysicsWorld::Update() {

	size_t size = Objects.size();
	for (int i = 0; i < size; i++) {
		PhysicsObject* object = Objects[i];

		Round(&object->Velocity);
		Round(&object->Position);
		Round(&object->Force);

		CheckCollisions(object);

		//float dt = t - object->t;

		// Por defecto le afecta la gravedad en el eje de Y
		if (object->affectedByGravity) {
			object->Force += Vector2f(0.0f, G * object->Mass);
		}
		
		// v = v0 + at
		// F = ma, a = F/m
		// v = v0 + (F/m)t
		object->Velocity += (object->Force / object->Mass) * dt;

		// x = x0 + vt
		object->Position += object->Velocity * dt;

		// resetear la fuerza resultante
		//object->Force = glm::vec2(0.0f, 0.0f);

	}

}

// Redondea hasta 3 decimales para no tener en cuenta valores demasiado pequeños
void PhysicsWorld::Round(Vector2f* v) {
	v->x = round(v->x * 1000.0f) / 1000.f;
	v->y = round(v->y * 1000.0f) / 1000.f;
}

void PhysicsWorld::CheckCollisions(PhysicsObject* object)
{
	size_t size = Objects.size();
	for (int i = 0; i < size; i++) {
		PhysicsObject* other = Objects[i];
		
		if (other != object) {

			if (object->objCollision && other->objCollision) {
				Vector2f tangent(0.0f, 0.0f);
				bool result = object->objCollision->collidesWith(other->objCollision, &tangent);
				if (result) {
					tangent.x = 0.0f;
				}

			}
		}
		
	}
}