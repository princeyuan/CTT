#ifndef FS_CA_GENERATOR_H
#define FS_CA_GENERATOR_H

#include "CAGenerator.h"
#include "FixedCoverage.h"

namespace CTT
{
	class FSCAGenerator : public CAGenerator
	{
	public:

		//Interfaces for generating fixed strength covering array without/with seed lines
		//If it is fail to generate covering array, return NULL
		CoveringArray* operator() (const FixedCoverage &req);
		CoveringArray* operator() (const FixedCoverage &req,
								   const CoveringArray &seed);

	protected:

		FSCAGenerator()
			:m_req(NULL)
		{};

	protected:

		const FixedCoverage *m_req;

	};	//class FSCAGenerator

}	//namespace CTT

#endif