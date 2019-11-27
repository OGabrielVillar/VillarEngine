#pragma once
#include <vector>

template<typename T>
class List
{
public:
	List()
		:
		element_size(6)
	{
	}
	List(int element_size_in)
		:
		element_size(element_size_in)
	{
	}
	~List()
	{
		for (int i = (int)ptrs.size(); i > 0; i--)
		{
			DeleteBackLayer();
		}//Delete every layer in the vector
	}

	T& operator[](int index)
	{
		return ptrs[index / element_size][index%element_size];
	}

public:
	T& GetLastElement() const
	{
		return *pLastElement;
	}
	void PushElement(const T& input)
	{
		if (pLastElement == nullptr)
		{
			GenerateBackLayer();
			pLastElement = ptrs[0];
		}
		else if (pLastElement == pContainerEnd)
		{
			GenerateBackLayer();
			pLastElement = pContainerEnd - (element_size - 1);
		}
		else
		{
			pLastElement++;
		}
		*pLastElement = input;
	}
	void EraseBackElement()
	{
		if (pLastElement == nullptr)
		{
			return;
		}
		else if (pLastElement == pContainerEnd - (element_size - 1))
		{
			DeleteBackLayer();
		}
		else
		{
			*pLastElement = T();
			pLastElement--;
		}
	}
	int capacity()
	{
		return ptrs.size() * element_size;
	}
private:
	void GenerateBackLayer() {
		T* layer = new T[element_size];
		ptrs.push_back(layer);
		pContainerEnd = &layer[element_size - 1];
	}
	void DeleteBackLayer()
	{
		delete[]ptrs.back();													//Free the memory,
		ptrs.pop_back();														//Shrinks the vector,
		if (ptrs.size() == 0) {													//If there's no more element, 
			pContainerEnd = nullptr; pLastElement = nullptr;					//	Untarget the pointers.
		}
		else {																	//Else,
			pContainerEnd = &ptrs[ptrs.size() - 1][element_size - 1];			//	Target the End with the last element, and
			pLastElement = pContainerEnd;										//	Assign the last element with the end.
		}
	}

private:
	const int element_size;
	std::vector<T*> ptrs;
	T* pLastElement = nullptr;
	T* pContainerEnd = nullptr;
};