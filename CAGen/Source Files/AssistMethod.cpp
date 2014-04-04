#include "AssistMethod.h"

#include <math.h>
#include <time.h>
#include <algorithm>

int C(int m,int n)
{
	if(m<n)
	{
		return 0;
	}

	if((m==n)||(n==0))
	{
		return 1;
	}

	int high=m;
	for(int i=1;i<=n-1;++i)
	{
		high=high*(m-i);
	}

	int low=n;
	for(int i=n-1;i>=2;--i)
	{
		low=low*i;
	}

	return high/low;
}

int P(int m,int n)
{
	if((m<n)||(m<=0)||(n<0))
	{
		return 0;
	}

	int value=1;
	for(int i=0;i<n;++i)
	{
		value=value*(m-i);
	}

	return value;
}

int toInt(char *str)
{
	int i=0;
	int num=0;
	int len=strlen(str);
	if(str[0]=='-')
		i=1;
	for(;i<len;++i)
	{
		num=num*10;
		num=num+(str[i]-'0');
	}
	if(str[0]=='-')
		return 0-num;
	else
		return num;
}

int toInt(const std::string str)
{
	int i=0;
	int num=0;
	int len=str.size();
	if(str[0]=='-')
		i=1;
	for(;i<len;++i)
	{
		num=num*10;
		num=num+(str[i]-'0');
	}
	if(str[0]=='-')
		return 0-num;
	else
		return num;
}

double toDouble(char *str)
{
	int len=strlen(str);
	int begin=0;
	if(str[0]=='-')
		++begin;

	int current=begin;
	for(;current!=len;++current)
		if(str[current]=='.')
			break;

	if(current!=len)
	{
		std::string str1(str,str+current);
		std::string str2(str+(++current),str+len);
		double a=(double)toInt(str1);
		double b1=(double)toInt(str2);
		double b=b1/pow((float)10,(int)str2.size());
		if(str[0]=='-')
			return 0.0-a-b;
		else
			return a+b;
	}
	else
		return (double)toInt(str);
}

double toDouble(const std::string str)
{
	std::string::const_iterator it_begin=str.begin();
	if(str[0]=='-')
		++it_begin;

	std::string::const_iterator it=it_begin;
	for(;it!=str.end();++it)
		if(*it=='.')
			break;

	if(it!=str.end())
	{
		std::string str1(it_begin,it);
		std::string str2(++it,str.end());
		double a=(double)toInt(str1);
		double b1=(double)toInt(str2);
		double b=b1/pow((float)10,(int)str2.size());
		if(str[0]=='-')
			return 0.0-a-b;
		else
			return a+b;
	}
	else
		return (double)toInt(str);
}

char* getOneNumFromLine(char *str,int &num)
{
	bool positive=true;
	int i=0;
	int length=strlen(str);

loop:
	while ((str[i]<'0' || str[i]>'9') && (str[i]!='-') && (i<length))
	{
		++i;
	}

	if(i==length)
	{
		return NULL;
	}
	else if(str[i]=='-')
	{
		++i;
		positive=false;
	}
	
	std::string token;
	if(str[i]>='0' && str[i]<='9')
	{
		int j=0;
		while((str[i]<='9') && (str[i]>='0') && (i<length))
		{
			token.push_back(str[i++]);
		}
		num=toInt(token);
		if(positive==false)
			num=-num;
	}
	else
	{
		++i;
		goto loop;
	}

 	str=&str[i];
	return str;
}

char* getOneNumFromLine(char *str,double &num)
{
	bool positive=true;
	int i=0;
	int length=strlen(str);

loop:
	while ((str[i]<'0' || str[i]>'9') && (str[i]!='-') && (i<length))
	{
		++i;
	}

	if(i==length)
	{
		return NULL;
	}
	else if(str[i]=='-')
	{
		++i;
		positive=false;
	}
	
	std::string token;
	if(str[i]>='0' && str[i]<='9')
	{
		int j=0;
		while((((str[i]<='9') && (str[i]>='0')) || (str[i])=='.' ) && (i<length))
		{
			token.push_back(str[i++]);
		}
		num=toDouble(token);
		if(positive==false)
			num=0.0-num;
	}
	else
	{
		++i;
		goto loop;
	}

 	str=&str[i];
	return str;
}

