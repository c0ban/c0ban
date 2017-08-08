c0ban Core 0.1.0.0
=====================
Currently, c0ban is only supported on ubuntu 16.04. (Aug 8, 2017)

Setup
---------------------
[c0ban Core](http://www.c0ban.co) is the original c0ban client and it builds the backbone of the network.

Running
---------------------
The following are some helpful notes on how to run c0ban on your native platform.

### Unix

Unpack the files into a directory and run:

- `bin/c0ban-qt` (GUI) or
- `bin/c0band` (headless)

### Windows

Unpack the files into a directory, and then run c0ban-qt.exe.

### OS X

Drag c0ban-Core to your applications folder, and then run c0ban-Core.


Building
---------------------
The following are developer notes on how to build c0ban on your native platform. They are not complete guides, but include notes on the necessary libraries, compile flags, etc.

- [OS X Build Notes](build-osx.md)
- [Unix Build Notes](build-unix.md)
- [Windows Build Notes](build-windows.md)
- [OpenBSD Build Notes](build-openbsd.md)
- [Gitian Building Guide](gitian-building.md)

Development
---------------------
The c0ban repo's [root README](/README.md) contains relevant information on the development process and automated testing.

- [Developer Notes](developer-notes.md)
- [Multiwallet Qt Development](multiwallet-qt.md)
- [Release Notes](release-notes.md)
- [Release Process](release-process.md)
- [Translation Process](translation_process.md)
- [Translation Strings Policy](translation_strings_policy.md)
- [Unit Tests](unit-tests.md)
- [Unauthenticated REST Interface](REST-interface.md)
- [Shared Libraries](shared-libraries.md)
- [BIPS](bips.md)
- [Dnsseed Policy](dnsseed-policy.md)
- [Benchmarking](benchmarking.md)

### Resources
* Discuss on the [c0banTalk](http://www.c0ban.co/#c0ban-forum) forums, in the [Development & Technical Discussion board](http://www.c0ban.co/#c0ban-forum).

### Miscellaneous
- [Assets Attribution](assets-attribution.md)
- [Files](files.md)
- [Tor Support](tor.md)
- [Init Scripts (systemd/upstart/openrc)](init.md)

License
---------------------
Distributed under the [MIT software license](http://www.opensource.org/licenses/mit-license.php).
This product includes software developed by the OpenSSL Project for use in the [OpenSSL Toolkit](https://www.openssl.org/). This product includes
cryptographic software written by Eric Young ([eay@cryptsoft.com](mailto:eay@cryptsoft.com)), and UPnP software written by Thomas Bernard.
