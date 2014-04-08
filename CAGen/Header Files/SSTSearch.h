#ifndef SST_SEARCH_H
#define SST_SEARCH_H

#include "FSCAGenerator.h"
#include "PathSelector.h"

namespace CTT
{
	class SSTSearch : public FSCAGenerator
	{
	public:

		//if search_strategy=0, use backtrack strategy one, which is by by L. Shi and C. Nie; 
		//else, use backtrack strategy two, which is by Z. Wang and R. Zhang 
		SSTSearch(CTT::PathSelector *path_selector,
				  int search_strategy=0)
			:m_path_selector(path_selector),m_search_strategy(search_strategy),
			 m_overlap(0),m_visited_node_count(0)
		{};

	protected:

		CoveringArray* run();

		CoveringArray* run(const CoveringArray &seed);

	private:

		void InitializeAlgorithm();

		void GenerateArray(CoveringArray &array);

		void BackTrack_1(int current_para,CoveringArray &array);
		void BackTrack_2(int current_para,CoveringArray &array);

		bool IsFit(const std::vector<int> &current_test,
				   const CoveringArray &array,
				   int current_para);

		void InitializeNodeCounter(){m_visited_node_count=0;};

		void VisitOneNode(){++m_visited_node_count;};

	public:

		int GetActualVisitedNodeCount()
		{
			return m_visited_node_count;
		};

		/*int GetTheoryVisitedNodeCount()
		{
			int count=1;
			for(int i=0;i<m_req->getParaNum();++i)
				count*=m_req->getParaValue(i);
			count*=m_req->getParaNum();
			return count;
		};*/

	private:

		PathSelector *m_path_selector;
		int m_search_strategy;

		int m_overlap;
		int m_visited_node_count;

	};	//class SSTSearch

}	//namespace CTT

#endif