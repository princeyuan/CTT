#include "Requirement.h"

namespace CTT
{
	Requirement::Requirement(const std::vector<int> &paravalues)
		:m_paravalues(paravalues)
	{
		HandleIllegal(CheckLegal());
	}

	int Requirement::CheckLegal() const
	{
		//all parameters must have more than 0 values (>=1) 
		for(std::vector<int>::const_iterator it=m_paravalues.begin();
			it!=m_paravalues.end();++it)
			if(*it<1)
				return 1;

		return 0;
	}

	void Requirement::HandleIllegal(int error_code) const
	{
		switch(error_code)
		{
		case 1:{
			std::cerr<<"Error when create Requirement: a parameter has less than 1 value!\n";
			throw "Illegal Coverage Strength";
			   }
		default:
			break;
		}
	}

	bool Requirement::IsFixedLevel() const
	{
		std::vector<int>::const_iterator it=m_paravalues.begin();
		for(;it!=m_paravalues.end();++it)
			if(*it!=*(m_paravalues.begin()))
				break;

		if(it!=m_paravalues.end())
			return false;
		else
			return true;
	}

	void Requirement::Print(std::ostream &out) const
	{
		out<<"Parameter Values:\n";
		int i=0;
		std::vector<int>::const_iterator it=m_paravalues.begin();
		out<<"|f"<<i++<<"|="<<*(it++);
		for(;it!=m_paravalues.end();++it)
			out<<'\t'<<"|f"<<i++<<"|="<<*it;
		out<<std::endl;
	}

}	//namespace CTT