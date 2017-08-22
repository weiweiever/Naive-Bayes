#include <iostream>  
#include <set>  
#include <vector>  
#include<fstream>
#include<string>
#include<string.h>

using namespace std;

ifstream datafile("G:\\im\\titanic.dat");		

 struct sdata
{
	double Class;
	double Age;
	double Sex;
	int survive;
}d;

vector<sdata> V_sdata;

int main()
{
	string line;
	double Class, Age, Sex;
	int survive;
	while (getline(datafile,line))
	{
		cout << line << endl;
		sscanf(const_cast<char*>(line.c_str()), "%lf,%lf,%lf,%d", &Class, &Age, &Sex, &survive);
		d = { Class,Age,Sex,survive };
		V_sdata.push_back(d);
	}
	system("pause");
	return 0;
}
