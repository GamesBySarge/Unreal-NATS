#include "GBSNatsConnection.h"

#include "GBSNatsSubscription.h"

#ifdef USE_NATS
#include "nats/nats.h"
#endif

GBSNATS_API DECLARE_LOG_CATEGORY_EXTERN(LogGBSNats, Log, All);

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

  const char* connString = TCHAR_TO_ANSI(*this->ConnectionSettings->GetConnectionString());
  UE_LOG(LogGBSNats, Log, TEXT("Connecting to %s"), connString);

  s = natsConnection_ConnectTo(&this->natsConn, connString);
  if (s != NATS_OK)
  {
      UE_LOG(LogGBSNats, Log, TEXT("Error connecting to %s: %s"), connString, natsStatus_GetText(s));
      
  }
#endif
}

UGBSNatsSubscription *UGBSNatsConnection::Subscribe(const FString &Subject)
{
  UGBSNatsSubscription* sub = NewObject<UGBSNatsSubscription>(this);

  sub->SetSubject(Subject);

#ifdef USE_NATS
  sub->SetConnection(this->natsConn);
#endif

  sub->DoSubscription();

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
