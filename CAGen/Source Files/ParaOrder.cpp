#include "ParaOrder.h"
#include <algorithm>

namespace CTT
{
	const std::set<int> &ParaOrder::SelectOneReq()
	{
		CombSet::iterator selected=
			(*m_req_selector)(*m_uncover_table,*m_req);
		return selected->getParaSet();
	}

	int ParaOrder::SelectOneFactor(std::set<int> &dealed_factors,
								   std::list<int> &undealed_factors)
	{
		return (*m_param_selector)(undealed_factors,dealed_factors,
								  *m_uncover_table,*m_req);
	}

	void ParaOrder::HandleOneFactor(CoveringArray &array,
									int current_factor,
									const std::set<int> &dealed_factors)
	{
		std::set<std::set<int> > inter_set;
		CreateInvolvedInters(dealed_factors,inter_set,current_factor);
		
		std::set<int> inserted_index;
		CombSet current_comb_set(*m_uncover_table,inter_set);
		HorizontalExtend(array,current_factor,current_comb_set,inserted_index);
		VerticalExtend(array,current_comb_set,inserted_index);
	}

	void ParaOrder::HorizontalExtend(CoveringArray &array,
									 int current_factor,
									 CombSet &current_comb_set,
									 std::set<int> &inserted_index)
	{
		int index=0;
		int last_value=-1;
		std::vector<int> appear_time(m_req->getParaValue(current_factor),0);
		for(CoveringArray::iterator it=array.begin();
			it!=array.end();++it,index++)
		{
			if(current_comb_set.Empty())
				break;

			if(canHorizontalExtend(current_factor,it,current_comb_set))
			{
				int selected_value=SelectValue(current_factor,current_comb_set,
											   it,appear_time,last_value);
				if(selected_value!=-1)
				{
					(*it)[current_factor]=selected_value;
					last_value=selected_value;
					++appear_time[selected_value];
					inserted_index.insert(index);
					ModifyUncoverTable(*it,current_comb_set);
				}
			}
		}
	}

	void ParaOrder::VerticalExtend(CoveringArray &array,
								   CombSet &current_comb_set,
								   std::set<int> &inserted_index)
	{
		if(current_comb_set.Empty())return;

		for(CombSet::iterator it=current_comb_set.begin();
			it!=current_comb_set.end();++it)
		{
			while(!(it->Empty()))
			{
				std::vector<int> combination;
				for(int i=0;i<it->Size();i++)
				{
					while(it->getState(i)!=0)
					{
						it->getCombination(combination,i);
						
						int max_match_degree=-1;
						CoveringArray::iterator max_match_it=array.end();
						int max_match_index,j=0;
						for(CoveringArray::iterator ita=array.begin();
							ita!=array.end();++ita,++j)
						{
							if(inserted_index.find(j)==inserted_index.end())
							{
								int match_degree=
									canInsertComb(combination,it->getParaSet(),*ita);
								if(max_match_degree<match_degree)
								{
									max_match_degree=match_degree;
									max_match_it=ita;
									max_match_index=j;
								}
							}
						}

						if(max_match_it!=array.end())
						{
							int k=0;
							for(std::set<int>::const_iterator it_p=it->getParaSet().begin();
								it_p!=it->getParaSet().end();++it_p)
								(*max_match_it)[*it_p]=combination[k++];

							ModifyUncoverTable(*max_match_it,current_comb_set);
						}
						else
						{
							int k=0;
							std::vector<int> one_line(m_req->getParaNum(),-1);
							for(std::set<int>::const_iterator it_p=it->getParaSet().begin();
								it_p!=it->getParaSet().end();++it_p)
								one_line[*it_p]=combination[k++];

							ModifyUncoverTable(one_line,current_comb_set);
							array.Push_Back(one_line);
						}
					}
				}
			}
		}
	}

	void ParaOrder::CreateInvolvedInters(const std::set<int> &dealed_factors,
										 std::set<std::set<int> > &inter_set,
										 int current_factor)
	{//此时, 当前待处理的因素已被加入集合dealed_fcator

		for(MixedCoverage::const_iterator it=m_req->begin();
			it!=m_req->end();++it)
		{
			if(it->find(current_factor)!=it->end())
			{
				if(includes(dealed_factors.begin(),dealed_factors.end(),
					it->begin(),it->end()))
				{
					inter_set.insert(*it);
				}
			}
		}
	}

