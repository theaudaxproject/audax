
Debian
====================
This directory contains files used to package audaxd/audax-qt
for Debian-based Linux systems. If you compile audaxd/audax-qt yourself, there are some useful files here.

## audax: URI support ##


audax-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install audax-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your audaxqt binary to `/usr/bin`
and the `../../share/pixmaps/audax128.png` to `/usr/share/pixmaps`

audax-qt.protocol (KDE)

