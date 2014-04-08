#include "TotalPriSort.h"

#include <time.h>
#include <stdlib.h>

namespace CTT
{
	std::vector<CoveringArray::const_iterator> *TotalPriSort::operator() (
			const CoveringArray &initial_array,
			const Requirement &req,
			const CombPriTable &pri_table,
			const std::vector<float> &cost_table)
	{
		srand(time(NULL));
		std::vector<CoveringArray::const_iterator> *p;
		p=new std::vector<CoveringArray::const_iterator>(initial_array.Size());

		int i=0;
		for(CoveringArray::const_iterator it=initial_array.begin();
			it!=initial_array.end();++it,++i)
			(*p)[i]=it;

		std::set<std::set<int> > inter_set;
		req.CreateAllInters(inter_set);
		CombSet comb_set(req.getAllParameters(),inter_set);

		i=0;
		std::vector<float> key(initial_array.Size(),0.0);
		for(CoveringArray::const_iterator it=initial_array.begin();
			it!=initial_array.end();++it,++i)
			key[i]=pri_table.CoverCount(*it,comb_set)/cost_table[i];

		for(i=0;i<initial_array.Size();++i)
		{
			int max_index=i;
			for(int j=i+1;j<initial_array.Size();++j)
			{
				if(key[max_index]<key[j])
					max_index=j;
				else if((key[max_index]-key[j]<0.00001) && rand()%2==0)
					max_index=j;
			}

			if(key[i]<key[max_index])
			{
				float temp1=key[i];
				CoveringArray::const_iterator temp2=(*p)[i];
				key[i]=key[max_index];
				(*p)[i]=(*p)[max_index];
				key[max_index]=temp1;
				(*p)[max_index]=temp2;
			}
		}
			
		return p;
	}
}