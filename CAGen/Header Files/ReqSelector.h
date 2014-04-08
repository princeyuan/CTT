#ifndef REQ_SELECTOR_H
#define REQ_SELECTOR_H

#include "MixedCoverage.h"
#include "CombSet.h"

namespace CTT
{
	class ReqSelector
	{
	public:

		//ѡ��һ��interaction, ɾ������cache�еľ���, ������һ��pair
		//����firstΪ��ѡ����interaction��CombSet�е�iterator
		//����second��ʾ��interaction�Ƿ����ѱ�����ֵ������, ���ȱ�֤��Ϊtrue
		virtual std::pair<CombSet::iterator,bool> operator() (
				std::list<CombSet::iterator> &local_state_cache,
				std::set<int> &dealed_factors,
				const Requirement &req)=0;

		//���㷨��ʼ, ����δ��interaction��ѡ��, Ҳû�����ر����������µ�����
		//��MF, LF, MC, LC, MR, LR�����ֲ��Կ���, �����������dealed_factorsΪ�ն��˻�ΪFirst����
		//��ҪӦ����IPO����
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