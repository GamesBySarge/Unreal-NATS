#include "GBSNatsSubscription.h"
#include <string.h>

UGBSNatsSubscription::UGBSNatsSubscription(const class FObjectInitializer &PCIP)
    : Super(PCIP)
{
}

void UGBSNatsSubscription::SetSubject(const FString &Subject)
{
  this->m_Subject = Subject;
}

#ifdef USE_NATS
void UGBSNatsSubscription::SetConnection(natsConnection *nc)
{
  this->natsConn = nc;
}
#endif

void UGBSNatsSubscription::InternalOnMessage(const FString& Subject, const FString& Message)
{
  this->OnMessage.Broadcast(Subject, Message);
}

#ifdef USE_NATS
void onMsg(natsConnection* nc, natsSubscription* sub, natsMsg* msg, void* closure)
{
  UGBSNatsSubscription* _this = (UGBSNatsSubscription *)closure;
  std::string cstr(reinterpret_cast<const char*>(natsMsg_GetData(msg)), natsMsg_GetDataLength(msg));

  FString message = (cstr.c_str());
  FString subject = natsMsg_GetSubject(msg);

  UE_LOG(LogGBSNats, Log, TEXT("%s : %s"), *subject, *message);

  _this->InternalOnMessage(subject, message);
  natsMsg_Destroy(msg);
}
#endif

void UGBSNatsSubscription::DoSubscription(const FString& subject)
{
#ifdef USE_NATS
  UE_LOG(LogGBSNats, Log, TEXT("Subscribing to \"%s\""), *subject);

  natsStatus s = NATS_OK;
  s = natsConnection_Subscribe(&this->natsSub, this->natsConn, TCHAR_TO_ANSI(*subject), onMsg, (void *)this);
  if (s != NATS_OK)
  {
      FString ErrorMessage = ANSI_TO_TCHAR(natsStatus_GetText(s));
      UE_LOG(LogGBSNats, Log, TEXT("Error subscribing to %s: %s"), *subject, *ErrorMessage);
  }

#endif
}

