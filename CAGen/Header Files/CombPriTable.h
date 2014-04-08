#ifndef COMB_PRI_TABLE_H
#define COMB_PRI_TABLE_H

#include <map>
#include <set>
#include <vector>
#include "CombSet.h"
#include "Requirement.h"

namespace CTT
{
	class CombPriTable
	{
	public:

		CombPriTable(const Requirement &req);

		int Size() const {return m_table.size();};

		float CoverCount(const std::vector<int> &test,const CombSet &comb_set) const;

		float CoverNewCount(const std::vector<int> &test,
							const CombSet &comb_set) const;

		std::vector<float> &getLocalTable(const std::set<int> &param_set);
		const std::vector<float> &getLocalTable(const std::set<int> &param_set) const;

	public:

		typedef std::map<std::set<int>,std::vector<float> >::iterator iterator;
		iterator begin() {return m_table.begin();};
		iterator end()   {return m_table.end();};

		typedef std::map<std::set<int>,std::vector<float> >::const_iterator const_iterator;
		const_iterator begin() const {return m_table.begin();};
		const_iterator end() const   {return m_table.end();};

	private:

		std::map<std::set<int>,std::vector<float> > m_table;
	};
}

#endif