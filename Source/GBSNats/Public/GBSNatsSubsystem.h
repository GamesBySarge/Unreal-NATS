# pragma once

#include "GBSNatsConnection.h"

#include "Subsystems/EngineSubsystem.h"

#include "GBSNatsSubsystem.generated.h"

UCLASS(BlueprintType, Blueprintable)
class GBSNATS_API UGBSNatsSubsystem : public UEngineSubsystem
{
  GENERATED_BODY()

public:
  UGBSNatsSubsystem();

	// Begin USubsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// End USubsystem

  /////////////////////////////////////////////////
  // GBSNats processing
public:
  UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Category = "GBSNats|Connection")
  UGBSNatsConnectionSettings* CreateConnectionSettings();

  UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Category = "GBSNats|Connection")
  UGBSNatsConnection* CreateConnection(UGBSNatsConnectionSettings* ConnectionSettings);
};
