#include "LocalCombSet.h"

namespace CTT
{
	LocalCombSet::LocalCombSet(const std::set<int> &para_set,
							   const Requirement &req)
		:m_para_set(para_set),m_uncover_number(1),m_denominator(m_para_set.size(),0)
	{
		int i=-1;
		for(std::set<int>::const_iterator it=m_para_set.end();
			it!=m_para_set.begin();)
		{
			m_denominator[++i]=m_uncover_number;
			m_uncover_number*=req.getParaValue(*(--it));
		}
		m_flags.resize(m_uncover_number,1);
	}

	LocalCombSet::LocalCombSet(const std::set<int> &para_set,
							   const std::vector<int> &parameters)
		:m_para_set(para_set),m_uncover_number(1),m_denominator(m_para_set.size(),0)
	{
		int i=-1;
		for(std::set<int>::const_iterator it=m_para_set.end();
			it!=m_para_set.begin();)
		{
			m_denominator[++i]=m_uncover_number;
			m_uncover_number*=parameters[*(--it)];
		}
		m_flags.resize(m_uncover_number,1);
	}

	/*LocalCombSet::LocalCombSet(const LocalCombSet &initial_state,
							   const std::set<int> &sub_para_set,
							   const Requirement &req,
							   bool is_equal_state)
		:m_para_set(sub_para_set),m_uncover_number(1),m_denominator(m_para_set.size(),0)
	{
		int i=-1;
		int intemp=1;
		for(std::set<int>::const_iterator it=m_para_set.end();
			it!=m_para_set.begin();)
		{
			m_denominator[++i]=intemp;
			intemp*=req.getParaValue(*(--it));
		}

		if(is_equal_state)
		{
			Initialize_equal(initial_state,intemp);
		}
		else
		{
			Initialize_unequal(initial_state,intemp);
		}
	}*/

	int LocalCombSet::getState(const std::vector<int> &combination) const
	{
		int index=getIndex(combination);
		if(index!=-1)
			return m_flags[index];
		else
			return -1;
	}

	int LocalCombSet::getState(int index) const
	{
		if(index>=0 && index<m_flags.size())
			return m_flags[index];
		else
			return -1;
	}

	bool LocalCombSet::Remove(const std::vector<int> &combination)
	{
		int index=getIndex(combination);
		if(index!=-1)
			return Remove(index);
		else
			return false;
	}

	bool LocalCombSet::Remove(int index)
	{
		if(m_flags[index]>0)
		{
			--m_flags[index];
			if(m_flags[index]==0)
				--m_uncover_number;
			return true;
		}
		else
			return false;
	}

	int LocalCombSet::getIndex(const std::vector<int> &combination) const
	{
		int index=0;
		for(int i=0;i<m_para_set.size();i++)
		{
			int j=m_para_set.size()-1-i;
			if(combination[j]!=-1)
				index=index+(combination[j]*m_denominator[i]);
			else
				return -1;
		}
		return index;
	}

	void LocalCombSet::getCombination(std::vector<int> &combination,int index) const
	{
		combination.resize(m_para_set.size(),-1);

		for(int i=0;i<m_para_set.size();i++)
		{
			int j=m_para_set.size()-1-i;
			combination[i]=index/m_denominator[j];
			index=index%m_denominator[j];
		}
	}

	int LocalCombSet::CoverNewCount(CoveringArray::const_iterator it_begin,
									CoveringArray::const_iterator it_end) const
	{
		std::set<int> covered_indexs;
		std::vector<int> combination(m_para_set.size(),-1);

		for(CoveringArray::const_iterator it=it_begin;it!=it_end;++it)
		{
			int i=-1;
			std::set<int>::const_iterator itp=m_para_set.begin();
			for(;itp!=m_para_set.end();++itp)
				if((*it)[*itp]!=-1)
					combination[++i]=(*it)[*itp];

			if(itp==m_para_set.end())
			{
				int index=getIndex(combination);
				if(index!=-1)
					covered_indexs.insert(index);
			}
		}

		return covered_indexs.size();
	}

	void LocalCombSet::ModifyCoverState(const std::vector<int> &test)
	{
		int i=0;
		std::vector<int> comb(m_para_set.size(),-1);
		std::set<int>::const_iterator it=m_para_set.begin();
		for(;it!=m_para_set.end();++it)
			comb[i++]=test[*it];

		int index=getIndex(comb);
		if(index!=-1)
			Remove(index);
	}

	bool LocalCombSet::isCover(CoveringArray::const_iterator it_begin,
							   CoveringArray::const_iterator it_end) const
	{
		int count=CoverNewCount(it_begin,it_end);
		if(count==Size())
			return true;
		else
			return false;
	}

	void LocalCombSet::Print(std::ostream &out) const
	{
		const std::set<int> &paras=getParaSet();
		out<<"Local Cover State with Parameters:";
		for(std::set<int>::const_iterator it=paras.begin();it!=paras.end();++it)
			out<<" f"<<*it;
		out<<'\n';

		std::vector<int> combination;
		for(int i=0;i<Size();++i)
		{
			out<<"NO. "<<i+1<<"\tcombination is: ";
			getCombination(combination,i);
			for(int j=0;j<m_para_set.size();j++)
				out<<combination[j]<<' ';
			out<<"\tstate is:"<<m_flags[i]<<'\n';
		}
	}

	/*void LocalCombSet::Initialize_equal(const LocalCombSet &initial_state,
										int vector_size)
	{
		int equal_cover_state_num=initial_state.getState(0);
		int multiple=initial_state.Size()/vector_size;
		m_flags.resize(vector_size,equal_cover_state_num*multiple);

		if(equal_cover_state_num!=0)
			m_uncover_number=vector_size;
		else
			m_uncover_number=0;
	}*/

	/*void LocalCombSet::Initialize_unequal(const LocalCombSet &initial_state,
										  int vector_size)
	{
		m_flags.resize(vector_size,-1);

		int i=0;
		int j=-1;
		std::vector<int> locations(m_para_set.size(),-1);
		const std::set<int> &all_paras=initial_state.getParaSet();
		for(std::set<int>::const_iterator it=all_paras.begin();
			it!=all_paras.end();++it)
		{
			if(m_para_set.find(*it)!=m_para_set.end())
				locations[++j]=i;
			++i;
		}

		std::vector<int> visit(initial_state.Size(),0);
		for(i=0;i<Size();i++)
		{
			std::vector<int> small_comb;
			getCombination(small_comb,i);

			for(int j=0;j<initial_state.Size();j++)
			{
				if(visit[j]==0)
				{
					std::vector<int> big_comb;
					initial_state.getCombination(big_comb,j);

					int k=0;
					for(;k<locations.size();k++)
						if(small_comb[k]!=big_comb[locations[k]])
							break;
					if(k==locations.size())
					{
						m_flags[i]+=initial_state.getState(j);
						++visit[j];
					}
				}
			}

			if(getState(i)!=0)
				++m_uncover_number;
		}
	}*/

}	//namespace CTT