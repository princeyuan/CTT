#include "CombSet.h"

namespace CTT
{
	CombSet::CombSet(const MixedCoverage &req)
	{
		for(MixedCoverage::const_iterator it=req.begin();it!=req.end();++it)
		{
			m_collections.insert(LocalCombSet(*it,req));
		}
	}

	CombSet::CombSet(const std::vector<int> &parameters,
					 const std::set<std::set<int> > &inter_set)
	{
		for(std::set<std::set<int> >::const_iterator it=inter_set.begin();
			it!=inter_set.end();++it)
		{
			m_collections.insert(LocalCombSet(*it,parameters));
		}
	}

	CombSet::CombSet(const CombSet &comb_set)
	{
		for(CombSet::const_iterator it=comb_set.begin();it!=comb_set.end();++it)
		{
			m_collections.insert(*it);
		}
	}

	CombSet::CombSet(const CombSet &comb_set,
					 const std::set<std::set<int> > &partial_inter_set)
	{
		for(std::set<std::set<int> >::const_iterator it=partial_inter_set.begin();
			it!=partial_inter_set.end();++it)
		{
			m_collections.insert(comb_set.getLocalState(*it));
		}
	}

	bool CombSet::Empty() const
	{
		for(const_iterator it=m_collections.begin();
			it!=m_collections.end();++it)
			if(!(it->Empty()))
				return false;
		return true;
	}

	int CombSet::CoverNewCount(const std::vector<int> &test) const
	{
		int count=0;
		for(CombSet::const_iterator it=begin();it!=end();++it)
		{
			std::vector<int> combination(it->getParaSet().size(),-1);

			int i=-1;
			std::set<int>::const_iterator itp=it->getParaSet().begin();
			for(;itp!=it->getParaSet().end();++itp)
				combination[++i]=test[*itp];

			 
			int index=it->getIndex(combination);
			if(index!=-1)
				if(it->getState(index)>0)
					++count;
		}
		return count;
	}

	void CombSet::ModifyCoverState(const std::vector<int> &test)
	{
		for(iterator it=m_collections.begin();
			it!=m_collections.end();++it)
		{
			it->ModifyCoverState(test);
		}
	}

	bool CombSet::isCover(CoveringArray::const_iterator it_begin,
						  CoveringArray::const_iterator it_end) const
	{
		for(const_iterator it=m_collections.begin();
			it!=m_collections.end();++it)
		{
			if(!(it->isCover(it_begin,it_end)))
				return false;
		}
		return true;
	}

	LocalCombSet &CombSet::getLocalState(const std::set<int> &para_set)
	{
		for(iterator it=begin();it!=end();++it)
			if(it->getParaSet()==para_set)
				return *it;
		std::cerr<<"No interaction among given parameters!"<<std::endl;
		throw "Out of Range";
	}

	const LocalCombSet &CombSet::getLocalState(
		const std::set<int> &para_set) const
	{
		for(const_iterator it=begin();it!=end();++it)
			if(it->getParaSet()==para_set)
				return *it;
		std::cerr<<"No interaction among given parameters!"<<std::endl;
		throw "Out of Range";
	}

	void CombSet::Print(std::ostream &out) const
	{
		int index=0;

		for(const_iterator it=m_collections.begin();
			it!=m_collections.end();++it)
		{
			std::cout<<"The "<<++index<<"-th interaction: ";
			it->Print(out);
			out<<std::endl;
		}
	}

}	//namespace CTT