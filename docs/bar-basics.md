The following is a summary of how the Beetle Adventure Racing game engine works, and how it's related to several other titles released for the N64.

## UltraVision

BAR was co-developed by Paradigm Entertainment, Inc. (PEI) and Electronic Arts (EA).  Development on the game was [first reported in magazines around April 1998](https://archive.org/details/vsixtyfour-issue-01-april-1998/page/n7/mode/2up?q=%22NEED+FOR+SPEED+64%22) and was originally going to be an N64-exclusive entry in EA's Need for Speed franchise.  

BAR uses an engine developed by Paradigm known as UltraVision.  This is the same engine used previously in other N64 games developed by Paradigm, starting with Pilotwings 64.

Aero Fighters Assault and F-1 World Grand Prix would be the next titles using UltraVision but F-1 World Grand Prix introduced an update to the file system that allows relocatable code overlays to be loaded into memory.  BAR became the next game to use this updated version of UltraVision. 

## UV Kernel

The UltraVision engine is divided into two sections: the kernel and the game.  The kernel handles low-level functions like controller input, drawing graphics on-screen, initializing sound, switching game states, etc.  The kernel doesn't have any relocatable code so all of the symbols inside use the same addresses every time the game is running.  Once the game engine is initialized, the kernel proceeds to load code modules from the file system and stores them in different parts of RAM.  

While these overlays make it easier for the game to load larger 3D levels and optimizes memory management, this complicates decompiling efforts because now we need to compensate for all the possible relocatable addresses that the code modules could possibly use.  

That being said, F-1's code modules are unfortunately compressed due to a lack of storage.  Because BAR uses a larger ROM size, the code modules are uncompressed here (and that certainly reduces the difficulty of this decomp project somewhat).

## FORM and Tags

The game assets and modules are stored in a file system that uses the FourCC header `FORM` for every single file in the game.  Pilotwings 64 and Aero Fighters Assault don't use a file table to look up the hundreds of assets in the ROM, but this was changed with F-1 World Grand Prix.  

Bloodangel from the PW64-decomp team recognized that this file structure is an implementation of the [Interchange File Format](https://en.wikipedia.org/wiki/Interchange_File_Format).  IFF has formed (pun intended) the basis for many other file formats that are commonly used today like .WAV, .AVI, and .AIFF.  In an interesting coincidence, IFF was developed by BAR's publisher EA back in 1985.

Each file has a FourCC "tag" assigned to it.  A majority of these tags start with "UV", followed by a two-letter suffix.  For example, `UVMO` stands for "**U**ltra**V**ision **Mo**dule" file.  You can think of this as the file's extension.

To make it easier to find assets, a table of contents is placed at the start of the file system that we refer to as `FORM0`.  This file table denotes the file's tag, along with the relative offset to the file's address.  To get the correct address for a file, simply add the address at the very end of `FORM0` (for the NTSC release, it's `0x25FD0`) with the offset of that file.  

Confusingly, the font files and `FORM0` appear to use the same file tag `UVFT`.  So depending on where it's used `UVFT` can either mean "**U**ltra**V**ision **F**on**t**" or "**U**ltra**V**ision **F**ile **T**able".
