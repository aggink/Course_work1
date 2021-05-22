//����������� �������� ������ � ���������� �������
#include"Header.h"


//������������� ������ ����
void list_word_initialize(list_word* list) {
	list->link_to_start = NULL;
	list->memory_error = false;
	list->saved_item = NULL;
	list->work_pointer = NULL;
	list->start = false;
}


//������� ����������� ���������� ����������� � �������. ���������� ��������� �� ������ ����.
list_word* take_sentence_from_console() {
	//���������� ����������� �� ����� �����������
	bool flag_end_sentence = false;
	bool flag_end_text = false;
	//��������� ������ ��� ������ �����������
	list_word* list = (list_word*)malloc(sizeof(list_word));
	//�������� �� ������ ��� ��������� ������
	if (list == NULL) {
		return list;
	}
	//�������������� ������ ����
	list_word_initialize(list);
	//���������� ��������� ��������
	int number_of_characters = 0;
	number_of_characters++;
	//��������� ������ ��� �����
	char* word = (char*)calloc(number_of_characters, sizeof(char));
	//�������� �� ������ ��� ��������� ������
	if (word == NULL) {
		return NULL;
	}
	word[number_of_characters - 1] = getchar();
	//������� ����� �� ������ ������� ���������
	if (word[number_of_characters - 1] == '\n') {
		return list;
	}
	//��������� ������ � �������
	while (true) {
		//��������� ������ � �������
		while (!search_character(word[number_of_characters - 1], &flag_end_sentence, &flag_end_text)) {
			number_of_characters++;
			//�������� ������ ��� �����
			char* new_pointer_word = (char*)realloc(word, number_of_characters * sizeof(char));
			//�������� ������� ��� ��������� ������
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
			//���������� ���������� �������
			if (word[number_of_characters - 1] != ' ' && word[number_of_characters - 1] != '	') {
				number_of_characters++;
				//��������� ������
				char* new_pointer_word = (char*)realloc(word, number_of_characters * sizeof(char));
				//�������� �� ������ ��� ��������� ������
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
		//�������� ������ ��� �����
		word_cell* new_cell = (word_cell*)malloc(sizeof(word_cell));
		//�������� �� ������ ��� ��������� ������
		if (new_cell == NULL) {
			list = NULL;
			return list;
		}
		//������ ������� ������ ����
		if (list->link_to_start == NULL) {
			new_cell->word = word;
			new_cell->next = NULL;
			list->link_to_start = new_cell;
			list->work_pointer = new_cell;
		}
		//���� ������ ������� ������ ���� ��� ����������
		else {
			new_cell->word = word;
			new_cell->next = NULL;
			list->work_pointer->next = new_cell;
			list->work_pointer = new_cell;

		}
		//������������� ���� ����� ����������� ��� ���������� ���������
		if (flag_end_sentence == true) {
			flag_end_sentence = false;
			break;
		}
		number_of_characters = 0;
		number_of_characters++;
		//��������� ������ ��� �����
		char* new_word = (char*)malloc(number_of_characters*sizeof(char));
		//�������� �� ������ ��� ��������� ������
		if (new_word == NULL) {
			cout << "������ ��� ��������� ������!" << endl;
			system("pause");
			exit(0);
		}
		word = new_word;
		//�������� �� ������ ��� ��������� ������
		if (word == NULL) {
			list = NULL;
			return list;
		}
		word[number_of_characters - 1] = getchar();
	}
	return list;
}
//������� ��������� ������� ������ ����� ����������. ��������� ��������� �� ����������� ������ �����������
void delete_cell_to_sentence_list_after(list_sentence* list) {
	//������� ��������� �� ������, ������� ����� �������
	sentence_cell* delete_cell = list->work_pointer->next;
	//�������� ��������� �� ������ ����, ������� ���� �������
	list_word* delete_list_word = delete_cell->list_word;
	//������� ��������� ������� ������
	if (delete_cell->next == NULL) {
		//������� ������
		clear_word_list(delete_list_word);
		list->work_pointer->next = NULL;
	}
	//������� n ������� ������
	else {
		//�������� ��������� �� ��������� �� ��������� ������� ���� ������
		sentence_cell* next_sentence = delete_cell->next;
		//������� ������ ����
		clear_word_list(delete_list_word);
		list->work_pointer->next = next_sentence;
		next_sentence->last = list->work_pointer;
	}
	free(delete_list_word);
	free(delete_cell);
}
//������� ��������� ������� ������ �� ���������. ��������� ��������� �� ������ �����������
void delete_cell_to_sentence_list_before(list_sentence* list) {
	//������� ��������� �� ������, ������� ����� �������
	sentence_cell* delete_cell = list->work_pointer->last;
	//�������� ��������� �� ������ ����, ������� ���� �������
	list_word* delete_list_word = delete_cell->list_word;
	//������� ������ ������� ������
	if (delete_cell->last == NULL) {
		//������� ������
		clear_word_list(delete_list_word);
		list->work_pointer->last = NULL;
		list->link_to_start = list->work_pointer;
	}
	else {
		//������� n ������� ������
		//�������� ��������� �� ���������� �� ���������� ������ ���� ������
		sentence_cell* last_sentence = delete_cell->last;
		last_sentence->next = list->work_pointer;
		list->work_pointer->last = last_sentence;
		//������� ������ ����
		clear_word_list(delete_list_word);
	}
	free(delete_list_word);
	free(delete_cell);
}
//������� ��������� ������ ����. ��������� ��������� �� ������ �����������
void clear_sentence_list(list_sentence* list) {
	list->work_pointer = list->link_to_start;
	//�������� �� ��������� ������� ������
	while (list->work_pointer->next != NULL) {
		//������� ������� ������ ����� ���������
		delete_cell_to_sentence_list_after(list);
	}
	//�������� ��������� �� ������ ����
	list_word* delete_list_word = list->work_pointer->list_word;
	//������� ������
	clear_word_list(delete_list_word);
	//������� ����������� ������� � ������ ����
	if ((list->saved_item) != NULL) {
		list_word* delete_saved_item = list->saved_item;
		//������ ������ ����
		clear_word_list(delete_saved_item);
		free(delete_saved_item);
	}
	free(delete_list_word);
	list->link_to_start = NULL;
	list->work_pointer = NULL;
	list->saved_item = NULL;
}
//������� ����������� ������ � ������. ��������� ��������� �� ����������� ������ �����������. ��������� true - ���� ������ ����, false - ���� ������� ���
bool list_sentence_access_check(list_sentence* list) {
	//�������� �� ������ ������ �� �������
	if (list->start == true)
	{
		return true;
	}
	//�������� �� ������ ������ �� �������
	if (list->start == false) {
		//������ ���������
		error_message_at_the_beginning_of_work();
		return false;
	}
}
//������� ����������� ������ �� �������. ��������� ��������� �� ����������� ������ �����������. ���������� true - ���� ������ ����, false - ���� � ������ ���� ������
bool list_sentence_check_for_empty_list_no_comment(list_sentence* list) {
	//�������� ������ �� �������
	if (list->link_to_start != NULL) {
		return true;
	}
	else {
		//������ ���������
		error_message_due_to_empty_list();
		return false;
	}
}
//������� ����������� ������ � ��������� ������. ��������� ��������� �� ����������� ������ �����������. ���������� true - ���� ������ ���, false - ���� ������ ����
bool list_sentence_check_for_errors_in_memory_allocation(list_sentence* list) {
	if (list->memory_error == true) {
		//������ ���������
		memory_allocation_error_message();
		return false;
	}
	else {
		return true;
	}
}
//������� ����������� �������� �� �������. ��������� ��������� �� ����������� ������ �����������.
void list_sentence_begin_work(list_sentence* list) {
	list->start = true;
	list->memory_error = false;
	list->work_pointer = list->link_to_start;
}
//������� ����������� ������ �� �������. ��������� ��������� �� ����������� ������ �����������.
void list_sentence_check_for_empty_list(list_sentence* list) {
	//�������� �� ������ � ������
	if (list_sentence_access_check(list)) {
		//�������� �� ������ ��� ��������� ������
		if (list_sentence_check_for_errors_in_memory_allocation(list)) {
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
//������� ����������� ������� �� ����������. ��������� ��������� �� ����������� ������ �����������.
void list_sentence_add_item_next(list_sentence* list) {
	//�������� �� ������ � ������
	if (list_sentence_access_check(list)) {
		//�������� �� ������ ��� ��������� ������
		if (list_sentence_check_for_errors_in_memory_allocation(list)) {
			if (list->link_to_start == NULL) {
				//�������� ������ �������
				sentence_cell* new_cell = (sentence_cell*)malloc(sizeof(sentence_cell));
				//�������� �� ������ � ��������� ������
				if (new_cell == NULL) {
					list->memory_error = true;
				}
				else {
					cout << endl << "������� �����������: ";
					//���������� �������� � �������
					new_cell->list_word = take_sentence_from_console();
					//�������� �� ������ ��� ��������� ������
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
			//��������� ������� � ����� ������
			else if (list->work_pointer->next == NULL) {
				//�������� ������
				sentence_cell* new_cell = (sentence_cell*)malloc(sizeof(sentence_cell));
				//�������� �� ������ ��� ��������� ������
				if (new_cell == NULL) {
					list->memory_error = true;
				}
				else {
					//���������� �������� � �������
					cout << endl << "������� �����������: ";
					//��������� ������ � �������
					new_cell->list_word = take_sentence_from_console();
					//�������� ���������� ������
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
				//��������� ������� � �������� ������
				sentence_cell* new_cell = (sentence_cell*)malloc(sizeof(sentence_cell));
				//�������� �� ������ ��� ��������� ������
				if (new_cell == NULL) {
					list->memory_error = true;
				}
				else {
					//���������� �������� � �������
					cout << endl << "������� �����������: ";
					//��������� ������ � �������
					new_cell->list_word = take_sentence_from_console();
					//�������� �� ������ ��� ��������� ������
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
//������� ����������� ������� �� ����������. ��������� ��������� �� ����������� ������ �����������.
void list_sentence_add_item_last(list_sentence* list) {
	//������� �� ������ � ������
	if (list_sentence_access_check(list)) {
		//�������� �� ������ ��� ��������� ������
		if (list_sentence_check_for_errors_in_memory_allocation(list)) {
			if (list->link_to_start == NULL) {
				//�������� ������ �������
				sentence_cell* new_cell = (sentence_cell*)malloc(sizeof(sentence_cell));
				//�������� �� ������ � ��������� ������
				if (new_cell == NULL) {
					list->memory_error = true;
				}
				else {
					//���������� �������� � �������
					cout << endl << "������� �����������: ";
					//��������� ������ � �������
					new_cell->list_word = take_sentence_from_console();
					//�������� �� ������ ��� ��������� ������
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
				//��������� ������� � ������ ������
				sentence_cell* new_cell = (sentence_cell*)malloc(sizeof(sentence_cell));
				//�������� �� ������ ��� ��������� ������
				if (new_cell == NULL) {
					list->memory_error = true;
				}
				else {
					//���������� �������� � �������
					cout << endl << "������� �����������: ";
					new_cell->list_word = take_sentence_from_console();
					//�������� �� ������ ��� ��������� ������
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
				//��������� ������� � �������� ������
				sentence_cell* new_cell = (sentence_cell*)malloc(sizeof(sentence_cell));
				//�������� �� ������ ��� ��������� ������
				if (new_cell == NULL) {
					list->memory_error = true;
				}
				else {
					//���������� �������� � �������
					cout << endl << "������� �����������: ";
					new_cell->list_word = take_sentence_from_console();
					//�������� �� ������ ��� ��������� ������
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
//������� ��������������� ������� ��������� � ������ ������. ��������� ��������� �� ����������� ������ �����������.
void list_sentence_set_cursor_to_beginning(list_sentence* list) {
	//�������� ������� � ������
	if (list_sentence_access_check(list)) {
		//�������� ������ �� �������
		if (list_sentence_check_for_empty_list_no_comment(list)) {
			//�������� �� ������ ��� ��������� ������
			if (list_sentence_check_for_errors_in_memory_allocation(list)) {
				list->work_pointer = list->link_to_start;
			}
		}
	}
}
//������� ������������ ��������� �� ����� ������. ��������� ��������� �� ����������� ������ �����������.
sentence_cell* list_sentence_go_to_bottom(list_sentence* list) {
	sentence_cell* pointer = list->link_to_start;
	//���� �� ����� ������
	while (pointer->next != NULL) {
		pointer = pointer->next;
	}
	return pointer;
}
//������� ��������������� ������� ��������� � ����� ������. ��������� ��������� �� ����������� ������ �����������.
void list_sentence_set_cursor_to_the_end(list_sentence* list) {
	//�������� ������� � ������
	if (list_sentence_access_check(list)) {
		//�������� ������ �� �������
		if (list_sentence_check_for_empty_list_no_comment(list)) {
			//�������� �� ������ ��� ��������� ������
			if (list_sentence_check_for_errors_in_memory_allocation(list)) {
				//����������� �� ������� ����
				list->work_pointer = list_sentence_go_to_bottom(list);
			}
		}
	}
}
//������� ��������� ������� ������ ����� ���������. ��������� ��������� �� ����������� ������ �����������.
void list_sentence_delete_item_after(list_sentence* list) {
	//�������� ������� � ������
	if (list_sentence_access_check(list)) {
		//�������� ������ �� �������
		if (list_sentence_check_for_empty_list_no_comment(list)) {
			//�������� �� ������ ��� ��������� ������
			if (list_sentence_check_for_errors_in_memory_allocation(list)) {
				if (list->work_pointer->next == NULL) {
					//������ ���������
					message_about_pointers_at_the_end_of_the_list();
				}
				else {
					//������� ������� ����� ���������
					delete_cell_to_sentence_list_after(list);
				}
			}
		}
	}
}
//������� ��������� ������� ������ �� ���������. ��������� ��������� �� ����������� ������ �����������.
void list_sentence_delete_item_before(list_sentence* list) {
	//�������� ������� � ������
	if (list_sentence_access_check(list)) {
		//�������� ������ �� �������
		if (list_sentence_check_for_empty_list_no_comment(list)) {
			//�������� �� ������ ��� ��������� ������
			if (list_sentence_check_for_errors_in_memory_allocation(list)) {
				if (list->work_pointer->last == NULL) {
					//������ ���������
					message_about_pointers_in_the_beginning_of_the_list();
				}
				else {
					//������� ������� �� ���������
					delete_cell_to_sentence_list_before(list);
				}
			}
		}
	}
}
//������� �������� ������ ������. ��������� ��������� �� ����������� ������ �����������.
void list_sentence_make_the_list_empty(list_sentence* list) {
	//�������� ������� � ������
	if (list_sentence_access_check(list)) {
		//�������� ������ �� �������
		if (list_sentence_check_for_empty_list_no_comment(list)) {
			//�������� �� ������ ��� ��������� ������
			if (list_sentence_check_for_errors_in_memory_allocation(list)) {
				//������� ������
				clear_sentence_list(list);
				char massive[] = "������ ����!\0";
				//������ ���������
				message_about(massive);
			}
		}
	}
}
//������� ����������� ���������� �������� ��������� � ����� ������. ��������� ��������� �� ����������� ������ �����������.
void list_sentence_check_for_working_pointer_to_end(list_sentence* list) {
	//�������� ������� � ������
	if (list_sentence_access_check(list)) {
		//�������� ������ �� �������
		if (list_sentence_check_for_empty_list_no_comment(list)) {
			//�������� �� ������ ��� ��������� ������
			if (list_sentence_check_for_errors_in_memory_allocation(list)) {
				//���������� ���������� �������� ���������
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
//������� ����������� ���������� �������� ��������� � ������ ������. ��������� ��������� �� ����������� ������ �����������.
void list_sentence_check_for_working_pointer_to_beginning(list_sentence* list) {
	//�������� ������� � �������
	if (list_sentence_access_check(list)) {
		//�������� ������ �� �������
		if (list_sentence_check_for_empty_list_no_comment(list)) {
			//�������� �� ������ ��� ��������� ������
			if (list_sentence_check_for_errors_in_memory_allocation(list)) {
				//���������� ���������� �������� ���������
				if (list->work_pointer->last == NULL) {
					char massive[] = "������� ��������� � ������ ������!\0";
					//������ ���������
					message_about(massive);
				}
				else {
					char massive[] = "������� ��������� �� � ������ ������!\0";
					//������ ���������
					message_about(massive);
				}
			}
		}
	}
}
//������� ��������� ��������� ������. ��������� ��������� �� ����������� ������ �����������.
void list_sentence_move_pointer_forward(list_sentence* list) {
	//�������� �� ������ � ������
	if (list_sentence_access_check(list)) {
		//�������� ������ �� �������
		if (list_sentence_check_for_empty_list_no_comment(list)) {
			//�������� �� ������ ��� ��������� ������
			if (list_sentence_check_for_errors_in_memory_allocation(list)) {
				//�������� �� ���������� �������� ��������� � ������ ������
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
//������� ��������� ��������� �����. ��������� ��������� �� ����������� ������ �����������.
void list_sentence_move_pointer_back(list_sentence* list) {
	//�������� ������� � ������
	if (list_sentence_access_check(list)) {
		//�������� ������ �� �������
		if (list_sentence_check_for_empty_list_no_comment(list)) {
			//�������� �� ������ ��� ��������� ������
			if (list_sentence_check_for_errors_in_memory_allocation(list)) {
				//�������� �� ���������� �������� ��������� � ����� ������
				if (list->work_pointer->last == NULL) {
					//������ ���������
					message_about_pointers_in_the_beginning_of_the_list();
				}
				else {
					list->work_pointer = list->work_pointer->last;
				}
			}
		}
	}
}
//������� ���������� ���� �����������(������ ����). �������� ��������� �� ����������� ������ ����.
void print_sentence(list_word* list) {
	//������� ������� ��������� ��� ����� ������
	word_cell* work_pointer_list_word = list->link_to_start;
	//�������� �����������
	while (work_pointer_list_word != NULL) {
		//������� ��������� �� �����
		char* word = work_pointer_list_word->word;
		cout << word << " ";
		work_pointer_list_word = work_pointer_list_word->next;
	}
	cout << endl;
}
//������� ������������ �������� �������� �� ����������. ��������� ��������� �� ����������� ������ �����������.
void list_sentence_show_el_value_after_pointer(list_sentence* list) {
	//�������� �� ������� � ������
	if (list_sentence_access_check(list)) {
		//�������� ������ �� �������
		if (list_sentence_check_for_empty_list_no_comment(list)) {
			//�������� �� ������ ��� ��������� ������
			if (list_sentence_check_for_errors_in_memory_allocation(list)) {
				if (list->work_pointer->next == NULL) {
					//������ ���������
					message_about_pointers_at_the_end_of_the_list();
				}
				else {
					cout << endl;
					//�������� ��������� �� ������, ������� ���� �����������
					list_word* list_word = list->work_pointer->next->list_word;
					//������ ������
					print_sentence(list_word);
				}
			}
		}
	}
}
//������� ������������ �������� �������� �� ����������. ��������� ��������� �� ����������� ������ �����������.
void list_sentence_show_el_value_before_pointer(list_sentence* list) {
	//�������� �� ������� � ������
	if (list_sentence_access_check(list)) {
		//�������� ������ �� �������
		if (list_sentence_check_for_empty_list_no_comment(list)) {
			//�������� �� ������ ��� ��������� ������
			if (list_sentence_check_for_errors_in_memory_allocation(list)) {
				if (list->work_pointer->last == NULL) {
					//������ ���������
					message_about_pointers_in_the_beginning_of_the_list();
				}
				else {
					cout << endl;
					//�������� ��������� �� ������, ������� ���� �����������
					list_word* list_word = list->work_pointer->last->list_word;
					//������� ������� ��������� ��� ����� ������
					word_cell* work_pointer_list_word = list_word->link_to_start;
					//�������� ������
					while (work_pointer_list_word != NULL) {
						//������� ��������� �� �����
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
//������� ������ ������������ ��������. ��������� ��������� �� ����������� ������ �����������
void print_saved_item(list_sentence* list) {
	//�������� ������� ������� 
	cout << endl;
	char massive[] = "����������� ������� ������:\0";
	//������ ���������
	message_about(massive);
	list_word* saved_list_word = list->saved_item;
	//��������� �� ������ ������� ������������ ������
	word_cell* work_pointer_saved_list_word = saved_list_word->link_to_start;
	//�������� �����������
	while (work_pointer_saved_list_word != NULL) {
		//������� ��������� �� �����
		char* word = work_pointer_saved_list_word->word;
		cout << word << " ";
		work_pointer_saved_list_word = work_pointer_saved_list_word->next;
	}
	cout << endl;
}
//������� ���������� ����������� (���������� ������ ����). ��������� ��������� �� ����������� ������ ����
list_word* save_item_pointer(list_word* list) {
	//������� ��������� �� ������, ���� �������� ������� �������
	list_word* saved_list_word = (list_word*)malloc(sizeof(list_word));
	if (saved_list_word == NULL) {
		return NULL;
	}
	else {
		//���������� ��������� �������� ������ ����
		list_word_initialize(saved_list_word);
		//������� ������� ��������� ��� ������������ ������
		word_cell* work_pointer_saved_list_word = NULL;
		//������� ������� ��������� ��� ������, ������� ����� ����������
		word_cell* work_pointer_save_item = list->link_to_start;
		//�������� �����������
		while (work_pointer_save_item != NULL) {
			char* word = work_pointer_save_item->word;
			int number_letters = 0;
			for (int i = 0; word[i] != '\0'; i++) {
				number_letters++;
			}
			number_letters++;
			//�������� ������
			char* copy_word = (char*)calloc(number_letters, sizeof(char));
			//�������� �� ������ ��� ��������� ������
			if (copy_word == NULL) {
				return NULL;
			}
			else {
				//�������� �����
				for (int i = 0; i <= number_letters; i++) {
					copy_word[i] = word[i];
				}
				//��������� ������ ��� ������ ������
				word_cell* copy_word_cell = (word_cell*)malloc(sizeof(word_cell));
				//�������� �� ������ ��� ��������� ������
				if (copy_word_cell == NULL) {
					return NULL;
				}
				else {
					//��������� ������ �������
					if (work_pointer_saved_list_word == NULL) {
						saved_list_word->link_to_start = copy_word_cell;
						saved_list_word->work_pointer = copy_word_cell;
						work_pointer_saved_list_word = copy_word_cell;
						copy_word_cell->word = copy_word;
						copy_word_cell->next = NULL;
					}
					else {
						//�������� n �������
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
//������� ������ �������� ������ �� ����������. ��������� ��������� �� ����������� ������ �����������.
void list_sentence_take_item_after(list_sentence* list) {
	//�������� �� ������� � ������
	if (list_sentence_access_check(list)) {
		//�������� ������ �� �������
		if (list_sentence_check_for_empty_list_no_comment(list)) {
			//�������� �� ������ ��� ��������� ������
			if (list_sentence_check_for_errors_in_memory_allocation(list)) {
				if (list->work_pointer->next == NULL) {
					//������ ���������
					message_about_pointers_at_the_end_of_the_list();
				}
				else {
					//�������� �� ����� ����������� ��������
					if ((list->saved_item) != NULL) {
						list_word* delete_saved_item = list->saved_item;
						//������� ������
						clear_word_list(delete_saved_item);
						free(delete_saved_item);
						list->saved_item = NULL;
					}
					//������� ��������� �� ������, ������� ��� ���� ���������
					list_word* save_item = list->work_pointer->next->list_word;
					//��������� ������� 
					list->saved_item = save_item_pointer(save_item);
					//�������� �� ������ ��������� ������
					if (list->saved_item == NULL) {
						list->memory_error = true;
					}
					else {
						//������� ������� ����� ���������
						list_sentence_delete_item_after(list);
						//������ ������������ ��������
						print_saved_item(list);
					}
				}
			}
		}
	}
}
//������� ������ �������� ������ �� ����������. ��������� ��������� �� ����������� ������ �����������.
void list_sentence_take_item_before(list_sentence* list) {
	//�������� �� ������� � ������
	if (list_sentence_access_check(list)) {
		//�������� ������ �� �������
		if (list_sentence_check_for_empty_list_no_comment(list)) {
			//�������� �� ������ ��� ��������� ������
			if (list_sentence_check_for_errors_in_memory_allocation(list)) {
				//�������� ���������� �������� ���������
				if (list->work_pointer->last == NULL) {
					//������ ���������
					message_about_pointers_in_the_beginning_of_the_list();
				}
				else {
					//�������� ��  ����� ����������� ��������
					if ((list->saved_item) != NULL) {
						list_word* delete_saved_item = list->saved_item;
						//������� ������
						clear_word_list(delete_saved_item);
						free(delete_saved_item);
						list->saved_item = NULL;
					}
					//������� ��������� �� ������, ������� ��� ���� ���������
					list_word* save_item = list->work_pointer->last->list_word;
					//��������� �������
					list->saved_item = save_item_pointer(save_item);
					//�������� �� ������ ��������� ������
					if (list->saved_item == NULL) {
						list->memory_error = true;
					}
					else {
						//������� ������� ����� ���������
						list_sentence_delete_item_before(list);
						//������ ������������ ��������
						print_saved_item(list);
					}
				}
			}
		}
	}
}
//������ ������ �����������. ��������� ��������� �� ������ �����������
void print_list_sentence(list_sentence* list) {
	//��������� �� ������ ������ �����������
	sentence_cell* pointer_sentence = list->link_to_start;
	//��������� �� ������ ������ ���� (������ �����������->������ ����)
	list_word* pointer_list_word = NULL;
	//��������� �� ���� (������ �����������->������ ����->�����)
	word_cell* pointer_word = NULL;
	int number = 0;
	//�������� ������
	while (pointer_sentence != NULL) {
		number++;
		cout << number << ". ";
		//��������� �� ������ ������ ���� (������ �����������->������ ����)
		pointer_list_word = pointer_sentence->list_word;
		//��������� �� ���� (������ �����������->������ ����->�����)
		pointer_word = pointer_list_word->link_to_start;
		//�������� ������
		while (pointer_word != NULL) {
			cout << pointer_word->word << " ";
			pointer_word = pointer_word->next;
		}
		pointer_sentence = pointer_sentence->next;
		cout << endl;
	}
	cout << endl;
}
//������� ���������� ������ �����������. ��������� ��������� �� ����������� ������ �����������.
void list_sentence_print(list_sentence* list) {
	//�������� �� ������� � ������
	if (list_sentence_access_check(list)) {
		//�������� ������ �� �������
		if (list_sentence_check_for_empty_list_no_comment(list)) {
			//�������� �� ������ ��� ��������� ������
			if (list_sentence_check_for_errors_in_memory_allocation(list)) {
				//��������� �� ������ ������ �����������
				sentence_cell* pointer_sentence = list->link_to_start;
				//��������� �� ������ ������ ���� (������ �����������->������ ����)
				list_word* pointer_list_word = NULL;
				//��������� �� ���� (������ �����������->������ ����->�����)
				word_cell* pointer_word = NULL;
				int number_of_sentence = 0;
				int number_of_sentence_work_pointer = 0;
				cout << endl;
				char massive[] = "������ ������ ����������� � ������ �������...\0";
				//������ ���������
				message_about(massive);
				//�������� ������ � ������ �������
				while (pointer_sentence != NULL) {
					number_of_sentence++;
					//���������� ����� ����������� �� ������� ��������� ������� ����������
					if (pointer_sentence == list->work_pointer) {
						number_of_sentence_work_pointer = number_of_sentence;
					}
					cout << number_of_sentence << ". ";
					//��������� �� ������ ������ ���� (������ �����������->������ ����)
					pointer_list_word = pointer_sentence->list_word;
					//��������� �� ���� (������ �����������->������ ����->�����)
					pointer_word = pointer_list_word->link_to_start;
					//�������� ������
					while (pointer_word != NULL) {
						cout << pointer_word->word << " ";
						pointer_word = pointer_word->next;
					}
					pointer_sentence = pointer_sentence->next;
					cout << endl;
				}
				cout << "������ ������ ����������� ���������..." << endl;
				//�������� �������� �������� ���������
				cout << endl << "������� ��������� ��������� �� ��������: " << endl;
				cout << number_of_sentence_work_pointer << ". ";
				pointer_sentence = list->work_pointer;
				//��������� �� ������ ������ ���� (������ �����������->������ ����)
				pointer_list_word = pointer_sentence->list_word;
				//��������� �� ���� (������ �����������->������ ����->�����)
				pointer_word = pointer_list_word->link_to_start;
				//�������� ������
				while (pointer_word != NULL) {
					cout << pointer_word->word << " ";
					pointer_word = pointer_word->next;
				}
				cout << endl << endl;
				//������ � �������� �������
				pointer_sentence = list_sentence_go_to_bottom(list);
				//��������� �� ������ ������ ���� (������ �����������->������ ����)
				pointer_list_word = NULL;
				//��������� �� ���� (������ �����������->������ ����->�����)
				pointer_word = NULL;
				cout << endl;
				char massive_2[] = "������ ������ ����������� � �������� �������...\0";
				message_about(massive_2);
				//�������� ������ � �������� �������
				while (pointer_sentence != NULL) {
					//����������� ����� ����������� �� ������� ��������� ������� ���������
					if (pointer_sentence == list->work_pointer) {
						number_of_sentence_work_pointer = number_of_sentence;
					}
					cout << number_of_sentence << ". ";
					//��������� �� ������ ������ ���� (������ �����������->������ ����)
					pointer_list_word = pointer_sentence->list_word;
					//��������� �� ���� (������ �����������->������ ����->�����)
					pointer_word = pointer_list_word->link_to_start;
					//�������� ������
					while (pointer_word != NULL) {
						cout << pointer_word->word << " ";
						pointer_word = pointer_word->next;
					}
					pointer_sentence = pointer_sentence->last;
					number_of_sentence--;
					cout << endl;
				}
				cout << "������ ������ ����������� ���������..." << endl;
				//�������� �������� �������� ���������
				cout << endl << "������� ��������� ��������� �� ��������: " << endl;
				cout << number_of_sentence_work_pointer << ". ";
				pointer_sentence = list->work_pointer;
				//��������� �� ������ ������ ���� (������ �����������->������ ����)
				pointer_list_word = pointer_sentence->list_word;
				//��������� �� ���� (������ �����������->������ ����->�����)
				pointer_word = pointer_list_word->link_to_start;
				//�������� ������
				while (pointer_word != NULL) {
					cout << pointer_word->word << " ";
					pointer_word = pointer_word->next;
				}
				cout << endl << endl;
			}
		}
	}
}
//������� �������� �������� �������� �� ����������. ��������� ��������� �� ����������� ������ �����������.
void list_sentence_change_element_value_after_pointer(list_sentence* list) {
	//�������� �� ������� � ������
	if (list_sentence_access_check(list)) {
		//�������� ������ �� �������
		if (list_sentence_check_for_empty_list_no_comment(list)) {
			//�������� �� ������ ��� ��������� ������
			if (list_sentence_check_for_errors_in_memory_allocation(list)) {
				//�������� ���������� ���������
				if (list->work_pointer->next == NULL) {
					//������ ���������
					message_about_pointers_at_the_end_of_the_list();
				}
				else {
					/*
					char massive[] = "�������� �������� �������� �� ����������!\0";
					message_about(massive);
					//���������� �������� � �������
					cout << endl << "������� �����������: ";
					list_word* new_value = take_sentence_from_console();
					if (new_value == NULL) {
						list->memory_error = true;
					}
					else {
						list->work_pointer->next->list_word = new_value;
					}
					*/
					//���������� �� ������� ����
					go_to_the_lower_level_next(list, list->work_pointer);
				}
			}
		}
	}
}
//������� �������� �������� �������� �� ����������. ��������� ��������� �� ����������� ������ �����������.
void list_sentence_change_element_value_before_pointer(list_sentence* list) {
	//�������� �� ������� � ������
	if (list_sentence_access_check(list)) {
		//�������� ������ �� �������
		if (list_sentence_check_for_empty_list_no_comment(list)) {
			//�������� �� ������ ��� ��������� ������
			if (list_sentence_check_for_errors_in_memory_allocation(list)) {
				//�������� ���������� ���������
				if (list->work_pointer->last == NULL) {
					//������ ���������
					message_about_pointers_in_the_beginning_of_the_list();
				}
				else {
					char massive[] = "�������� �������� �������� �� ���������!\0";
					//������ ���������
					message_about(massive);
					/*
					//���������� �������� � �������
					cout << endl << "������� �����������: ";
					list_word* new_value = take_sentence_from_console();
					if (new_value == NULL) {
						list->memory_error = true;
					}
					else {
						list->work_pointer->last->list_word = new_value;
					}
					*/
					//���������� �� ������� ����
					go_to_the_lower_level_last(list, list->work_pointer);
				}
			}
		}
	}
}
//������� ������������ ������ �� ��������. ��������� ��������� �� ����������� ������ �����������.
void list_sentence_finish_work(list_sentence* list) {
	//�������� �� ������ ������
	if (list->start == true) {
		//�������� �� ������ ��� ��������� ������
		if (list_sentence_check_for_errors_in_memory_allocation(list)) {
			char massive[] = "������ �� ������� ���������!\0";
			//������ ���������
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
//������� ���������� ������ � ��������� �������� �������� ���������. ��������� ��������� �� ����������� ������ �����������
void list_sentence_print_(list_sentence* list) {
	//�������� �� ������ � ������
	if (list->start == true) {
		//�������� ������ �� �������
		if (list->link_to_start != NULL) {
			//�������� �� ������ ��� ��������� ������
			if (list->memory_error != true) {
				//������ ������
				list_sentence_print(list);
			}
		}
	}
}
//������� ����������� ���������� ������ �� �������. ��������� ��������� �� ����������� ������. ���������� true - ���� ������ �� ������� ���������, false - ���� ������ �� ������� �� ���������.
bool list_sentence_back(list_sentence* list) {
	//�������� �� ������ ������
	if (list->start == true) {
		char massive[] = "��� ����������� ����� ��������� �������� '��������� ������ �� �������'\0";
		//������ ���������
		message_about(massive);
		return false;
	}
	return true;
}
//���������� �� ������� ����. ��������� ��������� �� ������ ����������� � ������� ���������
void go_to_the_lower_level(list_sentence* list, sentence_cell* check) {
	//�������� �� ������� � ������
	if (list_sentence_access_check(list)) {
		//�������� ������ �� �������
		if (list_sentence_check_for_empty_list_no_comment(list)) {
			//�������� �� ������ ��� ��������� ������
			if (list_sentence_check_for_errors_in_memory_allocation(list)) {
				sentence_cell* cell_work_pointer = NULL;
				//�������� ��������� �� �������
				if (check != NULL) {
					cell_work_pointer = check;
				}
				else {
					cell_work_pointer = list->work_pointer;
				}
				list_word* word_list = cell_work_pointer->list_word;
				//����� ���� ������ ����
				list_word_menu(word_list);
				//��������� ����������� ��������� ������ ����
				if (cell_work_pointer->last == NULL && cell_work_pointer->next == NULL && word_list->link_to_start == NULL) {
					free(cell_work_pointer);
					list->link_to_start = NULL;
					list->work_pointer = NULL;
				}
				else {
					if (word_list->link_to_start == NULL) {
						//���� � ������
						if (cell_work_pointer->last == NULL) {
							sentence_cell* next_cell = cell_work_pointer->next;
							list->link_to_start = next_cell;
							next_cell->last = NULL;
							list->work_pointer = list->link_to_start;
						}
						else {
							//���� � ����� ������
							sentence_cell* cursor = list->link_to_start;
							if (cell_work_pointer->next == NULL) {
								while (cursor->next != cell_work_pointer) {
									cursor = cursor->next;
								}
								cursor->next = NULL;
								list->work_pointer = list->link_to_start;
							}
							else {
								//�� n �������� ������
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
//���������� �� ������� ����. ��������� ��������� �� ������ ����������� � ������� ���������
void go_to_the_lower_level_last(list_sentence* list, sentence_cell* check) {
	//�������� �� ������� � ������
	if (list_sentence_access_check(list)) {
		//�������� ������ �� �������
		if (list_sentence_check_for_empty_list_no_comment(list)) {
			//�������� �� ������ ��� ��������� ������
			if (list_sentence_check_for_errors_in_memory_allocation(list)) {
				sentence_cell* cell_work_pointer = NULL;
				//��������� ������ �� �������
				if (check != NULL) {
					cell_work_pointer = check->last;
				}
				else {
					cell_work_pointer = list->work_pointer;
				}
				list_word* word_list = cell_work_pointer->list_word;
				//�������� ���� ������ ����
				list_word_menu(word_list);
				//��������� ����������� ��������� ������ ����
				if (cell_work_pointer->last == NULL && cell_work_pointer->next == NULL && word_list->link_to_start == NULL) {
					free(cell_work_pointer);
					list->link_to_start = NULL;
					list->work_pointer = NULL;
				}
				else {
					if (word_list->link_to_start == NULL) {
						//���� � ������
						if (cell_work_pointer->last == NULL) {
							sentence_cell* next_cell = cell_work_pointer->next;
							list->link_to_start = next_cell;
							next_cell->last = NULL;
							list->work_pointer = list->link_to_start;
						}
						else {
							//���� � ����� ������
							sentence_cell* cursor = list->link_to_start;
							if (cell_work_pointer->next == NULL) {
								while (cursor->next != cell_work_pointer) {
									cursor = cursor->next;
								}
								cursor->next = NULL;
								list->work_pointer = list->link_to_start;
							}
							else {
								//�� n �������� ������
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
//���������� �� ������� ����. ��������� ��������� �� ������ ����������� � ������� ���������
void go_to_the_lower_level_next(list_sentence* list, sentence_cell* check) {
	//�������� �� ������� � ������
	if (list_sentence_access_check(list)) {
		//�������� ������ �� �������
		if (list_sentence_check_for_empty_list_no_comment(list)) {
			//�������� �� ������ ��� ��������� ������
			if (list_sentence_check_for_errors_in_memory_allocation(list)) {
				sentence_cell* cell_work_pointer = NULL;
				//��������� ������ �� �������
				if (check != NULL) {
					cell_work_pointer = check->next;
				}
				else {
					cell_work_pointer = list->work_pointer;
				}
				list_word* word_list = cell_work_pointer->list_word;
				//��������� ���� ������ �����������
				list_word_menu(word_list);
				//��������� ����������� ��������� ������ ����
				if (cell_work_pointer->last == NULL && cell_work_pointer->next == NULL && word_list->link_to_start == NULL) {
					free(cell_work_pointer);
					list->link_to_start = NULL;
					list->work_pointer = NULL;
				}
				else {
					if (word_list->link_to_start == NULL) {
						//���� � ������
						if (cell_work_pointer->last == NULL) {
							sentence_cell* next_cell = cell_work_pointer->next;
							list->link_to_start = next_cell;
							next_cell->last = NULL;
							list->work_pointer = list->link_to_start;
						}
						else {
							//���� � ����� ������
							sentence_cell* cursor = list->link_to_start;
							if (cell_work_pointer->next == NULL) {
								while (cursor->next != cell_work_pointer) {
									cursor = cursor->next;
								}
								cursor->next = NULL;
								list->work_pointer = list->link_to_start;
							}
							else {
								//�� n �������� ������
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
//�������� �� ������� ������ ������� ������. ��������� ��������� �� ������ �����������
sentence_cell* check_for_emptiness(list_sentence* list) {
	//�������� �� ������� � ������
	if (list_sentence_access_check(list)) {
		//�������� ������ �� �������
		if (list_sentence_check_for_empty_list_no_comment(list)) {
			//�������� �� ������ ��� ��������� ������
			if (list_sentence_check_for_errors_in_memory_allocation(list)) {
				sentence_cell* work_pointer = list->link_to_start;
				//��������� ������ �� �������
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
//���� ������������ ������ ����
void list_sentence_menu(list_sentence* list_sentence) {
	//����������, ������� ������ � ���� ����� ������������
	int user_choice;
	//����������, ������� ������� ���������� � ������� ������������ �����
	bool back = false;
	//������� ���� � ��� ���, ���� ������������ �� ������� ����� �����
	while (!back) {
		//�������� �� ������ ��� ��������� ������
		if (list_sentence->memory_error == true) {
			//������ ����������
			memory_allocation_error_message();
			system("pause");
			break;
		}
		char massive[] = "�� ���������� � �������: ������ ������� -> ������ �����������\0";
		//������ ���������
		message_about(massive);
		//������ ������
		print_list_sentence(list_sentence);
		cout << "����" << endl;
		cout << " 1. ������ ������ �� �������." << endl;
		cout << " 2. ������� ������ ������." << endl;
		cout << " 3. ��������: ������ ���� / ������ �� ����." << endl;
		cout << " 4. ���������� ������� ��������� � ������ ������." << endl;
		cout << " 5. ���������� ������� ��������� � ����� ������." << endl;
		cout << " 6. ��������: ������� ��������� � ������ ������?" << endl;
		cout << " 7. ��������: ������� ��������� � ����� ������?" << endl;
		cout << " 8. ����������� ������� ��������� ������ ������." << endl;
		cout << " 9. ����������� ������� ��������� ������ �����." << endl;
		cout << "10. �������� �������� �������� ������ �� ���������." << endl;
		cout << "11. �������� �������� �������� ������ �� ����������." << endl;
		cout << "12. ������� ������� ������ �� ���������." << endl;
		cout << "13. ������� ������� ������ �� ����������." << endl;
		cout << "14. ����� ������� ������ �� ���������." << endl;
		cout << "15. ����� ������� ������ �� ����������." << endl;
		cout << "16. �������� �������� �������� ������ �� ���������." << endl;
		cout << "17. �������� �������� �������� ������ �� ����������." << endl;
		cout << "18. �������� ������� �� ���������." << endl;
		cout << "19. �������� ������� �� ����������." << endl;
		cout << "20. ����������� ��������� ������." << endl;
		cout << "21. ��������� ������ �� ��������." << endl;
		cout << "22. ������� �� ������� ���� (�� �������� ���������): ������ ����������� -> ������ ����" << endl;
		cout << "23. ������� �� ������� ����: ������ ������� <- ������ �����������." << endl;
		cout << endl << "�������� ���� �� ������� ��� ����������� ������: ";
		request_verification(&user_choice, 1, 23);
		cout << endl;
		sentence_cell* check = NULL;
		switch (user_choice) {
		case 1:
			//������ ������ �� �������.
			list_sentence_begin_work(list_sentence);
			break;
		case 2:
			// ������� ������ ������.
			list_sentence_make_the_list_empty(list_sentence);
			break;
		case 3:
			//��������: ������ ���� / ������ �� ����.
			list_sentence_check_for_empty_list(list_sentence);
			break;
		case 4:
			//���������� ������� ��������� � ������ ������.
			list_sentence_set_cursor_to_beginning(list_sentence);
			//������ ������
			list_sentence_print_(list_sentence);
			break;
		case 5:
			//���������� ������� ��������� � ����� ������.
			list_sentence_set_cursor_to_the_end(list_sentence);
			//������ ������
			list_sentence_print_(list_sentence);
			break;
		case 6:
			//��������: ������� ��������� � ������ ������?
			list_sentence_check_for_working_pointer_to_beginning(list_sentence);
			//������ ������
			list_sentence_print_(list_sentence);
			break;
		case 7:
			//��������: ������� ��������� � ����� ������?
			list_sentence_check_for_working_pointer_to_end(list_sentence);
			//������ ������
			list_sentence_print_(list_sentence);
			break;
		case 8:
			//������ ������
			list_sentence_print_(list_sentence);
			//����������� ������� ��������� ������ ������.
			list_sentence_move_pointer_forward(list_sentence);
			//������ ������
			list_sentence_print_(list_sentence);
			break;
		case 9:
			//������ ������
			list_sentence_print_(list_sentence);
			//����������� ������� ��������� ������ �����.
			list_sentence_move_pointer_back(list_sentence);
			//������ ������
			list_sentence_print_(list_sentence);
			break;
		case 10:
			//������ ������
			list_sentence_print_(list_sentence);
			//�������� �������� �������� ������ �� ���������.
			list_sentence_show_el_value_before_pointer(list_sentence);
			break;
		case 11:
			//������ ������
			list_sentence_print_(list_sentence);
			//�������� �������� �������� ������ �� ����������.
			list_sentence_show_el_value_after_pointer(list_sentence);
			break;
		case 12:
			//������ ������
			list_sentence_print_(list_sentence);
			//������� ������� ������ �� ���������.
			list_sentence_delete_item_before(list_sentence);
			//������ ������
			list_sentence_print_(list_sentence);
			break;
		case 13:
			//������ ������
			list_sentence_print_(list_sentence);
			//������� ������� ������ �� ����������.
			list_sentence_delete_item_after(list_sentence);
			//������ ������
			list_sentence_print_(list_sentence);
			break;
		case 14:
			//������ ������
			list_sentence_print_(list_sentence);
			//����� ������� ������ �� ���������.
			list_sentence_take_item_before(list_sentence);
			//������ ������
			list_sentence_print_(list_sentence);
			break;
		case 15:
			//������ ������
			list_sentence_print_(list_sentence);
			// ����� ������� ������ �� ����������. 
			list_sentence_take_item_after(list_sentence);
			//������ ������
			list_sentence_print_(list_sentence);
			break;
		case 16:
			//������ ������
			list_sentence_print_(list_sentence);
			//�������� �������� �������� ������ �� ���������.
			list_sentence_change_element_value_before_pointer(list_sentence);
			//������ ������
			list_sentence_print_(list_sentence);
			break;
		case 17:
			//������ ������
			list_sentence_print_(list_sentence);
			//�������� �������� �������� ������ �� ����������.
			list_sentence_change_element_value_after_pointer(list_sentence);
			//������ ������
			list_sentence_print_(list_sentence);
			break;
		case 18:
			//������ ������
			list_sentence_print_(list_sentence);
			//�������� ������� �� ���������.
			list_sentence_add_item_last(list_sentence);
			//����� ������� �����
			check = check_for_emptiness(list_sentence);
			if (check != NULL) {
				//���������� �� ������� ����
				go_to_the_lower_level(list_sentence, check);
			}
			else {
				//������ ������
				list_sentence_print_(list_sentence);
			}
			break;
		case 19:
			//������ ������
			list_sentence_print_(list_sentence);
			//�������� ������� �� ����������.
			list_sentence_add_item_next(list_sentence);
			//����� ������� �����
			check = check_for_emptiness(list_sentence);
			if (check != NULL) {
				//���������� �� ������� ����
				go_to_the_lower_level(list_sentence, check);
				//������ ������
				list_sentence_print_(list_sentence);
			}
			else {
				//������ ������
				list_sentence_print_(list_sentence);
			}
			break;
		case 20:
			//����������� ��������� ������.
			list_sentence_print(list_sentence);
			break;
		case 21:
			//��������� ������ �� ��������.
			list_sentence_finish_work(list_sentence);
			break;
		case 22:
			//���������� �� ������� ����
			go_to_the_lower_level(list_sentence, NULL);
			//������ ������
			list_sentence_print_(list_sentence);
			break;
		case 23:
			//�����.
			back = list_sentence_back(list_sentence);
			break;
		}
		system("pause");
		system("cls");
	}
}