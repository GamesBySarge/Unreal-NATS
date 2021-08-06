#include "GBSNatsConnection.h"

#include "GBSNatsSubscription.h"

UGBSNatsConnection::UGBSNatsConnection(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
}

void UGBSNatsConnection::SetSettings(UGBSNatsConnectionSettings *Settings)
{
  this->ConnectionSettings = Settings;
}

void UGBSNatsConnection::Connect()
{
  // TODO Probably should return an error of some sort.
}

UGBSNatsSubscription* UGBSNatsConnection::Subscribe(const FString& Subject)
{
  auto sub = NewObject<UGBSNatsSubscription>(this);

  // TODO set the subject
  sub->SetSubject(Subject);

  return sub;
}