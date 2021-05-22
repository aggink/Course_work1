//подключение структур данных и прототипов функций
#include"Header.h"


//инициализация списка слов
void list_word_initialize(list_word* list) {
	list->link_to_start = NULL;
	list->memory_error = false;
	list->saved_item = NULL;
	list->work_pointer = NULL;
	list->start = false;
}


//функция считаывания считывания предложения с консоли. Возвращает указатель на список слов.
list_word* take_sentence_from_console() {
	//переменная указывающая на конец предложения
	bool flag_end_sentence = false;
	bool flag_end_text = false;
	//выделение памяти под список предложений
	list_word* list = (list_word*)malloc(sizeof(list_word));
	//проверка на ошибку при выделении памяти
	if (list == NULL) {
		return list;
	}
	//инициализируем список слов
	list_word_initialize(list);
	//количество считанных символов
	int number_of_characters = 0;
	number_of_characters++;
	//выделение памяти под слово
	char* word = (char*)calloc(number_of_characters, sizeof(char));
	//проверка на ошибку при выделении памяти
	if (word == NULL) {
		return NULL;
	}
	word[number_of_characters - 1] = getchar();
	//быстрый спуск на нидний уровень структуры
	if (word[number_of_characters - 1] == '\n') {
		return list;
	}
	//считываем данные с консоли
	while (true) {
		//считываем данные с консоли
		while (!search_character(word[number_of_characters - 1], &flag_end_sentence, &flag_end_text)) {
			number_of_characters++;
			//выделяем память под слово
			char* new_pointer_word = (char*)realloc(word, number_of_characters * sizeof(char));
			//проверка ошибпри при выделении памяти
			if (new_pointer_word == NULL) {
				list = NULL;
				return list;
			}
			else {
				word = new_pointer_word;
			}
			word[number_of_characters - 1] = getchar();
		}
		if (word[number_of_characters - 1] == '\n') {
			word[number_of_characters - 1] = '\0';
		}
		else {
			//игнорируем пробельные символы
			if (word[number_of_characters - 1] != ' ' && word[number_of_characters - 1] != '	') {
				number_of_characters++;
				//добавляем память
				char* new_pointer_word = (char*)realloc(word, number_of_characters * sizeof(char));
				//проверка на ошибку при выделении памяти
				if (new_pointer_word == NULL) {
					list = NULL;
					return list;
				}
				else {
					word = new_pointer_word;
				}
			}
			word[number_of_characters - 1] = '\0';
		}
		//выделяем память под слово
		word_cell* new_cell = (word_cell*)malloc(sizeof(word_cell));
		//проверка на ошибку при выделении памяти
		if (new_cell == NULL) {
			list = NULL;
			return list;
		}
		//первый элемент списка слов
		if (list->link_to_start == NULL) {
			new_cell->word = word;
			new_cell->next = NULL;
			list->link_to_start = new_cell;
			list->work_pointer = new_cell;
		}
		//если первый элемент списка слов уже существует
		else {
			new_cell->word = word;
			new_cell->next = NULL;
			list->work_pointer->next = new_cell;
			list->work_pointer = new_cell;

		}
		//устанавливаем флаг конца предложения для завершения считывани
		if (flag_end_sentence == true) {
			flag_end_sentence = false;
			break;
		}
		number_of_characters = 0;
		number_of_characters++;
		//выделение памяти под слово
		char* new_word = (char*)malloc(number_of_characters*sizeof(char));
		//проверка на ошибку при выделении памяти
		if (new_word == NULL) {
			cout << "Ошибка при выделении памяти!" << endl;
			system("pause");
			exit(0);
		}
		word = new_word;
		//проверка на ошибку при выделении памяти
		if (word == NULL) {
			list = NULL;
			return list;
		}
		word[number_of_characters - 1] = getchar();
	}
	return list;
}
//функция удаляющая элемент списка после указателем. Принимает указаетль на двухсвязный список предложений
void delete_cell_to_sentence_list_after(list_sentence* list) {
	//создаем указатель на список, который нужно удалить
	sentence_cell* delete_cell = list->work_pointer->next;
	//получаем указатель на список слов, который надо удалить
	list_word* delete_list_word = delete_cell->list_word;
	//удаляем последний элемент списка
	if (delete_cell->next == NULL) {
		//очищаем список
		clear_word_list(delete_list_word);
		list->work_pointer->next = NULL;
	}
	//удаляем n элемент списка
	else {
		//получаем указатель на следующий за удаляемым списком слов список
		sentence_cell* next_sentence = delete_cell->next;
		//удаляем список слов
		clear_word_list(delete_list_word);
		list->work_pointer->next = next_sentence;
		next_sentence->last = list->work_pointer;
	}
	free(delete_list_word);
	free(delete_cell);
}
//функция удаляющая элемент списка до указателя. Принимает указаетль на список предложений
void delete_cell_to_sentence_list_before(list_sentence* list) {
	//создаем указатель на список, который нужно удалить
	sentence_cell* delete_cell = list->work_pointer->last;
	//получаем указатель на список слов, который надо удалить
	list_word* delete_list_word = delete_cell->list_word;
	//удаляем первый элемент списка
	if (delete_cell->last == NULL) {
		//очищаем список
		clear_word_list(delete_list_word);
		list->work_pointer->last = NULL;
		list->link_to_start = list->work_pointer;
	}
	else {
		//удаляем n элемент списка
		//получаем указатель на Предыдущий до удаляемого списка слов списка
		sentence_cell* last_sentence = delete_cell->last;
		last_sentence->next = list->work_pointer;
		list->work_pointer->last = last_sentence;
		//удаляем список слов
		clear_word_list(delete_list_word);
	}
	free(delete_list_word);
	free(delete_cell);
}
//функция очищающая список слов. принимает указатель на список предложений
void clear_sentence_list(list_sentence* list) {
	list->work_pointer = list->link_to_start;
	//проверка на последний элемент списка
	while (list->work_pointer->next != NULL) {
		//удаляем элемент списка после указателя
		delete_cell_to_sentence_list_after(list);
	}
	//получаем указатель на список слов
	list_word* delete_list_word = list->work_pointer->list_word;
	//очищаем список
	clear_word_list(delete_list_word);
	//удаляем сохраненный элемент в списке слов
	if ((list->saved_item) != NULL) {
		list_word* delete_saved_item = list->saved_item;
		//очищем список слов
		clear_word_list(delete_saved_item);
		free(delete_saved_item);
	}
	free(delete_list_word);
	list->link_to_start = NULL;
	list->work_pointer = NULL;
	list->saved_item = NULL;
}
//функция проверяющая доступ к списку. Принимает указатель на двухсвязный список предложений. Возращает true - если доступ есть, false - если доступа нет
bool list_sentence_access_check(list_sentence* list) {
	//проверка на начало работы со списком
	if (list->start == true)
	{
		return true;
	}
	//проверка на начало работы со списком
	if (list->start == false) {
		//печать сообщения
		error_message_at_the_beginning_of_work();
		return false;
	}
}
//функция проверающая список на пустоту. Принимает указатель на двухсвязный список предложений. Возвращает true - если список пуст, false - если в списке есть данные
bool list_sentence_check_for_empty_list_no_comment(list_sentence* list) {
	//проверка списка на пустоту
	if (list->link_to_start != NULL) {
		return true;
	}
	else {
		//печать сообщения
		error_message_due_to_empty_list();
		return false;
	}
}
//функция проверяющая ошибки в выделении памяти. Принимает указатель на двухсвязный список предложений. Возвращает true - усли ошибок нет, false - если ошибки есть
bool list_sentence_check_for_errors_in_memory_allocation(list_sentence* list) {
	if (list->memory_error == true) {
		//печать сообщения
		memory_allocation_error_message();
		return false;
	}
	else {
		return true;
	}
}
//функция позволяющая рабовать со списком. Принимает указатель на двухсвязный список предложений.
void list_sentence_begin_work(list_sentence* list) {
	list->start = true;
	list->memory_error = false;
	list->work_pointer = list->link_to_start;
}
//функция проверающая список на пустоту. Принимает указатель на двухсвязный список предложений.
void list_sentence_check_for_empty_list(list_sentence* list) {
	//проверка на доступ к списку
	if (list_sentence_access_check(list)) {
		//проверка на ошибку при выделении памяти
		if (list_sentence_check_for_errors_in_memory_allocation(list)) {
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
//функция добавляющая элемент за указателем. Принимает указатель на двухсвязный список предложений.
void list_sentence_add_item_next(list_sentence* list) {
	//проверка на доступ к списку
	if (list_sentence_access_check(list)) {
		//проверка на ошибку при выделении памяти
		if (list_sentence_check_for_errors_in_memory_allocation(list)) {
			if (list->link_to_start == NULL) {
				//добавить первый элемент
				sentence_cell* new_cell = (sentence_cell*)malloc(sizeof(sentence_cell));
				//проверка на ошибку в выделении памяти
				if (new_cell == NULL) {
					list->memory_error = true;
				}
				else {
					cout << endl << "Введите предложение: ";
					//считывание символов с консоли
					new_cell->list_word = take_sentence_from_console();
					//проверка на ошибку при выделении памяти
					if (new_cell->list_word == NULL) {
						list->memory_error = true;
					}
					else {
						new_cell->next = NULL;
						new_cell->last = NULL;
						list->link_to_start = new_cell;
						list->work_pointer = new_cell;
					}
				}
			}
			//добавляем элемент в конец списка
			else if (list->work_pointer->next == NULL) {
				//выделяем память
				sentence_cell* new_cell = (sentence_cell*)malloc(sizeof(sentence_cell));
				//проверка на ошибку при выделении памяти
				if (new_cell == NULL) {
					list->memory_error = true;
				}
				else {
					//считывание символов с консоли
					cout << endl << "Введите предложение: ";
					//считываем данные с консоли
					new_cell->list_word = take_sentence_from_console();
					//проверка полученных данных
					if (new_cell->list_word == NULL) {
						list->memory_error = true;
					}
					else {
						new_cell->next = NULL;
						new_cell->last = list->work_pointer;
						list->work_pointer->next = new_cell;
					}
				}
			}
			else {
				//добавляем элемент в середину списка
				sentence_cell* new_cell = (sentence_cell*)malloc(sizeof(sentence_cell));
				//проверка на ошибку при выделении памяти
				if (new_cell == NULL) {
					list->memory_error = true;
				}
				else {
					//считывание символов с консоли
					cout << endl << "Введите предложение: ";
					//считываем данные с консоли
					new_cell->list_word = take_sentence_from_console();
					//проверка на ошибку при выделении памяти
					if (new_cell->list_word == NULL) {
						list->memory_error = true;
					}
					else {
						sentence_cell* cell = list->work_pointer->next;
						list->work_pointer->next = new_cell;
						new_cell->last = list->work_pointer;
						new_cell->next = cell;
						cell->last = new_cell;
					}
				}
			}
		}
	}
}
//функция добавляющая элемент до указателем. Принимает указатель на двухсвязный список предложений.
void list_sentence_add_item_last(list_sentence* list) {
	//проверк на доступ к списку
	if (list_sentence_access_check(list)) {
		//проверка на ошибку при выделении памяти
		if (list_sentence_check_for_errors_in_memory_allocation(list)) {
			if (list->link_to_start == NULL) {
				//добавить первый элемент
				sentence_cell* new_cell = (sentence_cell*)malloc(sizeof(sentence_cell));
				//проверка на ошибку в выделении памяти
				if (new_cell == NULL) {
					list->memory_error = true;
				}
				else {
					//считывание символов с консоли
					cout << endl << "Введите предложение: ";
					//считываем данные с консоли
					new_cell->list_word = take_sentence_from_console();
					//проверка на ошибку при выделении памяти
					if (new_cell->list_word == NULL) {
						list->memory_error = true;
					}
					else {
						new_cell->next = NULL;
						new_cell->last = NULL;
						list->link_to_start = new_cell;
						list->work_pointer = new_cell;
					}
				}
			}
			else if (list->work_pointer->last == NULL) {
				//добавляем элемент в начало списка
				sentence_cell* new_cell = (sentence_cell*)malloc(sizeof(sentence_cell));
				//проверка на ошибку при выделении памяти
				if (new_cell == NULL) {
					list->memory_error = true;
				}
				else {
					//считывание символов с консоли
					cout << endl << "Введите предложение: ";
					new_cell->list_word = take_sentence_from_console();
					//проверка на ошибку при выделении памяти
					if (new_cell->list_word == NULL) {
						list->memory_error = true;
					}
					else {
						new_cell->last = NULL;
						new_cell->next = list->work_pointer;
						list->work_pointer->last = new_cell;
						list->link_to_start = new_cell;
					}
				}
			}
			else {
				//добавляем элемент в середину списка
				sentence_cell* new_cell = (sentence_cell*)malloc(sizeof(sentence_cell));
				//проверка на ошибку при выделении памяти
				if (new_cell == NULL) {
					list->memory_error = true;
				}
				else {
					//считывание символов с консоли
					cout << endl << "Введите предложение: ";
					new_cell->list_word = take_sentence_from_console();
					//проверка на ошибку при выделении памяти
					if (new_cell->list_word == NULL) {
						list->memory_error = true;
					}
					else {
						sentence_cell* cell = list->work_pointer->last;
						cell->next = new_cell;
						new_cell->last = cell;
						new_cell->next = list->work_pointer;
						list->work_pointer->last = new_cell;

					}
				}
			}
		}
	}
}
//функция устанавливающая рабочий указатель в начало списка. Принимает указатель на двухсвязный список предложений.
void list_sentence_set_cursor_to_beginning(list_sentence* list) {
	//проверка доступа к списку
	if (list_sentence_access_check(list)) {
		//проверка списка на пустоту
		if (list_sentence_check_for_empty_list_no_comment(list)) {
			//проверка на ошибку при выделении памяти
			if (list_sentence_check_for_errors_in_memory_allocation(list)) {
				list->work_pointer = list->link_to_start;
			}
		}
	}
}
//функция возвращающая указатель на конец списка. Принимает указатель на двухсвязный список предложений.
sentence_cell* list_sentence_go_to_bottom(list_sentence* list) {
	sentence_cell* pointer = list->link_to_start;
	//идем до конца списка
	while (pointer->next != NULL) {
		pointer = pointer->next;
	}
	return pointer;
}
//функция устанавливающая рабочий указатель в конец списка. Принимает указатель на двухсвязный список предложений.
void list_sentence_set_cursor_to_the_end(list_sentence* list) {
	//проверка доступа к списку
	if (list_sentence_access_check(list)) {
		//проверка списка на пустоту
		if (list_sentence_check_for_empty_list_no_comment(list)) {
			//проверка на ошибку при выделении памяти
			if (list_sentence_check_for_errors_in_memory_allocation(list)) {
				//спикукаемся на уровень ниже
				list->work_pointer = list_sentence_go_to_bottom(list);
			}
		}
	}
}
//функция удаляющая элемент списка после указателя. Принимает указатель на двухсвязный список предложений.
void list_sentence_delete_item_after(list_sentence* list) {
	//проверка доступа к списку
	if (list_sentence_access_check(list)) {
		//проверка списка на пустоту
		if (list_sentence_check_for_empty_list_no_comment(list)) {
			//проверка на ошибку при выделении памяти
			if (list_sentence_check_for_errors_in_memory_allocation(list)) {
				if (list->work_pointer->next == NULL) {
					//печать сообщения
					message_about_pointers_at_the_end_of_the_list();
				}
				else {
					//удаляем элемент после указателя
					delete_cell_to_sentence_list_after(list);
				}
			}
		}
	}
}
//функция удаляющая элемент списка до указателя. Принимает указатель на двухсвязный список предложений.
void list_sentence_delete_item_before(list_sentence* list) {
	//проверка доступа к списку
	if (list_sentence_access_check(list)) {
		//проверка списка на пустоту
		if (list_sentence_check_for_empty_list_no_comment(list)) {
			//проверка на ошибку при выделении памяти
			if (list_sentence_check_for_errors_in_memory_allocation(list)) {
				if (list->work_pointer->last == NULL) {
					//печать сообщения
					message_about_pointers_in_the_beginning_of_the_list();
				}
				else {
					//удаляем элемент до указателя
					delete_cell_to_sentence_list_before(list);
				}
			}
		}
	}
}
//функция делающая список пустым. Принимает указатель на двухсвязный список предложений.
void list_sentence_make_the_list_empty(list_sentence* list) {
	//проверка доступа к списку
	if (list_sentence_access_check(list)) {
		//проверка списка на пустоту
		if (list_sentence_check_for_empty_list_no_comment(list)) {
			//проверка на ошибку при выделении памяти
			if (list_sentence_check_for_errors_in_memory_allocation(list)) {
				//очищаем список
				clear_sentence_list(list);
				char massive[] = "Список пуст!\0";
				//печать сообщения
				message_about(massive);
			}
		}
	}
}
//функция проверяющая нахождение рабочего указателя в конце списка. Принимает указатель на двухсвязный список предложений.
void list_sentence_check_for_working_pointer_to_end(list_sentence* list) {
	//проверка доступа к списку
	if (list_sentence_access_check(list)) {
		//проверка списка на пустоту
		if (list_sentence_check_for_empty_list_no_comment(list)) {
			//проверка на ошибку при выделении памяти
			if (list_sentence_check_for_errors_in_memory_allocation(list)) {
				//определяем нахождение рабочего указателя
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
//функция проверяющая нахождение рабочего указателя в начале списка. Принимает указатель на двухсвязный список предложений.
void list_sentence_check_for_working_pointer_to_beginning(list_sentence* list) {
	//проверка доступа к спискку
	if (list_sentence_access_check(list)) {
		//проверка списка на пустоту
		if (list_sentence_check_for_empty_list_no_comment(list)) {
			//проверка на ошибку при выделении памяти
			if (list_sentence_check_for_errors_in_memory_allocation(list)) {
				//определяем нахождение рабочего указателя
				if (list->work_pointer->last == NULL) {
					char massive[] = "Рабочий указатель в начале списка!\0";
					//печать сообщения
					message_about(massive);
				}
				else {
					char massive[] = "Рабочий указатель не в начале списка!\0";
					//печать сообщения
					message_about(massive);
				}
			}
		}
	}
}
//функция двигающая указатель вперед. Принимает указатель на двухсвязный список предложений.
void list_sentence_move_pointer_forward(list_sentence* list) {
	//проверка на доступ к списку
	if (list_sentence_access_check(list)) {
		//проверка списка на пустоту
		if (list_sentence_check_for_empty_list_no_comment(list)) {
			//проверка на ошибку при выделении памяти
			if (list_sentence_check_for_errors_in_memory_allocation(list)) {
				//проверка на нахождение рабочего указателя в начале списка
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
//функция двигающая указатель назад. Принимает указатель на двухсвязный список предложений.
void list_sentence_move_pointer_back(list_sentence* list) {
	//проверка доступа к списку
	if (list_sentence_access_check(list)) {
		//проверка списка на пустоту
		if (list_sentence_check_for_empty_list_no_comment(list)) {
			//проверка на ошибку при выделении памяти
			if (list_sentence_check_for_errors_in_memory_allocation(list)) {
				//проверка на нахождение рабочего указателя в конце списка
				if (list->work_pointer->last == NULL) {
					//печать сообщения
					message_about_pointers_in_the_beginning_of_the_list();
				}
				else {
					list->work_pointer = list->work_pointer->last;
				}
			}
		}
	}
}
//функция печатующая одно предложение(список слов). Принмает указатель на односвязный список слов.
void print_sentence(list_word* list) {
	//создаем рабочий указатель для этого списка
	word_cell* work_pointer_list_word = list->link_to_start;
	//печатаем предложение
	while (work_pointer_list_word != NULL) {
		//создаем указатель на слово
		char* word = work_pointer_list_word->word;
		cout << word << " ";
		work_pointer_list_word = work_pointer_list_word->next;
	}
	cout << endl;
}
//функция показывающая значение элемента за указателем. Принимает указатель на двухсвязный список предложений.
void list_sentence_show_el_value_after_pointer(list_sentence* list) {
	//проверка на лроступ к списку
	if (list_sentence_access_check(list)) {
		//проверка списка на пустоту
		if (list_sentence_check_for_empty_list_no_comment(list)) {
			//проверка на ошибку при выделении памяти
			if (list_sentence_check_for_errors_in_memory_allocation(list)) {
				if (list->work_pointer->next == NULL) {
					//печать сообщения
					message_about_pointers_at_the_end_of_the_list();
				}
				else {
					cout << endl;
					//получаем указатель на список, который надо распечатать
					list_word* list_word = list->work_pointer->next->list_word;
					//печать списка
					print_sentence(list_word);
				}
			}
		}
	}
}
//функция показывающая значение элемента до указателем. Принимает указатель на двухсвязный список предложений.
void list_sentence_show_el_value_before_pointer(list_sentence* list) {
	//проверка на лроступ к списку
	if (list_sentence_access_check(list)) {
		//проверка списка на пустоту
		if (list_sentence_check_for_empty_list_no_comment(list)) {
			//проверка на ошибку при выделении памяти
			if (list_sentence_check_for_errors_in_memory_allocation(list)) {
				if (list->work_pointer->last == NULL) {
					//печать сообщения
					message_about_pointers_in_the_beginning_of_the_list();
				}
				else {
					cout << endl;
					//получаем указатель на список, который надо распечатать
					list_word* list_word = list->work_pointer->last->list_word;
					//создаем рабочий указатель для этого списка
					word_cell* work_pointer_list_word = list_word->link_to_start;
					//печатаем список
					while (work_pointer_list_word != NULL) {
						//создаем указатель на слово
						char* word = work_pointer_list_word->word;
						cout << word << " ";
						work_pointer_list_word = work_pointer_list_word->next;
					}
					cout << endl;
				}
			}
		}
	}
}
//функция печати сохраненного элемента. Принимает указатель на двухсвязный список предложений
void print_saved_item(list_sentence* list) {
	//печатаем изъятый элемент 
	cout << endl;
	char massive[] = "Сохраненный элемент данных:\0";
	//печать сообщения
	message_about(massive);
	list_word* saved_list_word = list->saved_item;
	//указатель на первый элемент сохраненного списка
	word_cell* work_pointer_saved_list_word = saved_list_word->link_to_start;
	//печатаем предложение
	while (work_pointer_saved_list_word != NULL) {
		//создаем указатель на слово
		char* word = work_pointer_saved_list_word->word;
		cout << word << " ";
		work_pointer_saved_list_word = work_pointer_saved_list_word->next;
	}
	cout << endl;
}
//функция сохранения предложения (сохранение списка слов). Принимает указатель на односвязный список слов
list_word* save_item_pointer(list_word* list) {
	//создаем указатель на список, куда сохраним изъятый элемент
	list_word* saved_list_word = (list_word*)malloc(sizeof(list_word));
	if (saved_list_word == NULL) {
		return NULL;
	}
	else {
		//присвоение начальных значений списку слов
		list_word_initialize(saved_list_word);
		//создаем рабочий указатель для сохраненного списка
		word_cell* work_pointer_saved_list_word = NULL;
		//создаем рабочий указатель для списка, который будем копировать
		word_cell* work_pointer_save_item = list->link_to_start;
		//копируем предложение
		while (work_pointer_save_item != NULL) {
			char* word = work_pointer_save_item->word;
			int number_letters = 0;
			for (int i = 0; word[i] != '\0'; i++) {
				number_letters++;
			}
			number_letters++;
			//выделяем память
			char* copy_word = (char*)calloc(number_letters, sizeof(char));
			//проверка на ошибку при выделении памяти
			if (copy_word == NULL) {
				return NULL;
			}
			else {
				//копируем слово
				for (int i = 0; i <= number_letters; i++) {
					copy_word[i] = word[i];
				}
				//выделение памяти под ячейку списка
				word_cell* copy_word_cell = (word_cell*)malloc(sizeof(word_cell));
				//проверка на ошибку при выделении памяти
				if (copy_word_cell == NULL) {
					return NULL;
				}
				else {
					//добавляем первый элемент
					if (work_pointer_saved_list_word == NULL) {
						saved_list_word->link_to_start = copy_word_cell;
						saved_list_word->work_pointer = copy_word_cell;
						work_pointer_saved_list_word = copy_word_cell;
						copy_word_cell->word = copy_word;
						copy_word_cell->next = NULL;
					}
					else {
						//добаляем n элемент
						work_pointer_saved_list_word->next = copy_word_cell;
						work_pointer_saved_list_word = work_pointer_saved_list_word->next;
						copy_word_cell->word = copy_word;
						copy_word_cell->next = NULL;
					}
				}
				work_pointer_save_item = work_pointer_save_item->next;
			}
		}
		return saved_list_word;
	}
}
//функция взятия элемента списка за указателем. Принимает указатель на двухсвязный список предложений.
void list_sentence_take_item_after(list_sentence* list) {
	//проверка на лроступ к списку
	if (list_sentence_access_check(list)) {
		//проверка списка на пустоту
		if (list_sentence_check_for_empty_list_no_comment(list)) {
			//проверка на ошибку при выделении памяти
			if (list_sentence_check_for_errors_in_memory_allocation(list)) {
				if (list->work_pointer->next == NULL) {
					//печать сообщения
					message_about_pointers_at_the_end_of_the_list();
				}
				else {
					//проверка на ранее сохраненные элементы
					if ((list->saved_item) != NULL) {
						list_word* delete_saved_item = list->saved_item;
						//удаляем список
						clear_word_list(delete_saved_item);
						free(delete_saved_item);
						list->saved_item = NULL;
					}
					//создаем указатель на список, который нам надо сохранить
					list_word* save_item = list->work_pointer->next->list_word;
					//сохраняем элемент 
					list->saved_item = save_item_pointer(save_item);
					//проверка на ошибку выделения памяти
					if (list->saved_item == NULL) {
						list->memory_error = true;
					}
					else {
						//удаляем элемент после указателя
						list_sentence_delete_item_after(list);
						//печать сохраненного элемента
						print_saved_item(list);
					}
				}
			}
		}
	}
}
//функция взятия элемента списка до указателем. Принимает указатель на двухсвязный список предложений.
void list_sentence_take_item_before(list_sentence* list) {
	//проверка на лроступ к списку
	if (list_sentence_access_check(list)) {
		//проверка списка на пустоту
		if (list_sentence_check_for_empty_list_no_comment(list)) {
			//проверка на ошибку при выделении памяти
			if (list_sentence_check_for_errors_in_memory_allocation(list)) {
				//проверка нахождения рабочего указателя
				if (list->work_pointer->last == NULL) {
					//печать сообщения
					message_about_pointers_in_the_beginning_of_the_list();
				}
				else {
					//проверка на  ранее сохраненнве элементы
					if ((list->saved_item) != NULL) {
						list_word* delete_saved_item = list->saved_item;
						//очищаем список
						clear_word_list(delete_saved_item);
						free(delete_saved_item);
						list->saved_item = NULL;
					}
					//создаем указатель на список, который нам надо сохранить
					list_word* save_item = list->work_pointer->last->list_word;
					//сохраняем элемент
					list->saved_item = save_item_pointer(save_item);
					//проверка на ошибку выделения памяти
					if (list->saved_item == NULL) {
						list->memory_error = true;
					}
					else {
						//удаляем элемент после указателя
						list_sentence_delete_item_before(list);
						//печать сохраненного элемента
						print_saved_item(list);
					}
				}
			}
		}
	}
}
//печать списка предложений. Принимает указатель на список предложений
void print_list_sentence(list_sentence* list) {
	//указатель на начало списка предложений
	sentence_cell* pointer_sentence = list->link_to_start;
	//указатель на начало списка слов (список предложений->список слов)
	list_word* pointer_list_word = NULL;
	//указатель на слов (список предложений->список слов->слово)
	word_cell* pointer_word = NULL;
	int number = 0;
	//печатаем список
	while (pointer_sentence != NULL) {
		number++;
		cout << number << ". ";
		//указатель на начало списка слов (список предложений->список слов)
		pointer_list_word = pointer_sentence->list_word;
		//указатель на слов (список предложений->список слов->слово)
		pointer_word = pointer_list_word->link_to_start;
		//печатаем список
		while (pointer_word != NULL) {
			cout << pointer_word->word << " ";
			pointer_word = pointer_word->next;
		}
		pointer_sentence = pointer_sentence->next;
		cout << endl;
	}
	cout << endl;
}
//функция печатующая список предложений. Принимает указатель на двухсвязный список предложений.
void list_sentence_print(list_sentence* list) {
	//проверка на лроступ к списку
	if (list_sentence_access_check(list)) {
		//проверка списка на пустоту
		if (list_sentence_check_for_empty_list_no_comment(list)) {
			//проверка на ошибку при выделении памяти
			if (list_sentence_check_for_errors_in_memory_allocation(list)) {
				//указатель на начало списка предложений
				sentence_cell* pointer_sentence = list->link_to_start;
				//указатель на начало списка слов (список предложений->список слов)
				list_word* pointer_list_word = NULL;
				//указатель на слов (список предложений->список слов->слово)
				word_cell* pointer_word = NULL;
				int number_of_sentence = 0;
				int number_of_sentence_work_pointer = 0;
				cout << endl;
				char massive[] = "Печать списка предложений в прямом порядке...\0";
				//печать сообщения
				message_about(massive);
				//печатаем списко в прямом порядке
				while (pointer_sentence != NULL) {
					number_of_sentence++;
					//запоминаем номер предложения на который указывает рабочий указателья
					if (pointer_sentence == list->work_pointer) {
						number_of_sentence_work_pointer = number_of_sentence;
					}
					cout << number_of_sentence << ". ";
					//указатель на начало списка слов (список предложений->список слов)
					pointer_list_word = pointer_sentence->list_word;
					//указатель на слов (список предложений->список слов->слово)
					pointer_word = pointer_list_word->link_to_start;
					//печатаем список
					while (pointer_word != NULL) {
						cout << pointer_word->word << " ";
						pointer_word = pointer_word->next;
					}
					pointer_sentence = pointer_sentence->next;
					cout << endl;
				}
				cout << "Печать списка предложений завершена..." << endl;
				//печатаем значение рабочего указателя
				cout << endl << "Рабочий указатель находится на элементе: " << endl;
				cout << number_of_sentence_work_pointer << ". ";
				pointer_sentence = list->work_pointer;
				//указатель на начало списка слов (список предложений->список слов)
				pointer_list_word = pointer_sentence->list_word;
				//указатель на слов (список предложений->список слов->слово)
				pointer_word = pointer_list_word->link_to_start;
				//печатаем список
				while (pointer_word != NULL) {
					cout << pointer_word->word << " ";
					pointer_word = pointer_word->next;
				}
				cout << endl << endl;
				//печать в обратном порядке
				pointer_sentence = list_sentence_go_to_bottom(list);
				//указатель на начало списка слов (список предложений->список слов)
				pointer_list_word = NULL;
				//указатель на слов (список предложений->список слов->слово)
				pointer_word = NULL;
				cout << endl;
				char massive_2[] = "Печать списка предложений в обратном порядке...\0";
				message_about(massive_2);
				//печатаем список в обратном порядке
				while (pointer_sentence != NULL) {
					//запомнинаем номер предложения на который указывает рабочий указатель
					if (pointer_sentence == list->work_pointer) {
						number_of_sentence_work_pointer = number_of_sentence;
					}
					cout << number_of_sentence << ". ";
					//указатель на начало списка слов (список предложений->список слов)
					pointer_list_word = pointer_sentence->list_word;
					//указатель на слов (список предложений->список слов->слово)
					pointer_word = pointer_list_word->link_to_start;
					//печатаем список
					while (pointer_word != NULL) {
						cout << pointer_word->word << " ";
						pointer_word = pointer_word->next;
					}
					pointer_sentence = pointer_sentence->last;
					number_of_sentence--;
					cout << endl;
				}
				cout << "Печать списка предложений завершена..." << endl;
				//печатаем значение рабочего указателя
				cout << endl << "Рабочий указатель находится на элементе: " << endl;
				cout << number_of_sentence_work_pointer << ". ";
				pointer_sentence = list->work_pointer;
				//указатель на начало списка слов (список предложений->список слов)
				pointer_list_word = pointer_sentence->list_word;
				//указатель на слов (список предложений->список слов->слово)
				pointer_word = pointer_list_word->link_to_start;
				//печатаем список
				while (pointer_word != NULL) {
					cout << pointer_word->word << " ";
					pointer_word = pointer_word->next;
				}
				cout << endl << endl;
			}
		}
	}
}
//функция меняющее значение элемента за указателем. Принимает указатель на двухсвязный список предложений.
void list_sentence_change_element_value_after_pointer(list_sentence* list) {
	//проверка на лроступ к списку
	if (list_sentence_access_check(list)) {
		//проверка списка на пустоту
		if (list_sentence_check_for_empty_list_no_comment(list)) {
			//проверка на ошибку при выделении памяти
			if (list_sentence_check_for_errors_in_memory_allocation(list)) {
				//проверка нахождения указателя
				if (list->work_pointer->next == NULL) {
					//печать сообщения
					message_about_pointers_at_the_end_of_the_list();
				}
				else {
					/*
					char massive[] = "Изменить значение элемента за указателем!\0";
					message_about(massive);
					//считывание символов с консоли
					cout << endl << "Введите предложение: ";
					list_word* new_value = take_sentence_from_console();
					if (new_value == NULL) {
						list->memory_error = true;
					}
					else {
						list->work_pointer->next->list_word = new_value;
					}
					*/
					//спускаемся на уровень ниже
					go_to_the_lower_level_next(list, list->work_pointer);
				}
			}
		}
	}
}
//функция меняющее значение элемента до указателем. Принимает указатель на двухсвязный список предложений.
void list_sentence_change_element_value_before_pointer(list_sentence* list) {
	//проверка на лроступ к списку
	if (list_sentence_access_check(list)) {
		//проверка списка на пустоту
		if (list_sentence_check_for_empty_list_no_comment(list)) {
			//проверка на ошибку при выделении памяти
			if (list_sentence_check_for_errors_in_memory_allocation(list)) {
				//проверка нахождения указателя
				if (list->work_pointer->last == NULL) {
					//печать сообщения
					message_about_pointers_in_the_beginning_of_the_list();
				}
				else {
					char massive[] = "Изменить значение элемента до указателя!\0";
					//печать сообщения
					message_about(massive);
					/*
					//считывание символов с консоли
					cout << endl << "Введите предложение: ";
					list_word* new_value = take_sentence_from_console();
					if (new_value == NULL) {
						list->memory_error = true;
					}
					else {
						list->work_pointer->last->list_word = new_value;
					}
					*/
					//спускаемся на уровень ниже
					go_to_the_lower_level_last(list, list->work_pointer);
				}
			}
		}
	}
}
//функция прекращающая работу со списоком. Принимает указатель на двухсвязный список предложений.
void list_sentence_finish_work(list_sentence* list) {
	//проверка на начало работы
	if (list->start == true) {
		//проверка на ошибку при выделении памяти
		if (list_sentence_check_for_errors_in_memory_allocation(list)) {
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
//функция печатующая список и выводящее значение рабочего указателя. Принимает указатель на односвязный список предложений
void list_sentence_print_(list_sentence* list) {
	//проверка на доступ к списку
	if (list->start == true) {
		//проверка списка на пустоту
		if (list->link_to_start != NULL) {
			//проверка на ошибку при выделении памяти
			if (list->memory_error != true) {
				//печать списка
				list_sentence_print(list);
			}
		}
	}
}
//функция проверяющая завершение работы со списком. Принимает указатель на односвязный список. Возвращает true - если работа со списком завершена, false - если работа со списком не зваершена.
bool list_sentence_back(list_sentence* list) {
	//проверка на начало работы
	if (list->start == true) {
		char massive[] = "Для возвращения назад выполните операцию 'Закончить работу со списком'\0";
		//печать сообщения
		message_about(massive);
		return false;
	}
	return true;
}
//спуститься на уровень ниже. Принимент указатель на список предложений и рабочий указатель
void go_to_the_lower_level(list_sentence* list, sentence_cell* check) {
	//проверка на лроступ к списку
	if (list_sentence_access_check(list)) {
		//проверка списка на пустоту
		if (list_sentence_check_for_empty_list_no_comment(list)) {
			//проверка на ошибку при выделении памяти
			if (list_sentence_check_for_errors_in_memory_allocation(list)) {
				sentence_cell* cell_work_pointer = NULL;
				//проверка указателя на пустоту
				if (check != NULL) {
					cell_work_pointer = check;
				}
				else {
					cell_work_pointer = list->work_pointer;
				}
				list_word* word_list = cell_work_pointer->list_word;
				//вызов меню списка слов
				list_word_menu(word_list);
				//проверяем вернувшийся указатель списка слов
				if (cell_work_pointer->last == NULL && cell_work_pointer->next == NULL && word_list->link_to_start == NULL) {
					free(cell_work_pointer);
					list->link_to_start = NULL;
					list->work_pointer = NULL;
				}
				else {
					if (word_list->link_to_start == NULL) {
						//если в начале
						if (cell_work_pointer->last == NULL) {
							sentence_cell* next_cell = cell_work_pointer->next;
							list->link_to_start = next_cell;
							next_cell->last = NULL;
							list->work_pointer = list->link_to_start;
						}
						else {
							//если в конце списка
							sentence_cell* cursor = list->link_to_start;
							if (cell_work_pointer->next == NULL) {
								while (cursor->next != cell_work_pointer) {
									cursor = cursor->next;
								}
								cursor->next = NULL;
								list->work_pointer = list->link_to_start;
							}
							else {
								//на n элементе списка
								while (cursor->next != cell_work_pointer) {
									cursor = cursor->next;
								}
								sentence_cell* next_cursor = cell_work_pointer->next;
								cursor->next = next_cursor;
								next_cursor->last = cursor;
								list->work_pointer = next_cursor;
							}
						}
						free(word_list);
						free(cell_work_pointer);
					}
				}
			}
		}
	}
}
//спуститься на уровень ниже. Принимает указатель на список предложений и рабочий указатель
void go_to_the_lower_level_last(list_sentence* list, sentence_cell* check) {
	//проверка на лроступ к списку
	if (list_sentence_access_check(list)) {
		//проверка списка на пустоту
		if (list_sentence_check_for_empty_list_no_comment(list)) {
			//проверка на ошибку при выделении памяти
			if (list_sentence_check_for_errors_in_memory_allocation(list)) {
				sentence_cell* cell_work_pointer = NULL;
				//проверяем список на пустоту
				if (check != NULL) {
					cell_work_pointer = check->last;
				}
				else {
					cell_work_pointer = list->work_pointer;
				}
				list_word* word_list = cell_work_pointer->list_word;
				//вызываем менб списка слов
				list_word_menu(word_list);
				//проверяем вернувшийся указатель списка слов
				if (cell_work_pointer->last == NULL && cell_work_pointer->next == NULL && word_list->link_to_start == NULL) {
					free(cell_work_pointer);
					list->link_to_start = NULL;
					list->work_pointer = NULL;
				}
				else {
					if (word_list->link_to_start == NULL) {
						//если в начале
						if (cell_work_pointer->last == NULL) {
							sentence_cell* next_cell = cell_work_pointer->next;
							list->link_to_start = next_cell;
							next_cell->last = NULL;
							list->work_pointer = list->link_to_start;
						}
						else {
							//если в конце списка
							sentence_cell* cursor = list->link_to_start;
							if (cell_work_pointer->next == NULL) {
								while (cursor->next != cell_work_pointer) {
									cursor = cursor->next;
								}
								cursor->next = NULL;
								list->work_pointer = list->link_to_start;
							}
							else {
								//на n элементе списка
								while (cursor->next != cell_work_pointer) {
									cursor = cursor->next;
								}
								sentence_cell* next_cursor = cell_work_pointer->next;
								cursor->next = next_cursor;
								next_cursor->last = cursor;
								list->work_pointer = next_cursor;
							}
						}
						free(word_list);
						free(cell_work_pointer);
					}
				}
			}
		}
	}
}
//спуститься на уровень ниже. Принимает указатель на список предложений и рабочий указатель
void go_to_the_lower_level_next(list_sentence* list, sentence_cell* check) {
	//проверка на лроступ к списку
	if (list_sentence_access_check(list)) {
		//проверка списка на пустоту
		if (list_sentence_check_for_empty_list_no_comment(list)) {
			//проверка на ошибку при выделении памяти
			if (list_sentence_check_for_errors_in_memory_allocation(list)) {
				sentence_cell* cell_work_pointer = NULL;
				//проверяем список на пустоту
				if (check != NULL) {
					cell_work_pointer = check->next;
				}
				else {
					cell_work_pointer = list->work_pointer;
				}
				list_word* word_list = cell_work_pointer->list_word;
				//открываем меню списка предложений
				list_word_menu(word_list);
				//проверяем вернувшийся указатель списка слов
				if (cell_work_pointer->last == NULL && cell_work_pointer->next == NULL && word_list->link_to_start == NULL) {
					free(cell_work_pointer);
					list->link_to_start = NULL;
					list->work_pointer = NULL;
				}
				else {
					if (word_list->link_to_start == NULL) {
						//если в начале
						if (cell_work_pointer->last == NULL) {
							sentence_cell* next_cell = cell_work_pointer->next;
							list->link_to_start = next_cell;
							next_cell->last = NULL;
							list->work_pointer = list->link_to_start;
						}
						else {
							//если в конце списка
							sentence_cell* cursor = list->link_to_start;
							if (cell_work_pointer->next == NULL) {
								while (cursor->next != cell_work_pointer) {
									cursor = cursor->next;
								}
								cursor->next = NULL;
								list->work_pointer = list->link_to_start;
							}
							else {
								//на n элементе списка
								while (cursor->next != cell_work_pointer) {
									cursor = cursor->next;
								}
								sentence_cell* next_cursor = cell_work_pointer->next;
								cursor->next = next_cursor;
								next_cursor->last = cursor;
								list->work_pointer = next_cursor;
							}
						}
						free(word_list);
						free(cell_work_pointer);
					}
				}
			}
		}
	}
}
//проверка на пустоту списка нижнего уровня. Принимает указатель на список предложений
sentence_cell* check_for_emptiness(list_sentence* list) {
	//проверка на лроступ к списку
	if (list_sentence_access_check(list)) {
		//проверка списка на пустоту
		if (list_sentence_check_for_empty_list_no_comment(list)) {
			//проверка на ошибку при выделении памяти
			if (list_sentence_check_for_errors_in_memory_allocation(list)) {
				sentence_cell* work_pointer = list->link_to_start;
				//проверяем список на пустоту
				while (work_pointer != NULL) {
					if (work_pointer->list_word->link_to_start == NULL) {
						return work_pointer;
					}
					work_pointer = work_pointer->next;
				}
			}
		}
	}
	return NULL;
}
//Меню односвязного списка слов
void list_sentence_menu(list_sentence* list_sentence) {
	//переменная, которая хранит в себе выбор пользователя
	int user_choice;
	//переменная, которая содежит информацию о желании пользователя выйти
	bool back = false;
	//выводим меню о тех пор, пока пользователь не выберет пункт выйти
	while (!back) {
		//проверка на ошибку при выделении памяти
		if (list_sentence->memory_error == true) {
			//печать сообшщения
			memory_allocation_error_message();
			system("pause");
			break;
		}
		char massive[] = "Вы находитесь в разделе: список текстов -> список предложений\0";
		//печать сообщения
		message_about(massive);
		//печать списка
		print_list_sentence(list_sentence);
		cout << "Меню" << endl;
		cout << " 1. Начать работу со списком." << endl;
		cout << " 2. Сделать список пустым." << endl;
		cout << " 3. Проверка: список пуст / список не пуст." << endl;
		cout << " 4. Установить рабочий указатель в начало списка." << endl;
		cout << " 5. Установить рабочий указатель в конец списка." << endl;
		cout << " 6. Проверка: рабочий указатель в начале списка?" << endl;
		cout << " 7. Проверка: рабочий указатель в конце списка?" << endl;
		cout << " 8. Передвинуть рабочий указатель списка вперед." << endl;
		cout << " 9. Передвинуть рабочий указатель списка назад." << endl;
		cout << "10. Показать значение элемента списка до указателя." << endl;
		cout << "11. Показать значение элемента списка за указателем." << endl;
		cout << "12. Удалить элемент списка до указателя." << endl;
		cout << "13. Удалить элемент списка за указателем." << endl;
		cout << "14. Взять элемент списка до указателя." << endl;
		cout << "15. Взять элемент списка за указателем." << endl;
		cout << "16. Изменить значение элемента списка до указателя." << endl;
		cout << "17. Изменить значение элемента списка за указателем." << endl;
		cout << "18. Добавить элемент до указателя." << endl;
		cout << "19. Добавить элемент за указателем." << endl;
		cout << "20. Распечатать структуру данных." << endl;
		cout << "21. Закончить работу со списоком." << endl;
		cout << "22. Перейти на уровень ниже (по рабочему указателю): список предложений -> список слов" << endl;
		cout << "23. Перейти на уровень выше: список текстов <- список предложений." << endl;
		cout << endl << "Выберите один из пунктов для продолжения работы: ";
		request_verification(&user_choice, 1, 23);
		cout << endl;
		sentence_cell* check = NULL;
		switch (user_choice) {
		case 1:
			//Начать работу со списком.
			list_sentence_begin_work(list_sentence);
			break;
		case 2:
			// Сделать список пустым.
			list_sentence_make_the_list_empty(list_sentence);
			break;
		case 3:
			//Проверка: список пуст / список не пуст.
			list_sentence_check_for_empty_list(list_sentence);
			break;
		case 4:
			//Установить рабочий указатель в начало списка.
			list_sentence_set_cursor_to_beginning(list_sentence);
			//печать списка
			list_sentence_print_(list_sentence);
			break;
		case 5:
			//Установить рабочий указатель в конец списка.
			list_sentence_set_cursor_to_the_end(list_sentence);
			//печать списка
			list_sentence_print_(list_sentence);
			break;
		case 6:
			//Проверка: рабочий указатель в начале списка?
			list_sentence_check_for_working_pointer_to_beginning(list_sentence);
			//печать списка
			list_sentence_print_(list_sentence);
			break;
		case 7:
			//Проверка: рабочий указатель в конце списка?
			list_sentence_check_for_working_pointer_to_end(list_sentence);
			//печать списка
			list_sentence_print_(list_sentence);
			break;
		case 8:
			//печать списка
			list_sentence_print_(list_sentence);
			//Передвинуть рабочий указатель списка вперед.
			list_sentence_move_pointer_forward(list_sentence);
			//печать списка
			list_sentence_print_(list_sentence);
			break;
		case 9:
			//печать списка
			list_sentence_print_(list_sentence);
			//Передвинуть рабочий указатель списка назад.
			list_sentence_move_pointer_back(list_sentence);
			//печать списка
			list_sentence_print_(list_sentence);
			break;
		case 10:
			//печать списка
			list_sentence_print_(list_sentence);
			//Показать значение элемента списка до указателя.
			list_sentence_show_el_value_before_pointer(list_sentence);
			break;
		case 11:
			//печать списка
			list_sentence_print_(list_sentence);
			//Показать значение элемента списка за указателем.
			list_sentence_show_el_value_after_pointer(list_sentence);
			break;
		case 12:
			//печать списка
			list_sentence_print_(list_sentence);
			//Удалить элемент списка до указателя.
			list_sentence_delete_item_before(list_sentence);
			//печать списка
			list_sentence_print_(list_sentence);
			break;
		case 13:
			//печать списка
			list_sentence_print_(list_sentence);
			//Удалить элемент списка за указателем.
			list_sentence_delete_item_after(list_sentence);
			//печать списка
			list_sentence_print_(list_sentence);
			break;
		case 14:
			//печать списка
			list_sentence_print_(list_sentence);
			//Взять элемент списка до указателя.
			list_sentence_take_item_before(list_sentence);
			//печать списка
			list_sentence_print_(list_sentence);
			break;
		case 15:
			//печать списка
			list_sentence_print_(list_sentence);
			// Взять элемент списка за указателем. 
			list_sentence_take_item_after(list_sentence);
			//печать списка
			list_sentence_print_(list_sentence);
			break;
		case 16:
			//печать списка
			list_sentence_print_(list_sentence);
			//Изменить значение элемента списка до указателя.
			list_sentence_change_element_value_before_pointer(list_sentence);
			//печать списка
			list_sentence_print_(list_sentence);
			break;
		case 17:
			//печать списка
			list_sentence_print_(list_sentence);
			//Изменить значение элемента списка за указателем.
			list_sentence_change_element_value_after_pointer(list_sentence);
			//печать списка
			list_sentence_print_(list_sentence);
			break;
		case 18:
			//печать списка
			list_sentence_print_(list_sentence);
			//Добавить элемент до указателя.
			list_sentence_add_item_last(list_sentence);
			//выбор способа ввода
			check = check_for_emptiness(list_sentence);
			if (check != NULL) {
				//спуститься на уровень ниже
				go_to_the_lower_level(list_sentence, check);
			}
			else {
				//печать списка
				list_sentence_print_(list_sentence);
			}
			break;
		case 19:
			//печать списка
			list_sentence_print_(list_sentence);
			//Добавить элемент за указателем.
			list_sentence_add_item_next(list_sentence);
			//выбор способа ввода
			check = check_for_emptiness(list_sentence);
			if (check != NULL) {
				//спуститься на уровень ниже
				go_to_the_lower_level(list_sentence, check);
				//печать списка
				list_sentence_print_(list_sentence);
			}
			else {
				//печать списка
				list_sentence_print_(list_sentence);
			}
			break;
		case 20:
			//Распечатать структуру данных.
			list_sentence_print(list_sentence);
			break;
		case 21:
			//Закончить работу со списоком.
			list_sentence_finish_work(list_sentence);
			break;
		case 22:
			//спуститься на уровень ниже
			go_to_the_lower_level(list_sentence, NULL);
			//печать списка
			list_sentence_print_(list_sentence);
			break;
		case 23:
			//Назад.
			back = list_sentence_back(list_sentence);
			break;
		}
		system("pause");
		system("cls");
	}
}