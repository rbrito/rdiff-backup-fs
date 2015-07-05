Q: **Compile complains about -D\_FILE\_OFFSET\_BITS=64 flag. How to fix it?**

A: This flag is set by pkg-config. You need to install both a package for pkg-config and development files for fuse library (for Ubuntu libfuse-dev).