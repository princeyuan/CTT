#include "ParaSelector.h"

namespace CTT
{
	int ParaSelector::ModifyFactorsList(std::list<int> &undealed_factors,
										std::set<int> &dealed_factors,
										std::list<int>::iterator selected_it)
	{
		if(selected_it!=undealed_factors.end())
		{
			int selected_factor=*selected_it;
			undealed_factors.erase(selected_it);
			dealed_factors.insert(selected_factor);
			return selected_factor;
		}
		else
			return -1;
	}

	int ParaS_First::operator() (std::list<int> &undealed_factors,
								 std::set<int> &dealed_factors,
								 const CTT::CombSet &global_state,
								 const CTT::MixedCoverage &req)
	{
		std::list<int>::iterator selected_it=undealed_factors.end();
		for(std::list<int>::iterator it_factor=undealed_factors.begin();
			it_factor!=undealed_factors.end();++it_factor)
		{
			MixedCoverage::const_iterator it_req=req.begin();
			for(;it_req!=req.end();++it_req)
				if(it_req->find(*it_factor)!=it_req->end())
					break;
			if(it_req==req.end())continue;

			selected_it=it_factor;
			break;
		}
		return ModifyFactorsList(undealed_factors,dealed_factors,selected_it);
	}

	int ParaS_MV::operator() (std::list<int> &undealed_factors,
							  std::set<int> &dealed_factors,
							  const CTT::CombSet &global_state,
							  const CTT::MixedCoverage &req)
	{
		int max_num=m_min_number;
		std::list<int>::iterator selected_it=undealed_factors.end();
		for(std::list<int>::iterator it_factor=undealed_factors.begin();
			it_factor!=undealed_factors.end();++it_factor)
		{
			MixedCoverage::const_iterator it_req=req.begin();
			for(;it_req!=req.end();++it_req)
				if(it_req->find(*it_factor)!=it_req->end())
					break;
			if(it_req==req.end())continue;

			if(req.getParaValue(*it_factor)>max_num)
			{
				max_num=req.getParaValue(*it_factor);
				selected_it=it_factor;
			}
		}
		return ModifyFactorsList(undealed_factors,dealed_factors,selected_it);
	}

	int ParaS_LV::operator() (std::list<int> &undealed_factors,
							  std::set<int> &dealed_factors,
							  const CTT::CombSet &global_state,
							  const CTT::MixedCoverage &req)
	{
		int min_num=m_max_number;
		std::list<int>::iterator selected_it=undealed_factors.end();
		for(std::list<int>::iterator it_factor=undealed_factors.begin();
			it_factor!=undealed_factors.end();++it_factor)
		{
			MixedCoverage::const_iterator it_req=req.begin();
			for(;it_req!=req.end();++it_req)
				if(it_req->find(*it_factor)!=it_req->end())
					break;
			if(it_req==req.end())continue;

			if(req.getParaValue(*it_factor)<min_num)
			{
				min_num=req.getParaValue(*it_factor);
				selected_it=it_factor;
			}
		}
		return ModifyFactorsList(undealed_factors,dealed_factors,selected_it);
	}

	int ParaS_MR::operator() (std::list<int> &undealed_factors,
							  std::set<int> &dealed_factors,
							  const CTT::CombSet &global_state,
							  const CTT::MixedCoverage &req)
	{
		int max_num=m_min_number;
		std::list<int>::iterator selected_it=undealed_factors.end();
		for(std::list<int>::iterator it_factor=undealed_factors.begin();
			it_factor!=undealed_factors.end();++it_factor)
		{
			int number=0;
			for(MixedCoverage::const_iterator it=req.begin();
				it!=req.end();++it)
			{
				if(it->find(*it_factor)!=it->end())
					++number;
			}
			if(number>max_num && number!=0)
			{
				max_num=number;
				selected_it=it_factor;
			}
		}
		return ModifyFactorsList(undealed_factors,dealed_factors,selected_it);
	}

