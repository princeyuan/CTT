#include "VSCAGenerator.h"

#include <iostream>

namespace  CTT
{
	/* //old versions
	CoveringArray* VSCAGenerator::operator() (const FixedCoverage &req)
	{
		m_req=new MixedCoverage(req);
		m_uncover_table=new CombSet(*m_req);

		CoveringArray *p=run();

		delete m_uncover_table;
		m_uncover_table=NULL;
		delete m_req;
		m_req=NULL;
		return p;
	}

	CoveringArray* VSCAGenerator::operator() (const FixedPlusCoverage &req)
	{
		m_req=new MixedCoverage(req);
		m_uncover_table=new CombSet(*m_req);

		CoveringArray *p=run();

		delete m_uncover_table;
		m_uncover_table=NULL;
		delete m_req;
		m_req=NULL;
		return p;
	}

	CoveringArray* VSCAGenerator::operator() (const MixedCoverage &req)
	{
		m_req=&req;
		m_uncover_table=new CombSet(*m_req);

		CoveringArray *p=run();

		delete m_uncover_table;
		m_uncover_table=NULL;
		m_req=NULL;
		return p;
	}

	CoveringArray* VSCAGenerator::operator() (const FixedCoverage &req,
											  const CoveringArray &seed)
	{
		if(isLegalSeed(req,seed))
		{
			m_have_seed=true;
			m_req=new MixedCoverage(req);
			m_uncover_table=new CombSet(*m_req);
			for(CoveringArray::const_iterator it=seed.begin();
				it!=seed.end();++it)
				ModifyUncoverTable(*it,*m_uncover_table);

			CoveringArray *p=run(seed);

			delete m_uncover_table;
			m_uncover_table=NULL;
			delete m_req;
			m_req=NULL;
			m_have_seed=false;
			return p;
		}
		else
			return IllegalSeedHandler();
	}

	CoveringArray* VSCAGenerator::operator() (const FixedPlusCoverage &req,
											  const CoveringArray &seed)
	{
		if(isLegalSeed(req,seed))
		{
			m_have_seed=true;
			m_req=new MixedCoverage(req);
			m_uncover_table=new CombSet(*m_req);
			for(CoveringArray::const_iterator it=seed.begin();
				it!=seed.end();++it)
				ModifyUncoverTable(*it,*m_uncover_table);

			CoveringArray *p=run(seed);

			delete m_uncover_table;
			m_uncover_table=NULL;
			delete m_req;
			m_req=NULL;
			m_have_seed=false;
			return p;
		}
		else
			return IllegalSeedHandler();
	}

	CoveringArray* VSCAGenerator::operator() (const MixedCoverage &req,
											  const CoveringArray &seed)
	{
		if(isLegalSeed(req,seed))
		{
			m_have_seed=true;
			m_req=&req;
			m_uncover_table=new CombSet(*m_req);
			for(CoveringArray::const_iterator it=seed.begin();
				it!=seed.end();++it)
				ModifyUncoverTable(*it,*m_uncover_table);

			CoveringArray *p=run(seed);

			delete m_uncover_table;
			m_uncover_table=NULL;
			m_req=NULL;
			m_have_seed=false;
			return p;
		}
		else
			return IllegalSeedHandler();
	}
	*/

	//new versions
	CoveringArray* VSCAGenerator::operator() (const Requirement &req)
	{
		if(strcmp(req.getReqType().c_str(),"MixedCoverage") != 0)
			m_req=new MixedCoverage(req);
		else
			m_req=dynamic_cast<const MixedCoverage*>(&req);
		if(m_req==NULL)
			return NULL;
		m_uncover_table=new CombSet(*m_req);

		CoveringArray *p=run();

		delete m_uncover_table;
		m_uncover_table=NULL;
		if(strcmp(req.getReqType().c_str(),"MixedCoverage") != 0)
			delete m_req;
		m_req=NULL;

		return p;
	}

	CoveringArray* VSCAGenerator::operator() (const Requirement &req,
											  const CoveringArray &seed)
	{
		if(isLegalSeed(req,seed))
		{
			if(strcmp(req.getReqType().c_str(),"MixedCoverage") != 0)
				m_req=new MixedCoverage(req);
			else
				m_req=dynamic_cast<const MixedCoverage*>(&req);
			if(m_req==NULL)
				return NULL;
			m_uncover_table=new CombSet(*m_req);
			for(CoveringArray::const_iterator it=seed.begin();
				it!=seed.end();++it)
				ModifyUncoverTable(*it,*m_uncover_table);

			CoveringArray *p=run(seed);

			delete m_uncover_table;
			m_uncover_table=NULL;
			if(strcmp(req.getReqType().c_str(),"MixedCoverage") != 0)
				delete m_req;
			m_req=NULL;

			return p;
		}
		else
			return IllegalSeedHandler();
	}

	CoveringArray* VSCAGenerator::operator() (const Requirement &req,
											  const CombSet &required_cover)
	{
		if(strcmp(req.getReqType().c_str(),"MixedCoverage") != 0)
			m_req=new MixedCoverage(req);
		else
			m_req=dynamic_cast<const MixedCoverage*>(&req);
		if(m_req==NULL)
			return NULL;
		m_uncover_table=new CombSet(required_cover);

		CoveringArray *p=run();

		delete m_uncover_table;
		m_uncover_table=NULL;
		if(strcmp(req.getReqType().c_str(),"MixedCoverage") != 0)
			delete m_req;
		m_req=NULL;

		return p;
	}

	CoveringArray* VSCAGenerator::operator() (const Requirement &req,
											  const CombSet &required_cover,
											  const CoveringArray &seed)
	{
		if(isLegalSeed(req,seed))
		{
			if(strcmp(req.getReqType().c_str(),"MixedCoverage") != 0)
				m_req=new MixedCoverage(req);
			else
				m_req=dynamic_cast<const MixedCoverage *>(&req);
			if(m_req==NULL)
				return NULL;
			m_uncover_table=new CombSet(required_cover);
			for(CoveringArray::const_iterator it=seed.begin();
				it!=seed.end();++it)
				ModifyUncoverTable(*it,*m_uncover_table);

			CoveringArray *p=run(seed);

			delete m_uncover_table;
			m_uncover_table=NULL;
			if(strcmp(req.getReqType().c_str(),"MixedCoverage") != 0)
				delete m_req;
			m_req=NULL;

			return p;
		}
		else
			return IllegalSeedHandler();
	}

}	//namespace CTT