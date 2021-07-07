#pragma once

#include <SFML/Graphics.hpp>
#include "Vector.hpp"
#include <vector>
#include <string>

struct Triangle {
	Vector vertex[3];
	sf::Color color = sf::Color::White;

	Vector& operator[](int i) {
		return vertex[i];
	}
	Vector operator[](int i) const {
		return vertex[i];
	}
};

struct Rectangle {
	Vector vertex[4];
	sf::Color color = sf::Color::White;

	Vector& operator[](int i) {
		return vertex[i];
	}
	Vector operator[](int i) const {
		return vertex[i];
	}
};

struct Matrix4x4 {
	float m[4][4] = { 0 };

	static Matrix4x4 Identity();
	static Matrix4x4 RotationX(float theta);
	static Matrix4x4 RotationY(float theta);
	static Matrix4x4 RotationZ(float theta);
	static Matrix4x4 Scalar(float k);
	static Matrix4x4 Translation(float x, float y, float z);
	static Matrix4x4 Projection(float zNear, float zFar, float fov, float aspectRatio);
	static Matrix4x4 Orthographic(float left, float right, float bottom, float top, float near, float far);
};

Vector operator*(const Matrix4x4& mat, const Vector& u);
Triangle operator*(const Matrix4x4& mat, const Triangle& t);
Rectangle operator*(const Matrix4x4& mat, const Rectangle& r);
Matrix4x4 operator*(const Matrix4x4& a, const Matrix4x4& b);
