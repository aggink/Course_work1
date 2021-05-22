#include<conio.h>
#include<Windows.h>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
//структура содержащая указатель на данное и на следующий элемент данных
struct word_cell {
	//указатель на строку символов
	char* word;
	//указатель на следующий элемент
	word_cell* next;
};

//список слов
struct list_word {
	//указатель на начало списка
	word_cell* link_to_start = NULL;
	//рабочий указатель
	word_cell* work_pointer = NULL;
	//переменная отвечающая за начало работы со списком
	bool start = false;
	//сохраненный элемент
	char* saved_item = NULL;
	//переменная-флаг сигнализирующая об ошибки в выделении памяти
	bool memory_error = false;
};
//Меню односвязного списка слов
void list_word_menu(list_word* list_word);
//функция удаляющая элемент списка. Принимает указаетль на односвязный спискок
void delete_cell_to_word_list(list_word* list);
//функция очищающая список слов
void clear_word_list(list_word* list);
//проверка введенного значения меню
int getValue(int* i);
//проверка запроса в меню
void request_verification(int* i, int range_1, int range_2);
//функция печатующая список слов. Принимает указатель на односвязный список слов.
void print_list_word(list_word* list);

//функция провещающее на допустимое значение слова
bool check_words_for_punctuation(char* word);
//функция проверяющая весь список на знаки пунктуации
void check_the_entire_list_for_punctuation(list_word* list);
//функция добавляющая знак пунктуации
void add_punctuation(list_word* list);



//односвязный список предложений
//структура содержащая указатель на односвязный список слов и на следующий список слов
struct sentence_cell {
	//указатель на прошлый элемент 
	sentence_cell* last;
	//указатель на список слов
	list_word* list_word;
	//указатель на следующий элемент
	sentence_cell* next;
};

//список предложений
struct list_sentence {
	//указатель на начало списка
	sentence_cell* link_to_start = NULL;
	//рабочий указатель
	sentence_cell* work_pointer = NULL;
	//переменная отвечающая за начало работы со списком
	bool start = false;
	//сохраненный элемент
	list_word* saved_item = NULL;
	//переменная-флаг сигнализирующая об ошибки в выделении памяти
	bool memory_error = false;
};
//вызов меню списка предложений
void list_sentence_menu(list_sentence* list_sentence);
//инициализация списка слов
void list_word_initialize(list_word* list);
//функция удаляющая элемент списка до указателя. Принимает указаетль на двухсвязный список предложений
void delete_cell_to_sentence_list_before(list_sentence* list);
//функция удаляющая элемент списка после указателем. Принимает указаетль на двухсвязный список предложений
void delete_cell_to_sentence_list_after(list_sentence* list);
//функция очищающая список слов
void clear_sentence_list(list_sentence* list);
//поиска определенного символа 
bool search_character(char c, bool* flag_end_sentence, bool* flag_end_text);
//функция сохранения предложения (сохранение списка слов). Принимает указатель на односвязный список слов
list_word* save_item_pointer(list_word* list);


//двухсвязный список текстов
//структура содержащая указатель на двухсвязный список предложений и на следующий список предложений
struct text_cell {
	//указатель на список предложений
	list_sentence* list_sentence;
	//указатель на следующий элемент
	text_cell* next;
};

//список текстов
struct list_text {
	//указатель на начало списка
	text_cell* link_to_start = NULL;
	//рабочий указатель
	text_cell* work_pointer = NULL;
	//переменная отвечающая за начало работы со списком
	bool start = false;
	//сохраненный элемент
	list_sentence* saved_item = NULL;
	//переменная-флаг сигнализирующая об ошибки в выделении памяти
	bool memory_error = false;
};
void list_text_menu(list_text* list_text);
//инициализация списка предложений
void list_sentence_initialize(list_sentence* list);

//заголовки функций об выводящий сообщение об ошибках
//сообщение об ошибке доступа к списку
void error_message_at_the_beginning_of_work();
//сообщение об ошибке вследствии пустого списка
void error_message_due_to_empty_list();
//сообщение об ошибке выделения памяти
void memory_allocation_error_message();
//сообщение о нахождении рабочего указателя в конце списка
void message_about_pointers_at_the_end_of_the_list();
//сообщение о нахождении рабочего указателя в начале списка
void message_about_pointers_in_the_beginning_of_the_list();
//сообщение о необходимости завершить работу со списком
void message_about(char massive[]);

//спуск на нижний уровень структуры
void go_to_the_lower_level_last(list_sentence* list, sentence_cell* check);
//спуск на нижний уровень структуры
void go_to_the_lower_level_2(list_text* list, text_cell* check);
//спуск на нижний уровень структуры
void go_to_the_lower_level_next(list_sentence* list, sentence_cell* check);