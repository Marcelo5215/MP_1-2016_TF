mkdir bin
cd test
mkdir obj
cd src
make
make clean
cp test ../../bin
rm test
cd ../../GUI
mkdir obj
cd src
make
make clean
cp gui ../../bin
rm gui
