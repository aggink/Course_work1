//����������� �������� ������ � ���������� �������
#include"Header.h"


//������� ����������� ������ � ������. ��������� ��������� �� ����������� ������ �������. ��������� true - ���� ������ ����, false - ���� ������� ���
bool list_text_access_check(list_text* list) {
	//�������� �� ������ ������
	if (list->start == true)
	{
		return true;
	}
	//�������� �� ������ ������
	if (list->start == false) {
		//������ ���������
		error_message_at_the_beginning_of_work();
		return false;
	}
}
//������� ����������� ������ �� �������. ��������� ��������� �� ����������� ������ �������. ���������� true - ���� ������ ����, false - ���� � ������ ���� ������
bool list_text_check_for_empty_list_no_comment(list_text* list) {
	//�������� �� ������� ������
	if (list->link_to_start != NULL) {
		return true;
	}
	else {
		//������ ��������� 
		error_message_due_to_empty_list();
		return false;
	}
}
//������� ����������� ������ � ��������� ������. ��������� ��������� �� ����������� ������ �������. ���������� true - ���� ������ ���, false - ���� ������ ����
bool list_text_check_for_errors_in_memory_allocation(list_text* list) {
	//�������� �� ������ ��� ��������� ������
	if (list->memory_error == true) {
		//������ ���������
		memory_allocation_error_message();
		return false;
	}
	else {
		return true;
	}
}
//������������� ������ �����������. ��������� ��������� �� ������ �����������
void list_sentence_initialize(list_sentence* list) {
	list->link_to_start = NULL;
	list->memory_error = false;
	list->saved_item = NULL;
	list->work_pointer = NULL;
	list->start = false;
}

