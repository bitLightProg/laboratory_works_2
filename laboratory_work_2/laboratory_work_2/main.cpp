/*Определить структурированный тип и набор  функций для работы с таблицей записей, реализованной в массиве структур.В перечень функций входят :
·        ввод записи таблицы с клавиатуры;
·        загрузка и сохранение таблицы в текстовом файле;
·        просмотр таблицы;
·        сортировка таблицы в порядке возрастания заданного поля;
·        поиск в таблице элемента с заданным значением поля или с наиболее близким к нему по значению;
·        удаление записи;
·        изменение(редактирование) записи;
·        вычисление с проверкой и использованием всех записей по заданному условию и формуле(например, общая сумма на всех счетах).
9. Фамилия, дата поступления, дата отчисления.
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
	//char endtance_date[11];
	//char leaving_date[11];
};

student **table = NULL;

struct student_list
{
	student_list* next_student = NULL;
	student this_student;

} main_list;

int student_add()
{
	student_list *ins_student = &main_list;
	system("cls");
	cout << "Введите фамилию студента, дату поступления и дату отчисления. Пример: Яковенко 24.9.2016 24.9.2018" << endl;
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
		main_list.this_student.e_day = d1;
		main_list.this_student.e_month = m1;
		main_list.this_student.e_year = y1;
		main_list.this_student.l_day = d2;
		main_list.this_student.l_month = m2;
		main_list.this_student.l_year = y2;
		main_list.this_student.second_name = new unsigned char[1 + strlen((char*) s_name)];

		for (short j = 0; j < i; j++)
		{
			main_list.this_student.second_name[j] = s_name[j];
		}
		main_list.this_student.second_name[i] = '\0';

		student_count++;
	}
	else
	{
		while (ins_student->next_student != NULL)
			ins_student = ins_student->next_student;

		student_list *new_student = new student_list;

		new_student->this_student.e_day = d1;
		new_student->this_student.e_month = m1;
		new_student->this_student.e_year = y1;
		new_student->this_student.l_day = d2;
		new_student->this_student.l_month = m2;
		new_student->this_student.l_year = y2;
		new_student->this_student.second_name = new unsigned char[1 + strlen((char*)s_name)];

		for (short j = 0; j < i; j++)
		{
			new_student->this_student.second_name[j] = s_name[j];
		}
		new_student->this_student.second_name[i] = '\0';

		ins_student->next_student = new_student;

		student_count++;
	}
	cout << "Студент по номеру " << student_count << " добавлен." << endl;
	/*while (ins_student->next_student != NULL)
		ins_student = ins_student->next_student;*/
	system("pause");
	return 0;

}

int print_file()
{
	system("cls");
	ofstream fout("out_table.txt");

	short i = 1;
	student_list *s_student = &main_list;
	while (s_student->next_student != NULL)
	{
		fout << i++ << ". " << s_student->this_student.second_name << " " << s_student->this_student.e_day << "."
			<< s_student->this_student.e_month << "." << s_student->this_student.e_year << " "
			<< s_student->this_student.l_day << "." << s_student->this_student.l_month << "."
			<< s_student->this_student.l_year;
		fout << endl;

		s_student = s_student->next_student;
	}
	if (s_student->this_student.second_name == NULL)
	{
		cout << "Записи отсутствуют." << endl;
		system("pause");
		return 1;
	}

	fout << i++ << ". " << s_student->this_student.second_name << " " << s_student->this_student.e_day << "."
		<< s_student->this_student.e_month << "." << s_student->this_student.e_year << " "
		<< s_student->this_student.l_day << "." << s_student->this_student.l_month << "."
		<< s_student->this_student.l_year;
	fout << endl;

	cout << "Вывод данных в файл успешно завершен." << endl;
	system("pause");
	return 0;
}

int read_file()
{
	system("cls");
	ifstream fin("in_table.txt");

	student_list *ins_student = &main_list;

	unsigned char s_name[128];
	short y1, m1, d1, m2, d2, y2, i = 0;
	unsigned char ch;
	while (!fin.eof())
	{
		fin >> d1 >> s_name;
		//while (!fin.eof())
		//{
			fin >> s_name;
			/*if (s_name[i] == ' ' || s_name[i] == '\n')
			{
				s_name[i] = '\0';
				break;
			}*/
			//i++;
		//}
		fin >> d1 >> ch >> m1 >> ch >> y1;
		fin >> d2 >> ch >> m2 >> ch >> y2;

		

		if (student_count == 0)
		{
			main_list.this_student.e_day = d1;
			main_list.this_student.e_month = m1;
			main_list.this_student.e_year = y1;
			main_list.this_student.l_day = d2;
			main_list.this_student.l_month = m2;
			main_list.this_student.l_year = y2;
			i = 1 + strlen((char*)s_name);
			main_list.this_student.second_name = new unsigned char[i];

			for (short j = 0; j < i; j++)
			{
				main_list.this_student.second_name[j] = s_name[j];
			}
			main_list.this_student.second_name[i] = '\0';

			student_count++;
		}
		else
		{
			while (ins_student->next_student != NULL)
				ins_student = ins_student->next_student;

			student_list *new_student = new student_list;

			new_student->this_student.e_day = d1;
			new_student->this_student.e_month = m1;
			new_student->this_student.e_year = y1;
			new_student->this_student.l_day = d2;
			new_student->this_student.l_month = m2;
			new_student->this_student.l_year = y2;
			i = 1 + strlen((char*)s_name);
			new_student->this_student.second_name = new unsigned char[i];

			for (short j = 0; j < i; j++)
			{
				new_student->this_student.second_name[j] = s_name[j];
			}
			new_student->this_student.second_name[i] = '\0';

			ins_student->next_student = new_student;

			student_count++;
		}
		cout << "Студент по номеру " << student_count << " добавлен." << endl;
		//fin >> ch;
	}

	system("pause");

	return 0;
}

