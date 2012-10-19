for (( i = 0 ; i <= 19 ; i++ ))
do
	zcat ~cis501/html/traces/gcc-10M.trace.gz | ./bpred 2 10
 $i	sleep 3
done
