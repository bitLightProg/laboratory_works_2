#include <GL/freeglut.h>
#include <iostream>
#include <ctime>

using namespace std;

bool is_line_on_screen = false;
bool arr[20][32];
bool arr1[20][32];

GLint width = 800, height = 400;
short x_centre = 400, y_centre = 232;
bool dda = 1, brez = 1;


int lenght(int begin, int end)
{
	if (begin * end < 0)
	{
		return end - begin >= 0 ? end - begin - 1 : end - begin + 1;
	}
	else return end - begin;
}

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

void draw_pixel(int y, int x, short mode = 1);

void DDA(short x0, short y0, short x1, short y1)
{
	short px = lenght(x0, x1);
	short py = lenght(y0, y1);

	if (abs(px) >= abs(py))
	{
		if (px >= 0)
		{
			float p = (float)py / px;
			for (float i = x0 + 1, j = y0; i < x1; i++)
			{
				if (i == 0)
					i++;

				j += p;
				if (j >= 0 && j < 1 && p < 0)
				{
					j--;
				}
				else if (j >= 0 && j < 1 && p > 0)
				{
					j++;
				}
				short y = intl(j);
				short x = intl(i);
				y = y > 0 ? 10 - y : 9 - y;
				x = x > 0 ? 15 + x : 16 + x;
				if (arr[y][x] == 1)
				{
					arr[y][x] = 0;
					continue;
				}
				arr[y][x] = 1;
			}
		}
		else if (px < 0)
		{
			float p = (float)-py / px;
			for (float i = x0 - 1, j = y0; i > x1; i--)
			{
				if (i == 0)
					i--;

				j += p;
				if (j >= 0 && j < 1 && p < 0)
				{
					j--;
				}
				else if (j >= 0 && j < 1 && p > 0)
				{
					j++;
				}

				short y = intl(j);
				short x = intl(i);
				y = y > 0 ? 10 - y : 9 - y;
				x = x > 0 ? 15 + x : 16 + x;
				if (arr[y][x] == 1)
				{
					arr[y][x] = 0;
					continue;
				}
				arr[y][x] = 1;
			}
		}
	}
	else
		if (abs(px) < abs(py))
		{
			if (py >= 0)
			{
				float p = (float)px / py;
				for (float i = y0 + 1, j = x0; i < y1; i++)
				{
					if (i == 0)
						i++;
					
					j += p;
					if (j >= 0 && j < 1 && p < 0)
					{
						j--;
					}
					else if (j >= 0 && j < 1 && p > 0)
					{
						j++;
					}

					short y = intl(i);
					short x = intl(j);
					y = y > 0 ? 10 - y : 9 - y;
					x = x > 0 ? 15 + x : 16 + x;
					if (arr[y][x] == 1)
					{
						arr[y][x] = 0;
						continue;
					}
					arr[y][x] = 1;
				}
			}
			else if (py < 0)
			{
				float p = (float)-px / py;
				for (float i = y0 - 1, j = x0; i > y1; i--)
				{
					if (i == 0)
						i--;
					
					j += p;
					if (j >= 0 && j < 1 && p < 0)
					{
						j--;
					}
					else if (j >= 0 && j < 1 && p > 0)
					{
						j++;
					}

					short y = intl(i);
					short x = intl(j);
					y = y > 0 ? 10 - y : 9 - y;
					x = x > 0 ? 15 + x : 16 + x;
					if (arr[y][x] == 1)
					{
						arr[y][x] = 0;
						continue;
					}
					arr[y][x] = 1;
				}
			}
		}
}

