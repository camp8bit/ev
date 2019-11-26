

// Pulse counter
volatile int pulseCounter = 0;

// RPM
int rpm = 0;

// Digital Pin for IRQ
int hall_irq_pin = 2; // INT0

// Calculation variables
const uint8_t pulsesPerRevolution = 20;
double pulsesPerMinute;
double distancePerRevolution = 1.36; // Distance travelled in one rotation in meters

uint8_t bits;
int speed = 0;

long now = 0, lastTime = 0;

void setup()   /****** SETUP: RUNS ONCE ******/
{
	Serial.begin(9600);
	setupHallSensorReader();
}//--setup()

void setupHallSensorReader() {
	pinMode(hall_irq_pin, INPUT_PULLUP);
	pinMode(4, INPUT_PULLUP);
	pinMode(5, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(hall_irq_pin), hallInterrupt, FALLING);
}//--setupHallSensorReader()


void loop()
{
	now = millis();

	// calculate RPM every one second
	if((now - lastTime) >= 1000 && pulseCounter != 0) {
		// For (now - lastTime) millis, the pulse is pulseCounter
		// for 1 min(60000 millis) what is pulseCount?
		pulsesPerMinute = (((double)pulseCounter)/(double)(now - lastTime))*60000;

		// RPM calculation
		rpm = pulsesPerMinute/pulsesPerRevolution;

		// Speed calculation in KMPH
		// 1.36 meters per revolution / 136 cms per revolution
		speed = (rpm * distancePerRevolution * 60)/1000;

		Serial.print("Speed is : ");
		Serial.println(speed);

		// Reset pulse counter
		pulseCounter = 0;
		lastTime = now;
	}
}//--loop()

void hallInterrupt() {
	//Serial.println("hallInterrupt");
	bits = PIND;
	bits != bits;
	if((bits & B00110100) == B00110100) // invalid case
		return;
	else if((bits & B00100100 == B00100100) || 
			(bits & B00010100 == B00010100)) // valid case
		pulseCounter++;
}//--hallInterrupt()



