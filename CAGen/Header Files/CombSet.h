#ifndef COMB_SET_H
#define COMB_SET_H

#include <set>
#include <iostream>
#include "LocalCombSet.h"
#include "MixedCoverage.h"

namespace CTT
{
	class CombSet
	{
	public:

		CombSet(const MixedCoverage &req);

		CombSet(const std::vector<int> &parameters,
				const std::set<std::set<int> > &inter_set);

		CombSet(const CombSet &comb_set);

		CombSet(const CombSet &comb_set,
				const std::set<std::set<int> > &partial_inter_set);

	public:

		int Size() const {return m_collections.size();};

		bool Empty() const;

		int CoverNewCount(const std::vector<int> &test) const;

		void ModifyCoverState(const std::vector<int> &test);

		bool isCover(CoveringArray::const_iterator it_begin,
					 CoveringArray::const_iterator it_end) const;

		float CoverPercent(CoveringArray::const_iterator it_begin,
						   CoveringArray::const_iterator it_end,
						   int &required_number,
						   int &covered_number) const;

		LocalCombSet &getLocalState(const std::set<int> &param_set);
		const LocalCombSet &getLocalState(const std::set<int> &param_set) const;

		void Print(std::ostream &out=std::cout) const;

	public:

		typedef std::set<LocalCombSet>::iterator iterator;
		iterator begin() {return m_collections.begin();};
		iterator end()   {return m_collections.end();};

		typedef std::set<LocalCombSet>::const_iterator const_iterator;
		const_iterator begin() const {return m_collections.begin();};
		const_iterator end() const   {return m_collections.end();};

	protected:

		std::set<LocalCombSet> m_collections;

	};	//class CombSet

}	//namespace CTT

#endif