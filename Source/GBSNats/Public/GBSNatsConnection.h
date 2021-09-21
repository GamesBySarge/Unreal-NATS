#pragma once

#include "GBSNatsConnectionSettings.h"
#include "GBSNatsSubscription.h"

#ifdef USE_NATS
#include "nats/nats.h"
#endif

#include "GBSNatsConnection.generated.h"


UCLASS(BlueprintType, Blueprintable)
class GBSNATS_API UGBSNatsConnection : public UObject
{
  GENERATED_UCLASS_BODY()

  //////////////////////////////////////////////////////
  // The fun stuff goes here
public:
  UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Category = "GBSNats|PubSub")
  UGBSNatsSubscription* Subscribe(const FString& Subject, const FOnMessage& OnMessage);

  UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Category = "GBSNats|PubSub")
  void Publish(const FString& Subject, const FString& Message);

  UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Category = "GBSNats|ReqRep")
  FString RequestString(const FString& Subject, const FString& Request);

  UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Category = "GBSNats|ReqRep")
  UGBSNatsSubscription* PublishRequestString(const FString& Subject, const FString& ReplySubject, const FString& Request);

  //////////////////////////////////////////////////////
  // Internal use only, not exposed to blueprints.
public:
  void SetSettings(UGBSNatsConnectionSettings* ConnectionSettings);
  void Connect();

protected:

  UPROPERTY()
  UGBSNatsConnectionSettings* ConnectionSettings;

private:
#ifdef USE_NATS
  natsConnection *natsConn;
#endif
};

