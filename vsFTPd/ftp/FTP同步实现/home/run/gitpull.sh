#!/bin/sh
i=0
j=0
declare -i  b=0
#echo "STARTING TO CHECK HOST ....."
while true
do
echo "while"

for ip in `cat /home/run/PC-HOST`

do

   ping -c 1 $ip > res
  grep ttl res >rus
 if [ `wc -l rus |awk '{print $1}'`  = 0 ]
  then  echo "host $ip is offline!!!!!!!!!"
if [ $b = '0' ]
then echo "$b -- "
else
echo "-- $b"

 b=0
fi

else
echo "host $ip is online $b"

if [ $b = '0' ];then

 b=1
echo "run 1 time"
sh /home/run/copy.sh &
else
echo "update "
fi

 fi
sleep 30
 done

done
~             
