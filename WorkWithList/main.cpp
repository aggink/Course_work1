//����������� �������� ������ � ���������� �������
#include"Header.h"


void main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	//�������� ������ ��� ������ �������
	struct list_text* list = (list_text*)malloc(sizeof(list_text));
	//�������� �� ������ ��� ��������� ������
	if (list == NULL) {
		cout << "������ � ��������� ������" << endl;
		system("pause");
		exit(0);
	}
	list->link_to_start = NULL;
	list->memory_error = false;
	list->saved_item = NULL;
	list->start = false;
	list->work_pointer = NULL;
	//�������� ���� �������
	list_text_menu(list);
}
//������� ���, ���� � ����� ����������� ������ �����, � � �������� ����������� ��� �� ����� �������������� ������������ ����� ����������!