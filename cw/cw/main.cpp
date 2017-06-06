/*
7. Динамическое распределение памяти
Разработать собственные функции динамического распределения памяти, используя в качестве «кучи» динамический
массив, создаваемый обычной функцией распределения памяти (malloc). Разработанная функция my_malloc должна
возвращать указатель на выделенную область, причем в память перед указателем должен быть записан
размер выделенной области, необходимый при ее возвращении, либо сохранена другая необходимая
системная информация. При освобождении памяти функцией my_free производится объединение соседних
свободных областей. Необходимы также средства отображения текущего состояния системы ДРП – размеры и адреса
свободных (и занятых) областей. Для собственных структур данных система ДРП не должна использовать
дополнительной внешней памяти, то есть размещать из в той же «куче», не используя дополнительных системных
malloc и free. Предусмотреть вывод текущего состояния системы ДРП – адресов и размерностей занятых и свободных
областей. Оценить производительность системы и степень фрагментации памяти при выполнении запросов зависимости
от количества занятых элементов: разработать генератор случайных запросов на выделение/освобождение памяти:
сначала запрашивается выделение N элементов и их адреса запоминаются в  массиве указателей.
Затем в цикле из этого массива выбирается любой фрагмент и освобождается, запрашивается новый и его адрес
помещается на то же самое место. Провести измерения при резервировании областей фиксированного и переменного
(случайного) размера.
1.Свободные области – односвязный список. Выделенные области – односвязный список.
Выделение по принципу наиболее подходящего.
2.Свободные области – односвязный список. Первый элемент списка – исходная “куча”.
Если при поиске не находится элемента с размером, точно совпадающим с требуемым,
новый элемент выделяется из элемента – “кучи”. Возвращаемые элементы  не “склеиваются”,
а используются при повторном выделении памяти того же размера.
3.Свободные области – динамический массив указателей. Выделение по принципу первого подходящего.
4.Свободные области – динамический массив указателей. Первый свободная область – исходная “куча”.
Если при поиске не находится элемента с размером, точно совпадающим с требуемым,
новый элемент выделяется из элемента – “кучи”. Возвращаемые элементы  не “склеиваются”,
а используются при повторном выделении памяти того же размера.
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
//char heap[2560];
int heap_size = 2560*1024;
int size_of_system_data = sizeof(block_list);

/*Выделяет нужным образом место размера size_of_insert_block в блоке current_free_block.
Возвращает адрес блока, под который выделялась память.*/
void* insert_block(block_list* &current_free_block, int size_of_inset_block)
{
	/*Запоминаем старые размер и адрес.*/
	int size_of_free_block = *((int*)current_free_block->block - 1);
	void* returning = current_free_block->block;

	/*Пересчитываем размер.*/
	int new_size_of_free_block = size_of_free_block - (size_of_inset_block + sizeof(int));
	/*Если не остаётся места для переадресовки свободного блока, оставляем всю память вставляемому блоку.*/
	if (new_size_of_free_block <= 0)
	{
		current_free_block->block = NULL;
		return returning;
	}

	/*Иначе записываем размер вставляемого блока, новый размер свободного блока и переносим адрес.*/
	*((int*)current_free_block->block - 1) = size_of_inset_block;
	current_free_block->block = (char*)current_free_block->block + size_of_inset_block + sizeof(int);
	*((int*)current_free_block->block - 1) = new_size_of_free_block;
	return returning;
}

/*Ищет наиболее подходящее место для вставки, которое больше или равно size_of_insert_block.
Возвращает указатель на подходящий элемент списка свободных блоков.
В случае неудачи возвращает NULL.*/
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

