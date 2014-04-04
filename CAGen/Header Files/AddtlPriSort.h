#ifndef ADDTL_PRI_SORT_H
#define ADDTL_PRI_SORT_H

#include "CoveringArray.h"
#include "CombPriTable.h"

namespace CTT
{
	//Additional technique in combinatorial test prioritization
	class AddtlPriSort
	{
	public:
		
		std::vector<CoveringArray::const_iterator> *operator() (
			const CoveringArray &initial_array,
			const Requirement &req,
			const CombPriTable &pri_table,
			const std::vector<float> &cost_table);
	};
}

#endif