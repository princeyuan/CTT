#ifndef GEN_ALGO_EXPER_H
#define GEN_ALGO_EXPER_H

#include <time.h>
#include <stdlib.h>
#include "AssistMethod.h"
#include "GenAlgoExperAssist.h"
#include "ReadInputFile.h"

#include "DensityRO.h"
#include "DensityFO.h"
#include "MyUnion.h"
#include "ReqMerge.h"
#include "ParaOrder.h"
#include "SSTSEarch.h"
#include "BestGreedy.h"

#include "CreatePartialCombSet.h"

void PCA_Run()
{
	/*int a[6]={2,2,2,2,2,2};
	int t=2;
	int d=2;

	CTT::FixedCoverage *req=new CTT::FixedCoverage(std::vector<int>(a,a+6),t+d);*/
	

	CTT::FixedCoverage *req=CTT::GetFixedCoverReq("input/input.txt");
	int t=2;
	int d=1;
	req->Print();

	CTT::CombSet *comb_set=CreatePartialCombSet(*req,t,d);
	//comb_set->Print();

	CTT::CoveringArray *array=NULL;
	CTT::CoveringArray *array_full=NULL;

	/*CTT::BestGreedy gen1;
	array_full=gen1(*req);
	array=gen1(*req,*comb_set);
	std::cout<<"BestGreedy: "<<array->Size()<<'/'<<array_full->Size()<<'\n';
	delete array;*/
	//不能处理全覆盖

	CTT::DensityRO gen2;
	array_full=gen2(*req);
	array=gen2(*req,*comb_set);
	std::cout<<"DensityRO: "<<array->Size()<<'/'<<array_full->Size()<<'\n';
	delete array;

	CTT::DensityFO gen3;
	array_full=gen3(*req);
	array=gen3(*req,*comb_set);
	std::cout<<"DensityFO: "<<array->Size()<<'/'<<array_full->Size()<<'\n';
	delete array;

	CTT::MyUnion gen4;
	array_full=gen4(*req);
	array=gen4(*req,*comb_set);
	std::cout<<"MyUnion: "<<array->Size()<<'/'<<array_full->Size()<<'\n';
	delete array;

	/*CTT::ParaOrder gen6(new CTT::ReqS_MC,new CTT::ParaS_MC);
	array=gen6(*req,*comb_set);
	std::cout<<"ParaOrder: "<<array->Size()<<'\n';
	delete array;*/
	//有问题，应该是选择因素时的问题

	delete comb_set;
	delete req;
}

//分析组合覆盖的速度
void GetCoverSpeed(const CTT::Requirement &req,const CTT::CoveringArray &array,std::vector<int> &cover_speed)
{
	CTT::CombSet *comb_table=new CTT::CombSet(*(new CTT::MixedCoverage(req)));
	cover_speed.resize(array.Size()+1,0);

	int i=0;
	for(CTT::CoveringArray::const_iterator it=array.begin();
		it!=array.end();++it,++i)
	{
		cover_speed[i]=comb_table->CoverNewCount(*it);
		comb_table->ModifyCoverState(*it);
		cover_speed[array.Size()]+=cover_speed[i];
	}
}

void Hybrid_exper()
{
	CTT::FixedCoverage *req=CTT::GetFixedCoverReq("input/input.txt");
	req->Print();

	CTT::DensityFO gen_fo;
	CTT::DensityRO gen_ro;
	CTT::BestGreedy gen_g;

	CTT::CoveringArray *array1=gen_fo(*req);array1->Print();
	CTT::CoveringArray *array2=gen_ro(*req);array2->Print();
	CTT::CoveringArray *array3=gen_g(*req); array3->Print();

	std::vector<int> speed1,speed2,speed3;
	GetCoverSpeed(*req,*array1,speed1);delete req;req=CTT::GetFixedCoverReq("input/input.txt");
	GetCoverSpeed(*req,*array2,speed2);delete req;req=CTT::GetFixedCoverReq("input/input.txt");
	GetCoverSpeed(*req,*array3,speed3);

	int sum=0;
	for(int i=0;i<speed1.size()-1;++i)
	{
		sum+=speed1[i];
		std::cout<<sum<<'\t';
	}
	std::cout<<"\n\n";

	sum=0;
	for(int i=0;i<speed2.size()-1;++i)
	{
		sum+=speed2[i];
		std::cout<<sum<<'\t';
	}
	std::cout<<"\n\n";

	sum=0;
	for(int i=0;i<speed3.size()-1;++i)
	{
		sum+=speed3[i];
		std::cout<<sum<<'\t';
	}
	std::cout<<"\n\n";
}

