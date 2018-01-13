#include "I2Cdev.h"
#include "MPU6050.h"
#include <SPI.h>
constexpr int MUX_S0 = 2;
constexpr int MUX_S1 = 3;
constexpr int MUX_E00 = 4;
constexpr int MUX_E01 = 5;
constexpr int MUX_E10 = 6;
constexpr int MUX_E11 = 7;
constexpr int MUX_Z = A0;

constexpr int SENSOR_FLEX_COUNT = 10;


MPU6050 accelgyro;
 
int16_t ax, ay, az;
int16_t gx, gy, gz;

 
struct SensorPacket {
    int flex[SENSOR_FLEX_COUNT];
    int gyroscope[3];
    int accelerometer[3];
};

void muxSetup() {
    pinMode(MUX_S0, OUTPUT);
    pinMode(MUX_S1, OUTPUT);
    pinMode(MUX_E00, OUTPUT);
    pinMode(MUX_E01, OUTPUT);
    pinMode(MUX_E10, OUTPUT);
    pinMode(MUX_E11, OUTPUT);
    pinMode(MUX_Z, INPUT);
}

void muxSelect(int z) {
    bool bit2 = bitRead(z, 2);
    bool bit3 = bitRead(z, 3);

    digitalWrite(MUX_E00, (!bit2 && !bit3) ? HIGH : LOW);
    digitalWrite(MUX_E01, (bit2 && !bit3) ? HIGH : LOW);
    digitalWrite(MUX_E10, (!bit2 && bit3) ? HIGH : LOW);
    digitalWrite(MUX_E11, (bit2 && bit3) ? HIGH : LOW);

    digitalWrite(MUX_S0, bitRead(z, 0) ? HIGH : LOW);
    digitalWrite(MUX_S1, bitRead(z, 1) ? HIGH : LOW);
}

int muxRead(bool digital = true) {
    if(digital) return digitalRead(MUX_Z); else analogRead(MUX_Z);
}

void muxWrite(int value, bool digital = true) {
    if(digital) digitalWrite(MUX_Z, value); else analogWrite(MUX_Z, value);
}

void setup() {
    Serial.begin(9600);

    pinMode(MUX_S0, OUTPUT);
    pinMode(MUX_S1, OUTPUT);
    pinMode(MUX_E00, OUTPUT);
    pinMode(MUX_E01, OUTPUT);
    pinMode(MUX_E10, OUTPUT);
    pinMode(MUX_E11, OUTPUT);
    pinMode(MUX_Z, INPUT);


      // join I2C bus
    Wire.begin();
 
 
    // initialize device
    Serial.println("Initializing I2C devices...");
    accelgyro.initialize();
 
    // verify connection
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

 
}

void loop() {
    SensorPacket packet;

    // Get flex sensor readings
    for(int i = 0; i < SENSOR_FLEX_COUNT; ++i) {
        muxSelect(i);
        packet.flex[i] = muxRead(false);
    }

      // read raw accel/gyro measurements from device
    accelgyro.getMotion6(&packet.accelerometer[0], &packet.accelerometer[1], &packet.accelerometer[2], &packet.gyroscope[0], &packet.gyroscope[1], &packet.gyroscope[2]);

    Serial.write((uint8_t*) &packet, sizeof(packet));

    delay(125);
}

