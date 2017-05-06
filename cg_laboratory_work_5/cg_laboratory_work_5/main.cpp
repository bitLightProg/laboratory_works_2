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

int x11 = -1, y11 = -1;
int draw_window()
{
	glColor3f((float)255 / 255, (float)255 / 255, (float)255 / 255);

	glBegin(GL_LINE_LOOP);
	glVertex2f(200, 100);
	glVertex2f(600, 100);
	glVertex2f(600, 300);
	glVertex2f(200, 300);
	glEnd();
	glFlush();
	return 0;
}
void Initialize(int w, int h)
{
	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, h, 0);

	glClear(GL_COLOR_BUFFER_BIT);

	draw_window();
}



void mouseFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_UP)
		{
			if (x11 == -1)
			{
				x11 = x;
				y11 = y;
			}
			else
			{
				glColor3f((float)64 / 255, (float)255 / 255, (float)64 / 255);
				glBegin(GL_LINES);
				glVertex2f(x11, y11);
				glVertex2f(x, y);
				glEnd();
				glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, arr);

				//arr[(400 - y) * 3 * width + x * 3]
				glColor3f((float)255 / 255, (float)64 / 255, (float)255 / 255);
				glBegin(GL_POINTS);
				for (int i = 0; i < width*height * 3; i += 3)
				{
					int xx = i / 3 % width;
					int yy = (int)i / 3 / (width);
					yy = 400 - yy;

					if (arr[i + 1] == 255)
					{
						if ((xx < 200 || xx > 600) || (yy < 100 || yy > 300))
						{
							arr[i] = 255;
							glVertex2f(xx, yy);
						}
					}
				}
				glEnd();

				x11 = -1;
				draw_window();

				glFlush();
			}
		}
	}
}


void processNormalKeys(unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
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

	Initialize(width, height);
	glutMouseFunc(mouseFunc);
	glutKeyboardFunc(processNormalKeys);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutMainLoop();

	delete[] arr;
	system("pause");
	return 0;
}

