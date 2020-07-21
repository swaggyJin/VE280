# copy all your codes in the same directory
# use the following line in command line to test p4
# ./test.sh
# contributors: Qiu Y., Zhang H., Tian Y.
###############################################
# test of compress and decompress
###############################################
cp -f PutYourCodesHere/binaryTree.h binaryTree.h
g++ --std=c++17 -o compress PutYourCodesHere/compress.cpp PutYourCodesHere/binaryTree.cpp PutYourCodesHere/huffmanTree.cpp
g++ --std=c++17 -o decompress PutYourCodesHere/decompress.cpp PutYourCodesHere/binaryTree.cpp PutYourCodesHere/huffmanTree.cpp
g++ --std=c++17 -o testbinary main.cpp PutYourCodesHere/binaryTree.cpp PutYourCodesHere/huffmanTree.cpp 
echo "---------------------------compile success!-------------------------------------"

# test binary
./testbinary > myans/BinaryTreeans.txt
diff myans/BinaryTreeans.txt Binaryans.txt
echo "---------------------------binary tree test done--------------------------------"

# type here the total number of testcases
num=1000

# generate testcases
for ((i = 1; i <= ${num}; i = i + 10)); do
    ./generate_testcase <<<"${i}" >testcase/testcase_${i}_text.txt
done

# test compress and decompress
# use text files in compress to generate tree and binary files
# then use these files in decompress to generate ans
# compare ans with text
for ((i = 1; i <= ${num}; i = i + 10)); do
    ./compress testcase/testcase_${i}_text.txt >testcase/testcase_${i}_binary.txt
    ./compress -tree testcase/testcase_${i}_text.txt >testcase/testcase_${i}_tree.txt
    ./decompress testcase/testcase_${i}_tree.txt testcase/testcase_${i}_binary.txt > myans/ans_${i}.txt

    echo "testcase_${i} done"
    diff myans/ans_${i}.txt testcase/testcase_${i}_text.txt
done

# memory check: random
for ((i = 1; i <= ${num}; i = i + 180)); do
    valgrind --leak-check=full ./compress testcase/testcase_${i}_text.txt >testcase/testcase_${i}_binary.txt
    valgrind --leak-check=full ./compress -tree testcase/testcase_${i}_text.txt >testcase/testcase_${i}_tree.txt
    valgrind --leak-check=full ./decompress testcase/testcase_${i}_tree.txt testcase/testcase_${i}_binary.txt > myans/ans_${i}.txt

    echo "----------------------------------------------memory check_${i} done----------------------------------------------"
done
python3 codestyle.py PutYourCodesHere
echo "----------------------------------------------Style check done----------------------------------------------"
python3 lineCheck.py PutYourCodesHere
echo "----------------------------------------------Line check done----------------------------------------------"