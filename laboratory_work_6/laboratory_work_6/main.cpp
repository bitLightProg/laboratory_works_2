/*9. Вершина дерева содержит указатель на строку и список указателей на потомков.
Размерность списка в корневой вершине - N, на каждом следующем уровне - в 2 раза больше.
Функция при включении строки создает  вершину, наиболее близкую к корню.*/
// 26 5
#include <iostream>
#include <Windows.h>

using namespace std;

/*Структура вершины дерева*/
extern struct pointer_list;
struct tree_member
{
	char* str = NULL;
	short ch_max = 2, ch_count = 0;
	pointer_list *children = NULL;
};

/*Структура списка потомков*/
struct pointer_list
{
	pointer_list *next = NULL;
	tree_member *child = NULL;
};

tree_member *root = NULL;

/*Функция добавление вершины в список детей*/
int add_child(tree_member *to, tree_member *child)
{
	pointer_list *list = to->children;
	/*Если детей еще нет*/
	if (list == NULL)
	{
		to->children = new pointer_list;
		to->children->child = child;
	}
	
	else
	{
		while (list->next != NULL)
			list = list->next;

		list->next = new pointer_list;
		list->next->child = child;
	}
	to->ch_count++;
	return 0;
}

tree_member* find_insert_place(tree_member *current = root)
{
	if (root == NULL)
		return NULL;

	/*if (current == NULL)
		current = root;*/

	
	/*Текущая вершина заполнена*/
	if (current->ch_count == current->ch_max)
	{
		int n = -1;
		tree_member *returning = NULL;

		pointer_list *list = current->children;
		while (list != NULL)
		{
			/*Поиск в глубину*/
			tree_member *ins = find_insert_place(list->child);
			/*Если найденная вершина ближе к корню*/
			if (ins->ch_max < n || n == -1)
			{
				n = ins->ch_max;
				returning = ins;
			}
			list = list->next;
		}
		return returning;
	}
	/*Найдено свободное место для вставки*/
	else
	{
		return current;
	}
}

/*Функция добавления вершины*/
int add_member(char* str)
{
	/*Создание дерева*/
	if (root == NULL)
	{
		root = new tree_member;
		root->str = str;
	}
	/*Добавление новой вершины*/
	else
	{
		/*Поиск места для вставки*/
		tree_member *ins = find_insert_place();
		if (ins == NULL)
			return 1;

		tree_member *child = new tree_member;
		child->str = str;
		child->ch_max = ins->ch_max * 2;

		/*Вставка новой вершины*/
		add_child(ins, child);
	}
	return 0;
}

int delete_tree(tree_member *current = root)
{
	if (current == NULL)
		return 1;
	pointer_list *list = current->children;
	while (list != NULL)
	{
		/*Поиск в глубину*/
		find_insert_place(list->child);
		pointer_list *deleting = list;
		list = list->next;
		delete deleting->child;
		delete deleting;
	}

	delete[] current->str;
	//delete current->children;
	return 0;
}

int print_tree(tree_member *current = root)
{
	if (current == NULL)
		return 1;
	pointer_list *list = current->children;
	

	
	if (current == root)
		cout << current->str << " " << current->ch_count << endl;
	while (list != NULL)
	{
		/*Поиск в глубину*/
		int n = list->child->ch_max / 2 - 1;
		for (int i = 0; i < n; i++)
			cout << "   ";
		cout << list->child->str << " " << list->child->ch_count << endl;
		print_tree(list->child);
		list = list->next;
	}

	return 0;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int a;
	while (true)
	{
		system("cls");
		cout << "1. Добавить вершину.\n"
			<< "2. Вывести дерево.\n"
			<< "0. Выход." << endl;
		cin >> a;

		if (a == 0)
			break;
		if (a == 1)
		{
			cout << "Введите строку, не содержащую пробелов: ";
			char* str = new char[256];
			cin >> str;
			add_member(str);
		}
		else if (a == 2)
		{
			cout << "Формат: *строка* *количество детей*" << endl;
			if (print_tree() == 1)
				cout << "Дерево пусто." << endl;
			system("pause");
		}

	}
	//print_tree();
	delete_tree();
	system("pause");
	return 0;
}