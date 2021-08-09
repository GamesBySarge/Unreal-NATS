#include "GBSNatsSubscription.h"

UGBSNatsSubscription::UGBSNatsSubscription(const class FObjectInitializer &PCIP)
    : Super(PCIP)
{
}

void UGBSNatsSubscription::SetSubject(const FString &Subject)
{
  this->m_Subject = Subject;
}

void UGBSNatsSubscription::SetConnection(natsConnection *nc)
{
  this->natsConn = nc;
}

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

  _this->InternalOnMessage(subject, message);
  natsMsg_Destroy(msg);
}
#endif

void UGBSNatsSubscription::DoSubscription()
{
#ifdef USE_NATS
  natsConnection_Subscribe(&this->natsSub, this->natsConn, "foo", onMsg, (void *)this);
#endif
}

