#include <iostream>
using namespace std;

class nul {
	protected:
		nul() {}
	public:
		virtual string to_string() const = 0;
};

class A: public nul {
	private:
		int a;
	public:
		A(int a) : a{a} {}
		string to_string() const { return "a: " + std::to_string(a); }
};

class B : public nul {
	private:
		int a;
		int b;
	public:
		B(int a, int b) : a(a), b {b} {}
		string to_string() const { return "a: " + std::to_string(a) + " - b: " + std::to_string(b); }
};


std::ostream &operator<<(std::ostream &os, nul *a) {
	os << a->to_string();
	return os;
}

int main() {
	A aptr(1);
	B bptr(2,3);

	cout << &aptr << endl;
	cout << &bptr << endl;
}