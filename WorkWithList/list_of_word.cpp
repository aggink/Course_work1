//����������� �������� ������ � ���������� �������
#include"Header.h"


//�������� ��������� �������� 
int getValue(int* i)
{
	while (true) // ���� ������������ �� ��� ���, ���� ������������ �� ������ ���������� ��������
	{
		std::cin >> *i;
		// �������� �� ���������� ����������
		if (std::cin.fail()) // ���� ���������� ���������� ��������� ����������
		{
			std::cin.clear(); // ���������� cin � '�������' ����� ������
			std::cin.ignore(32767, '\n'); // � ������� �������� ����������� ����� �� �������� ������
			cout << endl << "������������ ���� ������." << endl << "�������� ���� �� ������� ��� ����������� ������: ";
		}
		else
		{
			std::cin.ignore(32767, '\n'); // ������� ������ ��������
			return 0;
		}
	}
}
//�������� ������� � ����. ��������� 1 - ����� ����������, 2 - ������ ��������� 3 - ����� ���������
void request_verification(int* i, int range_1, int range_2) {
	while (true) {
		//��������� ������ � ������������
		getValue(i);
		if (*i < range_1 || *i > range_2) {
			cout << endl << "������������ ���� ������." << endl << "�������� ���� �� ������� ��� ����������� ������: ";
		}
		else {
			break;
		}
	}
}
//������� ����������� ������ � ������. ��������� ��������� �� ����������� ������ ����. ��������� true - ���� ������ ����, false - ���� ������� ���
bool list_word_access_check(list_word* list) {
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
//������� ����������� ������ �� �������. ��������� ��������� �� ����������� ������ ����. ���������� true - ���� ������ ����, false - ���� � ������ ���� ������
bool list_word_check_for_empty_list_no_comment(list_word* list) {
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
//������� ����������� ������ � ��������� ������. ��������� ��������� �� ����������� ������ ����. ���������� true - ���� ������ ���, false - ���� ������ ����
bool list_word_check_for_errors_in_memory_allocation(list_word* list) {
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
//������� ����������� ����� � �������. ���������� NULL � ������ �������, ��� ��������� �� ������ �������� � ������ ������
char* take_word_from_console() {
	//��������� �� ������ ���������� �����
	char* word;
	//���������� ��������� ��������
	int number_of_characters = 0;
	number_of_characters++;
	//��������� ������ ��� ������
	word = (char*)calloc(number_of_characters, sizeof(char));
	//�������� �� ������ ��� ��������� ������
	if (word == NULL) {
		return word;
	}
	//���������� �������� � �������
	cout << "������� �����: " ;
	word[number_of_characters - 1] = getchar();
	//��������� ������ � �������
	while (word[number_of_characters - 1] != '\n') {
		number_of_characters++;
		//������� ����� ��������� �� ������
		char* new_word = word;
		//���������� ������ � ������
		new_word = (char*)realloc(word, number_of_characters * sizeof(char));
		//�������� �� ������ ��� ��������� ������
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
//������� ��������� ������� ������. ��������� ��������� �� ����������� �������
void delete_cell_to_word_list(list_word* list) {
	word_cell* delete_cell = list->work_pointer->next;
	//���������� ��������� ���������� ��������
	if (delete_cell->next == NULL) {
		//������� ��������� ������� ������
		list->work_pointer->next = NULL;
	}
	else {
		//������� n ������� ������
		list->work_pointer->next = delete_cell->next;
	}
	free(delete_cell->word);
	free(delete_cell);
}
//������� ��������� ������� ������ ����� ���������. ��������� ��������� �� ����������� ������ ����.
void list_word_delete_item(list_word* list) {
	//�������� ������� � ������
	if (list_word_access_check(list)) {
		//�������� ������ �� �������
		if (list_word_check_for_empty_list_no_comment(list)) {
			//�������� �� ������ ��� ���������� ������
			if (list_word_check_for_errors_in_memory_allocation(list)) {
				if (list->work_pointer->next == NULL) {
					//������ ���������
					message_about_pointers_at_the_end_of_the_list();
				}
				else {
					//������� �������
					delete_cell_to_word_list(list);
				}
			}
		}
	}
}
//������� ��������� ������ ����
void clear_word_list(list_word* list) {
	list->work_pointer = list->link_to_start;
	//������� ������ �� ������ � ����������� ���������� ������
	while (list->work_pointer->next != NULL) {
		//������� �������
		delete_cell_to_word_list(list);
	}
	free(list->work_pointer->word);
	free(list->work_pointer);
	//�������� �� ������� ������������ ��������
	if ((list->saved_item) != NULL) {
		free(list->saved_item);
	}
	list->link_to_start = NULL;
	list->work_pointer = NULL;
	list->saved_item = NULL;
}
//������� ����������� �������� �� �������. ��������� ��������� �� ����������� ������ ����
void list_word_begin_work(list_word* list) {
	list->start = true;
	list->memory_error = false;
	list->work_pointer = list->link_to_start;
}
//������� ����������� ������ �� �������. ��������� ��������� �� ����������� ������ ����.
void list_word_check_for_empty_list(list_word* list) {
	//�������� ������� � ������
	if (list_word_access_check(list)) {
		//�������� �� ������ ��� ��������� ������
		if (list_word_check_for_errors_in_memory_allocation(list)) {
			//�������� ������ �� �������
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


//������� ����������� ������� �� ����������. ��������� ��������� �� ����������� ������ ����.
void list_word_add_item(list_word* list) {
	//�������� ������� � ������
	if (list_word_access_check(list)){
		//�������� �� ������ ��������� ������
		if (list_word_check_for_errors_in_memory_allocation(list)) {
			if (list->link_to_start == NULL) {
				//�������� ������ �������
				word_cell* new_cell = (word_cell*)malloc(sizeof(word_cell));
				//�������� �� ������ � ��������� ������
				if (new_cell == NULL) {
					list->memory_error = true;
				}
				else {
					//��������� ������ � �������
					new_cell->word = take_word_from_console();
					//�������� �� ������ ��������� ������
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
				//��������� ������� � ����� ������
				word_cell* new_cell = (word_cell*)malloc(sizeof(word_cell));
				//�������� �� ������ ��������� ������
				if (new_cell == NULL) {
					list->memory_error = true;
				}
				else {
					//��������� ������ � �������
					new_cell->word = take_word_from_console();
					//�������� �� ������ ��������� ������
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
				//��������� ������� � �������� ������
				word_cell* new_cell = (word_cell*)malloc(sizeof(word_cell));
				//�������� �� ������ ��������� ������
				if (new_cell == NULL) {
					list->memory_error = true;
				}
				else {
					//��������� ������ � �������
					new_cell->word = take_word_from_console();
					//�������� �� ������ ��������� ������
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
//������� ��������������� ������� ��������� � ������ ������. ��������� ��������� �� ����������� ������ ����.
void list_word_set_cursor_to_beginning(list_word* list) {
	//�������� ������� � ������
	if (list_word_access_check(list)) {
		//�������� ������ �� �������
		if (list_word_check_for_empty_list_no_comment(list)) {
			//�������� �� ������ ��� ���������� ������
			if (list_word_check_for_errors_in_memory_allocation(list)) {
				list->work_pointer = list->link_to_start;
			}
		}
	}
}
//������� �������� ������ ������. ��������� ��������� �� ����������� ������ ����.
void list_word_make_the_list_empty(list_word* list) {
	//�������� ������� � ������
	if (list_word_access_check(list)) {
		//�������� ������ �� �������
		if (list_word_check_for_empty_list_no_comment(list)) {
			//�������� �� ������ ��� ���������� ������
			if (list_word_check_for_errors_in_memory_allocation(list)) {
				//������� ������
				clear_word_list(list);
				char massive[] = "������ ����!\0";
				//����� ���������
				message_about(massive);
			}
		}
	}
}
//������� ����������� ���������� �������� ���������. ��������� ��������� �� ����������� ������ ����.
void list_word_check_for_working_pointer(list_word* list) {
	//�������� ������� � ������
	if (list_word_access_check(list)) {
		//�������� ������ �� �������
		if (list_word_check_for_empty_list_no_comment(list)) {
			//�������� �� ������ ��� ���������� ������
			if (list_word_check_for_errors_in_memory_allocation(list)) {
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
//������� ��������� ��������� ������. ��������� ��������� �� ����������� ������ ����.
void list_word_move_pointer_forward(list_word* list) {
	//�������� ������� � ������
	if (list_word_access_check(list)) {
		//�������� ������ �� �������
		if (list_word_check_for_empty_list_no_comment(list)) {
			//�������� �� ������ ��� ���������� ������
			if (list_word_check_for_errors_in_memory_allocation(list)) {
				//�������� ����������� �������� ���������
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
//������� ������������ �������� �������� �� ����������. ��������� ��������� �� ����������� ������ ����.
void list_word_show_el_value_after_pointer(list_word* list) {
	//�������� ������� � ������
	if (list_word_access_check(list)) {
		//�������� ������ �� �������
		if (list_word_check_for_empty_list_no_comment(list)) {
			//�������� �� ������ ��� ���������� ������
			if (list_word_check_for_errors_in_memory_allocation(list)) {
				//�������� ���������� �������� ���������
				if (list->work_pointer->next == NULL) {
					//������ ���������
					message_about_pointers_at_the_end_of_the_list();
				}
				else {
					cout << "�������� �������� ������: " << list->work_pointer->next->word << endl;
				}
			}
		}
	}
}
//������� ������ �������� ������ �� ����������.��������� ��������� �� ����������� ������ ����.
void list_word_take_item(list_word* list) {
	//�������� ������� � ������
	if (list_word_access_check(list)) {
		//�������� ������ �� �������
		if (list_word_check_for_empty_list_no_comment(list)) {
			//�������� �� ������ ��� ���������� ������
			if (list_word_check_for_errors_in_memory_allocation(list)) {
				if (list->work_pointer->next == NULL) {
					//������ ���������
					message_about_pointers_at_the_end_of_the_list();
				}
				else {
					//�������� �� ������� ��������� ��� ������������ ��������
					if ((list->saved_item) != NULL) {
						free(list->saved_item);
						list->saved_item = NULL;
					}
					char* word = list->work_pointer->next->word;
					int number_letters = 0;
					//������������ ���-�� ��������
					for (int i = 0; word[i] != '\0'; i++) {
						number_letters++;
					}
					number_letters++;
					//�������� ������ 
					char* copy_word = (char*)calloc(number_letters, sizeof(char));
					//�������� �� ������ ��������� ������
					if (copy_word == NULL) {
						list->memory_error = true;
					}
					else {
						//�������� �����
						for (int i = 0; i <= number_letters; i++) {
							copy_word[i] = word[i];
						}
						list->saved_item = copy_word;
						//������� �������
						list_word_delete_item(list);
						char massive[] = "����������� ������� ������:\0";
						//������ ���������
						message_about(massive);
						cout << list->saved_item << endl;
					}
				}
			}
		}
	}
}
//�������� ������. ��������� ��������� �� ������ ����
void print_list_word(list_word* list) {
	word_cell* pointer = list->link_to_start;
	int number = 0;
	//�������� ������
	while (pointer != NULL) {
		number++;
		cout << number << ". ";
		cout << pointer->word;
		pointer = pointer->next;
		cout << endl;
	}
	cout << endl;
}
//������� ���������� ������ ����. ��������� ��������� �� ����������� ������ ����.
void list_word_print(list_word* list) {
	//�������� ������� � ������
	if (list_word_access_check(list)) {
		//�������� ������ �� �������
		if (list_word_check_for_empty_list_no_comment(list)) {
			//�������� �� ������ ��� ���������� ������
			if (list_word_check_for_errors_in_memory_allocation(list)) {
				word_cell* pointer = list->link_to_start;
				cout << endl;
				char massive[] = "�������� ������ ����...\0";
				//������ ���������
				message_about(massive);
				int i = 0;
				int number_work_pointer = 0;
				//�������� ������
				while (pointer != NULL) {
					i++;
					cout << i << ". " << pointer->word << endl;
					//���� ����� �������� ���������
					if (list->work_pointer == pointer) {
						number_work_pointer = i;
					}
					pointer = pointer->next;
				}
				cout << "������� ��������� ��������� �� ��������: " << number_work_pointer << ". " << list->work_pointer->word << endl << endl;
			}
		}
	}
}
//������� �������� �������� �������� �� ����������. ��������� ��������� �� ����������� ������ ����.
void list_word_change_element_value_after_pointer(list_word* list) {
	//�������� ������� � ������
	if (list_word_access_check(list)) {
		//�������� ������ �� �������
		if (list_word_check_for_empty_list_no_comment(list)) {
			//�������� �� ������ ��� ���������� ������
			if (list_word_check_for_errors_in_memory_allocation(list)) {
				//�������� ���������� �������� ���������
				if (list->work_pointer->next == NULL) {
					//������ ���������
					message_about_pointers_at_the_end_of_the_list();
				}
				else {
					char massive[] = "�������� �������� �������� �� ����������!\0";
					//������ ���������
					message_about(massive);
					//��������� ������ � �������
					 char* new_value = take_word_from_console();
					 //�������� �� ������ ��������� ������
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
//������� ������������ ������ �� ��������. ��������� ��������� �� ����������� ������ ����.
void list_word_finish_work(list_word* list) {
	//�������� �� ������ � ������
	if (list->start == true) {
		//�������� �� ������ ��� ��������� ������
		if (list_word_check_for_errors_in_memory_allocation(list)) {
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
//������� ���������� ������ � ��������� �������� �������� ���������. ��������� ��������� �� ����������� ������
void list_word_print_(list_word* list) {
	//�������� �� ������ ������
	if (list->start == true) {
		//�������� ������ �� �������
		if (list->link_to_start != NULL) {
			//�������� �� ������ ��� ��������� ������
			if (list->memory_error != true) {
				//������ ������
				list_word_print(list);
			}
		}
	}
}
//������� ����������� ���������� ������ �� �������. ��������� ��������� �� ����������� ������. ���������� true - ���� ������ �� ������� ���������, false - ���� ������ �� ������� �� ���������.
bool list_word_back(list_word* list) {
	//�������� �� ������ ������
	if (list->start == true) {
		char massive[] = "��� ����������� ����� ��������� �������� '��������� ������ �� �������'";
		//������ ���������
		message_about(massive);
		return false;
	}
	return true;
}
//���� ������������ ������ ����
void list_word_menu(list_word* list_word) {
	//����������, ������� ������ � ���� ����� ������������
	int user_choice;
	//����������, ������� ������� ���������� � ������� ������������ �����
	bool back = false;
	//������� ���� � ��� ���, ���� ������������ �� ������� ����� �����
	while (!back) {
		//�������� �� ������ ��� ��������� ������
		if (list_word->memory_error == true) {
			//������ ���������
			memory_allocation_error_message();
			system("pause");
			break;
		}
		char massive[] = "�� ���������� � �������: ������ ������� -> ������ ����������� -> ������ ����\0";
		//������ ���������
		message_about(massive);
		//������ ������
		print_list_word(list_word);
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
		cout << "14. ������� �� ������� ����: ������ ����������� <- ������ ����." << endl;
		cout << endl << "�������� ���� �� ������� ��� ����������� ������: ";
		//������ ������ � ������������ � �� ��������
		request_verification(&user_choice, 1, 14);
		cout << endl;
		switch (user_choice) {
		case 1:
			//����� ������
			list_word_begin_work(list_word);
			break;
		case 2:
			//������� ������ ������
			list_word_make_the_list_empty(list_word);
			break;
		case 3:
			//�������� ������ �� �������
			list_word_check_for_empty_list(list_word);
			break;
		case 4:
			//������ ������
			list_word_print_(list_word);
			//��������� ������� ��������� � ������
			list_word_set_cursor_to_beginning(list_word);
			//������ ������
			list_word_print_(list_word);
			break;
		case 5:
			//��������� ���������� �������� ��������� �� ����� ������
			list_word_check_for_working_pointer(list_word);
			//������ ������
			list_word_print_(list_word);
			break;
		case 6:
			//������ ������
			list_word_print_(list_word);
			//����������� ��������� ������
			list_word_move_pointer_forward(list_word);
			//������ ������
			list_word_print_(list_word);
			break;
		case 7:
			//������ ������
			list_word_print_(list_word);
			//�������� �������� �������� �� ����������
			list_word_show_el_value_after_pointer(list_word);
			break;
		case 8:
			//������ ������
			list_word_print_(list_word);
			//������� ������� �� ����������
			list_word_delete_item(list_word);
			//������ ������
			list_word_print_(list_word);
			break;
		case 9:
			//������ ������
			list_word_print_(list_word);
			//����� ������� �� ����������
			list_word_take_item(list_word);
			//������ ������
			list_word_print_(list_word);
			break;
		case 10:
			//������ ������
			list_word_print_(list_word);
			//�������� �������� �� ����������
			list_word_change_element_value_after_pointer(list_word);
			//������ ������
			list_word_print_(list_word);
			break;
		case 11:
			//������ ������
			list_word_print_(list_word);
			//�������� �������
			list_word_add_item(list_word);
			//������ ������
			list_word_print_(list_word);
			break;
		case 12:
			//������ ������
			list_word_print(list_word);
			break;
		case 13:
			//��������� ������
			list_word_finish_work(list_word);
			break;
		case 14:
			//�����
			back = list_word_back(list_word);
			break;
		}
		system("pause");
		system("cls");
	}
}