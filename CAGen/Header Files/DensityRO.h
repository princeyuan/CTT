#ifndef DENSITY_RO_H
#define DENSITY_RO_H

#include <list>
#include "DensityFrame.h"

namespace CTT
{
	class DensityRO : public DensityFrame
	{
	protected:

		void CreateOneLine(const CoveringArray &array,std::vector<int> &one_line);

	private:

		CombSet::iterator SelectOneReq(std::list<CombSet::iterator> &local_state_cache,
												const std::vector<int> &one_line);
	
		void FixValues(CombSet::iterator &it_req,std::vector<int> &one_line);

		float CalculateCombDensity(const LocalCombSet &state,
								   const std::vector<int> &one_line,
								   int comb_index);

	};	//class DensityRO

}	//nanmespace CTT

#endif