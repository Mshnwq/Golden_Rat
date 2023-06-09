// #include <Arduino.h>
// #include <NewPing.h>

// // Pin definitions
// #define IR_RIGHT_EMIT 2
// #define IR_RIGHT_RECV 4
// #define IR_LEFT_EMIT 3
// #define IR_LEFT_RECV 5

// /* Sensors IDs*/
// #define SENSOR_SIDE_LEFT_ID 0
// #define SENSOR_SIDE_RIGHT_ID 1
// #define NUM_SENSOR 2

// #define MAX_DISTANCE_LEFT  20// Maximum distance (in cm)to ping
// #define MAX_DISTANCE_RIGHT 20 // Maximum distance (in cm)to ping

// NewPing IR[NUM_SENSOR] = {   // Sensor object array
//   // Each sensor's trigger pin, echo pin, and max distance to ping
//   NewPing(IR_RIGHT_EMIT, IR_RIGHT_RECV, MAX_DISTANCE_LEFT), 
//   NewPing(IR_LEFT_EMIT, IR_LEFT_RECV, MAX_DISTANCE_RIGHT),
// };

// // struct Sensor {   // Sensor object array
// //   // Each sensor's trigger pin, echo pin, and max distance to ping
// //   uint8_t trig;
// //   uint8_t echo;

// //   Sensor(uint8_t trigPin, uint8_t echoPin) : trig(trigPin), echo(echoPin) {}
// // };

// // Sensor IR[NUM_SENSOR] = {
// //   Sensor(IR_RIGHT_EMIT, IR_RIGHT_RECV), 
// //   Sensor(IR_LEFT_EMIT, IR_LEFT_RECV),
// // };

// //define sound speed in cm/uS
// #define SOUND_SPEED 0.034

// long duration;
// int distance;

// // Global variables for storing sensor values
// static volatile int adcValue;  // Global variable to store ADC value
// static volatile uint16_t sensors_off[NUM_SENSOR], sensors_on[NUM_SENSOR];

// int dValue, analogInputV;
// // Function prototypes
// void startTimer1();
// void sense_IR();
// void startADC(uint8_t reciever); 
// void readADC(uint8_t reciever); 
// void set_emitter_on(uint8_t emitter);
// void set_emitter_off(uint8_t emitter);


// void startTimer1() {
//   TCCR1A = 0;
//   TCCR1B = 1<<WGM12 | 0<<CS12 | 1<<CS11 | 1<<CS10;
//   TCNT1 = 0;          // reset Timer 1 counter
//   // OCR1A = ((F_clock / prescaler) / Fs) - 1 = 2499
//   OCR1A = 2499;       // Set sampling frequency Fs = 100 Hz
//   TIMSK1 = 1<<OCIE1A; // Enable Timer 1 interrupt
//   // Disable interrupts
//   // noInterrupts();

//   // // Set Timer1 control registers
//   // TCCR2A = 0;
//   // TCCR2B = 0;

//   // // Set the compare match register for the desired frequency (Hz)
//   // OCR2A = 156; // 100 Hz (16 MHz / 1024 prescaler / 100 Hz)

//   // // Set Timer1 prescaler to 1024 and start the timer
//   // TCCR2B |= (1 << CS20);
//   // TCCR2B |= (1 << CS21);
//   // TCCR2B |= (1 << CS22);

//   // // Enable Timer1 compare match A interrupt
//   // TIMSK2 |= (1 << OCIE2A);

//   // // Enable interrupts
//   // interrupts();
// }

// // Timer1 overflow interrupt
// ISR(TIMER1_COMPA_vect) {
//   // Call the sensor management state machine
//   // Serial.println("Interrupt timer");
//   sense_IR();
// }

//   /**
//  * @brief State machine to manage the sensors activation and deactivation
//  * states and readings.
//  *
//  * In order to get accurate distance values, the phototransistor's output
//  * will be read with the infrared emitter sensors powered on and powered
//  * off. Besides, to avoid undesired interactions between different emitters and
//  * phototranistors, the reads will be done one by one.
//  *
//  * 1. Start phototransistor ADC reading (emitter is off)
//  * 2. Save phototransistor reading and turn emitter on
//  * 3. Start phototransistor ADC reading (emitter is on)
//  * 4. Save phototransistor reading and turn emitter off
//  */
// // Sensor management state machine
// void sense_IR() {
// 	// static uint8_t emitter_status = 1;
// 	static uint8_t sensor_index = 0;

// 	// switch (emitter_status) {
// 	// case 1:
//   //   // startADC((sensor_index+1)%NUM_SENSOR);
//   //   // readADC((sensor_index+1)%NUM_SENSOR);
// 	// 	emitter_status = 2;
// 	// 	break;
// 	// case 1:
//     // // readADC((sensor_index+1)%NUM_SENSOR);
// 		// set_emitter_on(sensor_index);
// 		// emitter_status = 2;
// 		// break;
// 	// case 3:
//   //   // startADC((sensor_index+1)%NUM_SENSOR);
//   //   // readADC((sensor_index+1)%NUM_SENSOR);
// 	// 	emitter_status = 4;
// 	// 	break;
// 	// case 2:
//     // readADC((sensor_index+1)%NUM_SENSOR);
// 		// set_emitter_off(sensor_index);
    
