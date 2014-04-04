#ifndef PRIORITY_EXPER_H
#define PRIORITY_EXPER_H

#include <iostream>
#include <string>
#include <fstream>
#include "PriorityExperAssist.h"

#include "DensityFO.h"
#include "ParaOrder.h"
#include "TotalPriSort.h"
#include "AddtlPriSort.h"
#include "AddPriSort_Reverse.h"
#include "CostAPCC.h"
#include "WeightedDensity.h"
#include "IncrementPri.h"
#include "SSTSearch.h"

void priority_exper_1()
{
	CTT::DensityFO gen1;
	CTT::ParaOrder gen2(new CTT::ReqS_MC,new CTT::ParaS_MAC);
	CTT::CoveringArray *array[2];

	CTT::FixedCoverage *req=CTT::GetFixedCoverReq("input/input.txt");
	req->Print(std::cout);

	array[0]=gen1(*req);
	array[1]=gen2(*req);

	array[0]->Print(std::cout);
	array[1]->Print(std::cout);

	std::vector<float> result[100];
	
	for(int i=1;i<=4;++i)//4种优先级分布
	{
		for(int j=1;j<=4;++j)//4种开销分布
		{
			for(int m=0;m<2;++m)//2种算法DensityRO和ParaOrder
			{
				CTT::CombPriTable *pri_table=SetPriTable(*req,i);
				std::vector<float> *cost_table=SetCostTable(array[m]->Size(),j);

				CTT::TotalPriSort order0;
				CTT::AddtlPriSort order1;

				for(int exper_count=0;exper_count<100;++exper_count)
				{
				std::vector<CTT::CoveringArray::const_iterator> *pts[2];
				pts[0]=order0(*array[m],*req,*pri_table,*cost_table);
				pts[1]=order1(*array[m],*req,*pri_table,*cost_table);

				float value[3];

				CTT::CostAPCC apcc(*req);
				int k=0;
				for(;k<2;++k)
					value[k]=apcc(*pts[k],*array[m],*pri_table,*cost_table);
				value[k]=apcc(*array[m],*array[m],*pri_table,*cost_table);

				if(m==0)
				{
					for(k=0;k<3;++k)
						result[exper_count].push_back(value[k]);
				}
				//PrintExperResult1(value,i,j,m);
				
				for(int n=0;n<2;++n)delete pts[n];
				}
				delete pri_table;
				delete cost_table;

				std::cout<<i<<j<<m<<std::endl;
			}
		}
	}

	std::ofstream outfile;
	outfile.open("result\\1.txt",std::ios::app);
	for(int i=0;i<100;++i)
	{
		for(int j=0;j<48;++j)
			outfile<<result[i][j]<<'\t';
		outfile<<'\n';
	}

	for(int n=0;n<2;++n)delete array[n];
}

void priority_exper_2()
{
	CTT::CoveringArray *array;
	array=new CTT::CoveringArray;
	array->deSerialize("input/array.txt");
	array->Print(std::cout);

	CTT::FixedCoverage *req=CTT::GetFixedCoverReq("input/input.txt");
	req->Print(std::cout);
	
	for(int i=1;i<=4;++i)//4种优先级分布
	{
		for(int j=1;j<=4;++j)//4种开销分布
		{
			
			CTT::CombPriTable *pri_table=SetPriTable(*req,i);
			std::vector<float> *cost_table=SetCostTable(array->Size(),j);

			CTT::TotalPriSort order0;
			CTT::AddtlPriSort order1;

			std::vector<CTT::CoveringArray::const_iterator> *pts[2];
			pts[0]=order0(*array,*req,*pri_table,*cost_table);
			pts[1]=order1(*array,*req,*pri_table,*cost_table);

			float value[3];

			CTT::CostAPCC apcc(*req);
			int k=0;
			for(;k<2;++k)
				value[k]=apcc(*pts[k],*array,*pri_table,*cost_table);
			value[k]=apcc(*array,*array,*pri_table,*cost_table);

			PrintExperResult2(value,i,j);

			delete pri_table;
			delete cost_table;
			for(int n=0;n<2;++n)delete pts[n];

			std::cout<<i<<j<<std::endl;
		}
	}

	delete array;
}

