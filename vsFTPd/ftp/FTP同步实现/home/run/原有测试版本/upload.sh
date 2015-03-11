#!/bin/bash
HOST=`cat /home/PCNOW-HOST`
echo "$HOST "
USER="root"
PASS="123456"
#LCD="/home/dir/web/UpLoadFloder"

LCD="/home/uploads/"
RCD="/var/ftp/uploads/"
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
