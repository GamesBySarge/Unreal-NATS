#pragma once

#ifdef USE_NATS
#include "nats/nats.h"
#endif

#include "GBSNatsSubscription.generated.h"

/** Generate a delegate for callback events */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMessage, FString, Subject, FString, Message);

UCLASS(BlueprintType, Blueprintable)
class GBSNATS_API UGBSNatsSubscription : public UObject
{
  GENERATED_UCLASS_BODY()

  //////////////////////////////////////////////////////
  // The fun stuff goes here
public:
  UPROPERTY(BlueprintAssignable, Category = "GBSNats|PubSub")
  FOnMessage OnMessage;

  //////////////////////////////////////////////////////
  // Internal use only, not exposed to blueprints.
public:
#ifdef USE_NATS
  void SetConnection(natsConnection* nc);
#endif

  void SetSubject(const FString& Subject);
  void DoSubscription(const FString& subject);
  void InternalOnMessage(const FString& Subject, const FString& Message);

private:
  FString m_Subject;
#ifdef USE_NATS
  natsConnection* natsConn;
  natsSubscription* natsSub;
#endif
};
