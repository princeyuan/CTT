#include "MyUnion.h"

#include <time.h>

namespace CTT
{
	void MyUnion::InitializeAlgorithm()
	{
		UnionFrame::InitializeAlgorithm();

		srand(time(NULL));
	}

	void MyUnion::HandleOtherFactorsInCurrentLine(
			std::vector<int> &current_line,
			const std::set<int> &interaction)
	{
		//let values of other factors to be random
		for(int i=0;i<m_req->getParaNum();i++)
		{
			if(current_line[i]==-1)
				current_line[i]=rand()%m_req->getParaValue(i);
		}
	}

	void MyUnion::TakeUnion(CoveringArray &dest,const CoveringArray &origin)
	{
		for(CoveringArray::const_iterator it_o=origin.begin();
			it_o!=origin.end();++it_o)
		{
			CoveringArray::const_iterator it_d=dest.begin();
			for(;it_d!=dest.end();++it_d)
				if(IsSuitableLine(*it_o,*it_d))
					break;

			if(it_d==dest.end())
				dest.Push_Back(*it_o);
		}
	}

}	//namespace CTT