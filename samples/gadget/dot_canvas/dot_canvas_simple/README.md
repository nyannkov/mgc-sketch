# dot_canvas_simple

This example demonstrates how to display simple animations on a dot-matrix display using the MGC library.

## Sample BMP files

 - resources/tileset/tileset_hen.bmp
 - resources/tileset/tileset_chick.bmp

The LED dot-matrix display is 6×10, so tiles are defined with this size.

## Using your own BMP

To replace the displayed tiles, create an indexed-color BMP using a bitmap editor (preferably one that allows palette modification).  
This example has been tested with **mtPaint 3.50**.

## Converting BMPs for MGC

Add the following under the resources section in mgc-sketch.yaml. The BMPs will be converted into C structures for the MGC library.

- `src`: The source BMP file to convert
- `dest_dir`: Directory to store the converted files. The names of the generated files (source and header) will be based on the source name (without the extension)
- `tile_width`: Width of a single tile
- `tile_height`: Height of a single tile
- `tile_count`: Total number of tiles

```yaml
resources:
  - tileset:
      src:  "./resources/tileset/tileset_chick.bmp"
      dest_dir: "./src/gen/"
      tile_width: 6
      tile_height: 10 
      tile_count: 2 

  - tileset:
      src:  "./resources/tileset/tileset_hen.bmp"
      dest_dir: "./src/gen/"
      tile_width: 6
      tile_height: 10 
      tile_count: 2 
```

## Generating tilesets

Run the following script to convert the BMP files and generate the C structures for the tilesets:

```bash
python3 <path-to-this-repository>/scripts/mgc_generate.py
```

