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


int heap_size = 1024*1024*200;
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

/*Ищет подходящее место для вставки, которое больше или равно size_of_insert_block.
Возвращает указатель на подходящий элемент списка свободных блоков.
В случае неудачи возвращает NULL.*/
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

/*Вставляет блок с системными данными в кучу.
Возвращает адрес на вставленный системный блок.*/
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

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	void* heap;
	heap = malloc(heap_size);

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