	int ParaS_LR::operator() (std::list<int> &undealed_factors,
							  std::set<int> &dealed_factors,
							  const CTT::CombSet &global_state,
							  const CTT::MixedCoverage &req)
	{
		int min_num=m_max_number;
		std::list<int>::iterator selected_it=undealed_factors.end();
		for(std::list<int>::iterator it_factor=undealed_factors.begin();
			it_factor!=undealed_factors.end();++it_factor)
		{
			int number=0;
			for(MixedCoverage::const_iterator it=req.begin();
				it!=req.end();++it)
			{
				if(it->find(*it_factor)!=it->end())
					++number;
			}
			if(number<min_num && number!=0)
			{
				min_num=number;
				selected_it=it_factor;
			}
		}
		return ModifyFactorsList(undealed_factors,dealed_factors,selected_it);
	}

	int ParaS_MF::operator() (std::list<int> &undealed_factors,
							  std::set<int> &dealed_factors,
							  const CTT::CombSet &global_state,
							  const CTT::MixedCoverage &req)
	{
		int max_num=m_min_number;
		std::list<int>::iterator selected_it=undealed_factors.end();
		for(std::list<int>::iterator it_factor=undealed_factors.begin();
			it_factor!=undealed_factors.end();++it_factor)
		{
			int number=0;
			for(MixedCoverage::const_iterator it=req.begin();
				it!=req.end();++it)
			{
				if(it->find(*it_factor)!=it->end())
					number+=it->size();
			}
			if(number>max_num && number!=0)
			{
				max_num=number;
				selected_it=it_factor;
			}
		}
		return ModifyFactorsList(undealed_factors,dealed_factors,selected_it);
	}

	int ParaS_LF::operator() (std::list<int> &undealed_factors,
							  std::set<int> &dealed_factors,
							  const CTT::CombSet &global_state,
							  const CTT::MixedCoverage &req)
	{
		int min_num=m_max_number;
		std::list<int>::iterator selected_it=undealed_factors.end();
		for(std::list<int>::iterator it_factor=undealed_factors.begin();
			it_factor!=undealed_factors.end();++it_factor)
		{
			int number=0;
			for(MixedCoverage::const_iterator it=req.begin();
				it!=req.end();++it)
			{
				if(it->find(*it_factor)!=it->end())
					number+=it->size();
			}
			if(number<min_num && number!=0)
			{
				min_num=number;
				selected_it=it_factor;
			}
		}
		return ModifyFactorsList(undealed_factors,dealed_factors,selected_it);
	}

	int ParaS_MC::operator() (std::list<int> &undealed_factors,
							  std::set<int> &dealed_factors,
							  const CTT::CombSet &global_state,
							  const CTT::MixedCoverage &req)
	{
		int max_num=m_min_number;
		std::list<int>::iterator selected_it=undealed_factors.end();
		for(std::list<int>::iterator it_factor=undealed_factors.begin();
			it_factor!=undealed_factors.end();++it_factor)
		{
			int number=0;
			for(MixedCoverage::const_iterator it=req.begin();
				it!=req.end();++it)
			{
				if(it->find(*it_factor)!=it->end())
				{
					number+=global_state.getLocalState(*it).getUncoverNumber();
				}
			}
			if(number>max_num && number!=0)
			{
				max_num=number;
				selected_it=it_factor;
			}
		}
		return ModifyFactorsList(undealed_factors,dealed_factors,selected_it);
	}

	int ParaS_LC::operator() (std::list<int> &undealed_factors,
							  std::set<int> &dealed_factors,
							  const CTT::CombSet &global_state,
							  const CTT::MixedCoverage &req)
	{
		int min_num=m_max_number;
		std::list<int>::iterator selected_it=undealed_factors.end();
		for(std::list<int>::iterator it_factor=undealed_factors.begin();
			it_factor!=undealed_factors.end();++it_factor)
		{
			int number=0;
			for(CTT::MixedCoverage::const_iterator it=req.begin();
				it!=req.end();++it)
			{
				if(it->find(*it_factor)!=it->end())
					number+=global_state.getLocalState(*it).getUncoverNumber();
			}
			if(number<min_num && number!=0)
			{
				min_num=number;
				selected_it=it_factor;
			}
		}
		return ModifyFactorsList(undealed_factors,dealed_factors,selected_it);
	}


