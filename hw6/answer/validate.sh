rm -r result answer
mkdir result answer
cp -r /home/share/hw6/* answer/
echo 1 | xargs -n 1 > args
cat args | xargs -I {} bash -c "./hw6 answer/testcase{}/corpus{} answer/testcase{}/query{} > result/result{}"
cat args | xargs -I {} bash -c "diff answer/testcase{}/result_corpus{}_query{} result/result{}"
