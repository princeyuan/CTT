#ifndef COVERING_ARRAR_H
#define COVERING_ARRAR_H

#include <list>
#include <vector>
#include <iostream>

namespace CTT
{
	class CoveringArray
	{
	public:

		CoveringArray(int row=0,int col=0);
		CoveringArray(const CoveringArray &array);

		CoveringArray &operator = (const CoveringArray &array);

		typedef std::list<std::vector<int> >::iterator iterator;
		iterator begin() {return m_table.begin();};	
		iterator end()   {return m_table.end();};

		typedef std::list<std::vector<int> >::const_iterator const_iterator;
		const_iterator begin() const {return m_table.begin();};
		const_iterator end()   const {return m_table.end();};

		bool Push_Back(const std::vector<int> &one);
		bool Push_Back(const CoveringArray &array);

		bool Insert(iterator where,const std::vector<int> &one);
		bool Insert(iterator where,const CoveringArray &array);

		void ExtendColumns(int extra_columns_number);

		int Size()   const {return m_size;};
		int Column() const {return m_column;};

		void Clear();
		void Remove(iterator where);

		void Print(std::ostream &out=std::cout) const;

		bool Serialize(const char *filename) const;
		bool deSerialize(const char *filename);

	private:

		std::list<std::vector<int> > m_table;

		int m_size;
		int m_column;

	};//class CoveringArray

}	//namespace CTT

#endif