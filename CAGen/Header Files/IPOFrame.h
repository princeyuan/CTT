#ifndef IPO_FRAME_H
#define IPO_FRAME_H

#include "VSCAGenerator.h"

namespace CTT
{
	class IPOFrame : public VSCAGenerator
	{
	protected:

		IPOFrame(bool is_Need_FixDonotCareValue=false)
			:m_Is_Need_FixDonotCareValue(is_Need_FixDonotCareValue)
		{}

	protected:

		CoveringArray* run();

		CoveringArray* run(const CoveringArray &seed);

	private:

		void GenerateArray(CoveringArray &array);

		void HandleOneReq(const std::set<int> &interaction,
						  CoveringArray &array,
						  std::set<int> &dealed_factors,
						  std::list<int> &undealed_factors);

	protected:

		virtual const std::set<int> &SelectOneReq()=0;

		virtual int SelectOneFactor(std::set<int> &dealed_factors,
									std::list<int> &undealed_factors)=0;

		virtual void HandleOneFactor(CoveringArray &array,
									 int current_factor,
									 const std::set<int> &dealed_factors)=0;

	protected:

		int canInsertComb(const std::vector<int> &comb,
						  const std::set<int> &params,
						  const std::vector<int> &line);

	private:

		void HandleEmptyPosition(CoveringArray &array);

	protected:

		bool m_Is_Need_FixDonotCareValue;

	};	//class IPOFrame

}	//namespace CTT

#endif