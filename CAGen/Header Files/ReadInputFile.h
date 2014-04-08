#ifndef READ_INPUT_FILE_H
#define READ_INPUT_FILE_H

#include <vector>
#include "FixedCoverage.h"
#include "FixedPlusCoverage.h"
#include "MixedCoverage.h"

namespace CTT
{	
	//Get different types of requirement from a file
	//If it is fail to get a requirement, return NULL
	FixedCoverage *GetFixedCoverReq(char *filename);
	FixedPlusCoverage *GetFixedPlusCoverReq(char *filename);
	MixedCoverage *GetMixedCoverReq(char *filename);

	//Following functions are called by above 3 functions
	bool IsEmptyLine(char *str);
	bool IsParameters(char *str);
	bool IsFixedStrength(char *str);
	bool IsSubCover(char *str);
	bool IsInteractions(char *str);

	bool GetParameters(char* mark,std::ifstream &infile,std::vector<int> &params);
	bool GetFixedStrength(std::ifstream &infile,int &strength);
	bool GetSubSets(std::ifstream &infile,std::map<std::set<int>,int> &subsets);
	bool GetInteractions(std::ifstream &infile,std::set<std::set<int> > &inters);

	bool ReadExperParams(char *str,std::vector<int> &params);
	bool ReadSimpleParams(std::vector<char*> str,std::vector<int> &params);
	bool ReadFixedStrength(char *str,int &strength);
	bool ReadOneSimpleSubset(char *str,std::map<std::set<int>,int> &subsets);
}

#endif