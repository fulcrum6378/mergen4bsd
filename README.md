## Mergen4BSD

Forked from [**MergenLinux**](https://github.com/fulcrum6378/mergen_linux) at 12 November 2023, 04:04,
as a subproject of [**Mergen IV**](https://github.com/fulcrum6378/mergen_android).

FreeBSD uses the same webcam drivers of Linux ported as [**webcamd**](https://github.com/hselasky/webcamd),
so I copied some of [**Video4Linux2**](https://en.wikipedia.org/wiki/Video4Linux) headers as
[*videodev2.hpp*](vis/videodev2.hpp).

### Compilation

~$ `make`

### Execution

This is a mere command-line program. As soon as the program starts,
recording from first detected webcam, microphone and touchpad will begin.
The main thread listens if you press the Enter button; then it will stop recording.

~$ `build/Mergen`

### License

```
Copyright © Mahdi Parastesh - All Rights Reserved.
```
