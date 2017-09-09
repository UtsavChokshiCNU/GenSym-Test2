IFS=$'\n'
x=$(find ./src/g* -type f)
for file in $x
do
	git add $file
	git commit -m "Commiting all"
done