rm -r result answer
mkdir answer result
cp /home/share/hw2/* answer/
echo 1 2 3 | xargs -n 1 >> args
cat args | xargs -I {} bash -c "./hw2 answer/hw2_test{}.csv > result/result_{}"
cat args | xargs -I {} bash -c "diff result/result_{} answer/result_{}"
