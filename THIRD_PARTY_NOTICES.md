# Third-Party Notices

This document identifies the principal third-party software and resource
licensing considerations for Simple Circuit Generator System. It is provided
for informational purposes and does not replace the license text distributed
by each upstream project.

## Qt Framework

The application is built with Qt 6 and uses the Qt Core and Qt Widgets
modules. The Windows release dynamically links against Qt shared libraries.

- Project: Qt
- Copyright: The Qt Company Ltd. and other contributors
- Open-source licensing: GNU Lesser General Public License v3 and/or other
  licenses offered by the Qt project for the relevant modules
- Licensing information: <https://www.qt.io/licensing/open-source-lgpl-obligations>
- Source code: <https://code.qt.io/cgit/>

Qt and its libraries are not relicensed under this project's MIT License.
Anyone redistributing the packaged application must retain the applicable Qt
copyright and license notices and comply with the terms under which the Qt
libraries are distributed.

## GCC and MinGW-w64 Runtime Components

Windows packages built with the MinGW toolchain may include GCC runtime
libraries and MinGW-w64 runtime components.

- GCC runtime libraries are distributed under the GNU General Public License
  with the GCC Runtime Library Exception, where applicable.
- MinGW-w64 runtime components remain subject to their respective upstream
  license terms.
- GCC Runtime Library Exception: <https://www.gnu.org/licenses/gcc-exception-3.1.html>
- MinGW-w64 project: <https://www.mingw-w64.org/>

These runtime components are not relicensed under this project's MIT License.

## Images, Icons, and Other Media

The MIT License in the repository root applies to the original program source
code, project-authored interface definitions, styles, and documentation. It
does not automatically relicense third-party images, icons, character artwork,
or other media assets.

Files under `Cpp_Practice_Picture/` and `icons/` must be redistributed only
when their provenance and redistribution rights have been confirmed. An asset
that carries its own notice or license remains governed by that notice or
license.

## No Endorsement

The names and trademarks of third-party projects are used only to identify
dependencies. Their inclusion does not imply endorsement of this project.

