#include "DensityRO.h"

#include <algorithm>

namespace CTT
{
	void DensityRO::CreateOneLine(const CoveringArray &array,std::vector<int> &one_line)
	{
		one_line.resize(m_req->getParaNum(),-1);

		std::list<CombSet::iterator> local_state_cache;
		for(CombSet::iterator it=m_uncover_table->begin();
			it!=m_uncover_table->end();++it)
			local_state_cache.push_back(it);

		while(!local_state_cache.empty())
		{
			//Select one coverage requirement that have the greatest density
			CombSet::iterator selected_req_it=
				SelectOneReq(local_state_cache,one_line);

			//Select the values for factors in selected coverage requirement
			FixValues(selected_req_it,one_line);
		}
	}

	CombSet::iterator DensityRO::SelectOneReq(
			std::list<CombSet::iterator> &local_state_cache,
			const std::vector<int> &one_line)
	{
		float max_req_density=-1;
		CombSet::iterator selected_req_it=m_uncover_table->end();
		std::list<CombSet::iterator>::iterator selected_req_it_it=local_state_cache.end();

		//find out the first req that have the greatest density
		std::list<CombSet::iterator>::iterator it=local_state_cache.begin();
		for(;it!=local_state_cache.end();++it)
		{
			float density=CalculateReqDensity(**it,one_line);
			if(density > max_req_density)
			{
				max_req_density=density;
				selected_req_it_it=it;
				selected_req_it=*it;
			}
		}

		local_state_cache.erase(selected_req_it_it);
		return selected_req_it;
	}

	void DensityRO::FixValues(CombSet::iterator &req_it,std::vector<int> &one_line)
	{
		float max_comb_density=-1;
		int selected_comb_index=-1;

		for(int i=0;i<req_it->Size();i++)
		{
			float density=CalculateCombDensity(*req_it,one_line,i);
			if(density > max_comb_density)
			{
				max_comb_density=density;
				selected_comb_index=i;
			}
		}

		req_it->Remove(selected_comb_index);

		std::vector<int> comb_temp;
		req_it->getCombination(comb_temp,selected_comb_index);

		int k=0;
		for(std::set<int>::const_iterator param_it=req_it->getParaSet().begin();
			param_it!=req_it->getParaSet().end();++param_it)
		{
			one_line[*param_it]=comb_temp[k++];
		}
	}

	float DensityRO::CalculateCombDensity(const LocalCombSet &state,
										  const std::vector<int> &one_line,
										  int comb_index)
	{
		float density=0;
		std::vector<int> comb;
		state.getCombination(comb,comb_index);
		std::vector<int> one_line_temp(one_line);

		int k=0;
		for(std::set<int>::const_iterator it=state.getParaSet().begin();
			it!=state.getParaSet().end();++it)
		{
			if(one_line[*it]!=-1 && one_line[*it]!=comb[k])
				return -1;
			else if(one_line[*it]==-1)
				one_line_temp[*it]=comb[k];
			++k;
		}

		for(CombSet::const_iterator it=m_uncover_table->begin();
			it!=m_uncover_table->end();++it)
		{
			std::vector<int> intersect(state.getParaSet().size());
			std::vector<int>::iterator intersect_end=
				set_intersection(state.getParaSet().begin(),state.getParaSet().end(),
								 it->getParaSet().begin(),it->getParaSet().end(),
								 intersect.begin());

			if(intersect.begin()!=intersect_end)
			{
				density+=CalculateReqDensity(*it,one_line_temp);
			}
		}

		return density;
	}

}	//namespace CTT