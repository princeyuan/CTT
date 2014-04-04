#ifndef INCREMENT_PRI_H
#define INCREMENT_PRI_H

#include "CoveringArray.h"
#include "FixedCoverage.h"

namespace CTT
{
	//按照力度增量策略对已有高维组合测试用例集中的测试用例进行排序
	class IncrementPri
	{
	public:

		std::vector<CoveringArray::const_iterator> *operator() (
			const CoveringArray &initial_array,
			const FixedCoverage &req,
			std::list<int> &state);
	};
}

#endif