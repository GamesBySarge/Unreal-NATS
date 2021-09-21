#include "GBSNatsConnection.h"

#include "GBSNatsSubscription.h"

#ifdef USE_NATS
#include "nats/nats.h"
#include <string.h>
#endif


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
#ifdef USE_NATS
  natsStatus s = NATS_OK;

  FString ConnectionString = *this->ConnectionSettings->GetConnectionString();
  UE_LOG(LogGBSNats, Log, TEXT("Connecting to %s"), *ConnectionString);

  s = natsConnection_ConnectTo(&this->natsConn, TCHAR_TO_ANSI(*ConnectionString));
  if (s != NATS_OK)
  {
      FString ErrorMessage = ANSI_TO_TCHAR(natsStatus_GetText(s));
      UE_LOG(LogGBSNats, Log, TEXT("Error connecting to %s: %s"), *ConnectionString, *ErrorMessage);
  }
#endif
}

UGBSNatsSubscription *UGBSNatsConnection::Subscribe(const FString& Subject, const FOnMessage& OnMessage)
{
  UGBSNatsSubscription* sub = NewObject<UGBSNatsSubscription>(this);

  sub->SetSubject(Subject);
  sub->SetDelegate(OnMessage);

#ifdef USE_NATS
  sub->SetConnection(this->natsConn);
#endif

  sub->DoSubscription(Subject);

  return sub;
}

void UGBSNatsConnection::Publish(const FString& Subject, const FString& Message)
{
#ifdef USE_NATS
  natsConnection_PublishString(this->natsConn, TCHAR_TO_ANSI(*Subject), TCHAR_TO_ANSI(*Message));
#endif
}

FString UGBSNatsConnection::RequestString(const FString& Subject, const FString& Request)
{
  FString reply;
#ifdef USE_NATS
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
#endif

  return reply;
}

UGBSNatsSubscription* UGBSNatsConnection::PublishRequestString(const FString& Subject, const FString& ReplySubject, const FString& Request)
{
  UGBSNatsSubscription* sub = NewObject<UGBSNatsSubscription>(this);

  sub->SetSubject(ReplySubject);

#ifdef USE_NATS
  natsConnection_PublishRequestString(this->natsConn, TCHAR_TO_ANSI(*Subject), TCHAR_TO_ANSI(*ReplySubject), TCHAR_TO_ANSI(*Request));
#endif

  return sub;
}
