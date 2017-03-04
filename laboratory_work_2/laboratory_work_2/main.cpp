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

	int (*arr[10])();
	arr[0] = student_add;
	return 0;
}