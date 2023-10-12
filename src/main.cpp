#include "core/info.h"
#include "core/options.h"
#include "Colorful.hpp"

#include <set>
#include <iostream>
#include <algorithm>

#include <boost/system.hpp>
#include <boost/filesystem.hpp>

namespace fs=boost::filesystem;

int main(int argc,char *argv[])
{
	Options::parse(argc,argv);
	if(Options::print_help)
	{
		Info::displayHelp();
		return 0;
	}
	if(Options::print_version)
	{
		Info::displayVersion();
		return 0;
	}
	if(Options::rootdir_only && Options::subdir_only)
	{
		printNote("'--rootdir-only' and '--subdir-only' are both specified.\n"
				  "Program will do nothing and quit.");
		return 0;
	}
	fs::path root_path(Options::root_dir);
	if(!fs::exists(root_path))
		quitError("'%s' does not exist.",
				  root_path.generic_string().c_str());
	if(!fs::is_directory(root_path))
		quitError("'%s' is not a directory.",
				  root_path.generic_string().c_str());
	if(Options::output_dir.empty())
		quitError("No output directory provided.\n"
				  "Use 'oit-wrap --help' to get help.");
	fs::path output_path(Options::output_dir);
	boost::system::error_code ec;
	fs::create_directory(output_path,ec);
	if(ec) quitError("Failed to create output directory (%d).",ec.value());
	std::set<std::string> problemset;
	for(auto &entry: fs::directory_iterator(root_path))
	{
		auto path=entry.path();
		if(!Options::rootdir_only && entry.is_directory())
		{
			auto name=path.filename().string();
			auto cpp_path=path/(name+".cpp");
			if(fs::exists(cpp_path) && fs::is_regular_file(cpp_path))
				problemset.insert(name);
		}
		if(!Options::subdir_only && entry.is_regular_file() && path.extension().string()==".cpp")
		{
			auto name=path.replace_extension("").filename().string();
			problemset.insert(name);
		}
	}
	for(auto &name: problemset)
	{
		if(Options::exclude_list.count(name) ||
		   (!Options::include_list.empty() && !Options::include_list.count(name)))
			continue;
		fs::create_directory(output_path/name,ec);
		if(ec) quitError("Failed to create subdirectory for '%s'.",name.c_str());
		fs::path file1=root_path/name/(name+".cpp"),file2=root_path/(name+".cpp"),file;
		bool fl1=(!Options::rootdir_only && fs::exists(file1)),
			 fl2=(!Options::subdir_only && fs::exists(file2));
		if(fl1 && fl2)
		{
			std::string s;
			std::printf("Both '%s' (1) and '%s' (2) found, which to keep? (1/2): ",
						file1.generic_string().c_str(),
						file2.generic_string().c_str());
			std::getline(std::cin,s);
			while(s!="1" && s!="2")
			{
				std::printf("Unrecognized input. (1/2): ");
				std::getline(std::cin,s);
			}
			file=(s=="1"?file1:file2);
		}
		else file=(fl1?file1:file2);
		auto doCopy=[&](const fs::path &target)
		{
			// bug: boost::filesystem::copy_file does not overwrite but give out error instead.
			if(fs::is_regular_file(target))
				fs::remove(target);
			fs::copy_file(file,target,fs::copy_options::overwrite_existing,ec);
			if(!ec) return true;
			std::fprintf(stderr,"Failed to copy '%s' to '%s' (%d).\n",
								file.generic_string().c_str(),
								target.generic_string().c_str(),
								ec.value());
			return false;
		};
		bool ok=doCopy(output_path/name/(name+".cpp")) &&
				doCopy(output_path/(name+".cpp"));
		std::fprintf(stderr,"'%s' %s.\n",name.c_str(),ok?"done":"failed");
	}
	return 0;
}