#ifndef WEIGHTED_DENSITY_H
#define WEIGHTED_DENSITY_H

#include "DensityFO.h"
#include "CombPriTable.h"

namespace CTT
{
	//Bryce提出的基于Re-Generation的测试用例优先级算法
	//改进自DDA算法
	class WeightedDensity : public DensityFO
	{
	public:

		CoveringArray *operator() (const Requirement &req,
								   const CombPriTable &pri_table);

	private:

		float CalculateReqDensity(const LocalCombSet &state,
								  const std::vector<int> &one_line);

	private:
		
		const CombPriTable *m_pri_table;
	};
}

#endif