#include "WeightedDensity.h"

#include <math.h>

namespace CTT
{
	CoveringArray *WeightedDensity::operator() (const Requirement &req,
												const CombPriTable &pri_table)
	{
		m_pri_table=&pri_table;
		m_req=new MixedCoverage(req);
		m_uncover_table=new CombSet(*m_req);

		CoveringArray *p=run();

		delete m_uncover_table;
		m_uncover_table=NULL;
		delete m_req;
		m_req=NULL;

		return p;
	}

	float WeightedDensity::CalculateReqDensity(const LocalCombSet &state,
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

		const std::vector<float> &pri=m_pri_table->getLocalTable(state.getParaSet());

		if(locations1.empty())
		{
			float count=0;
			for(int i=0;i<state.Size();++i)
			{
				if(state.getState(i)!=0)
					count+=pri[i];
			}
			return (count)/((float)(m_max_denominator));
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
			int index=state.getIndex(comb_temp);

			if(state.getState(index)!=0)
				return pri[index];
			else
				return 0;
		}

		else
		{
			float count=0;
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
					{
						count+=pri[i];
					}
				}
			}

			int fixed_num=locations1.size();
			int para_num=state.getParaSet().size();
			float actual_exponent=((float)(para_num-fixed_num))/((float)(para_num));
			float actual_denominator=pow(((float)(m_max_denominator)),actual_exponent);
			return (count)/actual_denominator;
		}
	}
}