#ifndef ASSIST_METHOD_H
#define ASSIST_METHOD_H

#include <set>
#include <list>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

//�����m������ȡn�����������
//Return the number of n-combinations of m (m>=n)
int C(int m,int n);

//�����m������ȡn������������
//Return the number of n-permutations of m (m>=n)
int P(int m,int n);

//��ָ�����ַ���ת��������
//Convert string to an integer
int toInt(char *str);
int toInt(const std::string str);

//��ָ�����ַ���ת����˫���ȸ�����
//Convert string to a double float
double toDouble(char *str);
double toDouble(const std::string str);

//��ȡ�ַ����е�һ������, ���ؽ�ȥ�����ֺ���ַ����׵�ַ
//Find the first number from string, and return a pointer to the left string
//���ַ����в�������, �򷵻صĵ�ַΪNULL
//If there is not any number, return NULL
char* getOneNumFromLine(char* str,int &num);
char* getOneNumFromLine(char* str,double &num);

//���ַ��������λ�ȡ����������(������int��double����), ���������ֵ�����
//Find all numbers (int or double) from string, and return the number of them
template<class T>
int getAllNumFromLine(char* str,std::vector<T> &nums)
{
	T num;
	std::list<T> temp;
	int number=0;
	while(*str!='\0')
	{
		str=getOneNumFromLine(str,num);
		if(str!=NULL)
		{
			temp.push_back(num);
			++number;
		}
		else
			break;
	}

	nums.resize(number);
	std::list<T>::iterator it=temp.begin();
	for(int i=0;i<number;++i,++it)
		nums[i]=*it;

	return number;
}

//���������������, �õ���Ӧ���ַ���
//convert integer to a string
void toString(int num,char** str);

//����string��tag֮��ĵ�һ���ַ��ĵ�ַ
//Find a sub-string tag from string str, and return a pointer to the end of tag
char* InterceptString(char* str,char* tag);

//������һ�����
//Generate the next k-combination of the set {0,1,..,n-1}
//Where k=combination.size() and n=elements_number
bool next_combination(std::vector<int> &combination,
					  int elements_number,
					  bool is_lexical=false);

/************************************************
If is_lexical=true, next_combination_1() will be called by next_combination()
E.g. for the set {0,1,2,3,4} and k=3, there will be
	0,1,2
	0,1,3
	0,1,4
	0,2,3
	0,2,4
	0,3,4
	1,2,3
	1,2,4
	1,3,4
	2,3,4
*************************************************/
bool next_combination_1(std::vector<int> &combination,int elements_num);

/************************************************
If is_lexical=false, next_combination_2() will be called by next_combination()
E.g. for the set {0,1,2,3,4} and k=3, there will be
	0,1,2
	0,1,3
	0,2,3
	1,2,3
	0,1,4
	0,2,4
	1,2,4
	0,3,4
	1,3,4
	2,3,4
*************************************************/
bool next_combination_2(std::vector<int> &combination,int elements_num);

//ʹ��{0,1,...,para_num-1}�������inter_num�����������ļ���
//���ϵ������ȷ��, ��Ϊ2, 3, 4�ĸ���֮��Ϊ2:1:1
/*void CreateRandomInteractions(std::vector<std::set<int> > &interactions,
							  int para_num,
							  int inter_num);*/

bool LoadInteractionsFromFile(const std::string &filename,
							  std::vector<std::set<int> > &interactions,
							  int inter_num);

#endif