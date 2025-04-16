import sys
import os
import argparse
import subprocess
from pathlib import Path
import shutil
import yaml
import re
import tempfile

def parse_args():
    parser = argparse.ArgumentParser(description="MGC Sketch build helper")
    parser.add_argument(
        "-f", "--file",
        default="mgc-sketch.yaml",
        help="Path to mgc-sketch.yaml (default: ./mgc-sketch.yaml)"
    )
    return parser.parse_args()

def build_sketch(config):

    command = ["arduino-cli", "compile"]

    compile_options = config.get('compile')

    if compile_options.get("verbose", False):
        verbose = True
        command.append("--verbose")
    else:
        verbose = False

    target_profile = compile_options.get("profile")
    if target_profile:
        command.append("--profile")
        command.append(target_profile)

    target_profile = compile_options.get("build_path")
    if target_profile:
        command.append("--build-path")
        command.append(target_profile)

    sketch_config = config.get('sketch_config')

    if sketch_config:
        with open('./sketch.yaml', "w") as file:
            yaml.dump(sketch_config, file, default_flow_style=False)

    build_props = compile_options.get("build-property", {})

    for key, properties in build_props.items():
        if isinstance(properties, dict):
            for sub_key, sub_value in properties.items():
                command.append("--build-property")
                if isinstance(sub_value, list):
                    flags = " ".join(sub_value)
                    command.append(f"{key}.{sub_key}={flags}")
                else:
                    command.append("{key}.{sub_key}={sub_value}")

    if verbose:
        print(command)
    
    subprocess.run(command)

if __name__ == '__main__':

    args = parse_args()

    config_path = args.file
    if not os.path.isfile(config_path):
        print(f"Error: config file '{config_path}' not found.")
        sys.exit(1)

    print(f"Using config: {config_path}")

    with open(config_path, 'r', encoding='utf-8') as f:
        config = yaml.safe_load(f)

    build_sketch(config)

