#ifndef SIMPLE_UNION_H
#define SIMPLE_UNION_H

#include "UnionFrame.h"

namespace CTT
{
	class MyUnion : public UnionFrame
	{
	public:

		MyUnion()
			:UnionFrame(new ReqS_First)
		{};

	protected:

		void InitializeAlgorithm();

		void HandleOtherFactorsInCurrentLine(std::vector<int> &current_line,
											 const std::set<int> &interaction);

		void TakeUnion(CoveringArray &dest,const CoveringArray &origin);

	};	//class MyUnion

}	//namespace CTT

#endif