#include "ReqSelector.h"

#include <vector>
#include <algorithm>

namespace CTT
{
	CombSet::iterator ReqSelector::operator() (CombSet &global_state,
											   const Requirement &req)
	{
		std::list<CombSet::iterator> local_state_cache;
		for(CombSet::iterator it=global_state.begin();
			it!=global_state.end();++it)
			local_state_cache.push_back(it);

		return (operator () (local_state_cache,std::set<int>(),req)).first;
	}

	int ReqSelector::IsRelated(const CombSet::const_iterator &current_it,
							   const std::set<int> &dealed_factors)
	{
		int count=0;
		std::set<int>::const_iterator it1=current_it->getParaSet().begin();
		std::set<int>::const_iterator it2=dealed_factors.begin();
		while(it1!=current_it->getParaSet().end() && it2!=dealed_factors.end())
		{
			if(*it1<*it2)
				++it1;
			else if(*it1>*it2)
				++it2;
			else
			{
				++it1;
				++it2;
				++count;
			}
		}
		return count;
	}

	bool ReqSelector::ModifyLocalStateCache(
			const std::list<CombSet::iterator>::iterator &selected_it1,
			const std::list<CombSet::iterator>::iterator &selected_it2,
			std::list<CombSet::iterator> &local_state_cache,
			std::set<int> &dealed_factors,
			CombSet::iterator &selected)
	{
		bool flag;
		std::list<CombSet::iterator>::iterator selected_it;
		if(selected_it2==local_state_cache.end())
		{
			selected_it=selected_it1;
			flag=true;
		}
		else
		{
			selected_it=selected_it2;
			flag=false;
		}

		selected=*selected_it;
		local_state_cache.erase(selected_it);
		dealed_factors.insert(selected->getParaSet().begin(),
			selected->getParaSet().end());

		return flag;
	}

	std::pair<CombSet::iterator,bool> ReqS_First::operator() (
				std::list<CombSet::iterator> &local_state_cache,
				std::set<int> &dealed_factors,
				const Requirement &req)
	{
		std::list<CombSet::iterator>::iterator selected_it=local_state_cache.begin();

		bool flag=false;
		if(0!=IsRelated(*selected_it,dealed_factors))
			flag=true;

		CombSet::iterator selected_one=*selected_it;
		local_state_cache.erase(selected_it);
		dealed_factors.insert(selected_one->getParaSet().begin(),
			selected_one->getParaSet().end());

		return std::pair<CombSet::iterator,bool>(selected_one,flag);
	}

	std::pair<CombSet::iterator,bool> ReqS_MF::operator() (
				std::list<CombSet::iterator> &local_state_cache,
				std::set<int> &dealed_factors,
				const Requirement &req)
	{
		int max_num=m_min_number;
		std::list<CombSet::iterator>::iterator selected_it1=local_state_cache.end();
		std::list<CombSet::iterator>::iterator selected_it2=local_state_cache.end();
		for(std::list<CombSet::iterator>::iterator it=local_state_cache.begin();
			it!=local_state_cache.end();++it)
		{
			int number=(*it)->getParaSet().size();
			if(number>max_num)
			{
				max_num=number;
				selected_it1=it;
				if(0!=IsRelated(*it,dealed_factors))
					selected_it2=it;
			}
		}

		CombSet::iterator selected_one;
		bool flag=ModifyLocalStateCache(selected_it1,selected_it2,
			local_state_cache,dealed_factors,selected_one);
		return std::pair<CombSet::iterator,bool>(selected_one,flag);
	}

	std::pair<CombSet::iterator,bool> ReqS_LF::operator() (
				std::list<CombSet::iterator> &local_state_cache,
				std::set<int> &dealed_factors,
				const Requirement &req)
	{
		int min_num=m_max_number;
		std::list<CombSet::iterator>::iterator selected_it1=local_state_cache.end();
		std::list<CombSet::iterator>::iterator selected_it2=local_state_cache.end();
		for(std::list<CombSet::iterator>::iterator it=local_state_cache.begin();
			it!=local_state_cache.end();++it)
		{
			int number=(*it)->getParaSet().size();
			if(number<min_num)
			{
				min_num=number;
				selected_it1=it;
				if(0!=IsRelated(*it,dealed_factors))
					selected_it2=it;
			}
		}

		CombSet::iterator selected_one;
		bool flag=ModifyLocalStateCache(selected_it1,selected_it2,
			local_state_cache,dealed_factors,selected_one);
		return std::pair<CombSet::iterator,bool>(selected_one,flag);
	}

