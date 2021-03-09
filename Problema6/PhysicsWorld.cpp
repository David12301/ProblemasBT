#include "PhysicsWorld.h"

PhysicsWorld::PhysicsWorld() {
	t = 0.0f;
	dt = 0.016f;
	G = 9.81f;
}

void PhysicsWorld::Update() {

	size_t size = Objects.size();
	for (int i = 0; i < size; i++) {
		GameObject* object = Objects[i];

		Round(&object->phys.Velocity);
		Round(&object->phys.Position);
		Round(&object->phys.Force);

		//float dt = t - object->t;

		// Por defecto le afecta la gravedad en el eje de Y
		object->phys.Force += Vector2f(0.0f, G * object->phys.Mass);


		// v = v0 + at
		// F = ma, a = F/m
		// v = v0 + (F/m)t
		object->phys.Velocity += (object->phys.Force / object->phys.Mass) * dt;

		// x = x0 + vt
		object->phys.Position += object->phys.Velocity * dt;

		// resetear la fuerza resultante
		//object->Force = glm::vec2(0.0f, 0.0f);

	}

}

// Redondea hasta 3 decimales para no tener en cuenta valores demasiado pequeños
void PhysicsWorld::Round(Vector2f* v) {
	v->x = round(v->x * 1000.0f) / 1000.f;
	v->y = round(v->y * 1000.0f) / 1000.f;
}