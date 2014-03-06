import subprocess as sp

### Regular inotifies, for large directories like /etc with many sub-dirs ###
p_etc               = sp.Popen(['./regular_inotify', '/etc'], shell=False)

### Recursive inotifies, for directories you want to watch very closely ###
# Currently populating with Ubuntu (and probably Debian) filesystem architecture
# /etc
p_etc_mysql         = sp.Popen(['./recursive_inotify', '/etc/mysql'], shell=False)
p_etc_resolvconf    = sp.Popen(['./recursive_inotify', '/etc/resolvconf'], shell=False)
p_etc_network       = sp.Popen(['./recursive_inotify', '/etc/network'], shell=False)
p_etc_sudoers.d     = sp.Popen(['./recursive_inotify', '/etc/sudoers.d'], shell=False)
p_etc_sysctl.d      = sp.Popen(['./recursive_inotify', '/etc/sysctl.d'], shell=False)
p_etc_grub.d        = sp.Popen(['./recursive_inotify', '/etc/grub.d'], shell=False)
p_etc_fstab.d       = sp.Popen(['./recursive_inotify', '/etc/fstab.d'], shell=False)

# /boot
#p_boot              = sp.Popen(['./recursive_inotify', '/etc/boot'], shell=False)

# /home
p_home              = sp.Popen(['./recursive_inotify', '/etc/home'], shell=False)

### Grab STDOUT from all ###
p_etc.communicate()
p_etc_mysql.communicate()
p_etc_resolvconf.communicate()
p_etc_network.communicate()
p_etc_sudoers.d.communicate()
p_etc_sysctl.d.communicate()
p_etc_grub.d.communicate()
p_etc_fstab.d.communicate()

#p_boot.communicate()

p_home.communicate()


# End

