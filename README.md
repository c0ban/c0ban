c0ban Core integration/staging tree
=====================================

What is c0ban?
----------------

"blockchain tech for everyone" by Noritaka Kobayashi, Ph.D.

.
.


c0ban is the world’s first crypto currency tied up with entertainment and advertisement services from the beginning. 
Its application will be released on App store, Google play and Web application in 2017. 
It aims at destruction and creation of advertisement market by taking advantage of micro payment feature of blockchain. 
Its main purpose is not becoming major currency on some exchange markets but major crypto currency can be used 
in anywhere with advertisement solutions.

For more information, as well as an immediately useable, read the
[original whitepaper](http://www.c0ban.co/).

License
-------

c0ban Core is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see https://opensource.org/licenses/MIT.

Development Process
-------------------

The `master` branch is regularly built and tested, but is not guaranteed to be
completely stable. [Tags](https://github.com/c0ban/c0ban/tags) are created
regularly to indicate new official, stable release versions of c0ban Core.

The contribution workflow is described in [CONTRIBUTING.md](CONTRIBUTING.md).

Testing
-------

Testing and code review is the bottleneck for development; we get more pull
requests than we can review and test on short notice. Please be patient and help out by testing
other people's pull requests, and remember this is a security-critical project where any mistake might cost people
lots of money.

### Automated Testing

Developers are strongly encouraged to write [unit tests](src/test/README.md) for new code, and to
submit new unit tests for old code. Unit tests can be compiled and run
(assuming they weren't disabled in configure) with: `make check`. Further details on running
and extending unit tests can be found in [/src/test/README.md](/src/test/README.md).

There are also [regression and integration tests](/test), written
in Python, that are run automatically on the build server.
These tests can be run (if the [test dependencies](/test) are installed) with: `test/functional/test_runner.py`

The Travis CI system makes sure that every pull request is built for Windows, Linux, and OS X, and that unit/sanity tests are run automatically.

### Manual Quality Assurance (QA) Testing

Changes should be tested by somebody other than the developer who wrote the
code. This is especially important for large or high-risk changes. It is useful
to add a test plan to the pull request description if testing the changes is
not straightforward.
