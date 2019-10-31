pragma Singleton
import QtQuick 2.13
import QtQuick.Window 2.12

Item {
    property int dpi: Screen.pixelDensity * 25.4
    property bool isMobile: (Qt.platform.os === "android") || (Qt.platform.os === "ios")

    function dp(x) {
        if(dpi < 120) {
            return x;
        }
        else {
            return x * (dpi/160);
        }
    }


}
