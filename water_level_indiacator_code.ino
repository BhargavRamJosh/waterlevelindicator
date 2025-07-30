#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>



#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT);

#define TP 4      // Trigger Pin
#define EP 5      // Echo Pin
#define RED 6     // Red LED Pin
#define YELLOW 7  // Yellow LED Pin
#define GREEN 8   // Green LED Pin
#define BUZZER 9  // Buzzer Pin

void setup() {
  // Initialize the OLED display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  
  // Start serial communication for debugging
  Serial.begin(9600);


  // Set LED and Buzzer pins as OUTPUT
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // Set the trigger and echo pins for ultrasonic sensor
  pinMode(TP, OUTPUT);
  pinMode(EP, INPUT);
    Serial.println("Starting Water Level Monitoring...");
}

void loop() {
  // Trigger the ultrasonic sensor
  digitalWrite(TP, LOW);
  delayMicroseconds(2);
  digitalWrite(TP, HIGH);
  delayMicroseconds(10);
  digitalWrite(TP, LOW);

  // Read the distance from the echo pin
  long duration = pulseIn(EP, HIGH);
  long distance = (duration / 2) / 29.1; 
  long waterlevel= 10-distance;
  Serial.print("Water level is at: ");

     Serial.print(waterlevel);
    Serial.println(" cm");

  // Display the distance on OLED
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("WaterLevel");
  display.setCursor(15,15);
  display.print(waterlevel);
  display.print("cm");

  // Turn on LEDs and buzzer based on the distance
 if (distance >= 10) {
    // Water level >= 10 cm
    digitalWrite(RED, HIGH);    // Red light ON
    digitalWrite(YELLOW, LOW);  // Yellow light OFF
    digitalWrite(GREEN, LOW);   // Green light OFF
} else if (distance >= 5 && distance < 10) {
    // Water level between 5 and 9 cm
    digitalWrite(RED, LOW);     // Red light OFF
    digitalWrite(YELLOW, HIGH); // Yellow light ON
    digitalWrite(GREEN, LOW);   // Green light OFF
} else if (distance <=3 && distance < 5) {
    // Water level between 3 and 5 cm
    digitalWrite(RED, LOW);     // Red light OFF
    digitalWrite(YELLOW, LOW);  // Yellow light OFF
    digitalWrite(GREEN, HIGH); 
    digitalWrite( BUZZER,HIGH); // Green light ON
} else {
   
    digitalWrite(RED, LOW);     // Red light OFF
    digitalWrite(YELLOW, LOW);  // Yellow light OFF
    digitalWrite(GREEN, LOW);
    digitalWrite( BUZZER,LOW);
       // Green light OFF
}

  display.display(); // Update the display
  delay(1000); // Wait for 1 second before reading again
}
