#include "MemoryManager.h"

MemoryManager::MemoryManager()
{
}

MemoryManager::~MemoryManager()
{
	ResetTextureBlock();
}

void MemoryManager::InitTextureBlock(unsigned int many_textures_in)
{
	if (is_texture_block_initialized)
	{
		return; //Error
	}
	texture_block = new Texture*[many_textures_in] {nullptr};
	is_texture_id_loaded = new bool[many_textures_in] {false};
	many_textures = many_textures_in;
	is_texture_block_initialized = true;
}

void MemoryManager::LoadTexture(unsigned int id_in)
{
	if (id_in >= many_textures)
	{
		return; // error, id_in exceeds the limit
	}
	if (is_texture_id_loaded[id_in])
	{
		return; // optimal error, duplicated loading
	}

}

void MemoryManager::LoadTexture(unsigned int id_in, char * txr_link_in)//Illegal way, just for early tests.
{
	if (id_in >= many_textures)
	{
		return; // error, id_in exceeds the limit
	}
	if (is_texture_id_loaded[id_in])
	{
		return; // optimal error, duplicated loading
	}
	texture_block[id_in] = new Texture(txr_link_in);
	is_texture_id_loaded[id_in] = true;
}

void MemoryManager::ResetTextureBlock()
{
	for (unsigned int i = 0; i < many_textures; i++)
	{
		if (is_texture_id_loaded[i])
		{
			delete texture_block[i];
		}
	}
	delete [] texture_block;
	delete [] is_texture_id_loaded;
	texture_block = nullptr;
	is_texture_id_loaded = nullptr;
	many_textures = 0;
	is_texture_block_initialized = false;
}

Texture & MemoryManager::GetTexture(unsigned int id)
{
	return *texture_block[id];
}
