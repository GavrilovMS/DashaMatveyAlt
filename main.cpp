#include "tests.h"

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

int main() {
	setlocale(0,"");
	bool is_working = true;
	while (is_working) {
		std::cout << "1. Проверить простоту по критерию Люка" << std::endl;
		std::cout << "2. Сгенерировать простые числа в заданном диапазоне (теорема Диемитко)" << std::endl;
		std::cout << "3. Показать числа Мерсена" << std::endl;
		std::cout << "Ввведите номер задачи:" << std::endl;
		int num;
		std::cin >> num;
		std::string str;
		big_integer n, a, b;
		switch (num) {
		case 1:
			system("cls");
			std::cout << "Введите число: " << std::endl;
			str = enter_big_int();
			n = str;
			if (test_Luka(n) == 1) {
				std::cout << "Число простое!" << std::endl;
			}
			else {
				std::cout << "Число возможно составное!" << std::endl;
			}
			break;
		case 2: 
			system("cls");
			std::cout << "Введите небольшое простое число: " << std::endl;
			str = enter_big_int(); 
			n = str;

			while (test_Luka(n) != 1) {
				std::cout << "Число составное. Попробуйте еще раз: " << std::endl;
				str = enter_big_int();
				n = str;
			}
			

			std::cout << "Введите левую границу: " << std::endl;
			str = enter_big_int(); 
			a = str;

			std::cout << "Введите правую границу: " << std::endl;
			str = enter_big_int(); 
			b = str;
			
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
		if (str == "N") is_working = false;
		system("cls");
	}
	

	return 0;


}
