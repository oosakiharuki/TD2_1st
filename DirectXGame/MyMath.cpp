#include "MyMath.h"

Vector3 Add(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}

Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
}

Vector3 MultiplyV(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = v1.x * v2.x;
	result.y = v1.y * v2.y;
	result.z = v1.z * v2.z;
	return result;
}

Vector3 MultiplyFV(const float f, const Vector3& v) {
	Vector3 result;
	result.x = f * v.x;
	result.y = f * v.y;
	result.z = f * v.z;
	return result;
}

Matrix4x4 Multiply(Matrix4x4 m1, Matrix4x4 m2) {
	Matrix4x4 result{};
	result.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] + m1.m[0][3] * m2.m[3][0];
	result.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] + m1.m[0][3] * m2.m[3][1];
	result.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] + m1.m[0][3] * m2.m[3][2];
	result.m[0][3] = m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] + m1.m[0][3] * m2.m[3][3];

	result.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] + m1.m[1][3] * m2.m[3][0];
	result.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] + m1.m[1][3] * m2.m[3][1];
	result.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] + m1.m[1][3] * m2.m[3][2];
	result.m[1][3] = m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] + m1.m[1][3] * m2.m[3][3];

	result.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] + m1.m[2][3] * m2.m[3][0];
	result.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] + m1.m[2][3] * m2.m[3][1];
	result.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] + m1.m[2][3] * m2.m[3][2];
	result.m[2][3] = m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] + m1.m[2][3] * m2.m[3][3];

	result.m[3][0] = m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] + m1.m[3][3] * m2.m[3][0];
	result.m[3][1] = m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] + m1.m[3][3] * m2.m[3][1];
	result.m[3][2] = m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] + m1.m[3][3] * m2.m[3][2];
	result.m[3][3] = m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] + m1.m[3][3] * m2.m[3][3];
	return result;
}
Matrix4x4 MakeAffineMatrix(Vector3 scale_, Vector3 rotate_, Vector3 translate_) {

	Matrix4x4 resultX{};

	resultX.m[0][0] = 1.0f;
	resultX.m[0][1] = 0.0f;
	resultX.m[0][2] = 0.0f;
	resultX.m[0][3] = 0.0f;
	resultX.m[1][0] = 0.0f;
	resultX.m[1][1] = std::cos(rotate_.x);
	resultX.m[1][2] = std::sin(rotate_.x);
	resultX.m[1][3] = 0.0f;
	resultX.m[2][0] = 0.0f;
	resultX.m[2][1] = -(std::sin(rotate_.x));
	resultX.m[2][2] = std::cos(rotate_.x);
	resultX.m[2][3] = 0.0f;
	resultX.m[3][0] = 0.0f;
	resultX.m[3][1] = 0.0f;
	resultX.m[3][2] = 0.0f;
	resultX.m[3][3] = 1.0f;

	Matrix4x4 resultY{};

	resultY.m[0][0] = std::cos(rotate_.y);
	resultY.m[0][1] = 0.0f;
	resultY.m[0][2] = -(std::sin(rotate_.y));
	resultY.m[0][3] = 0.0f;
	resultY.m[1][0] = 0.0f;
	resultY.m[1][1] = 1.0f;
	resultY.m[1][2] = 0.0f;
	resultY.m[1][3] = 0.0f;
	resultY.m[2][0] = std::sin(rotate_.y);
	resultY.m[2][1] = 0.0f;
	resultY.m[2][2] = std::cos(rotate_.y);
	resultY.m[2][3] = 0.0f;
	resultY.m[3][0] = 0.0f;
	resultY.m[3][1] = 0.0f;
	resultY.m[3][2] = 0.0f;
	resultY.m[3][3] = 1.0f;

	Matrix4x4 resultZ{};

	resultZ.m[0][0] = std::cos(rotate_.z);
	resultZ.m[0][1] = std::sin(rotate_.z);
	resultZ.m[0][2] = 0.0f;
	resultZ.m[0][3] = 0.0f;
	resultZ.m[1][0] = -(std::sin(rotate_.z));
	resultZ.m[1][1] = std::cos(rotate_.z);
	resultZ.m[1][2] = 0.0f;
	resultZ.m[1][3] = 0.0f;
	resultZ.m[2][0] = 0.0f;
	resultZ.m[2][1] = 0.0f;
	resultZ.m[2][2] = 1.0f;
	resultZ.m[2][3] = 0.0f;
	resultZ.m[3][0] = 0.0f;
	resultZ.m[3][1] = 0.0f;
	resultZ.m[3][2] = 0.0f;
	resultZ.m[3][3] = 1.0f;

	Matrix4x4 rotateXYZ_ = Multiply(resultX, Multiply(resultY, resultZ));

	Matrix4x4 result{};
	result.m[0][0] = scale_.x * rotateXYZ_.m[0][0];
	result.m[0][1] = scale_.x * rotateXYZ_.m[0][1];
	result.m[0][2] = scale_.x * rotateXYZ_.m[0][2];
	result.m[0][3] = 0.0f;
	result.m[1][0] = scale_.y * rotateXYZ_.m[1][0];
	result.m[1][1] = scale_.y * rotateXYZ_.m[1][1];
	result.m[1][2] = scale_.y * rotateXYZ_.m[1][2];
	result.m[1][3] = 0.0f;
	result.m[2][0] = scale_.z * rotateXYZ_.m[2][0];
	result.m[2][1] = scale_.z * rotateXYZ_.m[2][1];
	result.m[2][2] = scale_.z * rotateXYZ_.m[2][2];
	result.m[2][3] = 0.0f;
	result.m[3][0] = translate_.x;
	result.m[3][1] = translate_.y;
	result.m[3][2] = translate_.z;
	result.m[3][3] = 1.0f;
	return result;
}

