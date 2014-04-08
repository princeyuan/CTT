#ifndef REQ_MERGE_H
#define REQ_MERGE_H

#include "UnionFrame.h"

namespace CTT
{
	class ReqMerge : public UnionFrame
	{
	public:

		ReqMerge(CTT::ReqSelector *req_selector)
			:UnionFrame(req_selector)
		{};

	protected:

		void HandleOtherFactorsInCurrentLine(std::vector<int> &current_line,
											 const std::set<int> &interaction);

		void TakeUnion(CoveringArray &dest,const CoveringArray &origin);

	};	//class ReqMerge

}	//namespace CTT

#endif