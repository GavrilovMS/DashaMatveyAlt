#include "big_int.h"

// создает длинное целое число со значением 0
big_integer::big_integer() {
}

// создает длинное целое число из C++-строки
big_integer::big_integer(std::string str) {
    if (str.length() == 0) {
    }
    else {
        for (long long i = str.length(); i > 0; i -= 9) {
            if (i < 9)
                this->_digits.push_back(atoi(str.substr(0, i).c_str()));
            else
                this->_digits.push_back(atoi(str.substr(i - 9, 9).c_str()));
        }

        this->_remove_leading_zeros();
    }
}

// удаляет ведущие нули
void big_integer::_remove_leading_zeros() {
    while (this->_digits.size() > 1 && this->_digits.back() == 0) {
        this->_digits.pop_back();
    }
}

// печатает число в поток вывода
std::ostream& operator <<(std::ostream& os, const big_integer& bi) {
    if (bi._digits.empty()) os << 0;
    else {
        os << bi._digits.back();
        char old_fill = os.fill('0');
        for (long long i = static_cast<long long>(bi._digits.size()) - 2; i >= 0; --i) os << std::setw(9) << bi._digits[i];
        os.fill(old_fill);
    }

    return os;
}

// сравнивает два числа на равенство
bool operator ==(const big_integer& left, const big_integer& right) {
    if (left._digits.empty()) {
        if (right._digits.empty() || (right._digits.size() == 1 && right._digits[0] == 0)) return true;
        else return false;
    }

    if (right._digits.empty()) {
        if (left._digits.size() == 1 && left._digits[0] == 0) return true;
        else return false;
    }

    if (left._digits.size() != right._digits.size()) return false;
    for (size_t i = 0; i < left._digits.size(); ++i) if (left._digits[i] != right._digits[i]) return false;

    return true;
}

// возвращает копию переданного числа
const big_integer big_integer::operator +() const {
    return big_integer(*this);
}

// проверяет, является ли левый операнд меньше правого
bool operator <(const big_integer& left, const big_integer& right) {
    if (left == right) return false;

    if (left._digits.size() != right._digits.size()) {
        return left._digits.size() < right._digits.size();
    }
    else {
        for (long long i = left._digits.size() - 1; i >= 0; --i) {
            if (left._digits[i] != right._digits[i]) return left._digits[i] < right._digits[i];
        }

        return false;
    }

}

// сравнивает два числа на неравенство
bool operator !=(const big_integer& left, const big_integer& right) {
    return !(left == right);
}

// проверяет, является ли левый операнд меньше либо равен правого
bool operator <=(const big_integer& left, const big_integer& right) {
    return (left < right || left == right);
}

// проверяет, является ли левый операнд больше правого
bool operator >(const big_integer& left, const big_integer& right) {
    return !(left <= right);
}

// проверяет, является ли левый операнд больше либо равен правого
bool operator >=(const big_integer& left, const big_integer& right) {
    return !(left < right);
}

// складывает два числа
const big_integer operator +(big_integer left, const big_integer& right) {
    int carry = 0;
    for (size_t i = 0; i < std::max(left._digits.size(), right._digits.size()) || carry != 0; ++i) {
        if (i == left._digits.size()) left._digits.push_back(0);
        left._digits[i] += carry + (i < right._digits.size() ? right._digits[i] : 0);
        carry = left._digits[i] >= big_integer::BASE;
        if (carry != 0) left._digits[i] -= big_integer::BASE;
    }

    return left;
}

// прибавляет к текущему числу новое
big_integer& big_integer::operator +=(const big_integer& value) {
    return *this = (*this + value);
}

// префиксный инкремент
const big_integer big_integer::operator++() {
    return (*this += 1);
}

