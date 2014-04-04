#ifndef PRIORITY_EXPER_ASSIST_H
#define PRIORITY_EXPER_ASSIST_H

#include <math.h>
#include <time.h>
#include <fstream>
#include "FixedCoverage.h"
#include "CombPriTable.h"

CTT::CombPriTable *SetPriTable(const CTT::FixedCoverage &req,int type)
{
	switch(type)
	{
	case 1:{//Equal
		CTT::CombPriTable *p=new CTT::CombPriTable(req);

		for(CTT::CombPriTable::iterator it=p->begin();it!=p->end();++it)
		{
			for(int i=0;i<it->second.size();++i)
				(it->second)[i]=1.0;
		}

		return p;
		   };
	case 2:{//Random
		CTT::CombPriTable *p=new CTT::CombPriTable(req);

		srand(time(NULL));
		for(CTT::CombPriTable::iterator it=p->begin();it!=p->end();++it)
		{
			for(int i=0;i<it->second.size();++i)
				(it->second)[i]=((rand()%10)+1)/10.0;
		}

		return p;
		   };
	case 3:{//Half
		CTT::CombPriTable *p=new CTT::CombPriTable(req);

		std::vector<std::vector<float> > value_pri(req.getParaNum());
		for(int i=0;i<req.getParaNum();++i)
		{
			value_pri[i].resize(req.getParaValue(i),0.1);

			int not_visit_num=req.getParaValue(i);
			std::vector<int> not_visit(req.getParaValue(i));
			for(int j=0;j<req.getParaValue(i);++j)
				not_visit[j]=j;

			srand(time(NULL));
			for(int j=0;j<req.getParaValue(i)/2;++j)
			{
				int index=rand()%not_visit_num;
				value_pri[i][not_visit[index]]=0.9;
				not_visit[index]=not_visit[--not_visit_num];
			}
		}

		std::set<std::set<int> > inter_set;
		req.CreateAllInters(inter_set);
		CTT::CombSet comb_set(req.getAllParameters(),inter_set);

		CTT::CombSet::const_iterator iti=comb_set.begin();
		for(CTT::CombPriTable::iterator itj=p->begin();itj!=p->end();++itj,++iti)
		{
			int strength=req.getStrength();
			std::vector<int> comb(strength,-1);
			std::set<int>::const_iterator itk=itj->first.begin();
			for(int j=0;j<itj->second.size();++j,++itk)
			{
				iti->getCombination(comb,j);
				float pri=1.0;
				for(int k=0;k<strength;++k)
				{
					pri*=value_pri[*itk][comb[k]];
				}
			}
		}

		return p;
		   };
	case 4:{//Reciprocal
		CTT::CombPriTable *p=new CTT::CombPriTable(req);

		for(CTT::CombPriTable::iterator it=p->begin();it!=p->end();++it)
		{
			float value=1.0;
			for(std::set<int>::const_iterator itk=it->first.begin();
				itk!=it->first.end();++itk)
				value*=1.0/(req.getParaValue(*itk)*req.getParaValue(*itk));
			for(int i=0;i<it->second.size();++i)
				(it->second)[i]=value;
		}

		return p;
		   };
	};
}

std::vector<float> *SetCostTable(int size,int type)
{
	switch(type)
	{
	case 1:{//Equal
		return new std::vector<float>(size,1.0);
		   };
	case 2:{//Random
		std::vector<float> *p=new std::vector<float>(size);
		srand(time(NULL));
		for(int i=0;i<size;++i)
			(*p)[i]=((rand()%10)+1)/10.0;
		return p;
		   };
	case 3:{//Mozilla
		std::vector<float> *p=new std::vector<float>(size,1.0);
		std::vector<int> not_visit(size);
		for(int i=0;i<size;++i)not_visit[i]=i;
		int not_visit_num=size;
		float frequent[]={0.01,0.02,0.1,0.87};
		float costs[]={2.0,3.0,4.0,1.0};
		srand(time(NULL));
		for(int i=0;i<3;++i)
		{
			for(int j=0;j<ceil(size*frequent[i]);++j)
			{
				int index=rand()%not_visit_num;
				(*p)[not_visit[index]]=costs[i];
				not_visit[index]=not_visit[--not_visit_num];
			}
		}
		return p;
		   };
	case 4:{//QTB
		std::vector<float> *p=new std::vector<float>(size,1.0);
		std::vector<int> not_visit(size);
		for(int i=0;i<size;++i)not_visit[i]=i;
		int not_visit_num=size;
		srand(time(NULL));
		for(int i=0;i<ceil(size*0.12);++i)
		{
			int index=rand()%not_visit_num;
			(*p)[not_visit[index]]=10.0;
			not_visit[index]=not_visit[--not_visit_num];
		}
		return p;
		   };
	};
}

void PrintExperResult1(float value[],int pri_type,int cost_type,int algo_type)
{
	char ch1='1'+algo_type;
	std::string name1(&ch1,(&ch1)+1);
	std::string name("result/");
	name+=name1;name+=".txt";

	char pri_name[]="ERHP";
	char cost_name[]="ERMQ";

	std::ofstream outfile;
	outfile.open(name.c_str(),std::ios::app);

	for(int m=0;m<3;++m)
		outfile<<value[m]<<'\t';
	outfile<<pri_name[pri_type-1]<<'+'<<cost_name[cost_type-1];
	outfile<<'\n';

	outfile.close();
}

void PrintExperResult2(float value[],int pri_type,int cost_type)
{
	char pri_name[]="ERHP";
	char cost_name[]="ERMQ";

	std::ofstream outfile;
	outfile.open("result\\result.txt",std::ios::app);

	for(int m=0;m<3;++m)
		outfile<<value[m]<<'\t';
	outfile<<pri_name[pri_type-1]<<'+'<<cost_name[cost_type-1];
	outfile<<'\n';

	outfile.close();
}

void PrintMemoResult(const std::vector<std::vector<float> > &addtl_pri)
{
	std::ofstream outfile;
	outfile.open("result\\memo.txt",std::ios::app);

	for(int i=0;i<3;++i)
	{
		for(int j=0;j<addtl_pri[i].size();++j)
		{
			if(j!=addtl_pri[i].size()-1)
				outfile<<addtl_pri[i][j]<<", ";
			else
				outfile<<addtl_pri[i][j]<<'\n';
		}
	}

	for(int j=0;j<addtl_pri[0].size();++j)
	{
		if(j!=addtl_pri[0].size()-1)
			outfile<<j+1<<", ";
		else
			outfile<<j+1<<"\n\n";
	}

	outfile.close();
}

#endif