/*Вставляет блок с системными данными в кучу.
Возвращает адрес на вставленный системный блок.*/
block_list* add_system_block(block_list* &first_free_block, block_list* &first_occupied_block)
{
	block_list* place_to_insert = find_place(first_free_block, size_of_system_data);
	if (place_to_insert == NULL)
		return NULL;
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
	cout << "Адрес начала кучи: " << (int*)first_free_block - 1 << endl;
	cout << "Под системные данные выделено ";	
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
	cout << sys*size_of_system_data << " Байт." << endl;
	cout << "Под размерности данных выделено " << sizes*sizeof(int) << " Байт." << endl;

	current_free_block = first_free_block;
	current_occupied_block = first_occupied_block;

	//cout << "Первые " << sizeof(block_list) * 2 + sizeof(int) * 3 << " Байт заняты системными данными." << endl;
	cout << "Блоки свободной памяти:" << "\t\t\tБлоки занятой памяти:"<< endl;
	
	for (;current_free_block != NULL || current_occupied_block != NULL;
		current_free_block != NULL ? current_free_block = current_free_block->next_element: 0,
			current_occupied_block != NULL ? current_occupied_block = current_occupied_block->next_element: 0)
	{
		if ((current_free_block != NULL ? current_free_block->block == NULL: 1) && (current_occupied_block != NULL ? current_occupied_block->block == NULL: 1) )
			break;
		if ((current_free_block != NULL ? current_free_block->block != NULL : 0))
			cout << (int*)current_free_block->block << " Б: " << *((int*)current_free_block->block - 1);
		if ((current_occupied_block != NULL ? current_occupied_block->block != NULL : 0))
			cout << "\t\t\t" << (int*)current_occupied_block->block
			<< " Б: " << *((int*)current_occupied_block->block - 1);

		cout << endl;
	}
	return 0;
}

void press_system_blocks();

/*Выделяет память под блок размером size.
В случае неудачи возвращает NULL.*/
void* my_malloc(int size)
{
	/*Если задан неправильный размер.*/
	if (size <= 0)
		return NULL;
	block_list* first_free_block = (block_list*)((char*)heap + sizeof(int));
	press_system_blocks();
	/*Если в куче не осталось места*/
	if (first_free_block->block == NULL)
	{
		return NULL;
	}
	block_list* first_occupied_block = (block_list*)((char*)heap + size_of_system_data + sizeof(int)*2);

	block_list* current_occupied_block = first_occupied_block;
	/*Ищем крайний пустой элемент списка занятой памяти.*/
	while (current_occupied_block->block != NULL && current_occupied_block->next_element != NULL)
	{
		current_occupied_block = current_occupied_block->next_element;
	}

	/*Если он не пустой, то он последний. Создаём новый.*/
	if (current_occupied_block->block != NULL)
	{
		current_occupied_block->next_element = add_system_block(first_free_block, first_occupied_block);
		current_occupied_block = current_occupied_block->next_element;
		if (current_occupied_block == NULL)
			return NULL;
		if (first_free_block->block == NULL)
		{
			return NULL;
		}
	}

	block_list* insert_block_list = find_place(first_free_block, size);
	/*Если не удалось найти место для вставки.*/
	if (insert_block_list == NULL)
		return NULL;
	void* returning_pointer = insert_block(insert_block_list, size);
	/*Помещаем занятый блок в список.*/
	current_occupied_block->block = returning_pointer;
	return returning_pointer;
}

/*Сливает в блок first блок second.
В результате получается блок размером на 4 Байта больше суммы размеров старых блоков,
начинающийся с адреса first.*/
void* merge_blocks(void* first, void* second)
{
	int first_size = *((int*)first - 1);
	int second_size = *((int*)second - 1);
	*((int*)first - 1) = first_size + second_size + 4;
	return first;
}

void press_system_blocks()
{
	block_list* first_free_block = (block_list*)((char*)heap + sizeof(int));
	block_list* first_occupied_block = (block_list*)((char*)heap + size_of_system_data + sizeof(int) * 2);

	block_list* current_free_block = first_free_block;
	block_list* current_occupied_block = first_occupied_block;

	block_list* first_empty_free_list = NULL;
	/*Перенос блоков свободной памяти поближе к началу списка.*/
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
			current_free_block = first_free_block;
		}
		current_free_block = current_free_block->next_element;
	}
	current_free_block = first_free_block;

	block_list* first_empty_occupied_list = NULL;
	/*Перенос блоков занятой памяти поближе к началу списка.*/
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
			current_occupied_block = first_occupied_block;
		}
		current_occupied_block = current_occupied_block->next_element;
	}
	current_occupied_block = first_occupied_block;
}

