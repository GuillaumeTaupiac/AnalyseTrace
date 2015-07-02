#!/bin/bash

if [ $# -ne 2 ]
then
	echo "Syntaxe: $0 nomModele nombreSimulations"
	exit 1
fi

nomModele=$1;
nombreSimulations=$2;

if [ -e "Resultat$nomModele" ]
then
	rm -rf Resultat$nomModele
fi

mkdir Resultat$nomModele;
for n in `seq 1 $nombreSimulations`
do
	cd $nomModele" ("$n")";

#commande PINT

for i in `ls *.pts` 
do
	/home/gtaupiac/Documents/IRCCYN/extraireMotComposantTemporel/bin/Release/extraireMotComposant $i $n $nomModele;
done;
	cd ../
done;

cd Resultat$nomModele
rename 's/\.pts//' *.txt

for i in `ls *.txt`
do
	f=`basename $i .txt`
	x=`grep -c A $i`
	n=`wc -l $i | cut -d' ' -f1`
	echo $f $x $n | awk '{print $1": "$2/$3*100"% acceptes ("$2"/"$3"), "($3-$2)/$3*100"% refuses ("$3-$2"/"$3")"}' >> stats
done;
mv stats stats.txt

