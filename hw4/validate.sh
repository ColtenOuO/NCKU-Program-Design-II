#!/bin/bash

if [ $# -eq 0 ]; then
	echo "Usage: validate.sh [options] hw_name"
	echo "Options:"
	echo "  -m		Measure execution time"
	echo "  -d		Print diff detail"
	echo "  -n <cnt>	Measure execution time by taking the mean of running the program <cnt> times. Default is 20"
	echo "  -t <path>	Also copies test data from <path>"
	exit 1
fi


MEASURE_TIME="false"
MEASURE_SAMPLE=20
DIFF_DETAIL="false"

while getopts ":mdn:t:" OPTION
do
	case "${OPTION}" in
		m ) MEASURE_TIME="true";;
		d ) DIFF_DETAIL="true";;
		n ) MEASURE_SAMPLE=${OPTARG};;
		t ) TEST_PATH=${OPTARG};;
		\?) echo "$0: Error: Invalid option: -${OPTARG}" >&2; exit 1;;
		: ) echo "$0: Error: option -${OPTARG} requires an argument" >&2; exit 1;;
	esac
done
shift $((OPTIND - 1))
		
HW=$1
HW_PATH=$HOME/$HW
HW_EXEC=$HW_PATH/$HW
ANS_PATH=$HW_PATH/answer
RES_PATH=$HW_PATH/results

if [ $# -eq 0 ]; then
    echo Expected hw name
    exit 0
fi


if [ -e $ANS_PATH ]; then
    rm -rf $ANS_PATH
fi

cp /home/share/$HW $ANS_PATH -r
if [ -v TEST_PATH ]; then
	cp $TEST_PATH/* $ANS_PATH
fi

if ! [ -e $RES_PATH ]; then
    mkdir $RES_PATH
fi
rm $RES_PATH/*


make --directory $HW_PATH clean all

OLD_IFS=$IFS
IFS="_"

if [ "$HW" == "hw1" ]; then
    for file in $ANS_PATH/result_*; do

        read -ra str <<< $file
        N=${str[1]}

        $HW_EXEC $N > $RES_PATH/result_$N

        diff -sq $ANS_PATH/result_$N $RES_PATH/result_$N
    done

elif [ "$HW" == "hw2" ]; then
    for file in $ANS_PATH/*.csv; do

        read -ra str <<< $file

        N=${str[1]:4:1}

        $HW_EXEC "$file" > $RES_PATH/result_$N


        diff -sq $ANS_PATH/result_$N $RES_PATH/result_$N
    done

elif [ "$HW" == "hw3" ] || [ "$HW" == "hw4" ]; then
    for file in $ANS_PATH/*.csv; do

		IFS='_'
        read -ra str <<< $file
		IFS='.'
		read -ra str <<< ${str[1]}
		IFS='test'
		read -ra str <<< ${str[0]}

        N=${str[4]}
		IFS=$OLD_IFS

		echo "[ Test case $N ]"

		if [ $MEASURE_TIME == "true" ]; then

			 for ((i=0; i < $MEASURE_SAMPLE; i++)); do
				 { time $HW_EXEC "$file" > $RES_PATH/result_$N; } 2>&1
			 done | awk -F 'm' '
				 /real/ { real = real + $2; nr++ }
				 /user/ { user = user + $2; nu++ }
				 /sys/  { sys  = sys  + $2; ns++ }
				 END {
					 if (nr>0) printf("real %.3fs\n", real/nr);
					 if (nu>0) printf("user %.3fs\n", user/nu);
					 if (ns>0) printf("sys  %.3fs\n", sys/ns);
				 }'
		else
			$HW_EXEC "$file" > $RES_PATH/result_$N
		fi
		
		if [ $DIFF_DETAIL == "true" ]; then
        	diff -s $ANS_PATH/result_$N $RES_PATH/result_$N
		else
        	diff -sq $ANS_PATH/result_$N $RES_PATH/result_$N
		fi

		echo ""
    done
fi
