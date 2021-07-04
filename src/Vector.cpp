#include "Vector.hpp"

Vector operator+(const Vector& u, const Vector& v)
{
	return { u.x + v.x, u.y + v.y, u.z + v.z };
}

Vector operator-(const Vector& u, const Vector& v)
{
	return { u.x - v.x, u.y - v.y, u.z - v.z };
}

Vector operator*(const Vector& v, float n)
{
	return { n * v.x, n * v.y, n * v.z };
}

Vector operator/(const Vector& v, float n)
{
	return {  v.x / n, v.y / n,  v.z / n };
}

std::ostream& operator<<(std::ostream& out, const Vector& v)
{
	out << "( " << v.x << ", " << v.y << ", " << v.z << " )";
	return out;
}

Vector unit(const Vector& v)
{
	float m = mag(v);
	return { v.x / m, v.y / m, v.z / m };
}

float dot(const Vector& u, const Vector& v)
{
	return u.x * v.x + u.y * v.y + u.z * v.z;
}

Vector cross(const Vector& u, const Vector& v)
{
	return { u.y * v.z - u.z * v.y, v.x * u.z - u.x * v.z, u.x * v.y - u.y * v.x };

}
float crossMag(const Vector& u, const Vector& v)
{

	return mag(cross(u, v));
}

float mag(const Vector& v)
{
	return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}
