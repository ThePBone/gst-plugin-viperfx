./autogen.sh
make
sudo cp src/.libs/libgstviperfx.so /usr/lib/x86_64-linux-gnu/gstreamer-1.0/
make clean
rm -rf src/.deps