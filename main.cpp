#include <math.h>
#include <vector>
#include <iostream>

using namespace std;



int power_mod(const long long& x, long long power, const long long& module) {
	if (power == 0LL) return 1LL;
	if (power % 2 == 1) return (x * power_mod(x, power - 1, module)) % module;
	long long tmp = power_mod(x, power / 2, module);
	return (tmp * tmp) % module;
}
int main() {
	long long int n = 909091;
	long long int m = n - 1;
	vector <int> fact_m;



	for (long long q = 2; q * q <= m; q++) {
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

	/*for (size_t i = 0; i < fact_m.size(); i++) {
		cout << fact_m[i] << endl;
	}*/
	char is_prime = false;
	for (int a = 1; a < (n - 1); a++) {
		if (power_mod(a, n - 1, n) == 1) {
			for (int i = 0; i < fact_m.size(); i++) {
				if (power_mod(a, (n - 1) / fact_m[i], n) == 1) {
					break;
				}
				if (i == fact_m.size() - 1) {
					is_prime = true;
				}
			}
		}
	}

	if (is_prime) {
		cout << "true" << endl;
	}
	else {
		cout << "false" << endl;
	}




	return 0;
}