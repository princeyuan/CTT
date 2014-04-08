#include "IncrementPri.h"

#include "CombSet.h"

namespace CTT
{
	std::vector<CoveringArray::const_iterator> *IncrementPri::operator() (
			const CoveringArray &initial_array,
			const FixedCoverage &req,
			std::list<int> &state)
	{
		std::vector<CoveringArray::const_iterator> *p;
		p=new std::vector<CoveringArray::const_iterator>(initial_array.Size());

		int index=0;
		(*p)[index]=initial_array.begin();
		++index;

		int max_strength=req.getStrength();
		for(int t=2;t<=max_strength;++t)
		{
			FixedCoverage req_temp(req.getAllParameters(),t);
			CombSet t_comb_set(req_temp);

			for(int i=0;i<index;++i)
				t_comb_set.ModifyCoverState(*((*p)[i]));

			while(!t_comb_set.Empty())
			{
				int max_count=-1;
				CoveringArray::const_iterator max_it=initial_array.end();

				for(CoveringArray::const_iterator itt=initial_array.begin();
					itt!=initial_array.end();++itt)
				{
					int count=t_comb_set.CoverNewCount(*itt);
					if(max_count<count)
					{
						max_count=count;
						max_it=itt;
					}
				}

				(*p)[index]=max_it;
				++index;

				t_comb_set.ModifyCoverState(*max_it);
			}

			state.push_back(index);
		}

		return p;
	}
}