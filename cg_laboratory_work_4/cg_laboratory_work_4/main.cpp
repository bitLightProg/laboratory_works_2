#include <GL/freeglut.h>
#include <iostream>
#include <ctime>
#include <stack>

using namespace std;

GLint width = 800, height = 400;
short init_mode = 1;
unsigned char *arr;
int max_count = width*height * 3;

short points_count = 0;
short list_count = 0;

struct point
{
	short x;
	short y;
	short md = 0;
};

stack<point> st;

void Initialize(int w, int h)
{
	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, h, 0);


	glClear(GL_COLOR_BUFFER_BIT);
	
	glColor3f((float)255 / 255, (float)64 / 255, (float)64 / 255);

	glBegin(GL_LINE_LOOP);
	float x = 400;
	float y = 400 - 275 - 45;
	int r = 40;

	for (int i = 0; i < 30; i++)
	{
		float angle = 2.0 * 3.1415926 * float(i) / float(30);

		float dx = r * cosf(angle);
		float dy = r * sinf(angle);

		glVertex2f(x + dx, y + dy);
	}
	glEnd();

	glBegin(GL_LINE_LOOP);
	r = 70;

	for (int i = 0; i < 30; i++)
	{
		float angle = 2.0 * 3.1415926 * float(i) / float(30);

		float dx = r * cosf(angle);
		float dy = r * sinf(angle);

		glVertex2f(x + dx, y + dy);
	}
	glEnd();

	glColor3f((float)255 / 255, (float)64 / 255, (float)64 / 255);

	glBegin(GL_LINES);

	glVertex2f(x, y + r); //1
	glVertex2f(x - (int)r*cos(46 * 3.14 / 180), y - (int)r*sin(46 * 3.14 / 180));//4

	glVertex2f(x, y + r);//1
	glVertex2f(x + (int)r*cos(46 * 3.14 / 180), y - (int)r*sin(46 * 3.14 / 180));//3

	glVertex2f(x - (int)r*cos(46 * 3.14 / 180), y - (int)r*sin(46 * 3.14 / 180));//4
	glVertex2f(x + (int)r*sin(69 * 3.14 / 180), y + (int)r*cos(69 * 3.14 / 180));//2

	glVertex2f(x + (int)r*sin(69 * 3.14 / 180), y + (int)r*cos(69 * 3.14 / 180));//2
	glVertex2f(x - (int)r*sin(69 * 3.14 / 180), y + (int)r*cos(69 * 3.14 / 180));//5

	glVertex2f(x - (int)r*sin(69 * 3.14 / 180), y + (int)r*cos(69 * 3.14 / 180));//5
	glVertex2f(x + (int)r*cos(46 * 3.14 / 180), y - (int)r*sin(46 * 3.14 / 180));//3

	glEnd();

	glBegin(GL_LINE_LOOP);



	x -= 85;
	y += 125 + 45;
	r += 45;
	
	for (int i = 0; i < 30; i++)
	{
		float angle = 2.0 * 3.1415926 * float(i * 16 + 90) / float(30);

		float dx = r * cosf(angle);
		float dy = r * sinf(angle);

		glVertex2f(x + 90 + dx, y + 30 + dy);
	}
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2f(20, 20);
	glVertex2f(20, 60);
	glVertex2f(60, 60);
	glVertex2f(60, 20);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex2f(30, 30);
	glVertex2f(30, 40);
	glVertex2f(40, 40);
	glVertex2f(40, 30);
	glEnd();
	glFlush();
}

int fill_it_all(int x, int y, short mode)
{
	if (x < 0 || y < 0 || x >= width || y >= height)
		return 0;
	int init = (400 - y) * 3 * width + x * 3;
	if (init < 0)
		return 0;
	if ((bool)(arr[init]) != (!mode))
		return 0;
	glColor3f((float)255 / 255 * mode, (float)64 / 255 * mode, (float)64 / 255 * mode);
	int he = -1;
	int we = -1;
	he = 400 - init / 3 / (width);
	we = (init / 3) % (width);
	
	short x_md[4];
	short y_md[4];
	/*x_md[0] = 1; // Против часовой справа
	x_md[1] = 0;
	x_md[2] = -1;
	x_md[3] = 0;
	y_md[0] = 0;
	y_md[1] = -1;
	y_md[2] = 0;
	y_md[3] = 1;*/

	x_md[0] = 0; // По часовой снизу
	x_md[1] = -1;
	x_md[2] = 0;
	x_md[3] = 1;
	y_md[0] = -1;
	y_md[1] = 0;
	y_md[2] = 1;
	y_md[3] = 0;

	/*x_md[0] = 1;// Наискосок
	x_md[1] = -1;
	x_md[2] = -1;
	x_md[3] = 1;
	y_md[0] = 1;
	y_md[1] = 1;
	y_md[2] = -1;
	y_md[3] = -1;*/
	
	point pushed;
	pushed.x = x;
	pushed.y = y;
	st.push(pushed);
	short md = 0;
	for (;;)
	{
		bool f = false;
		init = (400 - y) * 3 * width + x * 3;
		glBegin(GL_POINTS);
		
		if (x < 0 || y < 0 || x >= width || y >= height)
		{
			if (st.size() <= 0)
				break;

			point a = st.top();
			
			x = a.x;
			y = a.y;
			md = a.md;
			md++;
			init = (400 - y) * 3 * width + x * 3;
			st.pop();
		}
		if (((bool)(arr[init]) != (!mode)) && md == 0)
		{
			if (st.size() <= 0)
				break;

			point a = st.top();

			x = a.x;
			y = a.y;
			md = a.md;
			md++;
			init = (400 - y) * 3 * width + x * 3;
			st.pop();
		}
		if (md > 3)
		{
			if (st.size() <= 0)
				break;

			point a = st.top();

			x = a.x;
			y = a.y;
			md = a.md;
			md++;
			init = (400 - y) * 3 * width + x * 3;
			st.pop();
		}
		
		if (arr[init] == 255 * mode)
			f = true;
		arr[init] = 255 * mode;
		glVertex2f(x, y);
		pushed.x = x;
		pushed.y = y;
		pushed.md = md;
		st.push(pushed);

		x += x_md[md];
		y += y_md[md];
		md = 0;
		
		glEnd();
		if (!f)
		{
			glFlush();
		}
			//glFlush();
		
	}
	glFlush();
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

			fill_it_all(x, y, (short)(arr[(400 - y) * 3 * width + x * 3] == 0 ? 1 : 0));
			glVertex2f(x, y);

			glEnd();
			glFlush();			
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