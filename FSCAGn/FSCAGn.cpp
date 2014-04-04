#include "AssistMethod.h"
#include "ReadInputFile.h"

//FSCAGen algorithm parameters|inputfile [-configuration]
int main(int argc, char* argv[])
{
	if(argc<3)return 0;

	CTT::FixedCoverage *req=NULL;
	if(1<=argv[2][0] && argv[2][0]<=9)
	{
		char *tag=argv[2];
		int value,number;
		std::vector<int> &paras
		while(true)
		{
			tag=getOneNumFromLine(tag,value);
			if(*tag!='\0' && *tag!='^' && *tag!='*')
				return false;

			if(*tag!='^')
			{
				number=1;
			}
			else
			{
				tag=getOneNumFromLine(++tag,number);
				if(*tag!='\0' && *tag!='^' && *tag!='*')
					return false;
			}
			
			for(int i=0;i<number;++i)
				paras.push_back(value);

			if(*tag!='*')
				break;
			else
				++tag;
		}

	}
	else
	{
		req=CTT::GetFixedCoverReq(argv[2]);
	}
	return 0;
}

