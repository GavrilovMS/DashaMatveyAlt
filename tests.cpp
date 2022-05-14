#include "tests.h"


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

big_integer NOD(big_integer a, big_integer b) {
	while (a != 0 && b != 0)
		if (a > b) a %= b;
		else b %= a;
	return a + b;
}

char test_Luka(big_integer n, const std::vector <big_integer>& fact_m) {

	if (n % 2 == 0) {
		return 0;
	}

	 
	 big_integer m;
	 m = n - 1;
	 
	 char is_prime = 2;
	 
	 for (int i = 0; i < 10; i++) {
		 big_integer a;
		 a = random(m);
		 if (power_mod(a, m, n) == 1) {
			 for (int i = 0; i < fact_m.size(); i++) {
				 if (power_mod(a, m/fact_m[i], n) != 1) {
					 is_prime = 1;
					 
				 }
				 else {
					 is_prime = 3;
					 break;
				 }
				 
			 }
		 }
		 
		 if (is_prime != 3) break;

	 } 
	 return is_prime;
	
	
}


void T_Diemitko(big_integer q) {
	
	for (big_integer R = 2; R < 4 * (q + 1); R += 2) {
		big_integer n;
		std::vector<big_integer> fact_m;
		fact_m = fact(R);
		fact_m.push_back(q);
		n = q * R + 1;
		char d = test_Luka(n, fact_m);
		if (d == 1) {
			if (n > 10000000000) std::cout << n << " Wow!" << std::endl;
			if (n > 1000000000000000) return;
			T_Diemitko(n);
			
		}

	}
}

std::vector <big_integer> q_all = { 2,3,5,7,11,13,17,19,23,29,31,37,41 };

void T_Poklingtona() {
	big_integer F(1);
	std::vector<big_integer> fact_m;

	int count_q = 1+rand() % 2;
	for (int i = 0; i < count_q; i++) {
		big_integer q;
		q = q_all[rand() % q_all.size()];
		
		fact_m.push_back(q);

		big_integer a;
		a = 2 + rand() % 2;
		
		F *= q.pow(a);
	}

	big_integer R;
	R = random(F / 2);
	if (R % 2 != 0) R -= 1;

	big_integer n;
	n = F * R + 1;
	
	char is_prime = 2;
	for (int i = 0; i < 10; i++) {
		big_integer a;
		a = random(n - 1);

		if (power_mod(a, n-1, n) == 1) {

			for (int i = 0; i < fact_m.size(); i++) {
					if (NOD(n, a.pow((n - 1) / fact_m[i]) - 1) == 1) {

						is_prime = 1;
					}
					else {
						is_prime = 2;
						break;
					}
			}
		}
		if (is_prime == 1) break;
	}
	if (is_prime == 1) {
		std::cout << n << " Wow!" << std::endl;
	}
}
