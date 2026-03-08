import os
import shutil

def rename_only_with_spaces(root_dir):
    # Walk bottom-up to ensure we rename children before parents
    for root, dirs, files in os.walk(root_dir, topdown=False):
        for name in files + dirs:
            # Check if there is an actual space in the name
            if ' ' in name:
                old_path = os.path.join(root, name)
                
                # Create the clean name: replace spaces and strip leading/trailing underscores
                new_name = name.replace(' ', '_').strip('_')
                new_path = os.path.join(root, new_name)
                
                # If the new name is identical to the old one (rare, but possible with strip)
                if old_path == new_path:
                    continue

                print(f"Renaming: {name} -> {new_name}")

                if os.path.exists(new_path):
                    # HANDLE COLLISIONS (Merge)
                    if os.path.isdir(old_path) and os.path.isdir(new_path):
                        for item in os.listdir(old_path):
                            shutil.move(os.path.join(old_path, item), os.path.join(new_path, item))
                        os.rmdir(old_path)
                        print("  -> Merged folder contents.")
                    else:
                        # If it's a file collision, we rename with a suffix to avoid data loss
                        base, ext = os.path.splitext(new_path)
                        conflicted_path = f"{base}_duplicate{ext}"
                        os.rename(old_path, conflicted_path)
                        print(f"  -> Name collision! Renamed to: {os.path.basename(conflicted_path)}")
                else:
                    os.rename(old_path, new_path)

if __name__ == "__main__":
    # Run from current directory
    rename_only_with_spaces('.')
