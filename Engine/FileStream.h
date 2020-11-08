#pragma once

	#include <conio.h>
	#include <fstream>

class FileStream
{
public:
	FileStream() = default;
	~FileStream() = default;
	void OpenFile(const char* cP_in);
	template <class inT>
	inT Read();
	template <class outT>
	void Write(outT out_buffer, const char * name);
private:
	std::ifstream in;
	std::ofstream out;
};



template<class inT>
inline inT FileStream::Read()
{
	inT* buffer = new inT;
	in.read(reinterpret_cast<char*>(buffer), sizeof(inT));
	return *buffer;
}

template<class outT>
inline void FileStream::Write(outT out_buffer,const char * name)
{
	std::string link = std::string("test/");
	link += name;
	link += ".txt";
	out.open(link, std::ios::binary);
	out.seekp(in.tellg(), std::ios_base::beg);
	out.write(reinterpret_cast<const char*>(&out_buffer), sizeof(outT));
}

