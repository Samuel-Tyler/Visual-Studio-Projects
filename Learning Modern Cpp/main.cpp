#include <iostream>
#include <string>
#include <memory>
#include <math.h>

template <typename T>
typename std::remove_reference<T>::type&& move(T&& arg)
{
	return static_cast<typename std::remove_reference<T>::type&&>(arg);
}

template <typename T>
void swap(T& lhs, T& rhs)
{
	T tmp(move(lhs));
	lhs = move(rhs);
	rhs = move(tmp);
	tmp.print();
}

class Widget
{
public:
	Widget(std::string str) : string_(str) { std::cout << "Constructor" << std::endl; }
	~Widget() { std::cout << "Destructor" << std::endl; };
	Widget(const Widget & rhs) : string_(rhs.string_) { std::cout << "Copy Constructor" << std::endl; }
	Widget(const Widget && rhs) : string_(std::move(rhs.string_)) { std::cout << "Move Constructor" << std::endl; }
	Widget& operator=(const Widget & rhs) { string_ = rhs.string_; std::cout << "Copy Assignment" << std::endl; return *this; }
	Widget& operator=(const Widget && rhs) { string_ = std::move(rhs.string_); std::cout << "Move Assignment" << std::endl; return *this; }
	
	friend std::ostream& operator<<(std::ostream& os, const Widget& widget) { os << widget.string_; return os; }

	void print() const { std::cout << string_ << std::endl; }
	
public:
	std::string string_;
};

template <class T>
void print (const T& input)
{
	input.print();
}

int main()
{

	decltype(auto) widget_ptr = std::make_shared<Widget>("test");
	widget_ptr = std::make_shared<Widget>("potato");

	std::cout << "Widget contents : " << *widget_ptr << std::endl;

	while (1)
		;
}
