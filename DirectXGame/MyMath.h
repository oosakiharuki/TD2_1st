#include "Matrix4x4.h"
#include "Vector3.h"
#include <cmath>

class MyMath{

public:
	Matrix4x4 MakeAffineMatrix(Vector3 scale_, Vector3 rotate_, Vector3 translate_);
	Matrix4x4 Multiply(Matrix4x4 m1, Matrix4x4 m2);

	//Vector3& operator+=(const Vector3& v1, const Vector3& v2);
};