# workspace-player

This software loads the workspaces, is the main component of Sirena OS, everything in GUI is executed by a instance of `workspace-player`

# Depends

This is a Qt 6 + Lua application developed over a Kubuntu environment, everything you need at this time is install:

- `qtcreator`
- `qmake6`
- `qt6-base-dev`
- `libqt6svg6-dev`
- `liblua5.4-dev`

> If you is getting error "No valid suitable kits found", do this on Qt Creator:
> 
> 1. Click on Tools -> Options
> 2. On new window: Click in "Add..."
> 3. Navigate to `/usr/lib/qt-6/bin`and select `qmake6`
