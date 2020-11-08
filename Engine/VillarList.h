#pragma once
#define BLOCK_SIZE 1
template <class T>
class IdListBlock
{
public:
	IdListBlock() = default;
	~IdListBlock() = default;
	T* operator [](unsigned int);
	void PushElement(T& element_in);
	T* GetElement(unsigned int id);
	IdListBlock<T>* GenerateNextBlock();
	IdListBlock<T>* GetPreviousBlock();
	IdListBlock<T>* GetNextBlock();
private:
	T* elements[BLOCK_SIZE];
	IdListBlock<T>* previous_block;
	IdListBlock<T>* next_block;
	unsigned int many_elements = 0;
	unsigned int id;
};

template<class T>
inline T * IdListBlock<T>::operator[](unsigned int id)
{
	return elements[id];
}

template<class T>
inline void IdListBlock<T>::PushElement(T & element_in)
{
	if (many_elements == BLOCK_SIZE)
	{
		return;
	}
	elements[many_elements] = new T(element_in);
	many_elements++;
}

template<class T>
inline T * IdListBlock<T>::GetElement(unsigned int id)
{
	return elements[id];
}

template<class T>
inline IdListBlock<T>* IdListBlock<T>::GenerateNextBlock()
{
	next_block = new IdListBlock<T>;
	return next_block;
}

template<class T>
inline IdListBlock<T>* IdListBlock<T>::GetPreviousBlock()
{
	return previous_block;
}

template<class T>
inline IdListBlock<T>* IdListBlock<T>::GetNextBlock()
{
	return next_block;
}







template <class T>
class VList {
public:
	VList() = default;
	~VList() = default;
public://FUNCTIONS
	T* operator [](unsigned int);
	//void ClearRem();
	void PushElement(T& element_in);
	IdListBlock<T>* Next();
	IdListBlock<T>* PeekNext();
	IdListBlock<T>* GetCurrent();
	IdListBlock<T>* GetPrevious();
	bool last_one();
private://PRIVATE FUNCTIONS
	void NewBlock();
	IdListBlock<T>* SeekBlock(unsigned int id);
private:
	unsigned int many_next_blocks = 0;
	unsigned int many_elements = 0;
	IdListBlock<T> first_block;
	IdListBlock<T>* last_block = &first_block;
	IdListBlock<T>* current_block = &first_block;
};

template<class T>
inline T * VList<T>::operator[](unsigned int x)
{
	int z = x % BLOCK_SIZE;
	return SeekBlock((x - z) / BLOCK_SIZE)->GetElement(z);
}

template<class T>
inline void VList<T>::PushElement(T & element_in)
{
	if ((many_elements) % BLOCK_SIZE == 0)
	{
		if (many_elements != 0)
		{
			NewBlock();
		}
	}
	last_block->PushElement(element_in);
	many_elements++;
}

template<class T>
inline IdListBlock<T>* VList<T>::Next()
{
	current_block = current_block->GetNextBlock();
	return current_block;
}

template<class T>
inline IdListBlock<T>* VList<T>::PeekNext()
{
	return current_block->GetNextBlock();
}

template<class T>
inline IdListBlock<T>* VList<T>::GetCurrent()
{
	return current_block;
}

template<class T>
inline IdListBlock<T>* VList<T>::GetPrevious()
{
	return current_block->GetPreviousBlock();
}

template<class T>
inline bool VList<T>::last_one()
{
	return current_block == last_block;
}

template<class T>
inline void VList<T>::NewBlock()
{
	last_block = last_block->GenerateNextBlock();
	many_next_blocks++;
}

template<class T>
inline IdListBlock<T>* VList<T>::SeekBlock(unsigned int id)
{
	if (id == 0)
	{
		return &first_block;
	}
	IdListBlock<T>* seek = &first_block;
	for (unsigned int i = 0; i < many_next_blocks; i++)
	{
		seek = seek->GetNextBlock();
	}
	return seek;
}

