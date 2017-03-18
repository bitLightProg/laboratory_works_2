/*���������� ����������������� ��� � �����  ������� ��� ������ � �������� �������, ������������� � ������� ��������.� �������� ������� ������ :
�        ���� ������ ������� � ����������;
�        �������� � ���������� ������� � ��������� �����;
�        �������� �������;
�        ���������� ������� � ������� ����������� ��������� ����;
�        ����� � ������� �������� � �������� ��������� ���� ��� � �������� ������� � ���� �� ��������;
�        �������� ������;
�        ���������(��������������) ������;
�        ���������� � ��������� � �������������� ���� ������� �� ��������� ������� � �������(��������, ����� ����� �� ���� ������).
9. �������, ���� �����������, ���� ����������.
*/
#include <iostream>
#include <fstream>
#include <Windows.h>

using namespace std;

short student_count = 0;
short table_size = 0;


struct student
{
	unsigned char* second_name;
	short e_year;
	short e_month;
	short e_day;

	short l_year;
	short l_month;
	short l_day;
};

student **table = NULL; // ������� ���������� �� ���������, ������������ ��� ����������

struct student_list
{
	student_list* next_student = NULL;
	student this_student;

} main_list; // ���������� ������ ���������

int student_set(student_list &st, unsigned char* const &s_name, short &d1, short &m1, short &y1, short &d2, short &m2, short &y2) // ��������� �������� ��� ���������
{
	st.this_student.e_day = d1;
	st.this_student.e_month = m1;
	st.this_student.e_year = y1;
	st.this_student.l_day = d2;
	st.this_student.l_month = m2;
	st.this_student.l_year = y2;
	short i = 1 + strlen((char*)s_name);
	st.this_student.second_name = new unsigned char[i];

	for (short j = 0; j < i; j++)
	{
		st.this_student.second_name[j] = s_name[j];
	}
	st.this_student.second_name[i] = '\0';

	return 0;
}

int student_add() // ���������� �������� � ������ � ������� ����������
{
	student_list *ins_student = &main_list;
	system("cls");
	cout << "������� ������� ��������, ���� ����������� � ���� ����������. ������: �������� 24.9.2016 24.9.2018" << endl;
	unsigned char s_name[128];
	short y1, m1, d1, m2, d2, y2, i = 0;
	unsigned char ch;
	getchar();
	while (s_name[i] = getchar())
	{
		if (s_name[i] == ' ' || s_name[i] == '\n')
		{
			s_name[i] = '\0';
			break;
		}
		i++;
	}
	cin >> d1 >> ch >> m1 >> ch >> y1;
	cin >> d2 >> ch >> m2 >> ch >> y2;
	
	if (student_count == 0)
	{
		student_set(main_list, s_name, d1, m1, y1, d2, m2, y2);

		student_count++;
	}
	else
	{
		while (ins_student->next_student != NULL)
			ins_student = ins_student->next_student;

		student_list *new_student = new student_list;

		student_set(*new_student, s_name, d1, m1, y1, d2, m2, y2);

		ins_student->next_student = new_student;

		student_count++;
	}
	cout << "������� �� ������ " << student_count << " ��������." << endl;
	
	system("pause");
	return 0;

}

int student_print(ostream &fout, student &st, short i) // ����� ������ ��������
{
	fout << i << ". " << st.second_name << " " << st.e_day << "."
		<< st.e_month << "." << st.e_year << " "
		<< st.l_day << "." << st.l_month << "."
		<< st.l_year;
	fout << endl;

	return 0;
}

int print_file() // ����� ��������� � ����
{				// TODO: �������� ����� �������
	system("cls");
	ofstream fout("out_table.txt");

	short i = 1;
	student_list *s_student = &main_list;
	while (s_student->next_student != NULL)
	{
		student_print(fout, s_student->this_student, i++);

		s_student = s_student->next_student;
	}
	if (s_student->this_student.second_name == NULL)
	{
		cout << "������ �����������." << endl;
		system("pause");
		return 1;
	}
	student_print(fout, s_student->this_student, i++);

	cout << "����� ������ � ���� ������� ��������." << endl;
	system("pause");
	return 0;
}

int read_file() // ���������� ��������� �� �����
{
	system("cls");
	ifstream fin("in_table.txt");

	student_list *ins_student = &main_list;

	unsigned char s_name[128];
	short y1, m1, d1, m2, d2, y2, i = 0;
	unsigned char ch;
	while (!fin.eof())
	{
		fin >> d1 >> s_name; // ���������� ����������� ������ � �������� ����� ���� �� �������
		
		fin >> s_name;
			
		fin >> d1 >> ch >> m1 >> ch >> y1; // ���������� ��� � ��������� ������������ ������������
		fin >> d2 >> ch >> m2 >> ch >> y2;		

		if (student_count == 0)
		{
			student_set(main_list, s_name, d1, m1, y1, d2, m2, y2);

			student_count++;
		}
		else
		{
			while (ins_student->next_student != NULL)
				ins_student = ins_student->next_student;

			student_list *new_student = new student_list;

			student_set(*new_student, s_name, d1, m1, y1, d2, m2, y2);

			ins_student->next_student = new_student;

			student_count++;
		}
		cout << "������� �� ������ " << student_count << " ��������." << endl;
	}

	system("pause");

	return 0;
}

