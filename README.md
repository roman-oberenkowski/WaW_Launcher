# WaW Launcher
Simple mod launcher/ogarnizer for Call of Duty World at War (COD5)
# Screenshots
![demo](https://github.com/roman-oberenkowski/WaW_Launcher/blob/0c459aee56739bbeeb74f92159f2ea5d3e61d5b4/readme_resources/wawlauncher.jpg)

# Features
- Allows to have more than 128 mods (this is the limit of WaW mod menu)
- Launch selected mod
- Place mods in the same directory as game (you no longer need to clutter %appdata% on `C` drive)
- Automatically lauch borderless gaming app [Link](https://github.com/Codeusa/Borderless-Gaming/releases)
- Easily choose fullscreen/windowed mode
- Use diffrent wersions of the game (CoDWaW.exe and t4m.exe)

# Used lauch options
- `+seta r_fullscreen "0"` for fullscreen/widowed option
- `+set fs_localAppData %cd%` for using game directory as profile location
- `+set fs_game "mods/modName"` for launching selected mod

# How to use
1. Compile
2. Place in game directory and launch
3. Refresh modlist by typing `r` and than pressing enter 
4. Type mod number and youre set
# Additional options
- If You want to use fullscreen type also `f` (eg. `f123` or `1f23` or `123f`)
- Empty input means no mods (clean)
- `n` stands for notes - `n123` will launch notepad to edit/create notes for mod with number 123
- adding `t` will launch t4m.exe instead of CoDWaW.exe (eg. `t123` or `tf123` ...) 
