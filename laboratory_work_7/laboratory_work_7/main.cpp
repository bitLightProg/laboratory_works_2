/*ѕреобразовать функцию сортировки с использованием массивов(b), списков(6.3), деревьев(8.4, 8.5) в итератор.
ѕроверить его работу на двух структурах данных содержащих указатели на различные типы(например, целые и строки).
ћассив преобразовать в массив указателей.*/

#include <iostream>
#include <Windows.h>

using namespace std;

struct some_list_i
{
	some_list_i* next = NULL;
	int val;
};

struct some_list_str
{
	some_list_str* next = NULL;
	char* val;
};

struct some_tree
{
	some_tree* left = NULL;
	some_tree* right = NULL;
	int val;
};

short type = -1;
short size = -1;
short size_of_arr = -1;

void* get_next_arr_i(void* p...)
{
	int* p1 = (int*)&p;
	if ( (int*)*(p1 + 1) + size_of_arr - 1 == p)
	{
		return NULL;
	}
	return (void*)((char*)p + sizeof(int));
}

void* get_next_arr_d(void* p...)
{
	int* p1 = (int*)&p;
	if ((double*)*(p1 + 1) + size_of_arr - 1 == p)
	{
		return NULL;
	}
	return (void*)((char*)p + sizeof(double));
}

void* get_next_arr_ch(void* p...)
{
	int* p1 = (int*)&p;
	if ((char*)*(p1 + 1) + size_of_arr - 1 == p)
	{
		return NULL;
	}
	return (void*)((char*)p + sizeof(char));
}

void* get_next_l(void* p...)
{
	p = *(void**)p;	
	return p;
}

int n = -1;
int k = 0;
bool f = false;

void* get_next_tree(void* p...)
{
	if (n == -1)
	{
		n = 0;
		return NULL;
	}
	if (n == 0)
	{
		while (((some_tree*)p)->left != NULL)
			p = ((some_tree*)p)->left;
		n = 1;
		return p;
	}
	if (n == 1)
	{
		bool l = false;
		void* p1 = *(void**)((int*)&p + 1);
		void* p2 = NULL;
		if (p1 == p)
		{
			if (k != 0) f = true;
			if (((some_tree*)p1)->right != NULL)
			{
				p1 = ((some_tree*)p1)->right;
				while (((some_tree*)p1)->left != NULL)
				{
					p1 = ((some_tree*)p1)->left;
				}
				if (k != 0) k--;
				return p1;
			}
			else
			{
				if (k != 0) k--;
				return NULL;
			}
		}
		else
		{
			if (!f)
			{
				while (((some_tree*)p1)->left != NULL)
				{
					
					k++;
					p2 = get_next_tree(p, ((some_tree*)p1)->left/*, &p1*/);
					if (f)
					{
						l = true;
						break;
					}
					break;
				}
			}
			if (!f)
			{
				while (((some_tree*)p1)->right != NULL)
				{
					if (f)
					{
						break;
					}
					k++;
					p2 = get_next_tree(p, ((some_tree*)p1)->right/*, &p1*/);
					break;
				}
				
			}

			if (f)
			{
				if (k == 0)
				{
					k++;
					f = false;
				}

				if (p2 != NULL)
				{
					k--;
					return p2;
				}

				if (l)
				{
					k--;
					return p1;
				}
				else
				{
					k--;
					return NULL;
				}
			}
		}
		k--;
		return NULL;
	}
}

int cmp_i(void* p1, void* p2)
{
	return *(int*)p1 - *(int*)p2 > 0 ? 1 : -1;
}

int cmp_d(void* p1, void* p2)
{
	return *(double*)p1 - *(double*)p2 > 0 ? 1 : -1;
}

int cmp_ch(void* p1, void* p2)
{
	return *(char*)p1 - *(char*)p2 > 0 ? 1 : -1;
}

int cmp_str(void* p1, void* p2)
{
	return strcmp((char*)p1, (char*)p2);
}

int cmp_l_i(void* p1, void* p2)
{
	return cmp_i(&((some_list_i*)p1)->val, &((some_list_i*)p2)->val);
}

int cmp_l_str(void* p1, void* p2)
{
	return cmp_str(((some_list_str*)p1)->val, ((some_list_str*)p2)->val);
}

int cmp_tree(void* p1, void* p2)
{
	return cmp_i(&((some_tree*)p1)->val, &((some_tree*)p2)->val);
}

int swap_i(void* p1, void* p2)
{
	int a = *(int*)p1;
	*(int*)p1 = *(int*)p2;
	*(int*)p2 = a;
	return 0;
}

