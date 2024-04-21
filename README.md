## Mergen4BSD

Forked from [**MergenLinux**](https://github.com/fulcrum6378/mergen_linux) at 12 November 2023, 04:04,
as a subproject of [**Mergen IV**](https://github.com/fulcrum6378/mergen_android).

### Compilation

/mergen # `make`

### Execution

This is a mere command-line program. As soon as the program starts,
recording from first detected webcam, microphone and touchpad will begin.
The main thread listens if you press the Enter button; then it will stop recording.

/mergen # `build/Mergen`

### Dependencies

#### 1. [WebcamD](https://github.com/hselasky/webcamd)

FreeBSD uses the same webcam drivers of Linux's, ported as *webcamd* (webcam daemon).

~ \# `pkg install webcamd`

To see a list of all available devices:

~ \# `webcamd`

Find the actual webcam and start the daemon in the background:

~ \# `webcamd -d <device name> -B`

#### 2. [Video4Linux](https://en.wikipedia.org/wiki/Video4Linux)

API headers for reading image frames from a supported webcam device.

~ \# `pkg install v4l_compat`

### License

```
Copyright © Mahdi Parastesh - USE IT WELL!!
```
