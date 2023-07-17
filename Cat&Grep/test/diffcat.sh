filename="Cat/cat.h";
echo -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- "*CAT" ;
diff <(cat -b "$filename") <(./cat -b "$filename") -s ;
echo -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- "*CAT" ;
diff <(cat -e "$filename") <(./cat -e "$filename") -s ;
echo -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- "*CAT" ;
diff <(cat -n "$filename") <(./cat -n "$filename") -s ;
echo -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- "*CAT" ;
diff <(cat "$filename" -n) <(./cat "$filename" -n) -s ;
echo -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- "*CAT" ;
diff <(cat "$filename" -n) <(./cat "$filename" -n) -s ;
echo -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- "*CAT" ;
diff <(cat -s "$filename") <(./cat -s "$filename") -s ;
echo -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- "*CAT" ;
diff <(cat -t "$filename") <(./cat -t "$filename") -s ;

