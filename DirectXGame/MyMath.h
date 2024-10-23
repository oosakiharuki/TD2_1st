#include "Matrix4x4.h"
#include "Vector3.h"
#include "Segment.h"
#include <cmath>

Vector3 Add(const Vector3& v1, const Vector3& v2);
Vector3 Subtract(const Vector3& v1, const Vector3& v2);
Vector3 MultiplyV(const Vector3& v1, const Vector3& v2);
Vector3 MultiplyFV(const float f, const Vector3& v);

Matrix4x4 MakeAffineMatrix(Vector3 scale_, Vector3 rotate_, Vector3 translate_);
Matrix4x4 Multiply(Matrix4x4 m1, Matrix4x4 m2);

Vector3 Projection(Vector3 start, Vector3 end);
Vector3 ClosestPoint(const Vector3& point, const Segment& v2);
Vector3 Normalize(const Vector3& v);
Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);

Matrix4x4 MakeRotateXMatrix(float radian);
Matrix4x4 MakeRotateYMatrix(float radian);
Matrix4x4 MakeRotateZMatrix(float radian);
Matrix4x4 MakeTranslateMatrix(const Vector3& teanslate);
Matrix4x4 MakeScaleMatrix(const Vector3& Scale);

Vector3 operator+(Vector3 v1, Vector3 v2);
Vector3 operator-(Vector3 v1, Vector3 v2);
Vector3 operator*(Vector3 v1, Vector3 v2);
Vector3 operator*(float f, Vector3 v);
//Vector3 operator*(Vector3 v, float f);

Vector3& operator+=(Vector3 v1, Vector3 v2);
Vector3& operator+=(Vector3 v, float f);

Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);