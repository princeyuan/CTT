#ifndef FIXED_COVERAGE_H
#define FIXED_COVERAGE_H

#include <set>
#include <iostream>
#include "Requirement.h"

namespace CTT
{
	class FixedCoverage : public Requirement
	{
	public:

		FixedCoverage(const std::vector<int> &paravalues,int strength);

	public:

		void CreateAllInters(std::set<std::set<int> > &inters) const;

		std::string getReqType() const { return "FixedCoverage"; };

	public:

		int getStrength() const {return m_strength;};

		void Print(std::ostream &out=std::cout) const;

	private:

		int CheckLegal() const;

		void HandleIllegal(int error_code) const;

	protected:

		int m_strength;

	};	//class FixedCoverage

}	//namespace CTT

#endif