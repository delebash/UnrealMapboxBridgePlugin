import unreal
import sys

heightmap_directory = sys.argv[1]
heightmap_file_name = sys.argv[2]
heightmap_textures_path = sys.argv[3]

# # Import known images as a list of Texture2D objects
heightmap_texture_png = heightmap_directory + "\\" + heightmap_file_name
data = unreal.AutomatedAssetImportData()
data.set_editor_property('destination_path', heightmap_textures_path)
data.set_editor_property('filenames', [heightmap_texture_png])
lst_texture2D = unreal.AssetToolsHelpers.get_asset_tools().import_assets_automated(data)
