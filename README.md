![LiveWatcher logo](/images/icon-256.png)

## Overview

The program is a simple rtsp-player for video surveillance cameras.
Its main features are:
* saving/restoring settings;
* system tray usage;
* IP-address format checking;
* full screen mode;
* real time color settings.
It's written on plain C++, without QML and QDesigner. It has handy installer not to clutter up its host operating system.

![LiveWatcher GUI](/images/screenshot.png)

## Build instructions

To generate distrib files:
```
windeployqt camera_viewer.exe --release
```

To generate installer:
```
..\..\bin\binarycreator.exe -c config\config.xml -p packages LiveWatcher-1.0.0.Installer.exe
```

To generate icon:
```
magick.exe convert icon-16.png icon-32.png icon-256.png icon.ico
```

## Useful links
- [Qt for Windows - Deployment](https://doc.qt.io/qt-5/windows-deployment.html)
- [Tutorial: Creating an Installer](https://doc.qt.io/qtinstallerframework/ifw-tutorial.html)
- [Setting the Application Icon](https://doc.qt.io/qtinstallerframework/ifw-tutorial.html)
- [QDarkStyleSheet](https://github.com/ColinDuquesnoy/QDarkStyleSheet)


## Known bugs

All the known bugs are related to the internal Qt errors:
* window detaches when exit from full screen mode in Linux OS;
* errors when working with multiple monitors.
