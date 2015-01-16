#!/bin/bash
HOST="192.168.0.128"
USER="root"
PASS="54007"

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
