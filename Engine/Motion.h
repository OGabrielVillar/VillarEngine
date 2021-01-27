#pragma once

#include "Reference.h"

template<class T>
class Motion
{
public:
	Motion(Reference<T>* reference_in) :
		reference(reference_in)
	{
		
	}
	~Motion() {
		reference->RemoveUser();
		delete [] key_times;
		delete [] key_values;
	}

public:
	//
	void Go(float ft_in) {
		if (!reference->IsActive())
		{
			active = false;
			return;
		}

		needle += ft_in;
		if (needle >= end)//CHECKS IF NEEDLE PASSES THE END
		{
			if (one_hit_motion)//CHECKS IF IT'S A NON LOOPING ANIMATION
			{
				*reference->GetReference() = key_values[many_keys-1];
				active = false;
				return;
			}

			float remnant = std::floorf(needle / end);
			needle -= end * remnant;
			key = 0;
		}

		//IF THE LAST KEY IS SMALLER THEN THE KEY LIMIT IT LOOPS UNTIL IT FINDS THE KEY TIME THAT IS GREATER THEN THE NEEDLE TIME
		for (; key < many_keys && needle >= key_times[key]; ){
			key++;
		}
		//THEN IT APPLIES THE CHANGES
		*reference->GetReference() = key_values[key];
	}

	//
	bool IsActive() {
		return active;
	}

	//
	void SetUpKeys(float* times_in, T* values_in, unsigned int many_keys_in) {

		if (many_keys != 0)
		{
			return;
		}

		active = true;
		many_keys = many_keys_in;
		key_times = new float[many_keys_in];
		key_values = new T[many_keys_in];

		float time_sum = 0.0f;
		for (unsigned int i = 0; i < many_keys_in; i++)
		{
			time_sum += times_in[i];
			key_times[i] = time_sum;
			key_values[i] = values_in[i];
		}
		end = key_times[many_keys-1];

	}
private:
	bool active = false;

	float end = 0.0f;
	float needle = 0.0f;

	float* key_times = nullptr;
	T* key_values = nullptr;
	unsigned int many_keys = 0;
	unsigned int key = 0;

	Reference<T>* reference;

	//motion personalization
	bool one_hit_motion = false;
};