void VStrength_exper()
{
	int p[2][10]={{3,3,3,3,3,3,3,3,3,3},{2,2,2,3,3,3,4,4,4,5}};
	std::vector<int> paras[2];
	for(int j=0;j<2;j++)
		for(int i=0;i<10;i++)
			paras[j].push_back(p[j][i]);

	std::vector<std::set<int> > inters;
	LoadInteractionsFromFile("input/interactions.txt",inters,60);

	CTT::ParaOrder gen1(new CTT::ReqS_MC,new CTT::ParaS_MAC);
	CTT::ReqMerge gen2(new CTT::ReqS_LC);

	int round=1;
	for(int j=0;j<2;j++)
	{
		for(int i=0;i<paras[j].size();i++)
			std::cout<<paras[j][i]<<' ';
		std::cout<<'\n';

		for(int i=1;i<=6;i++)
		{
			CTT::MixedCoverage req(paras[j],
				std::vector<std::set<int> >(inters.begin(),inters.begin()+(i*10)));

			CTT::CoveringArray *array1;
			long start_1=time(0);
			for(int k=0;k<round;k++)
				array1=gen1(req);
			long end_1=time(0);
			std::cout<<array1->Size()<<'\t'<<(end_1-start_1)/round;
			delete array1;

			std::cout<<"\t|\t";

			CTT::CoveringArray *array2;
			long start_2=time(0);
			for(int k=0;k<round;k++)
				array2=gen2(req);
			long end_2=time(0);
			std::cout<<array2->Size()<<'\t'<<(end_2-start_2)/round;
			delete array2;

			std::cout<<'\n';
		}
	}
}

void Nway_exper()
{
	CTT::FixedCoverage *req=CTT::GetFixedCoverReq("input/input2.txt");
	req->Print();

	//CTT::DensityFO gen;
	CTT::ParaOrder gen(new CTT::ReqS_MC,new CTT::ParaS_MAC);

	long start=time(0);
	CTT::CoveringArray *array=gen(*req);
	long end=time(0);
	std::cout<<array->Size()<<'\t'<<end-start<<'\n';
	array->Print(std::cout);
	delete array;

	delete req;
}

void NS_VStrength_exper(char* filename)
{
	CTT::FixedPlusCoverage *req=CTT::GetFixedPlusCoverReq(filename);
	req->Print();

	CTT::BestGreedy gen;

	long start=time(0);
	CTT::CoveringArray *array=gen(*req);
	long end=time(0);
	std::cout<<array->Size()<<'\t'<<end-start<<'\n';
	delete array;

	delete req;
}

void SSTSearch_exper()
{
	CTT::FixedCoverage *req=CTT::GetFixedCoverReq("input/input.txt");
	req->Print();
	CTT::SSTSearch gen1(new CTT::PathS_Greater,0);
	CTT::SSTSearch gen2(new CTT::PathS_Greater,1);
	CTT::CoveringArray *array1=gen1(*req);
	CTT::CoveringArray *array2=gen2(*req);
	std::cout<<array1->Size()<<'\n';
	std::cout<<gen1.GetActualVisitedNodeCount()<<'\n';
	//array1->Print();
	delete array1;
	std::cout<<array2->Size()<<'\n';
	std::cout<<gen2.GetActualVisitedNodeCount()<<'\n';
	//array2->Print();
	delete array2;
}

