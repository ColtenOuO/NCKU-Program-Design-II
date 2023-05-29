#!/bin/bash

print_usage () {
	echo "Usage: validate.sh [options] hw_name"
	echo "Options:"
	echo "  -m		Measure execution time"
	echo "  -d		Print diff detail"
	echo "  -n <cnt>	Measure execution time by taking the mean of running the program <cnt> times. Default is 20"
	echo "  -t <path>	Also copies test data from <path>"
	echo "  -f		Use formal test cases"
	exit 1
}

update () {
	echo "Updating validate.sh..."
	SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
	wget -O $SCRIPT_DIR/validate.sh https://raw.githubusercontent.com/SimonLiu423/2023-ncku-pd2/main/validate.sh
	echo "Done!"
	exit 1
}

if [ $# -eq 0 ]; then
	print_usage
fi

if [ "$1" == "update" ]; then
	update
fi

MEASURE_TIME="false"
MEASURE_SAMPLE=20
DIFF_DETAIL="false"
USE_FORMAL="false"

while getopts ":mdn:t:f" OPTION
do
	case "${OPTION}" in
		m ) MEASURE_TIME="true";;
		d ) DIFF_DETAIL="true";;
		f ) USE_FORMAL="true";;
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
declare -A input_prefix=(   ["hw1"]="result_" ["hw2"]="hw2_test" ["hw3"]="hw3_test" ["hw4"]="hw4_test" \
                            ["hw5"]="corpus_" )
declare -A input_postfix=(  ["hw1"]=""        ["hw2"]=".csv"     ["hw3"]=".csv"     ["hw4"]=".csv" \
                            ["hw5"]=".txt" )
declare -A output_prefix=(  ["hw1"]="result_" ["hw2"]="result_"   ["hw3"]="result_"   ["hw4"]="result_" \
                            ["hw5"]="result" )
declare -A output_postfix=( ["hw1"]=""        ["hw2"]=""         ["hw3"]=""         ["hw4"]="" \
                            ["hw5"]="" )

declare -A f_input_prefix=(   ["hw1"]=""            ["hw2"]="hw2_test" ["hw3"]="problem_" )
declare -A f_input_postfix=(  ["hw1"]="_output.txt" ["hw2"]=".csv"     ["hw3"]=".csv" )
declare -A f_output_prefix=(  ["hw1"]=""            ["hw2"]="result_"  ["hw3"]="answer_" )
declare -A f_output_postfix=( ["hw1"]="_output.txt" ["hw2"]=""         ["hw3"]="" )


exec_and_measure () {
	for ((i=0; i < $MEASURE_SAMPLE; i++)); do
	    { time $HW_EXEC $1 > $RES_PATH/"$2""$N""$3"; } 2>&1
	done | awk -F 'm' '
	    /real/ { real = real + $2; nr++ }
	    /user/ { user = user + $2; nu++ }
	    /sys/  { sys  = sys  + $2; ns++ }
	    END {
	   	 if (nr>0) printf("real %.3fs\n", real/nr);
	   	 if (nu>0) printf("user %.3fs\n", user/nu);
	   	 if (ns>0) printf("sys  %.3fs\n", sys/ns);
	    }'

}

hw1_parse () {
	if [ "$USE_FORMAL" == "true" ]; then
		IFS='/'
		read -ra str <<< $1
		IFS='_'	
		read -ra str <<< ${str[-1]}
		echo "${str[0]}"
	else
		read -ra str <<< $1
		echo "${str[1]}"
	fi
}

hw2_parse () {
    read -ra str <<< $1
    IFS='.'
    read -ra str <<< ${str[1]}
    IFS='test'
    read -ra str <<< ${str[0]}

    echo "${str[4]}"	
}

hw3_parse () {
   	read -ra str <<< $1
	if [ "$USE_FORMAL" == "true" ]; then
		IFS='.'
		read -ra str <<< ${str[-1]}
		echo "${str[0]}"	
	else
   	    IFS='.'
   	    read -ra str <<< ${str[1]}
   	    IFS='test'
   	    read -ra str <<< ${str[0]}

   	    echo "${str[4]}"	
	fi
}

