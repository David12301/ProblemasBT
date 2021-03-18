#include "PhysicsWorld.h"
#include "Shape.h"
#include "Circle.h"
#include "Segment.h"

PhysicsWorld::PhysicsWorld() {
	t = 0.0f;
	dt = 0.016f;
	G = 9.81f;
	objCollider1 = nullptr;
	objCollider2 = nullptr;
}

void PhysicsWorld::Update() {

	size_t size = Objects.size();
	for (int i = 0; i < size; i++) {
		PhysicsObject* object = Objects[i];



		Round(&object->Velocity);
		Round(&object->Position);
		Round(&object->Force);


		Vector2f temp_pos = object->Position;

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

		object->DPosition = temp_pos - object->Position;

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

			if (object->collisionObjectType == PhysicsObject::CollisionObjectType::CIRCLE) {
				this->circleCollider1.center.x = object->Position.x;
				this->circleCollider1.center.y = object->Position.y;
				this->circleCollider1.radius = object->collisionInfo.radius;
				objCollider1 = &this->circleCollider1;
			}
			else if (object->collisionObjectType == PhysicsObject::CollisionObjectType::SEGMENT) {
				this->segmentCollider1.p1.x = object->collisionInfo.x1;
				this->segmentCollider1.p1.y = object->collisionInfo.y1;
				this->segmentCollider1.p2.x = object->collisionInfo.x2;
				this->segmentCollider1.p2.y = object->collisionInfo.y2;
				objCollider1 = &this->segmentCollider1;
			}

			if (other->collisionObjectType == PhysicsObject::CollisionObjectType::CIRCLE) {
				this->circleCollider2.center.x = other->Position.x;
				this->circleCollider2.center.y = other->Position.y;
				this->circleCollider2.radius = other->collisionInfo.radius;
				objCollider2 = &this->circleCollider2;
			}
			else if (other->collisionObjectType == PhysicsObject::CollisionObjectType::SEGMENT) {
				this->segmentCollider2.p1.x = other->collisionInfo.x1;
				this->segmentCollider2.p1.y = other->collisionInfo.y1;
				this->segmentCollider2.p2.x = other->collisionInfo.x2;
				this->segmentCollider2.p2.y = other->collisionInfo.y2;
				objCollider2 = &this->segmentCollider2;
			}

			

			if (objCollider1 && objCollider2 && object->collisionResponse) {
				Vector2f tangent(0.0f, 0.0f);
				bool result = objCollider1->collidesWith(objCollider2, &tangent);
				if (result) {
					Vector2f reflected = Vector2f::Reflect(object->Velocity, tangent);
					//object->Force = reflected;
					/*reflected.x = reflected.x < 0 ? -1.0f : reflected.x > 0 ? 1.0f : 0.0f;
					reflected.y = reflected.y < 0 ? -1.0f : reflected.y > 0 ? 1.0f : 0.0f;
					
					

					object->Velocity.x *= reflected.x;
					object->Velocity.y *= reflected.y;*/
					object->Velocity = reflected;
					object->Velocity.x *= other->ElasticK;
					object->Velocity.y *= other->ElasticK;

					Vector2f F_Normal = tangent.normal();
					F_Normal.x *= -object->Force.x;
					F_Normal.y *= -object->Force.y;
					Vector2f F_Friction(-object->Force.x * other->Friction.x, -object->Force.y * other->Friction.y);
					object->Force += F_Friction;

					
					float dy = abs(F_Friction.y);
					float dx = abs(F_Friction.x);
					if (dy < 1.0f) {
 						object->Force.y = 0.0f;
						object->Force.y = -G * object->Mass;
					}




					/*
					if (dy <= 3.5f) {
						object->Velocity.y = 0.0f;
						object->Force.y = 0.0f;
						object->Force.y -= G * object->Mass;
					} 

					if (dx <= 1.5f) {
						object->Velocity.x = 0.0f;
						object->Force.x = 0.0f;
					}*/

				}

			}
		}
		
	}
}