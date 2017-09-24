#!/bin/bash
echo "install mysql";

service mysqld stop
rm -rf /usr/local/mysql
rm -rf /etc/my.cnf
rm -rf /etc/rc.d/init.d/mysqld
cd /home/soft/lamp_linux
mysql=`ls | grep mysql*glibc*.tar.gz`
tar zxvf $mysql  -C /usr/local/
cd /usr/local/
mysql_=`ls | grep mysql-`
ln -sv $mysql_ mysql

mysqluser=`cat /etc/shadow | grep mysql`
if [ -z $mysqluser ]
	then 
	groupadd -r mysql
	useradd -g mysql -r -s /sbin/nologin  -M -d /usr/local/mysql/data mysql
fi

chown  -R mysql:mysql .

cd mysql
cp support-files/my-default.cnf  /etc/my.cnf
cp support-files/mysql.server /etc/rc.d/init.d/mysqld
chmod +x /etc/rc.d/init.d/mysqld
yum -y install libaio-devel
scripts/mysql_install_db --user=mysql


