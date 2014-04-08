#include "AddtlPriSort.h"

#include <time.h>
#include <stdlib.h>

namespace CTT
{
	std::vector<CoveringArray::const_iterator> *AddtlPriSort::operator() (
			const CoveringArray &initial_array,
			const Requirement &req,
			const CombPriTable &pri_table,
			const std::vector<float> &cost_table)
	{
		srand(time(NULL));
		std::vector<CoveringArray::const_iterator> *p;
		p=new std::vector<CoveringArray::const_iterator>(initial_array.Size());

		std::list<CoveringArray::const_iterator> temp;
		for(CoveringArray::const_iterator it=initial_array.begin();
			it!=initial_array.end();++it)
			temp.push_back(it);

		std::list<float> cost_temp;
		for(std::vector<float>::const_iterator it=cost_table.begin();
			it!=cost_table.end();++it)
			cost_temp.push_back(*it);

		std::set<std::set<int> > inter_set;
		req.CreateAllInters(inter_set);
		CombSet comb_set(req.getAllParameters(),inter_set);

		for(int i=0;i<p->size();++i)
		{
			float max_key=0.0;
			std::list<float>::iterator cost_it=cost_temp.end();
			std::list<CoveringArray::const_iterator>::iterator max_it=temp.end();

			std::list<float>::iterator iti=cost_temp.begin();
			std::list<CoveringArray::const_iterator>::iterator itj=temp.begin();
			for(;itj!=temp.end();++iti,++itj)
			{
				float key=pri_table.CoverNewCount(**itj,comb_set)/(*iti);
				if(max_key<key)
				{
					max_key=key;
					cost_it=iti;
					max_it=itj;
				}
				else if((max_key-key<0.00001) && rand()%2==0)
				{
					max_key=key;
					cost_it=iti;
					max_it=itj;
				}
			}

			if(max_it!=temp.end())
			{
				(*p)[i]=*max_it;
				comb_set.ModifyCoverState(**max_it);
				temp.erase(max_it);
				cost_temp.erase(cost_it);
			}
			else
			{
				for(itj=temp.begin();itj!=temp.end();++itj)
					(*p)[i++]=*itj;
				break;
			}
		}

		return p;
	}
}