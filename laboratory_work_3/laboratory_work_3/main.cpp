/*
9. Функция читает из файла текст по словам и возвращает двухуровневый динамический массив указателей
на строки на строки, содержащие слова из исходного файла, упорядоченные по алфавиту
(тип данных char *** - см. 87. иерархические структуры данных).
Размерность массива указателей нижнего уровня задана, каждый массив указателей ограничен NULL.
Очередная строка вставляется с сохранением порядка, в первом цикле просматривается массив указателей первого уровня
и в каждом – элемент с индексом 0 второго уровня. Если его значение больше нового,
то выполянется вставка в предыдущий массив указателей нижнего уровня.
Если при вставке происходит переполнение, массив создается новый массив указателей,
в который копируется половина указателей текущего.*/

#include <iostream>
#include <fstream>

using namespace std;

int p_count = 16;
int l_size = 5;

int show(char*** out) // Вывод массива на экран
{
	for (int i = 0; i < p_count; i++)
	{
		if (out[i][0] == NULL)
			break;
		cout << i << ". ";
		for (int j = 0; j < l_size; j++)
		{
			if (out[i][j] == NULL)
			{
				cout << "NULL" << endl;
				continue;
			}
			cout << out[i][j] << endl;
		}
	}
	return 0;
}

int r_alloc(char*** out) // Выделение дополнительной памяти под массив
{
	int new_count = p_count * 2;
	char*** temp = (char***)realloc(out, new_count*sizeof(char**));
	if (temp == 0)
		return 1;

	if (temp != out)
		out = temp;

	for (int i = p_count; i < new_count; out[i++] = NULL); // Обнуление новой памяти на всякий случай
	p_count = new_count;
	//strcmp();
	return 0;
}

int add_string(char* str, char*** out) // Добавление строки
{
	int flag_p = -1;
	for (int i = 0; i < p_count; i++) // Внешний цикл
	{
		if (out[i][0] == 0) // Если условие вставки не выполнилось и мы на пустой ячейке
		{
			out[i][0] = str;
			return 0;
		}
		if (out[i][0] != 0 && (strcmp(out[i][0], str) > 0)) // условие вставки
		{
			if (i == 0) // Если вторая входная строка меньше первой
			{			// Чтобы не было обращения к -1 элементу массива
				out[i + 1][0] = str; // Записываем в следующую ячейку и меняем указатели местами
				char** temp = out[i];
				out[i] = out[i + 1];
				out[i + 1] = temp;
				return 0;
			}
			for (int j = 0; j < l_size - 1; j++) // Вставка в обычных условиях
			{
				if (out[i-1][j] == 0)
				{
					out[i-1][j] = str;
					return 0;
				}
			}
			flag_p = i - 1; // Если досюда дошло, то вставлять некуда
			break;
		}
	}
	if (flag_p == -1) // Заполнен верхний уровень, все 0 строки < текущей
	{
		if (r_alloc(out) == 1) // Расширение массива
		{
			cout << "Ошибка при выделении памяти. Завершение работы." << endl;
			free(out);
			system("pause");
			return 1;
		}
		add_string(str, out); // Добавление строки
		return 0;
	}
	else
	if (flag_p != -1) // Найдено место для вставки, переполнение
	{
		if (out[p_count - 1] != NULL) // Если массив забит, выделение памяти для сдвига
			r_alloc(out);
		int i = 0;
		for (i = p_count; i > flag_p && out[i] == NULL; i--); // Крайняя правая заполненная ячейка
		
		for (; i > flag_p; i--) // Сдвиг вправо всех указателей, после переполненного
		{
			out[i + 1] = out[i];
		}

		out[flag_p + 1] = (char**)calloc(l_size, l_size * sizeof(char*)); // Выделение памяти под строки

		for (int j = l_size / 2, k = 0; j < l_size; j++, k++) // Перенос половины
		{
			out[flag_p + 1][k] = out[flag_p][j];
			out[flag_p][j] = NULL;
		}



	}
	return 0;
}

char*** read_file(istream& fin)
{
	char*** out = (char***) calloc(p_count, p_count*sizeof(char**));
	for (int i = 0; i < p_count; i++)
	{
		out[i] = (char**) calloc(l_size, l_size * sizeof(char*));
	}
	
	while (!fin.eof())
	{
		char *str = new char[256];
		str[255] = 0;
		fin.getline(str, 255, '\n');
		if (str[0] != 0)
			add_string(str, out);
//			cout << str << endl;
	}
	//fin.getline(ch, 19, '\n');
	//ch[19] = 0;
	//cout << ch << endl;
	/*for (int i = 0; i < p_count; i++)
	{
		free(out[i]);
	}*/
	//free(out);
	return out;
}

int main()
{
	setlocale(LC_ALL,"");
	//ifstream fin("1.txt");
	//ifstream fin("in_table.txt");
	ifstream fin("1.txt");
	char*** out;
	out = read_file(fin);
	//out = read_file(cin);
	show(out);
	for (int i = 0; i < p_count; i++)
	{
		if (out[i] != NULL)
		{
			for (int j = 0; j < l_size; j++)
				if (out[i][j] != NULL)
					delete[] out[i][j];
				else break;
				free(out[i]);
		}
	}
	free(out);
	system("pause");
	return 0;
}