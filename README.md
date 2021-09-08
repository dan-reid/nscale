# nscale
Generate an equal tempered scale for a given midinote

### To compile

From the root directory run:

```
$ cd nscale
$ gcc nscale main.c
```

### Usage
`$ ./nscale <number_of_notes> <midinote> <interval>(optional)`

Example:
```
$ ./nscale 12 60 2.0
note 0: 261.625565
note 1: 277.182631
note 2: 293.664768
note 3: 311.126984
note 4: 329.627557
note 5: 349.228231
note 6: 369.994423
note 7: 391.995436
note 8: 415.304698
note 9: 440.000000
note 10: 466.163762
note 11: 493.883301
note 12: 523.251131
```


