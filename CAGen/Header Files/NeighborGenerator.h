#ifndef NEIGHBOR_GENERATOR_H
#define NEIGHBOR_GENERATOR_H

#include "ReqMerge.h"
#include "NeighborCoverage.h"
#include "NeighborPlusCoverage.h"

namespace CTT
{
	class NeighborGenerator : public ReqMerge
    {
	public:

		NeighborGenerator()
			:ReqMerge(new CTT::ReqS_First)
		{};

		CoveringArray *operator() (const NeighborCoverage &req);

		CoveringArray *operator() (const NeighborPlusCoverage &req);
        
    };	//class Neighbor
    
}	//namespace CTT

#endif
