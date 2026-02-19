#include <WiFi.h>
#include <AsyncUDP.h>
#include <Adafruit_BNO08x.h>

// WiFi credentials
const char* ssid = "SHOOBY";
const char* password = "MichaelA";

//Digital Button
#define BUTTON_PIN 27
int buttonState = 0;

// BNO08x SPI Pins
#define BNO08X_CS    33
#define BNO08X_INT   26
#define BNO08X_RESET 32



//Bno08X Connections ##VERYYY IMPORTANT!!!
//VCC -> 3.3V
//GND -> GND
//SCL -> 18
//SDA -> 19
//AD0 - 23
//CS -> 33
//INT -> 26
//RST -> 32
//PS1 -> 3.3V
//PS0 -> 3.3V
//PUSHBUTTON-DATA -> 27
//PUSHBUTTON-GROUND -> GROUND 

// BNO08x object
Adafruit_BNO08x bno08x(BNO08X_RESET);

// UDP object
AsyncUDP udp;

// Destination IP and port
IPAddress destIP(192, 168, 137, 1);
const uint16_t destPort = 1234;

String failMessage = "Failed to find BNO08x chip";

String successMessage = "BNO08x Found!";
void setup() {
    Serial.begin(115200);

    //Set the button pin as input with internal pull-up resistor
    pinMode(BUTTON_PIN, INPUT_PULLUP);



    // Connect to WiFi
    ConnectWifi();

    // Initialize BNO08x
    InitializeBnO08X();
}

void loop() {


    // Read and send all available sensor events
    sh2_SensorValue_t sensorValue;
    while (bno08x.getSensorEvent(&sensorValue)) {
        if (sensorValue.sensorId == SH2_ROTATION_VECTOR) {
            // Format: real, i, j, k, accuracy
            String message =
                String(sensorValue.un.rotationVector.real, 6) + "," +
                String(sensorValue.un.rotationVector.i, 6) + "," +
                String(sensorValue.un.rotationVector.j, 6) + "," +
                String(sensorValue.un.rotationVector.k, 6) + "," +
                String(sensorValue.un.rotationVector.accuracy);

            udp.print(message.c_str());
            //Serial.println("Sent: " + message);





            delay(100);

            // Read the state of the button as input with internal pull-up resistor
            buttonState = digitalRead(BUTTON_PIN);

            //Serial.print("{Buttonstate: ");
            Serial.println(String(buttonState) + String(sensorValue.un.rotationVector.k));
            //+String(sensorValue.un.rotationVector.i)+","+String(sensorValue.un.rotationVector.j)+","

            //Serial.print("X: ");
            //Serial.println();
            //Serial.print(",");

            //Serial.print("Y: ");
            //Serial.println(String(sensorValue.un.rotationVector.j));
            //Serial.print(",");

            //Serial.print("Z: ");
            //Serial.println(String(sensorValue.un.rotationVector.k));


        }
    }
    //delay(2); // Small delay for stability





}

void InitializeBnO08X() {
    Serial.println("Initializing BNO08x...");
    if (!bno08x.begin_SPI(BNO08X_CS, BNO08X_INT)) {
        Serial.println("Failed to find BNO08x chip");
        udp.print(failMessage.c_str());
        while (1) delay(10);
    }
    Serial.println("BNO08x Found!");
    udp.print(successMessage.c_str());

    // Enable rotation vector report (every 10ms = 100Hz)
    bno08x.enableReport(SH2_ROTATION_VECTOR, 10000); // microseconds
}

void ConnectWifi() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println("Connecting to WiFi...");
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("WiFi Failed!");
        while (1) delay(1000);
    }
    Serial.print("WiFi Connected. IP: ");
    Serial.println(WiFi.localIP());

    // Connect UDP
    if (udp.connect(destIP, destPort)) {
        Serial.println("UDP connected!");
        udp.print("UDP CONNECTED!");
    }
    else {
        Serial.println("UDP connection failed!");
        while (1) delay(1000);
    }

}