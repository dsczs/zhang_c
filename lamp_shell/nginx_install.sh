#!/bin/bash
echo "install nginx";

# Install zlib
cd /home/soft/lamp_linux
zlib=`ls |grep zlib*.tar.gz`
rm -rf ${zlib:0:10}
tar xf $zlib
cd ${zlib:0:10}
rm -rf /usr/local/zlib
./configure --prefix=/usr/local/zlib && make && make install

# pcre
cd /home/soft/lamp_linux
pcre=`ls | grep pcre*.zip`

# Install Nginx
service nginx stop
rm -rf /usr/local/nginx
user=`cat /etc/shadow | grep www`
if [ -z $user ]
	then 
	groupadd www
	useradd -g www -s /sbin/nologin www
fi

mkdir /usr/local/nginx/
cd /home/soft/lamp_linux
openssl=`ls | grep openssl*.tar.gz`
rm -rf ${openssl:0:14}
tar xf $openssl
nginx=`ls | grep nginx*.tar.gz`
rm -rf ${nginx:0:12}
tar xf $nginx
cp -R ${openssl:0:14} ${nginx:0:12}
cd ${nginx:0:12}
./configure --prefix=/usr/local/nginx --user=www --group=www --sbin-path=/usr/local/nginx/sbin --with-http_stub_status_module --conf-path=/usr/local/nginx/nginx.conf --pid-path=/usr/local/nginx/nginx.pid --error-log-path=/usr/local/nginx/nginx-error.log  --with-http_ssl_module --with-pcre=/home/lamp_linux/pcre-8.32 --with-zlib=/home/lamp_linux/zlib-1.2.8 --with-openssl=/home/lamp_linux/openssl-1.0.1r && make && make install

--with-pcre=/home/soft/lamp_linux/${pcre:0:9} --with-zlib=/home/soft/lamp_linux/${zlib:0:10}
--with-openssl=/home/soft/lamp_linux/${openssl:0:14} && make && make install

mkdir /usr/local/nginx/access
mkdir /usr/local/nginx/vhost
rm -rf /etc/rc.d/init.d/nginx
cp /home/scripts/nginx.sh /etc/rc.d/init.d/nginx
chmod +x /etc/rc.d/init.d/nginx

