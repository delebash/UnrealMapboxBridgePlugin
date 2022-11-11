import unreal
import sys

alpha_brush_path = sys.argv[1]
alpha_brush_name = sys.argv[2]
heightmap_directory = sys.argv[3]
alpha_brush_template_path = sys.argv[4]
alpha_textures = sys.argv[5]
heightmap_property = sys.argv[6]
stamp_tool = sys.argv[7]
alpha_textures_path = alpha_brush_path + alpha_textures

# Import known images as a list of Texture2D objects
alpha_texture_png = heightmap_directory + "\\" + alpha_brush_name + ".png"

data = unreal.AutomatedAssetImportData()
data.set_editor_property('destination_path', alpha_textures_path)
data.set_editor_property('filenames', [alpha_texture_png])
lst_texture2D = unreal.AssetToolsHelpers.get_asset_tools().import_assets_automated(data)

if stamp_tool == 'Unreal Stamp Brush Plugin':
    # Duplicate stamp brush
    unreal.EditorAssetLibrary.duplicate_asset(alpha_brush_template_path, alpha_brush_path + alpha_brush_name)

    # Load texture
    blueprint_generated = unreal.EditorAssetLibrary.load_blueprint_class(alpha_brush_path + alpha_brush_name)
    texture = unreal.EditorAssetLibrary.load_asset(alpha_textures_path + alpha_brush_name)

    # from that, get the class default object ( the actual template for the blueprint )
    blueprint_class_default = unreal.get_default_object(blueprint_generated)

    #  set or get properties
    blueprint_class_default.set_editor_property(heightmap_property, texture)
    unreal.EditorAssetLibrary.save_asset(alpha_brush_path + alpha_brush_name)
