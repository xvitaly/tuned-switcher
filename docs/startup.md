# Startup

## Service startup

Enable startup of the Tuned service to automatically apply performance profile settings at system boot.

If the system supports systemd, it can be done using the `systemctl` tool:

```
sudo systemctl enable --now tuned.service
```

## Application startup

To enable program startup, just open the **Settings** dialog and set the **Run application on startup** checkbox.

Also, the autorun settings of current desktop environment can be used too.
