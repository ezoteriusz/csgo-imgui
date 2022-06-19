#pragma once

namespace framestage {
	using org = void(__fastcall*)(void* ecx, void* udx, ClientFrameStageT);
	inline org oFrameStage = nullptr;
	void __fastcall hkFrameStage(void* ecx, void* udx,ClientFrameStageT id);
}