hw4_parse () {
	echo "$(hw3_parse "$1")"
}

hw5_parse () {
   	read -ra str <<< $1
	IFS='.'
	read -ra str <<< ${str[-1]}
	echo "${str[0]}"
}

if [ $# -eq 0 ]; then
    echo Expected hw name
    exit 0
fi

if [[ ! ($(type -t "$HW"_parse) == function) ]]; then
	echo Script for $HW not found, try updating the script by running ./validate.sh update
	exit 1
fi

if [ -e $ANS_PATH ]; then
    rm -rf $ANS_PATH
fi

if [ $USE_FORMAL == "true" ]; then
	cp -r /home/share/$HW/formalData $ANS_PATH
else
	if [ $HW == "hw5" ]; then
		mkdir $ANS_PATH
		cp -r /home/share/hw5/testcase2/* $ANS_PATH/	
		cp -r /home/share/hw5/testcase3/* $ANS_PATH/	
		cp -r /home/share/hw5/testcase4/* $ANS_PATH/	
		cp -r /home/share/hw5/testcase5/* $ANS_PATH/	
		mv $ANS_PATH/result_002 $ANS_PATH/result002
		mv $ANS_PATH/result_003 $ANS_PATH/result003
		mv $ANS_PATH/result_004 $ANS_PATH/result004
		cp /home/share/hw5/testcase1/corpus1.txt $ANS_PATH/corpus_1.txt
		cp /home/share/hw5/testcase1/query1.txt $ANS_PATH/query_1.txt
		cp /home/share/hw5/testcase1/result1 $ANS_PATH/
	else
		cp -r /home/share/$HW $ANS_PATH
	fi
fi
if [ -v TEST_PATH ]; then
	cp $TEST_PATH/* $ANS_PATH
fi

if ! [ -e $RES_PATH ]; then
    mkdir $RES_PATH
fi
rm $RES_PATH/*

make --directory $HW_PATH -k clean all

run_tests () {
	in_pre=$1
	in_post=$2
	out_pre=$3
	out_post=$4
    for file in $ANS_PATH/"$in_pre"*"$in_post"; do
		OLD_IFS=$IFS
		IFS="_"

		N="$("$HW"_parse "$file")"

		IFS=$OLD_IFS

		echo "[ Test case $N ]"

		if [ $MEASURE_TIME == "true" ]; then
			if [ "$HW" == "hw1" ]; then
				exec_and_measure "$N" "$out_pre" "$out_post"
			elif [ "$HW" == "hw5" ]; then
				inputs="$file $ANS_PATH/query_$N.txt"
				exec_and_measure "$inputs" "$out_pre" "$out_post"
			else
				exec_and_measure "$file" "$out_pre" "$out_post"
			fi
		else
			if [ "$HW" == "hw1" ]; then
				$HW_EXEC "$N" > $RES_PATH/"$out_pre"$N"$out_post"
			elif [ "$HW" == "hw5" ]; then
				inputs="$file $ANS_PATH/query_$N.txt"
				$HW_EXEC $inputs > $RES_PATH/"$out_pre"$N"$out_post"
			else
				$HW_EXEC "$file" > $RES_PATH/"$out_pre"$N"$out_post"
			fi
		fi
		
		if [ $DIFF_DETAIL == "true" ]; then
        	diff -s $ANS_PATH/"$out_pre""$N""$out_post" $RES_PATH/"$out_pre""$N""$out_post"
		else
        	diff -sq $ANS_PATH/"$out_pre""$N""$out_post" $RES_PATH/"$out_pre""$N""$out_post"
		fi

		echo ""
    done

}

if [ "$USE_FORMAL" == "true" ]; then
	run_tests "${f_input_prefix["$HW"]}" "${f_input_postfix["$HW"]}" "${f_output_prefix["$HW"]}" "${f_output_postfix["$HW"]}"
else
	run_tests "${input_prefix["$HW"]}" "${input_postfix["$HW"]}" "${output_prefix["$HW"]}" "${output_postfix["$HW"]}"
fi
