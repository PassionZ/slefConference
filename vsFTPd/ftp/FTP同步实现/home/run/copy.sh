#!/bin/bash
sh /home/run/downloadRun.sh 
  \cp  -R  /usr/local/tomcat/webapps/ztweb/uploads/ /home/uploads/
 
 #����web�ϵ��ļ���ftp�ϣ��Ա������ͻ��������ȡ
 sh /home/run/copytoftp.sh

sh /home/run/upload.sh
sh /home/run/download.sh
 #\cp  -R /home/web/ /var/www/


#����
 \cp -f /usr/local/tomcat/webapps/ztweb/WEB-INF/lib/commons-zsh-1.0.jar /home/
 
 \cp  -R /home/web/ztweb/ /usr/local/tomcat/webapps/
 \cp  -R /home/web/ztwebdb/ /usr/local/mysql5.6/data/
   #�����ļ���ָ��Ŀ¼
   
   #��ԭ
   \cp -f /home/commons-zsh-1.0.jar /usr/local/tomcat/webapps/ztweb/WEB-INF/lib/commons-zsh-1.0.jar 
   
#cp -R /home/web/ /var/www/
#/var/www/web
