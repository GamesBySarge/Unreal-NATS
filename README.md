# Unreal-NATS

This Unreal plugin is for integrating your Linux Game Server with [NATS.io](https://nats.io).

It currently only supports FString types as messages, but you could convert UStruct to JSON to FString if you wanted to use UStructs as messages.  It works well with the VARest JSON structures.

All of this implementation is exposed to Blueprint.

This implementation is a work in progress and is NOT production ready; it does not properly destroy connections or subscriptions, and in some places it does not do error handling.

## Roadmap

* More rubust implementation with error handling and no memory leaks
* Directly support UStruct and JSON messages.
* Support Windows
