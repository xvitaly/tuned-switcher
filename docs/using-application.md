# Using application

## Modes

### Available modes

This program can operate in two modes:

  * system tray icon (aka applet) - default and recommended mode controlled by the system tray icon;
  * GUI application (aka widget) - simplified mode for desktop environments without a system tray support.

### Modes auto-selection

If current desktop environment has a system tray support, an applet will be used, otherwise a widget.

This behavior can be overridden using the environment variable `TUNED_SWITCHER_FORCE_GUI=1`.

## Startup

### Tuned startup

Enable startup of the Tuned service to automatically apply performance profile settings at system boot.

If the system supports systemd, it can be done using the `systemctl` tool:

```
sudo systemctl enable --now tuned.service
```

### Application startup

To enable program startup, the autorun settings of current desktop environment should be used.
