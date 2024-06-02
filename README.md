NXEngine
========

NXEngine is open-source rewrite engine of the [Cave Story](https://en.wikipedia.org/wiki/Cave_Story) game. Author - [Caitlin (rogueeve) Shaw](http://nxengine.sourceforge.net/).

![Ritmix RZX-50](screens/Cave_Story_Ritmix_1.png)

This repository contains source code of my NXEngine fork for various weak devices. I have added some engine improvements:

1. Sound through SDL_mixer.
2. Support for widescreen displays (480x272).
3. Ports to various platforms.
4. Russification.

## DATA files

You will need following assets to run `./nx` executable:

**Provided here:**
- sprites.sif
- smalfont.bmp
- tilekey.dat

**Provided externally:**
- Dokutsu.exe
- data/ - dir from org game.
- xm/ - dir with [XM sound files](https://github.com/Apaczer/NXEngine/blob/1083a338213004e689f3c2a430db9158a4be45b5/sound/sound.cpp#L30) in lowercase (for SDL_mixer)

**Binary build:**
- nx

_Directory structure:_
```
cavestory
├── data/
├── xm/
├── Doukutsu.exe
├── nx
├── smalfont.bmp
├── sprites.sif
└── tilekey.dat
```

In linux env you can execute `./dl_data.sh all` from this repo to download and extract all "provided externally" assets.
If you have original *.org songs in `org/` dir already (use `./nx` native build if not) and gcc `binutils` pkg installed, you could just use org2xm submodule tool:
```
git submodule update --init --recursive
make org2xm
```

## Build instructions

### Generic

Building requires some SDL libraries: SDL-1.2, SDL_ttf-2.0, SDL_mixer-1.2 (optional). Please install developer versions of these libraries before building the project. You can open "nx.pro" project file in the [Qt Creator](https://www.qt.io/download) IDE for easy code navigation.

Platform defines:

| Define | Description |
| --- | --- |
| `-D_480X272` | Use widescreen 480x272 resolution. |
| `-D_320X240` | Use normal 320x240 resolution. |
| `-D_DINGUX` | Dingux platform and keyboard layout (Ritmix RZX-50, Dingoo A320, Dingoo A380, etc). |
| `-D_MOTOMAGX` | MotoMAGX platform and keyboard layout (Motorola ZN5, Z6, E8, EM30, VE66, etc). |
| `-D_MOTOEZX` | MotoEZX platform and keyboard layout (Motorola E2, E6, A1200, A1600). |
| `-D_SDL_MIXER` | Don't use realtime music generation, `*.xm` tracks and sounds will be played via SDL_mixer. |
| `-D_DEBUG` | Enable detailed debug output to the console. |
| `-D_L10N_CP1251` | Enable Russian l10n (you need a `*.ttf` font and Russian version of data-files). |

Please read [addition building information (in Russian)](http://exlmoto.ru/nxengine/#3) in the EXL's Developer Blog.

### Native build

```
make rel
```

### Docker CROSS-COMPILE for MiyooCFW

```
docker run --volume ./:/src/ -it miyoocfw/toolchain-shared-uclibc:latest
cd /src
export OPT="-mcpu=arm926ej-s -mtune=arm926ej-s -fno-PIC -flto" CXXOPT="-mcpu=arm926ej-s -mtune=arm926ej-s -fno-PIC -flto"
make clean
make rel COPT="$OPT" CXXOPT="$OPT"
exit
```

### Extract data from the Web
- full data with XM tracks
```
make data
```
- only necessary data and convert .org to .xm
```
make clean
make -j$(nproc)
make data-cave
./nx
git submodule update --init --recursive
make org2xm
```

## Changelog MiyooCFW

2.1

- correct MIYOO inputs binding

2.0

- fixed music stuttering via XM tracks played through updated SDL_Mixer libs with MOD support (libmikmod)
- other changes from upstream

1.0

- initial legacy release without music support

## Screens

Ritmix RZX-50:

![Ritmix RZX-50](screens/Cave_Story_Ritmix_2.png)

Windows 8.1:

![Windows 8.1](screens/Cave_Story_Windows.png)

Haiku OS:

![Haiku OS](screens/Cave_Story_HaikuOS.png)

## Photos

![Motorola ROKR E6](platform/EZX/NXEngine-EZX-ROKR_E6.jpg)

## Videos

Demonstration [video on YouTube](https://youtu.be/aZPgX9Ismq4) which showing launch Cave Story game with this engine on the Ritmix RZX-50 device.

## More information

Please read [Porting Guide (in Russian)](http://exlmoto.ru/nxengine) for more info about porting NXEngine to various platforms.
