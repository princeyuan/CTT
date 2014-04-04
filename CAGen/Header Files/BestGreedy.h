#ifndef BEST_GREEDY_H
#define BEST_GREEDY_H

#include "GreedyFrame.h"

namespace CTT
{
	class BestGreedy : public GreedyFrame
	{
	public:

		BestGreedy()
			:m_in_memory(false),m_cover_num_upper(0),m_all_candidates(NULL)
		{}

	protected:

		void InitializeAlgorithm();

		void FinishAlgorithm();

		void CreateOneLine(const CoveringArray &array,std::vector<int> &one_line);

	private:

		void CreateAllCandidates();

		bool GetNextCandidate(std::vector<int> &line_candidate);

	private:

		bool m_in_memory;

		int m_cover_num_upper;

		CoveringArray *m_all_candidates;
	};
}

#endif