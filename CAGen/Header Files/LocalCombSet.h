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

		//���һ��Coverage Requirement�в������ϵ�һ���Ӽ�
		//�������Ӽ�����Ӧ��Coverage Requirement����ϸ���״̬
		//LocalCombSet(const LocalCombSet &initial_state,  //ԭʼ����״̬����
		//			 const std::set<int> &sub_para_set,  //�����Ӽ�
		//			 const Requirement &req,  //���������������ȡֵ���
		//			 bool is_equal_state=true);  //initial_state�и���״̬�Ƿ���ͬ

	public:

		int Size() const {return  m_flags.size();};

		bool Empty() const {return (m_uncover_number==0)?true:false;};

		int getUncoverNumber() const {return m_uncover_number;};

		//�ж����combination�����ǵ�״̬
		int getState(const std::vector<int> &combination) const;
		//�жϱ��Ϊindex����ϱ����ǵ�״̬
		int getState(int index) const;

		//��������ѱ�����һ��ʱ, �����״̬
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

		std::set<int> m_para_set; //���ؼ���

		std::vector<int> m_flags; //������豻���ǵĴ���

		int m_uncover_number;     //״̬��Ϊ0����ϵ�����

	private:

		std::vector<int> m_denominator;//�����ڲ�����(�ڱ���������ϼ����ת��)

	};	//class LocalCombSet

}	//namespace CTT

#endif