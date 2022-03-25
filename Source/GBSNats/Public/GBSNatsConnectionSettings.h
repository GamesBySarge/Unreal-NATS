#pragma once

#include "nats/nats.h"

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

  /**
   * Sets the expected host name
   * 
   * Use this if the server name to which you're connecting is different from
   * that server's internal host name.
   */
  UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Category = "GBSNats|Connection")
  void SetExpectedHostName(const FString& HostName);

  /**
   * Skip the TLS verification
   */
  UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Category = "GBSNats|Connection")
  void SkipServerVerification(const bool Skip);

  /////////////////////////////////////////////////////
  // Internal C++ stuff, not used by blueprints
public:
  FString GetConnectionString();
  natsOptions* GetOptions();

private:
  TArray<FString> Servers;
  natsOptions* opts;
};
