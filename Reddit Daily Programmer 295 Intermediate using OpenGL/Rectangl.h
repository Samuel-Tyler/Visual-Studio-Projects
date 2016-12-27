#pragma once

#include "Drawable_object.h"
#include <utility>

#include <GL\glew.h>
#include <GL\freeglut.h>

using coord = std::pair<float, float>;

struct Rectangl : public Drawable_object
{
	Rectangl(coord bottom_left, coord top_right);
	~Rectangl() = default;
	coord m_bottom_left;
	coord m_top_right;
	void draw() const override;
	float area();
	bool m_is_intercept;
};

template <typename T>
bool float_greater_than(const T lhs, T rhs)
{
	return (lhs > (1 + numeric_limits<T>::epsilon()) * rhs);
}

template <typename T>
bool float_less_than(const T lhs, T rhs)
{
	return (lhs < (1 - numeric_limits<T>::epsilon()) * rhs);
}

std::pair<bool, Rectangl> find_intercept(const Rectangl& lhs, const Rectangl& rhs);