/*Слитие ненужных элементов списков с областями свободной памяти.*/
void free_system_blocks()
{
	block_list* first_free_block = (block_list*)((char*)heap + sizeof(int));
	block_list* first_occupied_block = (block_list*)((char*)heap + size_of_system_data + sizeof(int) * 2);

	block_list* current_free_block = first_free_block;
	block_list* current_occupied_block = first_occupied_block;

	press_system_blocks();

	/*Последний не пустой из блоков свободной памяти.*/
	block_list* last_not_empty_free_block = first_free_block;
	//print_memory(first_free_block, first_occupied_block);
	while (last_not_empty_free_block->next_element != NULL &&
			last_not_empty_free_block->next_element->block != NULL)
	{
		last_not_empty_free_block = last_not_empty_free_block->next_element;
	}

	/*Последний не пустой из блоков занятой памяти.*/
	block_list* last_not_empty_occupied_block = first_occupied_block;
	while (last_not_empty_occupied_block->next_element != NULL &&
		last_not_empty_occupied_block->next_element->block != NULL)
	{
		last_not_empty_occupied_block = last_not_empty_occupied_block->next_element;
	}

	/*Поиск соседних с свободными блоками пустых системных блоков.*/
	for (;current_free_block != last_not_empty_free_block->next_element;
					current_free_block = current_free_block->next_element)
	{
		int size_of_current_free_block = *((int*)current_free_block->block - 1);

		block_list* prev_free_block = last_not_empty_free_block;
		block_list* this_free_block = prev_free_block->next_element;
		/*По списку свободной памяти.*/
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
		/*По списку занятой памяти*/
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

int pm(block_list* first_free_block, block_list* first_occupied_block, int byte = 0);

/*Освобождает память по адресу block. Если память не была зарезервирована, выходит из функции.*/
void my_free(void* block)
{
	/*Если передан нулевой адрес.*/
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
	/*Если адрес, переданный функции, не находится в списке занятой памяти.*/
	if (current_occupied_block == NULL)
	{
		return;
	}

	/*Убираем из списка блоков занятой памяти.*/
	

	/*Наводим порядок в списках.*/
	pm(first_free_block, first_occupied_block);
	current_occupied_block->block = NULL;
	free_system_blocks();
	pm(first_free_block, first_occupied_block);
	int size_of_block = *((int*)block - 1);

	block_list* current_free_block = first_free_block;
	/*Сливаем освободившуюся память со свободной памятью.*/
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
			pm(first_free_block, first_occupied_block);
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
			pm(first_free_block, first_occupied_block);
			return;
		}
			
	}

	/*Если не получилось слить освобожденный фрагмент с блоками свободной памяти.*/
	current_free_block = first_free_block;
	/*Ищем крайний пустой элемент списка свободной памяти.*/
	while (current_free_block->block != NULL && current_free_block->next_element != NULL)
	{
		current_free_block = current_free_block->next_element;
	}

	/*Если он не пустой, то он последний. Создаём новый.*/
	if (current_free_block->block != NULL)
	{
		current_free_block->next_element = add_system_block(first_free_block, first_occupied_block);
		current_free_block = current_free_block->next_element;
	}

	current_free_block->block = block;
	pm(first_free_block, first_occupied_block);
	return;
}

