#ifndef __LOG_H__
#define __LOG_H__

#include <sstream>
#include <string>
#include <stdio.h>

//------------------------------------------------------------------------------
inline std::string NowTime();

enum LogLevel
{
    logNONE, // Used with ReportingLevel to suppress all logging at runtime.
    logERROR,
    logWARNING,
    logINFO,
    logDEBUG,
    logDEBUG1,
    logDEBUG2,
    logDEBUG3,
    logDEBUG4
};
//------------------------------------------------------------------------------
template <typename T>
class Log
{
public:
    Log();
    virtual ~Log();
	
    std::ostringstream& Get(LogLevel level = logINFO);
	
public:
    static LogLevel& ReportingLevel();
    static std::string ToString(LogLevel level);
    static LogLevel FromString(const std::string& level);
	
protected:
    std::ostringstream os;
	
private:
    Log(const Log&);
    Log& operator =(const Log&);
};

template <typename T>
Log<T>::Log()
{
}

template <typename T>
std::ostringstream& Log<T>::Get(LogLevel level)
{
    os << "- " << NowTime();
    os << " " << ToString(level) << ": ";
    os << std::string(level > logDEBUG ? level - logDEBUG : 0, '\t');
	
    return os;
}

template <typename T>
Log<T>::~Log()
{
    os << std::endl;
    T::Output(os.str());
}

template <typename T>
LogLevel& Log<T>::ReportingLevel()
{
    static LogLevel reportingLevel = logDEBUG4;
    return reportingLevel;
}

template <typename T>
std::string Log<T>::ToString(LogLevel level)
{
	static const char* const buffer[] =
	{
		"ERROR", "WARNING", "INFO", "DEBUG", "DEBUG1", "DEBUG2", "DEBUG3", "DEBUG4"
	};
    return buffer[level - 1];
}

template <typename T>
LogLevel Log<T>::FromString(const std::string& level)
{
    typedef std::map<std::string, LogLevel> LogLevelNamesMap;
    static LogLevelNamesMap logLevels;
	
	if (logLevels.empty())
	{
		logLevels["ERROR"]   = logERROR;
		logLevels["WARNING"] = logWARNING;
		logLevels["INFO"]    = logINFO;
		logLevels["DEBUG"]   = logDEBUG;
		logLevels["DEBUG1"]  = logDEBUG1;
		logLevels["DEBUG2"]  = logDEBUG2;
		logLevels["DEBUG3"]  = logDEBUG3;
		logLevels["DEBUG4"]  = logDEBUG4;
	}
	
	LogLevelNamesMap::iterator it = logLevels.find(level);
	if (it == logLevels.end())
	{
		Log<T>().Get(logWARNING) << L"Unknown logging level '" << level
		<< L"'. Using INFO level as default.";
		
		return logINFO;
	}
	
	return it->second;
}
//------------------------------------------------------------------------------
class Output2FILE
{
public:
    static FILE*& Stream();
    static void Output(const std::string& msg);
};

inline FILE*& Output2FILE::Stream()
{
    static FILE* pStream = stderr;
    return pStream;
}

inline void Output2FILE::Output(const std::string& msg)
{
    FILE* pStream = Stream();
    if (!pStream)
        return;
    fprintf(pStream, "%s", msg.c_str());
    fflush(pStream);
}
//------------------------------------------------------------------------------
typedef Log<Output2FILE> FILELog;

#ifndef LOG_MAX_LEVEL
#define LOG_MAX_LEVEL logDEBUG4
#endif

#define LOG(level) \
if (level > LOG_MAX_LEVEL) ; \
else if (level > FILELog::ReportingLevel() || !Output2FILE::Stream()) ; \
else FILELog().Get(level)

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)

#include <windows.h>

inline std::string NowTime()
{
    const int MAX_LEN = 200;
    char buffer[MAX_LEN];
    if (GetTimeFormatA(LOCALE_USER_DEFAULT, 0, 0,
					   "HH':'mm':'ss", buffer, MAX_LEN) == 0)
        return "Error in NowTime()";
	
    char result[100] = {0};
    static DWORD first = GetTickCount();
    std::sprintf(result, "%s.%03ld", buffer, (long)(GetTickCount() - first) % 1000);
    return result;
}

#else

#include <sys/time.h>

inline std::string NowTime()
{
    char buffer[11];
    time_t t;
    time(&t);
    tm r = {0};
    strftime(buffer, sizeof(buffer), "%X", localtime_r(&t, &r));
    struct timeval tv;
    gettimeofday(&tv, 0);
    char result[100] = {0};
    std::sprintf(result, "%s.%03ld", buffer, (long)tv.tv_usec / 1000);
    return result;
}

#endif //WIN32
//------------------------------------------------------------------------------

#endif //__LOG_H__