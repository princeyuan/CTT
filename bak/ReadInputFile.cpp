#include "ReadInputFile.h"

#include <string>
#include <fstream>
#include "AssistMethod.h"

namespace CTT
{
	/*FixedCoverage *FileReader::GetFixedCoverReq(char *filename,ParaMap &para_map)
	{
		std::ifstream infile;
		infile.open(filename,std::ios::in);
		if(!infile)return NULL;

		int strength=1;
		std::vector<int> paras;
		char buffer[1024];
		bool have_paras=false;
		bool have_strength=false;
		bool have_weight=false;
		
		while(infile.getline(buffer,1024,'\n'))
		{
			if(IsEmptyLine(buffer))
				continue;

			if(IsParameters(buffer))
				if(GetParameters(buffer,infile,paras,para_map))
					have_paras=true;

			if(IsFixedStrength(buffer))
				if(GetFixedStrength(infile,strength))
					have_strength=true;
		}

		infile.close();
		if(have_paras && have_strength)
			return new FixedCoverage(paras,strength);
		else
			return NULL;
	}

	FixedPlusCoverage *FileReader::GetFixedPlusCoverReq(char *filename,ParaMap &para_map)
	{
		std::ifstream infile;
		infile.open(filename,std::ios::in);
		if(!infile)return NULL;

		int strength=1;
		std::vector<int> paras;
		std::map<std::set<int>,int> subsets;
		char buffer[1024];
		bool have_paras=false;
		bool have_strength=false;
		bool have_subsets=false;
		bool have_weight=false;
		
		while(infile.getline(buffer,1024,'\n'))
		{
			if(IsEmptyLine(buffer))
				continue;

			if(IsParameters(buffer))
				if(GetParameters(buffer,infile,paras,para_map))
					have_paras=true;

			if(IsFixedStrength(buffer))
				if(GetFixedStrength(infile,strength))
					have_strength=true;

			if(IsSubSets(buffer))
				if(GetSubSets(infile,subsets))
					have_subsets=true;

			if(IsWeight(buffer))
				//if(GetWeight(buffer,infile,para_map,CombPriTable))
					have_weight=true;
		}

		infile.close();
		if(have_paras && have_strength && have_subsets)
			return new FixedPlusCoverage(paras,strength,subsets);
		else if(have_paras && have_subsets)
			return new FixedPlusCoverage(paras,1,subsets);
		else
			return NULL;
	}

	MixedCoverage *FileReader::GetMixedCoverReq(char *filename,ParaMap &para_map)
	{
		std::ifstream infile;
		infile.open(filename,std::ios::in);
		if(!infile)return NULL;

		std::vector<int> paras;
		std::set<std::set<int> > interactions;
		char buffer[1024];
		bool have_paras=false;
		bool have_inters=false;
		bool have_weight=false;
		
		while(infile.getline(buffer,1024,'\n'))
		{
			if(IsEmptyLine(buffer))
				continue;

			if(IsParameters(buffer))
				if(GetParameters(buffer,infile,paras,para_map))
					have_paras=true;

			if(IsRelationship(buffer))
				if(GetInteractions(infile,interactions))
					have_inters=true;

			if(IsWeight(buffer))
				//if(GetWeight(buffer,infile,para_map,CombPriTable))
					have_weight=true;
		}

		infile.close();
		if(have_paras && have_inters)
			return new MixedCoverage(paras,interactions);
		else
			return NULL;
	}*/

	bool FileReader::GetAllInfo(
		char *filename,std::vector<int> &paras,int &strength,
		std::map<std::set<int>,int> &subsets,std::set<std::set<int> > &relationship,
		CombPriTable &weight_table,ParaMap &para_map)
	{
		std::ifstream infile;
		infile.open(filename,std::ios::in);
		if(!infile)return false;

		char buffer[1024];
		bool have_paras=false;
		bool have_strength=false;
		bool have_subsets=false;
		bool have_relation=false;
		bool have_weight=false;
		
		while(infile.getline(buffer,1024,'\n'))
		{
			if(IsEmptyLine(buffer))
				continue;

			if(IsParameters(buffer))
				if(GetParameters(buffer,infile,paras,para_map))
					have_paras=true;

			if(IsFixedStrength(buffer))
				if(GetFixedStrength(infile,strength))
					have_strength=true;

			if(IsSubSets(buffer))
				if(GetSubSets(infile,para_map,subsets))
					have_subsets=true;

			if(IsRelationship(buffer))
				if(GetInteractions(infile,para_map,relationship))
					have_relation=true;

			if(IsWeight(buffer))
				//if(GetWeight(buffer,infile,para_map,weight_table))
					have_weight=true;
		}

		infile.close();
	}

