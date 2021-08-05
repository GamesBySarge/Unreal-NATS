# Unreal-NATS notes

## Multi-threading in Unreal


HttpManager adds requests to HttpThread, then during Tick() it gets completed requests 

HttpThread.cpp is the running thread that dequeues requests, and  enques the results when the request is complete.

When HttpManager gets the completed requests (within the game thread), it calls the HttpRequest::FinishRequest(), which publishes the `ProcessRequestComplete` event.

See `FWinHttpHttpRequest` for an implementation of this.

