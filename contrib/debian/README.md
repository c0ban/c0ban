
Debian
====================
This directory contains files used to package c0band/c0ban-qt
for Debian-based Linux systems. If you compile c0band/c0ban-qt yourself, there are some useful files here.

## c0ban: URI support ##


c0ban-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install c0ban-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your c0ban-qt binary to `/usr/bin`
and the `../../share/pixmaps/c0ban128.png` to `/usr/share/pixmaps`

c0ban-qt.protocol (KDE)
