#include "MixedCoverage.h"

#include <algorithm>
#include "AssistMethod.h"

namespace CTT
{
	MixedCoverage::MixedCoverage(const std::vector<int> &paravalues,
								 const std::set<std::set<int> > &interactions)
		:Requirement(paravalues),m_interactions(interactions)
	{
		HandleIllegal(CheckLegal());
		CreateIndependentFactors();
	}

	MixedCoverage::MixedCoverage(const std::vector<int> &paravalues,
								 const std::vector<std::set<int> > &interactions)
		:Requirement(paravalues),m_interactions(interactions.begin(),interactions.end())
	{
		HandleIllegal(CheckLegal());
		CreateIndependentFactors();
	}

	MixedCoverage::MixedCoverage(const Requirement &req)
		:Requirement(req.getAllParameters())
	{
		req.CreateAllInters(m_interactions);
	}

	void MixedCoverage::CreateAllInters(std::set<std::set<int> > &inters) const
	{
		inters.clear();
		inters.insert(m_interactions.begin(),m_interactions.end());
	}

	int MixedCoverage::CheckLegal() const
	{
		//element of sub-collection must be legal parameter
		for(std::set<std::set<int> >::const_iterator it1=m_interactions.begin();
			it1!=m_interactions.end();++it1)
			for(std::set<int>::const_iterator it2=it1->begin();
				it2!=it1->end();++it2)
				if(*it2<0 || *it2>=getParaNum())
					return 1;

		//cardinality of sub-collection must be greater than 1
		for(std::set<std::set<int> >::const_iterator it1=m_interactions.begin();
			it1!=m_interactions.end();++it1)
			if(it1->size()<=1)
				return 2;

		//sub-collection should not be subset of other sub-collection
		for(std::set<std::set<int> >::const_iterator it1=m_interactions.begin();
			it1!=m_interactions.end();++it1)
		{
			std::set<std::set<int> >::const_iterator it_temp=it1;
			for(std::set<std::set<int> >::const_iterator it2=++it_temp;
				it2!=m_interactions.end();++it2)
				if(includes(it1->begin(),it1->end(),it2->begin(),it2->end()) && 
					includes(it2->begin(),it2->end(),it1->begin(),it1->end()))
					return 3;
		}

		return 0;
	}

	void MixedCoverage::HandleIllegal(int error_code) const
	{
		switch(error_code)
		{
		case 1:{
			std::cerr<<"Error when create MixedCoverage: element of sub-collection is illegal!\n";
			throw "Illegal Requirement";break;
			   };
		case 2:{
			std::cerr<<"Error when create MixedCoverage: cardinality of sub-collections is less than 2!\n";
			throw "Illegal Requirement";break;
			   };
		case 3:{
			std::cerr<<"Error when create MixedCoverage: sub-collection is subset of other!\n";
			throw "Illegal Requirement";break;
			   };
		default:
			break;
		}
	}

	void MixedCoverage::CreateIndependentFactors()
	{
		std::vector<int> all_factors(getParaNum());
		for(int i=0;i<getParaNum();++i)
			all_factors[i]=i;

		int index[2]={0,1};
		std::vector<int> related_factors[2]={std::vector<int>(getParaNum(),-1),
											 std::vector<int>(getParaNum(),-1)};
		std::vector<int>::iterator related_end[2]={related_factors[0].begin(),
												   related_factors[1].begin()};
		for(const_iterator it=begin();it!=end();++it)
		{
			related_end[index[1]]=set_union(it->begin(),it->end(),
											related_factors[index[0]].begin(),
											related_end[index[0]],
											related_factors[index[1]].begin());
			index[0]=(index[0]==0?1:0);
			index[1]=(index[1]==0?1:0);
		}

		std::vector<int> independent_factors(getParaNum(),-1);
		std::vector<int>::iterator independent_end=
			set_difference(all_factors.begin(),all_factors.end(),
						   related_factors[index[0]].begin(),
						   related_end[index[0]],
						   independent_factors.begin());

		m_independent.insert(independent_factors.begin(),independent_end);
	}

	void MixedCoverage::Print(std::ostream &out) const
	{
		Requirement::Print(out);

		int i=0;
		out<<"Interaction Relationship:\n";
		for(std::set<std::set<int> >::const_iterator it1=m_interactions.begin();
			it1!=m_interactions.end();++it1)
		{
			out<<"interaction"<<++i<<": {";
			std::set<int>::const_iterator it2=it1->begin();
			out<<*(it2++);
			for(;it2!=it1->end();++it2)
				out<<", "<<*it2;
			out<<'}'<<std::endl;
		}

		if(!m_independent.empty())
		{
			out<<"Independent parameters Index:\n";
			std::set<int>::const_iterator it_i=m_independent.begin();
			out<<*(it_i++);
			for(;it_i!=m_independent.end();++it_i)
				out<<", "<<*it_i;
			out<<std::endl;
		}
	}

}	//namespace CTT