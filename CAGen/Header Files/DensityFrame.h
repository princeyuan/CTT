#ifndef DENSITY_FRAME_H
#define DENSITY_FRAME_H

#include "GreedyFrame.h"

namespace CTT
{
	class DensityFrame : public GreedyFrame
	{
	protected:

		DensityFrame()
			:m_max_denominator(0)
		{};

	protected:

		void InitializeAlgorithm();

		virtual float CalculateReqDensity(const LocalCombSet &state,
										  const std::vector<int> &one_line);

	protected:

		int m_max_denominator;

	};	//class DensityFrame

}	//namespace CTT

#endif