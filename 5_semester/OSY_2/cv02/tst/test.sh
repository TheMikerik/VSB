cd lib_w && make clean && make && cd ..
cd lib_d && make clean && make && cd ..
cd lib_o && make clean && make && cd ..
cd vernum && make clean && make && cd ..


echo "--------------------------------"
echo "STDIN"
echo "--------------------------------\n"
echo "10 20 30 60" | DYLD_LIBRARY_PATH=./lib_w ./vernum/vernum
echo "10.00 20.00 30.00 60.00" | DYLD_LIBRARY_PATH=./lib_d ./vernum/vernum
echo "012 024 036 072" | DYLD_LIBRARY_PATH=./lib_o ./vernum/vernum


echo "\n\n--------------------------------"
echo "FILES"
echo "--------------------------------\n"
DYLD_LIBRARY_PATH=./lib_w ./vernum/vernum < inty.txt
DYLD_LIBRARY_PATH=./lib_d ./vernum/vernum < floaty.txt
DYLD_LIBRARY_PATH=./lib_o ./vernum/vernum < binarka.txt

echo "\n\n--------------------------------"
echo "FILES WITH MISTAKES"
echo "--------------------------------\n"
DYLD_LIBRARY_PATH=./lib_w ./vernum/vernum < inty_chyba.txt
DYLD_LIBRARY_PATH=./lib_d ./vernum/vernum < floaty_chyba.txt
DYLD_LIBRARY_PATH=./lib_o ./vernum/vernum < binarka_chyba.txt
echo "--------------------------------\n"

