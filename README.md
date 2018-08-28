# jka-multihack

This is a multihack for the q3 based game Jedi Academy with these features:

- Wallhack
- Player glow (team and duel aware)
- Cheat unlocker
- Triggerbot

![alt text](https://github.com/ps1337/r/blob/master/jka-multihack/wallhax.jpg?raw=true)

## How it works

This hack uses DLL injection via `LoadLibraryA` (`loader.cpp`). On startup, it hooks system calls of the q3 game VM to inject custom code into the game process.

## Resources
- [mhook - A Windows API hooking library](https://github.com/martona/mhook)
- [JKA SDK](https://jkhub.org/files/file/1137-jedi-academy-sdk/)
- [Q3 Source Code](https://github.com/id-Software/Quake-III-Arena)