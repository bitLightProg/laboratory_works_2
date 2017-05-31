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


void* heap = NULL;
int heap_size = 256;
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

/*���� �������� ���������� ����� ��� �������, ������� ������ ��� ����� size_of_insert_block.
���������� ��������� �� ���������� ������� ������ ��������� ������.
� ������ ������� ���������� NULL.*/
block_list* find_place(block_list* first_free_block, int size_of_inset_block)
{
	block_list* current_free_block = first_free_block;
	block_list* returning = NULL;
	int min_difference = *((int*)current_free_block->block - 1);
	while (current_free_block != NULL && current_free_block->block != NULL)
	{
		int size_of_block = *((int*)current_free_block->block - 1);
		if (size_of_block >= size_of_inset_block && (size_of_block - size_of_inset_block < min_difference))
		{
			returning = current_free_block;
			min_difference = size_of_block - size_of_inset_block;
			if (min_difference == 0)
				break;
		}
		current_free_block = current_free_block->next_element;
	}
	return returning;
}

/*��������� ���� � ���������� ������� � ����.
���������� ����� �� ����������� ��������� ����.*/
block_list* add_system_block(block_list* &first_free_block, block_list* &first_occupied_block)
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

/*�������� ������ ��� ���� �������� size.
� ������ ������� ���������� NULL.*/
void* my_malloc(int size)
{
	/*���� ����� ������������ ������.*/
	if (size <= 0)
		return NULL;
	block_list* first_free_block = (block_list*)((char*)heap + sizeof(int));
	/*���� � ���� �� �������� �����*/
	if (first_free_block->block == NULL)
	{
		return NULL;
	}
	block_list* first_occupied_block = (block_list*)((char*)heap + size_of_system_data + sizeof(int)*2);

	block_list* current_occupied_block = first_occupied_block;
	/*���� ������� ������ ������� ������ ������� ������.*/
	while (current_occupied_block->block != NULL && current_occupied_block->next_element != NULL)
	{
		current_occupied_block = current_occupied_block->next_element;
	}

	/*���� �� �� ������, �� �� ���������. ������ �����.*/
	if (current_occupied_block->block != NULL)
	{
		current_occupied_block->next_element = add_system_block(first_free_block, first_occupied_block);
		current_occupied_block = current_occupied_block->next_element;
	}

	block_list* insert_block_list = find_place(first_free_block, size);
	/*���� �� ������� ����� ����� ��� �������.*/
	if (insert_block_list == NULL)
		return NULL;
	void* returning_pointer = insert_block(insert_block_list, size);
	/*�������� ������� ���� � ������.*/
	current_occupied_block->block = returning_pointer;
	return returning_pointer;
}

/*������� � ���� first ���� second.
� ���������� ���������� ���� �������� �� 4 ����� ������ ����� �������� ������ ������,
������������ � ������ first.*/
void* merge_blocks(void* first, void* second)
{
	int first_size = *((int*)first - 1);
	int second_size = *((int*)second - 1);
	*((int*)first - 1) = first_size + second_size + 4;
	return first;
}

