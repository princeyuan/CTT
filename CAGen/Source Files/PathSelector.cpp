#include "PathSelector.h"

namespace CTT
{
	int *PathS_Forward::operator ()(const Requirement &req,int para,int last_value)
	{
		int *vec=new int[req.getParaValue(para)];
		for(int i=0;i<req.getParaValue(para);i++)
			vec[i]=i;
		return vec;
	}

	int *PathS_Backward::operator ()(const Requirement &req,int para,int last_value)
	{
		int *vec=new int[req.getParaValue(para)];
		for(int i=req.getParaValue(para)-1;i>=0;i--)
			vec[i]=i;
		return vec;
	}

	int *PathS_Greater::operator ()(const Requirement &req,int para,int last_value)
	{
		int *vec=new int[req.getParaValue(para)];
		if(para==0)
		{
			for(int i=0;i<req.getParaValue(para);i++)
				vec[i]=i;
		}
		else
		{
			for(int i=0;i<req.getParaValue(para);i++)
				vec[i]=(last_value+i)%req.getParaValue(para);
		}
		return vec;
	}

	int *PathS_Less::operator ()(const Requirement &req,int para,int last_value)
	{
		int *vec=new int[req.getParaValue(para)];
		if(para==0)
		{
			for(int i=req.getParaValue(para)-1;i>=0;i--)
				vec[i]=i;
		}
		else
		{
			for(int i=req.getParaValue(para);i>0;i--)
				vec[i]=(last_value+i)%req.getParaValue(para);
		}
		return vec;
	}
}