void Brezenhem(short x0, short y0, short x1, short y1)
{
	short e = -100;

	short px = lenght(x0, x1);
	short py = lenght(y0, y1);

	if (abs(px) >= abs(py))
	{
		if (px >= 0 && py >= 0)
		{
			for (float i = x0 + 1, j = y0; i < x1; i++)
			{
				if (i == 0)
					i++;
				if (j >= 0 && j < 1 && py > 0)
				{
					j++;
				}
				if (e == -100)
					e = 2 * py - px;
				else
					if (e > 0)
					{
						e += 2 * (py - px);
					}
					else
						if (e <= 0)
						{
							e += 2 * py;
						}

				if (e > 0)
				{
					if (py > 0)
						j++;
					short y = j > 0 ? 10 - j : 9 - j;
					short x = i > 0 ? 15 + i : 16 + i;
					if (arr1[y][x] == 1)
					{
						arr1[y][x] = 0;
						continue;
					}
					arr1[y][x] = 1;
				}
				else
					if (e <= 0)
					{
						short y = j > 0 ? 10 - j : 9 - j;
						short x = i > 0 ? 15 + i : 16 + i;
						if (arr1[y][x] == 1)
						{
							arr1[y][x] = 0;
							continue;
						}
						arr1[y][x] = 1;
					}
			}
		}
		if (px >= 0 && py < 0)
		{
			for (float i = x0 + 1, j = y0; i < x1; i++)
			{
				if (i == 0)
					i++;
				if (j >= 0 && j < 1 && py < 0)
				{
					j--;
				}
				if (e == -100)
					e = -2 * py - px;
				else
					if (e > 0)
					{
						e += 2 * (-py - px);
					}
					else
						if (e <= 0)
						{
							e += -2 * py;
						}

				if (e > 0)
				{
					if (py < 0)
						j--;
					short y = j > 0 ? 10 - j : 9 - j;
					short x = i > 0 ? 15 + i : 16 + i;
					if (arr1[y][x] == 1)
					{
						arr1[y][x] = 0;
						continue;
					}
					arr1[y][x] = 1;
				}
				else
					if (e <= 0)
					{
						short y = j > 0 ? 10 - j : 9 - j;
						short x = i > 0 ? 15 + i : 16 + i;
						if (arr1[y][x] == 1)
						{
							arr1[y][x] = 0;
							continue;
						}
						arr1[y][x] = 1;
					}
			}
		}
		if (px < 0 && py < 0)
		{
			for (float i = x0 - 1, j = y0; i > x1; i--)
			{
				if (i == 0)
					i--;
				if (j >= 0 && j < 1 && py < 0)
				{
					j--;
				}
				if (e == -100)
					e = 2 * -py + px;
				else
					if (e > 0)
					{
						e += 2 * (-py + px);
					}
					else
						if (e <= 0)
						{
							e += 2 * -py;
						}

				if (e > 0)
				{
					if (py < 0)
						j--;
					short y = j > 0 ? 10 - j : 9 - j;
					short x = i > 0 ? 15 + i : 16 + i;
					if (arr1[y][x] == 1)
					{
						arr1[y][x] = 0;
						continue;
					}
					arr1[y][x] = 1;
				}
				else
					if (e <= 0)
					{
						short y = j > 0 ? 10 - j : 9 - j;
						short x = i > 0 ? 15 + i : 16 + i;
						if (arr1[y][x] == 1)
						{
							arr1[y][x] = 0;
							continue;
						}
						arr1[y][x] = 1;
					}
			}
		}
		if (px < 0 && py >= 0)
		{
			for (float i = x0 - 1, j = y0; i > x1; i--)
			{
				if (i == 0)
					i--;
				if (j >= 0 && j < 1 && py > 0)
				{
					j++;
				}
				if (e == -100)
					e = 2 * py + px;
				else
					if (e > 0)
					{
						e += 2 * (py + px);
					}
					else
						if (e <= 0)
						{
							e += 2 * py;
						}

				if (e > 0)
				{
					if (py > 0)
						j++;
					short y = j > 0 ? 10 - j : 9 - j;
					short x = i > 0 ? 15 + i : 16 + i;
					if (arr1[y][x] == 1)
					{
						arr1[y][x] = 0;
						continue;
					}
					arr1[y][x] = 1;
				}
				else
					if (e <= 0)
					{
						short y = j > 0 ? 10 - j : 9 - j;
						short x = i > 0 ? 15 + i : 16 + i;
						if (arr1[y][x] == 1)
						{
							arr1[y][x] = 0;
							continue;
						}
						arr1[y][x] = 1;
					}
			}
		}
	}
	else
	{
		if (px >= 0 && py >= 0)
		{
			for (float i = y0 + 1, j = x0; i < y1; i++)
			{
				if (i == 0)
					i++;
				if (j >= 0 && j < 1 && px > 0)
				{
					j++;
				}
				if (e == -100)
					e = 2 * px - py;
				else
					if (e > 0)
					{
						e += 2 * (px - py);
					}
					else
						if (e <= 0)
						{
							e += 2 * px;
						}

				if (e > 0)
				{
					if (px > 0)
						j++;
					short y = i > 0 ? 10 - i : 9 - i;
					short x = j > 0 ? 15 + j : 16 + j;
					if (arr1[y][x] == 1)
					{
						arr1[y][x] = 0;
						continue;
					}
					arr1[y][x] = 1;
				}
				else
					if (e <= 0)
					{
						short y = i > 0 ? 10 - i : 9 - i;
						short x = j > 0 ? 15 + j : 16 + j;
						if (arr1[y][x] == 1)
						{
							arr1[y][x] = 0;
							continue;
						}
						arr1[y][x] = 1;
					}
			}
		}
		if (px >= 0 && py < 0)
		{
			for (float i = y0 - 1, j = x0; i > y1; i--)
			{
				if (i == 0)
					i--;
				if (j >= 0 && j < 1 && px > 0)
				{
					j++;
				}
				if (e == -100)
					e = 2 * px + py;
				else
					if (e > 0)
					{
						e += 2 * (px + py);
					}
					else
						if (e <= 0)
						{
							e += 2 * px;
						}

				if (e > 0)
				{
					if (px > 0)
						j++;
					short y = i > 0 ? 10 - i : 9 - i;
					short x = j > 0 ? 15 + j : 16 + j;
					if (arr1[y][x] == 1)
					{
						arr1[y][x] = 0;
						continue;
					}
					arr1[y][x] = 1;
				}
				else
					if (e <= 0)
					{
						short y = i > 0 ? 10 - i : 9 - i;
						short x = j > 0 ? 15 + j : 16 + j;
						if (arr1[y][x] == 1)
						{
							arr1[y][x] = 0;
							continue;
						}
						arr1[y][x] = 1;
					}
			}
		}
		if (px < 0 && py < 0)
		{
			for (float i = y0 - 1, j = x0; i > y1; i--)
			{
				if (i == 0)
					i--;
				if (j >= 0 && j < 1 && px < 0)
				{
					j--;
				}
				if (e == -100)
					e = 2 * -px + py;
				else
					if (e > 0)
					{
						e += 2 * (-px + py);
					}
					else
						if (e <= 0)
						{
							e += 2 * -px;
						}

				if (e > 0)
				{
					if (px < 0)
						j--;
					short y = i > 0 ? 10 - i : 9 - i;
					short x = j > 0 ? 15 + j : 16 + j;
					if (arr1[y][x] == 1)
					{
						arr1[y][x] = 0;
						continue;
					}
					arr1[y][x] = 1;
				}
				else
					if (e <= 0)
					{
						short y = i > 0 ? 10 - i : 9 - i;
						short x = j > 0 ? 15 + j : 16 + j;
						if (arr1[y][x] == 1)
						{
							arr1[y][x] = 0;
							continue;
						}
						arr1[y][x] = 1;
					}
			}
		}
		if (px < 0 && py >= 0)
		{
			for (float i = y0 + 1, j = x0; i < y1; i++)
			{
				if (i == 0)
					i++;
				if (j >= 0 && j < 1 && px < 0)
				{
					j--;
				}
				if (e == -100)
					e = 2 * -px - py;
				else
					if (e > 0)
					{
						e += 2 * (-px - py);
					}
					else
						if (e <= 0)
						{
							e += 2 * -px;
						}

				if (e > 0)
				{
					if (px < 0)
						j--;
					short y = i > 0 ? 10 - i : 9 - i;
					short x = j > 0 ? 15 + j : 16 + j;
					if (arr1[y][x] == 1)
					{
						arr1[y][x] = 0;
						continue;
					}
					arr1[y][x] = 1;
				}
				else
					if (e <= 0)
					{
						short y = i > 0 ? 10 - i : 9 - i;
						short x = j > 0 ? 15 + j : 16 + j;
						if (arr1[y][x] == 1)
						{
							arr1[y][x] = 0;
							continue;
						}
						arr1[y][x] = 1;
					}
			}
		}
	}

}

