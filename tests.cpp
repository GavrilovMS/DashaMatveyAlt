#include "tests.h"


std::vector <Big_int> fact(Big_int m)
{
	std::vector <Big_int> fact_m;
	
	for (Big_int q({ 2 }); multiplication(q, q) <= m; q = summa(to_big(1), q)) {
		if (mod(m, q) == to_big(0)) {
			fact_m.push_back(q);

			while (mod(m, q) == to_big(0)) {
				m = div_big_int(m, q);
			}
		}

	}
	if ((m > to_big(1))) {
		fact_m.push_back(m);
	}
	return fact_m;
}

void test_Luka(Big_int n) {
	 std::vector <Big_int> fact_m;
	 Big_int m;
	 m = difference(n, to_big(1));
	 fact_m = fact(m);
	 bool is_prime = false;
	 for (int i = 0; i < 100; i++) {
		 Big_int a;
		 a = random(m);
		 if (power_mod(a, m, n) == to_big(1)) {
			 for (int i = 0; i < fact_m.size(); i++) {
				 if (power_mod(a, div_big_int(m, fact_m[i]), n) != to_big(1)) {
					 is_prime = true;
					 break;
				 }
				 
			 }
		 }
	 }
	 n.print();
	 if (is_prime) {
		 std::cout << " is prime" << std::endl;
	 }
	 else {
		 std::cout << " is not prime" << std::endl;;
	 }
}
