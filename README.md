# Prepare your environment

## Get the source

```bash
git clone https://github.com/hhool/vlc_plugin_img_process.git
```

```bash
wget ftp://ftp.videolan.org/pub/videolan/vlc/3.0.18/vlc-3.0.18.tar.xz
tar -xvf vlc-3.0.18.tar.xz
```

## Ubuntu 22.04.3 LTS (x86_64)

- (UnixCompile)(<https://wiki.videolan.org/UnixCompile/>)

### Install dependencies for Ubuntu 22.04.3 LTS (x86_64)

`The "Contrib" method is the easiest way to get all the build dependencies.`

```bash
sudo cp /etc/apt/sources.list /etc/apt/sources.list~
sudo sed -Ei 's/^# deb-src /deb-src /' /etc/apt/sources.list
sudo apt-get update
```

```bash
sudo apt-get install -y vim git g++ make libtool automake autopoint pkg-config flex bison lua5.2

sudo apt-get install -y libxcb-shm0-dev libxcb-xv0-dev libxcb-keysyms1-dev libxcb-randr0-dev libxcb-composite0-dev libx11-xcb-dev

sudo apt-get install -y subversion yasm cvs cmake ragel meson gperf default-jdk gettext ant protobuf-compiler gtk-doc-tools

sudo apt-get build-dep vlc
```

### Build VLC Source for Ubuntu 22.04.3 LTS (x86_64)

```bash
export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig
export LD_LIBRARY_PATH=/usr/local/lib/
```

```bash
./configure && ./compile && sudo make install
```

### Build VLC Plugin img_process for Ubuntu 22.04.3 LTS (x86_64)

```bash
cd vlc_plugin_img_process

cmake -S . -B out/build_x86_64_linux -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local

cmake --build out/build_x86_64_linux  -v

sudo cmake --build out/build_x86_64_linux --target install
```

### Run VLC Plugin img_process for Ubuntu 22.04.3 LTS (x86_64)

```bash
/usr/local/bin/qvlc
```

## Windows 10 (x86_64)

- (Win32Compile)(<https://wiki.videolan.org/Win32Compile/>)

### Install dependencies for Windows 10 (x86_64)

- [MSYS2](<https://www.msys2.org/>)

```bash
pacman -Syu
pacman -S --needed base-devel mingw-w64-x86_64-toolchain
pacman -S --needed git subversion mercurial cvs wget p7zip unzip \
    mingw-w64-x86_64-cmake mingw-w64-x86_64-nasm \
    mingw-w64-x86_64-gettext mingw-w64-x86_64-libtool \
    mingw-w64-x86_64-automake mingw-w64-x86_64-autoconf
```
