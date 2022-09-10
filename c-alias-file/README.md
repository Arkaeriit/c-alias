# C Alias File

If you want to make a complex C Alias, it can be quite tedious to do so in the command line. Instead, you might want to write your alias as a shell script and then convert it. This is what `c-alias-file.sh` is for.

`c-alias-file.sh` is a shell script that can convert an other shell script into a C Alias. Furthermore, it can convert itself into a C Alias.

## Usage

```
c-alias-file <file to convert> <output c alias>
```

## Installation

To install c-alias, simply run `make && sudo make install`. You can choose the installation location with the environment variable `INSTALL_PATH_BIN`.

## Limitations

As I am too lazy to fix that, octothorpes that are always considered as the start of a comment, even if they are inside quotes. If you really want to put octothorpes inside of quotes, you can use `\x23` instead.

As the script will be made into a C Alias, it have to expects its arguments to be given to it. You can make a script that works both as a C Alias and as a shell script by have it in the following fashion:

```shell
main() {
    echo $1 $2
}

main $@
```