/*������ �������� ��������� ������� � ��������� ��������� ������.*/
void free_system_blocks()
{
	block_list* first_free_block = (block_list*)((char*)heap + sizeof(int));
	block_list* first_occupied_block = (block_list*)((char*)heap + size_of_system_data + sizeof(int) * 2);

	block_list* current_free_block = first_free_block;
	block_list* current_occupied_block = first_occupied_block;

	block_list* first_empty_free_list = NULL;
	/*������� ������ ��������� ������ ������� � ������ ������.*/
	while (current_free_block != NULL)
	{
		if (current_free_block->block == NULL && first_empty_free_list == NULL)
		{
			first_empty_free_list = current_free_block;
		}
		else if (first_empty_free_list != NULL && current_free_block->block != NULL)
		{
			first_empty_free_list->block = current_free_block->block;
			current_free_block->block = NULL;
			first_empty_free_list = NULL;
		}
		current_free_block = current_free_block->next_element;
	}
	current_free_block = first_free_block;

	block_list* first_empty_occupied_list = NULL;
	/*������� ������ ������� ������ ������� � ������ ������.*/
	while (current_occupied_block != NULL)
	{
		if (current_occupied_block->block == NULL && first_empty_occupied_list == NULL)
		{
			first_empty_occupied_list = current_occupied_block;
		}
		else if (first_empty_occupied_list != NULL && current_occupied_block->block != NULL)
		{
			first_empty_occupied_list->block = current_occupied_block->block;
			current_occupied_block->block = NULL;
			first_empty_occupied_list = NULL;
		}
		current_occupied_block = current_occupied_block->next_element;
	}
	current_occupied_block = first_occupied_block;

	/*��������� �� ������ �� ������ ��������� ������.*/
	block_list* last_not_empty_free_block = first_free_block;
	while (last_not_empty_free_block->next_element != NULL &&
			last_not_empty_free_block->next_element->block != NULL)
	{
		last_not_empty_free_block = last_not_empty_free_block->next_element;
	}

	/*��������� �� ������ �� ������ ������� ������.*/
	block_list* last_not_empty_occupied_block = first_occupied_block;
	while (last_not_empty_occupied_block->next_element != NULL &&
		last_not_empty_occupied_block->next_element->block != NULL)
	{
		last_not_empty_occupied_block = last_not_empty_occupied_block->next_element;
	}

	/*����� �������� � ���������� ������� ������ ��������� ������.*/
	for (;current_free_block != last_not_empty_free_block->next_element;
					current_free_block = current_free_block->next_element)
	{
		int size_of_current_free_block = *((int*)current_free_block->block - 1);

		block_list* prev_free_block = last_not_empty_free_block;
		block_list* this_free_block = prev_free_block->next_element;
		/*�� ������ ��������� ������.*/
		for (;this_free_block != NULL;)
		{
			if ((void*)((char*)current_free_block->block + size_of_current_free_block) ==
				(void*)((int*)this_free_block - 1))
			{
				current_free_block->block = merge_blocks(current_free_block->block, this_free_block);
				size_of_current_free_block = *((int*)current_free_block->block - 1);
				prev_free_block->next_element = this_free_block->next_element;
				prev_free_block = last_not_empty_free_block;
				this_free_block = prev_free_block->next_element;
				//this_free_block = this_free_block->next_element;
			}
			else
			if ((void*)((char*)this_free_block + size_of_system_data) ==
				(void*)((int*)current_free_block->block - 1))
			{
				current_free_block->block = merge_blocks(this_free_block, current_free_block->block);
				size_of_current_free_block = *((int*)current_free_block->block - 1);
				prev_free_block->next_element = this_free_block->next_element;
				prev_free_block = last_not_empty_free_block;
				this_free_block = prev_free_block->next_element;
				//this_free_block = this_free_block->next_element;
			}
			else
			{
				prev_free_block = this_free_block;
				this_free_block = this_free_block->next_element;
			}
		}

		block_list* prev_occupied_block = last_not_empty_occupied_block;
		block_list* this_occupied_block = prev_occupied_block->next_element;
		/*�� ������ ������� ������*/
		for (; this_occupied_block != NULL;)
		{
			if ((void*)((char*)current_free_block->block + size_of_current_free_block) ==
				(void*)((int*)this_occupied_block - 1))
			{
				current_free_block->block = merge_blocks(current_free_block->block, this_occupied_block);
				size_of_current_free_block = *((int*)current_free_block->block - 1);
				prev_occupied_block->next_element = this_occupied_block->next_element;
				prev_occupied_block = last_not_empty_occupied_block;
				this_occupied_block = prev_occupied_block->next_element;
				//this_occupied_block = this_occupied_block->next_element;
			}
			else
				if ((void*)((char*)this_occupied_block + size_of_system_data) ==
					(void*)((int*)current_free_block->block - 1))
				{
					current_free_block->block = merge_blocks(this_occupied_block, current_free_block->block);
					size_of_current_free_block = *((int*)current_free_block->block - 1);
					prev_occupied_block->next_element = this_occupied_block->next_element;
					prev_occupied_block = last_not_empty_occupied_block;
					this_occupied_block = prev_occupied_block->next_element;
					//this_occupied_block = this_occupied_block->next_element;
				}
				else
				{
					prev_occupied_block = this_occupied_block;
					this_occupied_block = this_occupied_block->next_element;
				}
		}
	}
	return;
}

