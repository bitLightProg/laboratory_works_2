#include <GL/freeglut.h>
#include <iostream>
#include <ctime>
#include <stack>

using namespace std;

GLint width = 800, height = 400;
unsigned char *arr;

struct point
{
	short x;
	short y;
	short md = 0;
};

stack<point> st;
stack<point> points;

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

int push_el(stack<point> &st, int &x, int &y, int &md)
{
	point p;
	p.x = x;
	p.y = y;
	p.md = md;
	st.push(p);
	return 0;
}

int pop_el(stack<point> &st, int &x, int &y, int &md)
{
	if (st.size() <= 0)
		return 1;

	point p;
	p = st.top();
	st.pop();
	x = p.x;
	y = p.y;
	md = p.md;
	return 0;
}
bool was[800 * 400];
int fill_it_all(int x, int y, short mode)
{
	if (x < 0 || y < 0 || x >= width || y >= height)
		return 0;
	int init = (400 - y) * 3 * width + x * 3;
	if (init < 0)
		return 0;
	if ((bool)(arr[init]) != (!mode))
		return 0;
	glColor3f((float)255 / 255 * mode, (float)64 / 255 * mode, (float)255 / 255 * mode);
	int he = -1;
	int we = -1;
	he = 400 - init / 3 / (width);
	we = (init / 3) % (width);

	short x_md[4];
	short y_md[4];

	x_md[0] = 0; // По часовой снизу
	x_md[1] = -1;
	x_md[2] = 0;
	x_md[3] = 1;
	y_md[0] = -1;
	y_md[1] = 0;
	y_md[2] = 1;
	y_md[3] = 0;

	int md = 0;	

	for (int i = 0; i < 800 * 400; i++)
	{
		was[i] = false;
	}

	for (;;)
	{
		init = (400 - y) * 3 * width + x * 3;
		if (x < 0 || y < 0 || x >= width || y >= height)
		{
			if (pop_el(st, x, y, md))
				break;
			md++;
			init = (400 - y) * 3 * width + x * 3;
		}
		if (md > 3)
		{
			if (pop_el(st, x, y, md))
				break;
			md++;
			init = (400 - y) * 3 * width + x * 3;
			continue;
		}

		if (was[y*width + x] && md == 0)
		{
			if (pop_el(st, x, y, md))
				break;
			md++;
			init = (400 - y) * 3 * width + x * 3;
			continue;
		}

		was[y*width + x] = true;
		if ((arr[init] == 64 && arr[init + 1] == 255 && arr[init + 2] == 64))
		{
			if ((x < 199 || x > 600) || (y < 100 || y > 300))
			{
				arr[init] = 255 * mode;
				arr[init + 1] = 64 * mode;
				arr[init + 2] = 255 * mode;
				glBegin(GL_POINTS);
				glColor3f((float)255 / 255 * mode, (float)64 / 255 * mode, (float)255 / 255 * mode);
				glVertex2f(x, y);
				glEnd();
			}
			if (pop_el(st, x, y, md))
				break;
			md++;
			init = (400 - y) * 3 * width + x * 3;
			continue;
		}

		if (arr[init] == 255 && arr[init + 1] == 255 && arr[init + 2] == 255)
		{
			arr[init] = 255 * mode;
			arr[init + 1] = 64 * mode;
			arr[init + 2] = 255 * mode;
			glBegin(GL_POINTS);
			glColor3f((float)64 / 255 * mode, (float)255 / 255 * mode, (float)64 / 255 * mode);
			glVertex2f(x, y);
			glEnd();
		}
		
		push_el(st, x, y, md);

		x += x_md[md];
		y += y_md[md];
		md = 0;
	}

	return 0;
}

short max_x = -1, max_y = -1, min_x = -1, min_y = -1;



void mouseFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_UP)
		{
			if (x11 == -1)
			{
				cout << x << " " << y << endl;
				glColor3f((float)64 / 255, (float)255 / 255, (float)64 / 255);
				x11 = x;
				y11 = y;
				glBegin(GL_LINE_LOOP);
				glVertex2f(x11, y11);	
				point pushed;
				pushed.x = x;
				pushed.y = y;
				points.push(pushed);
			}
			else
			{	
				cout << x << " " << y << endl;
				glVertex2f(x, y);	
				point pushed;
				pushed.x = x;
				pushed.y = y;
				points.push(pushed);
			}
		}
	}
	if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_UP)
		{
			Initialize(width, height);
			for (int i = 0; i < 800 * 400; i++)
			{
				was[i] = false;
			}
		}
	}
}


void processNormalKeys(unsigned char key, int x, int y)
{
	if (key == 27)
	{
		delete[] arr;
		exit(0);
	}		
	if (key == ' ')
	{
		glEnd();
		x11 = -1;
		glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, arr);

		glColor3f((float)255 / 255, (float)64 / 255, (float)255 / 255);
		
		point pushed1 = points.top();
		points.pop();
		point pushed2 = points.top();
		points.pop();
		point pushed3 = points.top();
		short xx = pushed1.x + round((pushed3.x - pushed1.x) / 2);
		short yy = pushed1.y + round((pushed3.y - pushed1.y) / 2);
		short xx1 = pushed1.x + round((pushed2.x - pushed1.x) / 2);
		short yy1 = pushed1.y + round((pushed2.y - pushed1.y) / 2);
		cout << xx << " " << yy << endl;
		cout << xx1 << " " << yy1 << endl;

		if ((xx != pushed1.x || xx != pushed2.x || xx != pushed3.x) && (yy != pushed1.y || yy != pushed2.y || yy != pushed3.y))
			fill_it_all(xx, yy, 1);
		else
			fill_it_all(xx1, yy1, 1);
		glBegin(GL_POINTS);
		for (int i = 0; i < width*height * 3; i += 3)
		{
			int xx = i / 3 % width;
			int yy = (int)i / 3 / (width);
			yy = 400 - yy;

			if (arr[i + 1] == 255)
			{
				if ((xx < 199 || xx > 600) || (yy < 100 || yy > 300))
				{
					arr[i] = 255;
					glVertex2f(xx, yy);
				}
			}
		}
		glEnd();
		glFlush();
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

	Initialize(width, height);
	glutMouseFunc(mouseFunc);
	glutKeyboardFunc(processNormalKeys);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutMainLoop();

	delete[] arr;
	system("pause");
	return 0;
}

