#!/bin/bash
echo "install php";


yum -y install bzip2-devel

# Install libmcrypt
rm -rf /usr/local/libmcrypt
cd /home/soft/lamp_linux
libmcrypt=`ls | grep libmcrypt*.tar.gz`
rm -rf ${libmcrypt:0:15}
tar xf $libmcrypt
cd ${libmcrypt:0:15}
./configure --prefix=/usr/local/libmcrypt && make && make install


#Install libiconv
rm -rf /usr/local/libiconv
cd /home/soft/lamp_linux
libiconv=`ls | grep libiconv*.tar.gz`
rm -rf ${libiconv:0:13}
tar xf $libiconv
cd ${libiconv:0:13}
cd srclib
sed -i -e '/gets is a security/d' ./stdio.in.h
cd ..
./configure --prefix=/usr/local/libiconv && make && make install


#Install libxml
rm -rf /usr/local/libxml2
cd /home/soft/lamp_linux
libxml=`ls | grep libxml*.tar.gz`
rm -rf ${libxml:0:13}
tar xf $libxml
cd ${libxml:0:13}
./configure --prefix=/usr/local/libxml2 --with-zlib=/usr/local/zlib/ && make && make install


#Install curl
rm -rf /usr/local/curl
cd /home/soft/lamp_linux
curl=`ls | grep curl*.tar.gz`
rm -rf ${curl:0:11}
tar xf $curl
cd ${curl:0:11}
./configure --prefix=/usr/local/curl && make && make install

#Install PHP
rm -rf /usr/local/php
rm -rf /etc/php.ini
cd /home/soft/lamp_linux
php=`ls | grep php*.tar.gz`
tar xf $php
cd ${php:0:10}
./configure --prefix=/usr/local/php --with-mysql=/usr/local/mysql --with-openssl --with-mysqli=/usr/local/mysql/bin/mysql_config --enable-mbstring --with-freetype-dir --with-jpeg-dir --with-png-dir --with-zlib --with-libxml-dir=/usr/local/libxml2 --enable-xml --enable-sockets   --with-mcrypt=/usr/local/libmcrypt/ --with-config-file-path=/etc/ --with-config-file-scan-dir=/etc/php.d  --with-bz2 --enable-maintainer-zts --enable-fpm --disable-fileinfo  --with-iconv=/usr/local/libiconv --with-curl=/usr/local/curl && make && make install

cp php.ini-production /usr/local/php/php.ini
ln -sv  /usr/local/php/php.ini /etc/php.ini
sed -i "s/max_execution_time = 30/max_execution_time = 300/g" /etc/php.ini 
sed -i "s/;date.timezone =/date.timezone = PRC/g" /etc/php.ini

cp /usr/local/php/etc/php-fpm.conf.default  /usr/local/php/etc/php-fpm.conf
rm -rf /etc/php.d/*
sed -i "s/;pid = run\/php-fpm.pid/pid = run\/php-fpm.pid/g" /usr/local/php/etc/php-fpm.conf
rm -rf /etc/rc.d/init.d/php-fpm
cp  /home/scripts/php-fpm.sh /etc/rc.d/init.d/php-fpm
chmod +x /etc/rc.d/init.d/php-fpm

service php-fpm restart

rm -rf /usr/local/nginx/nginx.conf
cp /home/scripts/nginx.conf /usr/local/nginx/nginx.conf
rm -rf /usr/local/nginx/vhost/test.conf
cp /home/scripts/test.conf /usr/local/nginx/vhost/test.conf
rm -rf /home/php
mkdir -p /home/php/php_test
cp /home/scripts/index.php /home/php/php_test


