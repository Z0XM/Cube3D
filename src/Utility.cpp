#include "Utility.hpp"
#include <fstream>
#include <sstream>

float toRadians(float degree) {
	return degree / 180.0f * 3.14159f;
}

Matrix4x4 Matrix4x4::Identity()
{
	Matrix4x4 mat;
	mat.m[0][0] = 1;
	mat.m[1][1] = 1;
	mat.m[2][2] = 1;
	mat.m[3][3] = 1;
	return mat;
}

Matrix4x4 Matrix4x4::RotationX(float theta)
{
	theta = toRadians(theta);
	Matrix4x4 mat;
	mat.m[0][0] = 1;
	mat.m[1][1] = cosf(theta);
	mat.m[1][2] = sinf(theta);
	mat.m[2][1] = -sinf(theta);
	mat.m[2][2] = cosf(theta);
	mat.m[3][3] = 1;
	return mat;
}

Matrix4x4 Matrix4x4::RotationY(float theta)
{
	theta = toRadians(theta);
	Matrix4x4 mat;
	mat.m[0][0] = cosf(theta);
	mat.m[0][2] = sinf(theta);
	mat.m[2][0] = -sinf(theta);
	mat.m[1][1] = 1.0f;
	mat.m[2][2] = cosf(theta);
	mat.m[3][3] = 1.0f;
	return mat;
}

Matrix4x4 Matrix4x4::RotationZ(float theta)
{
	theta = toRadians(theta);
	Matrix4x4 mat;
	mat.m[0][0] = cosf(theta);
	mat.m[0][1] = sinf(theta);
	mat.m[1][0] = -sinf(theta);
	mat.m[1][1] = cosf(theta);
	mat.m[2][2] = 1.0f;
	mat.m[3][3] = 1.0f;
	return mat;
}

Matrix4x4 Matrix4x4::Scalar(float k)
{
	Matrix4x4 mat;
	mat.m[0][0] = k;
	mat.m[1][1] = k;
	mat.m[2][2] = k;
	mat.m[3][3] = 1.f;
	return mat;
}

Matrix4x4 Matrix4x4::Translation(float x, float y, float z)
{
	Matrix4x4 mat;
	mat.m[0][0] = 1.f;
	mat.m[1][1] = 1.f;
	mat.m[2][2] = 1.f;
	mat.m[3][3] = 1.f;
	mat.m[3][0] = x;
	mat.m[3][1] = y;
	mat.m[3][2] = z;
	return mat;
}

Matrix4x4 Matrix4x4::Projection(float zNear, float zFar, float fov, float aspectRatio)
{
	Matrix4x4 mat;

	float fovRad = 1.0f / tanf(toRadians(fov * 0.5f));

	mat.m[0][0] = aspectRatio * fovRad;
	mat.m[1][1] = fovRad;
	mat.m[2][2] = -zFar / (zFar - zNear);
	mat.m[3][2] = (-zFar * zNear) / (zFar - zNear);
	mat.m[2][3] = -1.0f;
	mat.m[3][3] = 0.0f;
	return mat;
}

Matrix4x4 Matrix4x4::Orthographic(float left, float right, float bottom, float top, float near, float far)
{
	Matrix4x4 mat;

	float dx = right - left;
	float dy = -(top - bottom);
	float dz = far - near;

	mat.m[0][0] = 2.0f / dx;
	mat.m[1][1] = 2.0f / dy;
	mat.m[2][2] = 2.0f / dz;

	mat.m[3][0] = -(right + left) / dx;
	mat.m[3][1] = -(top + bottom) / dy;
	mat.m[3][2] = -(far + near) / dz;

	mat.m[3][3] = 1.f;

	return mat;
}

Vector operator*(const Matrix4x4& mat, const Vector& u)
{
	Vector v;
	v.x = u.x * mat.m[0][0] + u.y * mat.m[1][0] + u.z * mat.m[2][0] + u.w * mat.m[3][0];
	v.y = u.x * mat.m[0][1] + u.y * mat.m[1][1] + u.z * mat.m[2][1] + u.w * mat.m[3][1];
	v.z = u.x * mat.m[0][2] + u.y * mat.m[1][2] + u.z * mat.m[2][2] + u.w * mat.m[3][2];
	v.w = u.x * mat.m[0][3] + u.y * mat.m[1][3] + u.z * mat.m[2][3] + u.w * mat.m[3][3];
	return v;
}

Triangle operator*(const Matrix4x4& mat, const Triangle& t)
{
	Triangle tri;
	tri[0] = mat * t[0];
	tri[1] = mat * t[1];
	tri[2] = mat * t[2];
	return tri;
}

Rectangle operator*(const Matrix4x4& mat, const Rectangle& r)
{
	Rectangle rect;
	rect[0] = mat * r[0];
	rect[1] = mat * r[1];
	rect[2] = mat * r[2];
	rect[3] = mat * r[3];
	return rect;
}

Matrix4x4 operator*(const Matrix4x4& a, const Matrix4x4& b)
{
	Matrix4x4 mat;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			mat.m[i][j] = a.m[i][0] * b.m[0][j] + a.m[i][1] * b.m[1][j] + a.m[i][2] * b.m[2][j] + a.m[i][3] * b.m[3][j];

	return mat;
}