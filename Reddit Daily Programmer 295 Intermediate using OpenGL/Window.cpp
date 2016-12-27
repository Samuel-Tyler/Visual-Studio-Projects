#include "Window.h"

#include <GL/glew.h>
#include <GL/freeglut.h>

namespace window_callback {
	Window* global_window_ptr = nullptr;

	void display_func()
	{
		if (global_window_ptr != nullptr)
		{
			global_window_ptr->display();
		}
	}

	void reshape_func(int width, int height)
	{
		if (global_window_ptr != nullptr)
		{
			global_window_ptr->reshape(width, height);
		}
	}
}

Window::Window(int* argc, char** argv)
	:
	m_object_buffer{}
{
	window_callback::global_window_ptr = this;
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Rectangle Intercept");
	glutDisplayFunc(window_callback::display_func);
	glutReshapeFunc(window_callback::reshape_func);
	glEnable(GL_DEPTH_TEST);
}

void Window::display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glOrtho(-5.0, 5.0, -5.0, 5.0, 5.0, -5.0);
	glMatrixMode(GL_MODELVIEW);

	for (auto& object_ptr : m_object_buffer)
	{
		object_ptr->draw();
	}
	display_text();
	glFlush();
}

void Window::reshape(int width, int height) {
	;
}

void Window::begin_loop()
{
	glutMainLoop();
}

void Window::set_text(std::string text)
{
	m_text = text;
}

void Window::display_text()
{
	glPushMatrix();
	glColor3f(0.5f, 0.5f, 1.0f);
	glRasterPos2f(-4, -4);
	glutBitmapString(GLUT_BITMAP_HELVETICA_12, (unsigned char*)m_text.c_str());
	glPopMatrix();
}