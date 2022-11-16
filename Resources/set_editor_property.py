import unreal
import sys

asset_path = sys.argv[1]
asset_property = sys.argv[2]
asset_value = sys.argv[3]
is_texture = sys.argv[4]
in_scene = sys.argv[5]
asset_class = sys.argv[6]
method = sys.argv[7]

world = unreal.EditorLevelLibrary.get_editor_world

if is_texture == "1":
    # Load texture
    value = unreal.EditorAssetLibrary.load_asset(asset_value)
else:
    value = asset_value

if in_scene == "0":
    # print(in_scene)
    # Asset to be loaded from Editor Content 
    # from that, get the class default object ( the actual template for the blueprint )
    blueprint_generated = unreal.EditorAssetLibrary.load_blueprint_class(asset_path)
    my_act = unreal.get_default_object(blueprint_generated) 


if in_scene == "1":
    lst_actors = unreal.EditorLevelLibrary.get_all_level_actors()
    for act in lst_actors:
        act_label = act.get_actor_label()
        if asset_class in act_label:
            my_act = act


if asset_property != "/":
    my_act.set_editor_property(asset_property,value)

if method == "import_tile":
    my_act.import_tile(my_act)

if method == "match_landscape_size":
    my_act.match_landscape_size(my_act)
 

            
            # print('tets')
            # if(len(method) == 0):
            #     print(method)
                


    # Asset to be loaded from Scene
    # print(asset_path)
    # asset = unreal.find_object(None, asset_path)
    # print (type(asset))
    # blueprint_class_default = unreal.get_default_object(asset)
    # print (type(blueprint_class_default))
    # print(dir(blueprint_class_default)) 
    # blueprint_class_default.set_editor_property('height_map',value)

    # m = unreal.find_object("EarthLandscapeClip")
    # m = unreal.load_object(Blueprint, asset_path)
    # act = unreal.load_class(Class, ' + asset_class + ')
    # print(act)
    



# #  set or get properties
# blueprint_class_default.set_editor_property(asset_property, value)
# unreal.EditorAssetLibrary.save_asset(asset_path)
