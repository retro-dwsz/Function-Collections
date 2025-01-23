// Essentials
#include <iostream>
#include <vector>
#include <tuple>
#include <windows.h>

// Headers
#include <windows.devices.bluetooth.h>
#include <windows.devices.enumeration.h>
#include <windows.devices.geolocation.h>
#include <windows.devices.haptics.h>
#include <windows.devices.input.h>
#include <windows.devices.power.h>
#include <windows.devices.radios.h>
#include <windows.devices.usb.h>

// .idl
#include <windows.devices.bluetooth.idl>
#include <windows.devices.enumeration.idl>
#include <windows.devices.geolocation.idl>
#include <windows.devices.haptics.idl>
#include <windows.devices.input.idl>
#include <windows.devices.power.idl>
#include <windows.devices.radios.idl>
#include <windows.devices.usb.idl>

int main(const argv, const char *argv[]){
    auto deviceSelector = Windows::Devices::Bluetooth::BluetoothDevice::GetDeviceSelector();
    auto devices = Windows::Devices::Enumeration::DeviceInformation::FindAllAsync(deviceSelector).get();

    std::wcout << L"Bluetooth Devices Found: " << devices.Size() << std::endl;

    for (const auto& device : devices) {
        std::wcout << L"Name: " << device.Name().c_str() << std::endl;
    }

    return 0;
}