#! /bin/bash

cub="./cub3D" 
path="src/maps/good/"

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color


declare -a maps=( \
cheese_maze.cub \
creepy.cub \
dungeon.cub \
library.cub \
matrix.cub \
my.cub \
sad_face.cub \
square_map.cub \
subject_map.cub \
test_map.cub \
test_pos_bottom.cub \
test_pos_left.cub \
test_pos_right.cub \
test_pos_top.cub \
test_textures.cub \
test_whitespace.cub \
works.cub \
 )
rm failed
for map in "${maps[@]}"
do
	echo " ------------------------------------" >&2
	printf "|$path$map\n" >&2
	echo " ------------------------------------" >&2
	echo "" >&2
	$cub $path$map
	if [ $? -eq 1 ]
	then
	echo "------------------------------------" >> failed
		echo "$path$map" >> failed
		# cat  "$path$map" >> failed
	echo "------------------------------------" >> failed
	fi
	echo "">&2
done