/*����������� ������ �� ������ block. ���� ������ �� ���� ���������������, ������� �� �������.*/
void my_free(void* block)
{
	/*���� ������� ������� �����.*/
	if (block == NULL)
	{
		return;
	}

	block_list* first_free_block = (block_list*)((char*)heap + sizeof(int));
	block_list* first_occupied_block = (block_list*)((char*)heap + size_of_system_data + sizeof(int) * 2);

	block_list* current_occupied_block = first_occupied_block;
	
	while (current_occupied_block != NULL && current_occupied_block->block != block)
	{
		current_occupied_block = current_occupied_block->next_element;
	}
	/*���� �����, ���������� �������, �� ��������� � ������ ������� ������.*/
	if (current_occupied_block == NULL)
	{
		return;
	}

	/*������� �� ������ ������ ������� ������.*/
	current_occupied_block->block = NULL;

	/*������� ������� � �������.*/
	free_system_blocks();
	int size_of_block = *((int*)block - 1);

	block_list* current_free_block = first_free_block;
	/*������� �������������� ������ �� ��������� �������.*/
	for (; current_free_block != NULL; current_free_block = current_free_block->next_element)
	{
		int size_of_current_free_block = *((int*)current_free_block->block - 1);

		if ((void*)((char*)current_free_block->block + size_of_current_free_block) ==
			(void*)((int*)block - 1))
		{
			current_free_block->block = merge_blocks(current_free_block->block, block);
			size_of_current_free_block = *((int*)current_free_block->block - 1);
			current_occupied_block->block = NULL;
			free_system_blocks();
			return;
		}
		else
		if ((void*)((char*)block + size_of_block) ==
				(void*)((int*)current_free_block->block - 1))
		{
			current_free_block->block = merge_blocks(block, current_free_block->block);
			size_of_current_free_block = *((int*)current_free_block->block - 1);
			current_occupied_block->block = NULL;
			free_system_blocks();
			return;
		}
			
	}

	/*���� �� ���������� ����� ������������� �������� � ������� ��������� ������.*/
	current_free_block = first_free_block;
	/*���� ������� ������ ������� ������ ��������� ������.*/
	while (current_free_block->block != NULL && current_free_block->next_element != NULL)
	{
		current_free_block = current_free_block->next_element;
	}

	/*���� �� �� ������, �� �� ���������. ������ �����.*/
	if (current_free_block->block != NULL)
	{
		current_free_block->next_element = add_system_block(first_free_block, first_occupied_block);
		current_free_block = current_free_block->next_element;
	}

	current_free_block->block = block;

	return;
}

