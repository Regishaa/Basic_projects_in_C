filename1="diffgrep.sh"
filename2="Grep/grep.c"
filename3="Grep/grep.h"

echo "----------------------------------------------*GREP 1"
diff <(grep int "$filename2" "$filename1") <(./grep int "$filename2" "$filename1") -s -q

echo "----------------------------------------------*GREP 1 -e"
diff <(grep -e int "$filename2" "$filename1") <(./grep -e int "$filename2" "$filename1") -s -q

echo "----------------------------------------------*GREP 2"
diff <(grep -i int "$filename1") <(./grep -i int "$filename1") -s -q

echo "----------------------------------------------*GREP 3"
diff <(grep -v int "$filename1") <(./grep -v int "$filename1") -s -q

echo "----------------------------------------------*GREP 4"
diff <(grep -c int "$filename1") <(./grep -c int "$filename1") -s -q

echo "----------------------------------------------*GREP 5"
diff <(grep -l int "$filename2" "$filename3" "$filename1") <(./grep -l int "$filename2" "$filename3" "$filename1") -s -q

echo "----------------------------------------------*GREP 6"
diff <(grep -n int "$filename1") <(./grep -n int "$filename1") -s -q

echo "----------------------------------------------*GREP 7 BONUS"
diff <(grep -h int "$filename1") <(./grep -h int "$filename1") -s -q

echo "----------------------------------------------*GREP 8 BONUS"
diff <(grep -o int "$filename1") <(./grep -o int "$filename1") -s -q

echo "----------------------------------------------*GREP 9 BONUS"
diff <(grep -h int "$filename2" "$filename1") <(./grep -h int "$filename2" "$filename1") -s -q

echo "----------------------------------------------*GREP 10 BONUS"
diff <(grep int -s aboba) <(./grep int -s aboba) -s -q

echo "----------------------------------------------*GREP 11 BONUS"
diff <(grep -f "$filename3" "$filename2") <(./grep -f "$filename3" "$filename2") -s -q

echo "----------------------------------------------*GREP 12 BONUS"
diff <(grep -in int "$filename1") <(./grep -in int "$filename1") -s -q

echo "----------------------------------------------*GREP 13 BONUS"
diff <(grep -cv int "$filename1") <(./grep -cv int "$filename1") -s -q

echo "----------------------------------------------*GREP 14 BONUS"
diff <(grep -iv int "$filename1") <(./grep -iv int "$filename1") -s -q

echo "----------------------------------------------*GREP 15 BONUS"
diff <(grep -lv int "$filename2" "$filename3" "$filename1") <(./grep -lv int "$filename2" "$filename3" "$filename1") -s -q

echo "----------------------------------------------*GREP 16 BONUS"
diff <(grep -ho int "$filename2" "$filename1") <(./grep -ho int "$filename2" "$filename1") -s -q

echo "----------------------------------------------*GREP 17 BONUS"
diff <(grep -nf "$filename3" "$filename2") <(./grep -nf "$filename3" "$filename2") -s -q

echo "----------------------------------------------*Tests ended*"

