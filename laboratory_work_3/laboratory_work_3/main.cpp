/*
9. ������� ������ �� ����� ����� �� ������ � ���������� ������������� ������������ ������ ����������
�� ������ �� ������, ���������� ����� �� ��������� �����, ������������� �� ��������
(��� ������ char *** - ��. 87. ������������� ��������� ������).
����������� ������� ���������� ������� ������ ������, ������ ������ ���������� ��������� NULL.
��������� ������ ����������� � ����������� �������, � ������ ����� ��������������� ������ ���������� ������� ������
� � ������ � ������� � �������� 0 ������� ������. ���� ��� �������� ������ ������,
�� ����������� ������� � ���������� ������ ���������� ������� ������.
���� ��� ������� ���������� ������������, ������ ��������� ����� ������ ����������,
� ������� ���������� �������� ���������� ��������.*/

#include <iostream>
#include <fstream>

using namespace std;

int p_count = 16;
int l_size = 5;

int show(char*** out) // ����� ������� �� �����
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

int r_alloc(char*** out) // ��������� �������������� ������ ��� ������
{
	int new_count = p_count * 2;
	char*** temp = (char***)realloc(out, new_count*sizeof(char**));
	if (temp == 0)
		return 1;

	if (temp != out)
		out = temp;

	for (int i = p_count; i < new_count; out[i++] = NULL); // ��������� ����� ������ �� ������ ������
	p_count = new_count;
	//strcmp();
	return 0;
}

int add_string(char* str, char*** out) // ���������� ������
{
	int flag_p = -1;
	for (int i = 0; i < p_count; i++) // ������� ����
	{
		if (out[i][0] == 0) // ���� ������� ������� �� ����������� � �� �� ������ ������
		{
			out[i][0] = str;
			return 0;
		}
		if (out[i][0] != 0 && (strcmp(out[i][0], str) > 0)) // ������� �������
		{
			if (i == 0) // ���� ������ ������� ������ ������ ������
			{			// ����� �� ���� ��������� � -1 �������� �������
				out[i + 1][0] = str; // ���������� � ��������� ������ � ������ ��������� �������
				char** temp = out[i];
				out[i] = out[i + 1];
				out[i + 1] = temp;
				return 0;
			}
			for (int j = 0; j < l_size - 1; j++) // ������� � ������� ��������
			{
				if (out[i-1][j] == 0)
				{
					out[i-1][j] = str;
					return 0;
				}
			}
			flag_p = i - 1; // ���� ������ �����, �� ��������� ������
			break;
		}
	}
	if (flag_p == -1) // �������� ������� �������, ��� 0 ������ < �������
	{
		if (r_alloc(out) == 1) // ���������� �������
		{
			cout << "������ ��� ��������� ������. ���������� ������." << endl;
			free(out);
			system("pause");
			return 1;
		}
		add_string(str, out); // ���������� ������
		return 0;
	}
	else
	if (flag_p != -1) // ������� ����� ��� �������, ������������
	{
		if (out[p_count - 1] != NULL) // ���� ������ �����, ��������� ������ ��� ������
			r_alloc(out);
		int i = 0;
		for (i = p_count; i > flag_p && out[i] == NULL; i--); // ������� ������ ����������� ������
		
		for (; i > flag_p; i--) // ����� ������ ���� ����������, ����� ��������������
		{
			out[i + 1] = out[i];
		}

		out[flag_p + 1] = (char**)calloc(l_size, l_size * sizeof(char*)); // ��������� ������ ��� ������

		for (int j = l_size / 2, k = 0; j < l_size; j++, k++) // ������� ��������
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