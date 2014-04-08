#ifndef READ_INPUT_FILE_H
#define READ_INPUT_FILE_H

#include <vector>
#include "FixedCoverage.h"
#include "FixedPlusCoverage.h"
#include "MixedCoverage.h"
#include "CombPriTable.h"

namespace CTT
{
	class FileReader
	{
		public:

		typedef std::vector<std::vector<std::string> > ParaMap;

		FixedCoverage *GetFixedCoverReq(char *filename,ParaMap &para_map);
		FixedPlusCoverage *GetFixedPlusCoverReq(char *filename,ParaMap &para_map);
		MixedCoverage *GetMixedCoverReq(char *filename,ParaMap &para_map);

	private:

		bool GetAllInfo(
			char *filename,std::vector<int> &paras,int &strength,
			std::map<std::set<int>,int> &subsets,std::set<std::set<int> > &relationship,
			CombPriTable &weight_table,ParaMap &para_map);

		bool IsEmptyLine(char *str);
		bool IsParameters(char *str);
		bool IsFixedStrength(char *str);
		bool IsSubSets(char *str);
		bool IsRelationship(char *str);
		bool IsWeight(char *str);

		bool GetParameters(char* mark,std::ifstream &infile,std::vector<int> &paras,ParaMap &para_map);
		bool GetFixedStrength(std::ifstream &infile,int &strength);
		bool GetSubSets(std::ifstream &infile,const ParaMap &para_map,std::map<std::set<int>,int> &subsets);
		bool GetInteractions(std::ifstream &infile,const ParaMap &para_map,std::set<std::set<int> > &inters);

		bool ReadExperParas(char *str,std::vector<int> &paras);
		bool ReadSimpleParas(std::vector<char*> strs,std::vector<int> &paras);
		bool ReadOneRealPara(char *str,std::vector<int> &paras,ParaMap &para_map);
		bool ReadFixedStrength(char *str,int &strength);
		bool ReadOneSimpleSubset(char *str,std::map<std::set<int>,int> &subsets);

	};
}

#endif