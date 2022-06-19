#pragma once
#include "../utils.h"
#include "../valve/structs/usercmd.h"
#include "../../interfaces/interfaces.h"

#include "../../library/minhook/minhook.h"

//imgui
#include "../../library/imgui/imgui.h"
#include "../../library/imgui/imgui_impl_dx9.h"
#include "../../library/imgui/imgui_impl_win32.h"


#include "../../features/features.h"
#include "../../gui/menu/variables.h"

//hooks
#include "core/createmove.h"
#include "core/dopostspacescreeneffects.h"
#include "core/framestage.h"
#include "core/painttraverse.h"
#include "core/presentscene.h"

namespace global {
inline CEntity* localPlayer;
}

class CHooks {
public:
	bool init();
	void detach();
private:
	inline unsigned int getVirtualTable(void* _class, unsigned int index) { return static_cast<unsigned int>((*static_cast<int**>(_class))[index]); }
};
extern CHooks gHooks;