sudo apt update
sudo apt upgrade -y
sudo apt dist-upgrade -y
sudo apt-get install linux-headers-$(uname -r)
sudo reboot now
sudo apt update
sudo apt install realtek-rtl88xxau-dkms
sudo apt install dkms
git clone https://github.com/aircrack-ng/rtl8812au
cd rtl8812au/
make
sudo make install
lsusb
iwconfig
