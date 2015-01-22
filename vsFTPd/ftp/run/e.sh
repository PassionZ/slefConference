#!/bin/bash

cat ServerPass | while read  PASS
do
   # echo "$HOST"
   # echo "$USER"
    echo "$PASS"
cat UPSERVER | while read UPSERVER  
do
    echo "$HOST"
   # echo "$USER"
   # echo "$PASS"

cat ServerName | while read USER
do
   # echo "$HOST"
    echo "$USER"
   # echo "$PASS"




LCD="/home/UpLoadFloder/"
RCD="/var/ftp/UpLoadFloder/"
lftp -c "set ftp:list-options -a;
open ftp://$USER:$PASS@$HOST;
lcd $LCD;
cd $RCD;
mirror --reverse \
       --only-newer  \
          --verbose \
        --exclude-glob a-dir-to-exclude/ \
       --exclude-glob a-file-to-exclude \
       --exclude-glob a-file-group-to-exclude* \
       --exclude-glob other-files-to-esclude"


done
done 
done
echo "////////////"
    #echo '$HOST'
    #echo $USER
    echo "$PASS"

