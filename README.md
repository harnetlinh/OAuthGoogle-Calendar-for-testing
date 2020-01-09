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

# Cross-compile and deploy Qt 5.12 for Raspberry Pi
### Install OS for RaspberryPi
### Config on RPi
#### Update RPi
```
sudo rpi-update
sudo apt-get update
sudo reboot

```
#### Install libs
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
### Create build-kit RPi on Ubuntu
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

### Build source on Ubuntu
Go to https://download.qt.io/archive/qt/ to download qt source
I use qt 5.12.6 for my project

