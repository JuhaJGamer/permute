# PERMUTE

A tool to get a random random-block-permutation of a string

## Usage

```
Usage: permute [OPTION]... [TEXT]...
Randomly permutes a string of characters

With no TEXT or when TEXT is -, read standard input.

  -b, --block		Set average block length (default: 4)
      --help		Show this help.
  -s, --seed		Set random seed
      --version		Show version information
```

## Algorithm

Basically, it splits a string into a sequence of blocks, each with a random length distribution centered on a mean (default: 4). It then shuffles those blocks randomly. It can take in a seed if it needs to get the same permutation multiple times.

## Installing

See [Installing](INSTALL.md)

## License

This software is licensed under the MIT Software license

See [License](LICENSE.md)

