#include <iostream>  
#include <set>  
#include <vector>  
#include<fstream>
#include<string>
#include<string.h>

using namespace std;

ifstream datafile("G:\\im\\titanic.dat");		


multiset<int> Val_survive;
multiset<double> Val_Class, Val_Age, Val_Sex;			//各属性所有可能的值

set<int> surviveset;
set<double> Classset, Ageset, Sexset;			//各属性所有可能的值


multiset<int>::iterator it1;
multiset<double>::iterator it2;

double Py_1, Py1;


int main()
{
	int all_num = 0;			//训练数据总数
	string line;				//每行的字符
	double Class, Age, Sex;		//属性值
	int survive;				//待分类属性



	Val_Age.clear();			//vector初始化
	Val_Class.clear();
	Val_Sex.clear();
	Val_survive.clear();

	while (getline(datafile,line))		//数据读入
	{
		cout << line << endl;
		sscanf(const_cast<char*>(line.c_str()), "%lf,%lf,%lf,%d", &Class, &Age, &Sex, &survive);

		Classset.insert(Class);				//set
		Ageset.insert(Age);
		Sexset.insert(Sex);
		surviveset.insert(survive);

		Val_Class.insert(Class);			//multiset
		Val_Age.insert(Age);
		Val_Sex.insert(Sex);
		Val_survive.insert(survive);

		all_num++;
	}

	Py1 = Val_survive.count(1) / (double)all_num;		//P(y=1)
	Py_1 = 1 - Py1;										//P(y=-1)

	cout << "P(y=1)=" << Py1 << endl;

	//条件概率




	system("pause");
	return 0;
}
