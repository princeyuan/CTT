#ifndef GEN_ALGO_TESTING_H
#define GEN_ALGO_TESTING_H

#include "DensityRO.h"
#include "DensityFO.h"
#include "MyUnion.h"
#include "ReqMerge.h"
#include "ParaOrder.h"
#include "NeighborGenerator.h"
#include "SSTSearch.h"
#include "TwoLevel.h"
#include "BestGreedy.h"
#include "CombPriTable.h"
#include "WeightedDensity.h"

#include "CreatePartialCombSet.h"

void DensityRO_Test();
void DensityFO_Test();
void MyUnion_Test();
void ReqMerge_Test();
void ParaOrder_Test();
void NeighborGenerator_Test();
void SSTSearch_Test();
void TwoLevel_Test();
void BestGreedy_Test();
void WeightedDensity_Test();

void PCAGen_Test();

#endif