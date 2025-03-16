# Packaged versions

## Distribution packages

### Fedora

Install the `tuned-switcher` package:

```
sudo dnf install tuned-switcher
```

## Distribution-agnostic packages

### Flatpak

Enable Flathub repository:

```
flatpak --user remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo
```

Install the [org.easycoding.TunedSwitcher](https://flathub.org/apps/details/org.easycoding.TunedSwitcher) package:

```
flatpak --user install flathub org.easycoding.TunedSwitcher
```
