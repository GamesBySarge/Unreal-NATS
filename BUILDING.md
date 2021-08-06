# Building the GBSNats plugin

- [Building the GBSNats plugin](#building-the-gbsnats-plugin)
  - [Dependencies](#dependencies)
    - [vcpkg](#vcpkg)
    - [openssl](#openssl)

## Dependencies

Note: For windows I was using vcpkg, but protobuf-c isn't implemented for Windows via vcpkg, so that was a dead end.  Since I'm currently only using this plugin for my dedicated servers which run on Linux, I'm temporarily dropping support for Windows.  You can still edit blueprints in Windows, but it won't execute any NATS.io calls.

### vcpkg

Install vcpkg (and then optionally add \vcpkg to your PATH)

```bat
git clone https://github.com/microsoft/vcpkg
.\vcpkg\bootstrap-vcpkg.bat
```

### openssl

OpenSSL

```
.\vcpkg install openssl:x64-windows
