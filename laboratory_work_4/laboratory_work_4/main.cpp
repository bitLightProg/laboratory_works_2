//9. Разность двух циклических списков.
#include <iostream>

using namespace std;

struct some_list
{
	some_list *next = NULL;
	int some_int = 0;
};

some_list** create_empty_list()
{
	some_list **out_list = new some_list*[2];
	out_list[0] = NULL;
	out_list[1] = NULL;
	return out_list;
}

int delete_list(some_list** deleted_list)
{
	some_list* deleted_element = deleted_list[0];
	
	if (deleted_element == NULL)
		return 1;
	if (deleted_list[1] != NULL)
		deleted_list[1]->next = NULL;
	some_list* next_element = deleted_element->next;

	while (next_element != NULL)
	{
		delete deleted_element;
		deleted_element = next_element;
		
		next_element = deleted_element->next;
	}
	delete deleted_element;
	return 0;
}

int add_element(some_list** list, some_list *element)
{
	if (list[0] == NULL)
	{
		element->next = element;
		list[0] = element;
		list[1] = list[0];
		return 0;
	}
	else
	{
		element->next = list[0];
		list[1]->next = element;
		list[1] = element;
	}
	return 0;
}

int copy_list(some_list** from, some_list** to)
{
	some_list* this_element = from[0];

	if (this_element == NULL)
	{
		return 1;
	}

	do
	{
		some_list *p = new some_list;
		p->some_int = this_element->some_int;
		add_element(to, p);
		this_element = this_element->next;
	} while (this_element != from[0]);
	return 0;
}

int print_list(some_list** a)
{
	some_list* this_element = a[0];

	if (this_element == NULL)
	{
		cout << "Список пуст." << endl;
		return 1;
	}
		
	
	some_list* next_element = this_element->next;
	cout << "Элементы списка: ";

	do
	{
		cout << this_element->some_int << " ";
		this_element = this_element->next;
	} while (this_element != a[0]);
	cout << endl;
	return 0;
}

int comp_list(void* p1, void* p2, unsigned int size)
{
	char* ph1 = (char*)p1;
	char* ph2 = (char*)p2;
	for (int i = sizeof(char*); i < size; i++)
	{
		if (*(ph1 + i) != *(ph2 + i))
			return 1;
	}
	return 0;
}

some_list** difference(some_list** l1, some_list** l2)
{
	some_list** out_list = create_empty_list();
	some_list* this_element_1 = l1[0];

	if (this_element_1 == NULL) // Первый список пуст. Разность пустая
	{
		return out_list;
	}

	some_list* this_element_2 = l2[0];

	if (this_element_2 == NULL) // Второй список пуст. Разность - первый список
	{
		copy_list(l1, out_list);
		return out_list;
	}

	do // Для каждого элемента первого списка
	{
		this_element_2 = l2[0];
		bool flag = false;		

		do // Для каждого элемента второго списка
		{
			if (comp_list(this_element_1, this_element_2, sizeof(*this_element_1)) == 0)
			{
				flag = true; // Хотя бы один элемент равен
				break;
			}
			this_element_2 = this_element_2->next;
		} while (this_element_2 != l2[0]);

		if (!flag) // Ни один элемент для текущего не равен - добавляем в третий список
		{
			some_list *p = new some_list;
			p->some_int = this_element_1->some_int;
			add_element(out_list, p);
		}

		this_element_1 = this_element_1->next;
	} while (this_element_1 != l1[0]);
	return out_list;
}

int main()
{
	setlocale(LC_ALL, "");
	some_list **a = create_empty_list();
	some_list **b = create_empty_list();
	cout << "Введите количество элементов первого списка." << endl;
	int c1, c2;
	cin >> c1;
	cout << "Введите элементы первого списка." << endl;
	for (int i = 0; i < c1; i++)
	{
		some_list *p1 = new some_list;
		cin >> p1->some_int;
		add_element(a, p1);
	}
	cout << "Введите количество элементов второго списка." << endl;
	cin >> c2;
	cout << "Введите элементы второго списка." << endl;
	for (int i = 0; i < c2; i++)
	{
		some_list *p1 = new some_list;
		cin >> p1->some_int;
		add_element(b, p1);
	}
	
	cout << "A: ";
	print_list(a);
	cout << "B: ";
	print_list(b);
	
	some_list** c = difference(a, b);
	cout << "Список С - разность первого и второго списка: ";
	print_list(c);

	delete_list(c);
	delete_list(a);
	delete_list(b);
	
	system("pause");
	return 0;
}