#include <iostream>

int main(int argc, char* argv[])
{
	if(argc<2)
	{
		std::cerr<<"Error parameters!\n";return 0;
	}

	char *txt=NULL;
	char *xls=NULL;
	char *algo=NULL;
	char *seed=NULL;

	bool is_txt=false;
	bool is_xls=false;
	bool is_algo=false;
	bool is_seed=false;

	char *input=argv[1];

	for(int i=2;i<argc;++i)
	{
		char *temp=argv[i];
		if(temp[0]!='/' || temp[2]!=':')
		{
			std::cerr<<"Error parameters!\n";
			return 0;
		}

		switch(temp[1])
		{
		case 't':{
			if(!is_txt)
			{
				txt=temp+3;is_txt=true;break;
			}
			else
			{
				std::cerr<<"Error parameters!\n";return 0;
			}
					};
		case 'x':{
			if(!is_xls)
			{
				xls=temp+3;is_xls=true;break;
			}
			else
			{
				std::cerr<<"Error parameters!\n";return 0;
			}
					};
		case 'a':{
			if(!is_algo)
			{
				algo=temp+3;is_algo=true;break;
			}
			else
			{
				std::cerr<<"Error parameters!\n";return 0;
			}
					};
		case 's':{
			if(!is_seed)
			{
				seed=temp+3;is_seed=true;break;
			}
			else
			{
				std::cerr<<"Error parameters!\n";return 0;
			}
					};
		default:{
			std::cerr<<"Error parameters!\n";return 0;
				}
		}
	}

	//ReadInputFile(input,);
	
	return 0;
}
