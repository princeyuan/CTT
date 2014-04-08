#include "CoveringArray.h"

#include <string>
#include <iostream>
#include <fstream>
#include "AssistMethod.h"

namespace CTT
{
	CoveringArray::CoveringArray(int row,int col):
		m_size(row),m_column(col)
	{
		if(m_size>0 && m_column>0)
		{
			for(int i=0;i<m_size;++i)
			{
				std::vector<int> temp(m_column,-1);
				m_table.push_back(temp);
			}
		}
	}

	CoveringArray::CoveringArray(const CoveringArray &array):
		m_size(array.Size()),m_column(array.Column())
	{
		for(CoveringArray::const_iterator it=array.begin();it!=array.end();++it)
		{
			m_table.push_back(*it);
		}
	}

	CoveringArray &CoveringArray::operator = (const CoveringArray &array)
	{
		if(this==&array)
		{
			return *this;
		}

		m_table.clear();

		m_size=array.Size();
		m_column=array.Column();
		for(CoveringArray::const_iterator it=array.begin();it!=array.end();++it)
		{
			m_table.push_back(*it);
		}

		return *this;
	}

	bool CoveringArray::Push_Back(const std::vector<int> &one)
	{
		return Insert(end(),one);
	}

	bool CoveringArray::Push_Back(const CoveringArray &array)
	{
		return Insert(end(),array);
	}

	bool CoveringArray::Insert(iterator where,const std::vector<int> &one)
	{
		if((one.size()!=m_column)&&(m_column!=0)&&(m_size!=0))
		{
			return false;
		}
		else
		{
			m_table.insert(where,one);
			++m_size;
			m_column=one.size();
			return true;
		}
	}

	bool CoveringArray::Insert(iterator where,const CoveringArray &array)
	{
		if((array.Column()!=m_column)&&(m_column!=0))
		{
			return false;
		}
		else
		{
			for(CoveringArray::const_iterator it=array.begin();it!=array.end();++it)
			{
				m_table.insert(where,*it);
			}
			m_size=m_size+array.Size();
			if(m_column==0)
			{
				m_column=array.Column();
			}
			return true;
		}
	}

	void CoveringArray::ExtendColumns(int extra_columns_number)
	{
		int new_column_num=m_column+extra_columns_number;
		std::vector<int> temp(m_column);
		for(CoveringArray::iterator it=begin();it!=end();++it)
		{
			for(int i=0;i<m_column;++i)
				temp[i]=(*it)[i];
			it->resize(new_column_num,-1);
			for(int i=0;i<m_column;++i)
				(*it)[i]=temp[i];
		}
		m_column=new_column_num;
	}

	void CoveringArray::Clear()
	{
		m_size=0;
		m_column=0;
		m_table.clear();
	}

	void CoveringArray::Remove(iterator where)
	{
		--m_size;
		m_table.erase(where);
	}

	void CoveringArray::Print(std::ostream &out) const
	{
		int i=0;
		for(CoveringArray::const_iterator it=begin();it!=end();++it)
		{
			out<<++i<<':'<<'\t';
			for(int j=0;j<m_column;++j)
			{
				out<<(*it)[j];
				if(j<m_column-1)
				{
					out<<'\t';
				}
			}
			out<<'\n';
		}
	}

	bool CoveringArray::Serialize(const char *filename) const
	{
		std::ofstream outfile;
		outfile.open(filename,std::ios::out);

		if(!outfile)
		{
			std::cerr<<"Can not open file "<<filename<<"!"<<std::endl;
			return false;
		}

		try
		{
			Print(outfile);
		}
		catch(...)
		{
			outfile.close();
			return false;
		}

		outfile.close();
		return true;
	}

	bool CoveringArray::deSerialize(const char *filename)
	{
		std::ifstream infile;
		infile.open(filename,std::ios::in);

		if(!infile)
		{
			std::cerr<<"Can not open file "<<filename<<"!"<<std::endl;
			return false;
		}

		try
		{
			char buffer[1024];

			while(infile.getline(buffer,1024,'\n'))
			{
				int value;
				char *str=getOneNumFromLine(buffer,value);
				std::vector<int> temp;
				getAllNumFromLine(str,temp);
				m_table.push_back(temp);
			}

			m_size=m_table.size();
			m_column=m_table.begin()->size();
		}
		catch(...)
		{
			infile.close();
			return false;
		}

		infile.close();
		return true;
	}

}	//namespace CTT