//������� ����������� ����� � �������. ���������� NULL � ������ �������, ��� ��������� �� ������ �������� � ������ ������
list_sentence* take_text_from_console() {
	cout << "������� �����:" << endl;
	bool flag_end = false;
	bool flag_end_sentence = false;
	bool begin_n = true;
	//��������� ������ ��� ������ �����������
	list_sentence* sentence_list = (list_sentence*)malloc(sizeof(list_sentence));
	//�������� �� ������ ��� ��������� ������
	if (sentence_list == NULL) {
		return NULL;
	}
	//���� ��������� �������� ������ �����������
	list_sentence_initialize(sentence_list);
	//�������� �� ���������� ���������� ������ � �������
	while (!flag_end) {
		//�������� ������ ����
		list_word* word_list = (list_word*)malloc(sizeof(list_word));
		//�������� �� ������ ��� ��������� ������
		if (word_list == NULL) {
			return NULL;
		}
		//���� ��������� �������� ������ ����
		list_word_initialize(word_list);
		//��������� ������ � ������� � ������������ �� �� ��������� ����������
		while (!flag_end_sentence) {
			int number = 0;
			number++;
			///�������� ������ ��� �����
			char* word = (char*)calloc(number, sizeof(char));
			//�������� �� ������ ��� ��������� ������
			if (word == NULL) {
				sentence_list = NULL;
				return sentence_list;
			}
			word[number - 1] = getchar();
			//���������� ��� �������
			if (word[number - 1] == ' ' || word[number - 1] == '	') {
				word[number - 1] = getchar();
			}
			//������������� ����, ���� ��������� ������� �� ����� ������
			if (word[number - 1] == '\n') {
				flag_end = true;
				begin_n = true;
				break;
			}
			else {
				begin_n = false;
			}
			//��������� ����� �� �������
			while (word[number - 1] != ' ' && word[number - 1] !='	' && word[number - 1] != '\n') {
				if (word[number - 1] == '!' || word[number - 1] == '.' || word[number - 1] == ';' || word[number - 1] == '?') {
					flag_end_sentence = true;
				}
				number++;
				//������� ������ ��� ����� �����
				char* new_word = (char*)realloc(word, number * sizeof(char));
				//�������� �� ������ ��� ��������� ������
				if (new_word == NULL) {
					return NULL;
				}
				word = new_word;
				word[number - 1] = getchar();
			}
			if (word[number - 1] == '\n') {
				flag_end = true;
			}
			//���������� ������� \0
			word[number - 1] = '\0';
			//�������� ������ ������������ ������ ����
			word_cell* new_word_cell = (word_cell*)malloc(sizeof(word_cell));
			//�������� �� ������ ��� ��������� ������
			if (new_word_cell == NULL) {
				return NULL;
			}
			//���������� 1-��� �������� ������ ����
			if (word_list->link_to_start == NULL) {
				new_word_cell->word = word;
				new_word_cell->next = NULL;
				word_list->link_to_start = new_word_cell;
				word_list->work_pointer = new_word_cell;
			}
			else {
				//���������� n-�� �������� ������ ����
				new_word_cell->word = word;
				new_word_cell->next = NULL;
				word_list->work_pointer->next = new_word_cell;
				word_list->work_pointer = new_word_cell;
			}
		}
		//���������� � ������ �����������
		if (begin_n == true) {
			break;
		}
		//�������� ������ ��� ������ �����������
		sentence_cell* new_sentence_cell = (sentence_cell*)malloc(sizeof(sentence_cell));
		//�������� �� ������ ��� ��������� ������
		if (new_sentence_cell == NULL) {
			return NULL;
		}
		new_sentence_cell->list_word = word_list;
		//��� 1-�� ��������
		if (sentence_list->link_to_start == NULL) {
			new_sentence_cell->last = NULL;
			new_sentence_cell->next = NULL;
			sentence_list->link_to_start = new_sentence_cell;
			sentence_list->work_pointer = new_sentence_cell;
		}
		//��� n-�� ��������
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


//������� ����������� �������� �� �������. ��������� ��������� �� ����������� ������ �������
void list_text_begin_work(list_text* list) {
	list->start = true;
	list->memory_error = false;
	list->work_pointer = list->link_to_start;
}
//������� ����������� ������ �� �������. ��������� ��������� �� ����������� ������ �������.
void list_text_check_for_empty_list(list_text* list) {
	//�������� ������� � ������
	if (list_text_access_check(list)) {
		//�������� �� ������ ��� ��������� ������
		if (list_text_check_for_errors_in_memory_allocation(list)) {
			//���� ������ ����, ������� ���������
			if (list->link_to_start == NULL) {
				char massive[] = "������ ����!\0";
				//������ ���������
				message_about(massive);
			}
			else {
				char massive[] = "������ �� ����!\0";
				//������ ���������
				message_about(massive);
			}
		}
	}
}
//������� ����������� ������� �� ����������. ��������� ��������� �� ����������� ������ �������.
void list_text_add_item(list_text* list) {
	//�������� ������� � ������
	if (list_text_access_check(list)) {
		//�������� �� ������ ��� ��������� ������
		if (list_text_check_for_errors_in_memory_allocation(list)) {
			if (list->link_to_start == NULL) {
				//�������� ������ �������
				text_cell* new_cell = (text_cell*)malloc(sizeof(text_cell));
				//�������� �� ������ � ��������� ������
				if (new_cell == NULL) {
					list->memory_error = true;
				}
				else {
					//���������� ������ � �������
					new_cell->list_sentence = take_text_from_console();
					//������������ ������ �� ������� ������
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
			//��������� ������� � ����� ������
			else if (list->work_pointer->next == NULL) {
				//�������� ������ ��� ������ ������
				text_cell* new_cell = (text_cell*)malloc(sizeof(text_cell));
				//�������� �� ������ ��� ��������� ������
				if (new_cell == NULL) {
					list->memory_error = true;
				}
				else {
					//��������� ������ � �������
					new_cell->list_sentence = take_text_from_console();
					//������������ ������ �� ������� ������
					if (new_cell->list_sentence == NULL) {
						list->memory_error = true;
					}
					else {
						new_cell->next = NULL;
						list->work_pointer->next = new_cell;
					}
				}
			}
			//��������� ������� � �������� ������
			else {
				//�������� ������ ��� ������ ������
				text_cell* new_cell = (text_cell*)malloc(sizeof(text_cell));
				//�������� �� ������ ��� ��������� ������
				if (new_cell == NULL) {
					list->memory_error = true;
				}
				else {
					//��������� ������ � �������
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
//������� ��������� ������� ������. ��������� ��������� �� ����������� ������
void delete_cell_to_text_list(list_text* list) {
	text_cell* delete_cell = list->work_pointer->next;
	//������� ��������� ������� ������
	if (delete_cell->next == NULL) {
		list->work_pointer->next = NULL;
	}
	//������� n ������� ������
	else {
		list->work_pointer->next = delete_cell->next;
	}
	//������� ������ �����������
	clear_sentence_list(delete_cell->list_sentence);
	free(delete_cell->list_sentence);
	free(delete_cell);
}
//������� ��������� ������� ������ ����� ���������. ��������� ��������� �� ����������� ������ �������.
void list_text_delete_item(list_text* list) {
	//�������� ������� � ������
	if (list_text_access_check(list)) {
		//�������� ������ �� �������
		if (list_text_check_for_empty_list_no_comment(list)) {
			//�������� �� ������ ��� ��������� ������
			if (list_text_check_for_errors_in_memory_allocation(list)) {
				if (list->work_pointer->next == NULL) {
					//������ ���������
					message_about_pointers_at_the_end_of_the_list();
				}
				else {
					//������� ������ ������
					delete_cell_to_text_list(list);
				}
			}
		}
	}
}
//������� ��������� ������ �������. ��������� ��������� �� ����������� ������ �������
void clear_text_list(list_text* list) {
	list->work_pointer = list->link_to_start;
	while (list->work_pointer->next != NULL) {
		//������� ������ ������ �������
		delete_cell_to_text_list(list);
	}
	//�������� ��������� �� ������ ����
	list_sentence* delete_list_sentence = list->work_pointer->list_sentence;
	//������� ������ �����������
	clear_sentence_list(delete_list_sentence);
	//������� ����������� ������� � ������ ����
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
//������� ��������������� ������� ��������� � ������ ������. ��������� ��������� �� ����������� ������ �������.
void list_text_set_cursor_to_beginning(list_text* list) {
	//�������� ������� � ������
	if (list_text_access_check(list)) {
		//�������� �� ������� ������
		if (list_text_check_for_empty_list_no_comment(list)) {
			//�������� �� ������ ��� ��������� ������
			if (list_text_check_for_errors_in_memory_allocation(list)) {
				list->work_pointer = list->link_to_start;
			}
		}
	}
}
//������� �������� ������ ������. ��������� ��������� �� ����������� ������ �������.
void list_text_make_the_list_empty(list_text* list) {
	//�������� ������� � ������
	if (list_text_access_check(list)) {
		//�������� �� ������� ������
		if (list_text_check_for_empty_list_no_comment(list)) {
			//�������� �� ������ ��� ��������� ������
			if (list_text_check_for_errors_in_memory_allocation(list)) {
				//������� ������
				clear_text_list(list);
				char massive[] = "������ ����!\0";
				//������ ���������
				message_about(massive);
			}
		}
	}
}
//������� ����������� ���������� �������� ���������. ��������� ��������� �� ����������� ������ ����.
void list_text_check_for_working_pointer(list_text* list) {
	//�������� ������� � ������
	if (list_text_access_check(list)) {
		//�������� �� ������� ������
		if (list_text_check_for_empty_list_no_comment(list)) {
			//�������� �� ������ ��� ��������� ������
			if (list_text_check_for_errors_in_memory_allocation(list)) {
				//�������� ���������� �������� ���������
				if (list->work_pointer->next == NULL) {
					char massive[] = "������� ��������� � ����� ������!\0";
					//������ ���������
					message_about(massive);
				}
				else {
					char massive[] = "������� ��������� �� � ����� ������!\0";
					//������ ���������
					message_about(massive);
				}
			}
		}
	}
}
//������� ��������� ��������� ������. ��������� ��������� �� ����������� ������ �������.
void list_text_move_pointer_forward(list_text* list) {
	if (list_text_access_check(list)) {
		//�������� ������� � ������
		if (list_text_check_for_empty_list_no_comment(list)) {
			//�������� �� ������� ������
			if (list_text_check_for_errors_in_memory_allocation(list)) {
				//�������� ���������� �������� ���������
				if (list->work_pointer->next == NULL) {
					//������ ���������
					message_about_pointers_at_the_end_of_the_list();
				}
				else {
					list->work_pointer = list->work_pointer->next;
				}
			}
		}
	}
}
//������� ������������ �������� �������� �� ����������. ��������� ��������� �� ����������� ������ �������.
void list_text_show_el_value_after_pointer(list_text* list) {
	//�������� ������� � ������
	if (list_text_access_check(list)) {
		//�������� �� ������� ������
		if (list_text_check_for_empty_list_no_comment(list)) {
			//�������� �� ������ ��� ��������� ������
			if (list_text_check_for_errors_in_memory_allocation(list)) {
				//�������� ���������� �������� ���������
				if (list->work_pointer->next == NULL) {
					//������ ���������
					message_about_pointers_at_the_end_of_the_list();
				}
				else {
					char massive[] = "�������� �������� ������ �� ����������:\0";
					//������ ���������
					message_about(massive);
					text_cell* text_work_pointer = list->work_pointer->next;
					sentence_cell* sentence_work_pointer = text_work_pointer->list_sentence->link_to_start;
					//������� ������ �� �����
					while (sentence_work_pointer != NULL) {
						word_cell* word_work_pointer = sentence_work_pointer->list_word->link_to_start;
						//������ �����
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
//������� ����������� ������ �������. ��������� ��������� �� ����������� ������ �������. ���������� ��������� �������������� ������ �����������
list_sentence* save_item_pointer(list_sentence* list) {
	//������� ��������� ��� ������������� ������
	list_sentence* copy_list_sentence = (list_sentence*)malloc(sizeof(list_sentence));
	//����������� ��������� �������� ������
	list_sentence_initialize(copy_list_sentence);
	//�������� ������� ��������� � ������, ������� ���� �����������
	sentence_cell* work_pointer = list->link_to_start;
	//�������� �� ������ ��� ��������� ������
	if (copy_list_sentence == NULL) {
		return NULL;
	}
	//���������� ������� ��������
	while (work_pointer!= NULL) {
		//�������� ������ ����
		list_word* copy_list_word = save_item_pointer(work_pointer->list_word);
		//������� ������ ������ �����������
		sentence_cell* new_sentence_cell = (sentence_cell*)malloc(sizeof(sentence_cell));
		//�������� �� ������ ��� ��������� ������
		if (new_sentence_cell == NULL) {
			return NULL;
		}
		//��� ������� ��������
		if (copy_list_sentence->link_to_start == NULL) {
			new_sentence_cell->list_word = copy_list_word;
			new_sentence_cell->last = NULL;
			new_sentence_cell->next = NULL;
			copy_list_sentence->link_to_start = new_sentence_cell;
			copy_list_sentence->work_pointer = new_sentence_cell;
		}
		//��� n ��������
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
//������ ������������ ��������. ��������� ��������� �� ������ �������
void print_saved_item(list_text* list) {
	char massive[] = "����������� ������� ������: ";
	//������ ���������
	message_about(massive);
	list_sentence* saves_item = list->saved_item;
	sentence_cell* sentence_work_pointer = saves_item->link_to_start;
	//������� ������ �� �����
	while (sentence_work_pointer != NULL) {
		word_cell* word_work_pointer = sentence_work_pointer->list_word->link_to_start;
		//������ �����
		while (word_work_pointer != NULL) {
			char* word = word_work_pointer->word;
			cout << word << " ";
			word_work_pointer = word_work_pointer->next;
		}
		sentence_work_pointer = sentence_work_pointer->next;
	}
	cout << endl;
}
//������� ������ �������� ������ �� ����������. ��������� ��������� �� ����������� ������ �������.
void list_text_take_item(list_text* list) {
	//�������� �� ������ � ������
	if (list_text_access_check(list)) {
		//�������� �� ������� ������
		if (list_text_check_for_empty_list_no_comment(list)) {
			//�������� �� ������ ��� ��������� ������
			if (list_text_check_for_errors_in_memory_allocation(list)) {
				if (list->work_pointer->next == NULL) {
					//������ ���������
					message_about_pointers_at_the_end_of_the_list();
				}
				else {
					//�������� �� ������� ��� ������������ ������, ���� ������������, �� ������� ���
					if ((list->saved_item) != NULL) {
						list_sentence* delete_saved_item = list->saved_item;
						//������� ������ �����������
						clear_sentence_list(delete_saved_item);
						free(delete_saved_item);
						list->saved_item = NULL;
					}
					//������� ��������� �� ������, ������� ��� ���� ���������
					list_sentence* save_item = list->work_pointer->next->list_sentence;
					//��������� ������
					list->saved_item = save_item_pointer(save_item);
					//�������� �� ������ ��� ��������� ������
					if (list->saved_item == NULL) {
						list->memory_error = true;
					}
					else {
						//������� ������� ������
						list_text_delete_item(list);
						//������ ������������ ��������
						print_saved_item(list);
					}
				}
			}
		}
	}
}
//������� ���������� ������ �������. ��������� ��������� �� ����������� ������ �������.
void list_text_print(list_text* list) {
	//�������� ������� � ������
	if (list_text_access_check(list)) {
		//�������� ������ �� �������
		if (list_text_check_for_empty_list_no_comment(list)) {
			//�������� �� ������ ��� ��������� ������
			if (list_text_check_for_errors_in_memory_allocation(list)) {
				cout << endl;
				char massive[] = "������ ������ �������...";
				//������ ���������
				message_about(massive);
				text_cell* text_work_pointer = list->link_to_start;
				int number_work_pointer = 0;
				int number_of_texts = 0;
				//�������� ������
				while (text_work_pointer != NULL) {
					number_of_texts++;
					//���������� ����� ����������� �� ������� ��������� ������� ���������
					if (text_work_pointer == list->work_pointer) {
						number_work_pointer = number_of_texts;
					}
					cout << number_of_texts << ". ";
					sentence_cell* sentence_work_pointer = text_work_pointer->list_sentence->link_to_start;
					//�������� ������
					while (sentence_work_pointer != NULL) {
						word_cell* word_work_pointer = sentence_work_pointer->list_word->link_to_start;
						//������ �����
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
				cout << "������ ������ ������� ���������..." << endl;
				cout << endl << "������� ��������� ��������� �� ��������: " << endl;
				cout << number_work_pointer << ". ";
				text_work_pointer = list->work_pointer;
				sentence_cell* sentence_work_pointer = text_work_pointer->list_sentence->link_to_start;
				//������� �� ����� �������� �������� ���������
				while (sentence_work_pointer != NULL) {
					word_cell* word_work_pointer = sentence_work_pointer->list_word->link_to_start;
					//������ �����
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
//������� �������� �������� �������� �� ����������. ��������� ��������� �� ����������� ������ �������.
void list_text_change_element_value_after_pointer(list_text* list) {
	//�������� �� ������ � ������
	if (list_text_access_check(list)) {
		//�������� ������ �� �������
		if (list_text_check_for_empty_list_no_comment(list)) {
			//�������� �� ������ ��� ��������� ������
			if (list_text_check_for_errors_in_memory_allocation(list)) {
				if (list->work_pointer->next == NULL) {
					//������ ���������
					message_about_pointers_at_the_end_of_the_list();
				}
				else {
					/*
					char massive[] = "�������� �������� �������� �� ����������!\0";
					message_about(massive);
					list_sentence* new_value = take_text_from_console();
					if (new_value == NULL) {
						list->memory_error = true;
					}
					else {
						list->work_pointer->next->list_sentence = new_value;
					}
					*/
					//������� �� ������� ����
					go_to_the_lower_level_2(list, list->work_pointer);
				}
			}
		}
	}
}
//������� ������������ ������ �� ��������. ��������� ��������� �� ����������� ������ �������.
void list_text_finish_work(list_text* list) {
	//�������� �� ������ ������
	if (list->start == true) {
		//�������� �� ������ ��� ���������������
		if (list_text_check_for_errors_in_memory_allocation(list)) {
			char massive[] = "������ �� ������� ���������!\0";
			//������ ��������
			message_about(massive);
			list->start = false;
		}
	}
	else {
		char massive[] = "������ �� ������� �� ������!\0";
		//������ ���������
		message_about(massive);
	}
}
//������� ���������� ������ � ��������� �������� �������� ���������. ��������� ��������� �� ����������� ������
void list_text_print_(list_text* list) {
	//�������� �� ������ ������
	if (list->start == true) {
		//�������� ������ �� �������
		if (list->link_to_start != NULL) {
			//�������� �� ������ ��� ��������� ������
			if (list->memory_error != true) {
				//������ ������
				list_text_print(list);
			}
		}
	}
}
//������� ����������� ���������� ������ �� �������. ��������� ��������� �� ����������� ������. ���������� true - ���� ������ �� ������� ���������, false - ���� ������ �� ������� �� ���������.
bool list_text_back(list_text* list) {
	//�������� �� ������ � ������
	if (list->start == true) {
		char massive[] = "��� ������ ��������� �������� '��������� ������ �� �������'\0";
		//������ ���������
		message_about(massive);
		return false;
	}
	return true;
}
//������� �������� �� ������� ����.��������� ��������� �� ������ �������
void go_to_the_lower_level(list_text* list, text_cell* check) {
	//�������� �� ������ � ������
	if (list_text_access_check(list)) {
		//�������� ������ �� �������
		if (list_text_check_for_empty_list_no_comment(list)) {
			//�������� �� ������ ��� ��������� ������
			if (list_text_check_for_errors_in_memory_allocation(list)) {
				//������ �������� ������ �������
				text_cell* cell_text = NULL;
				//�������� ������ �� �������
				if (check != NULL) {
					cell_text = check;
				}
				else {
					cell_text = list->work_pointer;
				}
				//������ ������� �� ������ �������
				list_sentence* sentence_list = cell_text->list_sentence;
				//�������� ���� ������ �����������
				list_sentence_menu(sentence_list);
				//���� ������ ��� ������ � ��� ������������ � ������ �������
				if (list->link_to_start == cell_text && cell_text->next == NULL && sentence_list->link_to_start == NULL) {
					free(cell_text);
					list->link_to_start = NULL;
					list->work_pointer = NULL;
				}
				else {
					//���� ������� ������ ������ �����������
					if (sentence_list->link_to_start == NULL) {
						//���� �� ������ � ������
						if (cell_text == list->link_to_start)
						{
							list->link_to_start = cell_text->next;
							list->work_pointer = list->link_to_start;
						}
						else {
							//���� �� ��������� � ������
							text_cell* cursor = list->link_to_start;
							if (cell_text->next == NULL) {
								while (cursor->next != cell_text) {
									cursor = cursor->next;
								}
								cursor->next = NULL;
								list->work_pointer = list->link_to_start;
							}
							//���� �� � �������� ������
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
//����� �� �������� ����. ��������� ��������� �� ������ �������
void go_to_the_lower_level_2(list_text* list, text_cell* check) {
	//�������� ������� � ������
	if (list_text_access_check(list)) {
		//�������� ������ �� �������
		if (list_text_check_for_empty_list_no_comment(list)) {
			//�������� �� ������ ��� ��������� ������
			if (list_text_check_for_errors_in_memory_allocation(list)) {
				//������ �������� ������ �������
				text_cell* cell_text = NULL;
				if (check != NULL) {
					cell_text = check->next;
				}
				else {
					cell_text = list->work_pointer;
				}
				//������ ������� �� ������ �������
				list_sentence* sentence_list = cell_text->list_sentence;
				//�������� ���� ������ �����������
				list_sentence_menu(sentence_list);
				if (list->link_to_start == cell_text && cell_text->next == NULL && sentence_list->link_to_start == NULL) {
					free(cell_text);
					list->link_to_start = NULL;
					list->work_pointer = NULL;
				}
				else {
					//�������� ������ ����������� �� �������
					if (sentence_list->link_to_start == NULL) {
						//���� �� ������ � ������
						if (cell_text == list->link_to_start)
						{
							list->link_to_start = cell_text->next;
							list->work_pointer = list->link_to_start;
						}
						else {
							//���� �� ��������� � ������
							text_cell* cursor = list->link_to_start;
							if (cell_text->next == NULL) {
								while (cursor->next != cell_text) {
									cursor = cursor->next;
								}
								cursor->next = NULL;
								list->work_pointer = list->link_to_start;
							}
							//���� �� � �������� ������
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
//�������� �� ������� ������ ������� ������. �������� ��������� �� ������� �������
text_cell* check_for_emptiness(list_text* list) {
	//�������� ������� � ������
	if (list_text_access_check(list)) {
		//�������� ������ �� �������
		if (list_text_check_for_empty_list_no_comment(list)) {
			//�������� �� ������ ��� ��������� ������
			if (list_text_check_for_errors_in_memory_allocation(list)) {
				text_cell* work_pointer = list->link_to_start;
				//��������� ������� ���� �� ������ ������� ������ �� ������ ������ ���������
				while (work_pointer != NULL) {
					//�������� ������ ������� ������ �� �������
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
//���� ������������ ������ ����. ��������� ��������� �� ������ �������
void list_text_menu(list_text* list_text) {
	//����������, ������� ������ � ���� ����� ������������
	int user_choice;
	//����������, ������� ������� ���������� � ������� ������������ �����
	bool back = false;
	//������� ���� � ��� ���, ���� ������������ �� ������� ����� �����
	while (!back) {
		//�������� �� ������ ��� ��������� ������
		if (list_text->memory_error == true) {
			//������ ���������
			memory_allocation_error_message();
			system("pause");
			break;
		}
		char massive[] = "�� ���������� � �������: ������ �������\0";
		//������ ���������
		message_about(massive);
		cout << "����" << endl;
		cout << " 1. ������ ������ �� �������." << endl;
		cout << " 2. ������� ������ ������." << endl;
		cout << " 3. ��������: ������ ���� / ������ �� ����." << endl;
		cout << " 4. ���������� ������� ��������� � ������ ������." << endl;
		cout << " 5. ��������: ������� ��������� � ����� ������?" << endl;
		cout << " 6. ����������� ������� ��������� ������ ������." << endl;
		cout << " 7. �������� �������� �������� ������ �� ����������." << endl;
		cout << " 8. ������� ������� ������ �� ����������." << endl;
		cout << " 9. ����� ������� ������ �� ����������." << endl;
		cout << "10. �������� �������� �������� ������ �� ����������." << endl;
		cout << "11. �������� ������� �� ����������." << endl;
		cout << "12. ����������� ��������� ������." << endl;
		cout << "13. ��������� ������ �� ��������." << endl;
		cout << "14. ������� �� ������� ���� (�� �������� ���������): ������ ������� -> ������ �����������." << endl;
		cout << "15. �����." << endl;
		cout << endl << "�������� ���� �� ������� ��� ����������� ������: ";
		//������ ������ � ������������ � �������� ��������� ������ �� ������������
		request_verification(&user_choice, 1, 15);
		cout << endl;
		text_cell* check = NULL;
		switch (user_choice) {
		case 1:
			//����� ������ ��� �������
			list_text_begin_work(list_text);
			break;
		case 2:
			//������� ������ ������
			list_text_make_the_list_empty(list_text);
			break;
		case 3:
			//��������� ������ �� �������
			list_text_check_for_empty_list(list_text);
			break;
		case 4:
			//����������� ������
			list_text_print_(list_text);
			//���������� ������� ��������� � ������
			list_text_set_cursor_to_beginning(list_text);
			//����������� ������
			list_text_print_(list_text);
			break;
		case 5:
			//�������� ���������� �������� ��������� � ����� ������
			list_text_check_for_working_pointer(list_text);
			//����������� ������
			list_text_print_(list_text);
			break;
		case 6:
			//����������� ������
			list_text_print_(list_text);
			//����������� ��������� ������
			list_text_move_pointer_forward(list_text);
			//����������� ������
			list_text_print_(list_text);
			break;
		case 7:
			//����������� ������
			list_text_print_(list_text);
			//���������� ������� �� ����������
			list_text_show_el_value_after_pointer(list_text);
			break;
		case 8:
			//����������� ������
			list_text_print_(list_text);
			//������� ������� ����� ����� ���������
			list_text_delete_item(list_text);
			//����������� ������
			list_text_print_(list_text);
			break;
		case 9:
			//����������� ������
			list_text_print_(list_text);
			//����� ������� ������ ����� ���������
			list_text_take_item(list_text);
			//����������� ������
			list_text_print_(list_text);
			break;
		case 10:
			//����������� ������
			list_text_print_(list_text);
			//�������� �������� �������� ������ ����� ���������
			list_text_change_element_value_after_pointer(list_text);
			//����������� ������
			list_text_print_(list_text);
			break;
		case 11:
			//����������� ������
			list_text_print_(list_text);
			//�������� �������
			list_text_add_item(list_text);
			//�������� ������������ ������ �� �������
			check = check_for_emptiness(list_text);
			if (check != NULL) {
				//������� ���� ������ �����������
				go_to_the_lower_level(list_text, check);
				//����������� ������
				list_text_print_(list_text);
			}
			else {
				//����������� ������
				list_text_print_(list_text);
			}
			break;
		case 12:
			//����������� ������
			list_text_print(list_text);
			break;
		case 13:
			//��������� ������ �� �������
			list_text_finish_work(list_text);
			break;
		case 14:
			//���������� �� ������� ����
			go_to_the_lower_level(list_text, NULL);
			//����������� ������
			list_text_print_(list_text);
			break;
		case 15:
			//�����
			back = list_text_back(list_text);
			break;
		}
		system("pause");
		system("cls");
	}
}
