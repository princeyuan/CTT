#include "FixedPlusCoverage.h"
#include <algorithm>
#include "AssistMethod.h"

namespace CTT
{
	FixedPlusCoverage::FixedPlusCoverage(const std::vector<int> &paravalues,int strength,
										 const std::map<std::set<int>,int> subsets)
		:FixedCoverage(paravalues,strength),m_subsets(subsets)
	{
		HandleIllegal(CheckLegal());
	}

	FixedPlusCoverage::FixedPlusCoverage(const FixedCoverage &req)
		:FixedCoverage(req.getAllParameters(),req.getStrength())
	{}

	void FixedPlusCoverage::CreateAllInters(std::set<std::set<int> > &inters) const
	{
		inters.clear();

		//将每一个subset转化为一组interaction
		std::set<std::set<int> > big_interactions;
		for(std::map<std::set<int>,int>::const_iterator it_subset=m_subsets.begin();
			it_subset!=m_subsets.end();++it_subset)
		{
			std::vector<int> subset(it_subset->first.begin(),it_subset->first.end());

			std::vector<int> index(it_subset->second,0);
			for(int i=0;i<it_subset->second;i++)
				index[i]=i;
			std::set<int> temp;
			for(int i=0;i<index.size();i++)
				temp.insert(subset[index[i]]);
			big_interactions.insert(temp);

			while(next_combination(index,subset.size()))
			{
				temp.clear();
				for(int i=0;i<index.size();i++)
					temp.insert(subset[index[i]]);
				big_interactions.insert(temp);
			}
		}

		//处理FixedCoverage部分
		if(m_strength>1)
		{
			std::vector<int> index(m_strength,0);
			for(int i=0;i<m_strength;++i)
				index[i]=i;
			std::set<int> *inter_candidate=new std::set<int>(index.begin(),index.end());
			std::set<std::set<int> >::const_iterator it_collection=big_interactions.begin();
			for(;it_collection!=big_interactions.end();++it_collection)
				if(includes(it_collection->begin(),it_collection->end(),
							inter_candidate->begin(),inter_candidate->end()))
					break;
			if(it_collection==big_interactions.end())
				inters.insert(*inter_candidate);
			delete inter_candidate;

			while(next_combination(index,m_paravalues.size()))
			{
				inter_candidate=new std::set<int>(index.begin(),index.end());
				it_collection=big_interactions.begin();
				for(;it_collection!=big_interactions.end();++it_collection)
					if(includes(it_collection->begin(),it_collection->end(),
								inter_candidate->begin(),inter_candidate->end()))
						break;
				if(it_collection==big_interactions.end())
					inters.insert(*inter_candidate);
				delete inter_candidate;
			}
		}

		//综合FixedCoverage部分和subsets部分
		inters.insert(big_interactions.begin(),big_interactions.end());
	}

	void FixedPlusCoverage::Print(std::ostream &out) const
	{
		FixedCoverage::Print(out);

		int i=0;
		out<<"Sub-sets:\n";
		for(std::map<std::set<int>,int>::const_iterator it1=m_subsets.begin();
			it1!=m_subsets.end();++it1)
		{
			out<<"set"<<++i<<": {";
			std::set<int>::const_iterator it2=it1->first.begin();
			out<<*(it2++);
			for(;it2!=it1->first.end();++it2)
				out<<", "<<*it2;
			out<<"}\tstrength: "<<it1->second<<std::endl;
		}
	}

	int FixedPlusCoverage::CheckLegal() const
	{
		//element of subsets must be legal parameter
		for(std::map<std::set<int>,int>::const_iterator it1=m_subsets.begin();
			it1!=m_subsets.end();++it1)
			for(std::set<int>::const_iterator it2=it1->first.begin();
				it2!=it1->first.end();++it2)
				if(*it2<0 || *it2>=getParaNum())
					return 1;

		//cardinality of subsets must be greater than basic strength
		for(std::map<std::set<int>,int>::const_iterator it1=m_subsets.begin();
			it1!=m_subsets.end();++it1)
			if(it1->first.size()<=m_strength)
				return 2;

		//strength of subsets must be equal or smaller than cardinality of subsets
		for(std::map<std::set<int>,int>::const_iterator it1=m_subsets.begin();
			it1!=m_subsets.end();++it1)
			if(it1->first.size()<it1->second)
				return 3;

		//strength of subsets must be greater than basic strength
		for(std::map<std::set<int>,int>::const_iterator it1=m_subsets.begin();
			it1!=m_subsets.end();++it1)
			if(it1->second<=m_strength)
				return 4;

		return 0;
	}

	void FixedPlusCoverage::HandleIllegal(int error_code) const
	{
		switch(error_code)
		{
		case 1:{
			std::cerr<<"Error when create FixedPlusCoverage: element of subset is illegal!\n";
			throw "Illegal Requirement";break;
			   };
		case 2:{
			std::cerr<<"Error when create FixedPlusCoverage: cardinality of subset is less than basic strength!\n";
			throw "Illegal Requirement";break;
			   };
		case 3:{
			std::cerr<<"Error when create FixedPlusCoverage: strength of subset is greater than cardinality of subset!\n";
			throw "Illegal Requirement";break;
			   };
		case 4:{
			std::cerr<<"Error when create FixedPlusCoverage: strength of subset is not greater than basic strength!\n";
			throw "Illegal Requirement";break;
			   }
		default:
			break;
		}
	}

}	//namespace CTT