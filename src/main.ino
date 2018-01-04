constexpr int MUX_S0 = 2;
constexpr int MUX_S1 = 3;
constexpr int MUX_S2 = 4;
constexpr int MUX_S3 = 5;
constexpr int MUX_Z = A0;

void setup() {
    Serial.begin(9600);

    pinMode(MUX_S0, OUTPUT);
    pinMode(MUX_S1, OUTPUT);
    pinMode(MUX_S2, OUTPUT);
    pinMode(MUX_S3, OUTPUT);
    pinMode(MUX_Z, INPUT);
}

void loop() {
    Serial.write(256);

    uint8_t values[10];
    for(int i = 0; i < 10; ++i) {
        digitalWrite(MUX_S0, bitRead(i, 0));
        digitalWrite(MUX_S1, bitRead(i, 1));
        digitalWrite(MUX_S2, bitRead(i, 2));
        digitalWrite(MUX_S3, bitRead(i, 3));
        values[i] = static_cast<uint8_t>(constrain(map(analogRead(MUX_Z), 600, 900, 0, 255), 0, 255));

        Serial.write(values[i]);
    }

    delay(250);
}
