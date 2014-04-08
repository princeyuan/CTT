#include "NeighborCoverage.h"

namespace CTT
{
	NeighborCoverage::NeighborCoverage(const std::vector<int> &paravalues,int strength)
		:Requirement(paravalues),m_strength(strength)
	{
		HandleIllegal(CheckLegal());
	}

	void NeighborCoverage::CreateAllInters(std::set<std::set<int> > &inters) const
	{
		inters.clear();

		int upper_bound=getParaNum()-getStrength();
		for(int i=0;i<=upper_bound;i++)
		{
			std::set<int> temp;
			for(int j=0;j<getStrength();j++)
				temp.insert(i+j);
			inters.insert(temp);
		}
	}

	int NeighborCoverage::getStrength() const
	{
		return m_strength;
	}

	int NeighborCoverage::CheckLegal() const
	{
		//strength of n-way coverage must bigger than 1 (>=2)
		if(m_strength<2)
			return 1;
		//strength must be less or equal than number of parameters
		if(m_strength>=m_paravalues.size())
			return 2;

		return 0;
	}

	void NeighborCoverage::HandleIllegal(int error_code) const
	{
		switch(error_code)
		{
		case 1:
			{
			std::cerr<<"Error when create NeighborCoverage: strength is less than 2!\n";
			throw "Illegal Coverage Strength";
			break;
			};
		case 2:
			{
			std::cerr<<"Error when create NeighborCoverage: strength is equal to or bigger than parameter number!\n";
			throw "Illegal Coverage Strength";
			break;
			};
		default:
			break;
		}
	}

	void NeighborCoverage::Print(std::ostream &out) const
	{
		Requirement::Print(out);
		out<<"The global neighbor factors cover strength is:\t"<<m_strength<<'\n';
	}

}	//namespace CTT