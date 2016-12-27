#include <vector>

using namespace std;

struct point {
	int x;
	int y;
};

class polygon {
public:
	polygon() : area{ -1 } {}

	void add_point(const point pt) {
		area = -1;
		points.push_back(pt);
	}

	point get_point(const int i) const { return points[i]; }

	int get_num_points() const { return points.size(); }

	double get_area() const {
		if (area < 0)   // if not yet calculated and cached
			calc_area();     // calculate now
		return area;
	}

private:
	void calc_area() const {
		double tmp = 0;
		vector<point>::const_iterator i;
		for (i = begin(points); i != end(points); ++i)
			tmp += i->x * i->y;
		area = tmp;
	}

	vector<point> points;
	mutable double area;
};

polygon operator+(polygon& lhs, const polygon& rhs) {
	auto ret = lhs;
	const auto last = rhs.get_num_points();
	for (auto i = 0; i < last; ++i) // concatenate
		ret.add_point(rhs.get_point(i));
	return ret;
}

void f(polygon& poly) {
	polygon(poly).add_point({ 0,0 });
}
 
void g(polygon& poly) { poly.add_point({ 1,1 }); }

void h(polygon* const poly) { poly->add_point({ 2,2 }); }

int main() {
	polygon poly;
	const polygon cpoly;

	f(poly);
	//f(cpoly);
	g(poly);
	h(&poly);

	while (1)
		;
}