	std::pair<CombSet::iterator,bool> ReqS_MC::operator() (
				std::list<CombSet::iterator> &local_state_cache,
				std::set<int> &dealed_factors,
				const Requirement &req)
	{
		int max_num=m_min_number;
		std::list<CombSet::iterator>::iterator selected_it1=local_state_cache.end();
		std::list<CombSet::iterator>::iterator selected_it2=local_state_cache.end();
		for(std::list<CombSet::iterator>::iterator it=local_state_cache.begin();
			it!=local_state_cache.end();++it)
		{
			int number=(*it)->getUncoverNumber();
			if(number>max_num)
			{
				max_num=number;
				selected_it1=it;
				if(0!=IsRelated(*it,dealed_factors))
					selected_it2=it;
			}
		}

		CombSet::iterator selected_one;
		bool flag=ModifyLocalStateCache(selected_it1,selected_it2,
			local_state_cache,dealed_factors,selected_one);
		return std::pair<CombSet::iterator,bool>(selected_one,flag);
	}

	std::pair<CombSet::iterator,bool> ReqS_LC::operator() (
				std::list<CombSet::iterator> &local_state_cache,
				std::set<int> &dealed_factors,
				const Requirement &req)
	{
		int min_num=m_max_number;
		std::list<CombSet::iterator>::iterator selected_it1=local_state_cache.end();
		std::list<CombSet::iterator>::iterator selected_it2=local_state_cache.end();
		for(std::list<CombSet::iterator>::iterator it=local_state_cache.begin();
			it!=local_state_cache.end();++it)
		{
			int number=(*it)->getUncoverNumber();
			if(number<min_num)
			{
				min_num=number;
				selected_it1=it;
				if(0!=IsRelated(*it,dealed_factors))
					selected_it2=it;
			}
		}

		CombSet::iterator selected_one;
		bool flag=ModifyLocalStateCache(selected_it1,selected_it2,
			local_state_cache,dealed_factors,selected_one);
		return std::pair<CombSet::iterator,bool>(selected_one,flag);
	}


	/************************************************
	*当pair中second为false时

	*表示所有interaction均不含已赋过值的因素

	*选择第一个尚未被处理过的interaction
	*************************************************/
	std::pair<CombSet::iterator,bool> ReqS_MAF::operator() (
				std::list<CombSet::iterator> &local_state_cache,
				std::set<int> &dealed_factors,
				const Requirement &req)
	{
		int max_num=m_min_number;
		std::list<CombSet::iterator>::iterator selected_it1=local_state_cache.begin();
		std::list<CombSet::iterator>::iterator selected_it2=local_state_cache.end();
		for(std::list<CombSet::iterator>::iterator it=local_state_cache.begin();
			it!=local_state_cache.end();++it)
		{
			int number=IsRelated(*it,dealed_factors);
			if(number>max_num && number!=0)
			{
				max_num=number;
				selected_it2=it;
			}
		}

		CombSet::iterator selected_one;
		bool flag=ModifyLocalStateCache(selected_it1,selected_it2,
			local_state_cache,dealed_factors,selected_one);
		return std::pair<CombSet::iterator,bool>(selected_one,flag);
	}

