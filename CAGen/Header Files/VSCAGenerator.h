#ifndef VS_CA_GENERATOR_H
#define VS_CA_GENERATOR_H

#include "CAGenerator.h"
#include "FixedCoverage.h"
#include "FixedPlusCoverage.h"
#include "MixedCoverage.h"

namespace CTT
{
	class VSCAGenerator : public CAGenerator
	{
	public:

		//Interfaces for generating fixed and viriable strength covering array without/with seed lines
		//If it is fail to generate covering array, return NULL

		/* //following are old versions
		CoveringArray* operator() (const FixedCoverage &req);
		CoveringArray* operator() (const FixedPlusCoverage &req);
		CoveringArray* operator() (const MixedCoverage &req);

		CoveringArray* operator() (const FixedCoverage &req,
								   const CoveringArray &seed);
		CoveringArray* operator() (const FixedPlusCoverage &req,
								   const CoveringArray &seed);
		CoveringArray* operator() (const MixedCoverage &req,
								   const CoveringArray &seed);
		*/

		//following are new versions
		CoveringArray* operator() (const Requirement &req);
		CoveringArray* operator() (const Requirement &req,
								   const CoveringArray &seed);

		CoveringArray* operator() (const Requirement &req,
								   const CombSet &required_cover);
		CoveringArray* operator() (const Requirement &req,
								   const CombSet &required_cover,
								   const CoveringArray &seed);

	protected:

		VSCAGenerator()
			:m_req(NULL)
		{};

	protected:

		const MixedCoverage *m_req;

	};	//class VSCAGenerator

}	//namespace CTT

#endif