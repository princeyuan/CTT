#include "NeighborGenerator.h"
#include <algorithm>

namespace CTT
{
   CoveringArray *NeighborGenerator::operator() (const NeighborCoverage &req)
	{
		std::set<std::set<int> > inters;
		req.CreateAllInters(inters);
		m_req=new MixedCoverage(req.getAllParameters(),inters);
		m_uncover_table=new CombSet(req.getAllParameters(),inters);

		CoveringArray *p=run();

		delete m_req;
		return p;
	}

	CoveringArray *NeighborGenerator::operator() (const NeighborPlusCoverage &req)
	{
		std::set<std::set<int> > inters;
		req.CreateAllInters(inters);
		m_req=new MixedCoverage(req.getAllParameters(),inters);
		m_uncover_table=new CombSet(req.getAllParameters(),inters);

		CoveringArray *p=run();

		delete m_req;
		return p;
	}
    
}	//namespace CTT