// преобразует число к строке
big_integer::operator std::string() const {
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

// преобразует  char к big_integer
big_integer::big_integer(char c) {
    this->_digits.push_back(c);
}

// преобразует  short к big_integer
big_integer::big_integer(short s) {
    this->_digits.push_back(s);
}

// преобразует  int к big_integer
big_integer::big_integer(int i) {
    this->_digits.push_back(i % big_integer::BASE);
    i /= big_integer::BASE;
    if (i != 0) this->_digits.push_back(i);
}


// преобразует  long к big_integer
big_integer::big_integer(long l) {
    this->_digits.push_back(l % big_integer::BASE);
    l /= big_integer::BASE;
    if (l != 0) this->_digits.push_back(l);
}


// преобразует long long к big_integer
big_integer::big_integer(long long l) {
    do {
        this->_digits.push_back(l % big_integer::BASE);
        l /= big_integer::BASE;
    } while (l != 0);
}

// постфиксный инкремент
const big_integer big_integer::operator ++(int) {
    *this += 1;
    return *this - 1;
}

// префиксный декремент
const big_integer big_integer::operator --() {
    return *this -= 1;
}

// постфиксный декремент
const big_integer big_integer::operator --(int) {
    *this -= 1;
    return *this + 1;
}

// вычитает два числа
const big_integer operator -(big_integer left, const big_integer& right) {
    int carry = 0;
    for (size_t i = 0; i < right._digits.size() || carry != 0; ++i) {
        left._digits[i] -= carry + (i < right._digits.size() ? right._digits[i] : 0);
        carry = left._digits[i] < 0;
        if (carry != 0) left._digits[i] += big_integer::BASE;
    }

    left._remove_leading_zeros();
    return left;
}

// вычитает из текущего числа новое
big_integer& big_integer::operator -=(const big_integer& value) {
    return *this = (*this - value);
}

// перемножает два числа
const big_integer operator *(const big_integer& left, const big_integer& right) {
    big_integer result;
    result._digits.resize(left._digits.size() + right._digits.size());
    for (size_t i = 0; i < left._digits.size(); ++i) {
        int carry = 0;
        for (size_t j = 0; j < right._digits.size() || carry != 0; ++j) {
            long long cur = result._digits[i + j] +
                left._digits[i] * 1LL * (j < right._digits.size() ? right._digits[j] : 0) + carry;
            result._digits[i + j] = static_cast<int>(cur % big_integer::BASE);
            carry = static_cast<int>(cur / big_integer::BASE);
        }
    }
    result._remove_leading_zeros();
    return result;
}

// домножает текущее число на указанное
big_integer& big_integer::operator *=(const big_integer& value) {
    return *this = (*this * value);
}

// сдвигает все разряды на 1 вправо (домножает на BASE)
void big_integer::_shift_right() {
    if (this->_digits.size() == 0) {
        this->_digits.push_back(0);
        return;
    }
    this->_digits.push_back(this->_digits[this->_digits.size() - 1]);
    for (size_t i = this->_digits.size() - 2; i > 0; --i) this->_digits[i] = this->_digits[i - 1];
    this->_digits[0] = 0;
}

// делит два числа
const big_integer operator /(const big_integer& left, const big_integer& right) {
    if (right == 0) throw big_integer::divide_by_zero();
    big_integer b = right;
    big_integer result, current;
    result._digits.resize(left._digits.size());
    for (long long i = static_cast<long long>(left._digits.size()) - 1; i >= 0; --i) {
        current._shift_right();
        current._digits[0] = left._digits[i];
        current._remove_leading_zeros();
        int x = 0, l = 0, r = big_integer::BASE;
        while (l <= r) {
            int m = (l + r) / 2;
            big_integer t = b * m;
            if (t <= current) {
                x = m;
                l = m + 1;
            }
            else r = m - 1;
        }

        result._digits[i] = x;
        current = current - b * x;
    }

    result._remove_leading_zeros();
    return result;
}

// делит текущее число на указанное
big_integer& big_integer::operator /=(const big_integer& value) {
    return *this = (*this / value);
}

// возвращает остаток от деления двух чисел
const big_integer operator %(const big_integer& left, const big_integer& right) {
    big_integer result = left - (left / right) * right;
    return result;
}

// присваивает текущему числу остаток от деления на другое число
big_integer& big_integer::operator %=(const big_integer& value) {
    return *this = (*this % value);
}

// проверяет, является ли текущее число нечетным
bool big_integer::odd() const {
    if (this->_digits.size() == 0) return false;
    return this->_digits[0] & 1;
}

// проверяет, является ли текущее число четным
bool big_integer::even() const {
    return !this->odd();
}

// возводит текущее число в указанную степень
const big_integer big_integer::pow(big_integer n) const {
    big_integer a(*this), result(1);
    while (n != 0) {
        if (n.odd()) result *= a;
        a *= a;
        n /= 2;
    }

    return result;
}

//возводит число в степень по модулю
big_integer power_mod(const big_integer a, big_integer power, const big_integer MOD) {
    if (power == 0) return 1;
    if (power % 2 == 1) return (a * power_mod(a, power - 1, MOD)) % MOD;
    big_integer tmp;
    tmp = power_mod(a, power / 2, MOD);
    return tmp * tmp % MOD;
}

//генерация рандомного числа
big_integer random(big_integer a) {
    big_integer res;
    res = 0;
    for (int i = 0; i < 1000; i++) {
        res += rand();
    }
    return res % a;
}