	std::pair<CombSet::iterator,bool> ReqS_LAF::operator() (
				std::list<CombSet::iterator> &local_state_cache,
				std::set<int> &dealed_factors,
				const Requirement &req)
	{
		int min_num=m_max_number;
		std::list<CombSet::iterator>::iterator selected_it1=local_state_cache.begin();
		std::list<CombSet::iterator>::iterator selected_it2=local_state_cache.end();
		for(std::list<CombSet::iterator>::iterator it=local_state_cache.begin();
			it!=local_state_cache.end();++it)
		{
			int number=IsRelated(*it,dealed_factors);
			if(number<min_num && number!=0)
			{
				min_num=number;
				selected_it2=it;
			}
		}

		CombSet::iterator selected_one;
		bool flag=ModifyLocalStateCache(selected_it1,selected_it2,
			local_state_cache,dealed_factors,selected_one);
		return std::pair<CombSet::iterator,bool>(selected_one,flag);
	}

	std::pair<CombSet::iterator,bool> ReqS_MAFP::operator() (
				std::list<CombSet::iterator> &local_state_cache,
				std::set<int> &dealed_factors,
				const Requirement &req)
	{
		float max_num=(float)m_min_number;
		std::list<CombSet::iterator>::iterator selected_it1=local_state_cache.begin();
		std::list<CombSet::iterator>::iterator selected_it2=local_state_cache.end();
		for(std::list<CombSet::iterator>::iterator it=local_state_cache.begin();
			it!=local_state_cache.end();++it)
		{
			int num=IsRelated(*it,dealed_factors);
			float number=(float)num/(float)((*it)->getParaSet().size());
			if(number>max_num && num!=0)
			{
				max_num=number;
				selected_it2=it;
			}
		}

		CombSet::iterator selected_one;
		bool flag=ModifyLocalStateCache(selected_it1,selected_it2,
			local_state_cache,dealed_factors,selected_one);
		return std::pair<CombSet::iterator,bool>(selected_one,flag);
	}

	std::pair<CombSet::iterator,bool> ReqS_LAFP::operator() (
				std::list<CombSet::iterator> &local_state_cache,
				std::set<int> &dealed_factors,
				const Requirement &req)
	{
		float min_num=(float)m_max_number;
		std::list<CombSet::iterator>::iterator selected_it1=local_state_cache.begin();
		std::list<CombSet::iterator>::iterator selected_it2=local_state_cache.end();
		for(std::list<CombSet::iterator>::iterator it=local_state_cache.begin();
			it!=local_state_cache.end();++it)
		{
			int num=IsRelated(*it,dealed_factors);
			float number=(float)num/(float)((*it)->getParaSet().size());
			if(number<min_num && num!=0)
			{
				min_num=number;
				selected_it2=it;
			}
		}

		CombSet::iterator selected_one;
		bool flag=ModifyLocalStateCache(selected_it1,selected_it2,
			local_state_cache,dealed_factors,selected_one);
		return std::pair<CombSet::iterator,bool>(selected_one,flag);
	}

	std::pair<CombSet::iterator,bool> ReqS_MAC::operator() (
				std::list<CombSet::iterator> &local_state_cache,
				std::set<int> &dealed_factors,
				const Requirement &req)
	{
		int max_num=m_min_number;
		std::list<CombSet::iterator>::iterator selected_it1=local_state_cache.begin();
		std::list<CombSet::iterator>::iterator selected_it2=local_state_cache.end();
		for(std::list<CombSet::iterator>::iterator it=local_state_cache.begin();
			it!=local_state_cache.end();++it)
		{
			const std::set<int> &inter=(*it)->getParaSet();
			std::vector<int> temp(std::min(dealed_factors.size(),inter.size()),-1);
			std::vector<int>::iterator the_end=set_intersection(
					dealed_factors.begin(),dealed_factors.end(),
					inter.begin(),inter.end(),temp.begin());

			int number=1;
			for(std::vector<int>::const_iterator itp=temp.begin();itp!=the_end;++itp)
				number*=req.getParaValue(*itp);

			if(number>max_num && number>1)
			{
				max_num=number;
				selected_it2=it;
			}
		}

		CombSet::iterator selected_one;
		bool flag=ModifyLocalStateCache(selected_it1,selected_it2,
			local_state_cache,dealed_factors,selected_one);
		return std::pair<CombSet::iterator,bool>(selected_one,flag);
	}

