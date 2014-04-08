#include "CAGenerator.h"

#include <iostream>

namespace  CTT
{
	void CAGenerator::ModifyUncoverTable(const std::vector<int> &one_line,
										 CombSet &global_state)
	{
		for(CombSet::iterator it=global_state.begin();
			it!=global_state.end();++it)
		{
			int j=-1;
			const std::set<int> &params=it->getParaSet();
			std::vector<int> combination(params.size(),-1);
			std::set<int>::const_iterator it1=params.begin();
			for(;it1!=params.end();++it1)
			{
				if(one_line[*it1]!=-1)
					combination[++j]=one_line[*it1];
				else
					break;
			}
			if(it1==params.end())
				it->Remove(combination);
		}
	}

	bool CAGenerator::isLegalSeed(const Requirement &req,const CoveringArray &seed)
	{
		if(seed.Size()==0)
			return true;

		//number of parameters in req == number of columns in array
		if(req.getParaNum()!=seed.Column())
			return false;

		//all elements of array are assigned and legal
		for(CoveringArray::const_iterator it=seed.begin();it!=seed.end();++it)
			for(int i=0;i<it->size();++i)
				if((*it)[i]>=req.getParaValue(i) || (*it)[i]<0)
					return false;

		return true;
	}

	CoveringArray* CAGenerator::IllegalSeedHandler()
	{
		std::cerr<<"The seed covering array isn't legal for requirement!"<<std::endl;
		return NULL;
	}

}	//namespace CTT