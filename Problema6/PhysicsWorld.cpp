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
	max_velocity = 600.0f;
}

void PhysicsWorld::Update() {

	for (int i = 0; i < Objects.size(); i++) {
		PhysicsObject* object = Objects[i];

		if (object->shouldRemove) {
			Objects.erase(Objects.begin() + i);
			continue;
		}

		//Round(&object->Velocity);
		//Round(&object->Position);
		//Round(&object->Force);

		object->Velocity.x = object->Velocity.x > max_velocity ? max_velocity : object->Velocity.x;
		object->Velocity.y = object->Velocity.y > max_velocity ? max_velocity : object->Velocity.y;


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
				this->circleCollider1.center.x = object->Position.x + object->collisionInfo.radius;
				this->circleCollider1.center.y = object->Position.y + object->collisionInfo.radius;
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
				this->circleCollider2.center.x = other->Position.x + other->collisionInfo.radius;
				this->circleCollider2.center.y = other->Position.y + other->collisionInfo.radius;
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

					

					

					if (other->collisionObjectType == PhysicsObject::CollisionObjectType::CIRCLE &&
						object->collisionObjectType == PhysicsObject::CollisionObjectType::CIRCLE) {
						// Empujar los circulos una pequeña distancia (suma de radios - distancia de centros)
						// para que no coincidan en la misma posición entre ellos
						Circle* c1 = (Circle*)objCollider1;
						Circle* c2 = (Circle*)objCollider2;
						float dx = c1->center.x - c2->center.x;
						float dy = c1->center.y - c2->center.y;


						float rsum = c1->radius + c2->radius;
						float distance = rsum - sqrt(dx * dx + dy * dy);


						Vector2f normal = tangent.normal();
						float angle = atan(normal.y / normal.x);

						float mx = cos(angle) * distance;
						float my = sin(angle) * distance;

						

						if (c2->center.x > c1->center.x) {
							// c1 esta a la derecha de c2
							object->Position.x += mx;
							other->Position.x += mx;
							//object->Velocity.x = other->Velocity.x;
							//object->Position.x += mx;
							//object->Velocity.x = other->Velocity.x;
							//object->Force.x = other->Force.x * 0.5f;
						}
						else if (c2->center.x < c1->center.x) {
							// c1 esta a la izquierda de c2
							object->Position.x -= mx;
							other->Position.x -= mx;
							//object->Velocity.x = other->Velocity.x;
							//object->Position.x -= mx;
							//object->Velocity.x = other->Velocity.x;
							//object->Force.x = other->Force.x * 0.5f;
						}

						if(c2->center.y > c1->center.y) {
							// c1 esta abajo de c2
							object->Position.y -= my;
							other->Position.y -= my;
							//object->Velocity.y = other->Velocity.y;
						} else if (c2->center.y < c1->center.y) {
							// c1 esta arriba de c2
							object->Position.y += my;
							other->Position.y += my;
							//object->Velocity.y = other->Velocity.y;
						}

						object->Velocity = other->Velocity;

					}

					if (object->collisionObjectType == PhysicsObject::CollisionObjectType::CIRCLE &&
						other->collisionObjectType == PhysicsObject::CollisionObjectType::SEGMENT) {

						Circle* c1 = (Circle*)objCollider1;
						Segment* s1 = (Segment*)objCollider2;
						Vector2f vs1 = s1->toVector();

						if (vs1.x == 0.0f && vs1.y != 0.0f) {
							//Linea vertical
							float dx = fabs(c1->center.x - s1->p1.x);
							if (c1->center.x > s1->p1.x) {
								object->Position.x += dx;
							}

							if (c1->center.x < s1->p1.x) {
								object->Position.x -= dx;
							}
						}

						if (vs1.x != 0.0f && vs1.y == 0.0f) {

							if (c1->center.y < s1->p1.y && s1->p1.y != 50.0f) {
								object->Position.y = s1->p1.y - (2.0f * c1->radius);
							}
						}

					}
					//object->Force = reflected;
					/*reflected.x = reflected.x < 0 ? -1.0f : reflected.x > 0 ? 1.0f : 0.0f;
					reflected.y = reflected.y < 0 ? -1.0f : reflected.y > 0 ? 1.0f : 0.0f;
					
					

					object->Velocity.x *= reflected.x;
					object->Velocity.y *= reflected.y;*/

					Vector2f reflected = Vector2f::Reflect(object->Velocity, tangent);

					object->Velocity = reflected;
					object->Velocity.x *= other->ElasticK;
					object->Velocity.y *= other->ElasticK;


					Vector2f F_reflected = reflected.normalize();
					object->Force.x = F_reflected.x * other->ElasticK;
					//object->Force.y = F_reflected.x * other->ElasticK;
					


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

					if (dx < 1.0f) {
						object->Force.x = 0.0f;
					}

					if (dy < 1.0f && dx < 0.1f) {
						if (object->collisionObjectType == PhysicsObject::CollisionObjectType::CIRCLE &&
							other->collisionObjectType == PhysicsObject::CollisionObjectType::SEGMENT &&
							F_Normal.x == 0.0f) 
						{
							object->isActive = false;
						}
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
