## Mergen4BSD

Forked from [**MergenLinux**](https://github.com/fulcrum6378/mergen_linux) at 12 November 2023, 04:04,
as a subproject of [**Mergen IV**](https://github.com/fulcrum6378/mergen_android).

### Setup Webcam

FreeBSD uses the same webcam drivers of Linux's, ported as [**webcamd**](https://github.com/hselasky/webcamd).

~\# `pkg install webcamd`

Then run it to see a list of available devices:

~\# `webcamd`

Find the actual webcam and start the daemon in the background:

~\# `webcamd -d <device name> -B`

Now you'll need to install [**Video4Linux2**](https://en.wikipedia.org/wiki/Video4Linux) API headers too:

~\# `pkg install v4l_compat`

***

### Compilation

/mergen # `make`

### Execution

This is a mere command-line program. As soon as the program starts,
recording from first detected webcam, microphone and touchpad will begin.
The main thread listens if you press the Enter button; then it will stop recording.

/mergen # `build/Mergen`

### License

```
Copyright © Mahdi Parastesh - USE IT WELL!!
```
