#!/bin/bash
# attempting a kernel upgrade automation script in bash, olddefconfig and mrproper

if [[ $USER != "root" ]]; then
	echo "You must run this script with root privileges."
	return
else
	echo "root"
	
	## Here's where the symlink is updated by the user

	eselect kernel list # display options
	while true; do
		echo -n "Please choose from the list above, which symlink to use >>> "
		read ESEL
		eselect kernel set $ESEL
		if [[ $? == 0 ]]; then break # only break if eselect returns no error
		fi
	done

	cd /usr/src/linux
	#make mrproper
	#cp /usr/src/linux-$(uname -r)/.config . # copy config

	echo -n "Would you like to edit the configuration in menuconfig? [y/n] >>> "
	read -n 1 CH
	if [[ ${CH,,} == "n" ]]; then
		echo
		echo 'make olddefconfig'
	else
		echo
		echo 'make menuconfig'
	fi

	if mount | grep "/boot"; then
		echo "Boot partition mounted..."
		if [[ -e /boot/grub/grub.cfg ]]; then
			echo "GRUB configuration file found!"
			GRUBDIR="/boot/grub"
		else
			echo "Please enter the directory containing 'grub.cfg' >>> "
			read GRUBDIR

fi
