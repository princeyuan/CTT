#ifndef NEIGHBOR_PLUS_COVERAGE_H
#define NEIGHBOR_PLUS_COVERAGE_H

#include <set>
#include <map>
#include "NeighborCoverage.h"

namespace CTT
{
	class NeighborPlusCoverage : public NeighborCoverage
	{
	public:

		NeighborPlusCoverage(const NeighborCoverage &req);

		NeighborPlusCoverage(const std::vector<int> &paravalues,int strength,
							 const std::map<std::set<int>,int> subsets);

	public:

		void CreateAllInters(std::set<std::set<int> > &inters) const;

		std::string getReqType() const { return "NeighborPlusCoverage"; };

	public:

		int getSubsetNum() const {return m_subsets.size();};

		typedef std::map<std::set<int>,int>::iterator iterator;
		iterator begin() {return m_subsets.begin();};
		iterator end()   {return m_subsets.end();};

		typedef std::map<std::set<int>,int>::const_iterator const_iterator;
		const_iterator begin() const {return m_subsets.begin();};
		const_iterator end()   const {return m_subsets.end();};

		void Print(std::ostream &out=std::cout) const;

	protected:

		int CheckLegal() const;

		void HandleIllegal(int error_code) const;

	protected:

		std::map<std::set<int>,int> m_subsets;

	};	//class NeighborPlusCoverage

}	//namespace CTT

#endif