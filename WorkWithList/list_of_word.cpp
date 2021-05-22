//подключение структур данных и прототипов функций
#include"Header.h"


//проверка вводимого значения 
int getValue(int* i)
{
	while (true) // Цикл продолжается до тех пор, пока пользователь не введет корректное значение
	{
		std::cin >> *i;
		// Проверка на предыдущее извлечение
		if (std::cin.fail()) // если предыдущее извлечение оказалось провальным
		{
			std::cin.clear(); // возвращаем cin в 'обычный' режим работы
			std::cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
			cout << endl << "Некорректный ввод данных." << endl << "Выберите один из пунктов для продолжения работы: ";
		}
		else
		{
			std::cin.ignore(32767, '\n'); // удаляем лишние значения
			return 0;
		}
	}
}
//проверка запроса в меню. Принимает 1 - адрес переменной, 2 - начало диапозана 3 - конец диапазона
void request_verification(int* i, int range_1, int range_2) {
	while (true) {
		//запросить данные у пользователя
		getValue(i);
		if (*i < range_1 || *i > range_2) {
			cout << endl << "Некорректный ввод данных." << endl << "Выберите один из пунктов для продолжения работы: ";
		}
		else {
			break;
		}
	}
}
//функция проверяющая доступ к списку. Принимает указатель на односвязный список слов. Возращает true - если доступ есть, false - если доступа нет
bool list_word_access_check(list_word* list) {
	//проверка на начало работы
	if (list->start == true)
	{
		return true;
	}
	//проверка на начало работы
	if (list->start == false) {
		//печать сообщения
		error_message_at_the_beginning_of_work();
		return false;
	}
}
//функция проверающая список на пустоту. Принимает указатель на односвязный список слов. Возвращает true - если список пуст, false - если в списке есть данные
bool list_word_check_for_empty_list_no_comment(list_word* list) {
	//проверка списка на упстоту
	if (list->link_to_start != NULL) {
		return true;
	}
	else {
		//печать сообщения
		error_message_due_to_empty_list();
		return false;
	}
}
//функция проверяющая ошибки в выделении памяти. Принимает указатель на односвязный список слов. Возвращает true - усли ошибок нет, false - если ошибки есть
bool list_word_check_for_errors_in_memory_allocation(list_word* list) {
	//проверка на ошибку при выделении памяти
	if (list->memory_error == true) {
		//печать сообщения
		memory_allocation_error_message();
		return false;
	}
	else {
		return true;
	}
}
//функция считывающая слово с консоли. Возвращает NULL в случае неудачи, или указатель на строку символов в случае успеха
char* take_word_from_console() {
	//указатель на массив считанного слова
	char* word;
	//количество считанных символов
	int number_of_characters = 0;
	number_of_characters++;
	//выделение памяти под массив
	word = (char*)calloc(number_of_characters, sizeof(char));
	//проверка на ошибку при выделении памяти
	if (word == NULL) {
		return word;
	}
	//считывание символов с консоли
	cout << "Введите слово: " ;
	word[number_of_characters - 1] = getchar();
	//считываем данные с консоли
	while (word[number_of_characters - 1] != '\n') {
		number_of_characters++;
		//создаем копии указателя на массив
		char* new_word = word;
		//добавление памяти в массив
		new_word = (char*)realloc(word, number_of_characters * sizeof(char));
		//проверка на ошибку при выделении памяти
		if (new_word == NULL) {
			free(word);
			word = NULL;
			return word;
		}
		else {
			word = new_word;
		}
		word[number_of_characters - 1] = getchar();
	}
	word[number_of_characters - 1] = '\0';
	return word;
}
//функция удаляющая элемент списка. Принимает указаетль на односвязный спискок
void delete_cell_to_word_list(list_word* list) {
	word_cell* delete_cell = list->work_pointer->next;
	//определяем положение удаляемого элемента
	if (delete_cell->next == NULL) {
		//удаляем последний элемент списка
		list->work_pointer->next = NULL;
	}
	else {
		//удаляем n элемент списка
		list->work_pointer->next = delete_cell->next;
	}
	free(delete_cell->word);
	free(delete_cell);
}
//функция удаляющая элемент списка после указателя. Принимает указатель на односвязный список слов.
void list_word_delete_item(list_word* list) {
	//проверка доступа к списку
	if (list_word_access_check(list)) {
		//проверка списка на пустоту
		if (list_word_check_for_empty_list_no_comment(list)) {
			//проверка на ошибку при выделениеи памяти
			if (list_word_check_for_errors_in_memory_allocation(list)) {
				if (list->work_pointer->next == NULL) {
					//печать сообщения
					message_about_pointers_at_the_end_of_the_list();
				}
				else {
					//удалить элемент
					delete_cell_to_word_list(list);
				}
			}
		}
	}
}
//функция очищающая список слов
void clear_word_list(list_word* list) {
	list->work_pointer = list->link_to_start;
	//удаляем данные из списка и освобождаем выделенную память
	while (list->work_pointer->next != NULL) {
		//удалить элемент
		delete_cell_to_word_list(list);
	}
	free(list->work_pointer->word);
	free(list->work_pointer);
	//проверка на наличие сохраненного элемента
	if ((list->saved_item) != NULL) {
		free(list->saved_item);
	}
	list->link_to_start = NULL;
	list->work_pointer = NULL;
	list->saved_item = NULL;
}
//функция позволяющая рабовать со списком. Принимает указатель на односвязный список слов
void list_word_begin_work(list_word* list) {
	list->start = true;
	list->memory_error = false;
	list->work_pointer = list->link_to_start;
}
//функция проверающая список на пустоту. Принимает указатель на односвязный список слов.
void list_word_check_for_empty_list(list_word* list) {
	//проверка доступа к списку
	if (list_word_access_check(list)) {
		//проверка на ошибку при выделении памяти
		if (list_word_check_for_errors_in_memory_allocation(list)) {
			//проверка списка на пустоту
			if (list->link_to_start == NULL) {
				char massive[] = "Список пуст!\0";
				//печать сообщения
				message_about(massive);
			}
			else {
				char massive[] = "Список не пуст!\0";
				//печать сообщения
				message_about(massive);
			}
		}
	}
}


