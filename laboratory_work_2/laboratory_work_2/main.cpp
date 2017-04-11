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

} *main_list; // ���������� ������ ���������

struct student_pointer_array
{
	student_pointer_array* next = NULL;
	student_list* this_student = NULL;
	int n;
	int dd;
	int mm;
	int yy;
};

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
	student_list *ins_student = main_list;
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
		student_set(*main_list, s_name, d1, m1, y1, d2, m2, y2);

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

	short choose;
	cout << "0. ����� �� �������.\n"
		<< "1. ����� ����������� ������ ���������.\n"
		<< "2. ����� ��������������� ����� �������.\n";
	cin >> choose;

	if (!choose)
		return 0;

	ofstream fout("out_table.txt");

	short i = 1;
	student_list *s_student = main_list;
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

	student_list *ins_student = main_list;

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
			student_set(*main_list, s_name, d1, m1, y1, d2, m2, y2);

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
		if (student_count == 0)
		{
			cout << "������ �����������." << endl;
			system("pause");
			return 1;
		}
		student_list *s_student = main_list;
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

	student_list *this_student = main_list;
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
		<< "1. ����� �� �������� ���������.\n"
		<< "2. ����� �� ���� �����������.\n"
		<< "3. ����� �� ���� ����������.\n";
	cin >> choose;

	if (!choose)
		return 0;


	student_list *this_student = main_list;
	student_pointer_array arr;
	int count = 0;
	int d, m, y;
	int pd, pm, py;
	int n = 0;
	int field_length = 0;
	char ch;
	student_pointer_array *next_s;

	switch (choose)
	{
	case 1:
	{
		cout << "������� ������� ��������. ����� ������������ �� ����� � ������ ���� ��������." << endl;
		unsigned char field[128];
		cin >> field;
		field_length = strlen((char*)field);
		this_student = main_list;


		while (this_student != NULL)
		{
			int n = 0;
			int this_length = strlen((char*)this_student->this_student.second_name);

			if (field_length != this_length)
			{
				this_student = this_student->next_student;
				continue;
			}

			for (int i = 0; i < field_length; i++)
			{

				if (field[i] != this_student->this_student.second_name[i])
					n++;

			}
			if (n > 2)
			{
				this_student = this_student->next_student;
				continue;
			}

			if (count == 0)
			{
				arr.n = n;
				arr.this_student = this_student;
				count++;
			}
			else
			{
				student_pointer_array *next_s = &arr;

				while (next_s->next != NULL)
					next_s = next_s->next;

				next_s->next = new student_pointer_array;
				next_s = next_s->next;
				next_s->n = n;
				next_s->this_student = this_student;
				count++;
			}
			this_student = this_student->next_student;
		}

		if (count == 0)
		{
			cout << "�������� �������� �� �������." << endl;
			system("pause");
			return 1;
		}
		cout << "������ �������� ���������:" << endl;
		n = count;
		int j = 0;
		while (count > 0)
		{
			next_s = &arr;
			//j = 0;
			for (int i = 0; i < n; i++)
			{
				if (next_s->n == j)
				{
					student_print(cout, next_s->this_student->this_student, n - count-- + 1);
				}
				next_s = next_s->next;
			}
			j++;
		}
		system("pause");
		break;
	}
	case 2:
	{
		cout << "������� ���� ����������� �������� � �������: ��.��.���� ��.��.��" << endl
			<< "��� �� - ����������� ����, �� - ����������� �������, �� - ����������� ���" << endl;
		cin >> d >> ch >> m >> ch >> y;

		cin >> pd >> ch >> pm >> ch >> py;

		this_student = main_list;

		count = 0;
		while (this_student != NULL)
		{
			int dd = 0, mm = 0, yy = 0;
			if (abs(this_student->this_student.e_year - y) > py)
				yy = abs(this_student->this_student.e_year - y) - py;
			if (abs(this_student->this_student.e_month - m) > pm)
				mm = abs(this_student->this_student.e_month - m) - pm;
			if (abs(this_student->this_student.e_day - d) > pd)
				dd = abs(this_student->this_student.e_day - d) - pd;

			if (yy > 0 || (yy == 0 && mm > 0) || (yy == 0 && mm == 0 && dd > 0))
			{
				this_student = this_student->next_student;
				continue;
			}


			if (count == 0)
			{
				arr.dd = dd;
				arr.mm = mm;
				arr.yy = yy;
				arr.this_student = this_student;
				count++;
			}
			else
			{
				student_pointer_array *next_s = &arr;

				while (next_s->next != NULL)
					next_s = next_s->next;

				next_s->next = new student_pointer_array;
				next_s = next_s->next;
				next_s->dd = dd;
				next_s->mm = mm;
				next_s->yy = yy;
				next_s->this_student = this_student;
				count++;
			}
			this_student = this_student->next_student;
		}

		if (count == 0)
		{
			cout << "�������� �������� �� �������." << endl;
			system("pause");
			return 1;
		}
		cout << "������ �������� ���������:" << endl;
		n = count;
		int j = 0;
		while (count > 0)
		{
			next_s = &arr;

			for (int i = 0; i <= n && count != 0; i++)
			{
				if (next_s->yy == j)
					student_print(cout, next_s->this_student->this_student, n - count-- + 1);
				next_s = next_s->next;
			}
			j++;
		}
		system("pause");
		break;
	}
	case 3:
	{
		cout << "������� ���� ���������� �������� � �������: ��.��.���� ��.��.��" << endl
			<< "��� �� - ����������� ����, �� - ����������� �������, �� - ����������� ���" << endl;

		cin >> d >> m >> y;

		cin >> pd >> pm >> py;

		this_student = main_list;

		count = 0;
		while (this_student != NULL)
		{
			int dd = 0, mm = 0, yy = 0;
			if (abs(this_student->this_student.l_year - y) > py)
				yy = abs(this_student->this_student.l_year - y) - py;
			if (abs(this_student->this_student.l_month - m) > pm)
				mm = abs(this_student->this_student.l_month - m) - pm;
			if (abs(this_student->this_student.l_day - d) > pd)
				dd = abs(this_student->this_student.l_day - d) - pd;

			if (yy > 0 || (yy == 0 && mm > 0) || (yy == 0 && mm == 0 && dd > 0))
			{
				this_student = this_student->next_student;
				continue;
			}


			if (count == 0)
			{
				arr.dd = dd;
				arr.mm = mm;
				arr.yy = yy;
				arr.this_student = this_student;
				count++;
			}
			else
			{
				student_pointer_array *next_s = &arr;

				while (next_s->next != NULL)
					next_s = next_s->next;

				next_s->next = new student_pointer_array;
				next_s = next_s->next;
				next_s->dd = dd;
				next_s->mm = mm;
				next_s->yy = yy;
				next_s->this_student = this_student;
				count++;
			}
			this_student = this_student->next_student;
		}

		if (count == 0)
		{
			cout << "�������� �������� �� �������." << endl;
			system("pause");
			return 1;
		}
		cout << "������ �������� ���������:" << endl;
		n = count;
		int j = 0;
		while (count > 0)
		{
			next_s = &arr;

			for (int i = 0; i <= n && count != 0; i++)
			{
				if (next_s->yy == j)
					student_print(cout, next_s->this_student->this_student, n - count-- + 1);
				next_s = next_s->next;
			}
			j++;
		}
		break;
	}
	}

	student_pointer_array *an = arr.next;
	
	while (an != NULL)
	{
		student_pointer_array *ann = an->next;
		delete an;
		an = ann;
	}

	return 0;
}

