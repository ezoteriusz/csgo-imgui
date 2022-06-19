#pragma once

namespace createMove {
	using org = bool(__fastcall*)(void* ecx, void* udx,float, CUserCmd*);
	inline org oCreateMove = nullptr;
	bool __fastcall hkCreateMove(void* ecx, void* udx,float frameTime, CUserCmd* command);
}