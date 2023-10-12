#include "options.h"
#include "base/Colorful.hpp"

namespace Options
{

bool print_help=false,print_version=false,subdir_only=false,rootdir_only=false;
std::string root_dir("."),output_dir;
std::set<std::string> exclude_list,include_list;

option long_options[]={
	{"help",no_argument,0,'h'},
	{"version",no_argument,0,'v'},
	{"output",required_argument,0,'o'},
	{"subdir-only",no_argument,0,'S'},
	{"rootdir-only",no_argument,0,'R'},
	{"exclude",required_argument,0,'e'},
	{"include",required_argument,0,'i'},
	{0,0,0,0}
};
char short_options[]={
	":hvo:SRe:i:"
};

void parse(int argc,char *argv[])
{
	int arg,idx;
	opterr=0;
	while(~(arg=getopt_long(argc,argv,short_options,long_options,&idx)))
	{
		switch (arg)
		{
		 case 'h':
		 	print_help=true;
			break;
		 case 'v':
		 	print_version=true;
			break;
		 case 'o':
			output_dir=optarg;
			break;
		 case 'S':
			subdir_only=true;
			break;
		 case 'R':
			rootdir_only=true;
			break;
		 case 'e':
			exclude_list.insert(optarg);
			break;
		 case 'i':
			include_list.insert(optarg);
			break;
		 case ':':
			quitError("Missing argument for '%s'.\n",argv[optind-1]);
		 case '?':
			quitError("Unknown option '%s'.\n",argv[optind-1]);
		}
	}
	if(optind<argc)
		root_dir=argv[optind];
}

} // namespace Options
