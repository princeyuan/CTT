#include "CombPriTable.h"

namespace CTT
{
	CombPriTable::CombPriTable(const Requirement &req)
	{
		std::set<std::set<int> > inter_set;
		req.CreateAllInters(inter_set);

		for(std::set<std::set<int> >::const_iterator it=inter_set.begin();
			it!=inter_set.end();++it)
		{
			int number=1;
			for(std::set<int>::const_iterator iti=it->begin();
				iti!=it->end();++iti)
				number*=req.getParaValue(*iti);
			m_table.insert(std::pair<std::set<int>,std::vector<float> >
				(*it,std::vector<float>(number,1.0)));
		}
	}

	float CombPriTable::CoverCount(const std::vector<int> &test,
								   const CombSet &comb_set) const
	{
		float count=0.0;

		CombSet::const_iterator iti=comb_set.begin();
		for(const_iterator itj=begin();itj!=end();++itj,++iti)
		{
			int i=0;
			std::vector<int> comb(itj->first.size(),-1);
			for(std::set<int>::const_iterator itk=itj->first.begin();
				itk!=itj->first.end();++itk)
				comb[i++]=test[*itk];
			int index=iti->getIndex(comb);
			count+=(itj->second)[index];
		}

		return count;
	}

	float CombPriTable::CoverNewCount(const std::vector<int> &test,
									  const CombSet &comb_set) const
	{
		float count=0.0;

		CombSet::const_iterator iti=comb_set.begin();
		for(const_iterator itj=begin();itj!=end();++itj,++iti)
		{
			int i=0;
			std::vector<int> comb(itj->first.size(),-1);
			for(std::set<int>::const_iterator itk=itj->first.begin();
				itk!=itj->first.end();++itk)
				comb[i++]=test[*itk];
			int index=iti->getIndex(comb);
			if(iti->getState(index)>0)
				count+=(itj->second)[index];
		}

		return count;
	}

	std::vector<float> &CombPriTable::getLocalTable(const std::set<int> &para_set)
	{
		return m_table.find(para_set)->second;
	}

	const std::vector<float> &CombPriTable::getLocalTable(const std::set<int> &para_set) const
	{
		return m_table.find(para_set)->second;
	}
}