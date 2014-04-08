#include "NeighborPlusCoverage.h"
#include <algorithm>

namespace CTT
{
	NeighborPlusCoverage::NeighborPlusCoverage(const NeighborCoverage &req)
		:NeighborCoverage(req.getAllParameters(),req.getStrength())
	{}

	NeighborPlusCoverage::NeighborPlusCoverage(const std::vector<int> &paravalues,int strength,
											   const std::map<std::set<int>,int> subsets)
		:NeighborCoverage(paravalues,strength),m_subsets(subsets)
	{
		HandleIllegal(CheckLegal());
	}

	void NeighborPlusCoverage::CreateAllInters(std::set<std::set<int> > &inters) const
	{
		inters.clear();

		std::set<std::set<int> > big_inters;
		for(NeighborPlusCoverage::const_iterator it_1=begin();
			it_1!=end();++it_1)
		{
			std::set<int>::const_iterator it_begin=it_1->first.begin();
			std::set<int>::const_iterator it_end=it_1->first.begin();
			for(int i=0;i<it_1->second;i++)
				++it_end;

			for(;it_end!=it_1->first.end();++it_begin,++it_end)
				big_inters.insert(std::set<int>(it_begin,it_end));
		}

		int upper_bound=getParaNum()-getStrength();
		for(int i=0;i<=upper_bound;i++)
		{
			std::set<int> temp;
			for(int j=0;j<getStrength();j++)
				temp.insert(i+j);

			std::set<std::set<int> >::const_iterator it_2=big_inters.begin();
			for(;it_2!=big_inters.end();++it_2)
			{
				if(includes(it_2->begin(),it_2->end(),temp.begin(),temp.end()))
					break;
			}
			if(big_inters.end()==it_2)
				inters.insert(temp);
		}

		inters.insert(big_inters.begin(),big_inters.end());
	}

	void NeighborPlusCoverage::Print(std::ostream &out) const
	{
		NeighborCoverage::Print(out);

		int i=0;
		out<<"Sub-sets:\n";
		for(std::map<std::set<int>,int>::const_iterator it1=m_subsets.begin();
			it1!=m_subsets.end();++it1)
		{
			out<<"neighbor set "<<++i<<": {";
			std::set<int>::const_iterator it2=it1->first.begin();
			out<<*(it2++);
			for(;it2!=it1->first.end();++it2)
				out<<", "<<*it2;
			out<<"}\tneighbor strength: "<<it1->second<<std::endl;
		}
	}

	int NeighborPlusCoverage::CheckLegal() const
	{
		//element of subsets must be legal parameter
		for(std::map<std::set<int>,int>::const_iterator it1=m_subsets.begin();
			it1!=m_subsets.end();++it1)
			for(std::set<int>::const_iterator it2=it1->first.begin();
				it2!=it1->first.end();++it2)
				if(*it2<0 || *it2>=getParaNum())
					return 1;

		//cardinality of subsets must be bigger than basic strength
		for(std::map<std::set<int>,int>::const_iterator it1=m_subsets.begin();
			it1!=m_subsets.end();++it1)
			if(it1->first.size()<=m_strength)
				return 2;

		//strength of subsets must be equal or smaller than cardinality of subsets
		for(std::map<std::set<int>,int>::const_iterator it1=m_subsets.begin();
			it1!=m_subsets.end();++it1)
			if(it1->first.size()<it1->second)
				return 3;

		//strength of subsets must be bigger than basic strength
		for(std::map<std::set<int>,int>::const_iterator it1=m_subsets.begin();
			it1!=m_subsets.end();++it1)
			if(it1->second<=m_strength)
				return 4;

		return 0;
	}

	void NeighborPlusCoverage::HandleIllegal(int error_code) const
	{
		switch(error_code)
		{
		case 1:{
			std::cerr<<"Error when create NeighborPlusCoverage: element of subset is illegal!\n";
			throw "Illegal Requirement";break;
			   };
		case 2:{
			std::cerr<<"Error when create NeighborPlusCoverage: cardinality of subset is less than basic strength!\n";
			throw "Illegal Requirement";break;
			   };
		case 3:{
			std::cerr<<"Error when create NeighborPlusCoverage: strength of subset is bigger than cardinality of subset!\n";
			throw "Illegal Requirement";break;
			   };
		case 4:{
			std::cerr<<"Error when create NeighborPlusCoverage: strength of subset is not bigger than basic strength!\n";
			throw "Illegal Requirement";break;
			   }
		default:
			break;
		}
	}

}	//namespace CTT