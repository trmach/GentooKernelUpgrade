#!/bin/bash
# attempting a kernel upgrade automation script in bash, olddefconfig and mrproper

if [[ $USER != "root" ]]; then
	echo "You must run this script with root privileges."
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
	make mrproper
	cp /usr/src/linux-$(uname -r)/.config . # copy config

	echo -n "Would you like to edit the configuration in menuconfig? [y/n] >>> "
	read CH
	if [[ ${CH,,} == "n" ]]; then
		echo
		make olddefconfig
	else
		echo
		make menuconfig
	fi

	if mount | grep "/boot"; then
		echo "Boot partition mounted..."
	else
		echo "I'm going to tell you a secret, keep it between us, alright?"
		echo "Them, they do it on purpose, to tease newcomers. First they instruct"
		echo "you to create a separate boot partition, then they tell you not to"
		echo "automount it in fstab, and then they laugh on us when we forget to"
		echo "mount boot before installing a new kernel! Yup, with boot not mounted"
		echo "you can install kernels as many as you want, when you reboot it will"
		echo "still be the old kernel you installed with Gentoo."
	fi

	make modules_prepare
	
	# add option to enable distributed compilation?

	echo -n "Please enter the number of threads to allocate to compilation\
    (default: `nproc`) >>> "
	read THREADS
	if [[ -n "$THREADS" ]]; then
		echo "using ${THREADS} threads"
	else
		THREADS=`nproc`
		echo "using ${THREADS} threads"
	fi

	make -j${THREADS}
	make modules_install
	make install
	emerge @module-rebuild
	grub-mkconfig -o /boot/grub/grub.cfg

fi

