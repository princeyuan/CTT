#include "ReqMerge.h"

#include <algorithm>

namespace CTT
{
	void ReqMerge::HandleOtherFactorsInCurrentLine(
			std::vector<int> &current_line,
			const std::set<int> &interaction)
	{
		//Do nothing, let values of other factors be -1
	}

	void ReqMerge::TakeUnion(CoveringArray &dest,const CoveringArray &origin)
	{
		for(CoveringArray::const_iterator it_o=origin.begin();
			it_o!=origin.end();++it_o)
		{
			CoveringArray::iterator it_d=dest.begin();
			for(;it_d!=dest.end();++it_d)
				if(IsSuitableLine(*it_o,*it_d))
					break;

			if(it_d==dest.end())
				dest.Push_Back(*it_o);
			else
			{
				for(int i=0;i<m_req->getParaNum();i++)
				{
					if((*it_d)[i]==-1 && (*it_o)[i]!=-1)
						(*it_d)[i]=(*it_o)[i];
				}
			}
		}
	}
}