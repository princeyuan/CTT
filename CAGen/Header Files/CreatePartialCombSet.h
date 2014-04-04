#ifndef CREATE_PARTIAL_COMB_SET_H
#define CREATE_PARTIAL_COMB_SET_H

#include "CombSet.h"
#include "Requirement.h"

namespace CTT
{
	CombSet *CreatePartialCombSet(const Requirement &req,
								  int t, //number of non-zero values
								  int d  //number of zero values
								  );
}

#endif