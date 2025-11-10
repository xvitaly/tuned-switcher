# Modes

## Available modes

This program can operate in two modes:

  * system tray icon (aka applet) - default and recommended mode controlled by the system tray icon;
  * GUI application (aka widget) - simplified mode for desktop environments without a system tray support.

## Modes auto-selection

If current desktop environment has a system tray support, an applet will be used, otherwise a widget.

This behavior can be overridden using the environment variable `TUNED_SWITCHER_FORCE_GUI=1`.
