#ifndef ADDTL_PRI_SORT_REVERSE_H
#define ADDTL_PRI_SORT_REVERSE_H

#include "CoveringArray.h"
#include "CombPriTable.h"

namespace CTT
{
	//Additional technique in combinatorial test prioritization
	//But select bad test cases firstly
	class AddPriSort_Reverse
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