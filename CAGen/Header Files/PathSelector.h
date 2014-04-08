#ifndef PATH_SELECTOR_H
#define PATH_SELECTOR_H

#include "Requirement.h"

namespace CTT
{
	class PathSelector
	{
	public:
		virtual int *operator ()(const Requirement &req,int para,int last_value)=0;
	};

	class PathS_Forward : public PathSelector
	{
	public:
		int *operator ()(const Requirement &req,int para,int last_value);
	};

	class PathS_Backward : public PathSelector
	{
	public:
		int *operator ()(const Requirement &req,int para,int last_value);
	};

	class PathS_Greater : public PathSelector
	{
	public:
		int *operator ()(const Requirement &req,int para,int last_value);
	};

	class PathS_Less : public PathSelector
	{
	public:
		int *operator ()(const Requirement &req,int para,int last_value);
	};
}

#endif