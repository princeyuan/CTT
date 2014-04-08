#include "CostAPCC.h"

namespace CTT
{
	float CostAPCC::operator() (
		const CoveringArray &tests,
		const CoveringArray &initial_tests,
		const CombPriTable &pri_table,
		const std::vector<float> &cost_table)
	{
		int i=0;
		std::vector<CoveringArray::const_iterator> temp(tests.Size());
		for(CoveringArray::const_iterator it=tests.begin();
			it!=tests.end();++it,++i)
			temp[i]=it;

		return operator() (temp,initial_tests,pri_table,cost_table);
	}

	float CostAPCC::operator() (
		const CoveringArray &tests,
		const CoveringArray &initial_tests,
		const CombPriTable &pri_table,
		const std::vector<float> &cost_table,
		std::vector<float> &addtl_pri,
		float &sum_pri,float &sum_cost)
	{
		int i=0;
		std::vector<CoveringArray::const_iterator> temp(tests.Size());
		for(CoveringArray::const_iterator it=tests.begin();
			it!=tests.end();++it,++i)
			temp[i]=it;

		return operator() (temp,initial_tests,pri_table,
						   cost_table,addtl_pri,sum_pri,sum_cost);
	}

	float CostAPCC::operator() (
		const std::vector<CoveringArray::const_iterator> &tests,
		const CoveringArray &initial_tests,
		const CombPriTable &pri_table,
		const std::vector<float> &cost_table)
	{
		std::set<std::set<int> > inter_set;
		m_req->CreateAllInters(inter_set);
		CombSet cover_state(m_req->getAllParameters(),inter_set);

		float sum_pri=getSumPri(pri_table);
		float sum_cost=getActualSumCost(tests,initial_tests,cost_table);
		float number=
			Measure(tests,initial_tests,pri_table,cost_table,cover_state);
		return number/(sum_pri*sum_cost);
	}

	float CostAPCC::operator() (
		const std::vector<CoveringArray::const_iterator> &tests,
		const CoveringArray &initial_tests,
		const CombPriTable &pri_table,
		const std::vector<float> &cost_table,
		std::vector<float> &addtl_pri,
		float &sum_pri,float &sum_cost)
	{
		addtl_pri.resize(tests.size()+1,0.0);

		std::set<std::set<int> > inter_set;
		m_req->CreateAllInters(inter_set);
		CombSet cover_state(m_req->getAllParameters(),inter_set);

		sum_pri=getSumPri(pri_table);
		sum_cost=getActualSumCost(tests,initial_tests,cost_table);
		float number=
			Measure(tests,initial_tests,pri_table,cost_table,cover_state,addtl_pri);
		return number/(sum_pri*sum_cost);
	}

	float CostAPCC::Measure(
		const std::vector<CoveringArray::const_iterator> &tests,
		const CoveringArray &initial_tests,
		const CombPriTable &pri_table,
		const std::vector<float> &cost_table,
		CombSet &cover_state)
	{
		float number=0.0;
		float pri=0.0;

		std::vector<CoveringArray::const_iterator>::const_iterator iti=tests.begin();
		for(;iti!=tests.end();++iti)
		{
			int index=0;
			for(CoveringArray::const_iterator itj=initial_tests.begin();
				itj!=initial_tests.end();++itj,++index)
				if(*iti==itj)
					break;

			number+=(pri*cost_table[index]);
			pri+=pri_table.CoverNewCount(**iti,cover_state);
			cover_state.ModifyCoverState(**iti);
		}

		return number;
	}

	float CostAPCC::Measure(
		const std::vector<CoveringArray::const_iterator> &tests,
		const CoveringArray &initial_tests,
		const CombPriTable &pri_table,
		const std::vector<float> &cost_table,
		CombSet &cover_state,
		std::vector<float> &addtl_pri)
	{
		float number=0.0;
		float pri=0.0;

		int i=0;
		std::vector<CoveringArray::const_iterator>::const_iterator iti=tests.begin();
		for(;iti!=tests.end();++iti,++i)
		{
			int index=0;
			for(CoveringArray::const_iterator itj=initial_tests.begin();
				itj!=initial_tests.end();++itj,++index)
				if(*iti==itj)
					break;

			addtl_pri[i]=pri;
			number+=(pri*cost_table[index]);
			pri+=pri_table.CoverNewCount(**iti,cover_state);
			cover_state.ModifyCoverState(**iti);
		}
		addtl_pri[i]=pri;

		return number;
	}

	float CostAPCC::getSumPri(const CombPriTable &pri_table)
	{
		float sum_pri=0.0;
		for(CombPriTable::const_iterator iti=pri_table.begin();
			iti!=pri_table.end();++iti)
			for(std::vector<float>::const_iterator itj=iti->second.begin();
				itj!=iti->second.end();++itj)
				sum_pri+=*itj;
		return sum_pri;
	}

	float CostAPCC::getSumCost(const std::vector<float> &cost_table)
	{
		float sum_cost=0.0;
		for(std::vector<float>::const_iterator it=cost_table.begin();
			it!=cost_table.end();++it)
			sum_cost+=*it;
		return sum_cost;
	}

	float CostAPCC::getActualSumCost(
		const std::vector<CoveringArray::const_iterator> &tests,
		const CoveringArray &initial_tests,
		const std::vector<float> &cost_table)
	{
		float sum_cost=0.0;
		std::vector<CoveringArray::const_iterator>::const_iterator iti=tests.begin();
		for(;iti!=tests.end();++iti)
		{
			int index=0;
			for(CoveringArray::const_iterator itj=initial_tests.begin();
				itj!=initial_tests.end();++itj,++index)
				if(*iti==itj)
					break;

			sum_cost+=cost_table[index];
		}
		return sum_cost;
	}
}