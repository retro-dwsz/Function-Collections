// LyoqDQogKiBJbmNsdWRlcy5oeHggIkluY2x1ZGUgZmlsZXMgZm9yIFV0aWxpdHkgZmlsZXMiDQogKiBAYXV0aG9yIERhdmlkICJSw6l0cm8iIFNpxZlhaXQuDQogKiBUaGlzIGZpbGUgY29udGFpbnMgcmV1aWVyZWQgaW5jbHVkZXMgZm9yIHZhcmlvdXMgcmV1c2FibGUgZnVuY3Rpb25zIGFuZCBjbGFzc2VzLg0KICogVGhpcyBpcyBub3QgbWVhbnQgdG8gYmUgZXhlY3V0ZWQgZGlyZWN0bHkuDQogKiANCiAqIERvIG5vdCBydW4gb3IgY29tcGlsZS4gVXNlIGl0IGJ5IGltcG9ydGluZy4NCiAqIFJlcXVpcmVzIEMrKzIzICgtc3RkPWMrKzIzKQ0KICogDQogKiBDb21waWxlOiBjbGFuZysrIC1zdGQ9YysrMjMgLW8gPGZpbGU+IDxmaWxlPi5jcHAgLU8zIC1XYWxsIC1wZWRhbnRpYyAtcHRocmVhZCAtbXdpbmRvd3MgLWxnZGkzMiAtbHVzZXIzMiAtbHdzMl8zMiAtVyN3YXJuaW5ncw0KICogDQogKiAtVyN3YXJuaW5ncyBhbmQgLW13aW5kb3dzIGFyZSBvcHRpb25hbA0KICov

/**
 * Includes.hxx "Include files for Utility files"
 * @author David "Rétro" Siřait.
 * This file contains reuiered includes for various reusable functions and classes.
 * This is not meant to be executed directly.
 *
 * You can freely edit this file
 * Contact me via discord @dwsz56
 *
 * Do not run or compile. Use it by importing.
 * Requires C++23 (-std=c++23)
 *
 * Compile: clang++ -std=c++23 -o <file> <file>.cpp -O3 -Wall -pedantic -pthread -mwindows -lgdi32 -luser32 -lws2_32 -W#warnings
 *
 * -W#warnings and -mwindows are optional
 */

#pragma once;

#include <iostream>       // Standard input/output
#include <string>         // String operations
#include <sstream>        // String streams
#include <iomanip>        // Manipulators for formatting output
#include <limits>         // Numeric limits
#include <vector
#include <random>         // Random number generation
#include <filesystem>     // Filesystem operations
#include <algorithm>      // STL algorithms
#include <numeric>        // Numeric stuffs
#include <functional>     // Functional programming
#include <conio.h>        // For _getch() (used for waiting for keypress)
#include <thread>         // Multithreading
#include <chrono>         // Time-related functions
#include <cstdlib>        // Standard library utilities (e.g., rand, srand)
#include <ctime>          // Time utilities
#include <any>            // Type-safe containers for single values of any type
#include <windows.h>      // Core Windows API
#include <wincon.h>       // Console manipulation
#include <fstream>        // File streams
#include <tlhelp32.h>     // Process enumeration
#include <ws2tcpip.h>     // Networking utilities (getaddrinfo, inet_ntoa)
#include <winsock2.h>     // Networking (Winsock)
#include <lmcons.h>       // UNLEN for GetUsername
#include <winuser.h>      // User interface elements (e.g., message boxes)
#include "types.hxx"      // Custom type aliases

