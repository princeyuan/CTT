#include "CreatePartialCombSet.h"

namespace CTT
{
	CombSet *CreatePartialCombSet(const Requirement &req,
								  int t, //number of non-zero values
								  int d  //number of zero values
								  )
	{
		FixedCoverage *temp_fixed=new FixedCoverage(req.getAllParameters(),t+d);
		MixedCoverage *temp_mixed=new MixedCoverage(*temp_fixed);
		CombSet *p=new CombSet(*temp_mixed);
		delete temp_mixed;
		delete temp_fixed;

		//remove all elements that donot belongs to the Partial Set
		std::vector<int> combination;
		for(CombSet::iterator it=p->begin();
			it!=p->end();++it)
		{
			for(int i=0;i<it->Size();i++)
			{
				it->getCombination(combination,i);

				int num=0;
				for(std::vector<int>::const_iterator it_comb=combination.begin();
					it_comb!=combination.end();++it_comb)
				{
					if(*it_comb==0)
						++num;
				}

				if(num!=d)
				{
					it->Remove(i);
				}
			}
		}

		return p;
	}
}