	int ParaOrder::CountCoverNum(int current_factor,int value,
								 const CombSet &current_comb_set,
								 const std::vector<int> &one_line)
	{
		int cover_num=0;
		for(CombSet::const_iterator it=current_comb_set.begin();
			it!=current_comb_set.end();++it)
		{
			int j=-1;
			const std::set<int> &params=it->getParaSet();
			std::vector<int> combination(params.size(),-1);
			for(std::set<int>::const_iterator it_1=params.begin();
				it_1!=params.end();++it_1)
			{
				if(*it_1!=current_factor)
					combination[++j]=one_line[*it_1];
				else
					combination[++j]=value;
			}

			if(it->getState(combination)>0)
				++cover_num;
		}
		return cover_num;
	}

	int ParaOrder::SelectValue(int crrent_factor,
							   const CombSet &current_comb_set,
							   const CoveringArray::const_iterator it_array,
							   const std::vector<int> &appear_time,
							   int last_value)
	{
		//统计每一个取值的覆盖数
		int max_cover_num=0;
		std::list<std::pair<int,int> > cover_index_num;
		for(int i=0;i<m_req->getParaValue(crrent_factor);i++)
		{
			int cover_num=CountCoverNum(crrent_factor,i,current_comb_set,*it_array);
			cover_index_num.push_back(std::pair<int,int>(i,cover_num));
			if(max_cover_num<cover_num)
				max_cover_num=cover_num;
		}

		if(max_cover_num==0)
			return -1;

		//找出覆盖数最大的所有取值
		std::list<std::pair<int,int> > max_cover_index_num;
		for(std::list<std::pair<int,int> >::iterator it=cover_index_num.begin();
			it!=cover_index_num.end();++it)
			if(it->second==max_cover_num)
				max_cover_index_num.push_back(*it);

		//若只有一个覆盖数最大的取值, 输出之
		if(max_cover_index_num.size()==1)
			return max_cover_index_num.begin()->first;

		//否则, 统计每一个取值的出现次数
		int min_appear_time=appear_time[max_cover_index_num.begin()->first];
		std::list<std::pair<int,int> > appear_index_time;
		for(std::list<std::pair<int,int> >::iterator it=max_cover_index_num.begin();
			it!=max_cover_index_num.end();++it)
		{
			int appear=appear_time[it->first];
			appear_index_time.push_back(std::pair<int,int>(it->first,appear));
			if(min_appear_time>appear)
				min_appear_time=appear;
		}

		//找出出现次数最少的所有取值
		std::list<std::pair<int,int> > min_appear_index_time;
		for(std::list<std::pair<int,int> >::iterator it=appear_index_time.begin();
			it!=appear_index_time.end();++it)
			if(it->second==min_appear_time)
				min_appear_index_time.push_back(*it);

		//若只有一个出现次数最少的取值, 输出之
		if(min_appear_index_time.size()==1)
			return min_appear_index_time.begin()->first;

		//否则, 找出与上一个取值最为接近的一个值, 输出之
		int min_gap_index=-1;
		int min_gap=m_req->getParaValue(crrent_factor)+1;
		for(std::list<std::pair<int,int> >::iterator it=min_appear_index_time.begin();
			it!=min_appear_index_time.end();++it)
		{
			int gap=(it->first>last_value)?
				(it->first-last_value):(it->first+m_req->getParaValue(crrent_factor)-last_value);
			if(gap<min_gap)
			{
				min_gap=gap;
				min_gap_index=it->first;
			}
		}

		return min_gap_index;
	}

	bool ParaOrder::canHorizontalExtend(int current_factor,
										const CoveringArray::const_iterator it_array,
										const CombSet &current_comb_set)
	{
		for(CombSet::const_iterator it=current_comb_set.begin();
			it!=current_comb_set.end();++it)
		{
			for(std::set<int>::const_iterator it2=it->getParaSet().begin();
				it2!=it->getParaSet().end();++it2)
			{
				if(*it2!=current_factor)
					if((*it_array)[*it2]==-1)
						return false;
			}
		}

		return true;
	}

}	//namespace CTT