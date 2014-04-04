#ifndef AETG_H
#define AETG_H

#include "GreedyFrame.h"

namespace CTT
{
	class AETG : public GreedyFrame
	{
	public:

		AETG(int max_round=50)
			:m_max_round(max_round)
		{};

	protected:

		void InitializeAlgorithm();

		void FinishAlgorithm();

		void CreateOneLine(const CoveringArray &array,std::vector<int> &one_line);

	private:

		int m_max_round;
	};
}

#endif