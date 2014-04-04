#ifndef TOTAL_PRI_SORT_H
#define TOTAL_PRI_SORT_H

#include "CoveringArray.h"
#include "CombPriTable.h"

namespace CTT
{
	//Total technique in combinatorial test prioritization
	class TotalPriSort
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