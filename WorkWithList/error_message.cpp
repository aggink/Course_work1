//����������� �������� ������ � ���������� �������
#include"Header.h"


//��������� �� ������ ������� � ������
void error_message_at_the_beginning_of_work() {
	SetConsoleOutputCP(866);
	putchar(201);
	int max_number = strlen("��������� �������� '������ ������ �� �������'!");
	int min_number = strlen("������ �������� ����������!");
	//����� ������� �������
	for (int i = 0; i < max_number; i++)
	{
		putchar(205);
	}
	putchar(187);
	cout << endl;
	putchar(186);
	SetConsoleOutputCP(1251);
	cout << "������ �������� ����������!";
	//������� ���������� ������ 
	for (int i = 0; i < max_number - min_number; i++) {
		cout << " ";
	}
	SetConsoleOutputCP(866);
	putchar(186);
	cout << endl;
	putchar(186);
	SetConsoleOutputCP(1251);
	cout << "��������� �������� '������ ������ �� �������'!";
	SetConsoleOutputCP(866);
	putchar(186);
	cout << endl;
	putchar(200);
	//����� ������ �������
	for (int i = 0; i < max_number; i++)
	{
		putchar(205);
	}
	putchar(188);
	cout << endl << endl;
	SetConsoleOutputCP(1251);
}
//��������� �� ������ ���������� ������� ������
void error_message_due_to_empty_list() {
	SetConsoleOutputCP(866);
	putchar(201);
	int max_number = strlen("������ �������� ����������!");
	int min_number = strlen("������ ����!");
	//����� ������� �������
	for (int i = 0; i < max_number; i++)
	{
		putchar(205);
	}
	putchar(187);
	cout << endl;
	putchar(186);
	SetConsoleOutputCP(1251);
	cout << "������ �������� ����������!";
	SetConsoleOutputCP(866);
	putchar(186);
	cout << endl;
	putchar(186);
	SetConsoleOutputCP(1251);
	cout << "������ ����!";
	//������ ����������� �������
	for (int i = 0; i < max_number - min_number; i++) {
		cout << " ";
	}
	SetConsoleOutputCP(866);
	putchar(186);
	cout << endl;
	putchar(200);
	//����� ������ �������
	for (int i = 0; i < max_number; i++)
	{
		putchar(205);
	}
	putchar(188);
	cout << endl << endl;
	SetConsoleOutputCP(1251);
}
//��������� �� ������ ��������� ������
void memory_allocation_error_message() {
	SetConsoleOutputCP(866);
	putchar(201);
	int max_number = strlen("���������� ������ ���������");
	int min_number = strlen("������ � ��������� ������!");
	//����� ������� �������
	for (int i = 0; i < max_number; i++)
	{
		putchar(205);
	}
	putchar(187);
	cout << endl;
	putchar(186);
	SetConsoleOutputCP(1251);
	cout << "������ � ��������� ������!";
	//������ ������������ �������
	for (int i = 0; i < max_number - min_number; i++) {
		cout << " ";
	}
	SetConsoleOutputCP(866);
	putchar(186);
	cout << endl;
	putchar(186);
	SetConsoleOutputCP(1251);
	cout << "���������� ������ ���������";
	SetConsoleOutputCP(866);
	putchar(186);
	cout << endl;
	putchar(200);
	//����� ������ �������
	for (int i = 0; i < max_number; i++)
	{
		putchar(205);
	}
	putchar(188);
	cout << endl << endl;
	SetConsoleOutputCP(1251);
}
//��������� � ���������� �������� ��������� � ����� ������
void message_about_pointers_at_the_end_of_the_list() {
	SetConsoleOutputCP(866);
	putchar(201);
	int max_number = strlen("������� ��������� � ����� ������!");
	int min_number = strlen("������ �������� ����������!");
	//����� ������� �������
	for (int i = 0; i < max_number; i++)
	{
		putchar(205);
	}
	putchar(187);
	cout << endl;
	putchar(186);
	SetConsoleOutputCP(1251);
	cout << "������ �������� ����������!";
	//������ ����������� �������
	for (int i = 0; i < max_number - min_number; i++) {
		cout << " ";
	}
	SetConsoleOutputCP(866);
	putchar(186);
	cout << endl;
	putchar(186);
	SetConsoleOutputCP(1251);
	cout << "������� ��������� � ����� ������!";
	SetConsoleOutputCP(866);
	putchar(186);
	cout << endl;
	putchar(200);
	//����� ������ �������
	for (int i = 0; i < max_number; i++)
	{
		putchar(205);
	}
	putchar(188);
	cout << endl << endl;
	SetConsoleOutputCP(1251);
}
//��������� � ���������� �������� ��������� � ������ ������
void message_about_pointers_in_the_beginning_of_the_list() {
	SetConsoleOutputCP(866);
	putchar(201);
	int max_number = strlen("������� ��������� � ������ ������!");
	int min_number = strlen("������ �������� ����������!");
	//����� ������� �������
	for (int i = 0; i < max_number; i++)
	{
		putchar(205);
	}
	putchar(187);
	cout << endl;
	putchar(186);
	SetConsoleOutputCP(1251);
	cout << "������ �������� ����������!";
	//������ ����������� �������
	for (int i = 0; i < max_number - min_number; i++) {
		cout << " ";
	}
	SetConsoleOutputCP(866);
	putchar(186);
	cout << endl;
	putchar(186);
	SetConsoleOutputCP(1251);
	cout << "������� ��������� � ������ ������!";
	SetConsoleOutputCP(866);
	putchar(186);
	cout << endl;
	putchar(200);
	//����� ������ ������� 
	for (int i = 0; i < max_number; i++)
	{
		putchar(205);
	}
	putchar(188);
	cout << endl << endl;
	SetConsoleOutputCP(1251);
}
//������� ��������� �� �����. ��������� ������ ���� char
void message_about(char massive[]) {
	SetConsoleOutputCP(866);
	putchar(201);
	int max_number = strlen(massive);
	//����� ������� �������
	for (int i = 0; i < max_number; i++)
	{
		putchar(205);
	}
	putchar(187);
	cout << endl;
	putchar(186);
	SetConsoleOutputCP(1251);
	cout << massive;
	SetConsoleOutputCP(866);
	putchar(186);
	cout << endl;
	putchar(200);
	//����� ������ �������
	for (int i = 0; i < max_number; i++)
	{
		putchar(205);
	}
	putchar(188);
	cout << endl << endl;
	SetConsoleOutputCP(1251);
}