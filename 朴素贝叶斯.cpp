#include <iostream>  
#include <set>  
#include <vector>  
#include<fstream>
#include<string>
#include<string.h>
#include<random>  
#include<time.h>


using namespace std;

ifstream datafile("G:\\im\\titanic.dat");		


multiset<double> Val_Class, Val_Age, Val_Sex;			//各属性所有值
multiset<double> Val_Class_, Val_Age_, Val_Sex_;

set<double> Classset, Ageset, Sexset;			//各属性所有可能的值
set<double> Classset_, Ageset_, Sexset_;

vector<double> Classvector,Agevector, Sexvector;
vector<double> Classvector_, Agevector_, Sexvector_;

vector<double> Classtest, Agetest, Sextest, Survivetest;		//测试集

vector<double>::iterator it2,it1;				//迭代器
set<double>::iterator it0;



double Py_1, Py1;

default_random_engine random(time(NULL));		//产生1-100的随机数
uniform_int_distribution<int> dis(1, 100);


int main()
{
	int all_num = 0;			//训练数据总数
	int num_1 = 0;
	string line;				//每行的字符
	double Class, Age, Sex;		//属性值
	double survive;				//待分类属性

	cout << "正在分析概率..." << endl;
	while (getline(datafile,line))		//数据读入
	{
		cout << line << endl;
		if (line[0] == '@') continue;
		sscanf(const_cast<char*>(line.c_str()), "%lf,%lf,%lf,%lf", &Class, &Age, &Sex, &survive);
		
		if (dis(random) < 71)		//写入训练集
		{
			if (survive == 1.0)
			{
				Classset.insert(Class);				//set
				Ageset.insert(Age);
				Sexset.insert(Sex);

				Val_Class.insert(Class);			//multiset
				Val_Age.insert(Age);
				Val_Sex.insert(Sex);

				Classvector.push_back(Class);			//vector
				Agevector.push_back(Age);
				Sexvector.push_back(Sex);

				num_1++;
			}
			else
			{
				Classset_.insert(Class);				//set
				Ageset_.insert(Age);
				Sexset_.insert(Sex);

				Val_Class_.insert(Class);			//multiset
				Val_Age_.insert(Age);
				Val_Sex_.insert(Sex);

				Classvector_.push_back(Class);			//vector
				Agevector_.push_back(Age);
				Sexvector_.push_back(Sex);
			}

			all_num++;

		}
		else								//写入测试集
		{
			Classtest.push_back(Class);
			Agetest.push_back(Age);
			Sextest.push_back(Sex);
			Survivetest.push_back(survive);
		}
		
	}



	Py1 =num_1 / (double)all_num;		//P(y=1)
	Py_1 = 1 - Py1;						//P(y=-1)

	cout << "P(y=1)=" << Py1 << endl;
	cout << "P(y=-1)=" << Py_1 << endl;
	cout << "训练集数据数目" << all_num << endl;
	cout << "测试集数目" << Agetest.size() << endl;

	//条件概率

	vector<double> P_Class, P_Age, P_Sex;
	vector<double> P_Class_, P_Age_, P_Sex_;
	vector<double> Class_set_vector, Age_set_vector, Sex_set_vector;
	vector<double> Class_set_vector_, Age_set_vector_, Sex_set_vector_;

	copy(Classset.begin(), Classset.end(), back_inserter(Class_set_vector));
	copy(Ageset.begin(), Ageset.end(), back_inserter(Age_set_vector));
	copy(Sexset.begin(), Sexset.end(), back_inserter(Sex_set_vector));
	copy(Classset_.begin(), Classset_.end(), back_inserter(Class_set_vector_));
	copy(Ageset_.begin(), Ageset_.end(), back_inserter(Age_set_vector_));
	copy(Sexset_.begin(), Sexset_.end(), back_inserter(Sex_set_vector_));

	//y=1时Class的条件概率
	double PC0=1.0;
	for (it2 = Class_set_vector.begin(); it2 != Class_set_vector.end(); it2++)
	{
		PC0 = Val_Class.count(*it2) / (double)num_1;
		P_Class.push_back(PC0);
	}

	//y=1时Age的条件概率
	for (it2 = Age_set_vector.begin(); it2 != Age_set_vector.end(); it2++)
	{
		PC0 = Val_Age.count(*it2) / (double)num_1;
		P_Age.push_back(PC0);
	}

	//y=1时Sex的条件概率
	for (it2 = Sex_set_vector.begin(); it2 != Sex_set_vector.end(); it2++)
	{
		PC0 = Val_Sex.count(*it2) / (double)num_1;
		P_Sex.push_back(PC0);
	}

	//y=-1时Class的条件概率
	for (it2 = Class_set_vector_.begin(); it2 != Class_set_vector_.end(); it2++)
	{
		PC0 = Val_Class_.count(*it2) / (double)(all_num-num_1);
		P_Class_.push_back(PC0);
	}


	//y=-1时Age的条件概率
	for (it2 = Age_set_vector_.begin(); it2 != Age_set_vector_.end(); it2++)
	{
			PC0 = Val_Age_.count(*it2) / (double)(all_num - num_1);
		P_Age_.push_back(PC0);
	}

	//y=-1时Sex的条件概率
	for (it2 = Sex_set_vector_.begin(); it2 != Sex_set_vector_.end(); it2++)
	{
		PC0 = Val_Sex_.count(*it2) / (double)(all_num - num_1);
		P_Sex_.push_back(PC0);
	}


	cout << "读取测试集..." << endl;

	double P11=1.0, P21=1.0, P31=1.0;
	double P12 = 1.0, P22 = 1.0, P32 = 1.0;
	double P1 = 1.0, P2 = 1.0;
	int right = 0, wrong = 0;
	double solution;
	for (int i = 0; i < Agetest.size(); i++)
	{

		Class = Classtest[i];
		Age = Agetest[i];
		Sex = Sextest[i];
		solution = Survivetest[i];

		//survive=1情况下的概率

		for (unsigned int i = 0; i < Class_set_vector.size(); i++)
		{
			if (Class_set_vector[i] == Class)
				P11 = P_Class[i];
		}

		for (unsigned int i = 0; i < Age_set_vector.size(); i++)
		{
			if (Age_set_vector[i] == Age)
				P21 = P_Age[i];
		}

		for (unsigned int i = 0; i < Sex_set_vector.size(); i++)
		{
			if (Sex_set_vector[i] == Sex)
				P31 = P_Sex[i];
		}

		//survive=-1情况下的概率
		for (unsigned int i = 0; i < Class_set_vector_.size(); i++)
		{
			if (Class_set_vector_[i] == Class)
				P12 = P_Class_[i];
		}

		for (unsigned int i = 0; i < Age_set_vector_.size(); i++)
		{
			if (Age_set_vector_[i] == Age)
				P22 = P_Age_[i];
		}

		for (unsigned int i = 0; i < Sex_set_vector_.size(); i++)
		{
			if (Sex_set_vector_[i] == Sex)
				P32 = P_Sex_[i];
		}

		P1 = Py1*P11*P21*P31;		// 1的概率
		P2 = Py_1*P12*P22*P32;		//-1的概率

		if (P1 > P2&&Survivetest[i] == 1.0)
		{
			right++; continue;
		}
		if (P1 < P2&&Survivetest[i] == -1.0)
		{
			right++; continue;
		}
		wrong++;
	}
	cout << "正确 " << right << endl;
	cout << "错误" << wrong << endl;
	cout << "正确率" << right / (double)(right + wrong) << endl;


	system("pause");
	return 0;
}
