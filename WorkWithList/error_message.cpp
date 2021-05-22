//подключение структур данных и прототипов функций
#include"Header.h"


//сообщение об ошибке доступа к списку
void error_message_at_the_beginning_of_work() {
	SetConsoleOutputCP(866);
	putchar(201);
	int max_number = strlen("Выполните операцию 'Начать работу со списком'!");
	int min_number = strlen("Данная операция недоступна!");
	//вывод верхний границы
	for (int i = 0; i < max_number; i++)
	{
		putchar(205);
	}
	putchar(187);
	cout << endl;
	putchar(186);
	SetConsoleOutputCP(1251);
	cout << "Данная операция недоступна!";
	//выводим пробельный символ 
	for (int i = 0; i < max_number - min_number; i++) {
		cout << " ";
	}
	SetConsoleOutputCP(866);
	putchar(186);
	cout << endl;
	putchar(186);
	SetConsoleOutputCP(1251);
	cout << "Выполните операцию 'Начать работу со списком'!";
	SetConsoleOutputCP(866);
	putchar(186);
	cout << endl;
	putchar(200);
	//вывод нижний границы
	for (int i = 0; i < max_number; i++)
	{
		putchar(205);
	}
	putchar(188);
	cout << endl << endl;
	SetConsoleOutputCP(1251);
}
//сообщение об ошибке вследствии пустого списка
void error_message_due_to_empty_list() {
	SetConsoleOutputCP(866);
	putchar(201);
	int max_number = strlen("Данная операция недоступна!");
	int min_number = strlen("Список пуст!");
	//вывод верхней границы
	for (int i = 0; i < max_number; i++)
	{
		putchar(205);
	}
	putchar(187);
	cout << endl;
	putchar(186);
	SetConsoleOutputCP(1251);
	cout << "Данная операция недоступна!";
	SetConsoleOutputCP(866);
	putchar(186);
	cout << endl;
	putchar(186);
	SetConsoleOutputCP(1251);
	cout << "Список пуст!";
	//печать пробельного символа
	for (int i = 0; i < max_number - min_number; i++) {
		cout << " ";
	}
	SetConsoleOutputCP(866);
	putchar(186);
	cout << endl;
	putchar(200);
	//вывод нижний границы
	for (int i = 0; i < max_number; i++)
	{
		putchar(205);
	}
	putchar(188);
	cout << endl << endl;
	SetConsoleOutputCP(1251);
}
//сообщение об ошибке выделения памяти
void memory_allocation_error_message() {
	SetConsoleOutputCP(866);
	putchar(201);
	int max_number = strlen("Завершение работы программы");
	int min_number = strlen("Ошибка в выделении памяти!");
	//вывод верхней границы
	for (int i = 0; i < max_number; i++)
	{
		putchar(205);
	}
	putchar(187);
	cout << endl;
	putchar(186);
	SetConsoleOutputCP(1251);
	cout << "Ошибка в выделении памяти!";
	//печать спробельного символа
	for (int i = 0; i < max_number - min_number; i++) {
		cout << " ";
	}
	SetConsoleOutputCP(866);
	putchar(186);
	cout << endl;
	putchar(186);
	SetConsoleOutputCP(1251);
	cout << "Завершение работы программы";
	SetConsoleOutputCP(866);
	putchar(186);
	cout << endl;
	putchar(200);
	//вывод нижний границы
	for (int i = 0; i < max_number; i++)
	{
		putchar(205);
	}
	putchar(188);
	cout << endl << endl;
	SetConsoleOutputCP(1251);
}
//сообщение о нахождении рабочего указателя в конце списка
void message_about_pointers_at_the_end_of_the_list() {
	SetConsoleOutputCP(866);
	putchar(201);
	int max_number = strlen("Рабочий указатель в конце списка!");
	int min_number = strlen("Данная операция недоступна!");
	//вывод верхний границы
	for (int i = 0; i < max_number; i++)
	{
		putchar(205);
	}
	putchar(187);
	cout << endl;
	putchar(186);
	SetConsoleOutputCP(1251);
	cout << "Данная операция недоступна!";
	//печать пробельного символа
	for (int i = 0; i < max_number - min_number; i++) {
		cout << " ";
	}
	SetConsoleOutputCP(866);
	putchar(186);
	cout << endl;
	putchar(186);
	SetConsoleOutputCP(1251);
	cout << "Рабочий указатель в конце списка!";
	SetConsoleOutputCP(866);
	putchar(186);
	cout << endl;
	putchar(200);
	//вывод нижний границы
	for (int i = 0; i < max_number; i++)
	{
		putchar(205);
	}
	putchar(188);
	cout << endl << endl;
	SetConsoleOutputCP(1251);
}
//сообщение о нахождении рабочего указателя в начале списка
void message_about_pointers_in_the_beginning_of_the_list() {
	SetConsoleOutputCP(866);
	putchar(201);
	int max_number = strlen("Рабочий указатель в начале списка!");
	int min_number = strlen("Данная операция недоступна!");
	//вывод верхней границы
	for (int i = 0; i < max_number; i++)
	{
		putchar(205);
	}
	putchar(187);
	cout << endl;
	putchar(186);
	SetConsoleOutputCP(1251);
	cout << "Данная операция недоступна!";
	//печать пробельного символа
	for (int i = 0; i < max_number - min_number; i++) {
		cout << " ";
	}
	SetConsoleOutputCP(866);
	putchar(186);
	cout << endl;
	putchar(186);
	SetConsoleOutputCP(1251);
	cout << "Рабочий указатель в начале списка!";
	SetConsoleOutputCP(866);
	putchar(186);
	cout << endl;
	putchar(200);
	//вывод нижний границы 
	for (int i = 0; i < max_number; i++)
	{
		putchar(205);
	}
	putchar(188);
	cout << endl << endl;
	SetConsoleOutputCP(1251);
}
//выводит сообщение на экран. Принимает массив типа char
void message_about(char massive[]) {
	SetConsoleOutputCP(866);
	putchar(201);
	int max_number = strlen(massive);
	//вывод верхней границы
	for (int i = 0; i < max_number; i++)
	{
		putchar(205);
	}
	putchar(187);
	cout << endl;
	putchar(186);
	SetConsoleOutputCP(1251);
	cout << massive;
	SetConsoleOutputCP(866);
	putchar(186);
	cout << endl;
	putchar(200);
	//вывод нижний границы
	for (int i = 0; i < max_number; i++)
	{
		putchar(205);
	}
	putchar(188);
	cout << endl << endl;
	SetConsoleOutputCP(1251);
}