Vector3 Projection(Vector3 start, Vector3 end) {

	Vector3 a = start * end;
	Vector3 b = end * end;

	float t = (a.x + a.y + a.z) / (b.x + b.y + b.z);
	Vector3 result;
	result = t * end;

	return result;
}

Vector3 ClosestPoint(const Vector3& point, const Segment& v2) {

	Vector3 a = {point.x - v2.origin.x, point.y - v2.origin.y, point.z - v2.origin.z};

	float t = ((a.x * v2.diff.x) + (a.y * v2.diff.y) + (a.z * v2.diff.z)) / ((v2.diff.x * v2.diff.x) + (v2.diff.y * v2.diff.y) + (v2.diff.z * v2.diff.z));

	Vector3 result{};

	result.x = v2.origin.x + (t * v2.diff.x);
	result.y = v2.origin.y + (t * v2.diff.y);
	result.z = v2.origin.z + (t * v2.diff.z);

	return result;
}


Vector3 Normalize(const Vector3& v) {
	Vector3 result;
	result.x = v.x / (float)sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	result.y = v.y / (float)sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	result.z = v.z / (float)sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	return result;
}

Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m) {
	Vector3 result{v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0], v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1], v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2]};
	return result;
}

Vector3 operator+(Vector3 v1, Vector3 v2) { return Add(v1, v2); };
Vector3 operator-(Vector3 v1, Vector3 v2) { return Subtract(v1, v2); };
Vector3 operator*(Vector3 v1, Vector3 v2) { return MultiplyV(v1, v2); };
Vector3 operator*(float f, Vector3 v) { return MultiplyFV(f, v); };
//Vector3 operator*(Vector3 v, float f) { return v * f; };

Vector3& operator+=(Vector3 v1, Vector3 v2) {
	v1.x += v2.x;
	v1.x += v2.x;
	v1.x += v2.x;
	return v1;
}

Vector3& operator+=(Vector3 v, float f) { 
	v.x += f;
	v.y += f;
	v.z += f;
	return v;
}