/**
# List of windows APIs
// --------------------- Others ---------------------
- winwlx.h
- windef.h
- windns.h
- windot11.h

// --------------------- Application Model ---------------------
- windows.applicationmodel.activation.h
- windows.applicationmodel.activation.idl
- windows.applicationmodel.background.h
- windows.applicationmodel.background.idl
- windows.applicationmodel.core.h
- windows.applicationmodel.core.idl
- windows.applicationmodel.datatransfer.dragdrop.core.h
- windows.applicationmodel.datatransfer.dragdrop.core.idl
- windows.applicationmodel.datatransfer.dragdrop.h
- windows.applicationmodel.datatransfer.dragdrop.idl
- windows.applicationmodel.datatransfer.h
- windows.applicationmodel.datatransfer.idl
- windows.applicationmodel.h
- windows.applicationmodel.idl

// --------------------- Data ---------------------
- windows.data.json.h
- windows.data.json.idl
- windows.data.xml.dom.h
- windows.data.xml.dom.idl

// --------------------- Devices ---------------------
- windows.devices.bluetooth.h
- windows.devices.bluetooth.idl
- windows.devices.enumeration.h
- windows.devices.enumeration.idl
- windows.devices.geolocation.h
- windows.devices.geolocation.idl
- windows.devices.haptics.h
- windows.devices.haptics.idl
- windows.devices.input.h
- windows.devices.input.idl
- windows.devices.power.h
- windows.devices.power.idl
- windows.devices.radios.h
- windows.devices.radios.idl
- windows.devices.usb.h
- windows.devices.usb.idl

// --------------------- Foundation ---------------------
- windows.foundation.collections.h
- windows.foundation.collections.idl
- windows.foundation.h
- windows.foundation.idl
- windows.foundation.metadata.h
- windows.foundation.metadata.idl
- windows.foundation.numerics.h
- windows.foundation.numerics.idl

// --------------------- Gaming ---------------------
- windows.gaming.input.custom.h
- windows.gaming.input.custom.idl
- windows.gaming.input.forcefeedback.h
- windows.gaming.input.forcefeedback.idl
- windows.gaming.input.h
- windows.gaming.input.idl
- windows.gaming.ui.h
- windows.gaming.ui.idl

// --------------------- Global ---------------------
- windows.globalization.h
- windows.globalization.idl

// --------------------- Graphics ---------------------
- windows.graphics.capture.h
- windows.graphics.capture.idl
- windows.graphics.capture.interop.h
- windows.graphics.capture.interop.idl
- windows.graphics.directx.direct3d11.h
- windows.graphics.directx.direct3d11.idl
- windows.graphics.directx.h
- windows.graphics.directx.idl
- windows.graphics.effects.h
- windows.graphics.effects.idl
- windows.graphics.h
- windows.graphics.holographic.h
- windows.graphics.holographic.idl
- windows.graphics.idl
- windows.graphics.imaging.h
- windows.graphics.imaging.idl
- windows.h
- windows.management.deployment.h
- windows.management.deployment.idl

// --------------------- Media ---------------------
- windows.media.capture.h
- windows.media.capture.idl
- windows.media.closedcaptioning.h
- windows.media.closedcaptioning.idl
- windows.media.devices.h
- windows.media.devices.idl
- windows.media.effects.h
- windows.media.effects.idl
- windows.media.faceanalysis.h
- windows.media.faceanalysis.idl
- windows.media.h
- windows.media.idl
- windows.media.render.h
- windows.media.render.idl
- windows.media.speechrecognition.h
- windows.media.speechrecognition.idl
- windows.media.speechsynthesis.h
- windows.media.speechsynthesis.idl

// --------------------- Networking ---------------------
- windows.networking.connectivity.h
- windows.networking.connectivity.idl
- windows.networking.h
- windows.networking.idl

// --------------------- Perception ---------------------
- windows.perception.spatial.h
- windows.perception.spatial.idl
- windows.perception.spatial.surfaces.h
- windows.perception.spatial.surfaces.idl

// --------------------- Security ---------------------
- windows.security.authentication.onlineid.h
- windows.security.authentication.onlineid.idl
- windows.security.authorization.appcapabilityaccess.h
- windows.security.authorization.appcapabilityaccess.idl
- windows.security.credentials.h
- windows.security.credentials.idl
- windows.security.credentials.ui.h
- windows.security.credentials.ui.idl
- windows.security.cryptography.h
- windows.security.cryptography.idl
- windows.security.enterprisedata.h
- windows.security.enterprisedata.idl
- windows.security.exchangeactivesyncprovisioning.h
- windows.security.exchangeactivesyncprovisioning.idl
- windows.security.isolation.h
- windows.security.isolation.idl

// --------------------- Storage ---------------------
- windows.storage.fileproperties.h
- windows.storage.fileproperties.idl
- windows.storage.h
- windows.storage.idl
- windows.storage.search.h
- windows.storage.search.idl
- windows.storage.streams.h
- windows.storage.streams.idl

// --------------------- System ---------------------
- windows.system.h
- windows.system.idl
- windows.system.power.h
- windows.system.power.idl
- windows.system.profile.h
- windows.system.profile.idl
- windows.system.profile.systemmanufacturers.h
- windows.system.profile.systemmanufacturers.idl
- windows.system.threading.h
- windows.system.threading.idl
- windows.system.userprofile.h
- windows.system.userprofile.idl

// --------------------- UI ---------------------
- windows.ui.composition.h
- windows.ui.composition.idl
- windows.ui.composition.interop.h
- windows.ui.composition.interop.idl
- windows.ui.core.h
- windows.ui.core.idl
- windows.ui.h
- windows.ui.idl
- windows.ui.input.h
- windows.ui.input.idl
- windows.ui.notifications.h
- windows.ui.notifications.idl
- windows.ui.viewmanagement.h
- windows.ui.viewmanagement.idl
- windows.ui.xaml.h
- windows.ui.xaml.hosting.desktopwindowxamlsource.h
- windows.ui.xaml.hosting.desktopwindowxamlsource.idl
- windows.ui.xaml.idl
- windows.ui.xaml.interop.h
- windows.ui.xaml.interop.idl

// --------------------- IDK ---------------------
- windowscontracts.h
- windowscontracts.idl
- windowsnumerics.h
- windowsnumerics.impl.h
- windowsx.h
- windowsx.h16
- winefs.h
- winerror.h
- winevt.h
- wingdi.h
- winhttp.h
- winhvemulation.h
- winhvplatform.h
- winhvplatformdefs.h
- wininet.h
- winineti.h
- winioctl.h
- winldap.h
- winnetwk.h
- winnls.h
- winnls32.h
- winnt.h
- winnt.rh
- winperf.h
- winreg.h
- winres.h
- winresrc.h
- winsafer.h
- winsatcominterfacei.h
- winscard.h
- winsdkver.h
- winsmcrd.h
- winsnmp.h
- winsock.h
- winsock2.h
- winsplp.h
- winspool.h
- winstring.h
- winsvc.h
- winsxs.h
- winsync.h
- winternl.h
- wintrust.h
- winusb.h
- winusbio.h
- winuser.h
- winuser.rh
- winver.h
*/