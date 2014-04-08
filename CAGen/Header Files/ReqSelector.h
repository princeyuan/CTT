#ifndef REQ_SELECTOR_H
#define REQ_SELECTOR_H

#include "MixedCoverage.h"
#include "CombSet.h"

namespace CTT
{
	class ReqSelector
	{
	public:

		//选择一个interaction, 删除其在cache中的镜像, 并返回一个pair
		//其中first为被选出的interaction在CombSet中的iterator
		//其中second表示该interaction是否含有已被赋过值的因素, 优先保证其为true
		virtual std::pair<CombSet::iterator,bool> operator() (
				std::list<CombSet::iterator> &local_state_cache,
				std::set<int> &dealed_factors,
				const Requirement &req)=0;

		//在算法初始, 即尚未有interaction被选出, 也没有因素被处理的情况下的特例
		//仅MF, LF, MC, LC, MR, LR共四种策略可用, 其余策略由于dealed_factors为空而退化为First策略
		//主要应用于IPO策略
		CombSet::iterator operator() (CombSet &global_state,const Requirement &req);

	protected:

		int IsRelated(const CombSet::const_iterator &current_it,
					  const std::set<int> &dealed_factors);

		bool ModifyLocalStateCache(
			const std::list<CombSet::iterator>::iterator &selected_it1,
			const std::list<CombSet::iterator>::iterator &selected_it2,
			std::list<CombSet::iterator> &local_state_cache,
			std::set<int> &dealed_factors,
			CombSet::iterator &selected);

	protected:

		static const int m_max_number=2147483647;
		static const int m_min_number=0;
	};

	class ReqS_First : public ReqSelector	//select first one
	{
	public:
		std::pair<CombSet::iterator,bool> operator() (
				std::list<CombSet::iterator> &local_state_cache,
				std::set<int> &dealed_factors,
				const Requirement &req);
	};

	class ReqS_MF : public ReqSelector	//MoreFActor
	{
	public:
		std::pair<CombSet::iterator,bool> operator() (
				std::list<CombSet::iterator> &local_state_cache,
				std::set<int> &dealed_factors,
				const Requirement &req);
	};

	class ReqS_LF : public ReqSelector	//LessFActor
	{
	public:
		std::pair<CombSet::iterator,bool> operator() (
				std::list<CombSet::iterator> &local_state_cache,
				std::set<int> &dealed_factors,
				const Requirement &req);
	};

	class ReqS_MC : public ReqSelector	//MoreCombination
	{
	public:
		std::pair<CombSet::iterator,bool> operator() (
				std::list<CombSet::iterator> &local_state_cache,
				std::set<int> &dealed_factors,
				const Requirement &req);
	};

	class ReqS_LC : public ReqSelector	//LessCombination
	{
	public:
		std::pair<CombSet::iterator,bool> operator() (
				std::list<CombSet::iterator> &local_state_cache,
				std::set<int> &dealed_factors,
				const Requirement &req);
	};

	class ReqS_MAF : public ReqSelector	//MoreAssignedFactor
	{
	public:
		std::pair<CombSet::iterator,bool> operator() (
				std::list<CombSet::iterator> &local_state_cache,
				std::set<int> &dealed_factors,
				const Requirement &req);
	};

	class ReqS_LAF : public ReqSelector	//LessAssignedFactor
	{
	public:
		std::pair<CombSet::iterator,bool> operator() (
				std::list<CombSet::iterator> &local_state_cache,
				std::set<int> &dealed_factors,
				const Requirement &req);
	};

	class ReqS_MAFP : public ReqSelector	//MoreAssignedFactorPercentage
	{
	public:
		std::pair<CombSet::iterator,bool> operator() (
				std::list<CombSet::iterator> &local_state_cache,
				std::set<int> &dealed_factors,
				const Requirement &req);
	};

	class ReqS_LAFP : public ReqSelector	//LessAssignedFactorPercentage
	{
	public:
		std::pair<CombSet::iterator,bool> operator() (
				std::list<CombSet::iterator> &local_state_cache,
				std::set<int> &dealed_factors,
				const Requirement &req);
	};

	class ReqS_MAC : public ReqSelector	//MoreAssignedCombination
	{
	public:
		std::pair<CombSet::iterator,bool> operator() (
				std::list<CombSet::iterator> &local_state_cache,
				std::set<int> &dealed_factors,
				const Requirement &req);
	};

	class ReqS_LAC : public ReqSelector	//LessAssignedCombination
	{
	public:
		std::pair<CombSet::iterator,bool> operator() (
				std::list<CombSet::iterator> &local_state_cache,
				std::set<int> &dealed_factors,
				const Requirement &req);
	};

	class ReqS_MACP : public ReqSelector	//MoreAssignedCombinationPercentage
	{
	public:
		std::pair<CombSet::iterator,bool> operator() (
				std::list<CombSet::iterator> &local_state_cache,
				std::set<int> &dealed_factors,
				const Requirement &req);
	};

	class ReqS_LACP : public ReqSelector	//LessAssignedCombinationPercentage
	{
	public:
		std::pair<CombSet::iterator,bool> operator() (
				std::list<CombSet::iterator> &local_state_cache,
				std::set<int> &dealed_factors,
				const Requirement &req);
	};

}	//namespace CTT

#endif