	bool FileReader::IsEmptyLine(char *str)
	{
		if(str!=NULL)
			if(str[0]=='#' || str[0]=='\0')
				return true;

		return false;
	}

	bool FileReader::IsParameters(char *str)
	{
		if(str!=NULL)
		{
			if(strlen(str)>=strlen("[Exper Parameters]"))
				if(!strncmp(str,"[Exper Parameters]",strlen("[Exper Parameters]")))
					return true;
			if(strlen(str)>=strlen("[Simple Parameters]"))
				if(!strncmp(str,"[Simple Parameters]",strlen("[Simple Parameters]")))
					return true;
			if(strlen(str)>=strlen("[Real Parameters]"))
				if(!strncmp(str,"[Real Parameters]",strlen("[Real Parameters]")))
					return true;
		}
		return false;
	}

	bool FileReader::IsFixedStrength(char *str)
	{
		if(str!=NULL)
			if(strlen(str)>=strlen("[Fixed Strength]"))
				if(!strncmp(str,"[Fixed Strength]",strlen("[Fixed Strength]")))
					return true;
		return false;
	}

	bool FileReader::IsSubSets(char *str)
	{
		if(str!=NULL)
			if(strlen(str)>=strlen("[Interactions]"))
				if(!strncmp(str,"[Interactions]",strlen("[Interactions]")))
					return true;
		return false;
	}

	bool FileReader::IsRelationship(char *str)
	{
		if(str!=NULL)
			if(strlen(str)>=strlen("[Relationship]"))
				if(!strncmp(str,"[Relationship]",strlen("[Relationship]")))
					return true;
		return false;
	}

	bool FileReader::IsWeight(char *str)
	{
		if(str!=NULL)
		{
			if(strlen(str)>=strlen("[Combination Weight]"))
				if(!strncmp(str,"[Combination Weight]",strlen("[Combination Weight]")))
					return true;
			if(strlen(str)>=strlen("[Value Weight]"))
				if(!strncmp(str,"[Value Weight]",strlen("[Value Weight]")))
					return true;
		}
		return false;
	}

	bool FileReader::GetParameters(char* mark,std::ifstream &infile,std::vector<int> &paras,ParaMap &para_map)
	{
		char buffer[1024];

		if(strlen(mark)>=strlen("[Exper Parameters]"))
		{
			if(!strncmp(mark,"[Exper Parameters]",strlen("[Exper Parameters]")))
			{
				while(infile.getline(buffer,1024,'\n'))
					if(!IsEmptyLine(buffer))
						if(ReadExperParas(buffer,paras))
							return true;
			}
		}

		if(strlen(mark)>=strlen("[Simple Parameters]"))
		{
			if(!strncmp(mark,"[Simple Parameters]",strlen("[Simple Parameters]")))
			{
				char temp[1024];
				std::vector<char*> str(2);

				while(infile.getline(buffer,1024,'\n'))
					if(!IsEmptyLine(buffer))
					{
						strcpy(temp,buffer);
						str[0]=temp;
						break;
					}

				while(infile.getline(buffer,1024,'\n'))
					if(!IsEmptyLine(buffer))
					{
						str[1]=buffer;
						if(ReadSimpleParas(str,paras))
							return true;
						break;
					}
			}
		}

		if(strlen(mark)>=strlen("[Real Parameters]"))
		{
			if(!strncmp(mark,"[Real Parameters]",strlen("[Real Parameters]")))
			{
				bool is_start=false;

				while(infile.getline(buffer,1024,'\n'))
				{
					if(!IsEmptyLine(buffer))
						ReadOneRealPara(buffer,paras,para_map);
					else if(is_start)
						return true;
				}
			}
		}

		return false;
	}

