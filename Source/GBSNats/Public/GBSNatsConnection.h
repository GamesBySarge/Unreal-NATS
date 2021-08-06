#pragma once

#include "GBSNatsConnectionSettings.h"

#include "GBSNatsConnection.generated.h"

UCLASS(BlueprintType, Blueprintable)
class GBSNATS_API UGBSNatsConnection : public UObject
{
  GENERATED_UCLASS_BODY()

  //////////////////////////////////////////////////////
  // The fun stuff goes here
public:
  UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Category = "GBSNats|Connection")
  UGBSNatsSubscription* Subscribe(const FString& Subject);

  //////////////////////////////////////////////////////
  // Internal use only, not exposed to blueprints.
public:
  void SetSettings(UGBSNatsConnectionSettings* ConnectionSettings);
  void Connect();

protected:

  UPROPERTY()
  UGBSNatsConnectionSettings* ConnectionSettings;
};

