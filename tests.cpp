#include "tests.h"


std::vector <big_integer> fact(big_integer m)
{
	std::vector <big_integer> fact_m;

	for (big_integer q = 2; q * q <= m; q++) {
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
		if (NOD(a, n) == 1) {
			if (power_mod(a, m, n) == 1) {
				for (int i = 0; i < fact_m.size(); i++) {
					if (power_mod(a, m / fact_m[i], n) != 1) {
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

	}
	return is_prime;


}

char test_Luka(big_integer n) {

	if (n % 2 == 0) {
		return 0;
	} //если число четное, то оно точно не простое
	std::vector<big_integer> fact_m;
	big_integer m;
	m = n - 1;
	fact_m = fact(m);//здесь хранятся все делители числа n-1
	char is_prime = 0;//переменная, отвечающая за результат
	//0 - число составное
	//1 - число простое
	//3 - число возможно составное
	for (int i = 0; i < 10; i++) {
		big_integer a;
		a = random(m);//функция рандом генерирует рандомное число а в диапозоне(1,n)
		if (NOD(a, n) == 1) {
			if (power_mod(a, m, n) == 1) {
				for (int i = 0; i < fact_m.size(); i++) {
					if (power_mod(a, m / fact_m[i], n) != 1) {
						is_prime = 1;

					}
					else {
						is_prime = 3;
						break;
						//если какой-то делитель не прошел проверку на второе
						//условие, то мы переходим к следующей а
					}

				}
			}
		}

		if (is_prime != 3) break;
		//если нашлось такое а, что все проверки прошли успешно и мы точно можем сказать, что
		//число n-простое, то проверять остальные а не имеет смысла
	}
	return is_prime;


}


void T_Diemitko(big_integer q, big_integer left_edge, big_integer right_edge) {

	for (big_integer R = 2; R < 4 * (q + 1); R += 2) {
		big_integer n;
		std::vector<big_integer> fact_m;
		fact_m = fact(R);
		fact_m.push_back(q);
		n = q * R + 1;
		char d = test_Luka(n, fact_m);
		if (d == 1) {
			if (n > right_edge) return;
			if (n > left_edge) std::cout << n << " is prime" << std::endl;
			if (_kbhit()) return;
			T_Diemitko(n, left_edge, right_edge);

		}

	}
}



void T_Luka_Lemera(big_integer n) {
	big_integer M("2");
	M = M.pow(n) - 1;
	//проверяем простоту числа n тестом Люка
	if (test_Luka(n) != 1)
	{
		//std::cout << M << " is not prime" << std::endl;
		return;
	}
	big_integer U("4");
	for (big_integer k = 1; k <= n - 2; k++) {
		U = power_mod((U.pow(2) - 2), 1, M);
	}
	if (U == 0)
	{
		std::cout << M << " is prime" << std::endl;
	}
	else
	{
		//std::cout << M << " is not prime" << std::endl;
	}
}
