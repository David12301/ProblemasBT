#pragma once

class Vector2f
{
public:
	float x, y;

	Vector2f() { x = y = 0.0f; }
	Vector2f(float x, float y) { this->x = x; this->y = y; }

	Vector2f& operator = (const Vector2f& v) {
		this->x = v.x;
		this->y = v.y;
		return *this;
	}

	Vector2f& operator += (const Vector2f& v) {
		this->x += v.x;
		this->y += v.y;
		return *this;
	}

	Vector2f& operator -= (const Vector2f& v) {
		this->x -= v.x;
		this->y -= v.y;
		return *this;
	}

	Vector2f operator + (const Vector2f& v) const {
		return Vector2f(this->x + v.x, this->y + v.y);
	}

	Vector2f operator - (const Vector2f& v) const {
		return Vector2f(this->x - v.x, this->y - v.y);
	}

	Vector2f operator * (const float s) const {
		return Vector2f(this->x * s, this->y * s);
	}

	Vector2f operator / (const float s) const {
		return Vector2f(this->x / s, this->y / s);
	}

	float operator * (const Vector2f& v) const {
		return this->x * v.x + this->y * v.y;
	}

	float magnitude() const {
		return sqrt(this->x * this->x + this->y * this->y);
	}

	Vector2f normalize() const {
		float m = magnitude();
		return Vector2f(this->x / m, this->y / m);

	}

	Vector2f normal() const {
		return Vector2f(-this->y, this->x);
	}

	static Vector2f Reflect(const Vector2f& v, const Vector2f& t)
	{
		/*
			Proyeccion de v en N
			r = v - 2(v.N)N/|N|^2
		*/
		Vector2f n = t.normal();
		float N = n.magnitude();
		Vector2f r = v - (n * ((v * n) * 2) / (N * N));
		return r;
	}
};