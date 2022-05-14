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

char test_Luka(big_integer n) {

	if (n % 2 == 0) {
		return 0;
	}

	 std::vector <big_integer> fact_m;
	 big_integer m;
	 m = n - 1;
	 fact_m = fact(m);
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

char test_Poklingtona(big_integer n) {

	if (n % 2 == 0) {
		
		return 0;
	}

	std::vector <big_integer> fact_m;
	big_integer m;
	m = n - 1;
	fact_m = fact(m);
	

	char is_prime = 2;
	
	
	
	for (int i = 0; i < 10; i++) {
		big_integer a;
		a = random(m);

		
		if (power_mod(a, m, n) == 1) {
			
			for (int i = 0; i < fact_m.size(); i++) {
				big_integer q_quad;
				q_quad = fact_m[i] + 1;
				if (q_quad.pow(2) > n) {
					if (NOD(n, a.pow((n - 1) / fact_m[i]) - 1) == 1) {

						is_prime = 1;

					}
					else {
						is_prime = 2;
						break;
					}
				}
				
				
				
			}
		}
		if (is_prime != 2) break;
		
		
	}

	return is_prime;

} 

void T_Prota() {
	for (big_integer k = 5; k < 10; k++) {
		big_integer two_pow("2");
		two_pow = two_pow.pow(k);
		std::cout << two_pow << std::endl;
		for (big_integer R = 2; R < two_pow; R++) {
			big_integer n;
			n = two_pow * R + 1;
			for (int i = 0; i < 10; i++) {
				big_integer z;
				z = 2;
				if (R % z != 0) {
					if (power_mod(z, (n - 1) / 2, n) == n-1) {
						std::cout << n << " Wow!" << std::endl;
						break;
					}
				}
			}
		}
	}
}

void T_Diemitko(big_integer q) {
	
	for (big_integer R = 2; R < 4 * (q + 1); R += 2) {
		big_integer n;
		n = q * R + 1;
		char d = test_Luka(n);
		if (d == 1) {
			if (n > 1000000) std::cout << n << " Wow!" << std::endl;
			if (n > 10000000) return;
			T_Diemitko(n);
			
		}

	}
}
