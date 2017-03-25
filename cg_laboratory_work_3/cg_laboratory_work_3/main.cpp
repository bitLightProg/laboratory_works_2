#include <GL/freeglut.h>
#include <iostream>
#include <ctime>

using namespace std;

GLint width = 800, height = 400;

short points_count = 0;
struct points_list
{
	points_list* next = NULL;
	short x;
	short y;
} main_list;

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

void mouseFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_UP)
		{
			glColor3f((float)255 / 255, (float)64 / 255, (float)64 / 255);
			glBegin(GL_POINTS);
			
			glVertex2f(x, y);
			
			glEnd();
			glFlush();

			if (points_count == 0)
			{
				main_list.x = x;
				main_list.y = y;
				main_list.next = new points_list;
			}
			else
			{
				points_list *ins_point = &main_list;
				while (ins_point->next != NULL)
					ins_point = ins_point->next;

				ins_point->x = x;
				ins_point->y = y;
				ins_point->next = new points_list;
				

				points_count++;
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
	glutMainLoop();

	points_list *this_points = main_list.next;
	points_list *next_points;

	while (this_points != NULL) // Отчистка списка студентов
	{
		next_points = this_points->next;
		delete this_points;
		points_count--;
		this_points = next_points;
	}

	return 0;
}