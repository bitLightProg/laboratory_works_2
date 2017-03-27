#include <GL/freeglut.h>
#include <iostream>
#include <ctime>

using namespace std;

GLint width = 800, height = 400;

short points_count = 0;
short list_count = 0;

struct list
{
	list* next = NULL;
	int a;
} List;
struct points_list
{
	points_list* next = NULL;
	points_list* prev = NULL;
	short x;
	short y;
} main_list;
points_list *tail = &main_list;

void Display()
{
	
}

void Initialize(int w, int h)
{
	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, h, 0);
	

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f((float)192 / 255, (float)192 / 255, (float)192 / 255);

	glBegin(GL_LINES);
	
	glEnd();

	glFlush();
}

int comp_p(const void* v1, const void* v2)
{
	points_list *p1 = *(points_list**)v1;
	points_list *p2 = *(points_list**)v2;

	return (p1->y - p2->y);
}

int comp_l(const void* v1, const void* v2)
{
	list *p1 = *(list**)v1;
	list *p2 = *(list**)v2;

	return (p1->a - p2->a);
}

int fill()
{
	tail->next = &main_list;
	main_list.prev = tail;
	typedef points_list** pl;
	pl table = new points_list*[points_count];

	points_list* this_l = &main_list;

	for (int i = 0; i < points_count; i++)
	{
		table[i] = this_l;
		this_l = this_l->next;
	}

	qsort(table, points_count, sizeof(*table), comp_p);

	for (int i = 0; i < points_count; i++)
	{
		cout << table[i]->y << endl;
	}

	for (int i = table[0]->y; i <= table[points_count - 1]->y; i++)
	{
		list *l = List.next;
		while (l != NULL)
		{
			list* temp = l->next;
			//cout << l->a << endl;
			delete l;
			list_count--;
			l = temp;
		}
		if (list_count == 1)
		{
			List.next = NULL;
			list_count--;
		}
			
		//cout << "L_c: " << list_count << endl;
		for (int j = 0; j < points_count && table[j]->y <= i; j++)
		{
			if (table[j]->prev->y >= i && table[j]->next->y >= i)
			{
				//if (table[j]->prev->x <= table[j]->next->x)
				//{
					if (list_count == 0)
					{
						List.a = table[j]->x - ((double) table[j]->y - i) / (table[j]->y - table[j]->prev->y)*(table[j]->x - table[j]->prev->x);
						List.next = new list;
						List.next->a = table[j]->x - ((double) table[j]->y - i) / (table[j]->y - table[j]->next->y)*(table[j]->x - table[j]->next->x);
						//List.next->next = new list;
						list_count += 2;
					}
					else
					{
						list *l = &List;
						while (l->next != NULL)
							l = l->next;

						l->next = new list;
						l->next->a = table[j]->x - ((double) table[j]->y - i) / (table[j]->y - table[j]->prev->y)*(table[j]->x - table[j]->prev->x);
						l->next->next = new list;
						l->next->next->a = table[j]->x - ((double) table[j]->y - i) / (table[j]->y - table[j]->next->y)*(table[j]->x - table[j]->next->x);
						list_count += 2;
					}
					
				//}
			}
			else if (table[j]->prev->y >= i)
			{
				if (list_count == 0)
				{
					List.a = table[j]->x - ((double) table[j]->y - i) / (table[j]->y - table[j]->prev->y)*(table[j]->x - table[j]->prev->x);
					list_count++;
				}
				else
				{
					list *l = &List;
					while (l->next != NULL)
						l = l->next;

					l->next = new list;
					l->next->a = table[j]->x - ((double) table[j]->y - i) / (table[j]->y - table[j]->prev->y)*(table[j]->x - table[j]->prev->x);
					list_count++;
				}
				/*list *l = &List;
				while (l->next != NULL)
					l = l->next;

				l->next = new list;
				l->next->a = table[j]->x + (table[j]->y - i) / (table[j]->y - table[j]->prev->y)*(table[j]->x - table[j]->prev->x);*/
			}
			else if (table[j]->next->y >= i)
			{

				if (list_count == 0)
				{
					List.a = table[j]->x - ((double) table[j]->y - i) / (table[j]->y - table[j]->next->y)*(table[j]->x - table[j]->next->x);
					list_count++;
				}
				else
				{
					list *l = &List;
					while (l->next != NULL)
						l = l->next;

					l->next = new list;
					l->next->a = table[j]->x - ((double) table[j]->y - i) / (table[j]->y - table[j]->next->y)*(table[j]->x - table[j]->next->x);
					list_count++;
				}

				/*list *l = &List;
				while (l->next != NULL)
					l = l->next;

				l->next = new list;
				l->next->a = table[j]->x + (table[j]->y - i) / (table[j]->y - table[j]->next->y)*(table[j]->x - table[j]->next->x);*/
			}
		}


		list** table_l = new list*[list_count];
		l = &List;
		for (int k = 0; k < list_count; k++)
		{
			table_l[k] = l;
			l = l->next;
		}
		//int k = 0;
		/*while (l->next != NULL)
		{
			//cout << l->a << endl;
			table_l[k] = l;
			l = l->next;
			k++;
		}*/
		
		//cout << l->a << endl;

		//if (list_count != 1)
		qsort(table_l, list_count, sizeof(list*), comp_l);
		cout << "L_c: " << list_count << endl;

		for (int k = 0; k < list_count; k++)
		{
			cout << table_l[k]->a << endl;
			glColor3f((float)255 / 255, (float)64 / 255, (float)64 / 255);
			glBegin(GL_POINTS);

			glVertex2f(table_l[k]->a, i);

			glEnd();
			glFlush();
		}
		
	}
		
	return 0;
}

void mouseFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_UP)
		{
			//cout << y << endl;
			glColor3f((float)255 / 255, (float)64 / 255, (float)64 / 255);
			glBegin(GL_POINTS);
			
			glVertex2f(x, y);
			
			glEnd();
			glFlush();

			if (points_count == 0)
			{
				main_list.x = x;
				main_list.y = y;
				//main_list.next = new points_list;
				//main_list.next->prev = &main_list;
				//tail = main_list.next;
				points_count++;
			}
			else
			{
				//points_list *ins_point = &main_list;
				//while (ins_point->next != NULL)
				//	ins_point = ins_point->next;
				tail->next = new points_list;
				tail->next->prev = tail;
				tail = tail->next;
				tail->x = x;
				tail->y = y;
				
				//tail->next->prev = tail;
				//tail = tail->next;
				

				points_count++;
				//cout << points_count << endl;
			}
		}
	}
	if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_UP)
		{
		
			
		}
	}
}


void processNormalKeys(unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
	if (key == ' ')
		fill();
}

int main(int argc, char ** argv)
{
	setlocale(LC_ALL, "");
	srand(time(NULL));

	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 200);
	glutCreateWindow("Яковенко В.В. АВТ-615");
	glutDisplayFunc(Display);
	Initialize(width, height);
	glutMouseFunc(mouseFunc);
	glutKeyboardFunc(processNormalKeys);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutMainLoop();

	points_list *this_points = main_list.next;
	points_list *next_points;

	while (this_points != NULL) // Отчистка списка студентов
	{
		next_points = this_points->next;
		delete this_points;
		points_count--;
		this_points = next_points;
		//cout << points_count << endl;
	}
	system("pause");
	return 0;
}