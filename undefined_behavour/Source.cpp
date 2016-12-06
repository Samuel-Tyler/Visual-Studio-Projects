#include <iostream>
#include <bitset>
#include <list>
#include <string>
#include <algorithm>
#include <complex>

using namespace std;
 /*struct employee
{
	employee(string name_, string addr_) : name(name_), addr(addr_) {}
	string name;
	string addr;
	bool operator== (const string & rhs) const { return name == rhs; }
	bool operator== (const employee & rhs) const { return (name == rhs.name && addr == rhs.addr); }
};

string find_addr(const list<employee>& emps, const string &name) {
	const auto emp = find_if(emps.begin(), end(emps), [&](const auto e) { return e.name == name; } );
	return emp == end(emps) ? string{} : emp->addr;
}

int main()
{
	auto employee_list = list<employee>{employee("Sam", "London"), employee("Shernel", "Kuala Lumpur"), employee("Mariela", "Mexico")};

	cout << "Address of Sam : " << find_addr(employee_list, "Sam"s) << endl;
	cout << "Address of Shernel : " << find_addr(employee_list, "Shernel"s) << endl;
	cout << "Address of Mariela : " << find_addr(employee_list, "Mariela"s) << endl;
	cout << "Address of Steve : " << find_addr(employee_list, "Steve") << endl;

	int i;
	cin >> i;
}
*/

class base {
public:
virtual void f( int );
virtual void f( double );
virtual void g( int i = 10 );
};

void base::f( int ) {
cout << "base::f(int)" << endl;
}

void base::f( double ) {
cout << "base::f(double)" << endl;
}

void base::g( int i ) {
cout << i << endl;
}

class derived: public base {
public:
void f( complex<double> );
void g( int i = 20 );
};

void derived::f( complex<double> ) {
cout << "derived::f(complex)" << endl;
}

void derived::g( int i ) {
cout << "derived::g() " << i << endl;
}

int main() {
	base    b;
	derived d;
	base*   pb = new derived;

	b.f(1.0); // base::f(double)
	d.f(1.0); // derived::f(double)
	pb->f({1.0}); // base:f(double)

b.g(); // base::10
d.g(); // derived::20
pb->g(); // derived::10

int i;
cin >> i;

delete pb;
}