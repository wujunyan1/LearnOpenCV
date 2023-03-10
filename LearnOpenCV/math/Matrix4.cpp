#include "Matrix4.h"
#include "Quaternion.h"
#include "Matrix3.h"

using namespace Math;

const Matrix4 Matrix4::IDENTITY(
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1);

Math::Matrix4::Matrix4(Matrix3 mat3)
{
	m00 = mat3.m00; m01 = mat3.m01; m02 = mat3.m02; m03 = 0;
	m10 = mat3.m10; m11 = mat3.m11; m12 = mat3.m12; m13 = 0;
	m20 = mat3.m20; m21 = mat3.m21; m22 = mat3.m22; m23 = 0;
	m30 = 0; m31 = 0; m32 = 0; m33 = 1;
}

float Matrix4::determinant() const
{
	if (*this == Matrix4::IDENTITY) {
		return 1;
	}

	const auto m00 = m[0], m01 = m[1], m02 = m[2], m03 = m[3];
	const auto m10 = m[4], m11 = m[5], m12 = m[6], m13 = m[7];
	const auto m20 = m[8], m21 = m[9], m22 = m[10], m23 = m[11];
	const auto m30 = m[12], m31 = m[13], m32 = m[14], m33 = m[15];
	// https://en.wikipedia.org/wiki/Laplace_expansion
	// to compute the deterrminant of a 4x4 Matrix we compute the cofactors of any
	// row or column, then we multiply each Cofactor by its corresponding matrix
	// value and sum them all to get the determinant Cofactor(i, j) = sign(i,j) *
	// det(Minor(i, j)) where
	//  - sign(i,j) = (i+j) % 2 === 0 ? 1 : -1
	//  - Minor(i, j) is the 3x3 matrix we get by removing row i and column j from
	//  current Matrix
	//
	// Here we do that for the 1st row.

	const auto det_22_33 = m22 * m33 - m32 * m23;
	const auto det_21_33 = m21 * m33 - m31 * m23;
	const auto det_21_32 = m21 * m32 - m31 * m22;
	const auto det_20_33 = m20 * m33 - m30 * m23;
	const auto det_20_32 = m20 * m32 - m22 * m30;
	const auto det_20_31 = m20 * m31 - m30 * m21;
	const auto cofact_00 = +(m11 * det_22_33 - m12 * det_21_33 + m13 * det_21_32);
	const auto cofact_01 = -(m10 * det_22_33 - m12 * det_20_33 + m13 * det_20_32);
	const auto cofact_02 = +(m10 * det_21_33 - m11 * det_20_33 + m13 * det_20_31);
	const auto cofact_03 = -(m10 * det_21_32 - m11 * det_20_32 + m12 * det_20_31);
	return m00 * cofact_00 + m01 * cofact_01 + m02 * cofact_02 + m03 * cofact_03;
}

bool Matrix4::decompose(Vector3* scale, Quaternion* rotation, Vector3* translation) const
{
	if (translation)
	{
		// 提取平移信息
		translation->x = m30;
		translation->y = m31;
		translation->z = m32;
	}

	if (scale == nullptr && rotation == nullptr)
		return true;

	// 提取缩放信息
	// 就是矩阵中每个轴(行/列)的长度
	Vector3 xaxis(m00, m01, m02);
	float scaleX = xaxis.len();

	Vector3 yaxis(m10, m11, m12);
	float scaleY = yaxis.len();

	Vector3 zaxis(m20, m21, m22);
	float scaleZ = zaxis.len();

	// 检测是否存在负数缩放 (如果行列式小于0，则存在负数缩放).
	// 在这种情况下，简单的将一个轴向的缩放取反
	float det = determinant();

	if (det < Math::EPSILON)
		scaleZ = -scaleZ;

	if (scale)
	{
		scale->x = scaleX;
		scale->y = scaleY;
		scale->z = scaleZ;
	}

	if (rotation == nullptr)
		return true;

	// 缩放趋近于0，无法分解出旋转信息
	if (scaleX < Math::EPSILON || scaleY < Math::EPSILON || fabs(scaleZ) < Math::EPSILON)
		return false;

	float rn;

	// 对矩阵的轴进行缩放
	rn = 1.0f / scaleX;
	xaxis.x *= rn;
	xaxis.y *= rn;
	xaxis.z *= rn;

	rn = 1.0f / scaleY;
	yaxis.x *= rn;
	yaxis.y *= rn;
	yaxis.z *= rn;

	rn = 1.0f / scaleZ;
	zaxis.x *= rn;
	zaxis.y *= rn;
	zaxis.z *= rn;

	// 现在，从产生的矩阵（轴）中计算出旋转
	float trace = xaxis.x + yaxis.y + zaxis.z + 1.0f;

	if (trace > 1.0f)
	{
		float s = 0.5f / Math::Sqrt(trace);
		rotation->w = 0.25f / s;
		rotation->x = (yaxis.z - zaxis.y) * s;
		rotation->y = (zaxis.x - xaxis.z) * s;
		rotation->z = (xaxis.y - yaxis.x) * s;
	}
	else
	{
		// 注意：由于X轴、Y轴和Z轴都是归一化的
		// 下面的代码中不会遇到除零的情况
		if (xaxis.x > yaxis.y && xaxis.x > zaxis.z)
		{
			float s = 0.5f / Math::Sqrt(1.0f + xaxis.x - yaxis.y - zaxis.z);
			rotation->w = (yaxis.z - zaxis.y) * s;
			rotation->x = 0.25f / s;
			rotation->y = (yaxis.x + xaxis.y) * s;
			rotation->z = (zaxis.x + xaxis.z) * s;
		}
		else if (yaxis.y > zaxis.z)
		{
			float s = 0.5f / Math::Sqrt(1.0f + yaxis.y - xaxis.x - zaxis.z);
			rotation->w = (zaxis.x - xaxis.z) * s;
			rotation->x = (yaxis.x + xaxis.y) * s;
			rotation->y = 0.25f / s;
			rotation->z = (zaxis.y + yaxis.z) * s;
		}
		else
		{
			float s = 0.5f / Math::Sqrt(1.0f + zaxis.z - xaxis.x - yaxis.y);
			rotation->w = (xaxis.y - yaxis.x) * s;
			rotation->x = (zaxis.x + xaxis.z) * s;
			rotation->y = (zaxis.y + yaxis.z) * s;
			rotation->z = 0.25f / s;
		}
	}

	return true;
}