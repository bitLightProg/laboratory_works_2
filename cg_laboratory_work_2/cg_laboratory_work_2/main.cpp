#include <GL/freeglut.h>
#include <iostream>
#include <ctime>
#include <cmath>

using namespace std;

bool is_line_on_screen = false;
bool arr[20][32];
bool arr1[20][32];

GLint width = 800, height = 400;
short x_centre = 400, y_centre = 232;
bool mic = 1, brez = 1;

int center_X = -1, center_Y = -1, r = -1;

void draw_pixel(int y, int x, short mode = 1);


void Display();
void Initialize(int w, int h);

void drawCircle(float x, float y, float r, int amountSegments, unsigned char red, unsigned char green, unsigned char blue) // функция рисования многоугольников
{
	glBegin(GL_LINE_LOOP);
	glColor3f((float)red / 255, (float)green / 255, (float)blue / 255);

	for (int i = 0; i < amountSegments; i++)
	{
		float angle = 2.0 * 3.1415926 * float(i) / float(amountSegments);

		float dx = r * cosf(angle);
		float dy = r * sinf(angle);
		if (x + dx >= 144 && x + dx <= 656 && y + dy >= 72 && y + dy <= 392)
			glVertex2f(x + dx, y + dy);
	}

	glEnd();
}

void pixelCircle(int centerX, int centerY, int x, int y)
{
	if (centerY + y < 20 && centerX + x < 32)
	{
		arr[centerY + y][centerX + x] = 1;
	}
	if (centerY - y >= 0 && centerX + x < 32)
	{
		arr[centerY - y][centerX + x] = 1;
	}
	if (centerY - y >= 0 && centerX - x >= 0)
	{
		arr[centerY - y][centerX - x] = 1;
	}
	if (centerY + y < 20 && centerX - x >= 0)
	{
		arr[centerY + y][centerX - x] = 1;
	}

	//pixel->PutPixel(centerX + x, centerY + y);
	//pixel->PutPixel(centerX + x, centerY - y);
	//pixel->PutPixel(centerX - x, centerY - y);
	//pixel->PutPixel(centerX - x, centerY + y);

}

void pixelCircleM(int centerX, int centerY, int x, int y)
{
	/*pixel->PutPixel(centerX + x, centerY + y);
	pixel->PutPixel(centerX + y, centerY + x);
	pixel->PutPixel(centerX + y, centerY - x);
	pixel->PutPixel(centerX + x, centerY - y);
	pixel->PutPixel(centerX - x, centerY - y);
	pixel->PutPixel(centerX - y, centerY - x);
	pixel->PutPixel(centerX - y, centerY + x);
	pixel->PutPixel(centerX - x, centerY + y);*/
	if (centerY + y < 20 && centerX + x < 32) 
	{
		arr1[centerY + y][centerX + x] = 1;
	}
	if (centerY + x < 20 && centerX + y < 32)
	{
		arr1[centerY + x][centerX + y] = 1;
	}
	if (centerY - x >= 0 && centerX + y < 32)
	{
		arr1[centerY - x][centerX + y] = 1;
	}
	if (centerY - y >= 0 && centerX + x < 32)
	{
		arr1[centerY - y][centerX + x] = 1;
	}
	if (centerY - y >= 0 && centerX - x >= 0)
	{
		arr1[centerY - y][centerX - x] = 1;
	}
	if (centerY - x >= 0 && centerX - y >= 0)
	{
		arr1[centerY - x][centerX - y] = 1;
	}
	if (centerY + x < 20 && centerX - y >= 0)
	{
		arr1[centerY + x][centerX - y] = 1;
	}
	if (centerY + y < 20 && centerX - x >= 0)
	{
		arr1[centerY + y][centerX - x] = 1;
	}
	
}

