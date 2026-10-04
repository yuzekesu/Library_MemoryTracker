#include "./code/Memory.h"
#include "./code/MemoryTracker.h"

void foo();

int main() {
	foo();
	foo();
	return 0;
}

class coo {
public:
	operator std::string() const {
		return std::string{ "Custome class workds too ;)" };
	}
};

class eoo {
public:
	// empty.
};

void foo() {
	int a = 0;
	float b = 0.0f;
	coo c{};
	double d = 0.0;
	eoo e{};
	Memory<int> mem_a(a, "a");
	Memory<float> mem_b(b, "b", "f");
	Memory<coo> mem_c(c, "c", "");
	Memory<double> mem_d(d, "c", "");
	Memory mem_e(e, "e", "");
	MemoryTracker tracker(100u, mem_a, mem_b, mem_c, mem_d, mem_e);
	for (int i = 0; i < 10; i++) {
		a++;
		b += 0.1f;
		d += 0.01;
		Sleep(500);
	}
}