#ifndef DENSITY_FO_H
#define DENSITY_FO_H

#include <list>
#include "DensityFrame.h"

namespace CTT
{
	class DensityFO : public DensityFrame
	{
	protected:

		void CreateOneLine(const CoveringArray &array,std::vector<int> &one);

	private:

		int SelectOnePara(std::list<int> &para_cache,
						  const std::vector<int> &one);
	
		int FixOneValue(int selected_para,
						std::vector<int> &one);

		float CalculateParaDensity(int parameter,const std::list<float> &req_density_table);

		float CalculateValueDensity(int parameter,int value,
									const std::vector<int> &one);

	};	//class DensityFO

}	//nanmespace CTT

#endif