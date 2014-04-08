#include "GenAlgotesting.h"

void DensityRO_Test()
{
	int a[5]={3,3,3,3};
	/*std::vector<std::set<int> > interactions;
	int s1[2]={0,1};interactions.push_back(std::set<int>(s1,s1+2));
	int s2[2]={1,2};interactions.push_back(std::set<int>(s2,s2+2));
	int s3[2]={0,2};interactions.push_back(std::set<int>(s3,s3+2));
	CTT::MixedCoverage req(std::vector<int>(a,a+5),interactions);*/
	CTT::FixedCoverage req(std::vector<int>(a,a+4),2);
	req.Print();

	CTT::DensityRO gen;
	CTT::CoveringArray *array=gen(req);

	array->Print();
	delete array;
}

void DensityFO_Test()
{
	int a[6]={2,3,2,2,3,3};
	/*std::vector<std::set<int> > interactions;
	int s1[2]={0,1};interactions.push_back(std::set<int>(s1,s1+2));
	int s2[2]={1,2};interactions.push_back(std::set<int>(s2,s2+2));
	int s3[2]={0,2};interactions.push_back(std::set<int>(s3,s3+2));
	CTT::MixedCoverage req(std::vector<int>(a,a+5),interactions);*/
	CTT::FixedCoverage req(std::vector<int>(a,a+6),2);
	req.Print();

	CTT::DensityFO gen;
	CTT::CoveringArray *array=gen(req);

	array->Print();
	delete array;
}

void MyUnion_Test()
{
	int a[5]={5,5,5,5,5};
	CTT::FixedCoverage req(std::vector<int>(a,a+5),2);

	CTT::MyUnion gen;
	CTT::CoveringArray *array=gen(req);

	array->Print();
	delete array;
}

void ReqMerge_Test()
{
	int p[10]={4,4,4,4,4,4,4,4,4,4};
	std::vector<int> paras(p,p+10);
	std::map<std::set<int>,int> subsets;
	int s1[4]={1,2,3,4};std::set<int> subset1(s1,s1+4);
	subsets.insert(std::pair<std::set<int>,int>(subset1,3));
	int s2[4]={5,6,7,8};std::set<int> subset2(s2,s2+4);
	subsets.insert(std::pair<std::set<int>,int>(subset2,3));
	CTT::FixedPlusCoverage req(paras,2,subsets);
	req.Print();

	CTT::ReqMerge gen(new CTT::ReqS_MAF);
	CTT::CoveringArray *array=gen(req);

	array->Print();
	delete array;
}

void ParaOrder_Test()
{
	int a[15]={3,3,3,3,3,3};
	std::vector<std::set<int> > interactions;
	int s1[2]={0,1};interactions.push_back(std::set<int>(s1,s1+2));
	int s2[2]={1,2};interactions.push_back(std::set<int>(s2,s2+2));
	int s3[2]={0,2};interactions.push_back(std::set<int>(s3,s3+2));
	CTT::MixedCoverage req(std::vector<int>(a,a+5),interactions);
	req.Print();
	
	CTT::ParaOrder gen(new CTT::ReqS_MC,new CTT::ParaS_MC);
	CTT::CoveringArray *array=gen(req);

	array->Print();
	delete array;
}

void NeighborGenerator_Test()
{
	int p[10]={4,4,4,4,4,4,4,4,4,4};
	std::vector<int> paras(p,p+10);
	std::map<std::set<int>,int> subsets;
	int s1[4]={1,2,3,4};std::set<int> subset1(s1,s1+4);
	subsets.insert(std::pair<std::set<int>,int>(subset1,3));
	int s2[4]={5,6,7,8};std::set<int> subset2(s2,s2+4);
	subsets.insert(std::pair<std::set<int>,int>(subset2,3));
	CTT::NeighborPlusCoverage req(paras,2,subsets);
	req.Print();

	CTT::NeighborGenerator gen;
	CTT::CoveringArray *array=gen(req);
	array->Print();
	delete array;
}

void SSTSearch_Test()
{
	int p[]={3,3,3,3,3,3};
	std::vector<int> paras(p,p+5);
	CTT::FixedCoverage req(paras,3);
	CTT::SSTSearch gen(new CTT::PathS_Forward);
	CTT::CoveringArray *array=gen(req);
	array->Print();
	std::cout<<gen.GetActualCount()<<'/'<<gen.GetTheoryCount()<<std::endl;
	delete array;
	std::vector<int> paras2(p,p+4);
	CTT::FixedCoverage req2(paras2,3);
	array=gen(req2);
	array->Print();
}

void TwoLevel_Test()
{
	int p[16]={2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};
	std::vector<int> paras(p,p+11);
	CTT::FixedCoverage req(paras,2);
	CTT::TwoLevel gen;
	CTT::CoveringArray *array=gen(req);
	array->Print();
	delete array;
}

void BestGreedy_Test()
{
	int a[15]={3,3,3,3,3,3,3,3,3,3,3,3,3,3,3};
	std::vector<std::set<int> > interactions;
	int s1[2]={0,1};interactions.push_back(std::set<int>(s1,s1+2));
	int s2[2]={1,2};interactions.push_back(std::set<int>(s2,s2+2));
	int s3[2]={0,2};interactions.push_back(std::set<int>(s3,s3+2));
	CTT::MixedCoverage req(std::vector<int>(a,a+5),interactions);
	req.Print();
	
	CTT::BestGreedy gen;
	CTT::CoveringArray *array=gen(req);

	array->Print();
	delete array;
}

void WeightedDensity_Test()
{
	int a[15]={3,3,3,3,3,3,3,3,3,3,3,3,3,3,3};
	std::vector<std::set<int> > interactions;
	int s1[2]={0,1};interactions.push_back(std::set<int>(s1,s1+2));
	int s2[2]={1,2};interactions.push_back(std::set<int>(s2,s2+2));
	int s3[2]={0,2};interactions.push_back(std::set<int>(s3,s3+2));
	CTT::MixedCoverage req(std::vector<int>(a,a+5),interactions);
	req.Print();

	CTT::CombPriTable pri_table(req);
	
	CTT::WeightedDensity gen;
	CTT::CoveringArray *array=gen(req,pri_table);

	array->Print();
	delete array;
}

void PCAGen_Test()
{
	int a[6]={2,2,2,2,2,2};
	int t=2;
	int d=2;

	CTT::FixedCoverage req(std::vector<int>(a,a+6),t+d);
	req.Print();

	CTT::CombSet *comb_set=CreatePartialCombSet(req,t,d);
	comb_set->Print();

	CTT::CoveringArray *array=NULL;

	CTT::BestGreedy gen1;
	array=gen1(req,*comb_set);
	array->Print();
	delete array;

	CTT::DensityRO gen2;
	array=gen2(req,*comb_set);
	array->Print();
	delete array;

	CTT::DensityFO gen3;
	array=gen3(req,*comb_set);
	array->Print();
	delete array;

	CTT::MyUnion gen4;
	array=gen4(req,*comb_set);
	array->Print();
	delete array;

	CTT::ReqMerge gen5(new CTT::ReqS_MC);
	array=gen5(req,*comb_set);
	array->Print();
	delete array;

	CTT::ParaOrder gen6(new CTT::ReqS_MC,new CTT::ParaS_MC);
	array=gen6(req,*comb_set);
	array->Print();
	delete array;

	delete comb_set;
	
}