	bool FileReader::GetFixedStrength(std::ifstream &infile,int &strength)
	{
		char buffer[1024];
		while(infile.getline(buffer,1024,'\n'))
			if(!IsEmptyLine(buffer))
			{
				if(ReadFixedStrength(buffer,strength))
					return true;
				else
					return false;
			}

		return false;
	}

	bool FileReader::GetSubSets(std::ifstream &infile,const ParaMap &para_map,std::map<std::set<int>,int> &subsets)
	{
		char buffer[1024];
		while(infile.getline(buffer,1024,'\n'))
			if(!IsEmptyLine(buffer))
				break;

		while(true)
		{
			if(!ReadOneSimpleSubset(buffer,subsets))break;
			infile.getline(buffer,1024,'\n');
			if(IsEmptyLine(buffer))break;
		}

		if(subsets.begin()!=subsets.end())
			return true;
		else
			return false;
	}

	bool FileReader::GetInteractions(std::ifstream &infile,const ParaMap &para_map,std::set<std::set<int> > &inters)
	{
		char buffer[1024];
		std::vector<int> temp;
		while(infile.getline(buffer,1024,'\n'))
			if(!IsEmptyLine(buffer))
				break;

		while(true)
		{
			if(getAllNumFromLine(buffer,temp)!=NULL)
				inters.insert(std::set<int>(temp.begin(),temp.end()));
			infile.getline(buffer,1024,'\n');
			if(IsEmptyLine(buffer))break;
		}

		if(inters.begin()!=inters.end())
			return true;
		else
			return false;
	}

	bool FileReader::ReadExperParas(char *str,std::vector<int> &paras)
	{
		char *tag=str;
		int value,number;

		while(true)
		{
			tag=getOneNumFromLine(tag,value);
			if(tag==NULL || *tag!='^')
				return false;

			tag=getOneNumFromLine(++tag,number);
			if(tag==NULL)
				return false;
			
			for(int i=0;i<number;++i)
				paras.push_back(value);

			if(*tag!='*')
				break;
			else
				++tag;
		}

		return true;
	}

	bool FileReader::ReadSimpleParas(std::vector<char*> str,std::vector<int> &paras)
	{
		if(strncmp("number>>",str[0],8) || strncmp("list>>",str[1],6))
			return false;

		int number;
		if(getOneNumFromLine(str[0],number)==NULL)
			return false;
		if(number==0)
			return false;

		if(getAllNumFromLine(str[1],paras)<number)
			return false;

		return true;
	}

	bool FileReader::ReadOneRealPara(char *str,std::vector<int> &paras,ParaMap &para_map)
	{
		std::string temp;

		while(*str!=':')
		{
			temp.push_back(*str);
			++str;
		}
		if(temp.size()<1)return false;
		para_map[0].push_back(temp);
		while(*str==' ' || *str==':')++str;

		std::vector<std::string> value_map;
		temp.clear();
		while(*str!='\0')
		{
			while(*str!=',' && *str!=' ' && *str!='\0')
			{
				temp.push_back(*str);
				++str;
			}
			if(temp.size()<1)return false;
			value_map.push_back(temp);
			while(*str==' ' || *str==',')++str;
		}

		para_map.push_back(value_map);
		paras.push_back(para_map.size());

		return true;
	}

	bool FileReader::ReadFixedStrength(char *str,int &strength)
	{
		if(getOneNumFromLine(str,strength)==NULL)
			return false;

		return true;
	}

	bool FileReader::ReadOneSimpleSubset(char *str,std::map<std::set<int>,int> &subsets)
	{
		std::vector<int> temp;
		std::set<int> one_set;
		int all_num=getAllNumFromLine(str,temp);
		if(all_num<3)return false;//subset中至少2个因素
		for(int i=0;i<all_num-1;++i)
			one_set.insert(temp[i]);

		int strength;
		str=InterceptString(str,"}");
		if(str==NULL)return false;
		str=InterceptString(str,"@");
		if(str==NULL)return false;
		str=getOneNumFromLine(str,strength);
		if(str==NULL)return false;

		subsets.insert(std::pair<std::set<int>,int>(one_set,strength));
		return true;
	}
}