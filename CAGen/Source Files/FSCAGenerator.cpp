#include "FSCAGenerator.h"

#include <iostream>

namespace  CTT
{
	CoveringArray* FSCAGenerator::operator() (const FixedCoverage &req)
	{
		m_req=&req;
		m_uncover_table=new CombSet(*m_req);

		CoveringArray *p=run();

		delete m_uncover_table;
		m_uncover_table=NULL;
		m_req=NULL;

		return p;
	}

	CoveringArray* FSCAGenerator::operator() (const FixedCoverage &req,
											  const CoveringArray &seed)
	{
		if(isLegalSeed(req,seed))
		{
			m_req=&req;
			m_uncover_table=new CombSet(*m_req);
			for(CoveringArray::const_iterator it=seed.begin();
				it!=seed.end();++it)
				ModifyUncoverTable(*it,*m_uncover_table);

			CoveringArray *p=run(seed);

			delete m_uncover_table;
			m_uncover_table=NULL;
			m_req=NULL;

			return p;
		}
		else
			return IllegalSeedHandler();
	}

}	//namespace CTT