void BresenhamCircle(int centerX, int centerY, int radius)
{
	//Генерация окружности алгоритмом Брезенхейма
	int x = 0;
	int y = radius;
	int gap = 0;
	int delta = (2 - 2 * radius);
	while (y >= 0)
	{
		pixelCircle(centerX, centerY, x, y);
		gap = 2 * (delta + y) - 1;
		if (delta < 0 && gap <= 0)
		{
			x++;
			delta += 2 * x + 1;
			continue;
		}
		if (delta > 0 && gap > 0)
		{
			y--;
			delta -= 2 * y + 1;
			continue;
		}
		x++;
		delta += 2 * (x - y);
		y--;
	}
}

void MichinerCircle(int centerX, int centerY, int radius)
{
	//Генерация окружности алгоритмом Минчера
	int  x = 0;
	int y = radius;
	int d = 3 - 2 * radius;
	while (x < y) {
		pixelCircleM(centerX, centerY, x, y);
		if (d < 0) {
			d = d + 4 * x + 6;
		}
		else {
			d = d + 4 * (x - y) + 10;
			--y;
		}
		++x;
	}
	if (x == y) pixelCircleM(centerX, centerY, x, y);
}

void mouseFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_UP)
		{
			y = 400 - y;
			if ((y < 72 || y > 392) || (x < 144 || x > 656))
			{
				return;
			}

			if (r != -1)
			{
				if (mic && brez)
				{
					brez = 0;
					Initialize(width, height);
					Display();
				}
				else if (mic)
				{
					mic = 0; brez = 1;
					Initialize(width, height);
					Display();
				}
				else if (brez)
				{
					mic = 1;
					Initialize(width, height);
					Display();
				}
				return;
			}
			//cout << y << " " << x << endl;

			x -= 144;
			y -= 72;

			//cout << y << " " << x << endl;
			x /= 16;
			y = 19 - y/16;

			//cout << y << " " << x << endl;
			

			if (center_X == -1)
			{
				arr[y][x] = 1;
				arr1[y][x] = 1;
				center_X = x;
				center_Y = y;
			}
			else
			{
				int radius = sqrt(pow(x - center_X, 2) + pow(y - center_Y, 2));
				cout << radius << endl;
				r = radius;
				//drawCircle(144 + center_X*16 + 8, 72 + center_Y*16 + 8, radius*16 + 8, 20, 0, 0, 255);
				BresenhamCircle(center_X, center_Y, radius);
				MichinerCircle(center_X, center_Y, radius);
			}

			glutPostRedisplay();
		}
	}
	if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_UP)
		{
			y = 400 - y;
			if ((y < 72 || y > 392) || (x < 144 || x > 656))
			{
				return;
			}

			//cout << y << " " << x << endl;
			x -= 144;
			y -= 72;

			//cout << y << " " << x << endl;

			x /= 16;
			y = 19 - y / 16;

			//cout << y << " " << x << endl;
			
			if (arr[y][x] == 1 || arr1[y][x] == 1)
			{

				glColor3f((float)192 / 255, (float)192 / 255, (float)192 / 255);

				glBegin(GL_LINES);
				for (int i = 0; i < 33; i++)
				{
					if (i == 16)
						glColor3f((float)0 / 255, (float)255 / 255, (float)51 / 255);

					glVertex2f(144 + 16 * i, 40 + 32 + 0);
					glVertex2f(144 + 16 * i, 40 + 32 + 320);

					if (i == 16)
						glColor3f((float)192 / 255, (float)192 / 255, (float)192 / 255);
				}
				for (int i = 0; i < 21; i++)
				{
					if (i == 10)
						glColor3f((float)0 / 255, (float)255 / 255, (float)51 / 255);

					glVertex2f(144 + 0, 40 + 32 + 16 * i);
					glVertex2f(144 + 512, 40 + 32 + 16 * i);

					if (i == 10)
						glColor3f((float)192 / 255, (float)192 / 255, (float)192 / 255);

				}
				glEnd();

				glFlush();
				
				for (int i = 0; i < 20; i++)
					for (int j = 0; j < 32; j++)
					{
						arr[i][j] = 0;
						arr1[i][j] = 0;
						draw_pixel(i > 9 ? 9 - i : 10 - i, j > 15 ? j - 15 : j - 16, 0);
					}

				center_X = -1;
				r = -1;
				

				
				//Initialize(width, height);
				//Display();
			} 
			
		}
	}
}
void draw_pixel(int y, int x, short mode)
{
	if (mode == 0)
		glColor3f((float)0 / 255, (float)0 / 255, (float)0 / 255);
	else if (mode == 2)
		glColor3f((float)255 / 255, (float)64 / 255, (float)0 / 255);
	else if (mode == 3)
		glColor3f((float)0 / 255, (float)64 / 255, (float)255 / 255);
	else if (mode == 4)
		glColor3f((float)255 / 255, (float)64 / 255, (float)255 / 255);
	else
		glColor3f((float)brez*arr[y > 0 ? 10 - y : 9 - y][x > 0 ? 15 + x : 16 + x] * 255 / 255, (float)64 / 255, (float)mic*arr1[y > 0 ? 10 - y : 9 - y][x > 0 ? 15 + x : 16 + x] * 255 / 255);
	
	glBegin(GL_POINTS);
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
		{
			if (y > 0 && x > 0)
				glVertex2f(x_centre + (x - 1) * 16 + i, y_centre + (y - 1) * 16 + j + 1);
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

void renderBitmapString(float x, float y, void *font, char *string)
{
	char *c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++)
	{
		glutBitmapCharacter(font, *c);
	}
}

void Display()
{
	glColor3f((float)255 / 255, (float)0 / 255, (float)0 / 255);

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 32; j++)
			if (arr[i][j] == true || arr1[i][j] == true)
			{
				draw_pixel(i > 9 ? 9 - i : 10 - i, j > 15 ? j - 15 : j - 16);
			}
	}

	draw_pixel(-12, -14, 2); renderBitmapString(x_centre + -13 * 16 + 4, y_centre + -12 * 16 + 4, GLUT_BITMAP_9_BY_15, "Brezenhem");
	draw_pixel(-12, -6, 3); renderBitmapString(x_centre + -5 * 16 + 4, y_centre + -12 * 16 + 4, GLUT_BITMAP_9_BY_15, "Michiner"); //Brezenhem
	draw_pixel(-12, 4, 4); renderBitmapString(x_centre + 4 * 16 + 4, y_centre + -12 * 16 + 4, GLUT_BITMAP_9_BY_15, "Michiner + Brezenhem");

	if (r != -1)
		drawCircle(144 + center_X * 16 + 7, 72 + (19 - center_Y) * 16 + 7, r * 16 + 9, 500, 4, 64, 255);

	
	glFlush();
}

