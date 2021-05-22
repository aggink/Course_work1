//подключение структур данных и прототипов функций
#include"Header.h"


void main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	//выделяем память под список текстов
	struct list_text* list = (list_text*)malloc(sizeof(list_text));
	//проверка на ошибку при выделении памяти
	if (list == NULL) {
		cout << "Ошибка в выделении памяти" << endl;
		system("pause");
		exit(0);
	}
	list->link_to_start = NULL;
	list->memory_error = false;
	list->saved_item = NULL;
	list->start = false;
	list->work_pointer = NULL;
	//вызываем меню текстов
	list_text_menu(list);
}
//сделать так, чтоб в конце предлоежния стояли точки, а в середине предложения они не могли использоваться определенные знаки препинания!