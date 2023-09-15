#pragma once

#include <string>
#include <cstdio>
#include <vector>
#include <getopt.h>

namespace Options
{

extern bool print_help,print_version,subdir_only,rootdir_only;
extern std::string root_dir,output_dir;
extern std::vector<std::string> exclude_list;

void parse(int argc,char *argv[]);

} // namespace Options
