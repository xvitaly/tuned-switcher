# Startup

## Service startup

Enable startup of the Tuned service to automatically apply performance profile settings at system boot.

If the system supports systemd, it can be done using the `systemctl` tool:

```
sudo systemctl enable --now tuned.service
```

## Application startup

To enable program startup, the autorun settings of current desktop environment should be used.
