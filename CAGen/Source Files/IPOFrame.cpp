#include "IPOFrame.h"

#include <time.h>
#include <algorithm>

namespace CTT
{
	CoveringArray* IPOFrame::run()
	{
		CoveringArray *p=new CoveringArray(0,m_req->getParaNum());
		GenerateArray(*p);
		if(m_Is_Need_FixDonotCareValue)
			HandleEmptyPosition(*p);
		return p;
	}

	CoveringArray* IPOFrame::run(const CoveringArray &seed)
	{
		CoveringArray *p=new CoveringArray(seed);
		GenerateArray(*p);
		if(m_Is_Need_FixDonotCareValue)
			HandleEmptyPosition(*p);
		return p;
	}

	void IPOFrame::GenerateArray(CoveringArray &array)
	{
		std::set<int> dealed_factors;
		std::list<int> undealed_factors;
		for(int i=0;i<m_req->getParaNum();i++)
			undealed_factors.push_back(i);

		//Handle the first interaction
		const std::set<int> &first_inter=SelectOneReq();
		//All factors in the first interaction have been added into the set 'dealed_factors',
		//and removed from the set 'undealed_factors' in the function 'HandleOneReq'
		HandleOneReq(first_inter,array,dealed_factors,undealed_factors);

		//Handle other factors one by one
		//The selected factor has been selected into the set 'dealed_factors',
		//and removed from the set 'undealed_factors' in the function 'SelectOneFactor'
		int factor=SelectOneFactor(dealed_factors,undealed_factors);
		while(factor!=-1)
		{
			HandleOneFactor(array,factor,dealed_factors);
			factor=SelectOneFactor(dealed_factors,undealed_factors);
		}
	}

	void IPOFrame::HandleOneReq(const std::set<int> &interaction,
								CoveringArray &array,
								std::set<int> &dealed_factors,
								std::list<int> &undealed_factors)
	{
		LocalCombSet &local_state=m_uncover_table->getLocalState(interaction);

		for(int i=0;i<local_state.Size();i++)
		{
			while(local_state.getState(i)>0)
			{
				std::vector<int> combination;
				local_state.getCombination(combination,i);

				int j=0;
				std::vector<int> one_line(array.Column(),-1);
				for(std::set<int>::const_iterator it=interaction.begin();
					it!=interaction.end();++it)
					one_line[*it]=combination[j++];

				local_state.Remove(i);
				array.Push_Back(one_line);
			}
		}

		dealed_factors.insert(interaction.begin(),interaction.end());
		std::list<int>::iterator range_begin=undealed_factors.begin();
		for(std::set<int>::const_iterator it=dealed_factors.begin();
			it!=dealed_factors.end();++it)
		{
			std::list<int>::iterator del_it=find(range_begin,undealed_factors.end(),*it);
			range_begin=undealed_factors.erase(del_it);
		}
	}

	int IPOFrame::canInsertComb(const std::vector<int> &comb,
								const std::set<int> &paras,
								const std::vector<int> &one_line)
	{
		int k=0;
		int match_degree=0;
		for(std::set<int>::const_iterator it=paras.begin();
			it!=paras.end();++it,++k)
		{
			if(one_line[*it]!=-1 && comb[k]!=one_line[*it])
				return -1;
			else if(comb[k]==one_line[*it])
				++match_degree;
		}

		//返回值表示匹配程度
		return match_degree;
	}

	void IPOFrame::HandleEmptyPosition(CoveringArray &array)
	{
		srand(time(NULL));
		for(CoveringArray::iterator it=array.begin();
			it!=array.end();++it)
		{
			for(int i=0;i<array.Column();++i)
				if((*it)[i]==-1)
					(*it)[i]=rand()%m_req->getParaValue(i);
		}
	}

}	//namespace CTT