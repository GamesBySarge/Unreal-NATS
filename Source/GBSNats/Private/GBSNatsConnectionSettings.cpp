#include "GBSNatsConnectionSettings.h"

UGBSNatsConnectionSettings::UGBSNatsConnectionSettings(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
  // TODO this is being leaked; destroy it later, but when?
  natsOptions_Create(&this->opts);
}

void UGBSNatsConnectionSettings::AddServer(const FString& Server)
{
  Servers.Add(Server);
}

void UGBSNatsConnectionSettings::SetExpectedHostName(const FString& HostName)
{
  // TODO Handle errors
  natsOptions_SetExpectedHostname(this->opts, TCHAR_TO_ANSI(*HostName));
}

void UGBSNatsConnectionSettings::SkipServerVerification(const bool Skip)
{
  // TODO Handle errors
  natsOptions_SkipServerVerification(this->opts, Skip);
}

FString UGBSNatsConnectionSettings::GetConnectionString()
{
  FString connectionString = FString::Join(this->Servers, TEXT(", "));
  return connectionString;
}

natsOptions* UGBSNatsConnectionSettings::GetOptions()
{
  return this->opts;
}
