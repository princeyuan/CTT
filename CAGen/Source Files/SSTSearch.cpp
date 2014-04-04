#include "SSTSearch.h"

namespace CTT
{
	CoveringArray* SSTSearch::run()
	{
		InitializeAlgorithm();
		CoveringArray *p=new CoveringArray(0,m_req->getParaNum());
		GenerateArray(*p);
		return p;
	}

	CoveringArray* SSTSearch::run(const CoveringArray &seed)
	{
		InitializeAlgorithm();
		CoveringArray *p=new CoveringArray(seed);
		GenerateArray(*p);
		return p;
	}

	void SSTSearch::InitializeAlgorithm()
	{
		InitializeNodeCounter();
		m_overlap=m_req->getStrength()-1;
	}

	void SSTSearch::GenerateArray(CoveringArray &array)
	{
		if(m_search_strategy==0)
		{
			//The original version of solution space tree search algorithm (by L. Shi and C. Nie)
			BackTrack_1(0,array);
		}
		else
		{
			//The improved version of solution space tree search algorithm (by Z. Wang and R. Zhang)
			BackTrack_2(0,array);
		}
	}

	void SSTSearch::BackTrack_1(int current_para,CoveringArray &array)
	{
		static std::vector<int> temp(m_req->getParaNum());

		if(current_para==m_req->getParaNum())
		{
			array.Push_Back(temp);
		}
		else
		{
			int last_value=(current_para==0)?0:temp[current_para-1];
			int *candidates=(*m_path_selector)(*m_req,current_para,last_value);
			int para_value_num=m_req->getParaValue(current_para);
			for(int i=0;i<para_value_num;i++)
			{
				temp[current_para]=candidates[i];
				if(IsFit(temp,array,current_para))
					BackTrack_1(current_para+1,array);
			}
			delete []candidates;
		}
	}

	void SSTSearch::BackTrack_2(int current_para,CoveringArray &array)
	{
		static bool flag=false;
		static std::vector<int> temp(m_req->getParaNum());

		if(current_para==m_req->getParaNum())
		{
			array.Push_Back(temp);
			flag=true;
		}
		else
		{
			int last_value=(current_para==0)?0:temp[current_para-1];
			int *candidates=(*m_path_selector)(*m_req,current_para,last_value);
			int para_value_num=m_req->getParaValue(current_para);
			for(int i=0;i<para_value_num;i++)
			{
				if(flag)
				{
					//After find a test case in the Solution Space Tree, 
					//the depth should fall back to (strength-1) or (overlap),
					//because the overlap between the current test case and the next test case
					//should be less then (strength) or (overlap+1)
					if(current_para>m_overlap)
						break;
					else
						flag=false;
				}

				temp[current_para]=candidates[i];
				if(IsFit(temp,array,current_para))
					BackTrack_2(current_para+1,array);
			}
			delete []candidates;
		}
	}

	bool SSTSearch::IsFit(const std::vector<int> &current_test,
						   const CoveringArray &array,
						   int current_para)
	{
		VisitOneNode();

		for(CoveringArray::const_iterator it=array.begin();
			it!=array.end();++it)
		{
			int current_overlap=0;
			for(int i=0;i<=current_para;i++)
			{
				if(current_test[i]==(*it)[i])
					++current_overlap;
				if(current_overlap>m_overlap)
					return false;
			}
		}
		return true;
	}

}	//namespace CTT