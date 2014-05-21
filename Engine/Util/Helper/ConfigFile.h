/*
--------------------------------------------------------------------------------
Based on class found at: http://ai.stanford.edu/~gal/Code/FindMotifs/
--------------------------------------------------------------------------------
USAGE:
--------------------------------------------------------------------------------
Given a configuration file "settings.ini":
  atoms  = 25
  length = 8.0  # nanometers
  name = Reece Surcher

Named values are read in various ways, with or without default values:
  Config config("settings.inp");
  int atoms = config.read<int>("atoms");
  double length = config.read("length", 10.0);
  string author, title;
  config.readInto(author, "name");
  config.readInto(title, "title", string("Untitled"));
--------------------------------------------------------------------------------
*/

#ifndef DANGINE_CONFIG_H
#define DANGINE_CONFIG_H

#include "Platform/Prerequisites.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
class Config
{
// Data
protected:
	String myDelimiter;  // separator between key and value
	String myComment;    // separator between value and comments
	String mySentry;     // optional string to signal end of file
	std::map<String,String> myContents;  // extracted keys and values
	
	typedef std::map<String,String>::iterator mapi;
	typedef std::map<String,String>::const_iterator mapci;

public:
	Config(String filename,
	            String delimiter = "=",
	            String comment = "#",
				String sentry = "EndConfig");
	Config();
	
	// Search for key and read value or optional default value
	template<class T> T read(const String& key) const;  // call as read<T>
	template<class T> T read(const String& key, const T& value) const;
	template<class T> bool readInto(T& var, const String& key) const;
	template<class T>
	bool readInto(T& var, const String& key, const T& value) const;
	
	// Modify keys and values
	template<class T> void add(String key, const T& value);
	void remove(const String& key);
	
	// Check whether key exists in configuration
	bool keyExists(const String& key) const;
	
	// Check or change configuration syntax
	String getDelimiter() const { return myDelimiter; }
	String getComment() const { return myComment; }
	String getSentry() const { return mySentry; }
	String setDelimiter(const String& s)
		{ String old = myDelimiter;  myDelimiter = s;  return old; }  
	String setComment(const String& s)
		{ String old = myComment;  myComment = s;  return old; }
	
	// Write or read configuration
	friend std::ostream& operator<<(std::ostream& os, const Config& cf);
	friend std::istream& operator>>(std::istream& is, Config& cf);
	
protected:
	template<class T> static String T_as_string(const T& t);
	template<class T> static T string_as_T(const String& s);
	static void trim(String& s);

public:
	// Exception types
	struct file_not_found {
		String filename;
		file_not_found(const String& filename_ = String())
			: filename(filename_) {} };
	struct key_not_found {  // thrown only by T read(key) variant of read()
		String key;
		key_not_found(const String& key_ = String())
			: key(key_) {} };
};
//------------------------------------------------------------------------------
template<class T>
String Config::T_as_string(const T& t)
{
	// Convert from a T to a string
	// Type T must support << operator
	std::ostringstream ost;
	ost << t;
	return ost.str();
}
//------------------------------------------------------------------------------
template<class T>
T Config::string_as_T(const String& s)
{
	// Convert from a string to a T
	// Type T must support >> operator
	T t;
	std::istringstream ist(s);
	ist >> t;
	return t;
}
//------------------------------------------------------------------------------
template<>
inline String Config::string_as_T<String>(const String& s)
{
	// Convert from a string to a string
	// In other words, do nothing
	return s;
}
//------------------------------------------------------------------------------
template<>
inline bool Config::string_as_T<bool>(const String& s)
{
	// Convert from a string to a bool
	// Interpret "false", "F", "no", "n", "0" as false
	// Interpret "true", "T", "yes", "y", "1", "-1", or anything else as true
	bool b = true;
	String sup = s;
	for(String::iterator p = sup.begin(); p != sup.end(); ++p)
		*p = toupper(*p);  // make string all caps
	if (sup==String("FALSE") || sup==String("F") ||
	    sup==String("NO") || sup==String("N") ||
	    sup==String("0") || sup==String("NONE"))
		b = false;
	return b;
}
//------------------------------------------------------------------------------
template<class T>
T Config::read(const String& key) const
{
	// Read the value corresponding to key
	mapci p = myContents.find(key);
	if (p == myContents.end()) throw key_not_found(key);
	return string_as_T<T>(p->second);
}
//------------------------------------------------------------------------------
template<class T>
T Config::read(const String& key, const T& value) const
{
	// Return the value corresponding to key or given default value
	// if key is not found
	mapci p = myContents.find(key);
	if (p == myContents.end()) return value;
	return string_as_T<T>(p->second);
}
//------------------------------------------------------------------------------
template<class T>
bool Config::readInto(T& var, const String& key) const
{
	// Get the value corresponding to key and store in var
	// Return true if key is found
	// Otherwise leave var untouched
	mapci p = myContents.find(key);
	bool found = (p != myContents.end());
	if (found) var = string_as_T<T>(p->second);
	return found;
}
//------------------------------------------------------------------------------
template<class T>
bool Config::readInto(T& var, const String& key, const T& value) const
{
	// Get the value corresponding to key and store in var
	// Return true if key is found
	// Otherwise set var to given default
	mapci p = myContents.find(key);
	bool found = (p != myContents.end());
	if (found)
		var = string_as_T<T>(p->second);
	else
		var = value;
	return found;
}
//------------------------------------------------------------------------------
template<class T>
void Config::add(String key, const T& value)
{
	// Add a key with given value
	String v = T_as_string(value);
	trim(key);
	trim(v);
	myContents[key] = v;
	return;
}
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------

#endif // DANGINE_CONFIG_H