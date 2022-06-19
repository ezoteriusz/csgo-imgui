#pragma once
#include "../structs/valve/structs/clientclass.h"
class IClientMode; // clientmode

class IClient
{
public:
	CClientClass* GetClientAllClasses() {
		using original_fn = CClientClass * (__thiscall*)(IClient*);
		return (*(original_fn**)this)[8](this);
	}
};
