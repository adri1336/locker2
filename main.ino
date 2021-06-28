#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <AccelStepper.h>
 
ESP8266WebServer server(80);

#define motorPin1	5
#define motorPin2	4
#define motorPin3	0
#define motorPin4	2

#define MotorInterfaceType 8
AccelStepper stepper = AccelStepper(MotorInterfaceType, motorPin1, motorPin3, motorPin2, motorPin4);

bool isStepperMoving = false;
int stepperReverse = 0;

void setup() {
	Serial.begin(115200);

	WiFi.mode(WIFI_STA);
	Serial.println("");
	Serial.print("Connecting to ");
	Serial.println(ssid);
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	
	Serial.println("");
	Serial.print("Connected to ");
	Serial.println(ssid);
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());
	Serial.print("MAC address: ");
	Serial.println(WiFi.macAddress());
 
	restServerRouting();
	server.begin();
	Serial.println("HTTP server started!");

	stepper.setMaxSpeed(1000);
	Serial.println("Stepper OK!");
}
 
void loop() {
	server.handleClient();

	if(isStepperMoving) {
		if(stepper.distanceToGo() == 0) isStepperMoving = false;
		else {
			stepper.setSpeed(stepperReverse == 0 ? 1000 : -1000);
			stepper.runSpeed();
		}
	}
}

void restServerRouting() {
	server.on("/", HTTP_POST, []() {
		if(isStepperMoving) {
			isStepperMoving = false;
			delay(100);
		}

		int stepperSteps = (server.arg(String("steps"))).toInt();
		stepperReverse = (server.arg(String("reverse"))).toInt();

		Serial.println("stepperSteps: " + String(stepperSteps) + " stepperReverse: " + String(stepperReverse));
		stepper.setCurrentPosition(0);
		stepper.moveTo(stepperReverse == 0 ? stepperSteps : -stepperSteps);
		isStepperMoving = true;

		server.send(200, "text/plain", "Ok!");
    });
}