#include "UnionFrame.h"

#include <time.h>
#include <algorithm>

namespace CTT
{
	CoveringArray* UnionFrame::run()
	{
		CoveringArray *p=new CoveringArray(0,m_req->getParaNum());

		InitializeAlgorithm();
		GenerateArray(*p);
		HandleEmptyPosition(*p);

		return p;
	}

	bool UnionFrame::IsSuitableLine(const std::vector<int> &line1,
									const std::vector<int> &line2)
	{
		for(int i=0;i<line1.size();++i)
		{
			if(line1[i]!=line2[i] && line1[i]!=-1 && line2[i]!=-1)
				return false;
		}
		return true;
	}

	void UnionFrame::GenerateArray(CoveringArray &array)
	{
		std::set<int> dealed_factors;
		std::list<CombSet::iterator> local_state_cache;
		for(CombSet::iterator it=m_uncover_table->begin();
			it!=m_uncover_table->end();++it)
			local_state_cache.push_back(it);

		while(!local_state_cache.empty())
		{
			CoveringArray array_temp(0,m_req->getParaNum());

			std::pair<CombSet::iterator,bool> selected=
				(*m_req_selector)(local_state_cache,dealed_factors,*m_req);
			HandleOneReq(array_temp,selected.first->getParaSet());
			TakeUnion(array,array_temp);
		}
	}

	void UnionFrame::HandleOneReq(CoveringArray &array,
								  const std::set<int> &interaction)
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

				HandleOtherFactorsInCurrentLine(one_line,interaction);

				local_state.Remove(i);
				array.Push_Back(one_line);
			}
		}
	}

	void UnionFrame::HandleEmptyPosition(CoveringArray &array)
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