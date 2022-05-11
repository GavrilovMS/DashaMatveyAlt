#include "tests.h"
#include <iostream>

std::vector <big_integer> fact(big_integer m)
{
	std::vector <big_integer> fact_m;
	
	for (big_integer q = 2; q*q <= m; q++) {
		if (m % q == 0) {
			fact_m.push_back(q);

			while (m % q == 0) {
				m /= q;
			}
		}

	}
	if (m > 1) {
		fact_m.push_back(m);
	}
	return fact_m;
}

void test_Luka(big_integer n) {
	 std::vector <big_integer> fact_m;
	 big_integer m;
	 m = n - 1;
	 fact_m = fact(m);
	 bool is_prime = false;
	 for (int i = 0; i < 10; i++) {
		 big_integer a;
		 a = random(m);
		 if (power_mod(a, m, n) == 1) {
			 for (int i = 0; i < fact_m.size(); i++) {
				 if (power_mod(a, m/fact_m[i], n) != 1) {
					 is_prime = true;
					 break;
				 }
				 
			 }
		 }
		 else {
			 break;
		 }
	 }
	
	 if (is_prime) {
		 std::cout << n << " is prime" << std::endl;
	 }
	 else {
		 std::cout << n << " is not prime" << std::endl;;
	 }
}
