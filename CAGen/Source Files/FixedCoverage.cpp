#include "FixedCoverage.h"
#include "AssistMethod.h"

namespace CTT
{
	FixedCoverage::FixedCoverage(const std::vector<int> &paravalues,int strength)
		:Requirement(paravalues),m_strength(strength)
	{
		HandleIllegal(CheckLegal());
	}

	void FixedCoverage::CreateAllInters(std::set<std::set<int> > &inters) const
	{
		inters.clear();

		if(m_strength>1)
		{
			std::vector<int> temp(m_strength,0);
			for(int i=0;i<m_strength;++i)
				temp[i]=i;
			inters.insert(std::set<int>(temp.begin(),temp.end()));

			while(next_combination(temp,m_paravalues.size()))
				inters.insert(std::set<int>(temp.begin(),temp.end()));
		}
	}

	int FixedCoverage::CheckLegal() const
	{
		//strength of n-way coverage must greater than 0 (>=1)
		if(m_strength<1)
			return 1;
		//strength must be less than or equal to number of parameters
		if(m_strength>m_paravalues.size())
			return 2;

		return 0;
	}

	void FixedCoverage::HandleIllegal(int error_code) const
	{
		switch(error_code)
		{
		case 1:
			{
			std::cerr<<"Error when create FixedCoverage: strength is less than 1!\n";
			throw "Illegal Coverage Strength";
			break;
			};
		case 2:
			{
			std::cerr<<"Error when create FixedCoverage: strength is equal to or greater than parameter number!\n";
			throw "Illegal Coverage Strength";
			break;
			};
		default:
			break;
		}
	}

	void FixedCoverage::Print(std::ostream &out) const
	{
		Requirement::Print(out);
		out<<"The global cover strength is:\t"<<m_strength<<'\n';
	}

}	//namespace CTT