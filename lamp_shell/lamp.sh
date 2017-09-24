#!/bin/bash

sh update_os.sh
	sh apache_install.sh;
	sh nginx_install.sh;
	sh mysql_install.sh;
	sh php_install.sh;
sh ok_install.sh
