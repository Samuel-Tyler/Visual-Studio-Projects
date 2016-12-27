#include <iostream>
#include <iomanip>

class matrix3x3 
{
public:
	matrix3x3(float a1 = 0, float a2 = 0, float a3 = 0, float b1 = 0, float b2 = 0, float b3 = 0, float c1 = 0, float c2 = 0, float c3 = 0) : m_a1(a1) , m_a2(a2), m_a3(a3), m_b1(b1), m_b2(b2), m_b3(b3), m_c1(c1), m_c2(c2), m_c3(c3) {}
	matrix3x3(const matrix3x3 & rhs);
	void print();
	matrix3x3 & operator+=(const matrix3x3 & rhs);
	matrix3x3 & operator-=(const matrix3x3 & rhs);
	matrix3x3 & operator/=(const float rhs);
	matrix3x3 & operator*=(const float rhs);
	matrix3x3 & operator=(const matrix3x3 & rhs);
	float m_a1;
	float m_a2;
	float m_a3;
	float m_b1;
	float m_b2;
	float m_b3;
	float m_c1;
	float m_c2;
	float m_c3;
};

matrix3x3::matrix3x3(const matrix3x3 & rhs)
	:
m_a1(rhs.m_a1), m_a2(rhs.m_a2), m_a3(rhs.m_a3), m_b1(rhs.m_b1), m_b2(rhs.m_b2), m_b3(rhs.m_b3), m_c1(rhs.m_c1), m_c2(rhs.m_c2), m_c3(rhs.m_c3)
{
}


matrix3x3 & matrix3x3::operator=(const matrix3x3& rhs)
{
	matrix3x3 &lhs = *this;
	lhs.m_a1 = rhs.m_a1;
	lhs.m_a2 = rhs.m_a2;
	lhs.m_a3 = rhs.m_a3;
	lhs.m_b1 = rhs.m_b1;
	lhs.m_b2 = rhs.m_b2;
	lhs.m_b3 = rhs.m_b3;
	lhs.m_c1 = rhs.m_c1;
	lhs.m_c2 = rhs.m_c2;
	lhs.m_c3 = rhs.m_c3;

	return *this;
}

void matrix3x3::print()
{
	std::cout << std::fixed << std::setprecision(2) << std::showpos;
	std::cout << +m_a1 << "  " << m_a2 << "  " << m_a3 << std::endl;
	std::cout << m_b1 << "  " << m_b2 << "  " << m_b3 << std::endl;
	std::cout << m_c1 << "  " << m_c2 << "  " << m_c3 << std::endl;
}

matrix3x3 operator*(const matrix3x3& lhs, const matrix3x3& rhs)
{
	matrix3x3 result;

	result.m_a1 = lhs.m_a1 * rhs.m_a1 + lhs.m_a2 * rhs.m_b1 + lhs.m_a3 * rhs.m_c1;
	result.m_a2 = lhs.m_a1 * rhs.m_a2 + lhs.m_a2 * rhs.m_b2 + lhs.m_a3 * rhs.m_c2;
	result.m_a3 = lhs.m_a1 * rhs.m_a3 + lhs.m_a2 * rhs.m_b3 + lhs.m_a3 * rhs.m_c3;
	result.m_b1 = lhs.m_b1 * rhs.m_a1 + lhs.m_b2 * rhs.m_b1 + lhs.m_b3 * rhs.m_c1;
	result.m_b2 = lhs.m_b1 * rhs.m_a2 + lhs.m_b2 * rhs.m_b2 + lhs.m_b3 * rhs.m_c2;
	result.m_b3 = lhs.m_b1 * rhs.m_a3 + lhs.m_b2 * rhs.m_b3 + lhs.m_b3 * rhs.m_c3;
	result.m_c1 = lhs.m_c1 * rhs.m_a1 + lhs.m_c2 * rhs.m_b1 + lhs.m_c3 * rhs.m_c1;
	result.m_c2 = lhs.m_c1 * rhs.m_a2 + lhs.m_c2 * rhs.m_b2 + lhs.m_c3 * rhs.m_c2;
	result.m_c3 = lhs.m_c1 * rhs.m_a3 + lhs.m_c2 * rhs.m_b3 + lhs.m_c3 * rhs.m_c3;

	return result;
}

matrix3x3 operator*(float scalar, const matrix3x3& rhs)
{
	matrix3x3 result;

	result.m_a1 = rhs.m_a1 * scalar;
	result.m_a2 = rhs.m_a2 * scalar;
	result.m_a3 = rhs.m_a3 * scalar;
	result.m_b1 = rhs.m_b1 * scalar;
	result.m_b2 = rhs.m_b2 * scalar;
	result.m_b3 = rhs.m_b3 * scalar;
	result.m_c1 = rhs.m_c1 * scalar;
	result.m_c2 = rhs.m_c2 * scalar;
	result.m_c3 = rhs.m_c3 * scalar;

	return result;
}

matrix3x3 operator/(const matrix3x3& rhs, float divisior)
{
	matrix3x3 result;

	result.m_a1 = rhs.m_a1 / divisior;
	result.m_a2 = rhs.m_a2 / divisior;
	result.m_a3 = rhs.m_a3 / divisior;
	result.m_b1 = rhs.m_b1 / divisior;
	result.m_b2 = rhs.m_b2 / divisior;
	result.m_b3 = rhs.m_b3 / divisior;
	result.m_c1 = rhs.m_c1 / divisior;
	result.m_c2 = rhs.m_c2 / divisior;
	result.m_c3 = rhs.m_c3 / divisior;

	return result;
}

