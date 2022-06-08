#!/bin/sh

# This script compiles c_alias.c to generate an
# executable. The fist argument to this script will
# used as the name of the generated executable. All
# the other arguments are used as the command to
# alias.

# ----------------------------- Default variables ---------------------------- #

set_variables() {
    if [ -z "$CC" ]
    then
        CC=gcc
    fi

    if [ -z "$CFLAGS" ]
    then
        CFLAGS="-O2"
    fi
}

# ---------------------------- Argument processing --------------------------- #

# Remove the first arguments given to this function.
get_rest_arg() {
    echo $@ | sed "s:$1::" 
}

# Format the given input so that double quotes are escaped.
escape_quotes_and_slash() {
    sed s:\\\\:\\\\\\\\:g | sed s:\":\\\\\":g
}


# Process the arguments given to generate the compiled C alias
process() {
    set_variables
    output=$1
    alias_cmd=$(get_rest_arg $@)
    source_file=./c_alias.c
    alias_define="-DCMD_TO_ALIAS=\"$(echo $alias_cmd | escape_quotes_and_slash)\""
    $CC $CFLAGS -o $output $source_file "$alias_define"
    strip $output
}

process $@

