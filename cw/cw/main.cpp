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


int heap_size = 1024*1024*200;
int size_of_system_data = sizeof(block_list);

/*�������� ������ ������� ����� ������� size_of_insert_block � ����� current_free_block.
���������� ����� �����, ��� ������� ���������� ������.*/
void* insert_block(block_list* &current_free_block, int size_of_inset_block)
{
	/*���������� ������ ������ � �����.*/
	int size_of_free_block = *((int*)current_free_block->block - 1);
	void* returning = current_free_block->block;

	/*������������� ������.*/
	int new_size_of_free_block = size_of_free_block - (size_of_inset_block + sizeof(int));
	/*���� �� ������� ����� ��� ������������� ���������� �����, ��������� ��� ������ ������������ �����.*/
	if (new_size_of_free_block <= 0)
	{
		current_free_block->block = NULL;
		return returning;
	}

	/*����� ���������� ������ ������������ �����, ����� ������ ���������� ����� � ��������� �����.*/
	*((int*)current_free_block->block - 1) = size_of_inset_block;
	current_free_block->block = (char*)current_free_block->block + size_of_inset_block + sizeof(int);
	*((int*)current_free_block->block - 1) = new_size_of_free_block;
	return returning;
}

/*���� ���������� ����� ��� �������, ������� ������ ��� ����� size_of_insert_block.
���������� ��������� �� ���������� ������� ������ ��������� ������.
� ������ ������� ���������� NULL.*/
block_list* find_place(block_list* first_free_block, int size_of_inset_block)
{
	block_list* current_free_block = first_free_block;
	while (current_free_block != NULL)
	{
		if (*((int*)current_free_block->block - 1) >= size_of_inset_block)
		{
			break;
		}
		current_free_block = current_free_block->next_element;
	}
	return current_free_block;
}

/*��������� ���� � ���������� ������� � ����.
���������� ����� �� ����������� ��������� ����.*/
void* add_system_block(block_list* &first_free_block, block_list* &first_occupied_block)
{
	block_list* place_to_insert = find_place(first_free_block, size_of_system_data);
	block_list* new_system_block = (block_list*)insert_block(place_to_insert, size_of_system_data);
	new_system_block->block = NULL;
	new_system_block->next_element = NULL;
	return new_system_block;
}

int print_memory(block_list* first_free_block, block_list* first_occupied_block)
{
	block_list* current_free_block = first_free_block;
	block_list* current_occupied_block = first_occupied_block;
	int sys = 0, sizes = 0;
	cout << "����� ������ ����: " << (int*)first_free_block - 1 << endl;
	cout << "��� ��������� ������ �������� ";	
	for (; current_free_block != NULL; current_free_block = current_free_block->next_element)
	{
		sys++;
		sizes++;
		if (current_free_block->block != NULL)
			sizes++;
	}
	for (; current_occupied_block != NULL; current_occupied_block = current_occupied_block->next_element)
	{
		sys++;
		sizes++;
		if (current_occupied_block->block != NULL)
			sizes++;
	}
	cout << sys*size_of_system_data << " ����." << endl;
	cout << "��� ����������� ������ �������� " << sizes*sizeof(int) << " ����." << endl;

	current_free_block = first_free_block;
	current_occupied_block = first_occupied_block;

	//cout << "������ " << sizeof(block_list) * 2 + sizeof(int) * 3 << " ���� ������ ���������� �������." << endl;
	cout << "����� ��������� ������:" << "\t\t\t����� ������� ������:"<< endl;
	
	for (;current_free_block != NULL || current_occupied_block != NULL;
		current_free_block != NULL ? current_free_block = current_free_block->next_element: 0,
			current_occupied_block != NULL ? current_occupied_block = current_occupied_block->next_element: 0)
	{
		if ((current_free_block != NULL ? current_free_block->block == NULL: 1) && (current_occupied_block != NULL ? current_occupied_block->block == NULL: 1) )
			break;
		if ((current_free_block != NULL ? current_free_block->block != NULL : 0))
			cout << (int*)current_free_block->block << " �: " << *((int*)current_free_block->block - 1);
		if ((current_occupied_block != NULL ? current_occupied_block->block != NULL : 0))
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
	
	void* heap;
	heap = malloc(heap_size);

	/*������ ������ ������ ��������� ������*/
	int *pointer = (int*)heap;
	*pointer = sizeof(block_list);
	pointer++;
	block_list* current_block = (block_list*)pointer;
	block_list* first_free_block = current_block;
	first_free_block->block = NULL;
	first_free_block->next_element = NULL;
	current_block++;

	/*������ ������ ������ ������� ������*/
	pointer = (int*)current_block;
	*pointer = sizeof(block_list);
	pointer++;
	block_list* first_occupied_block = (block_list*)pointer;
	first_occupied_block->block = NULL;
	first_occupied_block->next_element = NULL;

	/*������ ������ �� ������ ���� ��������� ������*/
	first_free_block->block = first_occupied_block + 1;
	pointer = (int*)first_free_block->block;
	*pointer = heap_size - (sizeof(block_list) * 2 + sizeof(int) * 3);
	first_free_block->block = pointer + 1;

	print_memory(first_free_block, first_occupied_block);

	
	block_list* tail = first_free_block;
	for (int i = 0; i < 50; i++)
	{
		tail->next_element = (block_list*) add_system_block(first_free_block, first_occupied_block);
		tail = tail->next_element;
	}
	print_memory(first_free_block, first_occupied_block);

	free(heap);
	system("pause");
	return 0;
}