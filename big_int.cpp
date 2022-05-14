#include <vector>
#include <string>
#include <ostream>
#include <iomanip>
#include <sstream>

class big_integer {
    // основание системы счисления (1 000 000 000)
    static const int BASE = 1000000000;

    // внутреннее хранилище числа
    std::vector<int> _digits;


    void _remove_leading_zeros();
    void _shift_right();

public:
    // класс-исключение, бросаемое при делении на ноль
    class divide_by_zero : public std::exception {  };

    big_integer();
    big_integer(std::string);

    big_integer(char);

    big_integer(short);

    big_integer(int);

    big_integer(long);

    big_integer(long long);

    friend std::ostream& operator <<(std::ostream&, const big_integer&);
    operator std::string() const;
    const big_integer operator +() const;

    const big_integer operator ++();
    const big_integer operator ++(int);
    const big_integer operator --();
    const big_integer operator --(int);
    friend bool operator ==(const big_integer&, const big_integer&);
    friend bool operator <(const big_integer&, const big_integer&);
    friend bool operator !=(const big_integer&, const big_integer&);
    friend bool operator <=(const big_integer&, const big_integer&);
    friend bool operator >(const big_integer&, const big_integer&);
    friend bool operator >=(const big_integer&, const big_integer&);
    friend const big_integer operator +(big_integer, const big_integer&);
    big_integer& operator +=(const big_integer&);
    friend const big_integer operator -(big_integer, const big_integer&);
    big_integer& operator -=(const big_integer&);
    friend const big_integer operator *(const big_integer&, const big_integer&);
    big_integer& operator *=(const big_integer&);
    friend const big_integer operator /(const big_integer&, const big_integer&);
    big_integer& operator /=(const big_integer&);
    friend const big_integer operator %(const big_integer&, const big_integer&);
    big_integer& operator %=(const big_integer&);

    bool odd() const;
    bool even() const;
    const big_integer pow(big_integer) const;
};

big_integer random(big_integer a);
big_integer  power_mod(big_integer  a, big_integer  power, big_integer MOD);
