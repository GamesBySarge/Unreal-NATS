#include "GBSNatsConnectionSettings.h"

UGBSNatsConnectionSettings::UGBSNatsConnectionSettings(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
}

void UGBSNatsConnectionSettings::AddServer(const FString& Server)
{
  Servers.Add(Server);
}
