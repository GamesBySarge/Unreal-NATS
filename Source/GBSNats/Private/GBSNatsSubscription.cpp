#include "GBSNatsSubscription.h"

UGBSNatsSubscription::UGBSNatsSubscription(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
}

void UGBSNatsSubscription::SetSubject(const FString& Subject)
{
  this->m_Subject = Subject;
}