// 9. Функция находит в строке самое первое (по алфавиту) слово.
//С ее помощью реализовать размещение слов в выходной строке в алфавитном порядке.
#include <iostream>
#include <Windows.h>

using namespace std;

unsigned char* seek_min(unsigned char* string)
{
	unsigned char* output = NULL;

	unsigned char* first_word = NULL;
	unsigned char* second_word = NULL;
	unsigned char* pointer;

	for (pointer = string; *pointer != '\0'; ++pointer)
	{
		//cout << *pointer;
		if (*pointer == ' ')
			continue;

		if (first_word == NULL)
		{
			first_word = pointer;
			second_word = pointer;
			continue;
		}

		if (*(pointer - 1) == ' ' && *pointer <= *second_word)
		{
			second_word = pointer;
		}
		else
			continue;

		for (int i = 0; ; ++i)
		{
			if ( (*(first_word + i) > *(second_word + i)) && (*(first_word + i) != *(second_word + i) && *(first_word + i) != ' ') )
			{
				first_word = second_word;
				break;
			}

			if (*(first_word + i) == ' ')
				break;
		}

	}
	output = first_word;
	return output;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	unsigned char *string;
	unsigned size = 64;
	string = (unsigned char*)calloc(size + 1, size + 1);

	char ch;
	unsigned index = 0;

	cout << "Введите исходную строку:" << endl;
	while (ch = getchar())
	{
		if (ch == '\n')
			break;

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

	unsigned char *outstring = (unsigned char*)calloc(size * 2 + 1, size * 2 + 1);
	int out_index = 0;
	outstring[out_index] = '\0';

	while (1)
	{
		unsigned char* word = seek_min(string);
		if (word == NULL)
			break;

		//int lenght;
		for (int i = out_index; ; ++i)
		{
			if (word[i - out_index] == ' ' || word[i - out_index] == '\0')
			{
				//lenght = i - out_index;
				out_index = i;
				break;
			}

			outstring[i] = word[i - out_index];
			word[i - out_index] = ' ';
		}
		outstring[out_index++] = ' ';
	}
	outstring[--out_index] = '\0';

	cout << outstring << endl;

	free(string);
	free(outstring);

	


	system("pause");
	return 0;
}