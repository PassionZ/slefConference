#!/bin/bash
sh /home/run/downloadRun.sh 
  \cp  -R  /usr/local/tomcat/webapps/ztweb/uploads/ /home/uploads/
 
sh /home/run/upload.sh
sh /home/run/download.sh
 #\cp  -R /home/web/ /var/www/


 \cp  -R /home/web/ztweb/ /usr/local/tomcat/webapps/
 \cp  -R /home/web/ztwebdb/ /usr/local/mysql5.6/data/
   #拷贝文件到指定目录
   
#cp -R /home/web/ /var/www/
#/var/www/web
