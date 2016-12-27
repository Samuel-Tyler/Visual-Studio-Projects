#pragma once

#include <vector>
#include <memory>
#include <string>

#include "Drawable_object.h"

class Window
{
public:
	Window(int * argc, char** argv);
	Window(const Window& window) = delete;
	~Window() = default;

	Window& operator=(const Window& window) = delete;

	void begin_loop();
	void display();
	void reshape(int width, int height);
	void set_text(std::string text);
	void display_text();

	template <typename derived_object> void Window::add_drawable(const derived_object& object);
private:
	std::vector<std::unique_ptr<Drawable_object>> m_object_buffer;
	std::string m_text;
};

template <typename derived_object>
void Window::add_drawable(const derived_object& object)
{
	m_object_buffer.push_back(make_unique<derived_object>(object));
}