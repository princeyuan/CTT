#include "AssistTesting.h"

void AssistMethodTest()
{
	//getOneNumFromLine_Test();
	//getAllNumFromLine_Test();
	//next_combination_1_Test();
	//next_combination_2_Test();
	//toString_Test();
	//toDouble_Test();

	//GetFixedCoverReq_Test();
	//GetFixedPlusCoverReq_Test();
	//GetMixedCoverReq_Test();

	Partial_CombSet_Test();
}

void getOneNumFromLine_Test()
{
	{
		int num;
		char str1[]="abcd-45";
		char *a1=getOneNumFromLine(str1,num);
		std::cout<<num<<'\n';
		char str2[]="abcd54a";
		char *a2=getOneNumFromLine(str2,num);
		std::cout<<num<<'\n';
		char str3[]="asdfghj";
		char *a3=getOneNumFromLine(str3,num);
		std::cout<<num<<'\n';
		char str4[]="77abcde";
		char *a4=getOneNumFromLine(str4,num);
		std::cout<<num<<'\n';
	}

	{
		double num;
		char str1[]="abcd-4.5";
		char *a1=getOneNumFromLine(str1,num);
		std::cout<<num<<'\n';
		char str2[]="abcd54a";
		char *a2=getOneNumFromLine(str2,num);
		std::cout<<num<<'\n';
		char str3[]="asdfghj";
		char *a3=getOneNumFromLine(str3,num);
		std::cout<<num<<'\n';
		char str4[]="0.77abcde";
		char *a4=getOneNumFromLine(str4,num);
		std::cout<<num<<'\n';
	}
}

void getAllNumFromLine_Test()
{
	char str1[][40]={"asd>>1 : 0 -33 44 5 mdn",
					 "asd>>1: 2, 3 ,-4 ; 5"};
	for(int i=0;i<2;i++)
	{
		std::vector<int> nums;
		getAllNumFromLine(str1[i],nums);
		for(int j=0;j<nums.size();j++)
			std::cout<<nums[j]<<' ';
		std::cout<<'\n';
	}

	char str2[][40]={"asd>>1 : 0 -33 44 5.5 mdn",
					 "asd>>1.0: 2, -3.3 ,-0.44 ; 5"};
	for(i=0;i<2;i++)
	{
		std::vector<double> nums;
		getAllNumFromLine(str2[i],nums);
		for(int j=0;j<nums.size();j++)
			std::cout<<nums[j]<<' ';
		std::cout<<'\n';
	}
}

void next_combination_1_Test()
{
	int array[]={0,1,2};
	std::vector<int> comb(array,array+3);
	int num=0;
	do
	{
		for(int i=0;i<comb.size();i++)
			std::cout<<comb[i]<<' ';
		std::cout<<'\n';
		num++;
	}
	while(next_combination_1(comb,5));
	std::cout<<num<<" combinations!\n";
}

void next_combination_2_Test()
{
	int array[]={0,1,2};
	std::vector<int> comb(array,array+3);
	int num=0;
	do
	{
		for(int i=0;i<comb.size();i++)
			std::cout<<comb[i]<<' ';
		std::cout<<'\n';
		num++;
	}
	while(next_combination_2(comb,5));
	std::cout<<num<<" combinations!\n";
}

void toString_Test()
{
	int num[]={0,1,-1,123,-123,1234567,-1234567};
	for(int i=0;i<7;i++)
	{
		char *str=NULL;
		std::cout<<i+1<<": ";
		toString(num[i],&str);
		std::cout<<str<<'\n';
	}
}

void toDouble_Test()
{
	char str[][10]={"0","1","-1","12345","-12345","0.0","0.234","-0.234","23.45","-23.45"};
	for(int i=0;i<10;i++)
	{
		std::cout<<i+1<<": ";
		std::cout<<toDouble(str[i])<<'\n';
	}
}

void GetFixedCoverReq_Test()
{
	CTT::FixedCoverage *req=CTT::GetFixedCoverReq("Exper/input_test.txt");
	if(req==NULL)
	{
		std::cout<<"There is error in file!\n";
	}
	else
	{
		req->Print();
		delete req;
	}
}

void GetFixedPlusCoverReq_Test()
{
	CTT::FixedPlusCoverage *req=CTT::GetFixedPlusCoverReq("Exper/input_test.txt");
	if(req==NULL)
	{
		std::cout<<"There is error in file!\n";
	}
	else
	{
		req->Print();
		delete req;
	}
}

void GetMixedCoverReq_Test()
{
	CTT::MixedCoverage *req=CTT::GetMixedCoverReq("Exper/input_test.txt");
	if(req==NULL)
	{
		std::cout<<"There is error in file!\n";
	}
	else
	{
		req->Print();
		delete req;
	}
}

void Partial_CombSet_Test()
{
	int a[6]={3,3,3,3,3,3};
	CTT::FixedCoverage req(std::vector<int>(a,a+6),2);
	req.Print();

	CTT::CombSet *p=CreatePartialCombSet(req,2,3);
	p->Print();

	delete p;
}