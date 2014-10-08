#ifndef AINIReader_h_
#define AINIReader_h_

#include <string>

class AINIReader
{
public:
	enum parsingStatus
	{
		Success = 0,
		ErrorFileOpen = -1,
		ErrorMemoryAllocation = -2,
		ErrorParsing = -3,
	};

protected:
	virtual parsingStatus pParseFile(const std::string & filePath);
	virtual parsingStatus pParseFile(const std::string & filePath, int & errorLine);
	// Return true if no error
	virtual bool pOnNewKey(const char * section, const char * name, const char * value) = 0;

private:
	static int _valueHandler(void * user, const char * section, const char * name, const char * value);
};

#endif