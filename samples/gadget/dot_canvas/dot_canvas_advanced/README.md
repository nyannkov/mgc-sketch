# dot_canvas_advanced

This example demonstrates how to display advanced animations on a dot-matrix display using the MGC library.

It is recommended to first verify that `dot_canvas_simple` works correctly before using this project.

## Replacing Animations

By using the animation controller, you can load animations defined in YAML files.

The animations used in this example:

- `./resources/anim/anim_hen`
- `./resources/anim/anim_chick`

Example YAML for `anim_hen`:

```yaml
animations:
  - name: stand_left
    description: "Stand left"
    frames:
      - { file: frame_001.bmp, time_ms: 999999 }

  - name: stand_right
    description: "Stand right"
    frames:
      - { file: frame_003.bmp, time_ms: 999999 }

  - name: walk_left
    description: "Walk left"
    frames:
      - { file: frame_000.bmp, time_ms: 100 }
      - { file: frame_001.bmp, time_ms: 100 }

  - name: walk_right
    description: "Walk right"
    frames:
      - { file: frame_002.bmp, time_ms: 100 }
      - { file: frame_003.bmp, time_ms: 100 }

```
Each frame is defined as a single-tile BMP file with a display duration in milliseconds.
Multiple animations can be defined in a single YAML file.

When creating tiles, make sure that all tiles use the same color palette.
Although you can manually create one file per tile, it is recommended to first create a combined tileset and then split it into individual BMP files.
A helper script is provided for this purpose — see:

```bash
./resources/tileset/split.sh
```

## Generating Animation Data

To generate animation data, add an anim section under resources in mgc-sketch.yaml:

`src`: Path to the YAML file defining the animation
`dest_dir`: Directory where the generated animation data will be stored

```yaml
resources:
  - anim:
      src:  "./resources/anim/anim_chick/anim_chick.yml"
      dest_dir: "./src/gen/anim_chick"

  - anim:
      src:  "./resources/anim/anim_hen/anim_hen.yml"
      dest_dir: "./src/gen/anim_hen"
```

## Generating Animations

Run the following script to convert the YAML animation definitions into C structures compatible with the MGC library:

```bash
python3 <path-to-this-repository>/scripts/mgc_generate.py
```

