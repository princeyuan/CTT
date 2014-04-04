#include <string>
#include <iostream>

#include "ReqMerge.h"
#include "ReqSelector.h"
#include "ReadInputFile.h"

//VSCAGen algorithm inputfile [-configuration]
int main(int argc, char* argv[])
{
	if(argc<3)return 0;

	//CTT::MixedCoverage *req=CTT::GetMixedCoverReq(argv[2]);
	CTT::FixedCoverage *req=CTT::GetFixedCoverReq(argv[2]);
	req->Print();

	if(stricmp(argv[1],"ReqMerge")==0)
	{
		std::vector<CTT::ReqMerge *> gen(12);
		gen[0]=new CTT::ReqMerge(new CTT::ReqS_MF);
		gen[1]=new CTT::ReqMerge(new CTT::ReqS_LF);
		gen[2]=new CTT::ReqMerge(new CTT::ReqS_MC);
		gen[3]=new CTT::ReqMerge(new CTT::ReqS_LC);
		gen[4]=new CTT::ReqMerge(new CTT::ReqS_MAF);
		gen[5]=new CTT::ReqMerge(new CTT::ReqS_LAF);
		gen[6]=new CTT::ReqMerge(new CTT::ReqS_MAC);
		gen[7]=new CTT::ReqMerge(new CTT::ReqS_LAC);
		gen[8]=new CTT::ReqMerge(new CTT::ReqS_MAFP);
		gen[9]=new CTT::ReqMerge(new CTT::ReqS_LAFP);
		gen[10]=new CTT::ReqMerge(new CTT::ReqS_MACP);
		gen[11]=new CTT::ReqMerge(new CTT::ReqS_LACP);

		int min_size=0;
		CTT::CoveringArray *ca=NULL;
		std::vector<CTT::CoveringArray *> ca_temp(12);

		for(int i=0;i<12;++i)
		{
			ca_temp[i]=(*gen[i])(*req);
			if(min_size==0 || min_size>ca_temp[i]->Size())
			{
				min_size=ca_temp[i]->Size();
				ca=ca_temp[i];
			}
		}
		ca->Print();

		for(int i=0;i<12;++i)
		{
			delete gen[i];
			delete ca_temp[i];
		}
	}
	else if(strcmp(argv[1],"ParaOrder")==0)
	{
		std::cout<<'2';
	}
	else if(strcmp(argv[1],"Density1")==0)
	{
		std::cout<<'3';
	}
	else if(strcmp(argv[1],"Density2")==0)
	{
		std::cout<<'4';
	}
	else
	{
		std::cout<<'5';
	}
}