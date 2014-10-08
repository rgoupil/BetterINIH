#include "AINIReader.h"
#include "ini.h"

int AINIReader::_valueHandler(void * user, const char * section, const char * name, const char * value)
{
	AINIReader * reader = (AINIReader *)user;
	bool ret = reader->pOnNewKey(section, name, value);
	return (ret ? 1 : 0);
}

AINIReader::parsingStatus AINIReader::pParseFile(const std::string & filePath)
{
	int tmp;
	return pParseFile(filePath, tmp);
}

AINIReader::parsingStatus AINIReader::pParseFile(const std::string & filePath, int & errorLine)
{
	int ret = ini_parse(filePath.c_str(), _valueHandler, this);
	if (ret > 0)
	{
		errorLine = ret;
		ret = (int)parsingStatus::ErrorParsing;
	}

	return (parsingStatus)ret;
}