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

int print_list(some_list** a)
{
	some_list* this_element = a[0];

	if (this_element == NULL)
		return 1;
	
	some_list* next_element = this_element->next;

	do
	{
		cout << this_element->some_int << endl;
		this_element = this_element->next;
	} while (this_element != a[0]);
	//cout << this_element->some_int << endl;
	return 0;
}

int main()
{
	some_list **a = create_empty_list();
	some_list *p1 = new some_list;
	some_list *p2 = new some_list;
	p2->some_int = 1;
	some_list *p3 = new some_list;
	p3->some_int = 2;
	add_element(a, p1);
	add_element(a, p2);
	add_element(a, p3);
	print_list(a);
	delete_list(a);
	system("pause");
	return 0;
}