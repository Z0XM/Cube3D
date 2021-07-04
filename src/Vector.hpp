#pragma once
#include <ostream>
#include <SFML/System/Vector3.hpp>

struct Vector {
	float x = 0, y = 0, z = 0, w = 1;
};

Vector operator+(const Vector&, const Vector&);
Vector operator-(const Vector&, const Vector&);
Vector operator*(const Vector&, float);
Vector operator/(const Vector&, float);
std::ostream& operator<<(std::ostream&, const Vector&);

Vector unit(const Vector&);
float dot(const Vector&, const Vector&);
Vector cross(const Vector&, const Vector&);
float crossMag(const Vector&, const Vector&);
float mag(const Vector&);