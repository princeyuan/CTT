#include "TwoLevel.h"

#include <math.h>
#include "AssistMethod.h"

namespace CTT
{
	CoveringArray* TwoLevel::run()
	{
		if(!IsTwoLevelReq() || !IsTwoStrengthReq())
			return NULL;

		//generate a covering array with size 2^x for first 2(strength=2) parameters
		CoveringArray *p=HandleFirstReq();

		//create a temp vector as the last column of covering array,
		//to store candidate column
		std::vector<int> column_candidate(p->Size());
		InitializeCandidate(column_candidate,*p);

		//extend covering array for each new 2-level parameter
		for(int i=m_req->getStrength();i<m_req->getParaNum();++i)
		{
			bool is_add_ok=false;

			while(!is_add_ok)
			{
				//find the next vector that have equal number of 0 and 1
				while(GetNextCandidate(column_candidate))
				{
					//if such vector satisfy the property of combination coverage
					if(IsFitColumn(*p,column_candidate,i))
					{
						//add such vector as a new column of covering array
						//which has been done in function IsFitColumn
						is_add_ok=true;
						break;
					}
				}

				//if we can not find such a new vector, 
				//which satisfy the property of combination coverage
				if(!is_add_ok)
				{
					//add new lines into covering array
					AddNewLines(*p,i);

					//modify candidate column
					ModifyCandidate(column_candidate,*p);
				}
			}
		}

		return p;
	}

	CoveringArray *TwoLevel::HandleFirstReq()
	{
		int strength=m_req->getStrength();
		int current_size=pow(2,strength);
		CoveringArray *p=new CoveringArray(current_size,m_req->getParaNum());
		int total_round=1;
		for(int i=0;i<strength;++i)
		{
			CoveringArray::iterator it=p->begin();
			for(int j=0;j<total_round;++j)
			{
				//assign 0
				for(int k=0;k<current_size/(total_round*2);++k)
				{
					(*it)[i]=0;
					++it;
				}
				//assign 1
				for(int k=0;k<current_size/(total_round*2);++k)
				{
					(*it)[i]=1;
					++it;
				}
			}

			total_round*=2;
		}
		return p;
	}

	void TwoLevel::InitializeCandidate(std::vector<int> &column_candidate,
									   const CoveringArray &array)
	{
		int j=-1,k=m_req->getStrength()-1;
		for(CoveringArray::const_iterator it=array.begin();it!=array.end();++it)
			column_candidate[++j]=(*it)[k];
	}

	bool TwoLevel::GetNextCandidate(std::vector<int> &column_candidate)
	{
		//获取下一个01数量相等的二进制串
		//Get the next tuple with the same numbers of 0 and 1
		int last=column_candidate.size()-1;

		if(column_candidate[last]==0)
		{
			int i,count=0;
			for(i=last-1;i>=0;--i)
			{
				if(column_candidate[i]==1)
					break;
			}
			for(;i>=0;--i)
			{
				if(column_candidate[i]==0)
					break;
				else
					++count;
			}
			if(i==0)
			{
				return false;
			}
			else
			{
				column_candidate[i]=1;
				int j=last;
				for(;j>last-count+1;--j)
					column_candidate[j]=1;
				for(;j>i;--j)
					column_candidate[j]=0;
				return true;
			}
		}

		if(column_candidate[last]==1)
		{
			int i,count=0;
			for(i=last-1;i>=0;--i)
			{
				if(column_candidate[i]==1)
					++count;
				else
					break;
			}
			column_candidate[i]=1;
			column_candidate[i+1]=0;
			return true;
		}

		return false;
	}

	/*bool TwoLevel::GetNextCandidate(std::vector<int> &column_candidate)
	{
		//按照二进制递增的顺序获取下一个二进制串,不保证01数量相等
		int last=column_candidate.size()-1;

		if(column_candidate[last]==0)
		{
			column_candidate[last]=1;
			return true;
		}

		if(column_candidate[last]==1)
		{
			column_candidate[last]=0;
			for(int i=last-1;i>0;--i)
			{
				if(column_candidate[i]==0)
				{
					column_candidate[i]=1;
					return true;;
				}
				else
				{
					column_candidate[i]=0;
				}
			}
			return false;
		}

		return false;
	}*/

	bool TwoLevel::IsFitColumn(CoveringArray &array,const std::vector<int> &column,int current_para)
	{
		int strength=m_req->getStrength();
		int strength_minus_one=strength-1;

		//add current temp column as a new column of covering array in order to check it
		int i=-1;
		for(CoveringArray::iterator ita=array.begin();ita!=array.end();++ita)
			(*ita)[current_para]=column[++i];
		
		CombSet::const_iterator it=m_uncover_table->begin();
		std::vector<int> part_param_set(strength_minus_one);
		for(int i=0;i<strength_minus_one;++i)
			part_param_set[i]=i;

		do
		{
			//find the local cover state for such parameters
			bool is_found=false;
			while(!is_found)
			{
				int j=0;
				std::set<int>::const_iterator iti=it->getParaSet().begin();
				for(;j<strength_minus_one;++j)
				{
					if(*iti!=part_param_set[j])
						break;
					else
						++iti;
				}
				if(j==strength_minus_one && *iti==current_para)
					is_found=true;
				else
					++it;
			}

			//check if all combinations of such parameters have been covered
			if(it->isCover(array.begin(),array.end()))
				++it;
			else
				return false;
		}
		while(next_combination(part_param_set,current_para,true));

		//all have been checked and passed
		return true;
	}

	void TwoLevel::AddNewLines(CoveringArray &array,int current_para)
	{
		if(m_req->getStrength()==2)
		{
			std::vector<int> line1(m_req->getParaNum(),-1);
			std::vector<int> line2(m_req->getParaNum(),-1);
			for(int i=0;i<current_para;++i)
			{
				line1[i]=0;
				line2[i]=1;
			}
			array.Insert(array.begin(),line1);
			array.Insert(array.end(),line2);
		}

		if(m_req->getStrength()>2)
		{
			std::vector<int> sub_params(current_para,2);
			FixedCoverage sub_req(sub_params,m_req->getStrength()-1);
			TwoLevel sub_gen;
			CoveringArray *sub_array=sub_gen(sub_req);
			sub_array->ExtendColumns(m_req->getParaNum()-current_para);
			int mid=(sub_array->Size())/2;
			CoveringArray::iterator first_it=array.begin();
			CoveringArray::iterator it=sub_array->begin();
			//sub_array->Print();
			for(int i=0;i<mid;++i)
			{
				array.Insert(first_it,*it);
				++it;
			}
			for(;it!=sub_array->end();++it)
			{
				array.Insert(array.end(),*it);
			}
			delete sub_array;
		}
	}

	void TwoLevel::ModifyCandidate(std::vector<int> &column_candidate,const CoveringArray &array)
	{
		column_candidate.resize(array.Size());
		int m=-1,k=m_req->getStrength()-1;
		for(CoveringArray::const_iterator it=array.begin();it!=array.end();++it)
			column_candidate[++m]=(*it)[0];
	}

	bool TwoLevel::IsTwoLevelReq()
	{
		const std::vector<int> &parameters=m_req->getAllParameters();
		for(std::vector<int>::const_iterator it=parameters.begin();
			it!=parameters.end();++it)
			if(*it!=2)
				return false;
		return true;
	}
}