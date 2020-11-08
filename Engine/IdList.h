#pragma once
template <class T>
class IdListBlock
{
public:
	IdListBlock() = default;
	IdListBlock(unsigned int id_in);
	~IdListBlock() = default;
	void PushElement(T& element_in);
	T* GetElement();
	IdListBlock<T>* GenerateNextBlock(unsigned int id_in);
	IdListBlock<T>* GetPreviousBlock();
	IdListBlock<T>* GetNextBlock();
private:
	T* element = nullptr;
	IdListBlock<T>* previous_block = nullptr;
	IdListBlock<T>* next_block = nullptr;
	unsigned int id;
};

template<class T>
inline IdListBlock<T>::IdListBlock(unsigned int id_in)
{
	id = id_in;
}

template<class T>
inline void IdListBlock<T>::PushElement(T & element_in)
{
	element = new T(element_in);
}

template<class T>
inline T * IdListBlock<T>::GetElement()
{
	if (&*this == NULL) {
		return NULL;
	}
	return element;
}

template<class T>
inline IdListBlock<T>* IdListBlock<T>::GenerateNextBlock(unsigned int id_in)
{
	next_block = new IdListBlock<T>(id_in);
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
class IdList {
public:
	IdList() = default;
	~IdList() = default;
public://FUNCTIONS
	T* operator [](unsigned int);
	//void ClearRem();
	void PushElement(T& element_in);
	IdListBlock<T>* GetFirstBlock();
	IdListBlock<T>* GetLastBlock();
	T* GetFirstElement();
	T* GetLastElement();
	unsigned int ManyElements();
private://PRIVATE FUNCTIONS
	void NewBlock();
	IdListBlock<T>* SeekBlock(unsigned int id);
private:
	unsigned int many_elements = 0;
	unsigned int id_count = 0;
	IdListBlock<T>* first_block = nullptr;
	IdListBlock<T>* last_block = nullptr;
};

template<class T>
inline T * IdList<T>::operator[](unsigned int x)
{
	return SeekBlock(x)->GetElement();
}

template<class T>
inline void IdList<T>::PushElement(T & element_in)
{
	NewBlock();
	last_block->PushElement(element_in);
}

template<class T>
inline IdListBlock<T>* IdList<T>::GetFirstBlock()
{
	return first_block;
}

template<class T>
inline IdListBlock<T>* IdList<T>::GetLastBlock()
{
	return last_block;
}

template<class T>
inline T* IdList<T>::GetFirstElement()
{
	return first_block->GetElement();
}

template<class T>
inline T* IdList<T>::GetLastElement()
{
	return last_block->GetElement();
}

template<class T>
inline unsigned int IdList<T>::ManyElements()
{
	return many_elements;
}

template<class T>
inline void IdList<T>::NewBlock()
{
	if (many_elements == 0)
	{
		first_block = new IdListBlock<T>(0);
		last_block = first_block;
	}
	else
	{
		last_block = last_block->GenerateNextBlock(id_count);
	}
	id_count++;
	many_elements++;
}

template<class T>
inline IdListBlock<T>* IdList<T>::SeekBlock(unsigned int id)
{
	if (id >= many_elements)
	{
		return NULL;
	}
	if (id == 0)
	{
		return first_block;
	}
	IdListBlock<T>* seek = first_block;
	for (int i = 1; i <= id; i++)
	{
		seek = seek->GetNextBlock();
	}
	return seek;
}





template <class T>
class IdListReader
{
public:
	IdListReader(IdList<T>* list_in);
	~IdListReader() = default;
	T* Get();
	T* PeekNext();
	void Next();
	T* PeekPrevious();
	bool IsTheLastElement();
	bool Ended();
	void Reset();
private:
	IdList<T>* id_list = nullptr;
	IdListBlock<T>* current_block = nullptr;
};

template<class T>
inline IdListReader<T>::IdListReader(IdList<T>* list_in)
{
	id_list = list_in;
	current_block = list_in->GetFirstBlock();
}

template<class T>
inline void IdListReader<T>::Next()
{
	current_block = current_block->GetNextBlock();
}

template<class T>
inline T* IdListReader<T>::Get()
{
	return current_block->GetElement();
}

template<class T>
inline T * IdListReader<T>::PeekNext()
{
	return current_block->GetNextBlock()->GetElement();
}

template<class T>
inline T* IdListReader<T>::PeekPrevious()
{
	return current_block->GetPreviousBlock()->GetElement();
}

template<class T>
inline bool IdListReader<T>::IsTheLastElement()
{
	if (current_block == id_list->GetLastBlock())
	{
		return true;
	}
	return false;
}

template<class T>
inline bool IdListReader<T>::Ended()
{
	if (current_block == NULL)
	{
		return true;
	};
	return false;
}

template<class T>
inline void IdListReader<T>::Reset()
{
	current_block = id_list->GetFirstBlock();
}
