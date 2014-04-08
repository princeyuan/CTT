#include "ReadInputFile.h"

#include <string>
#include <fstream>
#include "AssistMethod.h"

namespace CTT
{
	FixedCoverage *GetFixedCoverReq(char *filename)
	{
		std::ifstream infile;
		infile.open(filename,std::ios::in);
		if(!infile)
		{
			return NULL;
		}

		int strength=1;
		std::vector<int> params;
		char buffer[1024];
		bool have_params=false;
		bool have_strength=false;
		
		while(infile.getline(buffer,1024,'\n'))
		{
			if(IsEmptyLine(buffer))
				continue;

			if(IsParameters(buffer))
				if(GetParameters(buffer,infile,params))
					have_params=true;

			if(IsFixedStrength(buffer))
				if(GetFixedStrength(infile,strength))
					have_strength=true;
		}

		infile.close();
		if(have_params && have_strength)
			return new FixedCoverage(params,strength);
		else
			return NULL;
	}

	FixedPlusCoverage *GetFixedPlusCoverReq(char *filename)
	{
		std::ifstream infile;
		infile.open(filename,std::ios::in);
		if(!infile)return NULL;

		int strength=1;
		std::vector<int> params;
		std::map<std::set<int>,int> subsets;
		char buffer[1024];
		bool have_params=false;
		bool have_strength=false;
		bool have_subsets=false;
		
		while(infile.getline(buffer,1024,'\n'))
		{
			if(IsEmptyLine(buffer))
				continue;

			if(IsParameters(buffer))
				if(GetParameters(buffer,infile,params))
					have_params=true;

			if(IsFixedStrength(buffer))
				if(GetFixedStrength(infile,strength))
					have_strength=true;

			if(IsSubCover(buffer))
				if(GetSubSets(infile,subsets))
					have_subsets=true;
		}

		infile.close();
		if(have_params && have_strength)
			return new FixedPlusCoverage(params,strength,subsets);
		else if(have_params && have_subsets)
			return new FixedPlusCoverage(params,1,subsets);
		else
			return NULL;
	}

	MixedCoverage *GetMixedCoverReq(char *filename)
	{
		std::ifstream infile;
		infile.open(filename,std::ios::in);
		if(!infile)return NULL;

		std::vector<int> params;
		std::set<std::set<int> > interactions;
		char buffer[1024];
		bool have_params=false;
		bool have_inters=false;
		
		while(infile.getline(buffer,1024,'\n'))
		{
			if(IsEmptyLine(buffer))
				continue;

			if(IsParameters(buffer))
				if(GetParameters(buffer,infile,params))
					have_params=true;

			if(IsInteractions(buffer))
				if(GetInteractions(infile,interactions))
					have_inters=true;
		}

		infile.close();
		if(have_params && have_inters)
			return new MixedCoverage(params,interactions);
		else
			return NULL;
	}

	bool IsEmptyLine(char *str)
	{
		if(str!=NULL)
			if(str[0]=='#' || str[0]=='\0')
				return true;

		return false;
	}

	bool IsParameters(char *str)
	{
		if(str!=NULL)
		{
			if(strlen(str)>=strlen("[Exper Parameters]"))
				if(!strncmp(str,"[Exper Parameters]",strlen("[Exper Parameters]")))
					return true;
			if(strlen(str)>=strlen("[Simple Parameters]"))
				if(!strncmp(str,"[Simple Parameters]",strlen("[Simple Parameters]")))
					return true;
		}
		return false;
	}

	bool IsFixedStrength(char *str)
	{
		if(str!=NULL)
			if(strlen(str)>=strlen("[Fixed Strength]"))
				if(!strncmp(str,"[Fixed Strength]",strlen("[Fixed Strength]")))
					return true;
		return false;
	}

	bool IsSubCover(char *str)
	{
		if(str!=NULL)
			if(strlen(str)>=strlen("[Sub Requirement]"))
				if(!strncmp(str,"[Sub Requirement]",strlen("[Sub Requirement]")))
					return true;
		return false;
	}

	bool IsInteractions(char *str)
	{
		if(str!=NULL)
			if(strlen(str)>=strlen("[Relationship]"))
				if(!strncmp(str,"[Relationship]",strlen("[Relationship]")))
					return true;
		return false;
	}

	bool GetParameters(char* mark,std::ifstream &infile,std::vector<int> &params)
	{
		char buffer[1024];

		if(strlen(mark)>=18)
		{
			if(!strncmp(mark,"[Exper Parameters]",18))
			{
				while(infile.getline(buffer,1024,'\n'))
					if(!IsEmptyLine(buffer))
						if(ReadExperParams(buffer,params))
							return true;
			}
		}

		if(strlen(mark)>=19)
		{
			if(!strncmp(mark,"[Simple Parameters]",19))
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
						if(ReadSimpleParams(str,params))
							return true;
						break;
					}
			}
		}

		return false;
	}

	bool GetFixedStrength(std::ifstream &infile,int &strength)
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

	bool GetSubSets(std::ifstream &infile,std::map<std::set<int>,int> &subsets)
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

	bool GetInteractions(std::ifstream &infile,std::set<std::set<int> > &inters)
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

	bool ReadExperParams(char *str,std::vector<int> &params)
	{
		char *tag=str;
		int value,number;

		while(true)
		{
			tag=getOneNumFromLine(tag,value);
			if(*tag!='\0' && *tag!='^' && *tag!='*')
				return false;

			if(*tag!='^')
			{
				number=1;
			}
			else
			{
				tag=getOneNumFromLine(++tag,number);
				if(*tag!='\0' && *tag!='^' && *tag!='*')
					return false;
			}
			
			for(int i=0;i<number;++i)
				params.push_back(value);

			if(*tag!='*')
				break;
			else
				++tag;
		}

		return true;
	}

	bool ReadSimpleParams(std::vector<char*> str,std::vector<int> &params)
	{
		if(strncmp("number>>",str[0],8) || strncmp("list>>",str[1],6))
			return false;

		int number;
		if(getOneNumFromLine(str[0],number)==NULL)
			return false;
		if(number==0)
			return false;

		if(getAllNumFromLine(str[1],params)<number)
			return false;

		return true;
	}

	bool ReadFixedStrength(char *str,int &strength)
	{
		if(getOneNumFromLine(str,strength)==NULL)
			return false;

		return true;
	}

	bool ReadOneSimpleSubset(char *str,std::map<std::set<int>,int> &subsets)
	{
		std::vector<int> temp;
		std::set<int> one_set;
		int all_num=getAllNumFromLine(str,temp);
		if(all_num<3)
			return false;//subset中至少2个因素
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