void toString(int num,char** str)
{
	if(num==0)
	{
		*str=new char[2];
		(*str)[0]='0';
		(*str)[1]='\0';
	}
	else
	{
		int len=0;
		if(num<0)++len;

		int i=1;
		while(num/i!=0)
		{
			++len;
			i=i*10;
		}

		*str=new char[len+1];
		if(num<0)(*str)[0]='-';
		(*str)[len]='\0';

		int j=0;
		if(num<0)
		{
			++j;
			num=0-num;
		}
		while(j<len)
		{
			i=i/10;
			int a=num/i;
			num=num%i;
			(*str)[j++]='0'+a;
		}
	}
}

char* InterceptString(char* str,char* tag)
{
	int len_str=strlen(str);
	int len_tag=strlen(tag);
	for(int i=0;i<len_str-len_tag+1;++i)
	{
		if(!strncmp(str,tag,len_tag))
		{
			return str+2;
		}
		else
		{
			++str;
		}
	}
	return NULL;
}

bool next_combination_1(std::vector<int> &combination,int element_num)
{
	int strength=combination.size();
	if(strength==0 || element_num==0 || strength>=element_num)
	{
		return false;
	}

	std::vector<int> temp=combination;
	int i=strength;
	int k=i-1;
	for(;i>0;--i)
	{
		k=i-1;
		if((temp[k]+1)/(element_num+i-strength)==0)
		{
			combination[k]=temp[k]+1;
			break;
		}
	}
	if(i==0)
	{
		return false;
	}
	else
	{
		int j=0;
		for(;j<k;++j)
		{
			combination[j]=temp[j];
		}
		for(j=i;j<strength;++j)
		{
			combination[j]=combination[j-1]+1;
		}
		return true;
	}
}

bool next_combination_2(std::vector<int> &combination,int element_num)
{
	int strength=combination.size();
	if(strength==0 || element_num==0 || strength>=element_num)
	{
		return false;
	}

	bool flag=false;
	int i=0;
	for(;i<strength;++i)
	{
		if(combination[i]!=element_num-strength+i)
		{
			flag=true;
			break;
		}
	}

	if(flag)
	{
		for(i=0;i<strength-1;++i)
		{
			if(combination[i]+1!=combination[i+1])
			{
				++combination[i];
				break;
			}
		}
		if(i==strength-1)
			++combination[i];

		for(int j=0;j<i;++j)
			combination[j]=j;
	}

	return flag;
}

bool next_combination(std::vector<int> &combination,
					  int elements_number,
					  bool is_lexical)
{
	if(is_lexical)
		return  next_combination_1(combination,elements_number);
	else
		return  next_combination_2(combination,elements_number);
}

/*void CreateRandomInteractions(std::vector<std::set<int> > &interactions,
							  int para_num,
							  int inter_num)
{
	srand((unsigned)time(NULL));
	do
	{
		std::set<int> inter;

		int seed=rand()%16;
		int strength;
		if(seed<8)
			strength=2;
		else if(seed<12)
			strength=3;
		else
			strength=4;

		do
		{
			int para=rand()%para_num;
			inter.insert(para);
		}
		while(inter.size()!=strength);

		std::vector<std::set<int> >::iterator it=interactions.begin();
		for(;it!=interactions.end();++it)
		{
			if(includes(it->begin(),it->end(),inter.begin(),inter.end()) || 
				includes(inter.begin(),inter.end(),it->begin(),it->end()))
			{
				inter.clear();
				break;
			}
		}

		if(it==interactions.end())
		{
			interactions.push_back(inter);
			std::cout<<interactions.size()<<": ";
			for(std::set<int>::iterator it=inter.begin();it!=inter.end();++it)
				std::cout<<*it<<' ';
			std::cout<<'\n';
		}
	}
	while(interactions.size()!=inter_num);
}*/

bool LoadInteractionsFromFile(const std::string &filename,
							  std::vector<std::set<int> > &interactions,
							  int inter_num)
{
	interactions.clear();
	std::ifstream infile;
	infile.open(filename.c_str(),std::ios::in);

	if(!infile)
	{
		std::cerr<<"Can not open file "<<filename<<"!"<<std::endl;
		return false;
	}

	try
	{
		int value;
		char buffer[1024];
		while(infile.getline(buffer,1024,'\n') && (inter_num--)!=0)
		{
			char *str=buffer;
			std::set<int> temp;
			while(*str!='\0')
			{
				str=getOneNumFromLine(str,value);
				if(str!=NULL)
					temp.insert(value);
				else
					break;
			}
			interactions.push_back(temp);
		}
	}
	catch (...)
	{
		infile.close();
		return false;
	}

	infile.close();
	return true;
}