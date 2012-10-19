for (( i = 2 ; i <= 20 ; i++ ))
do
	zcat ~cis501/html/traces/gcc-10M.trace.gz | ./bpred 1 $i
	sleep 3
done
