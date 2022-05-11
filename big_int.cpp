#include "big_int.h"

Big_int::Big_int(std::vector<unsigned short> number) {
	num = number;
}


Big_int& Big_int::operator= (std::string str) {
	num.clear();
	
	while (str != "") {
		const char digit = str[str.length()-1];
		num.push_back(atoi(&digit));
		str.pop_back();
	}
	return (*this);
}

bool Big_int::operator==(Big_int right)
{
	if (num[num.size() - 1] == 0)
	{
		delete_null(*this);
	}
	if (right[right.size() - 1] == 0)
	{
		delete_null(right);
	}
	if (num.size() != right.size())
	{
		return false;
	}
	else
	{
		for (size_t i = 0; i < num.size(); i++)
		{
			if (num[i] != right[i])
			{
				return false;
			}
		}
	}
	return true;
}

bool Big_int::operator!=(Big_int right)
{
	return !((*this) == right);
}

bool Big_int::operator<(Big_int right)
{
	if (num[num.size() - 1] == 0)
	{
		delete_null(*this);
	}
	if (right[right.size() - 1] == 0)
	{
		delete_null(right);
	}
	if (num.size() > right.size())
	{
		return false;
	}
	else if (num.size() == right.size())
	{
		for (int i = num.size() - 1; i >= 0; i--)
		{
			if (num[i] != right[i])
			{
				if (num[i] > right[i])
				{
					return false;
				}
				else
				{
					return true;
				}

			}
		}
		return false;
	}
	return true;
}

bool Big_int::operator>(Big_int right)
{
	if (!((*this) < right) && !((*this) == right))
	{
		return true;
	}
	return false;
}

bool Big_int::operator<=(Big_int right)
{
	if (((*this) < right) || ((*this) == right))
	{
		return true;
	}
	return false;
}

bool Big_int::operator>=(Big_int right)
{
	if (((*this) > right) || ((*this) == right))
	{
		return true;
	}
	return false;
}

unsigned short& Big_int::operator[](size_t index) {
	return num[index];
}

void Big_int::push_back(unsigned short a) {
	num.push_back(a);
}

void Big_int::pop_back() {
	num.pop_back();
}

size_t Big_int::size() {
	return num.size();
}

void zerkalo(Big_int& a)
{
	Big_int copy = a;
	for (size_t i = 0; i < a.size(); i++)
	{
		a[i] = copy[a.size() - 1 - i];
	}
}

void delete_null(Big_int& a) {
	long long length = a.size();
	bool flag = 0;
	for (int i = 0; i < length; i++)
	{
		if (a[i] != 0)
		{
			flag = 1;
			break;
		}
	}
	if (!flag)
	{
		while (a.size() != 1)
		{
			a.pop_back();
		}
	}
	if (flag) {
		while (a[length - 1] == 0)
		{
			a.pop_back();
		    --length;
		}
	}
}

char less_for_big_int(Big_int a, Big_int b, bool del) {
	if (del) {
		zerkalo(a);
		zerkalo(b);
	}
	char k = ' '; // если к == ' ', значит числа одинаковой длины
	delete_null(a);
	delete_null(b);
	unsigned long long length = a.size();
	if (a.size() > b.size())
	{
		length = a.size();
		k = 'a';// если к == 1, значит первое число длиннее второго
		return k;
	}
	else if (b.size() > a.size())
	{
		length = b.size();
		k = 'b'; // если к == 2, значит второе число длиннее первого
		return k;
	}
	// если числа одинаковой длины, то необходимо сравнить их веса
	else
	{
		for (int i = length - 1; i >= 0; i--) {
			// если разряд первого числа больше, значит первое число больше второго
			if (a[i] > b[i]) { k = 'a'; return k; }
			// если разряд второго числа больше, значит второе число больше первого
			if (b[i] > a[i])
			{
				k = 'b';
				return k;
			}
		}
	}
	if (k == ' ')
	{
		k = 'a';
	}
	return k;
}

