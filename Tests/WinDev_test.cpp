#include <site-packages\WindowsDev\Include\10.0.26100.0\winrt\windows.ui.notifications.h>
#include <site-packages\WindowsDev\Include\10.0.26100.0\winrt\Windows.Data.Xml.Dom.h>
// #include <site-packages\WindowsDev\Include\10.0.26100.0\winrt\windows.ui.notifications.h>
#include <iostream>

using namespace winrt;
using namespace Windows::UI::Notifications;
using namespace Windows::Data::Xml::Dom;

int main() {
    init_apartment(); // Initialize COM apartment.

    std::wcout << L"Sending notification..." << std::endl;

    // Create notification XML.
    XmlDocument toastXml;
    toastXml.LoadXml(L"<toast>"
                     L"  <visual>"
                     L"    <binding template='ToastGeneric'>"
                     L"      <text>Title: Hello!</text>"
                     L"      <text>Message: This is a simple notification.</text>"
                     L"    </binding>"
                     L"  </visual>"
                     L"</toast>");

    // Send toast notification.
    ToastNotification toast{ toastXml };
    ToastNotificationManager::Default().CreateToastNotifier().Show(toast);

    std::wcout << L"Notification sent!" << std::endl;
    return 0;
}
