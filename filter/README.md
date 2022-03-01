# Compile
```
$ make filter
```

# Run
```sh
$ ./filter -g INFILE.bmp OUTFILE.bmp # grayscale
$ ./filter -s INFILE.bmp OUTFILE.bmp # sepia
$ ./filter -r INFILE.bmp OUTFILE.bmp # reflect
$ ./filter -b INFILE.bmp OUTFILE.bmp # blur
```

# Note
Maybe the blur filter has some minor issue. One pixel in height darker line appears on top.
