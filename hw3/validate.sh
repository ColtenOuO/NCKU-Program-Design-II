rm -r result answer
mkdir answer result
cp /home/share/hw3/* answer/
echo 0 1 2 3 4 5 | xargs -n 1 >> args
cat args | xargs -I {} bash -c "./hw3 answer/hw3_test{}.csv > result/result_{}"
cat args | xargs -I {} bash -c "diff result/result_{} answer/result_{}"