void Initialize(int w, int h)
{
	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f((float)192 / 255, (float)192 / 255, (float)192 / 255);

	glBegin(GL_LINES);
	for (int i = 0; i < 33; i++)
	{
		if (i == 16)
			glColor3f((float)0 / 255, (float)255 / 255, (float)51 / 255);

		glVertex2f(144 + 16 * i, 40 + 32 + 0);
		glVertex2f(144 + 16 * i, 40 + 32 + 320);

		if (i == 16)
			glColor3f((float)192 / 255, (float)192 / 255, (float)192 / 255);
	}
	for (int i = 0; i < 21; i++)
	{
		if (i == 10)
			glColor3f((float)0 / 255, (float)255 / 255, (float)51 / 255);

		glVertex2f(144 + 0, 40 + 32 + 16 * i);
		glVertex2f(144 + 512, 40 + 32 + 16 * i);

		if (i == 10)
			glColor3f((float)192 / 255, (float)192 / 255, (float)192 / 255);

	}
	glEnd();

	glFlush();
}

int main(int argc, char ** argv)
{
	setlocale(LC_ALL, "");
	srand(time(NULL));

	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 32; j++)
		{
			arr[i][j] = false;
			arr1[i][j] = false;
		}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 200);
	glutCreateWindow("Яковенко В.В. АВТ-615");
	glutDisplayFunc(Display);
	Initialize(width, height);
	glutMouseFunc(mouseFunc);
	glutMainLoop();

	return 0;
}