Big_int summa(Big_int a, Big_int b) {
	unsigned long long length = 0;
	// определяем длину массива суммы
	if (a.size() > b.size())
		length = a.size() + 1;
	else
		length = b.size() + 1;

	//чтобы не было ошибки выхода за рамки размеров векторов добавляем незначащие нули
	for (int i = b.size() - 1; i < length; i++)
	{
		b.push_back(0);
	}
	for (int i = a.size() - 1; i < length; i++)
	{
		a.push_back(0);
	}

	for (int i = 0; i < length; i++)
	{
		b[i] += a[i]; // суммируем последние разряды чисел
		b[i + 1] += (b[i] / 10); // если есть разряд для переноса, переносим его в следующий разряд
		b[i] %= 10; // если есть разряд для переноса он отсекается
	}

	//убираем из результата незначащие нули
	delete_null(b);
	return b;
}

Big_int difference(Big_int a, Big_int b) {
	long long length = 0;
	if (less_for_big_int(a, b, false) == 'a')
	{
		length = a.size();
	}
	else
	{
		length = b.size();
	}
	//чтобы не было ошибки выхода за рамки размеров векторов добавляем незначащие нули
	for (int i = b.size() - 1; i < length; i++)
	{
		b.push_back(0);
	}
	for (int i = a.size() - 1; i < length; i++)
	{
		a.push_back(0);
	}

	Big_int c;
	for (unsigned long long i = 0; i < length; i++)
	{
		c.push_back(0);
	}

	//последний цикл работает для a>b, поэтому, если a<b, меняем их местами
	if (less_for_big_int(a, b, false) == 'b')
	{
		c = a;
		a = b;
		b = c;
		for (unsigned long long i = 0; i < c.size(); i++)
		{
			c[i] = 0;
		}
	}

	for (unsigned long long i = 0; i < length; i++) // проход по всем разрядам числа, начиная с последнего, не доходя до первого
	{
		if (i < (length - 1)) // если текущий разряд чисел не первый
		{
			a[i + 1]--; // в следующуем разряде большего числа занимаем 1.
			c[i] += 10 + a[i]; // в ответ записываем сумму значения текущего разряда большего числа и 10-ти

		}
		else // если текущий разряд чисел - первый
		{
			c[i] += a[i];
		} // в ответ суммируем значение текущего разряда большего числа

		c[i] -= b[i]; // вычитаем значение текущего разряда меньшего числа

		if (c[i] / 10 > 0) // если значение в текущем разряде двухразрядное
		{
			c[i + 1]++; // переносим единицу в старший разряд
			c[i] %= 10; // в текущем разряде отсекаем ее
		}
	}

	//убираем из результата незначащие нули
	delete_null(c);
	return c;
}
Big_int multiplication(Big_int a, Big_int b) {
	unsigned long long length = a.size() + b.size() + 1;
	Big_int c;
	for (unsigned long long i = 0; i < length; i++)
	{
		c.push_back(0);
	}
	for (unsigned long long i = 0; i < a.size(); i++)
		for (unsigned long long j = 0; j < b.size(); j++)
		{
			c[i + j] += a[i] * b[j];
		}

	for (unsigned long long i = 0; i < length - 1; i++)
	{
		c[i + 1] += c[i] / 10;
		c[i] %= 10;
	}

	delete_null(c);
	return c;
}

