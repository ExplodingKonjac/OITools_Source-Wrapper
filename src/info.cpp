#include "info.h"

namespace Info
{

void displayHelp()
{
	constexpr char text[]=
	"Usage: oit-wrap [<root>] [options...]\n"
	"Automatically searches the problem names under <root>, then\n"
	"wrap the sources into the output directory in tidy format.\n"
	"\n"
	"Arguments:\n"
	"  <root>\n"
	"    The directory to search in. '.' if not specified.\n"
	"\n"
	"Options:\n"
	"  -v, --version\n"
	"    Display version information.\n"
	"  -h, --help\n"
	"    Display helping message.\n"
	"  -o <directory>, --output=<directory>\n"
	"    Place output files in <directory>.\n"
	"  -S, --subdir-only\n"
	"    Program will only search problem names from sources in the form\n"
	"    of '<root>/A/A.cpp'.\n"
	"  -R, --rootdir-only\n"
	"    Program will only search problem names from sources in the form\n"
	"    of '<root>/A.cpp'.\n"
	"  --exclude=<name>\n"
	"    Program will ignore <name> if it appears as a searched name.";
	std::printf(text);
}

void displayVersion()
{
	constexpr char text[]=
	"oit-wrap 1.0\n"
	"Copyright (C) 2023 ExplodingKonjac\n"
	"\n"
	"This program is free software: you can redistribute it and/or modify\n"
	"it under the terms of the GNU General Public License as published by\n"
	"the Free Software Foundation, either version 3 of the License, or\n"
	"(at your option) any later version.\n"
	"\n"
	"This program is distributed in the hope that it will be useful,\n"
	"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
	"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
	"GNU General Public License for more details.\n"
	"\n"
	"You should have received a copy of the GNU General Public License\n"
	"along with this program.  If not, see <https://www.gnu.org/licenses/>.\n";
	std::printf(text);
}

} // namespace Info
