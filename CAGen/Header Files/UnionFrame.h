#ifndef UNION_FRAME_H
#define UNION_FRAME_H

#include "VSCAGenerator.h"
#include "ReqSelector.h"

namespace CTT
{
	class UnionFrame : public VSCAGenerator
	{
	protected:

		UnionFrame(CTT::ReqSelector *req_selector)
			:m_req_selector(req_selector)
		{};

		CoveringArray* run();

		CoveringArray* run(const CoveringArray &seed){return NULL;};

	protected:

		virtual void InitializeAlgorithm(){};

		virtual void HandleOtherFactorsInCurrentLine(
				std::vector<int> &current_line,
				const std::set<int> &interaction)=0;

		virtual void TakeUnion(CoveringArray &dest,const CoveringArray &origin)=0;

	protected:

		void HandleOneReq(CoveringArray &array,const std::set<int> &interaction);

		bool IsSuitableLine(const std::vector<int> &line1,const std::vector<int> &line2);

		void HandleEmptyPosition(CoveringArray &array);

	private:

		void GenerateArray(CoveringArray &array);

	protected:

		ReqSelector *m_req_selector;

	};	//class UnionFrame

}	//namespace CTT

#endif