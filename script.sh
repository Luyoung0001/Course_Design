#! /usr/bin/env sh

make clean &&
make &&
./main -z ./Test/1.pdf -o ./Test/zipfile1.code &&
./main -z ./Test/2.pptx -o ./Test/zipfile2.code &&
./main -z ./Test/3.png -o ./Test/zipfile3.code &&
./main -z ./Test/4.mp3 -o ./Test/zipfile4.code &&
./main -z ./Test/5.mp4 -o ./Test/zipfile5.code &&
./main -z ./Test/6.txt -o ./Test/zipfile6.code &&

./main -u ./Test/zipfile1.code -o ./Test/11decode.pdf &&
./main -u ./Test/zipfile2.code -o ./Test/22decode.pptx &&
./main -u ./Test/zipfile3.code -o ./Test/33decode.png &&
./main -u ./Test/zipfile4.code -o ./Test/44decode.mp3 &&
./main -u ./Test/zipfile5.code -o ./Test/55decode.mp4 &&
./main -u ./Test/zipfile6.code -o ./Test/66decode.txt &&
cd ./Test &&
ls -al &&
make clean
