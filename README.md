**DiscordRPConsoleClient**

A Simple command line application to control Discord Rich Presence display on your profile.
Before you can use this you need an app id. Head over to the [Discord developers site](https://discordapp.com/developers/applications/) and make yourself an app. Keep track of Client ID -- you'll be asked for it at the startup.

### Build & Run

In order to build and run the application, you first need to grab the libraries from Discord's Github [repository](https://github.com/discordapp/discord-rpc/releases). Version 3.4.0 is the latest one tested and guaranteed to be working.
After you have downloaded the libraries choose whether you wan't to link statically or dynamically.
Once you have decided navigate to `$(SolutionDir)dependencies\lib`. (If the lib folder doesn't exist just create it.)

**NOTICE: Only Windows is supported at the moment. (Read more below)**

#### Windows
Take the `.lib` file you downloaded and copy it to the `$(SolutionDir)dependencies\lib` folder. Whether you are building against 64-bit or 32-bit platform you must rename the lib file to 'discord-rpc-win64.lib' or 'discord-rpc-win32.lib'.

After that, if you are using Visual Studio with the solution settings provided in this repo, all settings are already set up and the application should build.

### Important
- Only Windows is currently supported but with small changes this should be able to run on other platforms. There are only 3 files that contain Windows specific code. These are `Main.cpp` (Windows APIs), `DiscordHandler.cpp` (Linker settings) and `pch.h` (Memory leak detection + precompiled headers).
- If the linker can't find the library files, make sure you have added `$(SolutionDir)dependencies\lib` to library directories.
- If you are getting errors on header files not found, you need to add these to include directories `$(ProjectDir)headers;$(SolutionDir)dependencies\include`.