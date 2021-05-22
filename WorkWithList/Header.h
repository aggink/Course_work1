#include<conio.h>
#include<Windows.h>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
//��������� ���������� ��������� �� ������ � �� ��������� ������� ������
struct word_cell {
	//��������� �� ������ ��������
	char* word;
	//��������� �� ��������� �������
	word_cell* next;
};

//������ ����
struct list_word {
	//��������� �� ������ ������
	word_cell* link_to_start = NULL;
	//������� ���������
	word_cell* work_pointer = NULL;
	//���������� ���������� �� ������ ������ �� �������
	bool start = false;
	//����������� �������
	char* saved_item = NULL;
	//����������-���� ��������������� �� ������ � ��������� ������
	bool memory_error = false;
};
//���� ������������ ������ ����
void list_word_menu(list_word* list_word);
//������� ��������� ������� ������. ��������� ��������� �� ����������� �������
void delete_cell_to_word_list(list_word* list);
//������� ��������� ������ ����
void clear_word_list(list_word* list);
//�������� ���������� �������� ����
int getValue(int* i);
//�������� ������� � ����
void request_verification(int* i, int range_1, int range_2);
//������� ���������� ������ ����. ��������� ��������� �� ����������� ������ ����.
void print_list_word(list_word* list);

//������� ����������� �� ���������� �������� �����
bool check_words_for_punctuation(char* word);
//������� ����������� ���� ������ �� ����� ����������
void check_the_entire_list_for_punctuation(list_word* list);
//������� ����������� ���� ����������
void add_punctuation(list_word* list);



//����������� ������ �����������
//��������� ���������� ��������� �� ����������� ������ ���� � �� ��������� ������ ����
struct sentence_cell {
	//��������� �� ������� ������� 
	sentence_cell* last;
	//��������� �� ������ ����
	list_word* list_word;
	//��������� �� ��������� �������
	sentence_cell* next;
};

//������ �����������
struct list_sentence {
	//��������� �� ������ ������
	sentence_cell* link_to_start = NULL;
	//������� ���������
	sentence_cell* work_pointer = NULL;
	//���������� ���������� �� ������ ������ �� �������
	bool start = false;
	//����������� �������
	list_word* saved_item = NULL;
	//����������-���� ��������������� �� ������ � ��������� ������
	bool memory_error = false;
};
//����� ���� ������ �����������
void list_sentence_menu(list_sentence* list_sentence);
//������������� ������ ����
void list_word_initialize(list_word* list);
//������� ��������� ������� ������ �� ���������. ��������� ��������� �� ����������� ������ �����������
void delete_cell_to_sentence_list_before(list_sentence* list);
//������� ��������� ������� ������ ����� ����������. ��������� ��������� �� ����������� ������ �����������
void delete_cell_to_sentence_list_after(list_sentence* list);
//������� ��������� ������ ����
void clear_sentence_list(list_sentence* list);
//������ ������������� ������� 
bool search_character(char c, bool* flag_end_sentence, bool* flag_end_text);
//������� ���������� ����������� (���������� ������ ����). ��������� ��������� �� ����������� ������ ����
list_word* save_item_pointer(list_word* list);


//����������� ������ �������
//��������� ���������� ��������� �� ����������� ������ ����������� � �� ��������� ������ �����������
struct text_cell {
	//��������� �� ������ �����������
	list_sentence* list_sentence;
	//��������� �� ��������� �������
	text_cell* next;
};

//������ �������
struct list_text {
	//��������� �� ������ ������
	text_cell* link_to_start = NULL;
	//������� ���������
	text_cell* work_pointer = NULL;
	//���������� ���������� �� ������ ������ �� �������
	bool start = false;
	//����������� �������
	list_sentence* saved_item = NULL;
	//����������-���� ��������������� �� ������ � ��������� ������
	bool memory_error = false;
};
void list_text_menu(list_text* list_text);
//������������� ������ �����������
void list_sentence_initialize(list_sentence* list);

//��������� ������� �� ��������� ��������� �� �������
//��������� �� ������ ������� � ������
void error_message_at_the_beginning_of_work();
//��������� �� ������ ���������� ������� ������
void error_message_due_to_empty_list();
//��������� �� ������ ��������� ������
void memory_allocation_error_message();
//��������� � ���������� �������� ��������� � ����� ������
void message_about_pointers_at_the_end_of_the_list();
//��������� � ���������� �������� ��������� � ������ ������
void message_about_pointers_in_the_beginning_of_the_list();
//��������� � ������������� ��������� ������ �� �������
void message_about(char massive[]);

//����� �� ������ ������� ���������
void go_to_the_lower_level_last(list_sentence* list, sentence_cell* check);
//����� �� ������ ������� ���������
void go_to_the_lower_level_2(list_text* list, text_cell* check);
//����� �� ������ ������� ���������
void go_to_the_lower_level_next(list_sentence* list, sentence_cell* check);