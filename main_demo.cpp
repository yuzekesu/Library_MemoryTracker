#include "./code/Memory.h"
#include "./code/MemoryTracker.h"

void foo();

int main() {
	foo();
	foo();
	return 0;
}

void foo() {
	int a = 0;
	float b = 0.0f;
	double c = 0.0;
	Memory<int> mem_a(a, "a: ");
	Memory<float> mem_b(b, "b: ", "f");
	Memory<double> mem_c(c, "c: ", "");
	MemoryTracker tracker(100u, mem_a, mem_b, mem_c);
	for (int i = 0; i < 10; i++) {
		a++;
		b += 0.1f;
		c += 0.01;
		Sleep(500);
	}
}