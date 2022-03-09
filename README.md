# Unreal Mapbox Bridge Plugin

(WIP)  Alpha stage.

This project will be used to import a geojson file created from this real world heightmap terrain web application https://terrain.justgeektechs.com/#/.

**To Install and Setup:**

1) Download this plugin and put it in your Plugins folder for your project.

2) Enable these Unreal Plugins.

Remote Control API

Editor Scripting Utilities

3) Start Unreal's Web Server by selecting Window/Developer Tools/Output Log.

4) In the Output Logs console command at the bottom.  Enter

`WebControl.EnableServerOnStartup`  this will start the server everytime you open this project.

Or you can start and stop the server manually by typing in `WebControl.StartServer` or `WebControl.StopServer`

5) Next you will need to download and use the companion web application to select your Real World Location.  See https://github.com/delebash/unreal_mapbox_bridge.

Once everything is running in the web application you will need to Download a heightmap file and then click Send To Unreal to automatically import your landscape.  You can import multiple landscapes if you want.

**NOTE:**  You will need to manually adjust the Z-Scale in Unreal to get it looking good.  In the future I hope to fix the Z-Scale calculation.

For more info on Unreal's Remote Control Api see:

https://docs.unrealengine.com/4.27/en-US/ProductionPipelines/ScriptingAndAutomation/WebControl/QuickStart/


**------------Not Implemented yet---------------**

The plugin will then draw the features from the geojson file on the imported heightmap.

**To Install:**

1) Install the open source plugin VaRest from the marketplace to your Unreal Engine.  Link:  https://www.unrealengine.com/marketplace/en-US/product/varest-plugin

2) Download or clone this repo into an Unreal 4.27 Project's Plugin folder.  If a Plugin folder does not exist in your root project create one.

3) Open your Unreal project go to Edit/Plugins and enable these 3 plugins  -- Varest, Georeferencing, and UnrealMapboxBridge.

4) Search for Actor Geo Referencing System and add to your project.

5)In your content Browser view options check Show Plugin Content.

6) Select the UnrealMapboxBridge Content Folder then Blueprints folder


**To run the plugin** 

Make sure your Output Log is visible by enabling via Window/Developer Tools/Output Log

Also it is a good idea to right click your Output Log window and choose clear to make it easier to see the results.

1) Right click on the MapboxInterface and choose run.

2) Left click on the Import Geojson button.

3) For now it is limited to certain testing data.  You can navigate to the UnrealMapboxBridgePlugin folder inside your Unreal project Plugin folder.  Then navigate to Resources/Test Geojson Files/wewahootee road Florida.  Select the geojson file.

4) In the output window you will see the goejson coordinates of the road converted to Unreal Engine Coordinates.

**To Edit the Blue Print**

1) Right click on the MapboxInterface and choose edit.

2) Select GRAPH in the upper right corner.  This will allow you to edit the Blue Print graph.  On the upper left side make sure you Save and then Compile before you test new changes.  Note: at the bottom of the Blue Print window it will let you know  if it compiled successfully.

