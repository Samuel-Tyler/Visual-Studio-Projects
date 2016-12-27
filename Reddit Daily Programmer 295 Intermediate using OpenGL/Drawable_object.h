#pragma once

class Drawable_object {
public:
	Drawable_object() = default;
	virtual ~Drawable_object() = default;

	virtual void draw() const = 0;
};