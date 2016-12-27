#include "Rectangl.h"

#include <algorithm>

using namespace std;

Rectangl::Rectangl(coord bottom_left, coord top_right)
	:
	m_bottom_left(bottom_left),
	m_top_right(top_right),
	m_is_intercept(false)
{
	if (float_greater_than(m_bottom_left.first, m_top_right.first))
	{
		swap(m_bottom_left.first, m_top_right.first);
	}

	if (float_greater_than(bottom_left.second, top_right.second))
	{
		swap(m_bottom_left.second, m_top_right.second);
	}
}

void Rectangl::draw() const
{
	auto depth = 0.0;
	if (m_is_intercept == true)
	{
		glBegin(GL_POLYGON);
		depth = 1.0;
		glColor3f(1.0, 0.0, 0.0);
	}
	else
	{
		glColor3f(1.0, 1.0, 1.0);
		depth = -1.0;
		glBegin(GL_LINE_LOOP);
	}
	glVertex3f(m_bottom_left.first, m_bottom_left.second, depth);
	glVertex3f(m_bottom_left.first, m_top_right.second, depth);
	glVertex3f(m_top_right.first, m_top_right.second, depth);
	glVertex3f(m_top_right.first, m_bottom_left.second, depth);
	glEnd();
}

float Rectangl::area()
{
	return (m_top_right.first - m_bottom_left.first) * (m_top_right.second - m_bottom_left.second);
}

pair<bool, Rectangl> find_intercept(const Rectangl& lhs, const Rectangl& rhs)
{
	auto intercept = true;
	auto interception = Rectangl{ { 0,0 },{ 0,0 } };
	interception.m_is_intercept = true;

	if (float_greater_than(lhs.m_top_right.first, rhs.m_bottom_left.first)
		&& float_less_than(lhs.m_bottom_left.first, rhs.m_top_right.first))
	{
		interception.m_bottom_left.first = max(lhs.m_bottom_left.first, rhs.m_bottom_left.first);
		interception.m_top_right.first = min(lhs.m_top_right.first, rhs.m_top_right.first);
	}
	else
	{
		intercept = false;
	}

	if (float_greater_than(lhs.m_top_right.second, rhs.m_bottom_left.second)
		&& float_less_than(lhs.m_bottom_left.second, rhs.m_top_right.second))
	{
		interception.m_bottom_left.second = max(lhs.m_bottom_left.second, rhs.m_bottom_left.second);
		interception.m_top_right.second = min(lhs.m_top_right.second, rhs.m_top_right.second);
	}
	else
	{
		intercept = false;
	}
	return make_pair(intercept, interception);
}
