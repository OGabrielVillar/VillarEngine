#pragma once

#include "Texture.h"

class MemoryManager
{
public:
	MemoryManager();
	~MemoryManager();
	void InitTextureBlock(unsigned int many_textures);
	void LoadTexture(unsigned int id_in);
	void LoadTexture(unsigned int id_in, char* txr_link_in);//Illegal way, just for early tests.
	void ResetTextureBlock();//Free the memory
	Texture& GetTexture(unsigned int id_in);
private:
	bool is_texture_block_initialized = false;
	Texture** texture_block = nullptr;
	bool* is_texture_id_loaded = nullptr;
	unsigned int many_textures;
};