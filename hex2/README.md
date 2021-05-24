# Hex Tools

Take a string in the form `name, FFFFFF` and returns RGB and HSL values.

Currently takes an input file, outputs JSON.

## Usage

Edit `dcolors` to include the colors that you like, then:

```
$ make
$ ./hex2
```

## Notes

- https://www.color-hex.com/color/f0f8ff -> gave me the wrong hsl for aliceblue, beware with online tools as they may be wrong
- There are issues when RGB values are equal
