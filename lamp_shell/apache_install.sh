#!/bin/bash
echo "Installing apache..............";

# Installing apr
yum -y install vim

# Installing apr
rm -rf /usr/local/apr
cd /home/soft/lamp_linux
apr=`ls | grep apr-1*.tar.gz`
rm -rf ${apr:0:9}
tar xf $apr
cd ${apr:0:9}
./configure --prefix=/usr/local/apr && make && make install

# Installing apr-util
rm -rf /usr/local/apr-util
cd /home/soft/lamp_linux
aprutil=`ls | grep apr-util*.tar.gz`
rm -rf ${aprutil:0:14}
tar xf $aprutil
cd ${aprutil:0:14}
./configure --prefix=/usr/local/apr-util --with-apr=/usr/local/apr && make && make install

#Installing pcre
yum -y install pcre pcre-devel
rm -rf /usr/local/pcre
cd /home/soft/lamp_linux
pcre=`ls | grep pcre*.zip`
rm -rf ${pcre:0:9}
unzip $pcre
cd ${pcre:0:9}
./configure --prefix=/usr/local/pcre && make && make install

#Installing apache
#service httpd stop
rm -rf /usr/local/apache
rm -rf /etc/httpd24
cd /home/soft/lamp_linux
yum -y install openssl-devel
http=`ls | grep http*.tar.gz`
rm -rf ${http:0:12}
tar xf $http
cd ${http:0:12}
./configure --prefix=/usr/local/apache --sysconfdir=/etc/httpd24 --enable-so --enable-ssl --enable-cgi --enable-rewrite --with-zlib --with-pcre=/usr/local/pcre/ --with-apr=/usr/local/apr --with-apr-util=/usr/local/apr-util/ --enable-modules=most --enable-mpms-shared=all --with-mpm=event && make && make install
echo "PidFile  \"/var/run/httpd.pid\"" >> /etc/httpd24/httpd.conf
rm -rf /etc/rc.d/init.d/httpd
cp /home/scripts/httpd.sh /etc/rc.d/init.d/httpd
chmod +x /etc/rc.d/init.d/httpd
cd /etc/httpd24
sed -i "s/Listen 80/Listen 81/g" httpd.conf
sed -i "s/#ServerName www.example.com:80/ServerName localhost:81/g" httpd.conf

