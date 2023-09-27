#pragma once

#include <string>
#include <cstdio>
#include <set>
#include <getopt.h>

namespace Options
{

extern bool print_help,print_version,subdir_only,rootdir_only;
extern std::string root_dir,output_dir;
extern std::set<std::string> exclude_list,include_list;

void parse(int argc,char *argv[]);

} // namespace Options
