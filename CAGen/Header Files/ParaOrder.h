#ifndef PARA_ORDER_H
#define PARA_ORDER_H

#include "IPOFrame.h"
#include "ReqSelector.h"
#include "ParaSelector.h"

namespace CTT
{
	class ParaOrder : public IPOFrame
	{
	public:

		ParaOrder(CTT::ReqSelector *req_selector = new CTT::ReqS_MC,
				  CTT::ParaSelector *param_selector = new CTT::ParaS_MV,
				  bool is_Need_FixDonotCareValue = false)
			:IPOFrame(is_Need_FixDonotCareValue),
			 m_req_selector(req_selector),
			 m_param_selector(param_selector)
		{};

	protected:

		const std::set<int> &SelectOneReq();

		int SelectOneFactor(std::set<int> &dealed_factors,
							std::list<int> &undealed_factors);

		void HandleOneFactor(CoveringArray &array,
							 int current_factor,
							 const std::set<int> &dealed_factors);

	private:

		void HorizontalExtend(CoveringArray &array,
							  int current_factor,
							  CombSet &current_comb_set,
							  std::set<int> &inserted_index);

		void VerticalExtend(CoveringArray &array,
							CombSet &current_comb_set,
							std::set<int> &inserted_index);

	private:

		void CreateInvolvedInters(const std::set<int> &dealed_factors,
								  std::set<std::set<int> > &inter_set,
								  int current_factor);

		int CountCoverNum(int current_factor,int value,
						  const CombSet &current_comb_set,
						  const std::vector<int> &one_line);

		int SelectValue(int current_factor,
						const CombSet &current_comb_set,
						const CoveringArray::const_iterator it_array,
						const std::vector<int> &appear_time,
						int last_value);

		bool canHorizontalExtend(int current_factor,
								 const CoveringArray::const_iterator it_array,
								 const CombSet &comb_set);

	private:

		CTT::ReqSelector *m_req_selector;
		CTT::ParaSelector *m_param_selector;

	};	//class ParaOrder

}	//namespace CTT

#endif