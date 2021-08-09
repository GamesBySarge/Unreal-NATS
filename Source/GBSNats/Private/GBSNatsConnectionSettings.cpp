#include "GBSNatsConnectionSettings.h"

UGBSNatsConnectionSettings::UGBSNatsConnectionSettings(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
}

void UGBSNatsConnectionSettings::AddServer(const FString& Server)
{
  Servers.Add(Server);
}


FString UGBSNatsConnectionSettings::GetConnectionString()
{
  FString connectionString = FString::Join(this->Servers, TEXT(", "));
  return connectionString;
}
