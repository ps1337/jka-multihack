When you extract this archive, you'll find these programs and docs in TOOLS:

ShaderEd2 - the shader editor/viewer
MD3View - model viewer for .md3 format models
ModView - model viewer for .glm (Ghoul2) format model
carcass - the glm model compiler (uses car files) converts root.xsi to model.glm
(note carcass requires no spaces in your path so you may have to move the files to build a model!)
Assimilate - edits car files
EffectsEd\EffectsEd.exe - the editor we used to create EFX files.
EffectsEd\Using_EffectsEd.doc
BehavEd.exe   - the editor we used to create Icarus scripts.
IBIZE.exe     - the Icarus script compiler (Note: the ICARUS compiler used in JKA is the same as the JK2 version, but the BehavEd.bhc file has changed.)
roq.exe       - tool to compile images into a RoQ video.
and JAscripts.zip - all the scripts from JKA as reference.
JKA_Game_Source_License.htm - The code license file. You must comply with this to use the source code.
Disclaimer-JediAcademy-Tools.htm - Legal disclaimer reguarding this release

It will also extract the game source folders:
CodeMP\   - all the source code for the MP game DLLs.  (see CodeMP\MakeAMod_readme.txt for more info)
ui\       - ui code header
docs\     - sample files describing NPC and saber creation

When you've made your mod, be sure to .zip it up correctly (refer to the submission guidelines you find at those sites) and submit it for everyone to enjoy!

IMPORTANT DEVELOPMENT NOTE: If you make your own models, skins or shaders for your multi-player map and want to run the map in the game, you must set sv_pure to "0" on the console.  If sv_pure is 1 (the default), the game *only* loads files that are in the pk3 files.  If you pak up your map first, into a pk3 file in your base dir, then you can load the map without turning off "pure" mode.  NOTE:  you will want to turn pure mode back on before you play online!



ShaderEd2:  

NOTE: We only recommend using this tool if you are somewhat familiar with shaders and GL in general.  You will not, generally, need to use textures that have shaders or textures that are not already in the game.  If you do, you can find resources on GL and id's shaders at many sites.  For those of you familiar with Quake 3 style shader commands, we have changed and added some commands, but it should be mostly backwards-compatible (i.e.: you may be able to take shaders from Quake 3 and Elite Force and use them in JKA).

The first time you open ShaderEd2, you need to tell it where to find your pk3 files... on the menu select "SourceSafe->Configure" and, in the "Dir" edit box, type the full path to your shader directory.  For example, with the default installation, this would be:

C:\Program Files\LucasArts\Star Wars Jedi Knight Jedi Academy\GameData\base\shaders
