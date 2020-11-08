#include "FileStream.h"

void FileStream::OpenFile(const char * cP_in)
{
	in.open(cP_in, std::ios::binary);
}

