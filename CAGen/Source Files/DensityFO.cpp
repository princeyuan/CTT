#include "DensityFO.h"

namespace CTT
{
	void DensityFO::CreateOneLine(const CoveringArray &array,std::vector<int> &one)
	{
		one.resize(m_req->getParaNum(),-1);

		//Create a list of all parameters
		std::list<int> para_cache;
		for(int i=0;i<m_req->getParaNum();i++)
			para_cache.push_back(i);

		while(!para_cache.empty())
		{
			//Select a parameter which have the greatest priority and remove it from para_cache
			int selected_para=SelectOnePara(para_cache,one);

			//Select a value for the selected parameter and fix it
			int select_value=FixOneValue(selected_para,one);
		}
	}

	int DensityFO::SelectOnePara(std::list<int> &para_cache,const std::vector<int> &one)
	{
		//Create a list of density for each coverage requirement
		std::list<float> req_density_table;
		for(CombSet::const_iterator it=m_uncover_table->begin();
			it!=m_uncover_table->end();++it)
		{
			req_density_table.push_back(CalculateReqDensity(*it,one));
		}

		float max_para_density=-1;
		std::list<int>::iterator selected_para_it=para_cache.end();

		//Select the parameter with greatest factor density
		for(std::list<int>::iterator it=para_cache.begin();it!=para_cache.end();++it)
		{
			float para_density=CalculateParaDensity(*it,req_density_table);
			
			if(para_density>max_para_density)
			{
				max_para_density=para_density;
				selected_para_it=it;
			}
		}
		
		int para_index=*selected_para_it;
		para_cache.erase(selected_para_it);
		return para_index;
	}
	
	int DensityFO::FixOneValue(int selected_para,
							   std::vector<int> &one)
	{
		int selected_value=-1;
		float max_value_density=-1;

		for(int i=0;i<m_req->getParaValue(selected_para);i++)
		{
			float value_density=CalculateValueDensity(selected_para,i,one);
			if(max_value_density<value_density)
			{
				selected_value=i;
				max_value_density=value_density;
			}
		}

		one[selected_para]=selected_value;
		return selected_value;
	}

	float DensityFO::CalculateParaDensity(int parameter,
										  const std::list<float> &req_density_table)
	{
		float para_density=0;

		std::list<float>::const_iterator it1=req_density_table.begin();
		CombSet::const_iterator it2=m_uncover_table->begin();
		for(;it1!=req_density_table.end();++it1,++it2)
			if(it2->getParaSet().find(parameter)!=it2->getParaSet().end())
				para_density+=*it1;

		return para_density;
	}

	float DensityFO::CalculateValueDensity(int parameter,int value,
										   const std::vector<int> &one)
	{
		float value_density=0;
		std::vector<int> one_temp(one);
		one_temp[parameter]=value;

		for(CombSet::const_iterator it=m_uncover_table->begin();
			it!=m_uncover_table->end();++it)
		{
			if(it->getParaSet().find(parameter)!=it->getParaSet().end())
			{
				float post_density=CalculateReqDensity(*it,one_temp);
				value_density+=post_density;
			}
		}

		return value_density;
	}

}	//nmespace CTT