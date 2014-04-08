#include "GreedyFrame.h"

namespace CTT
{
	CoveringArray* GreedyFrame::run()
	{
		CoveringArray *p=new CoveringArray(0,m_req->getParaNum());

		InitializeAlgorithm();
		GenerateArray(*p);
		FinishAlgorithm();

		return p;
	}

	CoveringArray* GreedyFrame::run(const CoveringArray &seed)
	{
		CoveringArray *p=new CoveringArray(seed);

		InitializeAlgorithm();
		GenerateArray(*p);
		FinishAlgorithm();

		return p;
	}

	void GreedyFrame::GenerateArray(CoveringArray &array)
	{
		while(!m_uncover_table->Empty())
		{
			std::vector<int> one_line;
			CreateOneLine(array,one_line);
			array.Push_Back(one_line);
			ModifyUncoverTable(one_line,*m_uncover_table);
		}
	}

}	//namespace CTT