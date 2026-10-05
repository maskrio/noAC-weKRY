for i in $(seq 1000); do echo -ne "\r$i"; ./gen $i > in; ./sol<in>o1; ./brute<in>o2; diff o1 o2||{ echo " seed $i"; break; }; done
