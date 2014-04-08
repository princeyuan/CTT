#ifndef MIXED_COVERAGE_H
#define MIXED_COVERAGE_H

#include <set>
#include <iostream>
#include "FixedCoverage.h"
#include "FixedPlusCoverage.h"

namespace CTT
{
	class MixedCoverage : public Requirement
	{
	public:

		MixedCoverage(const std::vector<int> &paravalues,
					  const std::set<std::set<int> > &interactions);

		MixedCoverage(const std::vector<int> &paravalues,
					  const std::vector<std::set<int> > &interactions);

		MixedCoverage(const Requirement &req);

	public:

		void CreateAllInters(std::set<std::set<int> > &inters) const;

		std::string getReqType() const { return "MixedCoverage"; };

	public:

		int getInteractionNum() const {return m_interactions.size();};

		const std::set<int> &getIndependentFactors() const {return m_independent;};

		void Print(std::ostream &out=std::cout) const;

	public:

		typedef std::set<std::set<int> >::iterator iterator;
		iterator begin() {return m_interactions.begin();};
		iterator end()   {return m_interactions.end();};

		typedef std::set<std::set<int> >::const_iterator const_iterator;
		const_iterator begin() const {return m_interactions.begin();};
		const_iterator end()   const {return m_interactions.end();};

	private:

		int CheckLegal() const;

		void HandleIllegal(int error_code) const;

		void CreateIndependentFactors();

	private:

		std::set<std::set<int> > m_interactions;

		std::set<int> m_independent;

	};	//class MixedCoverage

}	//namespace CTT

#endif