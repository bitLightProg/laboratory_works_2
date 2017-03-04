#include <GL/freeglut.h>
#include <iostream>
#include <ctime>
#include <list>

using namespace std;


bool arr[20][32];
short w = 32, h = 20, bw = 304, bh = 152;
GLint width = 800, height = 400;
short x_centre = 400, y_centre = 232;
bool display = false;
long time0 = 0;
long time_fps = 0;
short iter = 0; // количество пересчетов
short count_of_dec = 0; // количество шаров на сцене
short delay = 1000/60; // минимальная задержка по времени между пересчетами

int intl(float a)
{
	if (a >= 0)
		return (int)a;
	else
	{
		if (a - (int)a != 0)
			return (int)a - 1;
		else
			return (int)a;
	}
}

struct line
{
	line* next_point = NULL;
	short x, y;
} main_line;

void draw_pixel(int y, int x);

void mouseFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_UP)
		{
			//system("cls");
			x -= x_centre;
			y = 400 - y;
			y -= y_centre;
			
			int temp;
			x > 0 ? temp = 1 : temp = -1;
			x /= 16;
			x > 0 ? x++ : x < 0 ? x-- : x;
			x == 0 ? temp == 1 ? x++ : x-- : x;
			//x++;
			y > 0 ? temp = 1 : temp = -1;
			y /= 16;
			y > 0 ? y++ : y < 0 ? y-- : y;
			y == 0 ? temp == 1 ? y++ : y-- : y;
			//y++;
			//draw_pixel(y, x);
			arr[y > 0 ? 10 - y : 9 - y][x > 0 ? 15 + x : 16 + x] = true;
			/*for (int i = 0; i < 20; i++)
			{
				for (int j = 0; j < 32; j++)
					cout << arr[i][j] << ' ';
				cout << endl;
			}*/

			if (main_line.next_point == NULL)
			{
				main_line.x = x;
				main_line.y = y;
				main_line.next_point = new line;
			}
			else
			{
				main_line.next_point->x = x;
				main_line.next_point->y = y;

				short px = main_line.next_point->x - main_line.x;
				short py = main_line.next_point->y - main_line.y;

				if (abs(px) >= abs(py))
				{
					if (px >= 0)
					{
						float p = (float) py / px;
						for (float i = main_line.x, j = main_line.y; i <= main_line.next_point->x; i++)
						{
							bool flag = false;
							j += p;
							

							draw_pixel(intl(j), intl(i));
							

						}
					}
				}
			}

			glutPostRedisplay();
		}
	}
	if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_UP)
		{
			
			//system("cls");
			x -= x_centre;
			y = 400 - y;
			y -= y_centre;

			int temp;
			x > 0 ? temp = 1 : temp = -1;
			x /= 16;
			x > 0 ? x++ : x < 0 ? x-- : x;
			x == 0 ? temp == 1 ? x++ : x-- : x;
			//x++;
			y > 0 ? temp = 1 : temp = -1;
			y /= 16;
			y > 0 ? y++ : y < 0 ? y-- : y;
			y == 0 ? temp == 1 ? y++ : y-- : y;
			//y++;
			//draw_pixel(y, x);
			arr[y > 0 ? 10 - y : 9 - y][x > 0 ? 15 + x : 16 + x] = false;
			/*for (int i = 0; i < 20; i++)
			{
			for (int j = 0; j < 32; j++)
			cout << arr[i][j] << ' ';
			cout << endl;
			}*/

			glutPostRedisplay();
		}
	}
}
void draw_pixel(int y, int x)
{

	glColor3f((float)255 / 255, (float)0 / 255, (float)0 / 255);
	glBegin(GL_POINTS);
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
		{
			if (y > 0 && x > 0)
				glVertex2f(x_centre + (x-1)*16 + i, y_centre + (y-1)*16 + j+1);
			else if (y < 0 && x < 0)
				glVertex2f(x_centre + x * 16 + i, y_centre + y * 16 + j + 1);
			else if (y < 0)
				glVertex2f(x_centre + (x - 1) * 16 + i, y_centre + y * 16 + j + 1);
			else if (x < 0)
				glVertex2f(x_centre + x * 16 + i, y_centre + (y - 1) * 16 + j + 1);
		}

	glEnd();

	glFlush();
}

void Display()
{
	/*if (clock() - time0 < delay) 
		return;*/
	
	
	
	glColor3f((float)255 / 255, (float)0 / 255, (float)0 / 255);

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 32; j++)
			if (arr[i][j] == true)
			{
				draw_pixel(i > 9 ? 9 - i: 10 - i, j > 15 ? j - 15: j - 16);
			}
		//arr[y > 0 ? 10 - y : 9 - y][x > 0 ? 15 + x : 16 + x] = true;
	}

	glFlush();
	//draw_pixel(0, 0);
	time0 = clock();
	display = true;
}

void Initialize(int w, int h)
{
	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f((float)255 / 255, (float)255 / 255, (float)255 / 255);
	//glColor3f((float)0 / 255, (float)255 / 255, (float)0 / 255);


	glBegin(GL_LINES);
	for (int i = 0; i < 33; i++)
	{
		if (i == 16)
			glColor3f((float)0 / 255, (float)255 / 255, (float)51 / 255);
		glVertex2f(144 + 16 * i, 40 + 32 + 0);
		glVertex2f(144 + 16 * i, 40 + 32 + 320);
		//glVertex2f(0, 16 * i);
		//glVertex2f(width, 16 * i);
		if (i == 16)
			glColor3f((float)255 / 255, (float)255 / 255, (float)255 / 255);
	}
	for (int i = 0; i < 21; i++)
	{
		if (i == 10)
			glColor3f((float)0 / 255, (float)255 / 255, (float)51 / 255);
		//glVertex2f(16 * i, 0);
		//glVertex2f(16 * i, height);
		glVertex2f(144 + 0, 40 + 32 + 16 * i);
		glVertex2f(144 + 512, 40 + 32 + 16 * i);
		if (i == 10)
			glColor3f((float)255 / 255, (float)255 / 255, (float)255 / 255);

	}
	glEnd();

	glFlush();
}



void Idle()
{
	if (clock() - time0 < delay) // задержка установлена таким образом, чтобы наибольшее число
		return;					// перерисовок равнялось 200

	
		
	


	glutPostRedisplay();
	
}

void changeSize(int w, int h) {
	display = false;
	// предупредим деление на ноль
	// если окно сильно перетянуто будет
	

	width = w;
	height = h;

	// используем матрицу проекции
	glMatrixMode(GL_PROJECTION);

	// Reset матрицы
	glLoadIdentity();

	// определяем окно просмотра
	glViewport(0, 0, w, h);

	

	gluOrtho2D(0, w, 0, h);
	
	while (!display)
		Display();
	cout << width << " " << height << endl;

}

int main(int argc, char ** argv)
{
	setlocale(LC_ALL, "");
	srand(time(NULL));

	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 32; j++)
			arr[i][j] = false;
	

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 200);
	glutCreateWindow("Яковенко В.В. АВТ-615");
	glutDisplayFunc(Display);
	Initialize(width, height);
	//glutIdleFunc(Idle);

	//glutReshapeFunc(changeSize);

	glutMouseFunc(mouseFunc);
	time0 = clock();
	time_fps = time0;
	glutMainLoop();
	//draw_pixel(1, 1);
	return 0;
}