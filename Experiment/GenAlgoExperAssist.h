#ifndef GEN_ALGO_EXPER_ASSIST_H
#define GEN_ALGO_EXPER_ASSIST_H

#include <set>
#include <vector>
#include <fstream>

//���ı��ļ��ж�ȡinter_num������
/*bool LoadInteractionsFromFile(const std::string &filename,
							  std::vector<std::set<int> > &interactions,
							  int inter_num);*/

//��it_begin��it_end��Χ�ڵļ���д���ı��ļ�
template<class InputIterator1,class InputIterator2>
bool WriteInteractionsToFile(const std::string &filename,
							 InputIterator1 it_begin,
							 InputIterator1 it_end,
							 InputIterator2)
{
	std::ofstream outfile;
	outfile.open(filename.c_str(),std::ios::out);

	if(!outfile)
	{
		std::cerr<<"Can not open file "<<filename<<"!"<<std::endl;
		return false;
	}

	try
	{
		for(InputIterator1 it1=it_begin;it1!=it_end;++it1)
		{
			for(InputIterator2 it2=it1->begin();it2!=it1->end();++it2)
				outfile<<*it2<<' ';
			outfile<<'\n';
		}
	}
	catch(...)
	{
		outfile.close();
		return false;
	}
	
	outfile.close();
	return true;
}

//��it_begin��it_end��Χ�ڵļ�����PICT��submodel�ĸ�ʽд���ı��ļ�
template<class InputIterator1,class InputIterator2>
bool WriteInteractionsAsPictSubmodelFormat(const std::string &filename,
										   InputIterator1 it_begin,
										   InputIterator1 it_end,
										   InputIterator2)
{
	std::ofstream outfile;
	outfile.open(filename.c_str(),std::ios::out);

	if(!outfile)
	{
		std::cerr<<"Can not open file "<<filename<<"!"<<std::endl;
		return false;
	}

	try
	{
		for(InputIterator1 it1=it_begin;it1!=it_end;++it1)
		{
			outfile<<"{ ";
			for(InputIterator2 it2=it1->begin();it2!=it1->end();++it2)
			{
				if(it2!=it1->begin())
					outfile<<" ,";
				outfile<<*it2;
			}
			outfile<<" } @ ";
			outfile<<it1->size();
			outfile<<'\n';
		}
	}
	catch(...)
	{
		outfile.close();
		return false;
	}
	
	outfile.close();
	return true;
}

//��it_begin��it_end��Χ�ڵļ�����TVG��IOR�ĸ�ʽд���ı��ļ�
template<class InputIterator1,class InputIterator2>
bool WriteInteractionsAsTvgIorFormat(const std::string &filename,
									 InputIterator1 it_begin,
									 InputIterator1 it_end,
									 InputIterator2)
{
	std::ofstream outfile;
	outfile.open(filename.c_str(),std::ios::out);

	if(!outfile)
	{
		std::cerr<<"Can not open file "<<filename<<"!"<<std::endl;
		return false;
	}

	try
	{
		int num=1;
		for(InputIterator1 it1=it_begin;it1!=it_end;++it1)
		{
			outfile<<"output"<<num++;
			for(InputIterator2 it2=it1->begin();it2!=it1->end();++it2)
			{
				outfile<<':';
				outfile<<*it2;
			}
			outfile<<'\n';
		}
	}
	catch(...)
	{
		outfile.close();
		return false;
	}
	
	outfile.close();
	return true;
}

#endif