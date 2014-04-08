#ifndef WEIGHTED_DENSITY_H
#define WEIGHTED_DENSITY_H

#include "DensityFO.h"
#include "CombPriTable.h"

namespace CTT
{
	//Bryce����Ļ���Re-Generation�Ĳ����������ȼ��㷨
	//�Ľ���DDA�㷨
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