matrix3x3 & matrix3x3::operator+=(const matrix3x3& rhs)
{
	matrix3x3 &lhs = *this;
	matrix3x3 result(lhs.m_a1 + rhs.m_a1, lhs.m_a2 + rhs.m_a2, lhs.m_a3 + rhs.m_a3,
				 	 lhs.m_b1 + rhs.m_b1, lhs.m_b2 + rhs.m_b2, lhs.m_b3 + rhs.m_b3,
				 	 lhs.m_c1 + rhs.m_c1, lhs.m_c2 + rhs.m_c2, lhs.m_c3 + rhs.m_c3
		);
	*this = result;
	return *this;
}

matrix3x3 & matrix3x3::operator-=(const matrix3x3& rhs)
{
	matrix3x3 &lhs = *this;
	matrix3x3 result(lhs.m_a1 - rhs.m_a1, lhs.m_a2 - rhs.m_a2, lhs.m_a3 - rhs.m_a3,
		lhs.m_b1 - rhs.m_b1, lhs.m_b2 - rhs.m_b2, lhs.m_b3 - rhs.m_b3,
		lhs.m_c1 - rhs.m_c1, lhs.m_c2 - rhs.m_c2, lhs.m_c3 - rhs.m_c3
	);
	*this = result;
	return *this;
}


matrix3x3 & matrix3x3::operator/=(const float rhs)
{
	*this = *this / rhs;
	return *this;
}

matrix3x3 & matrix3x3::operator*=(const float rhs)
{
	*this = *this * rhs;
	return *this;
}

matrix3x3 operator+(const matrix3x3& lhs, const matrix3x3& rhs)
{
	auto result(lhs);
	result += rhs;
	return result;
}

matrix3x3 operator-(const matrix3x3& lhs, const matrix3x3& rhs)
{
	auto result(lhs);
	result -= rhs;
	return result;
}

matrix3x3 transpose(const matrix3x3& rhs)
{
	matrix3x3 lhs;
	lhs.m_a1 = rhs.m_a1;
	lhs.m_a2 = rhs.m_b1;
	lhs.m_a3 = rhs.m_c1;
	lhs.m_b1 = rhs.m_a2;
	lhs.m_b2 = rhs.m_b2;
	lhs.m_b3 = rhs.m_c2;
	lhs.m_c1 = rhs.m_a3;
	lhs.m_c2 = rhs.m_b3;
	lhs.m_c3 = rhs.m_c3;
	return lhs;
}


matrix3x3 cofactors(const matrix3x3& rhs)
{
	matrix3x3 lhs;
	lhs.m_a1 = rhs.m_b2 * rhs.m_c3 - rhs.m_b3 * rhs.m_c2;
	lhs.m_a2 = rhs.m_b3 * rhs.m_c1 - rhs.m_b1 * rhs.m_c3;
	lhs.m_a3 = rhs.m_b1 * rhs.m_c2 - rhs.m_b2 * rhs.m_c1;
	lhs.m_b1 = rhs.m_a3 * rhs.m_c2 - rhs.m_a2 * rhs.m_c3;
	lhs.m_b2 = rhs.m_a1 * rhs.m_c3 - rhs.m_a3 * rhs.m_c1;
	lhs.m_b3 = rhs.m_a2 * rhs.m_c1 - rhs.m_a1 * rhs.m_c2;
	lhs.m_c1 = rhs.m_a2 * rhs.m_b3 - rhs.m_a3 * rhs.m_b2;
	lhs.m_c2 = rhs.m_a3 * rhs.m_b1 - rhs.m_a1 * rhs.m_b3;
	lhs.m_c3 = rhs.m_a1 * rhs.m_b2 - rhs.m_a2 * rhs.m_b1;
	return lhs;
}

float determinant(const matrix3x3& rhs)
{
	auto T = transpose(rhs);
	float det_a1 = + (rhs.m_b2 * rhs.m_c3 - rhs.m_b3 * rhs.m_c2) * rhs.m_a1;
	float det_a2 = - (rhs.m_b1 * rhs.m_c3 - rhs.m_b3 * rhs.m_c1) * rhs.m_a2;
	float det_a3 = + (rhs.m_b1 * rhs.m_c2 - rhs.m_b2 * rhs.m_c1) * rhs.m_a3;

	return det_a1 + det_a2 + det_a3;
}


matrix3x3 inverse(const matrix3x3& rhs)
{
	auto T = transpose(cofactors(rhs));
	T /= determinant(rhs);
	return T;
}

float main()
{
	matrix3x3 a{ 7, 2, 1, 0, 3, -1, -3, 4, -2 };

	matrix3x3 b{ 3, 0, 2, 2, 0, -2, 0, 1, 1 };

	matrix3x3 identity{ 1, 0, 0, 0, 1, 0, 0, 0, 1 };

	std::cout << "b : " << std::endl;
	auto result = b;
	result.print();

	std::cout << "bi : " << std::endl;
	result = b * identity;
	result.print();

	std::cout << "ib : " << std::endl;
	result = identity * b;
	result.print();


	matrix3x3 x = b - ((inverse(a) * b) * a);

	std::cout << "AB : " << std::endl;
	result = a * b;
	result.print();

	std::cout << "AX + BA: " << std::endl;
	result = a * x + b * a;
	result.print();


	float i;
	std::cin >> i;
}