	/************************************************
	*当不存在一个因素
	*使得包含它的interaction中存在至少一个已处理因素时
	*选择相应的退化方法进行选择
	*************************************************/
	int ParaS_MAR::operator() (std::list<int> &undealed_factors,
							  std::set<int> &dealed_factors,
							  const CTT::CombSet &global_state,
							  const CTT::MixedCoverage &req)
	{
		int max_num=m_min_number;
		std::list<int>::iterator selected_it=undealed_factors.end();
		for(std::list<int>::iterator it_factor=undealed_factors.begin();
			it_factor!=undealed_factors.end();++it_factor)
		{
			int number=0;
			for(MixedCoverage::const_iterator it=req.begin();
				it!=req.end();++it)
			{
				if(it->find(*it_factor)!=it->end())
				{
					std::set<int>::const_iterator it1=it->begin();
					for(;it1!=it->end();++it1)
						if(dealed_factors.find(*it1)!=dealed_factors.end())
							break;
					if(it1!=dealed_factors.end())
						++number;
				}
			}
			if(number>max_num && number!=0)
			{
				max_num=number;
				selected_it=it_factor;
			}
		}

		if(selected_it==undealed_factors.end())
			return ParaS_MR()(undealed_factors,dealed_factors,global_state,req);
		else
			return ModifyFactorsList(undealed_factors,dealed_factors,selected_it);
	}

	int ParaS_LAR::operator() (std::list<int> &undealed_factors,
							  std::set<int> &dealed_factors,
							  const CTT::CombSet &global_state,
							  const CTT::MixedCoverage &req)
	{
		int min_num=m_max_number;
		std::list<int>::iterator selected_it=undealed_factors.end();
		for(std::list<int>::iterator it_factor=undealed_factors.begin();
			it_factor!=undealed_factors.end();++it_factor)
		{
			int number=0;
			for(MixedCoverage::const_iterator it=req.begin();
				it!=req.end();++it)
			{
				if(it->find(*it_factor)!=it->end())
				{
					std::set<int>::const_iterator it1=it->begin();
					for(;it1!=it->end();++it1)
						if(dealed_factors.find(*it1)!=dealed_factors.end())
							break;
					if(it1!=dealed_factors.end())
						++number;
				}
			}
			if(number<min_num && number!=0)
			{
				min_num=number;
				selected_it=it_factor;
			}
		}
		
		if(selected_it==undealed_factors.end())
			return ParaS_LR()(undealed_factors,dealed_factors,global_state,req);
		else
			return ModifyFactorsList(undealed_factors,dealed_factors,selected_it);
	}

	int ParaS_MAF::operator() (std::list<int> &undealed_factors,
							  std::set<int> &dealed_factors,
							  const CTT::CombSet &global_state,
							  const CTT::MixedCoverage &req)
	{
		int max_num=m_min_number;
		std::list<int>::iterator selected_it=undealed_factors.end();
		for(std::list<int>::iterator it_factor=undealed_factors.begin();
			it_factor!=undealed_factors.end();++it_factor)
		{
			int number=0;
			for(MixedCoverage::const_iterator it=req.begin();
				it!=req.end();++it)
			{
				if(it->find(*it_factor)!=it->end())
				{
					for(std::set<int>::const_iterator it1=it->begin();
						it1!=it->end();++it1)
						if(dealed_factors.find(*it1)!=dealed_factors.end())
							++number;
				}
			}
			if(number>max_num && number!=0)
			{
				max_num=number;
				selected_it=it_factor;
			}
		}
		
		if(selected_it==undealed_factors.end())
			return ParaS_MF()(undealed_factors,dealed_factors,global_state,req);
		else
			return ModifyFactorsList(undealed_factors,dealed_factors,selected_it);
	}

