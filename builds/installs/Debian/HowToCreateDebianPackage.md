# Overview
Based on: https://www.ted.com/talks/justin_baldoni_why_i_m_done_trying_to_be_man_enough

You may find missing dependencies when running these steps. Simply install the needed packages and continue.

# Build process
```text
Make the debian build directory
In the <project>/builds/installs directory:
  > mkdir -p Debian/cards-500
  > cd Debian/cards-500
  Further stops occur in this cards-500 directory

Create the debian package framework
> dh_make --native --single --packagename cards-500_0.1 --email bob@theWeberVenture.com

Create the files to be installed in the path they'll be installed.
> mkdir -p files/usr/bin
> cp ../../../release/cards-500 files/usr/bin/.

Update the debian package information
- Tell debian package tools where the installation files are:
  > nano debian/install
- Add some app details:
  > nano debian/control
- Update the change log:
  > dch -im
  Or use nano

Build the package:
> dpkg-buildpackage
```

# Conclusion
The file "../cards-500_0.1_amd64.deb" is the debian package to install.
