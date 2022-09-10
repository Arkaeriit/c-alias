# C Alias

C Alias is a tool to make binary executable that behave as a shell alias.

```shell
## Make a basic _hello world_ alias
$ c-alias hello-world echo Hello, World!
$ ./hello-world 
Hello, World!

## Make an alias that uses additional arguments
$ c-alias seq0 seq 0
$ ./seq0 3
0
1
2
3
```

## Usage

```shell
c-alias <alias name> <alias content...>
 ```

The alias content can either be given in a single arguments or in multiple arguments. If multiple arguments are given, they will be concatenated at the creation of the alias. Thus, `c-alias test echo a b` and `c-alias test "echo a b"` will produce the exact same output.

A binary of the given name is then generated. When executing this binary, the arguments given to it will be appended to the alias content. If you make the following alias: `c-alias my-echo 'echo Hi!'`, running `my-echo Hello, world` is an alias for `echo Hi! Hello, world!`.

When creating a C Alias, the arguments that you give are feed to a C compiler with the `system` with call the system shell. In that process, quotes might be removed and variables might get expanded. Think about it if some of your aliases do not behave as expected. If you want to see in detail what is going on under the hood, you can compile c-alias with the environment variable DEBUG set. This will print everything that is given to `system`.

## Installation

To install c-alias, simply run `make && sudo make install`. You can choose the installation location with the environment variables `INSTALL_PATH_SHARE` and `INSTALL_PATH_BIN`.

