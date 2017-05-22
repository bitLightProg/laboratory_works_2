/*9. Кодирование и декодирование строки символов, содержащих цифры, в последовательность битов.
Десятичная цифра кодируется 4 битами - одной шестнадцатеричной цифрой.
Цифра F обозначает, что за ней следует байт (2 цифры) с кодом символа, отличного от цифры.
Разработать функции кодирования и декодирования с определением процента уплотнения.*/
#include <iostream>
#include <ctime>
#include <Windows.h>

using namespace std;

int r_alloc(unsigned char* &in, int &size) // Выделение дополнительной памяти под массив
{
	int new_count = size * 2;
	unsigned char* temp = (unsigned char*)realloc(in, new_count * sizeof(unsigned char) + 1);
	if (temp == 0)
		return 1;

	if (temp != in)
		in = temp;

	for (int i = size; i < new_count; in[i++] = NULL); // Обнуление новой памяти на всякий случай
	size = new_count;
	
	return 0;
}

unsigned char* coding(unsigned char* &input, int &size)
{
	unsigned char* output = (unsigned char*)calloc(size + 1, size + 1);
	int o_index = 0;
	int flag = 0; // какая половина байта сейчас записывается

	for (int i = 0; input[i] != 0; i++)
	{
		if (size == o_index + 2)
		{
			r_alloc(output, size);
		}
		if (input[i] >= '0' && input[i] <= '9')
		{
			char byte = input[i] - '0';
			if (!flag)
			{
				output[o_index] |= byte;
				flag = 1;
				if (input[i + 1] == 0)
				{
					output[o_index] |= 0xE0;
				}
			}
			else
			{
				//byte <<= 4;
				output[o_index] |= (byte << 4); // в конец
				flag = 0;
				o_index++;
			}
		}
		else
		{
			char byte = input[i];
			if (!flag)
			{
				output[o_index] |= 0xF;
				output[o_index] |= (byte << 4); // первая половина в конец
				output[++o_index] |= ((byte & 0xF0) >> 4); // вторая половина в начало
				flag = 1;
			}
			else
			{
				output[o_index++] |= 0xF0;
				output[o_index++] |= byte;
				flag = 0;
			}
		}
	}
	flag == 1 ? output[o_index] |= 0xE0 : flag;
	flag == 0 ? output[o_index] = 0 : output[++o_index] = 0;

	realloc(output, o_index + 1);
	double lenght = strlen((char*)input);
	cout << (double)(lenght / o_index) * 100 - 100 << " %" << endl;
	size = o_index;

	free(input);

	return output;
}

unsigned char* decoding(unsigned char* &input, int &size)
{
	int out_size = size;
	unsigned char* output = (unsigned char*)calloc(size + 1, size + 1);
	int o_index = 0;
	int flag = 0; // какая половина байта сейчас декодируется

	for (int i = 0; i < size; i++)
	{
		if (out_size == o_index + 1)
		{
			r_alloc(output, out_size);
		}
		char byte = input[i];
		if (!flag)
		{
			if ((byte & 0xF) == 0xF) // если дальше символ
			{
				//cout << " ";
				output[o_index] = (byte & 0xF0) >> 4;
				output[o_index] |= (input[i + 1] << 4);
				flag = 1;
				o_index++;
				//i--;
				continue;
			}
			else
			{
				output[o_index++] = '0' + (byte & 0xF);
				flag = 1;
				i--;
				continue;
			}
		}
		else
		if (flag) // вторая половина
		{
			if (i == size - 1)
			{
				if ((byte & 0xF0) == 0xE0)
					break;
			}
			if ((byte & 0xF0) == 0xF0) // если дальше символ
			{
				//output[o_index] = (byte >> 4);
				output[o_index++] |= (input[++i]);
				flag = 0;
			}
			else
			{
				output[o_index++] = '0' + ((byte & 0xF0) >> 4);
				flag = 0;
			}
		}
	}

	//flag == 0 ? output[o_index] = 0 : output[++o_index] = 0;
	output[o_index] = 0;

	realloc(output, o_index + 1);
	double lenght = strlen((char*)input);
	cout << (double)(lenght / o_index) * 100 - 100 << " %" << endl;
	size = o_index + 1;

	free(input);

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
	//cout << (char)64 << endl;
	int size1 = size;
	unsigned char* out = coding(string, size1);
	for (int i = 0; i < size1; i++)
	{
		cout << out[i];
	}
	cout << endl;
	//cout << out << ":"<< endl;
	out = decoding(out, size1);
	cout << out << endl;

	free(out);
	//free(string);

	system("pause");
	return 0;
}