Big_int pow(Big_int a, Big_int pow) {
	Big_int res, i;
	res = "1";
	
	for (Big_int i({ 0 }); i < pow; i = summa(i, to_big(1))) {
		res = multiplication(res, a);
	}
	return res;
}
Big_int reduce_big_int(Big_int minuend, Big_int subtrahend) {
	for (size_t cur_pos = 0; cur_pos < subtrahend.size(); cur_pos++)
	{
		size_t minuend_cur_pos = minuend.size() - 1 - cur_pos;
		size_t subtrahend_cur_pos = subtrahend.size() - 1 - cur_pos;
		unsigned short& cur_minuend_dig_ref = minuend[minuend_cur_pos];
		const short& cur_subtrahend_dig_ref = subtrahend[subtrahend_cur_pos];
		if (cur_minuend_dig_ref >= cur_subtrahend_dig_ref)
		{
			cur_minuend_dig_ref -= cur_subtrahend_dig_ref;
		}
		else
		{
			(cur_minuend_dig_ref -= cur_subtrahend_dig_ref) += 10;
			for (int i = 1; ; ++i)
			{
				if (minuend[minuend_cur_pos - i] == 0)
				{
					minuend[minuend_cur_pos - i] = 9;
				}
				else
				{
				    --minuend[minuend_cur_pos - i];
					break;
				}
			}
		}
		if (minuend[0] == 0)
		{
			zerkalo(minuend);
			delete_null(minuend);
			zerkalo(minuend);
		}
	}
	if (minuend[0] == 0)
	{
		zerkalo(minuend);
		delete_null(minuend);
		zerkalo(minuend);
	}
	return minuend;
}
Big_int inc_big_int(Big_int a) {
	for (size_t cur_pos = a.size() - 1;; --cur_pos)
	{
		if (a[cur_pos] < 9)
		{
			++a[cur_pos];
			return a;
		}
		else
		{
			a[cur_pos] = 0;
			if (cur_pos == 0)
			{
				zerkalo(a);
				a.push_back(1);
				zerkalo(a);
				return a;
			}
		}
	}
}
Big_int div_big_int(Big_int a, Big_int b) {
	zerkalo(a);
	zerkalo(b);
	if (b.size() == 1 && b[0] == 0)
	{
		std::cout <<  "div on null" << std::endl;
		return b;
	}

	Big_int res( {0} );
	Big_int minuend = a;
	Big_int subtrahend = b;

	while (subtrahend.size() < minuend.size())
	{
		subtrahend.push_back(0);
	}

	for (;;)
	{
		while (less_for_big_int(minuend, subtrahend, true) == 'a')
		{
			minuend = reduce_big_int(minuend, subtrahend);
			res = inc_big_int(res);
		}
		if (subtrahend.size() <= b.size())
		{
			break;
		}

		subtrahend.pop_back();
		res.push_back(0);
		if (res[0] == 0)
		{
			zerkalo(res);
			delete_null(res);
			zerkalo(res);
		}
	}
	zerkalo(res);
	return res;
}

void Big_int::print() {
	for (int i = num.size() - 1; i >= 0; i--)
	{
		std::cout << num[i];
	}
}

Big_int mod(Big_int a, Big_int b) {
	zerkalo(a);
	zerkalo(b);
	if (b.size() == 1 && b[0] == 0)
	{
		std::cout << "div on null" << std::endl;
		return b;
	}
	Big_int minuend = a;
	Big_int subtrahend = b;

	while (subtrahend.size() < minuend.size())
	{
		subtrahend.push_back(0);
	}

	for (;;)
	{
		while (less_for_big_int(minuend, subtrahend, true) == 'a')
		{
			minuend = reduce_big_int(minuend, subtrahend);
		}
		if (subtrahend.size() <= b.size())
		{
			break;
		}

		subtrahend.pop_back();
	}
	zerkalo(minuend);
	return minuend;
}

Big_int power_mod(const Big_int a, Big_int power, const Big_int MOD) {
	if (power == to_big(0)) return to_big(1);
	if (mod(power, to_big(2)) == to_big(1)) return mod((multiplication(a, power_mod(a, difference(power, to_big(1)), MOD))), MOD);
	Big_int tmp;
	tmp = power_mod(a, div_big_int(power, to_big(2)), MOD);
	return mod(multiplication(tmp, tmp), MOD);
}


Big_int to_big(long long a) {
	Big_int big_a;
	big_a = std::to_string(a);
	return big_a;
}

Big_int random(Big_int a) {
	Big_int res;
	res = a;
	for (size_t i = 0; i < res.size(); i++) {
		res[i] = rand() % 10;
	}
	delete_null(res);
	return res;
}
