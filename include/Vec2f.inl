#include "Vec2f.hpp"
inline std::ostream& operator<<(std::ostream& os, Vec2f const& v)
{
		os << "(";
		os << v.x;
		os << ",";
		os << v.y;
		os << ")";
		return os;
}

inline Vec2f operator-(const Vec2f& right)
{
	return Vec2f(-right.x, -right.y);
}


inline Vec2f& operator+=(Vec2f& left, const Vec2f& right)
{
	left.x += right.x;
	left.y += right.y;

	return left;

}

inline Vec2f& operator-=(Vec2f& left, const Vec2f& right)
{
	left.x -= right.x;
	left.y -= right.y;

	return left;
}

inline Vec2f operator+(const Vec2f& left, const Vec2f& right)
{
	return Vec2f(left.x + right.x, left.y + right.y);
}

inline Vec2f operator-(const Vec2f& left, const Vec2f& right)
{
	return Vec2f(left.x - right.x, left.y - right.y);
}

inline Vec2f operator*(const Vec2f& left, float right)
{
	return Vec2f(left.x * right, left.y * right);
}

inline Vec2f operator*(float left, const Vec2f& right)
{
	return Vec2f(right.x * left, right.y * left);
}

inline float operator*(const Vec2f& left, const Vec2f& right)
{
	return left.x * right.x + left.y * right.y;//bruh typo made me rethink my life choices
}

inline Vec2f& operator*=(Vec2f& left, float right)
{
	left.x *= right;
	left.y *= right;

	return left;

}

inline Vec2f operator/(const Vec2f& left, float right)
{
	return Vec2f(left.x / right, left.y / right);
}

inline Vec2f& operator/=(Vec2f& left, float right)
{
	left.x /= right;
	left.y /= right;

	return left;

}

inline bool operator==(const Vec2f& left, const Vec2f right)
{
	return (left.x == right.x) && (left.y == right.y);
}

inline bool operator!=(const Vec2f& left, const Vec2f right)
{
	return (left.x != right.x) || (left.y != right.y);

}

