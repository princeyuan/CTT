#include "BestGreedy.h"

#include <time.h>

namespace CTT
{
	void BestGreedy::InitializeAlgorithm()
	{
		GreedyFrame::InitializeAlgorithm();

		m_cover_num_upper=0;
		for(CombSet::const_iterator it=m_uncover_table->begin();
			it!=m_uncover_table->end();++it)
			++m_cover_num_upper;

		try
		{
			//若解空间可以完全存入内存, 则使用内存模式
			CreateAllCandidates();
			m_in_memory=true;
		}
		catch(...)
		{
			//否则, 不使用内存模式, 每次均重新生成并遍历解空间
			delete m_all_candidates;
			m_in_memory=false;
		}
	}

	void BestGreedy::FinishAlgorithm()
	{
		if(m_in_memory)
			delete m_all_candidates;

		GreedyFrame::FinishAlgorithm();
	}

	void BestGreedy::CreateOneLine(const CoveringArray &array,std::vector<int> &one_line)
	{
		//内存模式运行算法
		if(m_in_memory)
		{
			int max_count=-1;
			CoveringArray::iterator selected=m_all_candidates->end();

			if(array.Size()==0)
			{
				srand(time(NULL));
				int rand_index=rand()%(m_all_candidates->Size());
				selected=m_all_candidates->begin();
				while(--rand_index>=0)
					++selected;
			}
			else
			{
				for(CoveringArray::iterator it=m_all_candidates->begin();
					it!=m_all_candidates->end();++it)
				{
					int count=0;
					for(CombSet::const_iterator its=m_uncover_table->begin();
						its!=m_uncover_table->end();++its)
					{
						int j=-1;
						std::vector<int> temp(its->getParaSet().size());
						for(std::set<int>::const_iterator itp=its->getParaSet().begin();
							itp!=its->getParaSet().end();++itp)
							temp[++j]=(*it)[*itp];
						if(its->getState(temp)!=0)
							++count;
					}

					if(count>max_count)
					{
						max_count=count;
						selected=it;
					}

					if(max_count==m_cover_num_upper)
						break;
				}
			}

			one_line.resize(m_req->getParaNum());
			for(int i=m_req->getParaNum()-1;i>=0;--i)
				one_line[i]=(*selected)[i];
			m_all_candidates->Remove(selected);
			m_cover_num_upper=max_count;
		}
		//非内存模式运行算法
		else
		{
			int max_count=-1;
			one_line.resize(m_req->getParaNum());
			std::vector<int> line_candidate(m_req->getParaNum(),0);

			while(GetNextCandidate(line_candidate))
			{
				int count=0;
				for(CombSet::const_iterator its=m_uncover_table->begin();
					its!=m_uncover_table->end();++its)
				{
					int j=-1;
					std::vector<int> temp(its->getParaSet().size());
					for(std::set<int>::const_iterator itp=its->getParaSet().begin();
						itp!=its->getParaSet().end();++itp)
						temp[++j]=line_candidate[*itp];
					if(its->getState(temp)!=0)
						++count;
				}

				if(count>max_count)
				{
					max_count=count;
					for(int i=m_req->getParaNum()-1;i>=0;--i)
						one_line[i]=line_candidate[i];
				}

				if(max_count==m_cover_num_upper)
					break;
			}
			m_cover_num_upper=max_count;
		}
	}

	void BestGreedy::CreateAllCandidates()
	{
		m_all_candidates=new CoveringArray;

		std::vector<int> line_candidate(m_req->getParaNum(),0);
		while(GetNextCandidate(line_candidate))
		{
			m_all_candidates->Push_Back(line_candidate);
		}

		int *temp=new int[1024];
		delete []temp;
	}

	bool BestGreedy::GetNextCandidate(std::vector<int> &line_candidate)
	{
		for(int i=line_candidate.size()-1;i>=0;--i)
		{
			if(line_candidate[i]+1<m_req->getParaValue(i))
			{
				++line_candidate[i];

				if(i!=line_candidate.size()-1)
				{
					for(int j=line_candidate.size()-1;j>i;--j)
						line_candidate[j]=0;
				}

				return true;
			}
		}

		return false;
	}
}