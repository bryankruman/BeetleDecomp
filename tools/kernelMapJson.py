#!/usr/bin/env python3
"""Convert the explicit kernel map without decomp.yaml CLI auto-detection."""
import argparse
import json
from pathlib import Path
from mapfile_parser.mapfile import MapFile

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('mapfile', type=Path)
parser.add_argument('output', type=Path)
args = parser.parse_args()
if args.mapfile.resolve() == args.output.resolve():
    parser.error('input map and output JSON must be different files')
data = MapFile.newFromMapFile(args.mapfile).toJson(humanReadable=True)
temporary = args.output.with_suffix(args.output.suffix + '.tmp')
temporary.write_text(json.dumps(data, indent=4) + '\n')
temporary.replace(args.output)
