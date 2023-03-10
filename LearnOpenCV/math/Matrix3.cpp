#include "Matrix3.h"
#include "Quaternion.h"
#include "Matrix4.h"

using namespace Math;

const Matrix3 Matrix3::IDENTITY(
	1, 0, 0,
	0, 1, 0,
	0, 0, 1);

Math::Matrix3::Matrix3(Matrix4 mat4)
{
	m00 = mat4.m00; m01 = mat4.m01; m02 = mat4.m02;
	m10 = mat4.m10; m11 = mat4.m11; m12 = mat4.m12;
	m20 = mat4.m20; m21 = mat4.m21; m22 = mat4.m22;
}

float Matrix3::determinant() const
{
	if (*this == Matrix3::IDENTITY) {
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