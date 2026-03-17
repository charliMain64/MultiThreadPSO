#!/bin/bash
arr=()
echo "Running 10 iterations of pso program each, with 10 particles at 100000 iterations"
for i in {1..10}; do
    trimed=$(./pso 10 10 100000)
    arr+=("$trimed")
done
#echo "${arr[@]}"

for i in "${!arr[@]}"; do
	getPos="${arr[i]#*:}"
	getPos="${getPos#*:}"
	arr[i]="${getPos%%m*}"
done

#echo "${arr[@]}"

getTotal=0

for i in "${arr[@]}"; do 
	getTotal=$(awk "BEGIN {print $getTotal + $i}")
done
#echo "$getTotal"

getMean=$(awk "BEGIN {print $getTotal / 10}")

echo "10 threads mean: $getMean"

#***************************20 threads*****************************************
arrTwenty=()
for i in {1..10}; do
    trimed=$(./pso 20 10 100000)
    arrTwenty+=("$trimed")
done

for i in "${!arrTwenty[@]}"; do
	getPos="${arrTwenty[i]#*:}"
	getPos="${getPos#*:}"
	arrTwenty[i]="${getPos%%m*}"
done

getTotalTwenty=0

for i in "${arrTwenty[@]}"; do 
	getTotalTwenty=$(awk "BEGIN {print $getTotalTwenty + $i}")
done

getMeanTwenty=$(awk "BEGIN {print $getTotalTwenty / 10}")

echo "20 threads mean: $getMeanTwenty"

#***************************30 threads*****************************************
arrThirty=()
for i in {1..10}; do
    trimed=$(./pso 30 10 100000)
    arrThirty+=("$trimed")
done

for i in "${!arrThirty[@]}"; do
	getPos="${arrThirty[i]#*:}"
	getPos="${getPos#*:}"
	arrThirty[i]="${getPos%%m*}"
done

getTotalThirty=0

for i in "${arrThirty[@]}"; do
	getTotalThirty=$(awk "BEGIN {print $getTotalThirty + $i}")
done

getMeanThirty=$(awk "BEGIN {print $getTotalThirty / 10}")

echo "30 threads mean: $getMeanThirty"
#**************************10 threads Increase particles***********************
arrTwo=()
echo "Running 10 iterations of pso program each, with 40 particles at 100000 iterations"
for i in {1..10}; do
    trimed=$(./pso 10 40 100000)
    arrTwo+=("$trimed")
done

for i in "${!arrTwo[@]}"; do
	getPos="${arrTwo[i]#*:}"
	getPos="${getPos#*:}"
	arrTwo[i]="${getPos%%m*}"
done

getTotalTwo=0

for i in "${arrTwo[@]}"; do 
	getTotalTwo=$(awk "BEGIN {print $getTotalTwo + $i}")
done

getMeanTwo=$(awk "BEGIN {print $getTotalTwo / 10}")

echo "10 threads mean: $getMeanTwo"

#***************************20 threads increase particles******************************
arrTwentyTwo=()
for i in {1..10}; do
    trimed=$(./pso 20 40 100000)
    arrTwentyTwo+=("$trimed")
done

for i in "${!arrTwentyTwo[@]}"; do
	getPos="${arrTwentyTwo[i]#*:}"
	getPos="${getPos#*:}"
	arrTwentyTwo[i]="${getPos%%m*}"
done

getTotalTwentyTwo=0

for i in "${arrTwentyTwo[@]}"; do 
	getTotalTwentyTwo=$(awk "BEGIN {print $getTotalTwentyTwo + $i}")
done

getMeanTwentyTwo=$(awk "BEGIN {print $getTotalTwentyTwo / 10}")

echo "20 threads mean: $getMeanTwentyTwo"

#***************************30 threads increase particles******************************
arrThirtyTwo=()
for i in {1..10}; do
    trimed=$(./pso 30 40 100000)
    arrThirtyTwo+=("$trimed")
done

for i in "${!arrThirtyTwo[@]}"; do
	getPos="${arrThirtyTwo[i]#*:}"
	getPos="${getPos#*:}"
	arrThirtyTwo[i]="${getPos%%m*}"
done

getTotalThirtyTwo=0

for i in "${arrThirtyTwo[@]}"; do
	getTotalThirtyTwo=$(awk "BEGIN {print $getTotalThirtyTwo + $i}")
done

getMeanThirtyTwo=$(awk "BEGIN {print $getTotalThirtyTwo / 10}")

echo "30 threads mean: $getMeanThirtyTwo"
#***************************10 threads increased particles 80***************************
arrThree=()
echo "Running 10 iterations of pso program each, with 80 particles at 100000 iterations"
for i in {1..10}; do
    trimed=$(./pso 10 80 100000)
    arrThree+=("$trimed")
done

for i in "${!arrTwo[@]}"; do
	getPos="${arrThree[i]#*:}"
	getPos="${getPos#*:}"
	arrThree[i]="${getPos%%m*}"
done

getTotalThree=0

for i in "${arrThree[@]}"; do
	getTotalThree=$(awk "BEGIN {print $getTotalThree + $i}")
done

getMeanThree=$(awk "BEGIN {print $getTotalThree / 10}")

echo "10 threads mean: $getMeanThree"

#***************************20 threads increase particles 80****************************
arrTwentyThree=()
for i in {1..10}; do
    trimed=$(./pso 20 80 100000)
    arrTwentyThree+=("$trimed")
done

for i in "${!arrTwentyThree[@]}"; do
	getPos="${arrTwentyThree[i]#*:}"
	getPos="${getPos#*:}"
	arrTwentyThree[i]="${getPos%%m*}"
done

getTotalTwentyThree=0

for i in "${arrTwentyThree[@]}"; do
	getTotalTwentyThree=$(awk "BEGIN {print $getTotalTwentyThree + $i}")
done

getMeanTwentyThree=$(awk "BEGIN {print $getTotalTwentyThree / 10}")

echo "20 threads mean: $getMeanTwentyThree"

#***************************30 threads increase particles 80****************************
arrThirtyThree=()
for i in {1..10}; do
    trimed=$(./pso 30 80 100000)
    arrThirtyThree+=("$trimed")
done

for i in "${!arrThirtyThree[@]}"; do
	getPos="${arrThirtyThree[i]#*:}"
	getPos="${getPos#*:}"
	arrThirtyThree[i]="${getPos%%m*}"
done

getTotalThirtyThree=0

for i in "${arrThirtyThree[@]}"; do
	getTotalThirtyThree=$(awk "BEGIN {print $getTotalThirtyThree + $i}")
done

getMeanThirtyThree=$(awk "BEGIN {print $getTotalThirtyThree / 10}")

echo "30 threads mean: $getMeanThirtyThree"

