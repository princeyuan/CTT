#ifndef TWO_LEVEL_H
#define TWO_LEVEL_H

#include "FSCAGenerator.h"

namespace CTT
{
	class TwoLevel : public FSCAGenerator
	{
	protected:

		CoveringArray* run();

		//Can not generate covering array with seed lines
		CoveringArray* run(const CoveringArray &seed) {return NULL;};	

	private:

		CoveringArray *HandleFirstReq();

		void InitializeCandidate(std::vector<int> &column_candidate,const CoveringArray &array);

		bool GetNextCandidate(std::vector<int> &column_candidate);

		bool IsFitColumn(CoveringArray &array,const std::vector<int> &column_candidate,int current_para);

		void AddNewLines(CoveringArray &array,int current_para);

		void ModifyCandidate(std::vector<int> &column_candidate,const CoveringArray &array);

		bool IsTwoStrengthReq() {return (m_req->getStrength()==2)?true:false;};

		bool IsTwoLevelReq();
	};
}

#endif