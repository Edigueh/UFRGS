import os
import shutil

def flatten_duplicates(root_dir):
    # We walk top-down to find the outer folder first
    for root, dirs, files in os.walk(root_dir):
        for d in dirs:
            outer_folder_path = os.path.join(root, d)
            # Check if there is a subfolder with the EXACT same name inside
            inner_folder_path = os.path.join(outer_folder_path, d)
            
            if os.path.exists(inner_folder_path) and os.path.isdir(inner_folder_path):
                print(f"Found duplicate nesting: {inner_folder_path}")
                
                # 1. Move everything from the inner folder to the outer folder
                for item in os.listdir(inner_folder_path):
                    s = os.path.join(inner_folder_path, item)
                    target = os.path.join(outer_folder_path, item)
                    
                    # If the target already exists (unlikely but possible), remove it or rename
                    if os.path.exists(target):
                        if os.path.isdir(target): shutil.rmtree(s)
                        else: os.remove(s)
                    else:
                        shutil.move(s, target)
                
                # 2. Remove the now-empty inner folder
                os.rmdir(inner_folder_path)
                print(f"  -> Successfully flattened {d}")

if __name__ == "__main__":
    flatten_duplicates('.')
