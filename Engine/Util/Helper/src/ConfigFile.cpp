/*
--------------------------------------------------------------------------------
Based on class found at: http://ai.stanford.edu/~gal/Code/FindMotifs/
--------------------------------------------------------------------------------
*/

#include "Platform/StableHeaders.h"

#include "Util/Helper/ConfigFile.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
Config::Config(String filename, String delimiter, String comment, String sentry)
	: myDelimiter(delimiter)
	, myComment(comment)
	, mySentry(sentry)
{
	// Construct a Config, getting keys and values from given file
	std::ifstream in(filename.c_str());
	if (!in) throw file_not_found(filename); 
	in >> (*this);
}
//------------------------------------------------------------------------------
Config::Config()
	: myDelimiter(String(1,'='))
	, myComment(String(1,'#'))
{
	// Construct a Config without a file; empty
}
//------------------------------------------------------------------------------
void Config::remove(const String& key)
{
	// Remove key and its value
	myContents.erase(myContents.find(key));
	return;
}
//------------------------------------------------------------------------------
bool Config::keyExists(const String& key) const
{
	// Indicate whether key is found
	mapci p = myContents.find(key);
	return (p != myContents.end());
}
//------------------------------------------------------------------------------
/* static */
void Config::trim(String& s)
{
	// Remove leading and trailing whitespace
	static const char whitespace[] = " \n\t\v\r\f";
	s.erase(0, s.find_first_not_of(whitespace));
	s.erase(s.find_last_not_of(whitespace) + 1U);
}
//------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const Config& cf)
{
	// Save a Config to os
	for (Config::mapci p = cf.myContents.begin();
	     p != cf.myContents.end();
		 ++p)
	{
		os << p->first << " " << cf.myDelimiter << " ";
		os << p->second << std::endl;
	}
	return os;
}
//------------------------------------------------------------------------------
std::istream& operator>>(std::istream& is, Config& cf)
{
	// Load a Config from is
	// Read in keys and values, keeping internal whitespace
	typedef String::size_type pos;
	const String& delim  = cf.myDelimiter;  // separator
	const String& comm   = cf.myComment;    // comment
	const String& sentry = cf.mySentry;     // end of file sentry
	const pos skip = delim.length();        // length of separator
	
	String nextline = "";  // might need to read ahead to see where value ends
	
	while (is || nextline.length() > 0)
	{
		// Read an entire line at a time
		String line;
		if (nextline.length() > 0)
		{
			line = nextline;  // we read ahead; use it now
			nextline = "";
		}
		else
		{
			std::getline(is, line);
		}
		
		// Ignore comments
		line = line.substr(0, line.find(comm));
		
		// Check for end of file sentry
		if (sentry != "" && line.find(sentry) != String::npos) return is;
		
		// Parse the line if it contains a delimiter
		pos delimPos = line.find(delim);
		if (delimPos < String::npos)
		{
			// Extract the key
			String key = line.substr(0, delimPos);
			line.replace(0, delimPos+skip, "");
			
			// See if value continues on the next line
			// Stop at blank line, next line with a key, end of stream,
			// or end of file sentry
			bool terminate = false;
			while(!terminate && is)
			{
				std::getline(is, nextline);
				terminate = true;
				
				String nlcopy = nextline;
				Config::trim(nlcopy);
				if (nlcopy == "") continue;
				
				nextline = nextline.substr(0, nextline.find(comm));
				if (nextline.find(delim) != String::npos)
					continue;
				if (sentry != "" && nextline.find(sentry) != String::npos)
					continue;
				
				nlcopy = nextline;
				Config::trim(nlcopy);
				if (nlcopy != "") line += "\n";
				line += nextline;
				terminate = false;
			}
			
			// Store key and value
			Config::trim(key);
			Config::trim(line);
			cf.myContents[key] = line;  // overwrites if key is repeated
		}
	}
	
	return is;
}
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------