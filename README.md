# Prepare your environment

## Get the source

```bash
sudo git clone https://github.com/videolan/vlc.git
cd vlc
git checkout 3.0.18
```

```bash
git clone https://github.com/hhool/vlc_plugin_img_process.git
```

## Ubuntu 22.04.3 LTS (x86_64)

- (UnixCompile)(<https://wiki.videolan.org/UnixCompile/>)

### Install dependencies for Ubuntu 22.04.3 LTS (x86_64)

```bash
sudo apt-get update
sudo apt-get install -y build-essential vim git g++ make libtool automake autopoint pkg-config flex bison lua5.2
sudo apt-get install -y libxcb-shm0-dev libxcb-xv0-dev libxcb-keysyms1-dev libxcb-randr0-dev libxcb-composite0-dev libx11-xcb-dev
sudo apt-get install -y subversion yasm nasm cvs cmake ragel meson gperf default-jdk gettext ant protobuf-compiler gtk-doc-tools dos2unix texinfo
```

```bash
mkdir -p contrib/3rdparty
cd contrib/3rdparty
../bootstrap && make fetch && make -j4
```

```bash
export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:`pwd`/../x86_64-linux-gnu/lib/pkgconfig
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:`pwd`/../x86_64-linux-gnu/lib/
```

`The "Contrib" method is the easiest way to get all the build dependencies.`

```bash
sudo cp /etc/apt/sources.list /etc/apt/sources.list~
sudo sed -Ei 's/^# deb-src /deb-src /' /etc/apt/sources.list
sudo apt-get update

sudo apt-get build-dep vlc
```

```bash
export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig:$PKG_CONFIG_PATH
export LD_LIBRARY_PATH=/usr/local/lib/:$LD_LIBRARY_PATH
```

### Build VLC Source for Ubuntu 22.04.3 LTS (x86_64)

```bash
cd contrib/native
sudo ../../bootstrap && sudo ../../configure && sudo ./compile -j4 && sudo make -j4 install
```

```bash
sudo strip --remove-section=.note.ABI-tag /usr/lib/x86_64-linux-gnu/libQt5Core.so.5
```

### Build VLC Plugin img_process for Ubuntu 22.04.3 LTS (x86_64)

```bash
cd vlc_plugin_img_process
sudo cmake -DCMAKE_TOOLCHAIN_FILE=./cmake/toolchain.linux.cmake -S . -B out/build_x86_64_linux -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local
sudo cmake --build out/build_x86_64_linux  -v
sudo cmake --build out/build_x86_64_linux --target install
```

### Run VLC Plugin img_process for Ubuntu 22.04.3 LTS (x86_64)

```bash
/usr/local/bin/qvlc
```

## Windows 10 (x86_64) with WSL1

- (Win32Compile)(<https://wiki.videolan.org/Win32Compile/>)

### Install dependencies for Windows 10 (x86_64) with WSL1

```bash
sudo apt-get update
```

```bash
sudo apt-get install -y vim git g++ make libtool autoconf automake autopoint pkg-config flex bison lua5.2
sudo apt-get install -y libxcb-shm0-dev libxcb-xv0-dev libxcb-keysyms1-dev libxcb-randr0-dev libxcb-composite0-dev libx11-xcb-dev
sudo apt-get install -y subversion yasm cvs cmake ragel meson gperf default-jdk gettext ant protobuf-compiler gtk-doc-tools
sudo apt-get install -y unzip wget bzip2 file libwine-dev libtool libtool-bin libltdl-dev meson dos2unix
sudo apt-get install -y gcc-mingw-w64-x86-64 g++-mingw-w64-x86-64 mingw-w64-tools
```

### Build VLC Source for Windows 10 (x86_64) with WSL1


```bash
git clone https://github.com/videolan/vlc.git
cd vlc
git checkout 3.0.18
mkdir -p contrib/win
cd contrib/win
sudo ../../extras/package/win32/build.sh -a x86_64 -p
cd win64/ && sudo make package-win-common
cd ..
```

```bash
export PKG_CONFIG_PATH=`pwd`/win64/_win32/lib/pkgconfig:$PKG_CONFIG_PATH
export LD_LIBRARY_PATH=`pwd`/win64/_win32/lib/:$LD_LIBRARY_PATH
```

```bash
git clone https://github.com/hhool/vlc_plugin_img_process.git
cd vlc_plugin_img_process
sudo cmake -DCMAKE_TOOLCHAIN_FILE=./cmake/toolchain.mingw32.cmake -S . -B out/build_x86_64_mingw32/
cmake --build out/build_x86_64_mingw32/ -v
cmake --build out/build_x86_64_mingw32/ --target install
```
