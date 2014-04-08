#ifndef REQUIREMENT_H
#define REQUIREMENT_H

#include <set>
#include <vector>
#include <string>
#include <iostream>

namespace CTT
{
    class Requirement
    {
	public:

		int getParaNum() const {return m_paravalues.size();};

		int getParaValue(int index) const {return m_paravalues[index];};

		const std::vector<int> &getAllParameters() const {return m_paravalues;};

		bool IsFixedLevel() const;

		void Print(std::ostream &out=std::cout) const;

	public:

		virtual void CreateAllInters(std::set<std::set<int> > &inters) const =0;

		virtual std::string getReqType() const =0;

	protected:

		Requirement(const std::vector<int> &paravalues);

	private:

		int CheckLegal() const;

		void HandleIllegal(int error_code) const;

	protected:

		std::vector<int> m_paravalues;
 
    };	//class Requirement
    
}	//namespace CTT

#endif