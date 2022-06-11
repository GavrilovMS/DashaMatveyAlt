#include "tests.h"
#include <windows.h>

std::string enter_big_int() {
    std::string str;
    std::cin >> str;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] < 48 || str[i] > 57) {
            std::cout << "Число введено некорректно. Попробуйте еще раз:" << std::endl;
            str = enter_big_int();
            break;
        }
    }
    return str;
}

int enter_int() {
    std::string str;
    std::cin >> str;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] < 48 || str[i] > 57) {
            std::cout << "Число введено некорректно. Попробуйте еще раз:" << std::endl;
            str = enter_int();
            break;
        }
    }

    return atoi(str.c_str());
}

int main() {


    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    
    bool is_working = true;
    while (is_working) {
        std::cout << "1. Проверить простоту числа по критерию Люка" << std::endl;
        std::cout << "2. Сгенерировать простые числа в заданном диапазоне (теорема Диемитко)" << std::endl;
        std::cout << "3. Сгенерировать числа Мерсенна" << std::endl;
        std::cout << "Ввведите номер задачи:" << std::endl;
        int num;
        num = enter_int();
        while (num != 1 && num != 2 && num!=3){
            std::cout << "Некорректный ввод. Попробуйте еще раз." << std::endl;
            num = enter_int();
        }
        big_integer edge("99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999");


        std::string str;
        big_integer n, a, b;
        switch (num) {
        case 1:
            for (;;){
            system("cls");
            std::cout << "Введите число: " << std::endl;
            str = enter_big_int();
            n = str;
            if (n == 0 || n == 1){
                 std::cout << "Ваше число ни простое, ни составное." << std::endl;
            } else
            if (n == 2 || n ==3){
            std::cout << "Число простое!" << std::endl;
            } else {
                char d = test_Luka(n);
                switch(d){
                case 0: std::cout << "Число составное!" << std::endl; break;
                case 1: std::cout << "Число простое!" << std::endl; break;
                case 2: std::cout << "Число возможно составное!" << std::endl; break;
                }

            }

            std::cout << "Еще одно число? (Y - Да, N - Нет)" << std::endl;
            std::cin >> str;
            while (str != "N" && str != "Y"){
                std::cout << "Некорректный ввод. Попробуйте еще раз: " << std::endl;
                std::cin >> str;
            }
            if (str == "N") break;
            }
            break;
        case 2:

            system("cls");
            std::cout << "Введите небольшое простое число: " << std::endl;
            str = enter_big_int();
            n = str;




            while (test_Luka(n) != 1 && n != 2 && n != 3) {
                std::cout << "Некорректный ввод. Попробуйте еще раз: " << std::endl;
                str = enter_big_int();
                n = str;
            }

            std::cout << "Введите левую границу: " << std::endl;
            str = enter_big_int();
            a = str;

            while (a > edge) {
                std::cout << "Число слишком большое. Попробуйте еще раз:" << std::endl;
                str = enter_big_int();
                a = str;
            }

            std::cout << "Введите правую границу: " << std::endl;
            str = enter_big_int();
            b = str;

            while (b > edge) {
                std::cout << "Число слишком большое. Попробуйте еще раз:" << std::endl;
                str = enter_big_int();
                b = str;
            }


            system("cls");
            std::cout << "Нажмите любую кнопку, чтобы закончить." << std::endl;
            T_Diemitko(n, a, b);

            break;
        case 3:
            system("cls");
            for (a = 2; a < 150; a++)
            {
            T_Luka_Lemera(a);
            }
              break;
            }
        std::cout << "Еще что-нибудь? (Y - Да, N - Нет)" << std::endl;
        std::cin >> str;
        while (str != "N" && str != "Y"){
            std::cout << "Некорректный ввод. Попробуйте еще раз: " << std::endl;
            std::cin >> str;
        }
        if (str == "N") is_working = false;
        system("cls");
    }


    return 0;


}
