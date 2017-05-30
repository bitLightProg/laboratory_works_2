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

int print_memory(block_list* first_free_block, block_list* first_occupied_block)
{
	cout << "Адрес начала кучи: " << (int*)first_free_block - 1 << endl;
	cout << "Первые " << sizeof(block_list) * 2 + sizeof(int) * 3 << " Байт заняты системными данными." << endl;
	cout << "Блоки свободной памяти:" << "\t\t\tБлоки занятой памяти:"<< endl;
	block_list* current_free_block = first_free_block;
	block_list* current_occupied_block = first_occupied_block;
	for (;current_free_block != NULL || current_occupied_block != NULL;
		current_free_block != NULL ? current_free_block = current_free_block->next_element: 0,
			current_occupied_block != NULL ? current_occupied_block = current_occupied_block->next_element: 0)
	{
		if (current_free_block->block == NULL && current_occupied_block->block == NULL)
			break;
		if (current_free_block->block != NULL)
			cout << (int*)current_free_block->block << " Б: " << *((int*)current_free_block->block - 1);
		if (current_occupied_block->block != NULL)
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