#include "netvar.h"
#include "../../interfaces/interfaces.h"
#include <fstream>
#include <format>
CNetvars gNetvars;
void CNetvars::Setup()
{
	// loop through linked-list and recursicely dump
	for (CClientClass* client = gInterfaces.client->GetClientAllClasses(); client; client = client->next)
		if (CRecvTable* table = client->table)
			Dump(client->networkName, table, 0);
}

void CNetvars::Dump(const std::string_view base, CRecvTable* table, const std::uint32_t offset)
{
	std::fstream netvarDump;
	// loop through props
	for (auto i = 0; i < table->count; ++i) {
		const CRecvProp* prop = &table->props[i];

		if (!prop)
			continue;

		if (std::isdigit(prop->name[0]))
			continue;

		if (hash::RunTime(prop->name) == hash::CompileTime("baseclass"))
			continue;

		// not a root table, dump again
		if (prop->type == ESendPropType::DATATABLE &&
			prop->table &&
			prop->table->name[0] == 'D')
			Dump(base, prop->table, offset + prop->offset);

		const auto netvarName = std::format("{}->{}", base, prop->name);

		// place offset in netvar map
		data[hash::RunTime(std::format("{}->{}", base, prop->name).c_str())] = offset + prop->offset;
		/*netvarDump.open("netvars.txt", std::ios::out | std::ios::in | std::ios::app);
		if (netvarDump.is_open())
		{
			netvarDump << "[NETVAR] " << netvarName << " found in class " << base << "\n";
			netvarDump.close();
		}
		netvarDump.close();*/
	}
}