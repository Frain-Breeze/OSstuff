./config.sh

./build.sh

export DISPLAY=:0; nohup frain_breeze &>/dev/null &
./qemu.sh