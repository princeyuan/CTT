#ifndef TCG_H
#define TCG_H

#include "GreedyFrame.h"

namespace CTT
{
	class TCG : public GreedyFrame
	{
	protected:

		void InitializeAlgorithm();

		void FinishAlgorithm();

		void CreateOneLine(const CoveringArray &array,std::vector<int> &one_line);

	};
}

#endif