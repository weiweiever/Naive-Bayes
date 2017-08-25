#include <iostream>  
#include <set>  
#include <vector>  
#include<fstream>
#include<string>
#include<string.h>

using namespace std;

ifstream datafile("G:\\im\\titanic.dat");		


multiset<double> Val_Survive;
multiset<double> Val_Class, Val_Age, Val_Sex;			//各属性所有值

vector<double> Val_class, Val_age, Val_sex, Val_survive;

set<double> surviveset;
set<double> Classset, Ageset, Sexset;			//各属性所有可能的值


vector<double>::iterator it0,it1;
set<double>::iterator it2,it3,it4;

set<double>::iterator it;

double Py_1, Py1;


int main()
{
	int all_num = 0;			//训练数据总数
	string line;				//每行的字符
	double Class, Age, Sex;		//属性值
	double survive;				//待分类属性



	Val_Age.clear();			//multiset初始化
	Val_Class.clear();
	Val_Sex.clear();
	Val_Survive.clear();

	cout << "正在分析概率..." << endl;

	while (getline(datafile,line))		//数据读入
	{
		cout << line << endl;
		if (line[0] == '@') continue;
		sscanf(const_cast<char*>(line.c_str()), "%lf,%lf,%lf,%lf", &Class, &Age, &Sex, &survive);

		Classset.insert(Class);				//set
		Ageset.insert(Age);
		Sexset.insert(Sex);
		surviveset.insert(survive);

		Val_Class.insert(Class);			//multiset
		Val_Age.insert(Age);
		Val_Sex.insert(Sex);
		Val_Survive.insert(survive);

		Val_class.push_back(Class);			//multiset
		Val_age.push_back(Age);
		Val_sex.push_back(Sex);
		Val_survive.push_back(survive);

		all_num++;
	}

	vector<double> Classvector;
	vector<double> Agevector;
	vector<double> Sexvector;

	copy(Classset.begin(), Classset.end(), back_inserter( Classvector));
	copy(Ageset.begin(), Ageset.end(), back_inserter(Agevector));
	copy(Sexset.begin(), Sexset.end(), back_inserter(Sexvector));


	Py1 = Val_Survive.count(1.0) / (double)Val_Survive.size();		//P(y=1)
	Py_1 = Val_Survive.count(-1.0) / (double)Val_Survive.size();										//P(y=-1)

	cout << "P(y=1)=" << Py1 << endl;
	cout << "P(y=-1)=" << Py_1 << endl;

	//条件概率

	//y=1时Class的条件概率
	double PC0=1.0;
	vector<double> P_Class;
	it1 = Val_survive.begin();
	for (it0 = Classvector.begin(); it0 != Classvector.end(); it0++)
	{
		if (*it1 == -1.0) { it1++; continue; }
		PC0 = Val_Class.count(*it0) / (double)Val_Class.size();
		P_Class.push_back(PC0);
		it1++;
	}

	//y=1时Age的条件概率
	vector<double> P_Age;
	it1 = Val_survive.begin();
	for (it0 = Agevector.begin(); it0 != Agevector.end(); it0++)
	{
		if (*it1 == -1.0) { it1++; continue; }
		PC0 = Val_Age.count(*it0) / (double)Val_Age.size();
		P_Age.push_back(PC0);
		it1++;
	}

	//y=1时Sex的条件概率
	vector<double> P_Sex;
	it1 = Val_survive.begin();
	for (it0 = Sexvector.begin(); it0 != Sexvector.end(); it0++)
	{
		if (*it1 == -1.0) { it1++; continue; }
		PC0 = Val_Sex.count(*it0) / (double)Val_Sex.size();
		P_Sex.push_back(PC0);
		it1++;
	}

	//y=-1时Class的条件概率
	vector<double> P_Class_;
	it1 = Val_survive.begin();
	for (it0 = Classvector.begin(); it0 != Classvector.end(); it0++)
	{
		if (*it1 == 1.0) { it1++; continue; }
		PC0 = Val_Class.count(*it0) / (double)Val_Class.size();
		P_Class_.push_back(PC0);
		it1++;
	}


	//y=-1时Age的条件概率
	vector<double> P_Age_;
	it1 = Val_survive.begin();
	for (it0 = Agevector.begin(); it0 != Agevector.end(); it0++)
	{
		if (*it1 == 1.0) { it1++; continue; }
		else
			PC0 = Val_Age.count(*it0) / (double)Val_Age.size();
		P_Age_.push_back(PC0);
		it1++;
	}

	//y=-1时Sex的条件概率
	vector<double> P_Sex_;
	it1 = Val_survive.begin();
	for (it0 = Sexvector.begin(); it0 != Sexvector.end(); it0++)
	{
		if (*it1 == 1.0) { it1++; continue; }
		PC0 = Val_Sex.count(*it0) / (double)Val_Sex.size();
		P_Sex_.push_back(PC0);
		it1++;
	}


	cout << "请分别输入需要分析的Class、Age、Sex值" << endl;
	cin >> Class;
	cin >> Age;
	cin >> Sex;
	
	double P11=1.0, P21=1.0, P31=1.0;
	double P12 = 1.0, P22 = 1.0, P32 = 1.0;
	
	//survive=1

	for (unsigned int i = 0; i < Classvector.size(); i++)
	{
		if (Classvector[i] == Class)
			P11 = P_Class[i];
	}

	for (unsigned int i = 0; i < Agevector.size(); i++)
	{
		if (Agevector[i] == Age)
			P21 = P_Age[i];
	}

	for (unsigned int i = 0; i < Sexvector.size(); i++)
	{
		if (Sexvector[i] == Sex)
			P31 = P_Sex[i];
	}
	//survive=-1
	for (unsigned int i = 0; i < Classvector.size(); i++)
	{
		if (Classvector[i] == Class)
			P12 = P_Class_[i];
	}

	for (unsigned int i = 0; i < Agevector.size(); i++)
	{
		if (Agevector[i] == Age)
			P22 = P_Age_[i];
	}

	for (unsigned int i = 0; i < Sexvector.size(); i++)
	{
		if (Sexvector[i] == Sex)
			P32 = P_Sex_[i];
	}


	double P1=1.0, P2=1.0;

	P1 = P11*P21*P31;
	P2 = P12*P22*P32;
	cout << "y=1的概率为" << P1 << endl;
	cout << "y=-1的概率为" << P2 << endl;
	if (P1 < P2)
		cout << "y最大可能是-1"<<endl;
	else
		cout << "y最大可能是1" << endl;
	system("pause");
	return 0;
}