//     dValue = IR[sensor_index].ping_cm();
//         // Function for calculating the distance measured by the Ultrasonic sensor
//     // int calculateDistance(int trig, int echo) {
      
//     // digitalWrite(IR[sensor_index].trig, LOW); 
//     // delayMicroseconds(2);
//     // // Sets the trigPin on HIGH state for 10 micro seconds
//     // digitalWrite(IR[sensor_index].trig, HIGH); 
//     // delayMicroseconds(10);
//     // digitalWrite(IR[sensor_index].trig, LOW);
//     // duration = pulseIn(IR[sensor_index].echo, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
//     // distance = duration*SOUND_SPEED/2;
//       // return distance;
//     // }
//     // dValue = analogRead(reciever);
//     // Serial.print("Digital value: ");
//     // Serial.print(dValue);
//     if ((dValue < 25) && (dValue > 2)) {
//       Serial.print("ADC Value (Pin ");
//       Serial.print(sensor_index);
//       Serial.print("): ");
//       // Serial.println(distance);
//       Serial.println(dValue);
//     }
// 		// emitter_status = 1;
// 		if (sensor_index == (NUM_SENSOR - 1))
// 			sensor_index = 0;
// 		else
// 			sensor_index++;
// 		// break;
// 	// default:
// 		// break;
// 	// }
// }

// // Set a specific emitter ON
// void set_emitter_on(uint8_t emitter) {
//   switch (emitter) {
//     case SENSOR_SIDE_LEFT_ID:
//       digitalWrite(IR_LEFT_EMIT, HIGH);
//       break;
//     case SENSOR_SIDE_RIGHT_ID:
//       digitalWrite(IR_RIGHT_EMIT, HIGH);
//       break;
//     default:
//       break;
//   }
// }

// // Set a specific emitter OFF
// void set_emitter_off(uint8_t emitter) {
//   switch (emitter) {
//     case SENSOR_SIDE_LEFT_ID:
//       digitalWrite(IR_LEFT_EMIT, LOW);
//       break;
//     case SENSOR_SIDE_RIGHT_ID:
//       digitalWrite(IR_RIGHT_EMIT, LOW);
//       break;
//     default:
//       break;
//   }
// }

// void startADC(uint8_t reciever) {
//   // Start the ADC conversion on the specified pin
//   // uint8_t adcChannel = analogPinToChannel(reciever);
//   // ADMUX = (ADMUX & 0xF0) | adcChannel; // Set ADC channel

//   ADCSRA |= (1 << ADSC); // Start ADC conversion
// }

// void readADC(uint8_t reciever) {
//   // Check if ADC conversion is complete
//   // if (ADCSRA & (1 << ADIF)) {
//     // Read the ADC result
//     // adcValue = ADC;
//     dValue = analogRead(reciever);
//     // Serial.print("Digital value: ");
//     // Serial.print(dValue);
//     Serial.print("ADC Value (Pin ");
//     Serial.print(reciever);
//     Serial.print("): ");
//     Serial.print(dValue);

//     analogInputV = dValue * 4.887;
//     Serial.print(" , Analog Input voltage: ");
//     Serial.print(analogInputV);
//     Serial.println(" mV");
//     // adcValue = analogRead(reciever);

//     // Print the ADC value
//   // } else {
//   //   Serial.print("ADC Value (Pin ");
//   //   Serial.print(reciever);
//   //   Serial.print("): ");
//   //   Serial.println("Not Done");
//   // }
// }

// void setup() {
//   // Start serial communication
//   Serial.begin(9600);

//   // Initialize IR sensors
//   // Set emitter pins as OUTPUT
//   // pinMode(IR_RIGHT_EMIT, OUTPUT);
//   // pinMode(IR_LEFT_EMIT, OUTPUT);
//   // Set reciever pins as INPUT_PULLUP
//   // pinMode(IR_RIGHT_RECV, INPUT_PULLUP);
//   // pinMode(IR_LEFT_RECV, INPUT_PULLUP);

//   // Configure ADC settings
//   // ADCSRA |= (1 << ADEN);       // Enable ADC
//   // ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);  // Set ADC prescaler to 128

//   // Start the timer for sensor management
//   startTimer1();
// }

// void loop() {
//   // main loop
//   // dValue = analogRead(A0);
//   // Serial.print("Digital value: ");
//   // Serial.print(dValue);

//   // analogInputV = dValue * 4.887;
//   // Serial.print(" , Analog Input voltage: ");
//   // Serial.print(analogInputV);
//   // Serial.println(" mV");
    
//   // delay(1000);
//   // static uint8_t sensor_index = 0;

//   //   dValue = sonar[sensor_index].ping_cm();
//   //   Serial.print("ADC Value (Pin ");
//   //   Serial.print(sensor_index);
//   //   Serial.print("): ");
//   //   Serial.println(dValue);
// 	// 	if (sensor_index == (NUM_SENSOR - 1))
// 	// 		sensor_index = 0;
// 	// 	else
// 	// 		sensor_index++;
// }