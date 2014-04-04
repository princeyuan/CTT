#ifndef LOCAL_COMB_SET_H
#define LOCAL_COMB_SET_H

#include <set>
#include <vector>
#include <iostream>
#include "CoveringArray.h"
#include "Requirement.h"

namespace CTT
{
	class LocalCombSet
	{
	public:

		LocalCombSet(const std::set<int> &para_set,const Requirement &req);

		LocalCombSet(const std::set<int> &para_set,const std::vector<int> &parameters);

		//针对一个Coverage Requirement中参数集合的一个子集
		//给出该子集所对应的Coverage Requirement的组合覆盖状态
		//LocalCombSet(const LocalCombSet &initial_state,  //原始覆盖状态集合
		//			 const std::set<int> &sub_para_set,  //因素子集
		//			 const Requirement &req,  //测试需求给出因素取值情况
		//			 bool is_equal_state=true);  //initial_state中覆盖状态是否相同

	public:

		int Size() const {return  m_flags.size();};

		bool Empty() const {return (m_uncover_number==0)?true:false;};

		int getUncoverNumber() const {return m_uncover_number;};

		//判断组合combination被覆盖的状态
		int getState(const std::vector<int> &combination) const;
		//判断编号为index的组合被覆盖的状态
		int getState(int index) const;

		//当该组合已被覆盖一次时, 变更其状态
		bool Remove(const std::vector<int> &combination);
		bool Remove(int index);

		int getIndex(const std::vector<int> &combination) const;
		void getCombination(std::vector<int> &combination,int index) const;

		const std::set<int> &getParaSet() const {return m_para_set;};

		int CoverNewCount(CoveringArray::const_iterator it_begin,
						  CoveringArray::const_iterator it_end) const;

		void ModifyCoverState(const std::vector<int> &test);

		bool isCover(CoveringArray::const_iterator it_begin,
					 CoveringArray::const_iterator it_end) const;

		void Print(std::ostream &out=std::cout) const;

		bool operator< (const LocalCombSet other) const
		{
			return m_para_set<other.getParaSet();
		};

	private:

		//void Initialize_equal(const LocalCombSet &state,int vector_size);
		//void Initialize_unequal(const LocalCombSet &state,int vector_size);

	private:

		std::set<int> m_para_set; //因素集合

		std::vector<int> m_flags; //各组合需被覆盖的次数

		int m_uncover_number;     //状态不为0的组合的数量

	private:

		std::vector<int> m_denominator;//用于内部计算(在编号与具体组合间进行转换)

	};	//class LocalCombSet

}	//namespace CTT

#endif