void Display();
void Initialize(int w, int h);

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
			if (is_line_on_screen)
			{
				if (dda && brez)
				{
					brez = 0;
					Initialize(width, height);
					Display();
				}
				else if (dda)
				{
					dda = 0; brez = 1;
					Initialize(width, height);
					Display();
				}
				else if (brez)
				{
					dda = 1;
					Initialize(width, height);
					Display();
				}
				return;
			}
				
			x -= x_centre;
			y -= y_centre;
			
			int temp;
			x > 0 ? temp = 1 : temp = -1;
			x /= 16;
			x > 0 ? x++ : x < 0 ? x-- : x;
			x == 0 ? temp == 1 ? x++ : x-- : x;

			y > 0 ? temp = 1 : temp = -1;
			y /= 16;
			y > 0 ? y++ : y < 0 ? y-- : y;
			y == 0 ? temp == 1 ? y++ : y-- : y;
			
			arr[y > 0 ? 10 - y : 9 - y][x > 0 ? 15 + x : 16 + x] = true;
			arr1[y > 0 ? 10 - y : 9 - y][x > 0 ? 15 + x : 16 + x] = true;

			if (main_line.next_point == NULL)
			{
				main_line.x = x;
				main_line.y = y;
				main_line.next_point = new line;
			}
			else
			{
				if (is_line_on_screen)
					return;

				is_line_on_screen = true;
				main_line.next_point->x = x;
				main_line.next_point->y = y;				

				DDA(main_line.x, main_line.y, main_line.next_point->x, main_line.next_point->y);

				Brezenhem(main_line.x, main_line.y, main_line.next_point->x, main_line.next_point->y);
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
			x -= x_centre;
			y -= y_centre;

			int temp;
			x > 0 ? temp = 1 : temp = -1;
			x /= 16;
			x > 0 ? x++ : x < 0 ? x-- : x;
			x == 0 ? temp == 1 ? x++ : x-- : x;

			y > 0 ? temp = 1 : temp = -1;
			y /= 16;
			y > 0 ? y++ : y < 0 ? y-- : y;
			y == 0 ? temp == 1 ? y++ : y-- : y;

			y = y > 0 ? 10 - y : 9 - y;
			x = x > 0 ? 15 + x : 16 + x;
			if (arr[y][x] == 1 || arr1[y][x] == 1)
			{
				DDA(main_line.x, main_line.y, main_line.next_point->x, main_line.next_point->y);
				Brezenhem(main_line.x, main_line.y, main_line.next_point->x, main_line.next_point->y);
				arr[main_line.y > 0 ? 10 - main_line.y : 9 - main_line.y][main_line.x > 0 ? 15 + main_line.x : 16 + main_line.x] = 0;
				arr1[main_line.y > 0 ? 10 - main_line.y : 9 - main_line.y][main_line.x > 0 ? 15 + main_line.x : 16 + main_line.x] = 0;
				draw_pixel(main_line.y, main_line.x, 0);
				arr[main_line.next_point->y > 0 ? 10 - main_line.next_point->y : 9 - main_line.next_point->y][main_line.next_point->x > 0 ? 15 + main_line.next_point->x : 16 + main_line.next_point->x] = 0;
				arr1[main_line.next_point->y > 0 ? 10 - main_line.next_point->y : 9 - main_line.next_point->y][main_line.next_point->x > 0 ? 15 + main_line.next_point->x : 16 + main_line.next_point->x] = 0;
				draw_pixel(main_line.next_point->y, main_line.next_point->x, 0);
				delete main_line.next_point;
				main_line.next_point = NULL;
				is_line_on_screen = false;
				Initialize(width, height);
				Display();
			}
			arr[y][x] = 0;
		}
	}
}
void draw_pixel(int y, int x, short mode)
{

	if (mode == 0)
	{
		glColor3f((float)0 / 255, (float)0 / 255, (float)0 / 255);
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
		return;
	}
	if (mode == 2)
	{
		glColor3f((float)255 / 255, (float)64 / 255, (float)0 / 255);
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
		return;
	}
	if (mode == 3)
	{
		glColor3f((float)0 / 255, (float)64 / 255, (float)255 / 255);
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
		return;
	}
	if (mode == 4)
	{
		glColor3f((float)255 / 255, (float)64 / 255, (float)255 / 255);
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
		return;
	}

	glColor3f((float)dda*arr[y > 0 ? 10 - y : 9 - y][x > 0 ? 15 + x : 16 + x]*255 / 255, (float)64 / 255, (float)brez*arr1[y > 0 ? 10 - y : 9 - y][x > 0 ? 15 + x : 16 + x] *255 / 255);
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
				draw_pixel(i > 9 ? 9 - i: 10 - i, j > 15 ? j - 15: j - 16);
			}
	}

	draw_pixel(-12, -14, 2); renderBitmapString(x_centre + -13 * 16 + 4, y_centre + -12 * 16 + 4, GLUT_BITMAP_9_BY_15, "DDA");
	draw_pixel(-12, -8, 3); renderBitmapString(x_centre + -7 * 16 + 4, y_centre + -12 * 16 + 4, GLUT_BITMAP_9_BY_15, "Brezenhem"); //Brezenhem
	draw_pixel(-12, 4, 4); renderBitmapString(x_centre + 4 * 16 + 4, y_centre + -12 * 16 + 4, GLUT_BITMAP_9_BY_15, "DDA + Brezenhem");

	if (is_line_on_screen)
	{
		glColor3f((float)21 / 255, (float)131 / 255, (float)240 / 255);
		glBegin(GL_LINES);

		glVertex2f(x_centre + (main_line.x > 0 ? main_line.x * 16 - 8 : main_line.x * 16 + 8), y_centre + (main_line.y > 0 ? main_line.y * 16 - 8 : main_line.y * 16 + 8));
		glVertex2f(x_centre + (main_line.next_point->x > 0 ? main_line.next_point->x * 16 - 8 : main_line.next_point->x * 16 + 8), y_centre + (main_line.next_point->y > 0 ? main_line.next_point->y * 16 - 8 : main_line.next_point->y * 16 + 8));

		glVertex2f(x_centre + (main_line.x > 0 ? main_line.x * 16 - 8 : main_line.x * 16 + 8), y_centre + (main_line.y > 0 ? main_line.y * 16 - 7 : main_line.y * 16 + 7));
		glVertex2f(x_centre + (main_line.next_point->x > 0 ? main_line.next_point->x * 16 - 8 : main_line.next_point->x * 16 + 8), y_centre + (main_line.next_point->y > 0 ? main_line.next_point->y * 16 - 7 : main_line.next_point->y * 16 + 7));

		glVertex2f(x_centre + (main_line.x > 0 ? main_line.x * 16 - 8 : main_line.x * 16 + 8), y_centre + (main_line.y > 0 ? main_line.y * 16 - 9 : main_line.y * 16 + 9));
		glVertex2f(x_centre + (main_line.next_point->x > 0 ? main_line.next_point->x * 16 - 8 : main_line.next_point->x * 16 + 8), y_centre + (main_line.next_point->y > 0 ? main_line.next_point->y * 16 - 9 : main_line.next_point->y * 16 + 9));

		glEnd();
	}

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
	glutCreateWindow("ßêîâåíêî Â.Â. ÀÂÒ-615");
	glutDisplayFunc(Display);
	Initialize(width, height);
	glutMouseFunc(mouseFunc);
	glutMainLoop();

	delete main_line.next_point;
	return 0;
}