int pm(block_list* first_free_block, block_list* first_occupied_block)
{
	char ch = 0;
	int k = 1;
	for (int i = 0; i < heap_size; i++)
	{
		int f = 0;
		block_list* cf = first_free_block;
		block_list* co = first_occupied_block;
		while (cf != NULL)
		{
			if (cf->block == NULL)
			{
				if (((char*)heap + i >= (char*)cf) && ((char*)heap + i < (char*)cf + size_of_system_data))
				{
					if (ch == 0)
						ch = 's';
					else
						if (ch == 's')
							k++;
						else
						{
							cout << ch << k;
							k = 1;
							ch = 's';
						}
					//cout << "s";
					f = 1;
					break;
				}
				cf = cf->next_element;
				continue;
			}
			if (((char*)heap + i >= (char*)cf->block) && ((char*)heap + i < (char*)cf->block + *((int*)cf->block - 1)))
			{
				if (ch == 0)
					ch = 'f';
				else
					if (ch == 'f')
						k++;
					else
					{
						cout << ch << k;
						k = 1;
						ch = 'f';
					}
				//cout << "f";
				f = 1;
				break;
			}
			else
			if (((char*)heap + i >= (char*)cf) && ((char*)heap + i < (char*)cf + size_of_system_data))
			{
				if (ch == 0)
					ch = 's';
				else
					if (ch == 's')
						k++;
					else
					{
						cout << ch << k;
						k = 1;
						ch = 's';
					}
				//cout << "s";
				f = 1;
				break;
			}
			cf = cf->next_element;
		}
		if (f)
			continue;
		while (co != NULL)
		{
			if (co->block == NULL)
			{
				if (((char*)heap + i >= (char*)co) && ((char*)heap + i < (char*)co + size_of_system_data))
				{
					if (ch == 0)
						ch = 's';
					else
						if (ch == 's')
							k++;
						else
						{
							cout << ch << k;
							k = 1;
							ch = 's';
						}
					//cout << "s";
					f = 1;
					break;
				}
				co = co->next_element;
				continue;
			}
			if (((char*)heap + i >= (char*)co->block) && ((char*)heap + i < (char*)co->block + *((int*)co->block - 1)))
			{
				if (ch == 0)
					ch = 'o';
				else
					if (ch == 'o')
						k++;
					else
					{
						cout << ch << k;
						k = 1;
						ch = 'o';
					}
				//cout << "o";
				f = 1;
				break;
			}
			else
			if (((char*)heap + i >= (char*)co) && ((char*)heap + i < (char*)co + size_of_system_data))
			{
				if (ch == 0)
					ch = 's';
				else
					if (ch == 's')
						k++;
					else
					{
						cout << ch << k;
						k = 1;
						ch = 's';
					}
				//cout << "s";
				f = 1;
				break;
			}
			co = co->next_element;
		}
		if (f)
			continue;

		if (ch == 0)
			ch = 'n';
		else
			if (ch == 'n')
				k++;
			else
			{
				cout << ch << k;
				k = 1;
				ch = 'n';
			}
		//cout << "n";

	}
	cout << ch << k << endl;
	return 0;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
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
	
	void* a[50];
	for (int i = 0; i < 5; i++)
	{
		a[i] = 0;
		a[i] = my_malloc(10);
		pm(first_free_block, first_occupied_block);
	}
	print_memory(first_free_block, first_occupied_block);
	//pm(first_free_block, first_occupied_block);
	for (int i = 0; i < 5; i++)
	{
		my_free(a[i]);
		pm(first_free_block, first_occupied_block);
	}
	//print_memory(first_free_block, first_occupied_block);
	for (int i = 0; i < 5; i++)
	{
		a[i] = 0;
		a[i] = my_malloc(10);
		pm(first_free_block, first_occupied_block);
	}
	//print_memory(first_free_block, first_occupied_block);
	for (int i = 0; i < 2; i++)
	{
		my_free(a[i]);
	}
	//print_memory(first_free_block, first_occupied_block);
	/*for (int i = 0; i < 50; i++)
	{
		a[i] = 0;
		a[i] = my_malloc(1024 * 1024);
	}
	print_memory(first_free_block, first_occupied_block);
	for (int i = 0; i < 50; i++)
	{
		my_free(a[i]);
	}
	print_memory(first_free_block, first_occupied_block);*/
	/*block_list* tail = first_free_block;
	for (int i = 0; i < 200; i++)
	{
		tail->next_element = (block_list*) add_system_block(first_free_block, first_occupied_block);
		tail = tail->next_element;
	}*/
	

	/*free_system_blocks();
	print_memory(first_free_block, first_occupied_block);*/

	free(heap);
	system("pause");
	return 0;
}