	std::pair<CombSet::iterator,bool> ReqS_LAC::operator() (
				std::list<CombSet::iterator> &local_state_cache,
				std::set<int> &dealed_factors,
				const Requirement &req)
	{
		int min_num=m_max_number;
		std::list<CombSet::iterator>::iterator selected_it1=local_state_cache.begin();
		std::list<CombSet::iterator>::iterator selected_it2=local_state_cache.end();
		for(std::list<CombSet::iterator>::iterator it=local_state_cache.begin();
			it!=local_state_cache.end();++it)
		{
			const std::set<int> &inter=(*it)->getParaSet();
			std::vector<int> temp(dealed_factors.size()+inter.size(),-1);
			std::vector<int>::iterator the_end=set_intersection(
					dealed_factors.begin(),dealed_factors.end(),
					inter.begin(),inter.end(),temp.begin());

			int number=1;
			for(std::vector<int>::const_iterator itp=temp.begin();itp!=the_end;++itp)
				number*=req.getParaValue(*itp);

			if(number<min_num && number>1)
			{
				min_num=number;
				selected_it2=it;
			}
		}

		CombSet::iterator selected_one;
		bool flag=ModifyLocalStateCache(selected_it1,selected_it2,
			local_state_cache,dealed_factors,selected_one);
		return std::pair<CombSet::iterator,bool>(selected_one,flag);
	}

	std::pair<CombSet::iterator,bool> ReqS_MACP::operator() (
				std::list<CombSet::iterator> &local_state_cache,
				std::set<int> &dealed_factors,
				const Requirement &req)
	{
		float max_num=(float)m_min_number;
		std::list<CombSet::iterator>::iterator selected_it1=local_state_cache.begin();
		std::list<CombSet::iterator>::iterator selected_it2=local_state_cache.end();
		for(std::list<CombSet::iterator>::iterator it=local_state_cache.begin();
			it!=local_state_cache.end();++it)
		{
			const std::set<int> &inter=(*it)->getParaSet();
			std::vector<int> temp(dealed_factors.size()+inter.size(),-1);
			std::vector<int>::iterator the_end=set_intersection(
					dealed_factors.begin(),dealed_factors.end(),
					inter.begin(),inter.end(),temp.begin());

			int num=1;
			for(std::vector<int>::const_iterator itp=temp.begin();itp!=the_end;++itp)
				num*=req.getParaValue(*itp);
			float number=(float)(num)/(float)((*it)->Size());

			if(number>max_num && num>1)
			{
				max_num=number;
				selected_it2=it;
			}
		}

		CombSet::iterator selected_one;
		bool flag=ModifyLocalStateCache(selected_it1,selected_it2,
			local_state_cache,dealed_factors,selected_one);
		return std::pair<CombSet::iterator,bool>(selected_one,flag);
	}

	std::pair<CombSet::iterator,bool> ReqS_LACP::operator() (
				std::list<CombSet::iterator> &local_state_cache,
				std::set<int> &dealed_factors,
				const Requirement &req)
	{
		float min_num=m_max_number;
		std::list<CombSet::iterator>::iterator selected_it1=local_state_cache.begin();
		std::list<CombSet::iterator>::iterator selected_it2=local_state_cache.end();
		for(std::list<CombSet::iterator>::iterator it=local_state_cache.begin();
			it!=local_state_cache.end();++it)
		{
			const std::set<int> &inter=(*it)->getParaSet();
			std::vector<int> temp(dealed_factors.size()+inter.size(),-1);
			std::vector<int>::iterator the_end=set_intersection(
					dealed_factors.begin(),dealed_factors.end(),
					inter.begin(),inter.end(),temp.begin());

			int num=1;
			for(std::vector<int>::const_iterator itp=temp.begin();itp!=the_end;++itp)
				num*=req.getParaValue(*itp);
			float number=((float)(num))/((float)((*it)->Size()));

			if(number<min_num && num>1)
			{
				min_num=number;
				selected_it2=it;
			}
		}

		CombSet::iterator selected_one;
		bool flag=ModifyLocalStateCache(selected_it1,selected_it2,
			local_state_cache,dealed_factors,selected_one);
		return std::pair<CombSet::iterator,bool>(selected_one,flag);
	}

}	//namespace CTT