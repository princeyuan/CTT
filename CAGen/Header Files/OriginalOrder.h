#ifndef ORIGINAL_ORDER_H
#define ORIGINAL_ORDER_H

#include "CoveringArray.h"
#include "CombPriTable.h"

namespace CTT
{
	class OriginalOrder
	{
	public:
		
		std::vector<CoveringArray::const_iterator> *operator() (
			const CoveringArray &initial_array,
			const CombPriTable &pri_table,
			const std::vector<float> &cost_table);
	};
}

#endif