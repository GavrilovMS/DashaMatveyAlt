#include <vector>
#include <iostream>
#include <string>

class Big_int {
private:
	std::vector <unsigned short> num;
public:
	
	Big_int(std::vector<unsigned short> number = { 0 });
	
	Big_int& operator = (std::string str);
	bool operator==(Big_int right);
	bool operator!=(Big_int right);
	bool operator<(Big_int right);
	bool operator>(Big_int right);
	bool operator<=(Big_int right);
	bool operator>=(Big_int right);
	unsigned short& operator[](size_t index);
	void push_back(unsigned short a);
	void pop_back();
	size_t size();
	void print();
};

void zerkalo(Big_int& a);
void delete_null(Big_int& a);
char less_for_big_int(Big_int a, Big_int b, bool del);
Big_int summa(Big_int a, Big_int b);
Big_int difference(Big_int a, Big_int b);
Big_int multiplication(Big_int a, Big_int b);
Big_int pow(Big_int a, Big_int pow);
Big_int reduce_big_int(Big_int minuend, Big_int subtrahend);
Big_int inc_big_int(Big_int a);
Big_int div_big_int(Big_int a, Big_int b);
Big_int mod(Big_int a, Big_int b);
Big_int power_mod(Big_int a, Big_int power, Big_int MOD);
Big_int to_big(long long a);
Big_int random(Big_int a);