int print()
{
	system("cls");
	short choose;
	cout << "0. Выход из функции.\n"
		<< "1. Вывод порядкового списка студентов.\n"
		<< "2. Вывод отсортированной ранее таблицы.\n";
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
			cout << i++ << ". " << s_student->this_student.second_name << " " << s_student->this_student.e_day << "."
				<< s_student->this_student.e_month << "." << s_student->this_student.e_year << " "
				<< s_student->this_student.l_day << "." << s_student->this_student.l_month << "."
				<< s_student->this_student.l_year;
			cout << endl;

			s_student = s_student->next_student;
		}
		if (s_student->this_student.second_name == NULL)
		{
			cout << "Записи отсутствуют." << endl;
			system("pause");
			return 1;
		}

		cout << i++ << ". " << s_student->this_student.second_name << " " << s_student->this_student.e_day << "."
			<< s_student->this_student.e_month << "." << s_student->this_student.e_year << " "
			<< s_student->this_student.l_day << "." << s_student->this_student.l_month << "."
			<< s_student->this_student.l_year;
		cout << endl;

		system("pause");

		return 0;
	}
		break;
	case 2:
		if (table_size == 0)
		{
			cout << "Записи отсутствуют." << endl;
			system("pause");
			return 1;
		}

		for (i = 0; i < table_size; i++)
		{
			cout << i + 1 << ". " << table[i]->second_name << " " << table[i]->e_day << "."
				<< table[i]->e_month << "." << table[i]->e_year << " "
				<< table[i]->l_day << "." << table[i]->l_month << "."
				<< table[i]->l_year;
			cout << endl;
		}
		system("pause");
		return 0;
		break;
	}
	
}

int compare_s_name(const void* v1, const void* v2)
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

int compare_e_date(const void* v1, const void* v2)
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
				short i;
				short n = strlen((char*)s1->second_name);
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
		}
	}	
}

int compare_l_date(const void* v1, const void* v2)
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
				short i;
				short n = strlen((char*)s1->second_name);
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
		}
	}
}

int sort()
{
	short choose;

	system("cls");
	cout << "0. Выход из функции.\n"
		<< "1. Сортировка по фамилиям студентов.\n"
		<< "2. Сортировка по дате поступления.\n"
		<< "3. Сортировка по дате отчисления.\n";
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
		//cout << sizeof(table[i]) << endl;
		qsort(table, table_size, sizeof(table[i]), compare_s_name);
		break;
	case 2:
		qsort(table, table_size, sizeof(table[i]), compare_e_date);
		break;
	case 3:

		break;
	}
	/*for (i = 0; i < table_size; i++)
	{
		//table + i;
		//cout << *(table + i)->second_name << endl;
		cout << table[i]->second_name << endl;
		
	}*/
	cout << "Сортировка таблицы успешно завершена." << endl;
	system("pause");

	return 0;



	
}

int find()
{
	short choose;
	system("cls");
	cout << "0. Выход из функции.\n"
		<< "1. Сортировка по фамилиям студентов.\n"
		<< "2. Сортировка по дате поступления.\n"
		<< "3. Сортировка по дате отчисления.\n";
	cin >> choose;

	if (!choose)
		return 0;
	return 0;
}

int main()
{
	//setlocale(LC_ALL, "");
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
		cout << "1. Добавление нового студента.\n"
			<< "2. Вывести таблицу в текстовый файл.\n"
			<< "3. Загрузить таблицу из текстового файла.\n"
			<< "4. Вывод таблицы на экран.\n"
			<< "5. Сортировка таблицы.\n"
			<< "6. Поиск в таблице элемента с заданным значением поля или с наиболее близким к нему по значению.\n"
			<< "7. Удаление записи.\n"
			<< "8. Редактирование записи.\n"
			<< "9. \n";
		cin >> choose;

		

		if (choose != 0)
			arr[choose - 1]();
	} while (choose != 0);

	student_list *this_student = main_list.next_student;
	student_list *next_student;

	while (this_student != NULL && this_student->next_student != NULL)
	{
		next_student = this_student->next_student;
			delete this_student;
		student_count--;
		this_student = next_student;
	}
	if (this_student != &main_list)
	{
		delete this_student;
		student_count--;
	}
		
	return 0;
}