//функция добавляющая элемент за указателем. Принимает указатель на односвязный список слов.
void list_word_add_item(list_word* list) {
	//проверка доступа к списку
	if (list_word_access_check(list)){
		//проверка на ошибку выделения памяти
		if (list_word_check_for_errors_in_memory_allocation(list)) {
			if (list->link_to_start == NULL) {
				//добавить первый элемент
				word_cell* new_cell = (word_cell*)malloc(sizeof(word_cell));
				//проверка на ошибку в выделении памяти
				if (new_cell == NULL) {
					list->memory_error = true;
				}
				else {
					//считываем данные с консоли
					new_cell->word = take_word_from_console();
					//проверка на ошибку выделения памяти
					if (new_cell->word == NULL) {
						list->memory_error = true;
					}
					else {
						new_cell->next = NULL;
						list->link_to_start = new_cell;
						list->work_pointer = new_cell;
					}
				}
			}
			else if (list->work_pointer->next == NULL) {
				//добавляем элемент в конец списка
				word_cell* new_cell = (word_cell*)malloc(sizeof(word_cell));
				//проверка на ошибку выделения памяти
				if (new_cell == NULL) {
					list->memory_error = true;
				}
				else {
					//считываем данные с консоли
					new_cell->word = take_word_from_console();
					//проверка на ошибку выделения памяти
					if (new_cell->word == NULL) {
						list->memory_error = true;
					}
					else {
						new_cell->next = NULL;
						list->work_pointer->next = new_cell;
					}
				}
			}
			else {
				//добавляем элемент в середину списка
				word_cell* new_cell = (word_cell*)malloc(sizeof(word_cell));
				//проверка на ошибку выделения памяти
				if (new_cell == NULL) {
					list->memory_error = true;
				}
				else {
					//считываем данные с консоли
					new_cell->word = take_word_from_console();
					//проверка на ошибку выделения памяти
					if (new_cell->word == NULL) {
						list->memory_error = true;
					}
					else {
						new_cell->next = list->work_pointer->next;
						list->work_pointer->next = new_cell;
					}
				}
			}
		}
	}
}
//функция устанавливающая рабочий указатель в начало списка. Принимает указатель на односвязный список слов.
void list_word_set_cursor_to_beginning(list_word* list) {
	//проверка доступа к списку
	if (list_word_access_check(list)) {
		//проверка списка на пустоту
		if (list_word_check_for_empty_list_no_comment(list)) {
			//проверка на ошибку при выделениеи памяти
			if (list_word_check_for_errors_in_memory_allocation(list)) {
				list->work_pointer = list->link_to_start;
			}
		}
	}
}
//функция делающая список пустым. Принимает указатель на односвязный список слов.
void list_word_make_the_list_empty(list_word* list) {
	//проверка доступа к списку
	if (list_word_access_check(list)) {
		//проверка списка на пустоту
		if (list_word_check_for_empty_list_no_comment(list)) {
			//проверка на ошибку при выделениеи памяти
			if (list_word_check_for_errors_in_memory_allocation(list)) {
				//очищаем список
				clear_word_list(list);
				char massive[] = "Список пуст!\0";
				//вывод сообщения
				message_about(massive);
			}
		}
	}
}
//функция проверяющая нахождение рабочего указателя. Принимает указатель на односвязный список слов.
void list_word_check_for_working_pointer(list_word* list) {
	//проверка доступа к списку
	if (list_word_access_check(list)) {
		//проверка списка на пустоту
		if (list_word_check_for_empty_list_no_comment(list)) {
			//проверка на ошибку при выделениеи памяти
			if (list_word_check_for_errors_in_memory_allocation(list)) {
				//проверка нахождения рабочего указателя
				if (list->work_pointer->next == NULL) {
					char massive[] = "Рабочий указатель в конце списка!\0";
					//печать сообщения
					message_about(massive);
				}
				else {
					char massive[] = "Рабочий указатель не в конце списка!\0";
					//печать сообщения
					message_about(massive);

				}
			}
		}
	}
}
//функция двигающая указатель вперед. Принимает указатель на односвязный список слов.
void list_word_move_pointer_forward(list_word* list) {
	//проверка доступа к списку
	if (list_word_access_check(list)) {
		//проверка списка на пустоту
		if (list_word_check_for_empty_list_no_comment(list)) {
			//проверка на ошибку при выделениеи памяти
			if (list_word_check_for_errors_in_memory_allocation(list)) {
				//проверка нахожднения рабочего указателя
				if (list->work_pointer->next == NULL) {
					//печать сообщения
					message_about_pointers_at_the_end_of_the_list();
				}
				else {
					list->work_pointer = list->work_pointer->next;
				}
			}
		}
	}
}
//функция показывающая значение элемента за указателем. Принимает указатель на односвязный список слов.
void list_word_show_el_value_after_pointer(list_word* list) {
	//проверка доступа к списку
	if (list_word_access_check(list)) {
		//проверка списка на пустоту
		if (list_word_check_for_empty_list_no_comment(list)) {
			//проверка на ошибку при выделениеи памяти
			if (list_word_check_for_errors_in_memory_allocation(list)) {
				//проверка нахождения рабочего указателя
				if (list->work_pointer->next == NULL) {
					//печать сообщения
					message_about_pointers_at_the_end_of_the_list();
				}
				else {
					cout << "Значение элемента данных: " << list->work_pointer->next->word << endl;
				}
			}
		}
	}
}
//функция взятия элемента списка за указателем.Принимает указатель на односвязный список слов.
void list_word_take_item(list_word* list) {
	//проверка доступа к списку
	if (list_word_access_check(list)) {
		//проверка списка на пустоту
		if (list_word_check_for_empty_list_no_comment(list)) {
			//проверка на ошибку при выделениеи памяти
			if (list_word_check_for_errors_in_memory_allocation(list)) {
				if (list->work_pointer->next == NULL) {
					//печать сообщения
					message_about_pointers_at_the_end_of_the_list();
				}
				else {
					//проверка на пустоту указателя для сохраненного элемента
					if ((list->saved_item) != NULL) {
						free(list->saved_item);
						list->saved_item = NULL;
					}
					char* word = list->work_pointer->next->word;
					int number_letters = 0;
					//подсчитываем кол-во символов
					for (int i = 0; word[i] != '\0'; i++) {
						number_letters++;
					}
					number_letters++;
					//выделяем память 
					char* copy_word = (char*)calloc(number_letters, sizeof(char));
					//проверка на ошибку выделения памяти
					if (copy_word == NULL) {
						list->memory_error = true;
					}
					else {
						//копируем слово
						for (int i = 0; i <= number_letters; i++) {
							copy_word[i] = word[i];
						}
						list->saved_item = copy_word;
						//удаляем элемент
						list_word_delete_item(list);
						char massive[] = "Сохраненный элемент данных:\0";
						//печать сообщения
						message_about(massive);
						cout << list->saved_item << endl;
					}
				}
			}
		}
	}
}
//Печатаем список. Принимает указатель на список слов
void print_list_word(list_word* list) {
	word_cell* pointer = list->link_to_start;
	int number = 0;
	//печатаем список
	while (pointer != NULL) {
		number++;
		cout << number << ". ";
		cout << pointer->word;
		pointer = pointer->next;
		cout << endl;
	}
	cout << endl;
}
//функция печатующая список слов. Принимает указатель на односвязный список слов.
void list_word_print(list_word* list) {
	//проверка доступа к списку
	if (list_word_access_check(list)) {
		//проверка списка на пустоту
		if (list_word_check_for_empty_list_no_comment(list)) {
			//проверка на ошибку при выделениеи памяти
			if (list_word_check_for_errors_in_memory_allocation(list)) {
				word_cell* pointer = list->link_to_start;
				cout << endl;
				char massive[] = "Печатаем список слов...\0";
				//печать сообщения
				message_about(massive);
				int i = 0;
				int number_work_pointer = 0;
				//печатаем список
				while (pointer != NULL) {
					i++;
					cout << i << ". " << pointer->word << endl;
					//ещем номер рабочего указателя
					if (list->work_pointer == pointer) {
						number_work_pointer = i;
					}
					pointer = pointer->next;
				}
				cout << "Рабочий указатель находится на элементе: " << number_work_pointer << ". " << list->work_pointer->word << endl << endl;
			}
		}
	}
}
//функция меняющее значение элемента за указателем. Принимает указатель на односвязный список слов.
void list_word_change_element_value_after_pointer(list_word* list) {
	//проверка доступа к списку
	if (list_word_access_check(list)) {
		//проверка списка на пустоту
		if (list_word_check_for_empty_list_no_comment(list)) {
			//проверка на ошибку при выделениеи памяти
			if (list_word_check_for_errors_in_memory_allocation(list)) {
				//проверка нахождения рабочего указателя
				if (list->work_pointer->next == NULL) {
					//печать сообщения
					message_about_pointers_at_the_end_of_the_list();
				}
				else {
					char massive[] = "Изменить значение элемента за указателем!\0";
					//печать сообщения
					message_about(massive);
					//считываем данные с консоли
					 char* new_value = take_word_from_console();
					 //проверка на ошибку выделения памяти
					 if (new_value == NULL) {
						 list->memory_error = true;
					 }
					 else {
						 list->work_pointer->next->word = new_value;
					 }
				}
			}
		}
	}
}
//функция прекращающая работу со списоком. Принимает указатель на односвязный список слов.
void list_word_finish_work(list_word* list) {
	//проверка на доступ к списку
	if (list->start == true) {
		//проверка на ошибки при выделении памяти
		if (list_word_check_for_errors_in_memory_allocation(list)) {
			char massive[] = "Работа со списком завершена!\0";
			//печать сообщения
			message_about(massive);
			list->start = false;
		}
	}
	else {
		char massive[] = "Работа со списком не начата!\0";
		//печать сообщения
		message_about(massive);
	}
}
//функция печатующая список и выводящее значение рабочего указателя. Принимает указатель на односвязный список
void list_word_print_(list_word* list) {
	//проверка на начало работы
	if (list->start == true) {
		//проверка списка на пустоту
		if (list->link_to_start != NULL) {
			//проверка на ошибку при выделении памяти
			if (list->memory_error != true) {
				//печать списка
				list_word_print(list);
			}
		}
	}
}
//функция проверяющая завершение работы со списком. Принимает указатель на односвязный список. Возвращает true - если работа со списком завершена, false - если работа со списком не зваершена.
bool list_word_back(list_word* list) {
	//проверка на начало работы
	if (list->start == true) {
		char massive[] = "Для возвращения назад выполните операцию 'Закончить работу со списком'";
		//печать сообщения
		message_about(massive);
		return false;
	}
	return true;
}
//Меню односвязного списка слов
void list_word_menu(list_word* list_word) {
	//переменная, которая хранит в себе выбор пользователя
	int user_choice;
	//переменная, которая содежит информацию о желании пользователя выйти
	bool back = false;
	//выводим меню о тех пор, пока пользователь не выберет пункт выйти
	while (!back) {
		//проверка на ошибку при выделении памяти
		if (list_word->memory_error == true) {
			//печать сообщения
			memory_allocation_error_message();
			system("pause");
			break;
		}
		char massive[] = "Вы находитесь в разделе: список текстов -> список предложений -> список слов\0";
		//печать сообщения
		message_about(massive);
		//печать списка
		print_list_word(list_word);
		cout << "Меню" << endl;
		cout << " 1. Начать работу со списком." << endl;
		cout << " 2. Сделать список пустым." << endl;
		cout << " 3. Проверка: список пуст / список не пуст." << endl;
		cout << " 4. Установить рабочий указатель в начало списка." << endl;
		cout << " 5. Проверка: рабочий указатель в конце списка?" << endl;
		cout << " 6. Передвинуть рабочий указатель списка вперед." << endl;
		cout << " 7. Показать значение элемента списка за указателем." << endl;
		cout << " 8. Удалить элемент списка за указателем." << endl;
		cout << " 9. Взять элемент списка за указателем." << endl;
		cout << "10. Изменить значение элемента списка за указателем." << endl;
		cout << "11. Добавить элемент за указателем." << endl;
		cout << "12. Распечатать структуру данных." << endl;
		cout << "13. Закончить работу со списоком." << endl;
		cout << "14. Перейти на уровень выше: список предложений <- список слов." << endl;
		cout << endl << "Выберите один из пунктов для продолжения работы: ";
		//запрос данных у пользователя и их проверка
		request_verification(&user_choice, 1, 14);
		cout << endl;
		switch (user_choice) {
		case 1:
			//нчать работу
			list_word_begin_work(list_word);
			break;
		case 2:
			//сделать список пустым
			list_word_make_the_list_empty(list_word);
			break;
		case 3:
			//проверка списка на пустоту
			list_word_check_for_empty_list(list_word);
			break;
		case 4:
			//печать списка
			list_word_print_(list_word);
			//поставить рабочий указатель в начало
			list_word_set_cursor_to_beginning(list_word);
			//печать списка
			list_word_print_(list_word);
			break;
		case 5:
			//проверить нахожедние рабочего указателя на конец списка
			list_word_check_for_working_pointer(list_word);
			//печать списка
			list_word_print_(list_word);
			break;
		case 6:
			//печать списка
			list_word_print_(list_word);
			//передвинуть указатель вперед
			list_word_move_pointer_forward(list_word);
			//печать списка
			list_word_print_(list_word);
			break;
		case 7:
			//печать списка
			list_word_print_(list_word);
			//показать значение элемента за указателем
			list_word_show_el_value_after_pointer(list_word);
			break;
		case 8:
			//печать списка
			list_word_print_(list_word);
			//удалить элемент за указателем
			list_word_delete_item(list_word);
			//печать списка
			list_word_print_(list_word);
			break;
		case 9:
			//печать списка
			list_word_print_(list_word);
			//взять элемент за указателем
			list_word_take_item(list_word);
			//печать списка
			list_word_print_(list_word);
			break;
		case 10:
			//печать списка
			list_word_print_(list_word);
			//изменить занчение за указателем
			list_word_change_element_value_after_pointer(list_word);
			//печать списка
			list_word_print_(list_word);
			break;
		case 11:
			//печать списка
			list_word_print_(list_word);
			//добавить элемент
			list_word_add_item(list_word);
			//печать списка
			list_word_print_(list_word);
			break;
		case 12:
			//печать списка
			list_word_print(list_word);
			break;
		case 13:
			//закончить работу
			list_word_finish_work(list_word);
			break;
		case 14:
			//выйти
			back = list_word_back(list_word);
			break;
		}
		system("pause");
		system("cls");
	}
}