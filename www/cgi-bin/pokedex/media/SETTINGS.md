#	This file is a setting file for the database used for program.

#SECTION - General settings
#	Hash size:	1 means hash result are on a range from 0 to file_len.
#				1.3 means are on range from 0 to (file_len * 1.3).

DEFAULT_FLAGS->:ny:,
HASH_SIZE->1.3
DEBUG_LOG->y
LIBFT->
ANDROID->

#SECTION - Files flags and enums
#	OPTIONAL: Choose the enum names of your files, 
#	and the flags of the lines you need to save.
#	⚠️Remember to run update.sh before modifying this file!⚠️
#	PATTERN: 	filename->[yy=,
#	___________________________________________________________
#  |FLAG:			[	 |||y/n		|||y/n	  |||=	  |||,	   |
#  |___________________________________________________________|
#  |DESCRIPTION:	field|||multiple|||split  |||key/ |||values|
#  |				sep	 |||lines?	|||values?|||value|||sep   |
#  |				     |||		|||       |||sep  |||	   |
#  |___________________________________________________________|

# -- FLAGS -- #
data/metadata_pokemon_moves.csv->,ny,,
data/pokedex->]yy=,
# -- ENUM -- #
data/metadata_pokemon_moves.csv->MOVES
data/pokedex->POKEDEX