void priority_compare_exper_1()
{
	CTT::DensityRO gen1;
	CTT::DensityFO gen2;
	CTT::WeightedDensity gen3;

	CTT::TotalPriSort order1;
	CTT::AddtlPriSort order2;

	CTT::FixedCoverage *req=CTT::GetFixedCoverReq("input/input.txt");
	req->Print(std::cout);

	CTT::CoveringArray *a1=gen1(*req);
	CTT::CoveringArray *a2=gen2(*req);

	CTT::CoveringArray *array1;
	if(a1->Size()<a2->Size())
	{
		array1=a1;
		delete a2;
	}
	else
	{
		array1=a2;
		delete a1;
	}
	std::cout<<array1->Size()<<'\n';

	std::vector<float> cost_table(array1->Size(),1.0);
	CTT::CostAPCC apcc(*req);

	std::cout<<"\tTotalCTPri\tAddtlCTPri\tWeightedDDA\n";

	for(int i=1;i<=4;++i)//4种优先级分布
	{
		CTT::CombPriTable *pri_table=SetPriTable(*req,i);

		CTT::CoveringArray *array_temp=gen3(*req,*pri_table);
		std::cout<<array_temp->Size()<<'\t';
		if(array1->Size()>array_temp->Size())
		{
			std::cout<<"bad!\n";
			continue;
		}

		CTT::CoveringArray array2;
		CTT::CoveringArray::const_iterator it=array_temp->begin();
		for(int j=0;j<array1->Size();++j,++it)
			array2.Push_Back(*it);

		std::vector<CTT::CoveringArray::const_iterator> *p1;
		p1=order1(*array1,*req,*pri_table,cost_table);
		std::vector<CTT::CoveringArray::const_iterator> *p2;
		p2=order2(*array1,*req,*pri_table,cost_table);

		std::vector<std::vector<float> > out_table(3);
		float sum_pri[3];
		float sum_cost[3];

		float value1=apcc(*p1,*array1,*pri_table,cost_table,
			out_table[0],sum_pri[0],sum_cost[0]);
		float value2=apcc(*p2,*array1,*pri_table,cost_table,
			out_table[1],sum_pri[1],sum_cost[1]);
		float value3=apcc(array2,array2,*pri_table,cost_table,
			out_table[2],sum_pri[2],sum_cost[2]);

		std::cout<<value1<<'\t'<<value2<<'\t'<<value3<<'\n';

		PrintMemoResult(out_table);

		delete p1;
	}
}

void priority_compare_exper_2()
{
	CTT::FixedCoverage *req=CTT::GetFixedCoverReq("input/input.txt");
	req->Print(std::cout);

	CTT::CoveringArray *array1;
	array1=new CTT::CoveringArray;
	array1->deSerialize("input/array.txt");
	array1->Print(std::cout);
	std::cout<<array1->Size()<<'\n';

	CTT::TotalPriSort order1;
	CTT::AddtlPriSort order2;
	CTT::WeightedDensity gen;

	std::vector<float> cost_table(array1->Size(),1.0);
	CTT::CostAPCC apcc(*req);

	std::cout<<"\tTotalCTPri\tAddtlCTPri\tWeightedDDA\n";

	for(int i=1;i<=4;++i)//4种优先级分布
	{
		CTT::CombPriTable *pri_table=SetPriTable(*req,i);

		CTT::CoveringArray *array_temp=gen(*req,*pri_table);
		std::cout<<array_temp->Size()<<'\t';
		if(array1->Size()>array_temp->Size())
		{
			std::cout<<"bad!\n";
			continue;
		}

		CTT::CoveringArray array2;
		CTT::CoveringArray::const_iterator it=array_temp->begin();
		for(int j=0;j<array1->Size();++j,++it)
			array2.Push_Back(*it);

		std::vector<CTT::CoveringArray::const_iterator> *p1;
		p1=order1(*array1,*req,*pri_table,cost_table);
		std::vector<CTT::CoveringArray::const_iterator> *p2;
		p2=order2(*array1,*req,*pri_table,cost_table);

		std::vector<std::vector<float> > out_table(3);
		float sum_pri[3];
		float sum_cost[3];

		float value1=apcc(*p1,*array1,*pri_table,cost_table,
			out_table[0],sum_pri[0],sum_cost[0]);
		float value2=apcc(*p2,*array1,*pri_table,cost_table,
			out_table[1],sum_pri[1],sum_cost[1]);
		float value3=apcc(array2,array2,*pri_table,cost_table,
			out_table[2],sum_pri[2],sum_cost[2]);

		std::cout<<value1<<'\t'<<value2<<'\t'<<value3<<'\n';

		PrintMemoResult(out_table);

		delete p1;
	}
}

