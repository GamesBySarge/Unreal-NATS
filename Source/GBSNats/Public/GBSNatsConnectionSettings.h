#pragma once

#include "GBSNatsConnectionSettings.generated.h"

UCLASS(BlueprintType, Blueprintable)
class GBSNATS_API UGBSNatsConnectionSettings : public UObject
{
  GENERATED_UCLASS_BODY()

public:

  /**
   * Add a server to the connection.
   * 
   * This should be fully qualified, such as "nats://user:password:x.x.x.x:xxxx"
   */
  UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Category = "GBSNats|Connection")
  void AddServer(const FString& Server);

private:
  TArray<FString> Servers;
};

