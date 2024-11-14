#! /bin/bash

cub="./cub3D" 
path="src/maps/bad/"

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color


declare -a maps=(color_invalid_rgb.cub \
my.cub \
color_missing.cub \
color_missing_ceiling_rgb.cub \
color_missing_floor_rgb.cub \
color_none.cub \
empty.cub \
file_letter_end.cub \
filetype_missing \
filetype_wrong.buc \
forbidden.cub \
map_first.cub \
map_middle.cub \
map_missing.cub \
map_only.cub \
map_too_small.cub \
player_multiple.cub \
player_none.cub \
player_on_edge.cub \
textures_dir.cub \
textures_duplicates.cub \
textures_forbidden.cub \
textures_invalid.cub \
textures_missing.cub \
textures_none.cub \
textures_not_xpm.cub \
wall_hole_east.cub \
wall_hole_north.cub \
wall_hole_south.cub \
wall_hole_west.cub \
wall_none.cub )

rm failed
for map in "${maps[@]}"
do
	echo " ------------------------------------" >&2
	printf "|$path$map\n" >&2
	echo " ------------------------------------" >&2
	echo "" >&2
	$cub $path$map
	if [ $? -eq 0 ]
	then
	echo "------------------------------------" >> failed
		echo "$path$map" >> failed
		# cat  "$path$map" >> failed
	echo "------------------------------------" >> failed
	fi
	echo "">&2
done