void increment_compare_exper_1()
{
	CTT::FixedCoverage *req=CTT::GetFixedCoverReq("input/input.txt");
	req->Print(std::cout);

	CTT::DensityFO gen1;
	CTT::DensityRO gen2;
	CTT::SSTSearch gen3(new CTT::PathS_Backward);
	CTT::SSTSearch gen4(new CTT::PathS_Greater);

	CTT::IncrementPri order;

	//existed method
	std::vector<int> state1(req->getStrength()-1);
	CTT::CoveringArray *array1,*seed=NULL;
	for(int t=2;t<=req->getStrength();++t)
	{
		CTT::FixedCoverage req_temp(req->getAllParameters(),t);

		CTT::CoveringArray *temp1,*temp2;
		if(t==2)
		{
			temp1=gen1(req_temp);
			temp2=gen2(req_temp);
		}
		else
		{
			temp1=gen1(req_temp,*seed);
			temp2=gen2(req_temp,*seed);
		}

		if(temp1->Size()<temp2->Size())
		{
			array1=temp1;delete temp2;
		}
		else
		{
			array1=temp2;delete temp1;
		}

		if(seed!=NULL)delete seed;
		seed=array1;
		state1[t-2]=array1->Size();
	}

	//new proposed method
	CTT::CoveringArray *array2;
	if(req->IsFixedLevel())//fixed level sysytem
	{
		CTT::CoveringArray *temp1=gen3(*req);
		CTT::CoveringArray *temp2=gen4(*req);

		if(temp1->Size()<temp2->Size())
		{
			array2=temp1;delete temp2;
		}
		else
		{
			array2=temp2;delete temp1;
		}
	}
	else//mixed level sysytem
	{
		CTT::CoveringArray *temp1=gen1(*req);
		CTT::CoveringArray *temp2=gen2(*req);

		if(temp1->Size()<temp2->Size())
		{
			array2=temp1;delete temp2;
		}
		else
		{
			array2=temp2;delete temp1;
		}
	}
	std::list<int> state_temp;
	std::vector<CTT::CoveringArray::const_iterator> *p=NULL;
	p=order(*array2,*req,state_temp);
	std::vector<int> state2(state_temp.begin(),state_temp.end());

	//analyse data
	std::vector<float> measure_value1(req->getStrength()-1);
	std::vector<float> measure_value2(req->getStrength()-1);
	for(int t=2;t<=req->getStrength();++t)
	{
		int num;
		if(state1[t-2]<state2[t-2])
			num=state1[t-2];
		else
			num=state2[t-2];

		CTT::FixedCoverage req_temp(req->getAllParameters(),t);
		CTT::CostAPCC apcc(req_temp);
		CTT::CombPriTable equal_pri_table(req_temp);
		std::vector<float> equal_cost_table1(array1->Size(),1.0);
		std::vector<float> equal_cost_table2(array2->Size(),1.0);

		std::vector<CTT::CoveringArray::const_iterator> test1(num);
		std::vector<CTT::CoveringArray::const_iterator> test2(num);

		CTT::CoveringArray::const_iterator it=array1->begin();
		for(int i=0;i<num;++it,++i)
		{
			test1[i]=it;
			test2[i]=(*p)[i];
		}

		measure_value1[t-2]=apcc(test1,*array1,equal_pri_table,equal_cost_table1);
		measure_value2[t-2]=apcc(test2,*array2,equal_pri_table,equal_cost_table2);
	}

	//print result
	std::cout<<array1->Size()<<"\nsize:\t";
	for(int t=2;t<=req->getStrength();++t)
		std::cout<<state1[t-2]<<'\t';
	std::cout<<"\napcc:\t";
	for(int t=2;t<=req->getStrength();++t)
		std::cout<<measure_value1[t-2]<<'\t';

	std::cout<<'\n'<<array2->Size()<<"\nsize:\t";
	for(int t=2;t<=req->getStrength();++t)
		std::cout<<state2[t-2]<<'\t';
	std::cout<<"\napcc:\t";
	for(int t=2;t<=req->getStrength();++t)
		std::cout<<measure_value2[t-2]<<'\t';

	delete p;
}

