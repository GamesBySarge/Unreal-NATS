#include "GBSNatsConnection.h"

#include "GBSNatsSubscription.h"

#include "nats/nats.h"
#include <string>


UGBSNatsConnection::UGBSNatsConnection(const class FObjectInitializer &PCIP)
    : Super(PCIP)
{
}

void UGBSNatsConnection::SetSettings(UGBSNatsConnectionSettings *Settings)
{
  this->ConnectionSettings = Settings;
}

void UGBSNatsConnection::Connect()
{
  natsStatus s = NATS_OK;

  s = natsConnection_Connect(&this->natsConn, this->ConnectionSettings->GetOptions());
  if (s != NATS_OK)
  {
      FString ErrorMessage = ANSI_TO_TCHAR(natsStatus_GetText(s));
      UE_LOG(LogGBSNats, Log, TEXT("Error connecting to nats server: %s"), *ErrorMessage);
  }
}

UGBSNatsSubscription *UGBSNatsConnection::Subscribe(const FString& Subject, const FOnMessage& OnMessage)
{
  UGBSNatsSubscription* sub = NewObject<UGBSNatsSubscription>(this);

  sub->SetSubject(Subject);
  sub->SetDelegate(OnMessage);

  sub->SetConnection(this->natsConn);

  sub->DoSubscription(Subject);

  return sub;
}

void UGBSNatsConnection::Publish(const FString& Subject, const FString& Message)
{
  natsConnection_PublishString(this->natsConn, TCHAR_TO_ANSI(*Subject), TCHAR_TO_ANSI(*Message));
}

FString UGBSNatsConnection::RequestString(const FString& Subject, const FString& Request)
{
  FString reply;

  natsMsg* msg;
  // TODO Don't hard-code the timeout.
  int64_t timeout = 1000;

  auto s = natsConnection_RequestString(&msg, this->natsConn, TCHAR_TO_ANSI(*Subject), TCHAR_TO_ANSI(*Request), timeout);
  if (s == NATS_OK)
  {
    std::string cstr(reinterpret_cast<const char*>(natsMsg_GetData(msg)), natsMsg_GetDataLength(msg));
    reply = (cstr.c_str());
    natsMsg_Destroy(msg);
  }

  return reply;
}

UGBSNatsSubscription* UGBSNatsConnection::PublishRequestString(const FString& Subject, const FString& ReplySubject, const FString& Request)
{
  UGBSNatsSubscription* sub = NewObject<UGBSNatsSubscription>(this);

  sub->SetSubject(ReplySubject);

  natsConnection_PublishRequestString(this->natsConn, TCHAR_TO_ANSI(*Subject), TCHAR_TO_ANSI(*ReplySubject), TCHAR_TO_ANSI(*Request));

  return sub;
}