	int ParaS_LAF::operator() (std::list<int> &undealed_factors,
							  std::set<int> &dealed_factors,
							  const CTT::CombSet &global_state,
							  const CTT::MixedCoverage &req)
	{
		int min_num=m_max_number;
		std::list<int>::iterator selected_it=undealed_factors.end();
		for(std::list<int>::iterator it_factor=undealed_factors.begin();
			it_factor!=undealed_factors.end();++it_factor)
		{
			int number=0;
			for(MixedCoverage::const_iterator it=req.begin();
				it!=req.end();++it)
			{
				if(it->find(*it_factor)!=it->end())
				{
					for(std::set<int>::const_iterator it1=it->begin();
						it1!=it->end();++it1)
						if(dealed_factors.find(*it1)!=dealed_factors.end())
							++number;
				}
			}
			if(number<min_num && number!=0)
			{
				min_num=number;
				selected_it=it_factor;
			}
		}
		
		if(selected_it==undealed_factors.end())
			return ParaS_LF()(undealed_factors,dealed_factors,global_state,req);
		else
			return ModifyFactorsList(undealed_factors,dealed_factors,selected_it);
	}

	int ParaS_MAC::operator() (std::list<int> &undealed_factors,
							  std::set<int> &dealed_factors,
							  const CTT::CombSet &global_state,
							  const CTT::MixedCoverage &req)
	{
		int max_num=m_min_number;
		std::list<int>::iterator selected_it=undealed_factors.end();
		for(std::list<int>::iterator it_factor=undealed_factors.begin();
			it_factor!=undealed_factors.end();++it_factor)
		{
			int number=0;
			for(CTT::MixedCoverage::const_iterator it=req.begin();
				it!=req.end();++it)
			{
				if(it->find(*it_factor)!=it->end())
				{
					int num=1;
					for(std::set<int>::const_iterator it1=it->begin();
						it1!=it->end();++it1)
						if(dealed_factors.find(*it1)!=dealed_factors.end())
							num*=req.getParaValue(*it1);
					number+=num;
				}
			}
			if(number>max_num && number!=0)
			{
				max_num=number;
				selected_it=it_factor;
			}
		}
		
		if(selected_it==undealed_factors.end())
			return ParaS_MC()(undealed_factors,dealed_factors,global_state,req);
		else
			return ModifyFactorsList(undealed_factors,dealed_factors,selected_it);
	}

	int ParaS_LAC::operator() (std::list<int> &undealed_factors,
							  std::set<int> &dealed_factors,
							  const CTT::CombSet &global_state,
							  const CTT::MixedCoverage &req)
	{
		int min_num=m_max_number;
		std::list<int>::iterator selected_it=undealed_factors.end();
		for(std::list<int>::iterator it_factor=undealed_factors.begin();
			it_factor!=undealed_factors.end();++it_factor)
		{
			int number=0;
			for(CTT::MixedCoverage::const_iterator it=req.begin();
				it!=req.end();++it)
			{
				if(it->find(*it_factor)!=it->end())
				{
					int num=1;
					for(std::set<int>::const_iterator it1=it->begin();
						it1!=it->end();++it1)
						if(dealed_factors.find(*it1)!=dealed_factors.end())
							num*=req.getParaValue(*it1);
					number+=num;
				}
			}
			if(number<min_num && number!=0)
			{
				min_num=number;
				selected_it=it_factor;
			}
		}
		
		if(selected_it==undealed_factors.end())
			return ParaS_LC()(undealed_factors,dealed_factors,global_state,req);
		else
			return ModifyFactorsList(undealed_factors,dealed_factors,selected_it);
	}

}	//namespace CTT