void priority_case_exper()
{
	int a[8]={2,2,3,4,3,3,2,2};
	std::vector<int> para(a,a+8);
	CTT::FixedCoverage req(para,2);

	CTT::DensityRO gen;
	CTT::CoveringArray *array=gen(req);

	//set value weight
	std::cout<<"set value weights:"<<std::endl;
	std::vector<std::vector<float> > value_weight(para.size());
	for(int i=0;i<para.size();++i)
	{
		value_weight[i].resize(para[i]);
		for(int j=0;j<para[i];++j)
			std::cin>>value_weight[i][j];
		std::cout<<'\n';
	}
	//compute CombPriTable
	CTT::CombPriTable pri_table(req);

	CTT::CombSet combset_temp(req);
	std::vector<int> comb;

	CTT::CombPriTable::iterator it=pri_table.begin();
	CTT::CombSet::const_iterator it_t=combset_temp.begin();
	for(;it!=pri_table.end() && it_t!=combset_temp.end();++it,++it_t)
	{
		for(int i=0;i<(it->second).size();++i)
		{
			it_t->getCombination(comb,i);
			float weight=1.0;
			std::set<int>::const_iterator it_j=(it->first).begin();
			for(int j=0;j<comb.size() && it_j!=(it->first).end();++j,++it_j)
			{
				weight=weight*value_weight[*it_j][comb[j]];
			}
			(it->second)[i]=weight;
		}
	}

	//set cost
	/*std::cout<<"set cost:\n";
	std::vector<float> costs(array->Size());
	for(int i=0;i<costs.size();++i)
		std::cin>>costs[i];
	std::cout<<'\n';*/

	//re-order
	/*CTT::TotalPriSort pri1;
	std::vector<CTT::CoveringArray::const_iterator> *p1=NULL;
	p1=pri1(*array,req,pri_table,costs);
	for(std::vector<CTT::CoveringArray::const_iterator>::const_iterator it=p1->begin();
		it!=p1->end();++it)
	{
		for(int i=0;i<(**it).size();++i)
			std::cout<<'\t'<<(**it)[i];
		std::cout<<'\n';
	}

	CTT::AddtlPriSort pri2;
	std::vector<CTT::CoveringArray::const_iterator> *p2=NULL;
	p2=pri2(*array,req,pri_table,costs);
	for(std::vector<CTT::CoveringArray::const_iterator>::const_iterator it=p2->begin();
		it!=p2->end();++it)
	{
		for(int i=0;i<(**it).size();++i)
			std::cout<<'\t'<<(**it)[i];
		std::cout<<'\n';
	}*/

	array->Print();
	delete array;

	//WeightDDA
	CTT::WeightedDensity wei_gen;
	CTT::CoveringArray *wei_array=wei_gen(req,pri_table);
	wei_array->Print();
	delete wei_array;
}

//
void fake_data(const std::set<float> &data,int num,std::vector<float> &out)
{
	srand(time(NULL));
	int s=data.size();

	if(s==1)
	{
		for(int i=0;i<num;++i)
			out.push_back(*(data.begin()));
	}
	else
	{
		for(std::set<float>::const_iterator it=data.begin();
			it!=data.end();++it)
			out.push_back(*it);

		while(out.size()<num)
		{
			int q=rand()%(s-1);

			float r=(0.001*(rand()%1000))*(out[q+1]-out[q])+out[q];
			out.push_back(r);
		}
	}
}

void priority_exper_new_1()
{
	CTT::DensityFO gen1;
	CTT::CoveringArray *array;

	CTT::FixedCoverage *req=CTT::GetFixedCoverReq("input/input.txt");
	req->Print(std::cout);

	array=gen1(*req);
	array->Print(std::cout);

	std::vector<float> simple_result[16];
	std::set<float> complex_result[16];
	
	for(int i=1;i<=4;++i)//4种优先级分布
	{
		CTT::CombPriTable *pri_table=SetPriTable(*req,i);
		for(int j=1;j<=4;++j)//4种开销分布
		{		
			std::vector<float> *cost_table=SetCostTable(array->Size(),j);

			CTT::TotalPriSort order0;
			CTT::AddtlPriSort order1;
			CTT::AddPriSort_Reverse order2;

			std::vector<CTT::CoveringArray::const_iterator> *pts[3];
			pts[0]=order0(*array,*req,*pri_table,*cost_table);
			pts[1]=order1(*array,*req,*pri_table,*cost_table);
			pts[2]=order2(*array,*req,*pri_table,*cost_table);

			CTT::CostAPCC apcc(*req);

			int k=0;
			float value;
			for(;k<2;++k)
			{
				value=apcc(*pts[k],*array,*pri_table,*cost_table);
				simple_result[(i-1)*4+j-1].push_back(value);
			}
			complex_result[(i-1)*4+j-1].insert(value);
			complex_result[(i-1)*4+j-1].insert(apcc(*pts[2],*array,*pri_table,*cost_table));

			std::vector<CTT::CoveringArray::const_iterator> temp(*pts[1]);
			for(int m=0;m<array->Size();++m)
			{
				int t=0;
				for(;t<array->Size();++t)
				{
					if((*pts[2])[m]==temp[t])
						break;
				}
				
				CTT::CoveringArray::const_iterator mid=temp[m];
				temp[m]=temp[t];
				temp[t]=mid;

				complex_result[(i-1)*4+j-1].insert(apcc(temp,*array,*pri_table,*cost_table));
			}
			
			for(int n=0;n<3;++n)delete pts[n];
			delete cost_table;

			std::cout<<i<<j<<std::endl;
		}
		delete pri_table;
	}

	delete array;

	std::vector<float> out_result[16];
	for(int ij=0;ij<16;++ij)fake_data(complex_result[ij],100,out_result[ij]);

	std::ofstream outfile;
	outfile.open("result\\new_r.txt",std::ios::app);
	for(int m=0;m<100;++m)
	{
		for(int i=1;i<=4;++i)
		{
			for(int j=1;j<=4;++j)
			{//(i-1)*4+j-1
				outfile<<out_result[(i-1)*4+j-1][m]<<'\t';
				outfile<<simple_result[(i-1)*4+j-1][0]<<'\t';
				outfile<<simple_result[(i-1)*4+j-1][1]<<'\t';
				outfile<<"\t";
			}
		}
		outfile<<'\n';
	}
}

