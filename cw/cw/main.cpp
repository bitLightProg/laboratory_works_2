/*
7. ������������ ������������� ������
����������� ����������� ������� ������������� ������������� ������, ��������� � �������� ����� ������������
������, ����������� ������� �������� ������������� ������ (malloc). ������������� ������� my_malloc ������
���������� ��������� �� ���������� �������, ������ � ������ ����� ���������� ������ ���� �������
������ ���������� �������, ����������� ��� �� �����������, ���� ��������� ������ �����������
��������� ����������. ��� ������������ ������ �������� my_free ������������ ����������� ��������
��������� ��������. ���������� ����� �������� ����������� �������� ��������� ������� ��� � ������� � ������
��������� (� �������) ��������. ��� ����������� �������� ������ ������� ��� �� ������ ������������
�������������� ������� ������, �� ���� ��������� �� � ��� �� �����, �� ��������� �������������� ���������
malloc � free. ������������� ����� �������� ��������� ������� ��� � ������� � ������������ ������� � ���������
��������. ������� ������������������ ������� � ������� ������������ ������ ��� ���������� �������� �����������
�� ���������� ������� ���������: ����������� ��������� ��������� �������� �� ���������/������������ ������:
������� ������������� ��������� N ��������� � �� ������ ������������ �  ������� ����������.
����� � ����� �� ����� ������� ���������� ����� �������� � �������������, ������������� ����� � ��� �����
���������� �� �� �� ����� �����. �������� ��������� ��� �������������� �������� �������������� � �����������
(����������) �������.
1.��������� ������� � ����������� ������. ���������� ������� � ����������� ������.
��������� �� �������� �������� �����������.
2.��������� ������� � ����������� ������. ������ ������� ������ � �������� ������.
���� ��� ������ �� ��������� �������� � ��������, ����� ����������� � ���������,
����� ������� ���������� �� �������� � �����. ������������ ��������  �� �������������,
� ������������ ��� ��������� ��������� ������ ���� �� �������.
3.��������� ������� � ������������ ������ ����������. ��������� �� �������� ������� �����������.
4.��������� ������� � ������������ ������ ����������. ������ ��������� ������� � �������� ������.
���� ��� ������ �� ��������� �������� � ��������, ����� ����������� � ���������,
����� ������� ���������� �� �������� � �����. ������������ ��������  �� �������������,
� ������������ ��� ��������� ��������� ������ ���� �� �������.
*/

#include <iostream>
#include <Windows.h>

using namespace std;

struct block_list
{
	block_list* next_element = NULL;
	void* block = NULL;
};

int print_memory(block_list* first_free_block, block_list* first_occupied_block)
{
	cout << "����� ������ ����: " << (int*)first_free_block - 1 << endl;
	cout << "������ " << sizeof(block_list) * 2 + sizeof(int) * 3 << " ���� ������ ���������� �������." << endl;
	cout << "����� ��������� ������:" << "\t\t\t����� ������� ������:"<< endl;
	block_list* current_free_block = first_free_block;
	block_list* current_occupied_block = first_occupied_block;
	for (;current_free_block != NULL || current_occupied_block != NULL;
		current_free_block != NULL ? current_free_block = current_free_block->next_element: 0,
			current_occupied_block != NULL ? current_occupied_block = current_occupied_block->next_element: 0)
	{
		if (current_free_block->block == NULL && current_occupied_block->block == NULL)
			break;
		if (current_free_block->block != NULL)
			cout << (int*)current_free_block->block << " �: " << *((int*)current_free_block->block - 1);
		if (current_occupied_block->block != NULL)
			cout << "\t\t\t" << (int*)current_occupied_block->block
			<< " �: " << *((int*)current_occupied_block->block - 1);

		cout << endl;
	}
	return 0;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int size = 1024;
	void* heap = calloc(size, size);

	int *pointer = (int*)heap;
	*pointer = sizeof(block_list);
	pointer++;
	block_list* current_block = (block_list*)pointer;
	block_list* first_free_block = current_block;
	current_block++;
	pointer = (int*)current_block;
	*pointer = sizeof(block_list);
	pointer++;
	block_list* first_occupied_block = (block_list*)pointer;

	first_free_block->block = first_occupied_block + 1;
	pointer = (int*)first_free_block->block;
	*pointer = size - (sizeof(block_list) * 2 + sizeof(int) * 3);
	first_free_block->block = pointer + 1;

	print_memory(first_free_block, first_occupied_block);

	free(heap);
	system("pause");
	return 0;
}