int print() // ����� �� �����
{
	system("cls");
	short choose;
	cout << "0. ����� �� �������.\n"
		<< "1. ����� ����������� ������ ���������.\n"
		<< "2. ����� ��������������� ����� �������.\n";
	cin >> choose;

	if (!choose)
		return 0;

	short i = 1;
	switch (choose)
	{
	case 1:
	{
		
		student_list *s_student = &main_list;
		while (s_student->next_student != NULL)
		{
			student_print(cout, s_student->this_student, i++);

			s_student = s_student->next_student;
		}
		if (s_student->this_student.second_name == NULL)
		{
			cout << "������ �����������." << endl;
			system("pause");
			return 1;
		}
		student_print(cout, s_student->this_student, i++);

		system("pause");

		return 0;
	}
		break;
	case 2:
		if (table_size == 0)
		{
			cout << "������ �����������." << endl;
			system("pause");
			return 1;
		}

		for (i = 0; i < table_size; i++)
		{
			student_print(cout, *(table[i]), i + 1);
		}
		system("pause");
		return 0;
		break;
	}
	
}

int compare_s_name(const void* v1, const void* v2) // ������� ��������� �������
{	
	const student* s1 = *((student**)(v1));
	const student* s2 = *((student**)(v2));
	short n = strlen((char*) s1->second_name);
	short i;
	for (i = 0; i <= n; i++)
	{
		if (s1->second_name[i] < s2->second_name[i])
		{
			return -1;
		}
		else if (s1->second_name[i] > s2->second_name[i])
		{
			return 1;
		}
	}
	
	return 0;
}

int compare_e_date(const void* v1, const void* v2) // ������� ��������� ��� �����������
{
	const student* s1 = *((student**)(v1));
	const student* s2 = *((student**)(v2));

	if (s1->e_year < s2->e_year)
		return -1;
	else if (s1->e_year > s2->e_year)
		return 1;
	else if (s1->e_year == s2->e_year)
	{
		if (s1->e_month < s2->e_month)
			return -1;
		else if (s1->e_month > s2->e_month)
			return 1;
		else if (s1->e_month == s2->e_month)
		{
			if (s1->e_day < s2->e_day)
				return -1;
			else if (s1->e_day > s2->e_day)
				return 1;
			else
			{
				return compare_s_name(v1, v2); // ���������� �� �������, ���� ���� �����
			}
		}
	}	
}

int compare_l_date(const void* v1, const void* v2) // ������� ���������� �� ���� ����������
{
	const student* s1 = *((student**)(v1));
	const student* s2 = *((student**)(v2));

	if (s1->l_year < s2->l_year)
		return -1;
	else if (s1->l_year > s2->l_year)
		return 1;
	else if (s1->l_year == s2->l_year)
	{
		if (s1->l_month < s2->l_month)
			return -1;
		else if (s1->l_month > s2->l_month)
			return 1;
		else if (s1->l_month == s2->l_month)
		{
			if (s1->l_day < s2->l_day)
				return -1;
			else if (s1->l_day > s2->l_day)
				return 1;
			else
			{
				return compare_s_name(v1, v2); // ���������� �� �������, ���� ���� �����
			}
		}
	}
}

int sort() // ������� ����������
{
	short choose;

	system("cls");
	cout << "0. ����� �� �������.\n"
		<< "1. ���������� �� �������� ���������.\n"
		<< "2. ���������� �� ���� �����������.\n"
		<< "3. ���������� �� ���� ����������.\n";
	cin >> choose;
	
	if (!choose)
		return 0;

	if (table_size != 0)
	{
		delete[] table;
		table_size = 0;
	}

	table_size = student_count;
	table = new student*[table_size];

	short i = 0;

	student_list *this_student = &main_list;
	while (this_student->next_student != NULL)
	{
		table[i++] = &this_student->this_student;
		this_student = this_student->next_student;
	}
	table[i] = &this_student->this_student;


	switch (choose)
	{
	case 1:
		qsort(table, table_size, sizeof(table[i]), compare_s_name); // �� �������
		break;
	case 2:
		qsort(table, table_size, sizeof(table[i]), compare_e_date); // �� �����������
		break;
	case 3:
		qsort(table, table_size, sizeof(table[i]), compare_l_date); // �� ����������
		break;
	}
	cout << "���������� ������� ������� ���������." << endl;
	system("pause");

	return 0;	
}

int find() // �����
{
	short choose;
	system("cls");
	cout << "0. ����� �� �������.\n"
		<< "1. ���������� �� �������� ���������.\n"
		<< "2. ���������� �� ���� �����������.\n"
		<< "3. ���������� �� ���� ����������.\n";
	cin >> choose;

	if (!choose)
		return 0;
	return 0;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	student_list first_student;
	short choose;
	int(*arr[10])();
	arr[0] = student_add;
	arr[1] = print_file;
	arr[2] = read_file;
	arr[3] = print;
	arr[4] = sort;
	arr[5] = find;

	do
	{
		system("cls");
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

		

		if (choose != 0)
			arr[choose - 1]();
	} while (choose != 0);

	student_list *this_student = main_list.next_student;
	student_list *next_student;

	while (this_student != NULL && this_student->next_student != NULL) // �������� ������ ���������
	{
		next_student = this_student->next_student;
			delete this_student;
		student_count--;
		this_student = next_student;
	}								// TODO: ��������� �� ������������
	if (this_student != &main_list)
	{
		delete this_student;
		student_count--;
	}
		
	return 0;
}