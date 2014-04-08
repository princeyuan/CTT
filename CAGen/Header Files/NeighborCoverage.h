#ifndef NEIGHBOR_COVERAGE_H
#define NEIGHBOR_COVERAGE_H

#include <set>
#include <iostream>
#include "Requirement.h"

namespace CTT
{
	class NeighborCoverage : public Requirement
	{
	public:

		NeighborCoverage(const std::vector<int> &paravalues,int strength);

	public:

		void CreateAllInters(std::set<std::set<int> > &inters) const;

		std::string getReqType() const { return "NeighborCoverage"; };

	public:

		int getStrength() const;

		void Print(std::ostream &out=std::cout) const;

	protected:

		int CheckLegal() const;

		void HandleIllegal(int error_code) const;

	protected:

		int m_strength;

	};	//class NeighborCoverage

}	//namespace CTT

#endif