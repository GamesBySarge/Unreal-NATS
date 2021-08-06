#include "GBSNatsSubsystem.h"


UGBSNatsSubsystem::UGBSNatsSubsystem()
	: UEngineSubsystem()
{
}


void UGBSNatsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UGBSNatsSubsystem::Deinitialize()
{
	// Do nothing for now
	Super::Deinitialize();
}

UGBSNatsConnectionSettings* UGBSNatsSubsystem::CreateConnectionSettings()
{
  UGBSNatsConnectionSettings* NewValue = NewObject<UGBSNatsConnectionSettings>(this);
  return NewValue;
}

UGBSNatsConnection* UGBSNatsSubsystem::CreateConnection(UGBSNatsConnectionSettings* ConnectionSettings)
{
  UGBSNatsConnection* NewValue = NewObject<UGBSNatsConnection>(this);
  NewValue->SetSettings(ConnectionSettings);
  return NewValue;
}