int swap_d(void* p1, void* p2)
{
	double a = *(double*)p1;
	*(double*)p1 = *(double*)p2;
	*(double*)p2 = a;
	return 0;
}

int swap_ch(void* p1, void* p2)
{
	char a = *(char*)p1;
	*(char*)p1 = *(char*)p2;
	*(char*)p2 = a;
	return 0;
}

int swap_l_i(void* p1, void* p2)
{
	int a = ((some_list_i*)p1)->val;
	((some_list_i*)p1)->val = ((some_list_i*)p2)->val;
	((some_list_i*)p2)->val = a;
	return 0;
}

int swap_l_str(void* p1, void* p2)
{
	char* a = ((some_list_str*)p1)->val;
	((some_list_str*)p1)->val = ((some_list_str*)p2)->val;
	((some_list_str*)p2)->val = a;
	return 0;
}

int swap_tree(void* p1, void* p2)
{
	int a = ((some_tree*)p1)->val;
	((some_tree*)p1)->val = ((some_tree*)p2)->val;
	((some_tree*)p2)->val = a;
	return 0;
}

int sort(void* begin,
			void* (*get_next)(void* p...),
				int (*cmp)(void* p1, void* p2),
						int (*swap)(void* p1, void* p2))
{
	void* it = begin;
	for (; it != NULL; it = get_next(it, begin))
	{
		void* min = it;
		for (void* it_min = it; it_min != NULL; it_min = get_next(it_min, begin))
		{
			if (cmp(min, it_min) > 0)
				min = it_min;
		}
		swap(it, min);
	}
	return 0;
}

int print_tree(some_tree *current, int t)
{
	/*if (current == NULL)
		return 1;*/
	
	for (int i = 0; i < t; i++)
		cout << "   ";
	if (current == NULL)
	{
		cout << "NULL" << endl;
		return 0;
	}
	cout << current->val << endl;
	//if (current->left != NULL)
		print_tree(current->left, t + 1);
		
	//if (current->right != NULL)
		print_tree(current->right, t + 1);
	

	return 0;
}



int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int arr[] = { 1,0,5,2,7,9 };
	double arr_d[] = { 1.0,2.1,2.2,2.3,2.22,2.21 };
	size_of_arr = 6;
	void* p = 0;
	for (int i = 0; i < size_of_arr; i++)
		cout << arr[i] << " ";
	cout << endl;
	for (int i = 0; i < size_of_arr; i++)
		cout << arr_d[i] << " ";
	cout << endl;
	sort(arr, get_next_arr_i, cmp_i, swap_i);
	sort(arr_d, get_next_arr_d, cmp_d, swap_d);
	for (int i = 0; i < size_of_arr; i++)
		cout << arr[i] << " ";
	cout << endl;
	for (int i = 0; i < size_of_arr; i++)
		cout << arr_d[i] << " ";
	cout << endl;
	//cout << get_next_arr_i((int*)p + 2, p) << endl;
	//cout << get_next_arr_d((double*)p + 1, p) << endl;
	
	char str[] = "12345678¬иктори€1234567890\0";
	size_of_arr = strlen(str);
	cout << str << endl;
	sort(str, get_next_arr_ch, cmp_ch, swap_ch);
	cout << str << endl;
	some_list_i* end = new some_list_i;
	some_list_i* some1 = new some_list_i;
	some_list_i* some2 = new some_list_i;
	some_list_i* beg = new some_list_i;
	end->val = 5;
	some1->next = end;
	some1->val = 6;
	some2->next = some1;
	some2->val = 10;
	beg->next = some2;
	beg->val = 2;
	cout << beg->val << " " << beg->next->val << " " << beg->next->next->val << " " << beg->next->next->next->val << endl;
	sort(beg, get_next_l, cmp_l_i, swap_l_i);
	cout << beg->val << " " << beg->next->val << " " << beg->next->next->val << " " << beg->next->next->next->val << endl;
	//cout << get_next_l(end) << endl;
	delete end;
	delete some2;
	delete some1;
	delete beg;


	some_tree* tree = new some_tree;
	tree->left = new some_tree;
	tree->right = new some_tree;
	tree->val = 4;
	tree->left->val = 3;
	tree->right->val = 1;
	tree->left->right = new some_tree;
	tree->left->right->val = 10;
	print_tree(tree, 0);
	sort(tree, get_next_tree, cmp_tree, swap_tree);
	print_tree(tree, 0);

	delete tree->left;
	delete tree->right;
	delete tree;
	system("pause");
	return 0;
}