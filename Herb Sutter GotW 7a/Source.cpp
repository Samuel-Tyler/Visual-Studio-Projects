//  x.h: original header
//
#include <iosfwd>
#include <list>

// None of A, B, C, D or E are templates.
// Only A and C have virtual functions.
#include "a.h"  // class A
#include "b.h"  // class B
#include "c.h"  // class C
#include "d.h"  // class D

class C;
class E;

class X : public A, private B {
public:
	X(const C&) { ; }
	B  f(int, char*) { return B{}; }
	C  f(int, C c) { return c; }
	C& g(B) { return C{}; }
	E  h(E e);
	virtual std::ostream& print(std::ostream& os) const { return os; };

private:
	std::list<C> clist;
	D            d_;
};

std::ostream& operator<<(std::ostream& os, const X& x) {
	return x.print(os);
}