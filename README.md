# GODOT ENGINE 4.2.1 - GDExtension C++ - Visual Studio 2022 - MSVC

![01_logo](https://github.com/godotengine/godot-cpp/assets/12847027/4b515778-d07a-4cb4-a618-e13af3d7dba7)

![Captura de pantalla 2023-12-04 185606](https://github.com/godotengine/godot-cpp/assets/12847027/31a43d24-2c1c-4c8c-91e1-ea20bfdd3567)

![Captura de pantalla 2023-12-04 191624](https://github.com/godotengine/godot-cpp/assets/12847027/bd4e618c-054c-4e33-a941-c7f5e42fda21)

# Downloadable template project

This is a stable Visual Studio community version template preconfigured with Godot GDExtension C++ engine, so just download the repository and easily use GDExtension C++ with Godot Engine.
Since the precompiled libraries are already in the project, you don't need Python or SCONS, since Visual Studio generates the DLL; however, make sure you have the C++ and .net compilers installed in Visual Studio. I leave you a screenshot of the necessary tools so you just have to press F5 and run Godot Engine with everything included

## Install Visual Studio 2022 community en Windows 11:

Note: install the stable version, unstable versions may not work
Overlap options
* .net desktop development
* desktop development with c++
* game development with c++

![Visual_studio_compiler_gdnative](https://gitlab.com/kone9/godot-engine-4.2-template-gdextension-with-vscode-windows-11/-/raw/main/01_instalacionVisualStudio.png)


## You have 2 solutions

debug editor and debug game. You can run the game directly from Visual Studio with F5 in debug mode or open the Godot editor with CTRL + F5.

Keep in mind that in editor mode the GDextension library is not reloaded, therefore you will have to run it with CTRL + F5 so that when you compile with F7 the changes will be seen in the editor without having to restart it. This is due to a problem with the debug PDB file overwriting that is already reported on Godot's github.

In Game mode, you can debug the game and when recording you will have a hot reload and see the changes in real time.

For now I only have a solution in DEBUG mode, the RELEASE mode cannot make them work in visual studio at the moment, however the static library is loaded in the editor for future improvements.

* Debug_EDITOR_Godot
* Debug_GAME_Godot
* Release_EDITOR_Godot (IT DOES NOT WORK AT THE MOMENT AND IS NOT VISIBLE)
* Release_GAME_Godot (IT DOES NOT WORK AT THE MOMENT AND IS NOT VISIBLE)

![Captura de pantalla 2023-12-14 133259](https://github.com/godotengine/godot-cpp/assets/12847027/21015767-f810-4ca9-86da-2ec255156048)



# -----------------------------------------------------------------------------------------
# -----------------------------------------------------------------------------------------
# -----------------------------------------------------------------------------------------

# --------------->  This is the configuration of this project <---------------

The setup of the entire project is documented below, but don't worry, you don't have to, just download the project. However, if you want to know how I did it, I'll document it below.
Keep in mind that although some screenshots of this document show absolute paths, relative paths are used throughout the project so as not to have to reload their location.

# To generate the visual studio compatible static libraries that are saved in godot-cpp/bin use the following scons command.

## lib debug:
`scons platform=windows custom_api_file="gdextension\extension_api.json" target=template_debug optimize=debug debug_symbols=yes`

## lib release
`scons platform=windows custom_api_file="gdextension\extension_api.json" target=template_release optimize=speed debug_symbols=yes
`

Note that extension_api.json in godot-cpp 4.2 is located inside gdextension\extension_api.json.

Pay attention to the location of "extension_api.json"

![Captura de pantalla 2023-12-04 142631](https://github.com/godotengine/godot-cpp/assets/12847027/f9ab7d5a-fd47-42cf-b933-ab0365b2152c)


# Then in the project properties you have to add the following settings
![Captura de pantalla 2023-12-04 115832](https://github.com/godotengine/godot-cpp/assets/12847027/821b2ca9-88b2-477c-9889-e38e563b5541)

# General

* directory goes to the location where the dll is compiled, that is, inside the game project directory, this is the dll that works with GDextension
* add this name to the dll that exits visual studio libgdexample.windows.template_debug.x86_64
* Dynamic Library (.dll) configuration type
* C++ Language Standart C++ 17

![Captura de pantalla 2023-12-04 133531](https://github.com/godotengine/godot-cpp/assets/12847027/bc5b347f-5a67-4b39-9c10-ef12f87db8f6)

# Debugging

* Command "You have to add the path to the Godot executable"
* Working Directory "You have to add the path to the Godot project, by default the main scene will be executed"
* Command Arguments Alternatively you can add command arguments such as "--editor" to run the editor instead of the game within visual studio, you can create different configurations within the editor.

![debugging](https://github.com/godotengine/godot-cpp/assets/12847027/0b6033ec-a1db-45de-a3f4-ed4cf2b9eaf3)

![debugging_02](https://github.com/godotengine/godot-cpp/assets/12847027/2c8ab9da-5411-45ae-a26b-7b9f445c45d1)


# VCC Directories

* Include Directories the paths go to the bookstore
* Library Directoria path to the preconfigured binding that is in Godot-cpp/bin

![03_configuration](https://github.com/godotengine/godot-cpp/assets/12847027/4832cbc8-9ec9-45f0-a536-7087330aaf8c)

![Captura de pantalla 2023-12-14 123726](https://github.com/godotengine/godot-cpp/assets/12847027/7547483b-2867-4cc9-bd19-1a457c9a2f08)

![Captura de pantalla 2023-12-14 123745](https://github.com/godotengine/godot-cpp/assets/12847027/bdb93117-15c8-4bd4-8dc3-368c0da1d3a0)



# C/C++

## Preprocessor

* in preprocessor definitions add `WIN64` `TYPED_METHOD_BIND`  `NOMINMAX` `HOT_RELOAD_ENABLED`  `_CONSOLE`

![Captura de pantalla 2023-12-10 220442](https://github.com/godotengine/godot-cpp/assets/12847027/c9c83b32-5d4b-4f33-aa14-0299cb17c459)

![Captura de pantalla 2023-12-10 220703](https://github.com/godotengine/godot-cpp/assets/12847027/5abdd7c9-c58b-49b8-98aa-9a0fa6fdfac8)



## Code Generation

* Runtime Library Multi-treaded (/MT)
![Captura de pantalla 2023-12-04 141342](https://github.com/godotengine/godot-cpp/assets/12847027/ff0ec031-79a9-46ea-9d2c-2729bc5eb84e)


# Linker

## General

* "Additional Library Directories" Again you add the Library Directoria path to the preconfigured binding that is in Godot-cpp/bin
![07_configuration](https://github.com/godotengine/godot-cpp/assets/12847027/1cbc9d53-bc87-48f6-891f-218c0c309674)
![08_configuration](https://github.com/godotengine/godot-cpp/assets/12847027/291dab2f-199c-4b54-938f-e39f66ff9f35)

## Input

* "Additional Dependencies" Here you have to add the name of the binding generated from godot-cpp that is located within the godot-cpp/bin folder
![09_configuration](https://github.com/godotengine/godot-cpp/assets/12847027/8a1e63f8-ba6a-43b5-b4a0-26423cabc41c)
![10_configuration](https://github.com/godotengine/godot-cpp/assets/12847027/86515a1a-afdc-4758-98b6-02843fcefc2c)
 


# Don't forget the "gdexample.gdextension" that goes inside the godot project and generates that link between gdextension and godot.
Also very important to set the property [configuration] `reloadable = true` so that when creating signals you do not have to restart the editor.
Anyway, check out the official GDextension documentation.
https://docs.godotengine.org/en/stable/tutorials/scripting/gdextension/gdextension_cpp_example.html

![Captura de pantalla 2023-12-10 215222](https://github.com/godotengine/godot-cpp/assets/12847027/b87d55f9-3d8b-4a01-ab7d-41cd6390a446)

![Captura de pantalla 2023-12-10 222053](https://github.com/godotengine/godot-cpp/assets/12847027/0126823d-744e-40eb-9243-4431233c75e6)


# Visual Studio 2022 stable, Python, Scons, windows 11

![Visual-Studio-2022-stable-Python-Scons-windows-11](https://gitlab.com/kone9/gdextension-visual-studio-windows-bug-lib/-/raw/main/17_configuration.png)

