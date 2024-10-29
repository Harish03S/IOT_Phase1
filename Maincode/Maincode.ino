#include <Wire.h>
#include <QMC5883LCompass.h>
#include <MPU6050.h>

QMC5883LCompass compass;
MPU6050 mpu;

void setup() {
  Serial.begin(115200);

  // Initialize I2C bus with default pins for both sensors (SDA = 21, SCL = 22)
  Wire.begin(21, 22);

  // Initialize MPU6050
  mpu.initialize();
  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed!");
    while (1);  // Loop forever if failed
  }
  Serial.println("MPU6050 connected successfully");

  // Initialize QMC5883L Compass
  compass.init();
  Serial.println("QMC5883L Compass initialized successfully");

  // Print the header line once
  Serial.println("time\tax\tay\taz\twx\twy\twz\tBx\tBy\tBz");
}

void loop() {
  // Variables for MPU6050 data
  int16_t ax, ay, az;
  int16_t gx, gy, gz;

  // Read MPU6050 data
  mpu.getAcceleration(&ax, &ay, &az);
  mpu.getRotation(&gx, &gy, &gz);

  // Read compass data from QMC5883L
  compass.read();
  int x = compass.getX();
  int y = compass.getY();
  int z = compass.getZ();

  // Get time in seconds, formatted as a floating-point number with 5 decimal places
  float currentTime = millis() / 1000.0;

  // Print data in the specified format
  Serial.print(currentTime, 5); Serial.print("\t"); // time in seconds with 5 decimal places
  Serial.print(ax); Serial.print("\t");             // ax
  Serial.print(ay); Serial.print("\t");             // ay
  Serial.print(az); Serial.print("\t");             // az
  Serial.print(gx); Serial.print("\t");             // wx
  Serial.print(gy); Serial.print("\t");             // wy
  Serial.print(gz); Serial.print("\t");             // wz
  Serial.print(x); Serial.print("\t");              // Bx
  Serial.print(y); Serial.print("\t");              // By
  Serial.println(z);                                // Bz

  delay(100);  // Delay to get regular sensor readings
}
