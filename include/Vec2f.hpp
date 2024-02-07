#pragma once
#include "Utils.hpp"






class Vec2f
{
public:
	Vec2f():x(0), y(0) {};
	Vec2f(float x, float y):x(x), y(y) {};

	sf::Vector2f& toSf() {
		return *reinterpret_cast<sf::Vector2f*>(this);
	}

	Vec2f(const sf::Vector2f& other) {
		this->x = other.x;
		this->y = other.y;
	}

	Vec2f(const sf::Vector2i& other) {
		this->x = (float)other.x;
		this->y = (float)other.y;
	}


	inline float length() {
		return sqrtf(this->x * this->x + this->y * this->y);
	};

	inline float lengthSquared() {
		return this->x * this->x + this->y * this->y;
	}

	inline Vec2f perpendicularL() {
		return Vec2f(-y, x);
	}	
	inline Vec2f perpendicularR() {
		return Vec2f(y, -x);
	}
	inline Vec2f normalize() {
		float len = length();
		return Vec2f(x/len, y/len);
	}

	static inline void drawVector(sf::RenderWindow* window, Vec2f vector, Vec2f origin, sf::Color color = sf::Color(255, 255, 255,255)) {
		sf::VertexArray v;	
		v.resize(2);
		v.setPrimitiveType(sf::LineStrip);

		v[0].color = color;
		v[1].color = color;

		v[0].position = origin.toSf();
		vector.x += origin.x;
		vector.y += origin.y;
		v[1].position = vector.toSf();
		window->draw(v);
	}
	

	float x;
	float y;
private:

};

static float Cross(Vec2f vec1, Vec2f vec2) {

	return vec1.x * vec2.y - vec1.y * vec2.x;
}



static Vec2f rotateVertex(const Vec2f& vertex, float angle) {
	float rad = (float)(angle * 3.14159265 / 180);  // Convert angle to radians
	float sinVal = sin(rad);
	float cosVal = cos(rad);

	Vec2f rotatedVertex;
	rotatedVertex.x = vertex.x * cosVal - vertex.y * sinVal;
	rotatedVertex.y = vertex.x * sinVal + vertex.y * cosVal;

	/*     rotatedVertex.x = vertex.x * cosVal + vertex.y * sinVal;
		 rotatedVertex.y = vertex.x * cosVal - vertex.y * sinVal;*/

	return rotatedVertex;
}

std::ostream& operator<<(std::ostream& os, Vec2f const& v);
Vec2f operator -(const Vec2f& right);

Vec2f& operator +=(Vec2f& left, const Vec2f& right);

Vec2f& operator -=(Vec2f& left, const Vec2f& right);


Vec2f operator +(const Vec2f& left, const Vec2f& right);

Vec2f operator -(const Vec2f& left, const Vec2f& right);

Vec2f operator *(const Vec2f& left, float right);

Vec2f operator * (float left, const Vec2f& right);

//dot product
float operator * (const Vec2f& left, const Vec2f& right);

Vec2f& operator *=(Vec2f& left, float right);

Vec2f operator / (const Vec2f& left, float right);

Vec2f& operator /= (Vec2f& left, float right);

bool operator == (const Vec2f& left, const Vec2f right);

bool operator != (const Vec2f& left, const Vec2f right);

static Vec2f Cross(float s, Vec2f vec) {
	return vec.perpendicularL() * s;
}
