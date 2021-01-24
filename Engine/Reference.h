#pragma once

#include "Vec2.h"

template<class T>
class Reference
{
public:
	Reference(T* server_in):
		server(server_in)
	{

	}
	void AddUser() {
		many_users++;
	}
	void RemoveUser() {
		many_users--;
		if (many_users == 0)
		{
			delete this;
		}
	}
	T* GetReference() {
		return server;
	}
	bool IsActive() {
		return active;
	}
private:
	bool active = true;
	T* server;
	unsigned int many_users = 1;
};

//use ints/floats/strings/chars/vec2/vec3 as template.

//with 0 users it should delete itself.

//when the server got deleted, put this in inactive state until every user got disconected with this reverence, then delete *this.