#include <iostream>

using namespace std;


//-----------------------------------------------------------5
void F5(char *c, char *out) {
	for (; *c != 0; c++)
		if (*c != ' ') {
			*out++ = *c;
			if (c[1] == ' ') *out++ = ' ';
		}
	*out = '\0';
}

//------------------------------------------------------------28
int inc1(int vv) { vv++; return vv; }
void main1() { int a, b = 5; a = inc1(b); cout << a << b << ' ' << endl; }

int main()
{
	char out[11];
	F5("123 456 78", out);
	cout << out << endl;
	main1();
	system("pause");
	return 0;
}