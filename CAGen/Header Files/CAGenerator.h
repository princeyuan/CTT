#ifndef CA_GENERATOR_H
#define CA_GENERATOR_H

#include "CoveringArray.h"
#include "CombSet.h"

namespace CTT
{
	//Interfaces are provided in sub-classes FSCAGenerator and VSCAGenerator
	class CAGenerator
	{		
	protected:

		//Create covering array for given requirement
		virtual CoveringArray* run()=0;

		//Create covering array for given requirement and given seeds
		virtual CoveringArray* run(const CoveringArray &seed)=0;

	protected:

		CAGenerator()
			:m_uncover_table(NULL)
		{};

		void ModifyUncoverTable(const std::vector<int> &one_line,
								CombSet &global_state);

		bool isLegalSeed(const Requirement &req,const CoveringArray &seed);

		CoveringArray* IllegalSeedHandler();

	protected:

		CombSet *m_uncover_table;

	};	//class VSCAGenerator

}	//namespace CTT

#endif