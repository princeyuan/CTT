#ifndef INCREMENT_PRI_H
#define INCREMENT_PRI_H

#include "CoveringArray.h"
#include "FixedCoverage.h"

namespace CTT
{
	//���������������Զ����и�ά��ϲ����������еĲ���������������
	class IncrementPri
	{
	public:

		std::vector<CoveringArray::const_iterator> *operator() (
			const CoveringArray &initial_array,
			const FixedCoverage &req,
			std::list<int> &state);
	};
}

#endif