/*9. Задан словарь из слов одинаковой длины, например «барак, баран, банан, дурак, бутон, бутан, питон, барин».
Для заданной пары слов определить цепочку так, чтобы каждое следующее слово отличалось не более чем на 2 буквы.*/
// барак баран банан дурак бутон бутан питон барин
#include <iostream>
#include <Windows.h>
#include <stack>
#include <list>

using namespace std;

struct word_list
{
	word_list* next = NULL;
	char* word;
};

word_list* tail = NULL;
word_list* beg = NULL;
int l_count = 0;
int lenght = 0;
/*Функция вывода слова по номеру*/
int print_word(short n)
{
	if (l_count <= n)
	{
		return 1;
	}
	else
	{
		word_list* it = beg;
		for (int i = 0; i < n; i++) it = it->next;
		cout << it->word << " ";
	}
	return 0;
}
/*Функция добавления слова в список*/
int add_word(char* str)
{
	if (beg == NULL)
	{
		beg = new word_list;
		tail = beg;
		beg->word = str;
		lenght = strlen(str);
		l_count++;
	}
	else
	{
		tail->next = new word_list;
		tail = tail->next;
		tail->word = str;
		l_count++;
	}
	return 0;
}
/*Считывание потока*/
int c = 0;
int read_file(istream& fin)
{

	while (/*!fin.eof()*/ c > 0)
	{
		char *str = new char[256];
		str[255] = 0;
		fin >> str;
		//fin.getline(str, 255);
		if (lenght != 0 && str[0] != 0 && strlen(str) != lenght)
		{
			cout << "Длина данного слова отличается от длины других слов. Слово не будет записано." << endl;
			delete str;
			continue;
		}
		if (str[0] != 0)
			add_word(str);
		c--;
	}
	
	return 0;
}

int n_max = 0;
bool *was;
int **arr;
list<short> max;
list<short> th;

int list_copy(list<short> &from, list<short> &to)
{
	list<short>::iterator f = from.begin();
	to.clear();
	for (; f != from.end(); f++)
	{
		to.push_back(*f);
	}	
	return 0;
}
/*Рекурсия-поиск пути наибольшего пути до ind2*/
int recurs(int i, int n, int ind2)
{
	th.push_back(i);
	was[i] = true;
	if (n > n_max && i == ind2)
	{
		list_copy(th, max);
		n_max = n;
	}
	for (int j = 0; j < l_count; j++)
	{
		if (arr[i][j] == 1 && was[j] == false)
		{
			recurs(j, n + 1, ind2);
		}
	}
	was[i] = false;
	th.pop_back();
	return 0;
}

int find_solution(int ind1, int ind2)
{
	arr = new int*[l_count];
	was = new bool[l_count];
	for (int i = 0; i < l_count; i++)
	{
		arr[i] = new int[l_count];
		was[i] = false;
	}

	int i = 0;
	word_list *el = beg;
	while (el != NULL)
	{
		word_list *another = beg;
		int j = 0;
		while (another != NULL)
		{
			if (another == el)
			{
				arr[i][j] = 0;
				another = another->next;
				j++;
				continue;
			}
			int n = 0;
			for (int k = 0; k < lenght; k++)
			{
				if (el->word[k] != another->word[k])
				{
					n++;
				}
				if (n > 2)
					break;
			}
			if (n > 2)
			{
				arr[i][j] = 0;
				another = another->next;
				j++;
				continue;
			}
			else
			{
				arr[i][j] = 1;
				another = another->next;
				j++;
				continue;
			}
		}
		el = el->next;
		i++;
	}

	for (int i = ind1; i < ind1+1; i++)
	{
		recurs(i, 1, ind2);
	}
	cout << "Цепочка слов: ";
	for (list<short>::iterator i = max.begin(); i != max.end(); i++)
	{
		print_word(*i);
	}
	cout << endl;

	delete[] arr;
	delete[] was;
	return 0;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	cout << "Введите количество слов в словаре: ";

	cin >> c;
	cout << "Введите словарь(слова разделены пробелом): ";
	read_file(cin);
	cout << "Введите пару слов(слова разделены пробелом): ";
	char* ch1 = new char[lenght + 1];
	char* ch2 = new char[lenght + 1];
	cin >> ch1 >> ch2;
	int ind1 = -1, ind2 = -1;
	int n = 0;
	word_list *l = beg;
	while (l != NULL)
	{
		if (!strcmp(ch1, l->word))
				ind1 = n;
		if (!strcmp(ch2, l->word))
			ind2 = n;
		n++;
		l = l->next;
	}
	find_solution(ind1, ind2);

	word_list* el = beg;
	word_list* el_n;

	while (el != NULL)
	{
		el_n = el->next;
		delete el->word;
		delete el;
		l_count--;
		el = el_n;		
	}


	system("pause");
	return 0;
}