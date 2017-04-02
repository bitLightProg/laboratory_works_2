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

int draw(int x1, int x2, int y)
{
	glColor3f((float)255 / 255, (float)64 / 255, (float)64 / 255);
	glBegin(GL_POINTS);
	for (int i = x1 + 1; i < x2; i++)
	{
		glVertex2f(i, y);
		if (i % 6 == 0)
			Sleep(1);
			glEnd();
			glFlush();
			glBegin(GL_POINTS);
	}
	glEnd();
	glFlush();
	
	return 0;
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
		cout << i << ". ";
		for (int k = 0; k < list_count; k++)
		{
			if ((list_count % 2) &&(k != list_count - 1) && (table_l[k]->a == table_l[k + 1]->a))
			{
				for (int j = k + 1; j < list_count - 1; j++)
				{
					table_l[j] = table_l[j + 1];
				}
			}
			cout << table_l[k]->a << " ";
			glColor3f((float)255 / 255, (float)64 / 255, (float)64 / 255);
			glBegin(GL_POINTS);

			glVertex2f(table_l[k]->a, i);

			glEnd();
			glFlush();
		}
		cout << endl;

		for (int j = 0; j < list_count - 1; j += 2)
		{
			draw(table_l[j]->a, table_l[j + 1]->a, i);
		}
		
	}
		
	return 0;
}

int fill_better()
{
	glColor3f((float)255 / 255, (float)64 / 255, (float)64 / 255);
	glBegin(GL_LINE_LOOP);
	points_list *this_p = &main_list;
	do
	{
		glVertex2f(this_p->x, this_p->y); 
		this_p = this_p->next;
	} while (this_p != NULL);
	glEnd();
	glColor3f((float)254 / 255, (float)64 / 255, (float)64 / 255);
	glBegin(GL_POINTS);
	this_p = &main_list;
	do
	{
		glVertex2f(this_p->x, this_p->y);
		this_p = this_p->next;
	} while (this_p != NULL);
	glEnd();
	glColor3f((float)255 / 255, (float)64 / 255, (float)64 / 255);
	glFlush();

	unsigned char *arr = new unsigned char[width*height * 3];
	glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, arr);
	list *points = NULL;
	int he = -1;
	int p_count = 0;
	for (int i = width*height * 3 + 3*width; i > 0; i += 3)
	{
		if (i / 3 % width == 0)
		{
			i -= 6 * width;
			if (he == -1)
			{
				he = (int)i / 3 / (width);
				he = 400 - he;
			}
			else
			{
				if (points != NULL && p_count % 2 != 1)
				{
					list *this_p = points;
					list *next_p = this_p->next;
					while (this_p != NULL)
					{
						draw(this_p->a, next_p->a, he);
						if (next_p->next == NULL)
							break;

						this_p = next_p->next;
						next_p = this_p->next;
					}
				}
				he = 400 - (int)i / 3 / (width);
				if (points != NULL)
				{
					list *this_p = points;
					list *next_p = points;
					while (this_p != NULL)
					{
						next_p = this_p->next;
						delete this_p;
						this_p = next_p;
						p_count--;
					}
					points = NULL;
				}
			}
		}
		if (i < 0)
			break;
		if (arr[i] == 255)
		{
			//int h = (int)i / 3 / (width);
			//h = 400 - h;
			int w = (i / 3) % (width);
			if (p_count == 0)
			{
				points = new list;
				points->a = w;
				p_count++;
				do
				{
					i += 3;
				} while (arr[i] == 255);
			}
			else if (p_count % 2 == 1)
			{
				if ((i+3)/3 % width != 0 && arr[i + 3] == 255)
				{
					continue;
				}
				else
				{
					list *next_p = points;
					while (next_p->next != NULL)
					{
						next_p = next_p->next;
					}
					next_p->next = new list;
					next_p->next->a = w;
					p_count++;
				}
			}
			else
			{
				list *next_p = points;
				while (next_p->next != NULL)
				{
					next_p = next_p->next;
				}
				next_p->next = new list;
				next_p->next->a = w;
				p_count++;
				do
				{
					i += 3;
				} while (arr[i] == 255);
			}
			//cout << h << " " << w << " " << (int)arr[i] << " " << (int)arr[i + 1] << " " << (int)arr[i + 2] << endl;
		}
	}
	/*for (int i = 0; i < width*height * 3; i += 3)
	{
		if (arr[i] != 0)
		{
			int h = (int)i / 3 / (width);
			int w = (i / 3) % (width);
			cout << h << " " << w << " " << (int)arr[i] << " " << (int)arr[i + 1] << " " << (int)arr[i + 2] << endl;
		}
	}*/
	delete[] arr;


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
			unsigned char *arr = new unsigned char[width*height*3];
			glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, arr);
			for (int i = 0; i < width*height * 3; i += 3)
			{
				//if (height != 0 && ((i % height * 3) == 0))
				//	cout << endl;
				if (arr[i] != 0)
				{
					int h = (int)i / 3 / (width);
					int w = (i / 3) % (width);
					cout << h << " " << w << " " << (int) arr[i] << " " << (int) arr[i + 1] << " " << (int) arr[i + 2] << endl;
					//arr[i] = 0;
					//arr[i + 1] = 0;
					//arr[i + 2] = 0;
				}
					//cout << (int) arr[i] << " ";
			}
			//glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, arr);
			delete[] arr;
			
		}
	}
}


void processNormalKeys(unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
	if (key == ' ')
	{
		fill();
		//fill_better();
	}
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