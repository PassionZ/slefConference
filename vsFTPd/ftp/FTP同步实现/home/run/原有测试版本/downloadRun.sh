#!/bin/bash
HOST=`cat /home/PCNOW-HOST`

USER="root"
PASS="123456"

LCD="/home/run/"
#mkdir $LCD
RCD="/var/ftp/run"
lftp -c "set ftp:list-options -a;
open ftp://$USER:$PASS@$HOST;
lcd $LCD;
cd $RCD;
mirror --delete \
       --verbose \
       --exclude-glob a-dir-to-exclude/ \
       --exclude-glob a-file-to-exclude \
       --exclude-glob a-file-group-to-exclude* \
       --exclude-glob other-files-to-esclude"
