#ifndef PARA_SELECTOR_H
#define PARA_SELECTOR_H

#include <list>
#include "MixedCoverage.h"
#include "CombSet.h"

namespace CTT
{
	class ParaSelector
	{
	public:

		virtual int operator() (std::list<int> &undealed_factors,
								std::set<int> &dealed_factors,
								const CTT::CombSet &global_state,
								const CTT::MixedCoverage &req)=0;

	protected:

		//Call by the function 'operator()', 
		//add the selected factor into the set 'dealed_factors',
		//and remove it from the set 'undealed_factors'
		int ModifyFactorsList(std::list<int> &undealed_factors,
							  std::set<int> &dealed_factors,
							  std::list<int>::iterator selected_it);

	protected:

		static const int m_max_number=100000;
		static const int m_min_number=0;
	};

	class ParaS_First : public ParaSelector	//MoreValue
	{
	public:
		int operator() (std::list<int> &undealed_factors,
						std::set<int> &dealed_factors,
						const CTT::CombSet &global_state,
						const CTT::MixedCoverage &req);
	};

	class ParaS_MV : public ParaSelector	//MoreValue
	{
	public:
		int operator() (std::list<int> &undealed_factors,
						std::set<int> &dealed_factors,
						const CTT::CombSet &global_state,
						const CTT::MixedCoverage &req);
	};

	class ParaS_LV : public ParaSelector	//LessValue
	{
	public:
		int operator() (std::list<int> &undealed_factors,
						std::set<int> &dealed_factors,
						const CTT::CombSet &global_state,
						const CTT::MixedCoverage &req);
	};

	class ParaS_MR : public ParaSelector	//MoreRequirement
	{
	public:
		int operator() (std::list<int> &undealed_factors,
						std::set<int> &dealed_factors,
						const CTT::CombSet &global_state,
						const CTT::MixedCoverage &req);
	};

	class ParaS_LR : public ParaSelector	//LessRequirement
	{
	public:
		int operator() (std::list<int> &undealed_factors,
						std::set<int> &dealed_factors,
						const CTT::CombSet &global_state,
						const CTT::MixedCoverage &req);
	};

	class ParaS_MF : public ParaSelector	//MoreFactor
	{
	public:
		int operator() (std::list<int> &undealed_factors,
						std::set<int> &dealed_factors,
						const CTT::CombSet &global_state,
						const CTT::MixedCoverage &req);
	};

	class ParaS_LF : public ParaSelector	//LessFactor
	{
	public:
		int operator() (std::list<int> &undealed_factors,
						std::set<int> &dealed_factors,
						const CTT::CombSet &global_state,
						const CTT::MixedCoverage &req);
	};

	class ParaS_MC : public ParaSelector	//MoreCombination
	{
	public:
		int operator() (std::list<int> &undealed_factors,
						std::set<int> &dealed_factors,
						const CTT::CombSet &global_state,
						const CTT::MixedCoverage &req);
	};

	class ParaS_LC : public ParaSelector	//LessCombination
	{
	public:
		int operator() (std::list<int> &undealed_factors,
						std::set<int> &dealed_factors,
						const CTT::CombSet &global_state,
						const CTT::MixedCoverage &req);
	};

	class ParaS_MAR : public ParaSelector	//MoreAssignedRequirement
	{
	public:
		int operator() (std::list<int> &undealed_factors,
						std::set<int> &dealed_factors,
						const CTT::CombSet &global_state,
						const CTT::MixedCoverage &req);
	};

	class ParaS_LAR : public ParaSelector	//LessAssignedRequirement
	{
	public:
		int operator() (std::list<int> &undealed_factors,
						std::set<int> &dealed_factors,
						const CTT::CombSet &global_state,
						const CTT::MixedCoverage &req);
	};

	class ParaS_MAF : public ParaSelector	//MoreAssignedFactor
	{
	public:
		int operator() (std::list<int> &undealed_factors,
						std::set<int> &dealed_factors,
						const CTT::CombSet &global_state,
						const CTT::MixedCoverage &req);
	};

	class ParaS_LAF : public ParaSelector	//LessAssignedFactor
	{
	public:
		int operator() (std::list<int> &undealed_factors,
						std::set<int> &dealed_factors,
						const CTT::CombSet &global_state,
						const CTT::MixedCoverage &req);
	};

	class ParaS_MAC : public ParaSelector	//MoreAssignedCombination
	{
	public:
		int operator() (std::list<int> &undealed_factors,
						std::set<int> &dealed_factors,
						const CTT::CombSet &global_state,
						const CTT::MixedCoverage &req);
	};

	class ParaS_LAC : public ParaSelector	//LessAssignedCombination
	{
	public:
		int operator() (std::list<int> &undealed_factors,
						std::set<int> &dealed_factors,
						const CTT::CombSet &global_state,
						const CTT::MixedCoverage &req);
	};

}	//namespace CTT

#endif