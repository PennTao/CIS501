for (( i = 2 ; i <= 20 ; i++ ))
do
	zcat ~cis501/html/traces/gcc-10M.trace.gz | ./bpred 3 `expr $i - 2`
 `expr $i - 1` `expr $i - 2` `expr $i - 1`	sleep 3
done
