#pragma once
#include "../structs/utils.h"


#include "../structs/valve/class/CEntity.h"
#include "iclient.h"
#include "icliententitylist.h"
#include "iglowmanager.h"
#include "ivengineclient.h"
#include "ivdebugoverlay.h"
#include "isurface.h"
#include "ipanel.h"



// directx9 sdk
#include <d3dx9.h>
#include <d3d9.h>
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"d3d9.lib")

class CInterfaces {
public:
	bool init();
	IClient* client;
	IClientMode* clientMode;
	IClientEntityList* entList;
	IGlowManager* glowManager;
	IClientEngine* engine;
	IDebugOverlay* debugOverlay;
	ISurface* surface;
	IPanel* panel;
	IDirect3DDevice9* directx9;
private:
	void* getInterface(const char* mod, const char* iface);
};
extern CInterfaces gInterfaces;