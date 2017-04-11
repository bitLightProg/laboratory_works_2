#include <GL/freeglut.h>
#include <iostream>
#include <ctime>

using namespace std;

GLint width = 800, height = 400;
short init_mode = 1;
unsigned char *arr;
int max_count = width*height * 3;

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
		//if (i % 200 == 0)
		//	Sleep(1);
		glEnd();
		//glFlush();
		glBegin(GL_POINTS);
	}
	glEnd();
	glFlush();

	return 0;
}

int fill(int x, int y, short mode, short n)
{
	//glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, arr);
	if (x < 0 || y < 0)
		return 0;
	glColor3f((float)255 / 255 * mode, (float)64 / 255 * mode, (float)64 / 255 * mode);
	int he = -1;
	int we = -1;
	int init = (400 - y) * 3 * width + x * 3;
	if (init < 0)
		return 0;
	glBegin(GL_POINTS);
	/*for (int i = init + 3; i < max_count; i += 3)// Вправо вниз
	{
		he = 400 - (int)i / 3 / (width);
		we = (i / 3) % (width);
		if (he < y)
		{
			int x = i + width * 3 - 3;
			while (i > 0 && i < max_count - 4 && ((mode) == arr[x])) // Влево
				x -= 3;
			if (n == -1)
				fill((x / 3) % (width), y + 1, mode, n);
			if (n == 1)
				fill((x / 3) % (width), y - 1, mode, n);
			//return 0;
			break;
		}
			

		/*if (arr[init] != arr[i])
		{
			int x = i + width * 3 - 3;
			while (i > 0 && i < max_count - 4 && ((mode) == arr[x])) // Влево
				x -= 3;
			if (n == 1)
				fill((x / 3) % (width), y + 1, mode, n);
			if (n == -1)
				fill((x / 3) % (width), y - 1, mode, n);
			//return 0;
			break;
		}
		arr[i] = 255;
		glVertex2f(we, he);
		glFlush();

	}*/

	for (int i = init - 3; i >= 0; i -= 3)// Влево
	{
		he = 400 - (int)i / 3 / (width);
		we = (i / 3) % (width);
		if (he > y)
		{
			int x = i + width * 3;
			while (i > 0 && i < max_count - 4 && ((mode) == arr[x]))// Вправо
				x += 3;
			if (n == -1)
				fill((x / 3) % (width), y + 1, mode, n);
			if (n == 1)
				fill((x / 3) % (width), y - 1, mode, n);
			//return 0;
			break;
		}

		/*if (arr[init] != arr[i])
		{
			int x = i + width * 3;
			while (i > 0 && i < max_count - 4 && ((mode) == arr[x]))// Вправо
				x += 3;
			if (n == 1)
				fill((x / 3) % (width), y + 1, mode, n);
			if (n == -1)
				fill((x / 3) % (width), y - 1, mode, n);
			//return 0;
			break;
		}*/
		arr[i] = 255;
		glVertex2f(we, he);
		glFlush();
	}
	glVertex2f(x, y);
	glEnd();
	glFlush();
	/*for (int i = width*height * 3 + 3 * width; i > 0; i += 3)
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
				if ((i + 3) / 3 % width != 0 && arr[i + 3] == 255)
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

		}
	}

	delete[] arr;*/


	return 0;
}



void mouseFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_UP)
		{

			

			glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, arr);

			glColor3f((float)255 / 255, (float)64 / 255, (float)64 / 255);
			glBegin(GL_POINTS);

			fill(x, y, (short)(arr[(400 - y) * 3 * width + x * 3] == 0 ? 1 : 0), 1);
			fill(x, y, (short)(arr[(400 - y) * 3 * width + x * 3] == 0 ? 1 : 0), -1);

			

			glVertex2f(x, y);

			glEnd();
			glFlush();

			/*if (points_count == 0)
			{
				main_list.x = x;
				main_list.y = y;

				points_count++;
			}
			else
			{

				tail->next = new points_list;
				tail->next->prev = tail;
				tail = tail->next;
				tail->x = x;
				tail->y = y;

				//tail->next->prev = tail;
				//tail = tail->next;


				points_count++;
				//cout << points_count << endl;
			}*/
		}
	}
	if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_UP)
		{
			unsigned char *arr = new unsigned char[width*height * 3];
			glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, arr);
			for (int i = 0; i < width*height * 3; i += 3)
			{
				//if (height != 0 && ((i % height * 3) == 0))
				//	cout << endl;
				if (arr[i] != 0)
				{
					int h = (int)i / 3 / (width);
					int w = (i / 3) % (width);
					cout << h << " " << w << " " << (int)arr[i] << " " << (int)arr[i + 1] << " " << (int)arr[i + 2] << endl;
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
		//fill();
		//fill_better();
	}
}

int main(int argc, char ** argv)
{
	setlocale(LC_ALL, "");
	srand(time(NULL));
	arr = new unsigned char[width*height * 3];

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
	delete[] arr;
	system("pause");
	return 0;
}