//比较ReqMerge中的各种策略
void ReqMerge_exper()
{
	int p[2][10]={{3,3,3,3,3,3,3,3,3,3},{2,2,2,3,3,3,4,4,4,5}};
	std::vector<int> paras[2];
	for(int j=0;j<2;j++)
		for(int i=0;i<10;i++)
			paras[j].push_back(p[j][i]);

	std::vector<std::set<int> > inters;
	LoadInteractionsFromFile("input/interactions1.txt",inters,60);

	std::vector<CTT::ReqMerge *> gen(12);
	gen[0]=new CTT::ReqMerge(new CTT::ReqS_MF);gen[1]=new CTT::ReqMerge(new CTT::ReqS_LF);
	gen[2]=new CTT::ReqMerge(new CTT::ReqS_MC);gen[3]=new CTT::ReqMerge(new CTT::ReqS_LC);
	gen[4]=new CTT::ReqMerge(new CTT::ReqS_MAF);gen[5]=new CTT::ReqMerge(new CTT::ReqS_LAF);
	gen[6]=new CTT::ReqMerge(new CTT::ReqS_MAC);gen[7]=new CTT::ReqMerge(new CTT::ReqS_LAC);
	gen[8]=new CTT::ReqMerge(new CTT::ReqS_MAFP);gen[9]=new CTT::ReqMerge(new CTT::ReqS_LAFP);
	gen[10]=new CTT::ReqMerge(new CTT::ReqS_MACP);gen[11]=new CTT::ReqMerge(new CTT::ReqS_LACP);

	for(int j=0;j<2;++j)
	{
		for(int i=0;i<paras[j].size();i++)
			std::cout<<paras[j][i]<<' ';
		std::cout<<'\n';

		for(int i=0;i<12;++i)
		{	
			for(int k=1;k<=6;++k)
			{
				CTT::MixedCoverage req(paras[j],
					std::vector<std::set<int> >(inters.begin(),inters.begin()+(k*10)));

				CTT::CoveringArray *array=(*gen[i])(req);
				std::cout<<array->Size()<<'\t';
				delete array;
			}
			std::cout<<std::endl;
		}
	}

	for(int i=0;i<12;++i)delete gen[i];
}

//比较ParaOrder中的各种策略
void ParaOrder_exper()
{
	int p[2][10]={{3,3,3,3,3,3,3,3,3,3},{2,2,2,3,3,3,4,4,4,5}};
	std::vector<int> paras[2];
	for(int j=0;j<2;j++)
		for(int i=0;i<10;i++)
			paras[j].push_back(p[j][i]);

	std::vector<std::set<int> > inters;
	LoadInteractionsFromFile("input/interactions2.txt",inters,60);

	std::vector<CTT::ParaOrder *> gen(14);
	CTT::ReqSelector *rs=new CTT::ReqS_MC;
	gen[0]=new CTT::ParaOrder(rs,new CTT::ParaS_MV);
	gen[1]=new CTT::ParaOrder(rs,new CTT::ParaS_LV);
	gen[2]=new CTT::ParaOrder(rs,new CTT::ParaS_MR);
	gen[3]=new CTT::ParaOrder(rs,new CTT::ParaS_LR);
	gen[4]=new CTT::ParaOrder(rs,new CTT::ParaS_MF);
	gen[5]=new CTT::ParaOrder(rs,new CTT::ParaS_LF);
	gen[6]=new CTT::ParaOrder(rs,new CTT::ParaS_MC);
	gen[7]=new CTT::ParaOrder(rs,new CTT::ParaS_LC);
	gen[8]=new CTT::ParaOrder(rs,new CTT::ParaS_MAR);
	gen[9]=new CTT::ParaOrder(rs,new CTT::ParaS_LAR);
	gen[10]=new CTT::ParaOrder(rs,new CTT::ParaS_MAF);
	gen[11]=new CTT::ParaOrder(rs,new CTT::ParaS_LAF);
	gen[12]=new CTT::ParaOrder(rs,new CTT::ParaS_MAC);
	gen[13]=new CTT::ParaOrder(rs,new CTT::ParaS_LAC);

	for(int j=0;j<2;++j)
	{
		for(int i=0;i<paras[j].size();i++)
			std::cout<<paras[j][i]<<' ';
		std::cout<<'\n';

		for(int i=0;i<14;++i)
		{
			for(int k=1;k<=6;++k)
			{
				CTT::MixedCoverage req(paras[j],
					std::vector<std::set<int> >(inters.begin(),inters.begin()+(k*10)));

				CTT::CoveringArray *array=(*gen[i])(req);
				std::cout<<array->Size()<<'\t';
				delete array;
			}
			std::cout<<std::endl;
		}
	}

	for(int i=0;i<12;++i)delete gen[i];
}

#endif