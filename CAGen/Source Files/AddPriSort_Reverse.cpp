#include "AddPriSort_Reverse.h"

#include <time.h>
#include <stdlib.h>

namespace CTT
{
	std::vector<CoveringArray::const_iterator> *AddPriSort_Reverse::operator() (
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
			float min_key=-1;
			std::list<float>::iterator cost_it=cost_temp.end();
			std::list<CoveringArray::const_iterator>::iterator min_it=temp.end();

			std::list<float>::iterator iti=cost_temp.begin();
			std::list<CoveringArray::const_iterator>::iterator itj=temp.begin();
			for(;itj!=temp.end();++iti,++itj)
			{
				float key=pri_table.CoverNewCount(**itj,comb_set)/(*iti);
				if(min_key<0 || min_key>key)
				{
					min_key=key;
					cost_it=iti;
					min_it=itj;
				}
				else if((min_key-key<0.000001 && key-min_key<0.000001) && rand()%2==0)
				{
					min_key=key;
					cost_it=iti;
					min_it=itj;
				}
			}

			if(min_it!=temp.end())
			{
				(*p)[i]=*min_it;
				comb_set.ModifyCoverState(**min_it);
				temp.erase(min_it);
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