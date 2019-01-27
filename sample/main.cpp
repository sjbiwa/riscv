#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

class MyClass {
public:
	MyClass() : a(0), b(1) {}
	int get() { return a+b;}
	
private:
	int a;
	int b;
};

MyClass aaa;

volatile uint64_t long_value;
int main()
{
	MyClass a;
	for (;;) {
		long_value += 123;
	}
	return 0;
}
