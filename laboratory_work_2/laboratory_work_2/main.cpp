#include <iostream>

using namespace std;

struct input
{
	short mode;

};

struct student
{
	char* second_name;

	//char endtance_date[11];
	//char leaving_date[11];
};

struct student_list
{
	student_list* next_student = NULL;
	student this_student;

} main_list;

int student_add()
{

}

int main()
{
	student_list first_student;
	short choose;

	cout << "1. ���������� ������ ��������.\n"
		<< "2. ������� ������� � ��������� ����.\n"
		<< "3. ��������� ������� �� ���������� �����.\n"
		<< "4. ����� ������� �� �����.\n"
		<< "5. ���������� �������.\n"
		<< "6. ����� � ������� �������� � �������� ��������� ���� ��� � �������� ������� � ���� �� ��������.\n"
		<< "7. �������� ������.\n"
		<< "8. �������������� ������.\n"
		<< "9. \n";
	cin >> choose;

	int (*arr[10])();
	arr[0] = student_add;
	return 0;
}