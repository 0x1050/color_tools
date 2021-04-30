# Hex Tools

Take a string in the form `name, FFFFFF` and returns RGB and HSL values.

Currently, it takes an input file, and exports html, which you can pipe into a file.
This is for the meantime, as my test set is the current CSS3 colors set and I'd rather scan a page for errors than look up a bunch of conversions and write a complicated test suite.

## Usage

Edit `dcolors` to include the colors that you like, then:

```
$ make
$ ./hex2
```
This outputs out.html, which you can open in your browser


## Todo

- Fix Bug: There is an error in the conversion algorithm when two of the RGB values are equal
- Delete debug statements in functions
- Refactor
- Create header
- Add ability to take arguments

## Notes

- https://www.color-hex.com/color/f0f8ff -> gave me the wrong hsl for aliceblue, beware with online tools as they may be wrong
- There are issues when RGB values are equal
