#!/bin/bash
sh /home/run/downloadRun.sh 
  \cp  -R  /usr/local/tomcat/webapps/ztweb/uploads/ /home/uploads/
 
 #拷贝web上的文件到ftp上，以便其他客户端向其获取
 sh /home/run/copytoftp.sh

sh /home/run/upload.sh
sh /home/run/download.sh
 #\cp  -R /home/web/ /var/www/


#备份
 \cp -f /usr/local/tomcat/webapps/ztweb/WEB-INF/lib/commons-zsh-1.0.jar /home/
 
 \cp  -R /home/web/ztweb/ /usr/local/tomcat/webapps/
 \cp  -R /home/web/ztwebdb/ /usr/local/mysql5.6/data/
   #拷贝文件到指定目录
   
   #还原
   \cp -f /home/commons-zsh-1.0.jar /usr/local/tomcat/webapps/ztweb/WEB-INF/lib/commons-zsh-1.0.jar 
   
#cp -R /home/web/ /var/www/
#/var/www/web