void my_free_2(void* block)
{
	
	/*Если передан нулевой адрес.*/
	if (block == NULL)
	{
		return;
	}

	block_list* first_free_block = (block_list*)((char*)heap + sizeof(int));
	block_list* first_occupied_block = (block_list*)((char*)heap + size_of_system_data + sizeof(int) * 2);

	/*if ((char*)block - (char*)heap >= 21447 && (char*)block - (char*)heap <= 23447)
	{
		cout << "Здесь" << endl;
		pm(first_free_block, first_occupied_block, (char*)block - (char*)heap);
	}*/

	block_list* current_occupied_block = first_occupied_block;
	block_list* prev_occupied_block = current_occupied_block;

	while (current_occupied_block != NULL && current_occupied_block->block != block)
	{
		prev_occupied_block = current_occupied_block;
		current_occupied_block = current_occupied_block->next_element;
	}
	/*Если адрес, переданный функции, не находится в списке занятой памяти.*/
	if (current_occupied_block == NULL)
	{
		return;
	}

	/*Убираем из списка блоков занятой памяти.*/
	current_occupied_block->block = NULL;

	press_system_blocks();

	block_list* current_free_block = first_free_block;

	while (current_free_block->next_element != NULL)
	{
		current_free_block = current_free_block->next_element;
	}
	current_occupied_block = first_occupied_block;
	prev_occupied_block = current_occupied_block;
	while (current_occupied_block->next_element != NULL)
	{
		prev_occupied_block = current_occupied_block;
		current_occupied_block = current_occupied_block->next_element;
	}
	//pm(first_free_block, first_occupied_block);
	if (current_occupied_block != first_occupied_block)
	{
		current_free_block->next_element = current_occupied_block;
		prev_occupied_block->next_element = NULL;
		current_occupied_block->next_element = NULL;
		current_occupied_block->block = block;
	}
	else
	{
		if (current_free_block->block == NULL)
		{
			current_free_block->block = block;
			current_occupied_block->block = NULL;
			prev_occupied_block->next_element = NULL;
		}
		else
		{
			current_free_block->next_element = add_system_block(first_free_block, first_occupied_block);
			current_free_block = current_free_block->next_element;
			current_free_block->block = block;
			current_occupied_block->block = NULL;
			prev_occupied_block->next_element = NULL;
		}
	}
	//print_memory(first_free_block, first_occupied_block);
	//pm(first_free_block, first_occupied_block);
	free_system_blocks();
	//pm(first_free_block, first_occupied_block);
	//print_memory(first_free_block, first_occupied_block);

	current_free_block = first_free_block;
	
	while (current_free_block != NULL && current_free_block->block != NULL)
	{
		//pm(first_free_block, first_occupied_block, (char*)block - (char*)heap);
		/*if (*((int*)current_free_block->block - 1) == 1110)
		{
			cout << "Здесь" << endl;
		}
		if (current_free_block->block == (char*)heap + 1450)
		{
			cout << "Здесь" << endl;
		}*/
		//pm(first_free_block, first_occupied_block, (int)((char*)current_free_block->block - heap));
		//int size_of_current_free_block = *((int*)current_free_block->block - 1);
		block_list* second_free_block = current_free_block->next_element;
		int flag = 1;
		while (second_free_block != NULL && second_free_block->block != NULL)
		{
			flag = 0;
			//int size_of_second_free_block = *((int*)second_free_block->block - 1);
			current_occupied_block = first_occupied_block;
			while (current_occupied_block != NULL && current_occupied_block->block != NULL)
			{
				current_free_block->block > second_free_block->block ?
					current_occupied_block->block > second_free_block->block &&
					current_occupied_block->block < current_free_block->block ? flag = 1 : flag = 0
					: current_occupied_block->block > current_free_block->block &&
					current_occupied_block->block < second_free_block->block ? flag = 1 : flag = 0;

				if (flag == 1)
					break;

				current_occupied_block = current_occupied_block->next_element;
			}
			if (flag == 1)
			{
				//flag = 0;
				second_free_block = second_free_block->next_element;
				continue;
			}

			break;
			//second_free_block = second_free_block->block;
		}

		if (flag == 1)
		{
			current_free_block = current_free_block->next_element;
			continue;
		}


		
		int reverse = 0;
after_reverse: after_sys_merge:
		if (current_free_block->block < second_free_block->block)
		{
			//pm(first_free_block, first_occupied_block, (int)((char*)current_free_block->block - heap));
	int size_of_current_free_block = *((int*)current_free_block->block - 1);
	int size_of_second_free_block = *((int*)second_free_block->block - 1);
	//pm(first_free_block, first_occupied_block, (int)((char*)current_free_block->block - 32 - heap));

			if ((char*)current_free_block->block + size_of_current_free_block + sizeof(int) ==
				second_free_block->block)
			{
				current_free_block->block = merge_blocks(current_free_block->block, second_free_block->block);
				second_free_block->block = NULL;
				if (reverse == 1)
				{
					reverse = 0;
					void* pointer = current_free_block;
					current_free_block = second_free_block;
					second_free_block = (block_list*)pointer;
				}
				free_system_blocks();
				current_free_block = first_free_block;
				continue;
			}
			else
			{
				block_list* system_free_block = first_free_block->next_element;
				block_list* prev_system_free_block = first_free_block;
				int is_next_system = 0;
				while (system_free_block != NULL)
				{
					if ((char*)current_free_block->block + size_of_current_free_block + sizeof(int) ==
						(char*)system_free_block)
					{
						is_next_system = 1;
						break;
					}
					if ((system_free_block->block != NULL) && ((char*)current_free_block->block
						+ size_of_current_free_block + sizeof(int) == (char*)system_free_block->block))
					{
						is_next_system = 3;
						break;
					}
					prev_system_free_block = system_free_block;
					system_free_block = system_free_block->next_element;
				}

				block_list* system_occupied_block = first_occupied_block->next_element;
				block_list* prev_system_occupied_block = first_occupied_block;
				while (system_occupied_block != NULL)
				{
					if ((char*)current_free_block->block + size_of_current_free_block + sizeof(int) ==
						(char*)system_occupied_block)
					{
						is_next_system = 2;
						break;
					}
					prev_system_occupied_block = system_occupied_block;
					system_occupied_block = system_occupied_block->next_element;
				}

				if (is_next_system == 1)
				{
					if (system_free_block->block == current_free_block->block)
					{
						//pm(first_free_block, first_occupied_block);
						//cout << "Здесь";
						block_list data = *system_free_block;
						current_free_block->block = merge_blocks(current_free_block->block, system_free_block);
						prev_system_free_block->next_element = (block_list*)insert_block(current_free_block, size_of_system_data);
						*(prev_system_free_block->next_element) = data;
						(prev_system_free_block->next_element->block) = (char*)(prev_system_free_block->next_element->block) + size_of_system_data + sizeof(int);
						current_free_block = prev_system_free_block->next_element;
					}
					/*else if (system_free_block->block == second_free_block->block)
					{
						//cout << "Здесь" << endl;
					}*/
					else
					{
						block_list data = *system_free_block;
						current_free_block->block = merge_blocks(current_free_block->block, system_free_block);
						prev_system_free_block->next_element = (block_list*)insert_block(current_free_block, size_of_system_data);
						*(prev_system_free_block->next_element) = data;
					}
					if (second_free_block == system_free_block)
					{
						second_free_block = prev_system_free_block->next_element;
					}
					//pm(first_free_block, first_occupied_block);
					system_free_block = prev_system_free_block->next_element;
					press_system_blocks();
					goto after_sys_merge; // Да простит меня бог.
				}
				else if (is_next_system == 2)
				{
					block_list data = *system_occupied_block;
					current_free_block->block = merge_blocks(current_free_block->block, system_occupied_block);
					prev_system_occupied_block->next_element = (block_list*)insert_block(current_free_block, size_of_system_data);
					*(prev_system_occupied_block->next_element) = data;
					press_system_blocks();
					goto after_sys_merge; // Да простит меня бог.
				}
				else if (is_next_system == 3)
				{
					//pm(first_free_block, first_occupied_block);
					current_free_block->block = merge_blocks(current_free_block->block, system_free_block->block);
					//current_free_block->block = system_free_block->block;
					system_free_block->block = NULL;
					press_system_blocks();
					//system_free_block->block = NULL;
					//pm(first_free_block, first_occupied_block);
					goto after_sys_merge; // Да простит меня бог.
				}
				else
				{
					print_memory(first_free_block, first_occupied_block);
					pm(first_free_block, first_occupied_block, (int)((char*)current_free_block->block - heap));
					cout << "Сюда он никогда не зайдет.";
					throw "it_was_here";
				}
			}
		}
		else if (current_free_block->block > second_free_block->block)
		{
			reverse = 1;
			void* pointer = current_free_block;
			current_free_block = second_free_block;
			second_free_block = (block_list*)pointer;
			goto after_reverse; // И не спрашивайте, зачем. Я устал.
		}


	}
	
	press_system_blocks();
	return;

}

