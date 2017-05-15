//10.  Программа генерирует текст из строки, содержащей определения циклических фрагментов вида ...(Иван,Петр,Федор=Жил-был 
//* (синего,белого,желтого= у самого * моря)).... Символ «*» определяет место подстановки имени из списка в очередное
//повторение фрагмента. Допускается вложенность фрагментов. Полученный текст помещается в выходную строку. 

#include <iostream>
#include <Windows.h>

using namespace std;

short* mass;
int n = 0;


int r_alloc(unsigned char* &str, int &size)
{
	unsigned char* ptr = new unsigned char[size * 2 + 1];
	int l = strlen((char*)str);

	for (int i = 0; i < l; i++)
	{
		ptr[i] = str[i];
	}

	ptr[l] = 0;

	delete[] str;

	str = ptr;
	size = size * 2 + 1;

	return 0;
	/*if ((ptr = (unsigned char*)realloc(str, (size * 2) + 5)) != NULL)
	{

	size *= 2;
	str = ptr;
	}
	else
	{
	cout << "Невозможно выделить память. Завершение работы программы.";
	system("pause");
	return 1;
	}*/
}

int Concatenation(unsigned char* &to, unsigned char* from, int &size)
{
	size = (strlen((char*)to) + strlen((char*)from) + 2) / 2;
	r_alloc(to, size);

	int l = strlen((char*)to);
	int i = l;
	int j = 0;

	for (; i < l + strlen((char*)from); i++)
	{
		to[i] = from[j++];
	}
	to[i] = 0;

	delete[] from;
	//free(from);

	return 0;
}


unsigned char* Create_text(unsigned char* str, int begin, int depth)
{
	int i;
	int j = 0;
	int z = 1;
	int size = 16;
	unsigned char* text = (unsigned char*)calloc(size + 1, size + 1);
	for (i = begin; str[i] != '\0'; i++)
	{
		if (str[i] == '=')
			break;
		if (str[i] == ',')
			z++;
	}

	str[i] == '=' ? i++ : i;
	int p = i;

	for (; str[i] != '\0'; i++)
	{
		if (mass[depth] % z == 0 && mass[depth] != 0)
			if (depth != 0)
			{
				mass[depth - 1]++;
				mass[depth] = 0;
			}
			else mass[depth] = -1;

			if (str[i] == '*')
			{
				int zz = 0;
				for (int k = begin; str[k] != '='; k++)
				{
					if (str[k] == ',')
					{
						zz++;
						continue;
					}

					if (mass[depth] == zz)
					{
						if (j == size - 1)
							r_alloc(text, size);
						text[j++] = str[k];
					}
				}

				if (mass[depth] % z == 0 && mass[depth] != 0)
					if (depth != 0)
					{
						mass[depth - 1]++;
						mass[depth] = 0;
					}
					else mass[depth] = -1;
			}
			else if (str[i] == '(')
			{
				//cout << Create_text(str, i + 1, depth + 1) << endl;
				//while (mass[depth + 1] != 0)
				//cout << Create_text(str, i + 1, depth + 1) << endl;
				//записать строку, сложение с переносом единицы
				text[j] = 0;
				Concatenation(text, Create_text(str, i + 1, depth + 1), size);

				if (mass[depth] % z == 0 && mass[depth] != 0)
					if (depth != 0)
					{
						mass[depth - 1]++;
						mass[depth] = 0;
					}
					else mass[depth] = -1;

					int m = 0;
					for (int s = i; str[s] != '\0'; s++)
					{
						if (str[s] == '(')
							m++;
						if (str[s] == ')')
							m--;
						if (m == 0)
						{
							i = s;
							break;
						}
					}
			}
			else if (str[i] == ')')
			{
				if (depth == n - 1)
					mass[depth]++;
				if (mass[depth] % z == 0 && mass[depth] != 0)
					if (depth != 0)
					{
						mass[depth - 1]++;
						mass[depth] = 0;
					}
					else mass[depth] = -1;
					return text;
			}
			else
			{
				if (j == size - 1)
					r_alloc(text, size);
				text[j++] = str[i];
			}
	}
	if (depth == n - 1)
		mass[depth]++;
	if (mass[depth] % z == 0 && mass[depth] != 0)
		if (depth != 0)
		{
			mass[depth - 1]++;
			mass[depth] = 0;
		}
		else mass[depth] = -1;

		return text;
}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	unsigned char *string;
	unsigned size = 64;
	string = (unsigned char*)calloc(size + 1, size + 1);

	char ch;
	int k = -1;
	unsigned index = 0;

	cout << "Введите исходную строку:" << endl;
	while (ch = getchar())
	{
		if (ch == '\n')
			break;

		if (ch == '(')
		{
			n++;
			if (k == -1)
				k = index;
		}

		if (index > size)
		{
			unsigned char* ptr;
			if ((ptr = (unsigned char*)realloc(string, (size * 2) + 1)) != NULL)
			{

				size *= 2;
				string = ptr;
			}
			else
			{
				cout << "Невозможно выделить память. Завершение работы программы.";
				system("pause");
				return 1;
			}
		}

		string[index++] = ch;
		string[index] = '\0';
	}

	if (n == 0)
		n++;

	mass = new short[n];

	for (int i = 0; i < n; i++)
		mass[i] = 0;

	//cout << Create_text(string, k + 1, 0) << endl;
	int size1 = 16;
	unsigned char* str = new unsigned char[size1];

	while (mass[0] != -1)
	{
		//r_alloc(str, size1);
	//	if (size1 > 20000)
		//	break;
		cout << Create_text(string, k + 1, 0) << endl;
	}

	free(str);

	system("pause");
	return 0;
}