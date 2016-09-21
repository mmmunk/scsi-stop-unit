#!/bin/sh

if [ "$1" = "debug" ]; then
	OPTIONS="-g -Wall"
else
	OPTIONS="-march=native -O2 -s"
fi

gcc $OPTIONS -o scsi-stop-unit scsi-stop-unit.c

if [ "$1" = "install" ]; then
	if [ `whoami` = "root" ]; then
		mv scsi-stop-unit /usr/local/bin/
		if [ "$?" = "0" ]; then
			echo "Successfully installed"
		fi
	else
		echo "Need root privileges to install"
	fi
fi
