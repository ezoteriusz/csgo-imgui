#pragma once
struct player_info_t { // global https://github.com/perilouswithadollarsign/cstrike15_src/blob/master/public/cdll_int.h#L129
	int64_t __pad0;
	union {
		int64_t xuid;
		struct {
			int xuidlow;
			int xuidhigh;
		};
	};
	char name[128];
	int userid;
	char guid[33];
	unsigned int friendsid;
	char friendsname[128];
	bool fakeplayer;
	bool ishltv;
	unsigned int customfiles[4];
	unsigned char filesdownloaded;
};

class IClientEngine {
public:
	int getLocalPlayerIndex()
	{
		using original = int(__thiscall*)(IClientEngine*);
		return (*(original**)this)[12](this);
	}
	bool isInGame()
	{
		using original = bool(__thiscall*)(IClientEngine*);
		return (*(original**)this)[26](this);
	}
	void GetPlayerInfo(int index, player_info_t* info) {
		using original_fn = void(__thiscall*)(IClientEngine*, int, player_info_t*);
		return (*(original_fn**)this)[8](this, index, info);
	}
	bool isConnected()
	{
		using original = bool(__thiscall*)(IClientEngine*);
		return (*(original**)this)[27](this);
	}
	int getMaxClients()
	{
		using original = int(__thiscall*)(IClientEngine*);
		return (*(original**)this)[20](this);
	}
	void getScreenSize(int& w, int& h)
	{
		using original_fn = void(__thiscall*)(IClientEngine*, int&, int&);
		return (*(original_fn**)this)[5](this, w, h);
	}
};