// PI

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>

#ifdef _MSC_VER
#include <ctime>
inline double get_time()
{
	return static_cast<double>(std::clock()) / CLOCKS_PER_SEC;
}
#else
#include <sys/time.h>
inline double get_time()
{
	timeval tv;
	gettimeofday(&tv, 0);
	return tv.tv_sec + 1e-6 * tv.tv_usec;
}
#endif

typedef unsigned long long number;

const int FIG      = 8;
const number BASE  = 0xffffffffULL;
const number NN    = 100000000ULL;

// C = 1.0 / (4 * log10(2)) / FIG;
#define C (0.830482023722/FIG)
#define M (X/FIG+2)
#define N (static_cast<int>(X*C+2))

template<int X> class PI {
private:
	number ans[N];

public:
	void add(number* a, number* b);
	void sub(number* a, number* b);
	void div(number* a, number d);
	number intdiv(number x, number y);
	void mul(number* a, number d);
	void atan(number* a, number m);
	number or_numbers(number* a);
	bool has_bit(number* a);
	void decimal(number* a, number* w);
	void print();
	void calc();
};

// a <- arctan(1 / m)
template<int X>
void PI<X>::atan(number* a, number m)
{
	number b[N] = { 1 };
	number c[N] = { 1 };
	div(b, m);
	std::copy(b, b + N, a);
	const number m2 = m * m;
	for (int i = 1; has_bit(c); i++) {
		div(b, m2);
		std::copy(b, b + N, c);
		div(c, i * 2 + 1);
		if (i & 1) sub(a, c);
		else add(a, c);
	}
}

// a <- a + b
template<int X>
void PI<X>::add(number* a, number* b)
{
	for (int i = 0; i < N; i++) {
		number x = a[i] + b[i];
		if (x & ~BASE) {
			a[i] = x & BASE;
			int j;
			for (j = i - 1; a[j] == BASE; j--) a[j] = 0;
			a[j]++;
		} else a[i] = x;
	}
}

// a <- a - b  (a > b)
template<int X>
void PI<X>::sub(number* a, number* b)
{
	for (int i = 0; i < N; i++) {
		if (a[i] < b[i]) {
			a[i] = (BASE + 1) + a[i] - b[i];
			int j;
			for (j = i - 1; a[j] == 0; j--) a[j] = BASE;
			a[j]--;
		} else a[i] -= b[i];
	}
}

// a <- a / d  (d <= BASE)
template<int X>
void PI<X>::div(number* a, number d)
{
	number res = 0;
	for (int i = 0; i < N; i++) {
		res <<= (FIG * 4);
		number x = a[i] + res;
		number q = x / d;
		a[i] = q;
		res = x - q * d;
	}
}

template<int X>
number PI<X>::intdiv(number x, number y)
{
	const number maxbit = ~((number)-1>>1);
	number a = 0;
    number b = 0;
	int cnt = sizeof(number) * 8;

	while (cnt--) {
		a <<= 1ULL;
		if (x & maxbit) a |= 1ULL;
		x <<= 1ULL;
		b <<= 1ULL;
		if (a >= y) { ++b; a -= y; }
	}
	return b;
}

// a <- a * d  (d <= BASE)
template<int X>
void PI<X>::mul(number* a, number d)
{
	number q = 0;
	for (int i = N - 1; i >= 0; i--) {
		number x = a[i] * d + q;
		a[i] = x & BASE;
		q = x >> (FIG * 4);
	}
}

// OR numbers
template<int X>
number PI<X>::or_numbers(number* a)
{
	number ret = 0;
	for (int i = 0; i < N; i++) ret |= a[i];
	return ret;
}

template<int X>
bool PI<X>::has_bit(number* a)
{
	for (int i = 0; i < N; i++) if (a[i]) return true;
	return false;
}

// hex to decimal number
template<int X>
void PI<X>::decimal(number* a, number* w)
{
	number b[N];
	std::copy(a, a + N, b);
	w[0] = b[0];
	b[0] = 0;
	for (int i = 1; i < M; i++) {
		mul(b, NN);
		w[i] = b[0];
		b[0] = 0;
	}
}

// print answer
template<int X>
void PI<X>::print()
{
	number w[M];
	decimal(ans, w);
	std::cout << std::setw(4) << std::right << w[0] << ".";
	for (int i = 1; i < M; i++) {
		std::cout << std::setw(FIG) << std::setfill('0') << w[i] << " ";
		if(i % 6 == 0) std::cout << std::endl << "     ";
	}
	std::cout << std::endl;
}

// calculate PI
// Machin's formula: 4 * arctan(1/5) - arctan(1/239) = PI / 4
template<int X>
void PI<X>::calc()
{
	number x[N];
	atan(ans, 5);
	mul(ans, 4);
	atan(x, 239);
	sub(ans, x);
	mul(ans, 4);
}

int main()
{
	std::ios_base::sync_with_stdio(false);

	PI<10000> pi;

	double start_time = get_time();
	pi.calc();
	double end_time = get_time();
	pi.print();

	std::cerr << "Time: " << end_time - start_time << std::endl;

	return 0;
}
