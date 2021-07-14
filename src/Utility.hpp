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

struct Quad {
	Vector vertex[4];
	sf::Color color = sf::Color::White;

	Vector& operator[](int i) {
		return vertex[i];
	}
	Vector operator[](int i) const {
		return vertex[i];
	}

	bool contains(const sf::Vector2f& pos);
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

Matrix4x4 operator+(const Matrix4x4& a, const Matrix4x4& b);

Vector operator*(const Matrix4x4& mat, const Vector& u);
Triangle operator*(const Matrix4x4& mat, const Triangle& t);
Quad operator*(const Matrix4x4& mat, const Quad& r);
Matrix4x4 operator*(const Matrix4x4& a, const Matrix4x4& b);
