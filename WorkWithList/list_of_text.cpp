//подключение структур данных и прототипов функций
#include"Header.h"


//функция проверяющая доступ к списку. Принимает указатель на односвязный список текстов. Возращает true - если доступ есть, false - если доступа нет
bool list_text_access_check(list_text* list) {
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
//функция проверающая список на пустоту. Принимает указатель на односвязный список текстов. Возвращает true - если список пуст, false - если в списке есть данные
bool list_text_check_for_empty_list_no_comment(list_text* list) {
	//проверка на пустоту списка
	if (list->link_to_start != NULL) {
		return true;
	}
	else {
		//печать сообщения 
		error_message_due_to_empty_list();
		return false;
	}
}
//функция проверяющая ошибки в выделении памяти. Принимает указатель на односвязный список текстов. Возвращает true - усли ошибок нет, false - если ошибки есть
bool list_text_check_for_errors_in_memory_allocation(list_text* list) {
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
//инициализация списка предложений. Принимает указатель на список предложений
void list_sentence_initialize(list_sentence* list) {
	list->link_to_start = NULL;
	list->memory_error = false;
	list->saved_item = NULL;
	list->work_pointer = NULL;
	list->start = false;
}

//функция считывающая текст с консоли. Возвращает NULL в случае неудачи, или указатель на строку символов в случае успеха
list_sentence* take_text_from_console() {
	cout << "Введите текст:" << endl;
	bool flag_end = false;
	bool flag_end_sentence = false;
	bool begin_n = true;
	//свыделяем память под список предложений
	list_sentence* sentence_list = (list_sentence*)malloc(sizeof(list_sentence));
	//проверка на ошибку при выделении памяти
	if (sentence_list == NULL) {
		return NULL;
	}
	//даем начальные значения списку предложений
	list_sentence_initialize(sentence_list);
	//проверка на завершение считывание данных с консоли
	while (!flag_end) {
		//создание списка слов
		list_word* word_list = (list_word*)malloc(sizeof(list_word));
		//проверка на ошибку при выделении памяти
		if (word_list == NULL) {
			return NULL;
		}
		//даем начальные значение списку слов
		list_word_initialize(word_list);
		//считываем данные с консоли и распределяем их по созданным структурам
		while (!flag_end_sentence) {
			int number = 0;
			number++;
			///выделяем память под слово
			char* word = (char*)calloc(number, sizeof(char));
			//проверка на ошибку при выделении памяти
			if (word == NULL) {
				sentence_list = NULL;
				return sentence_list;
			}
			word[number - 1] = getchar();
			//пропускаем все пробелы
			if (word[number - 1] == ' ' || word[number - 1] == '	') {
				word[number - 1] = getchar();
			}
			//устанавливаем флаг, если встретили переход на новую строку
			if (word[number - 1] == '\n') {
				flag_end = true;
				begin_n = true;
				break;
			}
			else {
				begin_n = false;
			}
			//считываем слово до пробела
			while (word[number - 1] != ' ' && word[number - 1] !='	' && word[number - 1] != '\n') {
				if (word[number - 1] == '!' || word[number - 1] == '.' || word[number - 1] == ';' || word[number - 1] == '?') {
					flag_end_sentence = true;
				}
				number++;
				//ыделяем память под новое слово
				char* new_word = (char*)realloc(word, number * sizeof(char));
				//проверка на ошибку при выделении памяти
				if (new_word == NULL) {
					return NULL;
				}
				word = new_word;
				word[number - 1] = getchar();
			}
			if (word[number - 1] == '\n') {
				flag_end = true;
			}
			//добавление символа \0
			word[number - 1] = '\0';
			//создание ячейки односвязного списка слов
			word_cell* new_word_cell = (word_cell*)malloc(sizeof(word_cell));
			//проверка на ошибку при выделении памяти
			if (new_word_cell == NULL) {
				return NULL;
			}
			//добавление 1-ого элемента списка слов
			if (word_list->link_to_start == NULL) {
				new_word_cell->word = word;
				new_word_cell->next = NULL;
				word_list->link_to_start = new_word_cell;
				word_list->work_pointer = new_word_cell;
			}
			else {
				//добавление n-го элемента списка слов
				new_word_cell->word = word;
				new_word_cell->next = NULL;
				word_list->work_pointer->next = new_word_cell;
				word_list->work_pointer = new_word_cell;
			}
		}
		//добавление в списко предложения
		if (begin_n == true) {
			break;
		}
		//выделяем память под список предложений
		sentence_cell* new_sentence_cell = (sentence_cell*)malloc(sizeof(sentence_cell));
		//проверка на ошибку при выделении памяти
		if (new_sentence_cell == NULL) {
			return NULL;
		}
		new_sentence_cell->list_word = word_list;
		//для 1-го элемента
		if (sentence_list->link_to_start == NULL) {
			new_sentence_cell->last = NULL;
			new_sentence_cell->next = NULL;
			sentence_list->link_to_start = new_sentence_cell;
			sentence_list->work_pointer = new_sentence_cell;
		}
		//для n-го элемента
		else {
			new_sentence_cell->last = sentence_list->work_pointer;
			sentence_list->work_pointer->next = new_sentence_cell;
			new_sentence_cell->next = NULL;
			sentence_list->work_pointer = new_sentence_cell;
		}
		flag_end_sentence = false;
	}
	return sentence_list;
}


//функция позволяющая рабовать со списком. Принимает указатель на односвязный список текстов
void list_text_begin_work(list_text* list) {
	list->start = true;
	list->memory_error = false;
	list->work_pointer = list->link_to_start;
}
//функция проверающая список на пустоту. Принимает указатель на односвязный список текстов.
void list_text_check_for_empty_list(list_text* list) {
	//проверка доступа к списку
	if (list_text_access_check(list)) {
		//проверка на ошибки при выделение памяти
		if (list_text_check_for_errors_in_memory_allocation(list)) {
			//если список пуст, выводим сообщение
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
//функция добавляющая элемент за указателем. Принимает указатель на односвязный список текстов.
void list_text_add_item(list_text* list) {
	//проверка доступа к списку
	if (list_text_access_check(list)) {
		//проверка на ошибки при выделении памяти
		if (list_text_check_for_errors_in_memory_allocation(list)) {
			if (list->link_to_start == NULL) {
				//добавить первый элемент
				text_cell* new_cell = (text_cell*)malloc(sizeof(text_cell));
				//проверка на ошибку в выделении памяти
				if (new_cell == NULL) {
					list->memory_error = true;
				}
				else {
					//ссчитываем данные с консоли
					new_cell->list_sentence = take_text_from_console();
					//распределяем данные по ячейкам списка
					if (new_cell->list_sentence == NULL) {
						list->memory_error = true;
					}
					else {
						new_cell->next = NULL;
						list->link_to_start = new_cell;
						list->work_pointer = new_cell;
					}
				}
			}
			//добавляем элемент в конец списка
			else if (list->work_pointer->next == NULL) {
				//выделяем память под ячейку текста
				text_cell* new_cell = (text_cell*)malloc(sizeof(text_cell));
				//проверка на ошибку при выделении памяти
				if (new_cell == NULL) {
					list->memory_error = true;
				}
				else {
					//считываем данные с консоли
					new_cell->list_sentence = take_text_from_console();
					//распределяем данные по ячейкам списка
					if (new_cell->list_sentence == NULL) {
						list->memory_error = true;
					}
					else {
						new_cell->next = NULL;
						list->work_pointer->next = new_cell;
					}
				}
			}
			//добавляем элемент в середину списка
			else {
				//выделяем память под ячейку текста
				text_cell* new_cell = (text_cell*)malloc(sizeof(text_cell));
				//проверка на ошибку при выделении памяти
				if (new_cell == NULL) {
					list->memory_error = true;
				}
				else {
					//считываем данные с консоли
					new_cell->list_sentence= take_text_from_console();
					if (new_cell->list_sentence == NULL) {
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
//функция удаляющая элемент списка. Принимает указаетль на односвязный список
void delete_cell_to_text_list(list_text* list) {
	text_cell* delete_cell = list->work_pointer->next;
	//удаляем последний элемент списка
	if (delete_cell->next == NULL) {
		list->work_pointer->next = NULL;
	}
	//удаляем n элемент списка
	else {
		list->work_pointer->next = delete_cell->next;
	}
	//очищаем список предложений
	clear_sentence_list(delete_cell->list_sentence);
	free(delete_cell->list_sentence);
	free(delete_cell);
}
//функция удаляющая элемент списка после указателя. Принимает указатель на односвязный список текстов.
void list_text_delete_item(list_text* list) {
	//проверка доступа к списку
	if (list_text_access_check(list)) {
		//проверка списка на пустоту
		if (list_text_check_for_empty_list_no_comment(list)) {
			//проверка на ошибки при выделении памяти
			if (list_text_check_for_errors_in_memory_allocation(list)) {
				if (list->work_pointer->next == NULL) {
					//печать сообщения
					message_about_pointers_at_the_end_of_the_list();
				}
				else {
					//удаляем ячейку списка
					delete_cell_to_text_list(list);
				}
			}
		}
	}
}
//функция очищающая список текстов. принимает указатель на односвязный список текстов
void clear_text_list(list_text* list) {
	list->work_pointer = list->link_to_start;
	while (list->work_pointer->next != NULL) {
		//удаляем ячейку списка текстов
		delete_cell_to_text_list(list);
	}
	//получаем указатель на список слов
	list_sentence* delete_list_sentence = list->work_pointer->list_sentence;
	//удаляем список предложений
	clear_sentence_list(delete_list_sentence);
	//удаляем сохраненный элемент в списке слов
	if ((list->saved_item) != NULL) {
		list_sentence* delete_saved_item = list->saved_item;
		clear_sentence_list(delete_saved_item);
		free(delete_saved_item);
	}
	free(delete_list_sentence);
	list->link_to_start = NULL;
	list->work_pointer = NULL;
	list->saved_item = NULL;
}
//функция устанавливающая рабочий указатель в начало списка. Принимает указатель на односвязный список текстов.
void list_text_set_cursor_to_beginning(list_text* list) {
	//проверка доступа к списку
	if (list_text_access_check(list)) {
		//проверка на пустоту списка
		if (list_text_check_for_empty_list_no_comment(list)) {
			//проверка на ошибки при выделении памяти
			if (list_text_check_for_errors_in_memory_allocation(list)) {
				list->work_pointer = list->link_to_start;
			}
		}
	}
}
//функция делающая список пустым. Принимает указатель на односвязный список текстов.
void list_text_make_the_list_empty(list_text* list) {
	//проверка доступа к списку
	if (list_text_access_check(list)) {
		//проверка на пустоту списка
		if (list_text_check_for_empty_list_no_comment(list)) {
			//проверка на ошибки при выделении памяти
			if (list_text_check_for_errors_in_memory_allocation(list)) {
				//очищаем список
				clear_text_list(list);
				char massive[] = "Список пуст!\0";
				//печать сообщения
				message_about(massive);
			}
		}
	}
}
//функция проверяющая нахождение рабочего указателя. Принимает указатель на односвязный список слов.
void list_text_check_for_working_pointer(list_text* list) {
	//проверка доступа к списку
	if (list_text_access_check(list)) {
		//проверка на пустоту списка
		if (list_text_check_for_empty_list_no_comment(list)) {
			//проверка на ошибки при выделении памяти
			if (list_text_check_for_errors_in_memory_allocation(list)) {
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
//функция двигающая указатель вперед. Принимает указатель на односвязный список текстов.
void list_text_move_pointer_forward(list_text* list) {
	if (list_text_access_check(list)) {
		//проверка доступа к списку
		if (list_text_check_for_empty_list_no_comment(list)) {
			//проверка на пустоту списка
			if (list_text_check_for_errors_in_memory_allocation(list)) {
				//проверка нахождения рабочего укащателя
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
//функция показывающая значение элемента за указателем. Принимает указатель на односвязный список текстов.
void list_text_show_el_value_after_pointer(list_text* list) {
	//проверка доступа к списку
	if (list_text_access_check(list)) {
		//проверка на пустоту списка
		if (list_text_check_for_empty_list_no_comment(list)) {
			//проверка на ошибки при выделении памяти
			if (list_text_check_for_errors_in_memory_allocation(list)) {
				//проверка нахождения рабочего указателя
				if (list->work_pointer->next == NULL) {
					//печать сообщения
					message_about_pointers_at_the_end_of_the_list();
				}
				else {
					char massive[] = "Значение элемента данных за указателем:\0";
					//печать сообщения
					message_about(massive);
					text_cell* text_work_pointer = list->work_pointer->next;
					sentence_cell* sentence_work_pointer = text_work_pointer->list_sentence->link_to_start;
					//Выводим список на экран
					while (sentence_work_pointer != NULL) {
						word_cell* word_work_pointer = sentence_work_pointer->list_word->link_to_start;
						//печать слова
						while (word_work_pointer != NULL) {
							char* word = word_work_pointer->word;
							cout << word << " ";
							word_work_pointer = word_work_pointer->next;
						}
						sentence_work_pointer = sentence_work_pointer->next;
					}
					cout << endl;
				}
			}
		}
	}
}
//функция сохраняющая взятый элемент. Принимает указатель на односвязный список текстов. Возвращает указатель скопированного списка предложений
list_sentence* save_item_pointer(list_sentence* list) {
	//создаем указатель для копированного списка
	list_sentence* copy_list_sentence = (list_sentence*)malloc(sizeof(list_sentence));
	//присваиваем начальные значения списку
	list_sentence_initialize(copy_list_sentence);
	//получаем рабочий указатель у списка, который надо скопировать
	sentence_cell* work_pointer = list->link_to_start;
	//проверка на ошибку при выделении памяти
	if (copy_list_sentence == NULL) {
		return NULL;
	}
	//сохранение взятого элемента
	while (work_pointer!= NULL) {
		//копируем список слов
		list_word* copy_list_word = save_item_pointer(work_pointer->list_word);
		//создаем ячейку списка предложений
		sentence_cell* new_sentence_cell = (sentence_cell*)malloc(sizeof(sentence_cell));
		//проверка на ошибку при выделение памяти
		if (new_sentence_cell == NULL) {
			return NULL;
		}
		//для первого элемента
		if (copy_list_sentence->link_to_start == NULL) {
			new_sentence_cell->list_word = copy_list_word;
			new_sentence_cell->last = NULL;
			new_sentence_cell->next = NULL;
			copy_list_sentence->link_to_start = new_sentence_cell;
			copy_list_sentence->work_pointer = new_sentence_cell;
		}
		//для n элемента
		else {
			new_sentence_cell->list_word = copy_list_word;
			new_sentence_cell->last = copy_list_sentence->work_pointer;
			new_sentence_cell->next = NULL;
			copy_list_sentence->work_pointer->next = new_sentence_cell;
			copy_list_sentence->work_pointer = new_sentence_cell;
		}
		work_pointer = work_pointer->next;
	}
	return copy_list_sentence;
}
//печать сохраненного элемента. Принимает указатель на список текстов
void print_saved_item(list_text* list) {
	char massive[] = "Сохраненный элемент данных: ";
	//печать сообщения
	message_about(massive);
	list_sentence* saves_item = list->saved_item;
	sentence_cell* sentence_work_pointer = saves_item->link_to_start;
	//выводим список на экран
	while (sentence_work_pointer != NULL) {
		word_cell* word_work_pointer = sentence_work_pointer->list_word->link_to_start;
		//печать слова
		while (word_work_pointer != NULL) {
			char* word = word_work_pointer->word;
			cout << word << " ";
			word_work_pointer = word_work_pointer->next;
		}
		sentence_work_pointer = sentence_work_pointer->next;
	}
	cout << endl;
}
//функция взятия элемента списка за указателем. Принимает указатель на односвязный список текстов.
void list_text_take_item(list_text* list) {
	//проверка на доступ к списку
	if (list_text_access_check(list)) {
		//проверка на пустоту списка
		if (list_text_check_for_empty_list_no_comment(list)) {
			//проверка на ошибку при выделении памяти
			if (list_text_check_for_errors_in_memory_allocation(list)) {
				if (list->work_pointer->next == NULL) {
					//печать сообщения
					message_about_pointers_at_the_end_of_the_list();
				}
				else {
					//проверка на наличие уже сохраненного списка, если присутствует, то удалаем его
					if ((list->saved_item) != NULL) {
						list_sentence* delete_saved_item = list->saved_item;
						//удаляем список предложений
						clear_sentence_list(delete_saved_item);
						free(delete_saved_item);
						list->saved_item = NULL;
					}
					//создаем указатель на список, который нам надо сохранить
					list_sentence* save_item = list->work_pointer->next->list_sentence;
					//сохраняем список
					list->saved_item = save_item_pointer(save_item);
					//проверка на ошибку при выделении памяти
					if (list->saved_item == NULL) {
						list->memory_error = true;
					}
					else {
						//удаляем элемент списка
						list_text_delete_item(list);
						//печать сохраненного элемента
						print_saved_item(list);
					}
				}
			}
		}
	}
}
//функция печатующая список текстов. Принимает указатель на односвязный список текстов.
void list_text_print(list_text* list) {
	//проверка доступа к списку
	if (list_text_access_check(list)) {
		//проверка списка на пустоту
		if (list_text_check_for_empty_list_no_comment(list)) {
			//проверка на ошибку при выделении памяти
			if (list_text_check_for_errors_in_memory_allocation(list)) {
				cout << endl;
				char massive[] = "Печать списка текстов...";
				//печать сообщения
				message_about(massive);
				text_cell* text_work_pointer = list->link_to_start;
				int number_work_pointer = 0;
				int number_of_texts = 0;
				//печатаем список
				while (text_work_pointer != NULL) {
					number_of_texts++;
					//определяем номер предложения на который указывает рабочий указатель
					if (text_work_pointer == list->work_pointer) {
						number_work_pointer = number_of_texts;
					}
					cout << number_of_texts << ". ";
					sentence_cell* sentence_work_pointer = text_work_pointer->list_sentence->link_to_start;
					//печатаем список
					while (sentence_work_pointer != NULL) {
						word_cell* word_work_pointer = sentence_work_pointer->list_word->link_to_start;
						//печать слова
						while (word_work_pointer != NULL) {
							char* word = word_work_pointer->word;
							cout << word << " ";
							word_work_pointer = word_work_pointer->next;
						}
						sentence_work_pointer = sentence_work_pointer->next;
					}
					text_work_pointer = text_work_pointer->next;
					cout << endl;
				}
				cout << "Печать списка текстов завершена..." << endl;
				cout << endl << "Рабочий указатель находится на элементе: " << endl;
				cout << number_work_pointer << ". ";
				text_work_pointer = list->work_pointer;
				sentence_cell* sentence_work_pointer = text_work_pointer->list_sentence->link_to_start;
				//выводим на экран значение рабочего указателя
				while (sentence_work_pointer != NULL) {
					word_cell* word_work_pointer = sentence_work_pointer->list_word->link_to_start;
					//печать слова
					while (word_work_pointer != NULL) {
						char* word = word_work_pointer->word;
						cout << word << " ";
						word_work_pointer = word_work_pointer->next;
					}
					sentence_work_pointer = sentence_work_pointer->next;
				}
				cout << endl << endl;
			}
		}
	}
}
//функция меняющее значение элемента за указателем. Принимает указатель на односвязный список текстов.
void list_text_change_element_value_after_pointer(list_text* list) {
	//проверка на доступ к списку
	if (list_text_access_check(list)) {
		//проверка списка на пустоту
		if (list_text_check_for_empty_list_no_comment(list)) {
			//проверка на ошибку при выделении памяти
			if (list_text_check_for_errors_in_memory_allocation(list)) {
				if (list->work_pointer->next == NULL) {
					//печать сообщения
					message_about_pointers_at_the_end_of_the_list();
				}
				else {
					/*
					char massive[] = "Изменить значение элемента за указателем!\0";
					message_about(massive);
					list_sentence* new_value = take_text_from_console();
					if (new_value == NULL) {
						list->memory_error = true;
					}
					else {
						list->work_pointer->next->list_sentence = new_value;
					}
					*/
					//переход на уровень ниже
					go_to_the_lower_level_2(list, list->work_pointer);
				}
			}
		}
	}
}
//функция прекращающая работу со списоком. Принимает указатель на односвязный список текстов.
void list_text_finish_work(list_text* list) {
	//проверка на начало работы
	if (list->start == true) {
		//проверка на ошибку при выделениипамяти
		if (list_text_check_for_errors_in_memory_allocation(list)) {
			char massive[] = "Работа со списком завершена!\0";
			//печать собщения
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
void list_text_print_(list_text* list) {
	//проверка на начало работы
	if (list->start == true) {
		//проверка списка на пустоту
		if (list->link_to_start != NULL) {
			//провкрка на ошибку при выделении памяти
			if (list->memory_error != true) {
				//печать списка
				list_text_print(list);
			}
		}
	}
}
//функция проверяющая завершение работы со списком. Принимает указатель на односвязный список. Возвращает true - если работа со списком завершена, false - если работа со списком не зваершена.
bool list_text_back(list_text* list) {
	//проверка на доступ к списку
	if (list->start == true) {
		char massive[] = "Для выхода выполните операцию 'Закончить работу со списком'\0";
		//печать сообщения
		message_about(massive);
		return false;
	}
	return true;
}
//Функция перехода на уровень ниже.Принимает указатель на список текстов
void go_to_the_lower_level(list_text* list, text_cell* check) {
	//проверка на доступ к списку
	if (list_text_access_check(list)) {
		//проверка списка на пустоту
		if (list_text_check_for_empty_list_no_comment(list)) {
			//проверка на ошибку при выделении памяти
			if (list_text_check_for_errors_in_memory_allocation(list)) {
				//ячейка элемента списка текстов
				text_cell* cell_text = NULL;
				//проверка списка на пустоту
				if (check != NULL) {
					cell_text = check;
				}
				else {
					cell_text = list->work_pointer;
				}
				//делаем переход на нижний уровень
				list_sentence* sentence_list = cell_text->list_sentence;
				//вызываем меню списка предложений
				list_sentence_menu(sentence_list);
				//если список был удален и был единственный в списке текстов
				if (list->link_to_start == cell_text && cell_text->next == NULL && sentence_list->link_to_start == NULL) {
					free(cell_text);
					list->link_to_start = NULL;
					list->work_pointer = NULL;
				}
				else {
					//если вернули пустой список предложений
					if (sentence_list->link_to_start == NULL) {
						//если он первый в списке
						if (cell_text == list->link_to_start)
						{
							list->link_to_start = cell_text->next;
							list->work_pointer = list->link_to_start;
						}
						else {
							//если он полседний в списке
							text_cell* cursor = list->link_to_start;
							if (cell_text->next == NULL) {
								while (cursor->next != cell_text) {
									cursor = cursor->next;
								}
								cursor->next = NULL;
								list->work_pointer = list->link_to_start;
							}
							//если он в середине списка
							else {
								while (cursor->next != cell_text) {
									cursor = cursor->next;
								}
								cursor->next = cell_text->next;
								list->work_pointer = cursor->next;
							}
						}
						free(sentence_list);
						free(cell_text);
					}
				}
			}
		}
	}
}
//спуск на уроквень ниже. Принимает указатель на список текстов
void go_to_the_lower_level_2(list_text* list, text_cell* check) {
	//проверка доступа к списку
	if (list_text_access_check(list)) {
		//проверка списка на пустоту
		if (list_text_check_for_empty_list_no_comment(list)) {
			//проверка на ошибку при выделении памяти
			if (list_text_check_for_errors_in_memory_allocation(list)) {
				//ячейка элемента списка текстов
				text_cell* cell_text = NULL;
				if (check != NULL) {
					cell_text = check->next;
				}
				else {
					cell_text = list->work_pointer;
				}
				//делаем переход на нижний уровень
				list_sentence* sentence_list = cell_text->list_sentence;
				//вызываем меню списка предложений
				list_sentence_menu(sentence_list);
				if (list->link_to_start == cell_text && cell_text->next == NULL && sentence_list->link_to_start == NULL) {
					free(cell_text);
					list->link_to_start = NULL;
					list->work_pointer = NULL;
				}
				else {
					//проверка списка предложений на пустоту
					if (sentence_list->link_to_start == NULL) {
						//если он первый в списке
						if (cell_text == list->link_to_start)
						{
							list->link_to_start = cell_text->next;
							list->work_pointer = list->link_to_start;
						}
						else {
							//если он полседний в списке
							text_cell* cursor = list->link_to_start;
							if (cell_text->next == NULL) {
								while (cursor->next != cell_text) {
									cursor = cursor->next;
								}
								cursor->next = NULL;
								list->work_pointer = list->link_to_start;
							}
							//если он в середине списка
							else {
								while (cursor->next != cell_text) {
									cursor = cursor->next;
								}
								cursor->next = cell_text->next;
								list->work_pointer = cursor->next;
							}
						}
						free(sentence_list);
						free(cell_text);
					}
				}
			}
		}
	}
}
//проверка на пустоту списка нижнего уровня. Принимет указатель на спискок текстов
text_cell* check_for_emptiness(list_text* list) {
	//проверка доступа к списку
	if (list_text_access_check(list)) {
		//проверка списка на упстоту
		if (list_text_check_for_empty_list_no_comment(list)) {
			//проверка на ошибку при выделении памяти
			if (list_text_check_for_errors_in_memory_allocation(list)) {
				text_cell* work_pointer = list->link_to_start;
				//проверяем наличие хотя бы одного пустого списка на нижнем уровне структуры
				while (work_pointer != NULL) {
					//проверка списка нижнего уровня на пустоту
					if (work_pointer->list_sentence->link_to_start == NULL) {
						return work_pointer;
					}
					work_pointer = work_pointer->next;
				}
			}
		}
	}
	return NULL;
}
//Меню односвязного списка слов. Принимает указатель на список текстов
void list_text_menu(list_text* list_text) {
	//переменная, которая хранит в себе выбор пользователя
	int user_choice;
	//переменная, которая содежит информацию о желании пользователя выйти
	bool back = false;
	//выводим меню о тех пор, пока пользователь не выберет пункт выйти
	while (!back) {
		//проверка на ошибку при выделении памяти
		if (list_text->memory_error == true) {
			//печать сообщения
			memory_allocation_error_message();
			system("pause");
			break;
		}
		char massive[] = "Вы находитесь в разделе: список текстов\0";
		//печать сообщения
		message_about(massive);
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
		cout << "14. Перейти на уровень ниже (по рабочему указателю): список текстов -> список предложений." << endl;
		cout << "15. Выйти." << endl;
		cout << endl << "Выберите один из пунктов для продолжения работы: ";
		//запрос данных у пользователя и проверка введенных данных на корректность
		request_verification(&user_choice, 1, 15);
		cout << endl;
		text_cell* check = NULL;
		switch (user_choice) {
		case 1:
			//нчать работу сос писоком
			list_text_begin_work(list_text);
			break;
		case 2:
			//сделать список пустым
			list_text_make_the_list_empty(list_text);
			break;
		case 3:
			//проверить список на пустоту
			list_text_check_for_empty_list(list_text);
			break;
		case 4:
			//распечатать список
			list_text_print_(list_text);
			//Установить рабочий указатель в начало
			list_text_set_cursor_to_beginning(list_text);
			//распечатать список
			list_text_print_(list_text);
			break;
		case 5:
			//проверка нахождения рабочего указателя в конце списка
			list_text_check_for_working_pointer(list_text);
			//распечатать список
			list_text_print_(list_text);
			break;
		case 6:
			//распечатать список
			list_text_print_(list_text);
			//передвинуть указатель вперед
			list_text_move_pointer_forward(list_text);
			//распечатать список
			list_text_print_(list_text);
			break;
		case 7:
			//распечатать список
			list_text_print_(list_text);
			//показатель элемент за указателем
			list_text_show_el_value_after_pointer(list_text);
			break;
		case 8:
			//распечатать список
			list_text_print_(list_text);
			//удалить элемент спика после указателя
			list_text_delete_item(list_text);
			//распечатать список
			list_text_print_(list_text);
			break;
		case 9:
			//распечатать список
			list_text_print_(list_text);
			//взять элемент списка после указателя
			list_text_take_item(list_text);
			//распечатать список
			list_text_print_(list_text);
			break;
		case 10:
			//распечатать список
			list_text_print_(list_text);
			//изменить значение элемента списка после указателя
			list_text_change_element_value_after_pointer(list_text);
			//распечатать список
			list_text_print_(list_text);
			break;
		case 11:
			//распечатать список
			list_text_print_(list_text);
			//добавить элемент
			list_text_add_item(list_text);
			//проверка добавленного списка на пустоту
			check = check_for_emptiness(list_text);
			if (check != NULL) {
				//вызвать меню списка предложений
				go_to_the_lower_level(list_text, check);
				//распечатать список
				list_text_print_(list_text);
			}
			else {
				//распечатать список
				list_text_print_(list_text);
			}
			break;
		case 12:
			//распечатать список
			list_text_print(list_text);
			break;
		case 13:
			//закончить работу со списком
			list_text_finish_work(list_text);
			break;
		case 14:
			//спуститься на уровень ниже
			go_to_the_lower_level(list_text, NULL);
			//распечатать список
			list_text_print_(list_text);
			break;
		case 15:
			//выйти
			back = list_text_back(list_text);
			break;
		}
		system("pause");
		system("cls");
	}
}