int student_delete()
{
	int choose;
	system("cls");
	if (student_count == 0)
	{
		cout << "������ �������." << endl;
		system("pause");
		return 1;
	}
	cout << "0. ����� �� �������.\n"
		<< "����� " << student_count << " ���������.\n"
		<< "������� ���������� ����� ��������, �������� ����� �������.\n";
	cin >> choose;

	if (!choose)
		return 0;

	if (choose > student_count)
	{
		cout << "�������� ����. ����� �� �������." << endl;
		system("pause");
		return 1;
	}

	int i = 1;
	student_list *this_student = main_list;
	student_list *prev_student = main_list;
	if (choose == 1)
	{
		main_list = main_list->next_student;
		delete this_student;
		student_count--;
		cout << "������� ��� ������� " << choose << " ������� ������." << endl;
		system("pause");
		return 0;
	}
	while (i < choose)
	{
		prev_student = this_student;
		this_student = this_student->next_student;
		i++;
	}
	prev_student->next_student = this_student->next_student;
	delete this_student;
	student_count--;

	cout << "������� ��� ������� " << choose << " ������� ������." << endl;
	system("pause");
	return 0;
}

int student_rewrite()
{
	int choose;
	system("cls");
	if (student_count == 0)
	{
		cout << "������ �������������." << endl;
		system("pause");
		return 1;
	}
	cout << "0. ����� �� �������.\n"
		<< "����� " << student_count << " ���������.\n"
		<< "������� ���������� ����� ��������, �������� ����� ��������.\n";
	cin >> choose;

	if (!choose)
		return 0;

	if (choose > student_count)
	{
		cout << "�������� ����. ����� �� �������." << endl;
		system("pause");
		return 1;
	}

	int i = 1;
	student_list *this_student = main_list;

	while (i < choose)
	{
		this_student = this_student->next_student;
		i++;
	}

	cout << "������� ��� ������� " << i << ":" << endl;
	student_print(cout, this_student->this_student, i);
	cout << "������� ����� ������ �������� � ��� �� �������." << endl;
	
	unsigned char s_name[128];
	short y1, m1, d1, m2, d2, y2;
	unsigned char ch;
	cin >> s_name;
	cin >> d1 >> ch >> m1 >> ch >> y1;
	cin >> d2 >> ch >> m2 >> ch >> y2;
	student_set(*this_student, s_name, d1, m1, y1, d2, m2, y2);

	
	return 0;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	main_list = new student_list;
	short choose;
	int(*arr[10])();
	arr[0] = student_add;
	arr[1] = print_file;
	arr[2] = read_file;
	arr[3] = print;
	arr[4] = sort;
	arr[5] = find;
	arr[6] = student_delete;
	arr[7] = student_rewrite;

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

	student_list *this_student = main_list;
	student_list *next_student;

	while (this_student != NULL) // �������� ������ ���������
	{
		next_student = this_student->next_student;
			delete this_student;
		student_count--;
		this_student = next_student;
	}
	

	delete[] table;
		
	return 0;
}