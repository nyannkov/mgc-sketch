import sys
import os
import subprocess
from pathlib import Path
import shutil
import yaml
import re

def is_folder_in_git(repo_path, ref, path):
    result = subprocess.run(
        ['git', '-C', repo_path, 'cat-file', '-t', f'{ref}:{path}'],
        stdout=subprocess.PIPE,
        stderr=subprocess.DEVNULL
    )
    return result.stdout.decode().strip() == 'tree'


def extract_file_from_git(repo_path, ref, file_path, dest_path):
    result = subprocess.run(
        ['git', '-C', repo_path, 'show', f'{ref}:{file_path}'],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE
    )

    if result.returncode != 0:
        print(f"Error reading {file_path} from {ref} in {repo_path}")
        print(result.stderr.decode())
        return

    os.makedirs(os.path.dirname(dest_path), exist_ok=True)

    with open(dest_path, 'wb') as f:
        f.write(result.stdout)
    print(f"Copied file: {file_path} -> {dest_path}")


def extract_folder_from_git(repo_path, ref, folder_path, dest_root):
    result = subprocess.run(
        ['git', '-C', repo_path, 'ls-tree', '-r', ref, folder_path],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE
    )
    if result.returncode != 0:
        print(f"Error listing folder: {folder_path} in {ref} from {repo_path}")
        print(result.stderr.decode())
        return

    for line in result.stdout.decode().splitlines():
        parts = line.split()
        if len(parts) >= 4:
            file_path = parts[3]
            relative_path = os.path.relpath(file_path, start=folder_path)
            dest_path = os.path.join(dest_root, relative_path)
            extract_file_from_git(repo_path, ref, file_path, dest_path)


def import_libs(config):
    for item in config.get("import_libs", []):
        repo = item["repo"]
        ref = item.get("ref", "HEAD") or "HEAD"

        for entry in item.get("resources", []):
            src_path, dest_path = map(str.strip, entry.split("->"))

            if is_folder_in_git(repo, ref, src_path):
                extract_folder_from_git(repo, ref, src_path, dest_path)
            else:
                extract_file_from_git(repo, ref, src_path, dest_path)


def generate_tileset(config):
    for item in config.get('resources', []):
        resource = item.get('tileset')
        if resource:
            tile_width = resource.get('tile_width')
            tile_height = resource.get('tile_height')
            tile_count = resource.get('tile_count')
            dest_dir = resource.get('dest_dir')
            bitmapfile = resource.get('src')

            command = [python_exe, str(tileset_gen)]
            params = {
                '--width': tile_width,
                '--height': tile_height,
                '--count': tile_count,
                '--dir' : dest_dir if dest_dir else './src/generated/tileset',
            }
            for key, value in params.items():
                if value:
                    command.extend([key, str(value)])

            command.append(bitmapfile)
            subprocess.run(command)


def generate_map(config):
    for item in config.get('resources', []):
        resource = item.get('map')
        if resource:
            map_compression = resource.get('compression')
            map_csv = resource.get('src')
            dest_dir = resource.get('dest_dir')

            command = [python_exe, str(map_gen)]
            params = {
                '--compression': map_compression,
                '--dir': dest_dir if dest_dir else './src/generated/map',
            }
            for key, value in params.items():
                if value:
                    command.extend([key, str(value)])
            command.append(map_csv)
            subprocess.run(command)


def generate_font(config):
    for item in config.get('resources', []):
        resource = item.get('font')
        if resource:
            font_subset = resource.get('subset')
            font_bdf = resource.get('src')
            dest_dir = resource.get('dest_dir')

            command = [python_exe, str(font_gen)]
            params = {
                '--subsettext': font_subset,
                '--dir': dest_dir if dest_dir else './src/generated/font',
            }
            for key, value in params.items():
                if value:
                    command.extend([key, str(value)])
            command.append(font_bdf)
            subprocess.run(command)

def generate_talkscript(config):
    for item in config.get('resources', []):
        resource = item.get('talkscript')
        if resource:
            talkscript_yml = resource.get('src')
            dest_dir = resource.get('dest_dir')

            command = [python_exe, str(talkscript_gen)]
            params = {
                '--dir': dest_dir if dest_dir else './src/generated/talkscript',
            }
            for key, value in params.items():
                if value:
                    command.extend([key, str(value)])
            command.append(talkscript_yml)
            subprocess.run(command)

def generate_btree(config):
    for item in config.get('resources', []):
        resource = item.get('btree')
        if resource:
            btree_yml = resource.get('src')
            dest_dir = resource.get('dest_dir')

            command = [python_exe, str(btree_gen)]
            params = {
                '--dir': dest_dir if dest_dir else './src/generated/btree',
            }
            for key, value in params.items():
                if value:
                    command.extend([key, str(value)])
            command.append(btree_yml)
            subprocess.run(command)


if __name__ == '__main__':

    python_exe = sys.executable

    mgc_tools_path = Path(__file__).parent.resolve() / '../libs/mgc/tools' 
    tileset_gen = mgc_tools_path / 'tileset_gen/tileset_gen.py'
    map_gen = mgc_tools_path / 'map_gen/map_gen.py'
    font_gen = mgc_tools_path / 'font_gen/font_gen.py'
    talkscript_gen = mgc_tools_path / 'talkscript_gen/talkscript_gen.py'
    btree_gen = mgc_tools_path / 'btree_gen/btree_gen.py'

    with open('mgc-sketch.yaml', 'r', encoding='utf-8') as f:
        config = yaml.safe_load(f)

    import_libs(config)

    generate_tileset(config)

    generate_map(config)

    generate_font(config)

    generate_talkscript(config)

    generate_btree(config)

