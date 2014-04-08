#include "DensityFrame.h"

#include <algorithm>
#include <math.h>

namespace CTT
{
	void DensityFrame::InitializeAlgorithm()
	{
		GreedyFrame::InitializeAlgorithm();

		int number=0;
		for(CombSet::const_iterator it=m_uncover_table->begin();
			it!=m_uncover_table->end();++it)
		{
			if(number<it->Size())
				number=it->Size();
		}
		m_max_denominator=number;
	}

	float DensityFrame::CalculateReqDensity(const LocalCombSet &state,
											const std::vector<int> &one_line)
	{
		int k=0;
		std::list<int> locations1,locations2;
		for(std::set<int>::const_iterator it=state.getParaSet().begin();
			it!=state.getParaSet().end();++it,++k)
		{
			if(one_line[*it]!=-1)
			{
				locations1.push_back(k);
				locations2.push_back(*it);
			}
		}

		if(locations1.empty())
		{
			return ((float)(state.getUncoverNumber()))/((float)(m_max_denominator));
		}

		else if(locations1.size()==state.getParaSet().size())
		{
			int j=-1;
			std::vector<int> comb_temp(state.getParaSet().size(),-1);
			for(std::set<int>::const_iterator it=state.getParaSet().begin();
				it!=state.getParaSet().end();++it)
			{
				comb_temp[++j]=one_line[*it];
			}

			if(state.getState(comb_temp)!=0)
				return 1;
			else
				return 0;
		}

		else
		{
			int sum=0;
			std::vector<int> comb_temp;
			for(int i=0;i<state.Size();i++)
			{
				if(state.getState(i)!=0)
				{
					state.getCombination(comb_temp,i);
					std::list<int>::iterator it1=locations1.begin();
					std::list<int>::iterator it2=locations2.begin();
					for(;it1!=locations1.end();++it1,++it2)
					{
						if(comb_temp[*it1]!=one_line[*it2])
							break;
					}

					if(it1==locations1.end())
						++sum;
				}
			}

			int fixed_num=locations1.size();
			int param_num=state.getParaSet().size();
			float actual_exponent=((float)(param_num-fixed_num))/((float)(param_num));
			float actual_denominator=pow(((float)(m_max_denominator)),actual_exponent);
			return ((float)(sum))/actual_denominator;
		}
	}

}	//namespace CTT