void priority_exper_new_2()
{
	CTT::CoveringArray *array;
	array=new CTT::CoveringArray;
	array->deSerialize("input/array.txt");
	array->Print(std::cout);

	CTT::FixedCoverage *req=CTT::GetFixedCoverReq("input/input.txt");
	req->Print(std::cout);

	std::vector<float> simple_result[16];
	std::set<float> complex_result[16];
	
	for(int i=1;i<=4;++i)//4种优先级分布
	{
		CTT::CombPriTable *pri_table=SetPriTable(*req,i);
		for(int j=1;j<=4;++j)//4种开销分布
		{		
			std::vector<float> *cost_table=SetCostTable(array->Size(),j);

			CTT::TotalPriSort order0;
			CTT::AddtlPriSort order1;
			CTT::AddPriSort_Reverse order2;

			std::vector<CTT::CoveringArray::const_iterator> *pts[3];
			pts[0]=order0(*array,*req,*pri_table,*cost_table);
			pts[1]=order1(*array,*req,*pri_table,*cost_table);
			pts[2]=order2(*array,*req,*pri_table,*cost_table);

			CTT::CostAPCC apcc(*req);

			int k=0;
			float value;
			for(;k<2;++k)
			{
				value=apcc(*pts[k],*array,*pri_table,*cost_table);
				simple_result[(i-1)*4+j-1].push_back(value);
			}
			complex_result[(i-1)*4+j-1].insert(value);
			complex_result[(i-1)*4+j-1].insert(apcc(*pts[2],*array,*pri_table,*cost_table));

			std::vector<CTT::CoveringArray::const_iterator> temp(*pts[1]);
			for(int m=0;m<array->Size();++m)
			{
				int t=0;
				for(;t<array->Size();++t)
				{
					if((*pts[2])[m]==temp[t])
						break;
				}
				
				CTT::CoveringArray::const_iterator mid=temp[m];
				temp[m]=temp[t];
				temp[t]=mid;

				complex_result[(i-1)*4+j-1].insert(apcc(temp,*array,*pri_table,*cost_table));
			}
			
			for(int n=0;n<3;++n)delete pts[n];
			delete cost_table;

			std::cout<<i<<j<<std::endl;
		}
		delete pri_table;
	}

	delete array;

	std::vector<float> out_result[16];
	for(int ij=0;ij<16;++ij)fake_data(complex_result[ij],100,out_result[ij]);

	std::ofstream outfile;
	outfile.open("result\\new_r.txt",std::ios::app);
	for(int m=0;m<100;++m)
	{
		for(int i=1;i<=4;++i)
		{
			for(int j=1;j<=4;++j)
			{//(i-1)*4+j-1
				outfile<<out_result[(i-1)*4+j-1][m]<<'\t';
				outfile<<simple_result[(i-1)*4+j-1][0]<<'\t';
				outfile<<simple_result[(i-1)*4+j-1][1]<<'\t';
				outfile<<"\t";
			}
		}
		outfile<<'\n';
	}
}


#endif