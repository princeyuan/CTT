#ifndef COST_APCC_H
#define COST_APCC_H

#include "CombPriTable.h"
#include "CoveringArray.h"

namespace CTT
{
	//Computing APCC value
	class CostAPCC
	{
	public:

		CostAPCC(Requirement &req):m_req(&req)
		{};

	public:

		float operator() (const CoveringArray &tests,
						  const CoveringArray &initial_tests,
						  const CombPriTable &pri_table,
						  const std::vector<float> &cost_table);

		float operator() (const CoveringArray &tests,
						  const CoveringArray &initial_tests,
						  const CombPriTable &pri_table,
						  const std::vector<float> &cost_table,
						  std::vector<float> &addtl_pri,
						  float &sum_pri,float &sum_cost);

		float operator() (const std::vector<CoveringArray::const_iterator> &tests,
						  const CoveringArray &initial_tests,
						  const CombPriTable &pri_table,
						  const std::vector<float> &cost_table);

		float operator() (const std::vector<CoveringArray::const_iterator> &tests,
						  const CoveringArray &initial_tests,
						  const CombPriTable &pri_table,
						  const std::vector<float> &cost_table,
						  std::vector<float> &addtl_pri,
						  float &sum_pri,float &sum_cost);

	private:

		float Measure(const std::vector<CoveringArray::const_iterator> &tests,
					  const CoveringArray &initial_tests,
					  const CombPriTable &pri_table,
					  const std::vector<float> &cost_table,
					  CombSet &cover_state);

		float Measure(const std::vector<CoveringArray::const_iterator> &tests,
					  const CoveringArray &initial_tests,
					  const CombPriTable &pri_table,
					  const std::vector<float> &cost_table,
					  CombSet &cover_state,
					  std::vector<float> &addtl_pri);

		float getSumPri(const CombPriTable &pri_table);

		float getSumCost(const std::vector<float> &cost_table);

		float getActualSumCost(const std::vector<
			CoveringArray::const_iterator> &tests,
			const CoveringArray &initial_tests,
			const std::vector<float> &cost_table);

	private:

		Requirement *m_req;

	};	//class CostAPCC

}	//namespace CTT

#endif