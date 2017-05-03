/*9. «адан словарь из слов одинаковой длины, например Ђбарак, баран, банан, дурак, бутон, бутан, питон, баринї.
ƒл€ заданной пары слов определить цепочку так, чтобы каждое следующее слово отличалось не более чем на 2 буквы.*/

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
		cout << it->word << endl;
	}
	return 0;
}

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

int read_file(istream& fin)
{

	while (!fin.eof())
	{
		char *str = new char[256];
		str[255] = 0;
		fin >> str;
		//fin.getline(str, 255);
		if (lenght != 0 && str[0] != 0 && strlen(str) != lenght)
		{
			cout << "ƒлина данного слова отличаетс€ от длины других слов. —лово не будет записано." << endl;
			delete str;
			continue;
		}
		if (str[0] != 0)
			add_word(str);
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

int recurs(int i, int n)
{
	th.push_back(i);
	was[i] = true;
	if (n > n_max)
	{
		list_copy(th, max);
		n_max = n;
	}
	for (int j = 0; j < l_count; j++)
	{
		if (arr[i][j] == 1 && was[j] == false)
		{
			recurs(j, n + 1);
		}
	}
	was[i] = false;
	th.pop_back();
	return 0;
}

int find_solution()
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

	for (int i = 0; i < l_count; i++)
	{
		recurs(i, 1);
		for (int j = 0; j < l_count; j++)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}

	for (list<short>::iterator i = max.begin(); i != max.end(); i++)
	{
		print_word(*i);
	}

	delete[] arr;
	delete[] was;
	return 0;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	

	read_file(cin);
	find_solution();

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