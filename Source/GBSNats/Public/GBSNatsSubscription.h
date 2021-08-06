#pragma once

#include "GBSNatsSubscription.generated.h"

/** Generate a delegate for callback events */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMessage, class UGBSNatsSubscription*, Message);

UCLASS(BlueprintType, Blueprintable)
class GBSNATS_API UGBSNatsSubscription : public UObject
{
  GENERATED_UCLASS_BODY()

  //////////////////////////////////////////////////////
  // The fun stuff goes here
public:
  UPROPERTY(BlueprintAssignable, Category = "GBSNats|Event")
  FOnMessage OnMessage;

  //////////////////////////////////////////////////////
  // Internal use only, not exposed to blueprints.
public:
  void SetSubject(const FString& Subject);

private:
  FString m_Subject;
};
