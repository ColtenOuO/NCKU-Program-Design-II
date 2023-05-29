rm -r result answer
mkdir answer result
cp /home/share/hw1/* answer/
echo 1 100 1000 120 158 370 850 | xargs -n 1 >> args
cat args | xargs -I {} bash -c "./hw1 {} > result/result_{}"
cat args | xargs -I {} bash -c "diff result/result_{} answer/result_{}"
