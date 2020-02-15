#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	cout << "Case #1:" << endl;
	fstream fin("sample.in");
	//fstream fin("E-small-practice.in");
	//fstream fin("E-large-practice.in");
	fin.seekg(0, fin.end);
	int len = fin.tellg();
	fin.seekg(0, fin.beg);
	char *buffer=new char[len + 1];
	fin.read(buffer, len);
	fin.close();
	int stk = 0, iout = 0;
	char last = '\t';
	for (int i = 0; i < len; ++i)
	{
		if (last == '/' && buffer[i] == '*')
		{
			if (stk == 0) --iout;
			++stk;
			last = '\t';
		}
		else if (last == '*' && buffer[i] == '/')
		{
			if (stk == 0)
			{
				buffer[iout++] = '/';
				last = '/';
			}
			else
			{
				--stk;
				last = '\t';
			}
		}
		else if (stk == 0)
		{
			buffer[iout++] = buffer[i];
			last = buffer[i];
		}
		else
		{
			last = buffer[i];
		}
	}
	buffer[iout] = '\0';
	cout << buffer << endl;
	delete[] buffer;
	return 0;
}
