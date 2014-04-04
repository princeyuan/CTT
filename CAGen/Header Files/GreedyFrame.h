#ifndef GREEDY_FRAME_H
#define GREEDY_FRAME_H

#include "VSCAGenerator.h"

namespace CTT
{
	class GreedyFrame : public VSCAGenerator
	{
	protected:

		CoveringArray* run();

		CoveringArray* run(const CoveringArray &seed);

	protected:

		virtual void InitializeAlgorithm(){};

		virtual void FinishAlgorithm(){};

		virtual void CreateOneLine(const CoveringArray &array,std::vector<int> &one_line)=0;

	private:

		void GenerateArray(CoveringArray &array);

	};	//class GreedyFrame

}	//namespace CTT

#endif