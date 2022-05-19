# SteamShim-N (SteamShim-New)

## About
steamshim-n is a shim written in CXX, providing various programs access to [Valve Steamworks API](https://partner.steamgames.com/doc/sdk/api) via Named Pipes.

## Compatible languages
 - C/C++, check `client/c` [In Heavy Development]
 - Ruby, check `client/ruby` [In Heavy Development]

## Installing Host
Currently, only Windows NT is supported in tested, but expect Linux and macOS support in future!
To build SteamShim-N you will need Python, Meson Build System, Ninja, MinGW GNU C Compiler and Steamworks SDK itself\
 - Meson Build System and Ninja: `pip3 install meson ninja`
 - MinGW GNU C Compiler: https://www.msys2.org/
 - Steamworks SDK: `Download SDK` button on [Steamworks Partners Website](https://partner.steamgames.com)

1. Clone SteamShim-N
```
git clone https://github.com/somedevfox/steamshim-n
```

2. Download Steamworks SDK, unpack it's .zip and copy `public` and `redistributable_bin` folders in `host/sdk` folder of SteamShim-N

3. Configure Meson Project
```
cd host; meson build
```

2. Build SteamShim-N Host
```
ninja
```

## Installing Client
To install client section of SteamShim into your game, simply add `client/source/client.c` to your file compilation list, and then add `client/source` in your include paths.

**Meson Example:**
```meson
project('steamshim-n-example', 'c')

executable(meson.project_name(),
    sources: files(
        'game.c',
        '../source/client.c'
    ),
    include_directories: include_directories('../source')
)
```