#include <iostream>
using namespace std;

struct A {
    A() {++A_count;}
    A(const A&) {++A_count;}
    A(A&&) {++A_count;}
    ~A() {--A_count;}

    static int get_count() {return A_count;}
private:
    static int A_count;
};

int main() {
    A var;

    int c0 = var.get_count(); //some compilers give a warning, but it's ok.
    int c1 = A::get_count(); //normal way
}