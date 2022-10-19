# Unreal Mapbox Bridge Plugin

10/19/2022 New Featuere

Size in KM of selected tile at selected zoom level

![](Docs/BBSizeInKM.png)

10/14/2022  New Features -- Alpha (WIP)

Track Generator

Georeference Lng/Lat points on landscape

Import Geojson features.

Video: https://www.youtube.com/watch?v=0YaTKKJuyh0

10/08/2022 Updated for 5.1 Preview

Updated for UE 5.0 Release

This project allows you to create an Unreal landscape from a real world location on a map.
This project is not affiliated with Mapbox it is just something I wanted to do. Cheers!


### New Feature: 09/09/2022

Added ability to create landmass brush stamps from selected location.
This feature requires a paid plugin from the market place.  
https://www.unrealengine.com/marketplace/en-US/product/landscape-stamping-tool-100-custom-brushes?sessionInvalidated=true

This new feature automates the creation of the landscape brush for the above plugin.

Video <a href="https://youtu.be/f33OBh1Xk4c" target="_blank">demo</a> 

Get help here <a href="https://discord.gg/2WkHWNDf8q" target="_blank">Discord Server</a>

![image](https://user-images.githubusercontent.com/2220160/177798094-7e1b613d-7f27-402d-b966-5a07288cf6b8.png)

Other free Unreal projects:

https://github.com/delebash/unreal_vault_organizer

https://github.com/delebash/unreal_mapbox_bridge

**To Install and Setup:**

1) Download this repo or the release file
2) Unzip
3) Rename the plugin the one with all the files, by removing the -master so the folder is just called UnrealMapboxBridgePlugin
4) Copy that folder to your Plugins directory in your Unreal Project.  If you do not have a Plugins directory just create one.
5) Open your project.  It should ask you to build the plugin, click ok.
6) In your content viewer you will need to show Plugin Content
7) Go to the UnrealMapboxBridge Content/Blueprints folder and drag the Mapbox_BP blueprint onto your empty scene.  Set up lights per normal.

8) On the Mapbox_BP properties screen click the Select Map button to open up a Web Application. This is the application that allows you to choose a real world location.  The first time you open the app you will need to enter a Mapbox Api on the settings page and choose a download directory for the map files.  A free Mapbox account works great!

9) Once you have selected your download folder you need to manually copy the folder path and set that to the Height Map Directory on the Mapbox_BP settings.  Ie. copy path
E:\\MyDowloadDirectory and paste that into the Height Map Directory field in Unreal.  You only need to do this once unless you delete the Blueprint from your scene or change download directory.

10) You can navigate around the map by holding your left mouse button and dragging around. Zoom in and out via mouse wheel.

10)  Once you find a location you want left click on it.  A blue square will be shown to indicate you have made a selection.

11) Click the Download button and wait for the loading screen to complete the download.

12) Click on the Send to Unreal Button and wait for the loading screen to complete.

At this point if you switch back to your Unreal project you will see your newly imported landscape.  You can import multiple different landscapes in one project.  The location of the imported landscapes will be on top of each other so you will need to move them to see each landscape.

The map application is simply a web application bundled to an exe for use in Unreal.  For source see https://github.com/delebash/unreal_mapbox_bridge

Adjust the Z-scale of the landscape in the landscape properties as needed to look correctly, Usually you will need to adjust it down in number.  The Map Application has a Z-scale displayed but this is not always accurate. 

The Create Features Button is a work in progress on importing landscape features.  Currently not working correctly.


Features Implemented:

1) Select real world location from Map and import it as a landscape into Unreal
2) WIP --  Import landscape features such as rivers, roads, lakes.

For project status please check the <a href="https://trello.com/b/7jXYlo13/unreal-mapbox-bridge" target="_blank">Roadmap</a>


Credits to:

Zak Parrish for Track Generator https://www.youtube.com/watch?v=wR0fH6O9jD8

[L1z4rD89](https://forums.unrealengine.com/u/L1z4rD89) for Georeference and Track Generator integration 