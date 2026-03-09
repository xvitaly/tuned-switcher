# Settings

## Dialog

The **Settings** dialog can be used to control over the supported configuration options with a simple and user-friendly GUI form.

## Program settings

The following settings can be configured via the graphical user interface:

  * **Save and restore form geometry** -- enable or disable saving and restoring the size and position of the application forms. Disabling this option will delete all saved geometry settings.
  * **Use sound for notifications** -- enable or disable using the sound for notifications.
  * **Run application on startup** -- enable or disable starting the program on system startup. The [service startup](startup.md) should be enabled first.

Press **Ctrl+R** to reset all settings to default values. A confirmation dialog will be shown.

## Config file

The default configuration file is located at `$HOME/.config/EasyCoding/tuned-switcher.conf`.

## Supported options

The following configuration file options are available:

| Namespace | Name | Type | Default | Description |
| ------- | ------- | ------- | ------- | ------- |
| common | autorunEnabled | bool | true | Stores whether the autorun feature is enabled. |
| common | saveGeometry | bool | true | Stores whether saving the form geometry is enabled. |
| common | soundEnabled | bool | true | Stores whether the notification sound is enabled. |
| about | geometry | QByteArray | not set | Stores the geometry of the About form. |
| settings | geometry | QByteArray | not set | Stores the geometry of the Settings form. |
| widget | geometry | QByteArray | not set | Stores the geometry of the Widget form. |

If no value is set, the default value will be used.
