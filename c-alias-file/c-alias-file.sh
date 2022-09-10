#!/bin/sh

# Remove comments from a shell script
remove_comments() {
    sed 's:\x23.*::'
}

# Remove non-meaningful new lines
fold_lines() {
    sed -z 's:{\s*\n:{:g' |
        sed -z 's:then\s*\n:then:g' |
        sed -z 's:else\s*\n:else:g' |
        sed -z 's:do\s*\n:do:g'     |
        sed -z 's:|\s*\n:|:g'       |
        sed -z 's:||\s*\n:||:g'     |
        sed -z 's:&&\s*\n:&&:g'     
}

remove_empty_lines() {
    sed -z 's:^\n\+::g' |
        sed -z 's:\n\+:\n:g'
}

# Replaces all remaining new lines by semicolons
remove_new_lines() {
    sed -z 's:\n:;:g'
}

# Remove the last semicolon that was left by the prvious function
remove_last_sc() {
    sed -z 's:;\s*$::'
}

# Takes the content of the first argument and feed it to c_alias using the secind argument as name
run_script() {
    c_alias $2 "$(cat $1 | remove_comments | fold_lines | remove_empty_lines | remove_new_lines | remove_last_sc)"
}

run_script $@

