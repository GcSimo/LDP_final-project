#include <iostream>
using namespace std;

class A {
	private:
		static int A_count;
		int a;
	public:
		A() { a = A_count++; }

		static int get_count() { return A_count; }
		int get_id() { return a; }
};

int A::A_count = 0;

int main() {
	cout << "ok" << endl;
	A a1;
	cout << a1.get_id() << " - " << a1.get_count() << endl;

	A a2;
	cout << a2.get_id() << " - " << a2.get_count() << endl;

	A a3;
	cout << a3.get_id() << " - " << a3.get_count() << endl;
	cout << "fine" << endl;
}
