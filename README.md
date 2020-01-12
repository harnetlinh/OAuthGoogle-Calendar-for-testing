# OAuthGoogle-Calendar-for-testing
A small project for learning and testing qt framework, cross compiling, oauth2, google API...
Based on a [Qt blog](http://blog.qt.io/blog/2017/01/25/connecting-qt-application-google-services-using-oauth-2-0/) <br>
This project is created for studying so it has a lot of bugs, the code is not clean. Totaly it isnt perfect. I will continous the work to upgrade. It is a pleasure to tell me some mistake which you can find from my project.
#### Tested on:
- Ubuntu 18.04.03, Raspbian with gcc-linaro-7.5.0-2019
- Windows  Qt 5.12.6


### Features!
  - View, insert, update, delete events of google calendar
<img src="https://github.com/harnetlinh/OAuthGoogle-Calendar-for-testing/blob/master/image/main.jpg" width="400" />

# 1.Cross-compile and deploy Qt 5.12 for Raspberry Pi
### 1.1 Install OS for RaspberryPi
### 1.2 Config on RPi
#### 1.2.1 Update RPi
```
sudo rpi-update
sudo apt-get update
sudo reboot

```
#### 1.2.2 Install libs
```
sudo apt install libxkbcommon-dev

sudo apt-get update && sudo apt-get install libssl-dev

sudo apt-get install xcb libxcb-keysyms1-dev libxcb-image0-dev libxcb-shm0-dev libxcb-icccm4-dev

sudo apt-get install libxcb-sync0-dev libxcb-xfixes0-dev libxcb-shape0-dev libxcb-randr0-dev libxcb-render-util0-dev

sudo apt-get install libxcb-xinerama0-dev libxcb-xinerama0

sudo apt-get install libx11-dev

sudo apt-get install gstreamer1.0-omx libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev

sudo mkdir /usr/local/qt5pi

sudo chown pi:pi /usr/local/qt5pi

sudo  reboot

```
### 1.3 Create build-kit RPi on Ubuntu
Before do this part, please turn on SSH on RPi configuration
```
mkdir ~/raspi

cd ~/raspi

git clone https://github.com/raspberrypi/tools

(rsync -avz --rsync-path="sudo rsync"  pi@192.168.1.180:/usr/lib sysroot/usr)--rsync with sudo

mkdir sysroot sysroot/usr sysroot/opt

rsync -avz --rsync-path="sudo rsync" pi@<RPi ip address>:/lib sysroot

rsync -avz --rsync-path="sudo rsync" pi@<RPi ip address>:/usr/include sysroot/usr

rsync -avz --rsync-path="sudo rsync" pi@<RPi ip address>:/usr/lib sysroot/usr

rsync -avz --rsync-path="sudo rsync" pi@<RPi ip address>:/opt/vc sysroot/opt


wget https://raw.githubusercontent.com/riscv/riscv-poky/master/scripts/sysroot-relativelinks.py

chmod +x sysroot-relativelinks.py

./sysroot-relativelinks.py sysroot
```
> To get ip address, go to terminal: `ip address`

### 1.4 Build source on Ubuntu
Go to https://download.qt.io/archive/qt/ to download qt source
I use qt 5.12.6 for my project
Go to file download, extract it.

Firtly, config
```
./configure -release -opengl es2 -device linux-rasp-pi3-g++ -device-option CROSS_COMPILE=~/raspi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf- -sysroot ~/raspi/sysroot -opensource -eglfs -openssl -openssl-linked -xcb -qt-xcb -system-xcb -xkbcommon -confirm-license -reduce-exports -make libs -prefix /usr/local/qt5pi -extprefix ~/raspi/qt5pi -hostprefix ~/raspi/qt5 -v -no-use-gold-linker

make -j2

make install
```

repeat for all: qtimageformats, qtcharts, qtconnectivity, qtdeclarative, qtscxml, qtscript|, qtmultimedia, qtquickcontrols, qtquickcontrols2, qtsvg, qtvirtualkeyboard, qtgraphicaleffects
```
cd qtimageformats
sudo ~/raspi/qt5/bin/qmake -r
sudo make
sudo make install
```

Note config specifically for qtvirtualkeyboard, qtmultimedia 
qtvirtualkeyboard: `: ~/raspi/qt5/bin/qmake CONFIG+="lang-ar_AR lang-da_DK lang-de_DE lang-en_GB lang-es_ES lang-fa_FA lang-fi_FI lang-fr_FR lang-hi_IN lang-it_IT lang-ja_JP lang-ko_KR lang-nb_NO lang-pl_PL lang-pt_PT lang-ru_RU lang-sv_SE lang-zh_CN lang-zh_TW"`
qtmultimedia: `~/raspi/qt5/bin/qmake -r GST_VERSION=1.0`
After installing is done, we need to update for qt5pi
```
rsync -avz --rsync-path="sudo rsync" qt5pi pi@192.168.1.180:/usr/local
```

### 1.5 Config on QtCreator
After install QtCreator, we need to create new kit for compiler:
#### 1.5.1 Compiler C/C++:
```
/home/longnm/raspi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-g++
/home/longnm/raspi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc
```
#### 1.5.2 QT Version
```
~/raspi/qt5/bin/qmake
```

### 1.6 Create filemake and send to machine

```
cd {name code folder}
/home/hangoclinh/raspi/qt5/bin/qmake
make
scp {name project} pi@192.168.1.180:/home/pi/
```

