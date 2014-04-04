#ifndef FIXED_PLUS_COVERAGE_H
#define FIXED_PLUS_COVERAGE_H

#include <set>
#include <map>
#include "FixedCoverage.h"

namespace CTT
{
	class FixedPlusCoverage : public FixedCoverage
	{
	public:

		FixedPlusCoverage(const std::vector<int> &paravalues,int strength,
						  const std::map<std::set<int>,int> subsets);

		FixedPlusCoverage(const FixedCoverage &req);

	public:

		void CreateAllInters(std::set<std::set<int> > &inters) const;

		std::string getReqType() const { return "FixedPlusCoverage"; };

	public:

		int getSubsetNum() const {return m_subsets.size();};

		void Print(std::ostream &out=std::cout) const;

	public:

		typedef std::map<std::set<int>,int>::iterator iterator;
		iterator begin() {return m_subsets.begin();};
		iterator end()   {return m_subsets.end();};

		typedef std::map<std::set<int>,int>::const_iterator const_iterator;
		const_iterator begin() const {return m_subsets.begin();};
		const_iterator end()   const {return m_subsets.end();};

	private:

		int CheckLegal() const;

		void HandleIllegal(int error_code) const;

	private:

		std::map<std::set<int>,int> m_subsets;

	};	//class FixedCoverage

}	//namespace CTT

#endif