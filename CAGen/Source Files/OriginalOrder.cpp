#include "OriginalOrder.h"

namespace CTT
{
	std::vector<CoveringArray::const_iterator> *OriginalOrder::operator() (
			const CoveringArray &initial_array,
			const CombPriTable &pri_table,
			const std::vector<float> &cost_table)
	{
		std::vector<CoveringArray::const_iterator> *p;
		p=new std::vector<CoveringArray::const_iterator>(initial_array.Size());
		int i=0;
		for(CoveringArray::const_iterator it=initial_array.begin();
			it!=initial_array.end();++it)
			(*p)[i++]=it;
		return p;
	}
}