int pm(block_list* first_free_block, block_list* first_occupied_block, int byte)
{
	char ch = 0;
	int k = 1;
	for (int i = byte; i < heap_size; i++)
	{
		int f = 0;
		block_list* cf = first_free_block;
		block_list* co = first_occupied_block;
		while (cf != NULL)
		{
			if (cf->block == NULL)
			{
				if (((char*)heap + i >= (char*)cf) && ((char*)heap + i < (char*)cf + *((int*)cf - 1)))
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
			if (((char*)heap + i >= (char*)cf) && ((char*)heap + i < (char*)cf + *((int*)cf - 1)))
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
				if (((char*)heap + i >= (char*)co) && ((char*)heap + i < (char*)co + *((int*)co - 1)))
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
			if (((char*)heap + i >= (char*)co) && ((char*)heap + i < (char*)co + *((int*)co - 1)))
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
	/*for (int i = 0; i < heap_size; i++)
		heap[i] = 0xCD;*/

	/*Запись начала списка свободной памяти*/
	int *pointer = (int*)heap;
	*pointer = sizeof(block_list);
	pointer++;
	block_list* current_block = (block_list*)pointer;
	block_list* first_free_block = current_block;
	first_free_block->block = NULL;
	first_free_block->next_element = NULL;
	current_block++;

	/*Запись начала списка занятой памяти*/
	pointer = (int*)current_block;
	*pointer = sizeof(block_list);
	pointer++;
	block_list* first_occupied_block = (block_list*)pointer;
	first_occupied_block->block = NULL;
	first_occupied_block->next_element = NULL;

	/*Запись ссылки на первый блок свободной памяти*/
	first_free_block->block = first_occupied_block + 1;
	pointer = (int*)first_free_block->block;
	*pointer = heap_size - (sizeof(block_list) * 2 + sizeof(int) * 3);
	first_free_block->block = pointer + 1;

	print_memory(first_free_block, first_occupied_block);
	
	void* a[5000];
	for (int i = 0; i < 50; i++)
	{
		a[i] = 0;
		a[i] = my_malloc(1 + rand() % 1000);
//		if (i > 820)
//			print_memory(first_free_block, first_occupied_block);
		//pm(first_free_block, first_occupied_block);
	}
	print_memory(first_free_block, first_occupied_block);
	for (int i = 0; i < 500000; i++)
	{
		int k = rand() % 50;
		/*if (i > 85)
			print_memory(first_free_block, first_occupied_block);*/
		my_free_2(a[k]);
		a[k] = my_malloc(1 + rand() % 1000);
	}
	print_memory(first_free_block, first_occupied_block);
	//pm(first_free_block, first_occupied_block);
	/*for (int i = 0; i < 50; i++)
	{
		my_free_2(a[i]);
		print_memory(first_free_block, first_occupied_block);
		//pm(first_free_block, first_occupied_block);
	}*/
	//pm(first_free_block, first_occupied_block);
	//print_memory(first_free_block, first_occupied_block);
	/*for (int i = 0; i < 50; i++)
	{
		a[i] = 0;
		a[i] = my_malloc(10);
		//pm(first_free_block, first_occupied_block);
	}*/
	//print_memory(first_free_block, first_occupied_block);
	/*for (int i = 0; i < 50; i++)
	{
		my_free_2(a[i]);
	}*/
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