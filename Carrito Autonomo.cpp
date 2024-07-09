/*#include <Arduino.h>
#include <SoftwareSerial.h>

// CONEXIONES PARA EL BLUETOOTH.
int bluetoothTx = 2; // Pin de transmisión para el módulo Bluetooth.
int bluetoothRx = 3; // Pin de recepción para el módulo Bluetooth.

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

// MOTOR 1.
int Motor1A = 5; // Pin de control del primer motor, dirección A.
int Motor1B = 6; // Pin de control del primer motor, dirección B.

// MOTOR 2.
int Motor2A = 9; // Pin de control del segundo motor, dirección A.
int Motor2B = 10; // Pin de control del segundo motor, dirección B.

// SENSOR HC-SR04 FRONTAL.
int echoPinFront = 12; // Pin Echo del sensor HC-SR04 frontal.
int trigPinFront = 11; // Pin Trig del sensor HC-SR04 frontal.

// SENSOR HC-SR04 TRASERO.
int echoPinBack = 8; // Pin Echo del sensor HC-SR04 trasero.
int trigPinBack = 7; // Pin Trig del sensor HC-SR04 trasero.

long duration;
int distanceFront;
int distanceBack;

void setup()
{
  bluetooth.begin(115200);
  bluetooth.print("$$$");
  delay(100);
  bluetooth.println("U,9600,N");
  bluetooth.begin(9600);

  pinMode(Motor1A, OUTPUT);
  pinMode(Motor2A, OUTPUT);
  pinMode(Motor1B, OUTPUT);
  pinMode(Motor2B, OUTPUT);

  pinMode(trigPinFront, OUTPUT);
  pinMode(echoPinFront, INPUT);

  pinMode(trigPinBack, OUTPUT);
  pinMode(echoPinBack, INPUT);

  digitalWrite(Motor1A, LOW);
  digitalWrite(Motor2A, LOW);
  digitalWrite(Motor1B, LOW);
  digitalWrite(Motor2B, LOW);
}

void stopMotors()
{
  digitalWrite(Motor1A, LOW);
  digitalWrite(Motor1B, LOW);
  digitalWrite(Motor2A, LOW);
  digitalWrite(Motor2B, LOW);
}

void moveForward()
{
  digitalWrite(Motor1A, HIGH);
  digitalWrite(Motor1B, LOW);
  digitalWrite(Motor2A, HIGH);
  digitalWrite(Motor2B, LOW);
}

void moveBackward()
{
  digitalWrite(Motor1A, LOW);
  digitalWrite(Motor1B, HIGH);
  digitalWrite(Motor2A, LOW);
  digitalWrite(Motor2B, HIGH);
}

void turnLeft()
{
  digitalWrite(Motor1A, LOW);
  digitalWrite(Motor1B, HIGH);
}

void turnRight()
{
  digitalWrite(Motor2A, LOW);
  digitalWrite(Motor2B, HIGH);
}

// Función para medir la distancia con el sensor HC-SR04.
int getDistance(int trigPin, int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;  // Calcula la distancia en centímetros.
  return distance;
}

void loop()
{
  // Lectura del sensor HC-SR04 frontal.
  distanceFront = getDistance(trigPinFront, echoPinFront);
  // Lectura del sensor HC-SR04 trasero.
  distanceBack = getDistance(trigPinBack, echoPinBack);

  // Si ambos sensores detectan un obstáculo (distancia menor a 10 cm), detener los motores.
  if (distanceFront < 10 && distanceBack < 10)
  {
    stopMotors();
  }
  else if (distanceFront < 10)
  {
    stopMotors();
    moveBackward();
    delay(100);  // Retrocede durante medio segundo.
    stopMotors();  // Detiene los motores después de retroceder.
  }
  else if (distanceBack < 10)
  {
    stopMotors();
    moveForward();
    delay(100);  // Avanza durante medio segundo.
    stopMotors();  // Detiene los motores después de avanzar.
  }
  else  // Si no hay obstáculos, continuar con el control Bluetooth.
  {
    if (bluetooth.available())
    {
      char toSend = (char)bluetooth.read();
      switch (toSend)
      {
      case 'S':
        stopMotors();
        break;
      case 'F':
        moveForward();
        break;
      case 'B':
        moveBackward();
        break;
      case 'L':
        turnLeft();
        break;
      case 'R':
        turnRight();
        break;
      default:
        stopMotors();
        break;
      }
    }
  }
}
*/
#include <Arduino.h>
#include <SoftwareSerial.h>

// CONEXIONES PARA EL BLUETOOTH.
int bluetoothTx = 2; // Pin de transmisión para el módulo Bluetooth.
int bluetoothRx = 3; // Pin de recepción para el módulo Bluetooth.

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

// MOTOR 1.
int Motor1A = 5; // Pin de control del primer motor, dirección A.
int Motor1B = 6; // Pin de control del primer motor, dirección B.

// MOTOR 2.
int Motor2A = 9; // Pin de control del segundo motor, dirección A.
int Motor2B = 10; // Pin de control del segundo motor, dirección B.

// SENSOR HC-SR04 FRONTAL.
int echoPinFront = 12; // Pin Echo del sensor HC-SR04 frontal.
int trigPinFront = 11; // Pin Trig del sensor HC-SR04 frontal.

// SENSOR HC-SR04 TRASERO.
int echoPinBack = 8; // Pin Echo del sensor HC-SR04 trasero.
int trigPinBack = 7; // Pin Trig del sensor HC-SR04 trasero.

// SENSORES DE LÍNEA TCRT5000.
int lineSensorLeft = A0; // Pin para el sensor de línea izquierdo.
int lineSensorRight = A1; // Pin para el sensor de línea derecho.

long duration;
int distanceFront;
int distanceBack;

void setup()
{
  bluetooth.begin(115200);
  bluetooth.print("$$$");
  delay(100);
  bluetooth.println("U,9600,N");
  bluetooth.begin(9600);

  pinMode(Motor1A, OUTPUT);
  pinMode(Motor2A, OUTPUT);
  pinMode(Motor1B, OUTPUT);
  pinMode(Motor2B, OUTPUT);

  pinMode(trigPinFront, OUTPUT);
  pinMode(echoPinFront, INPUT);

  pinMode(trigPinBack, OUTPUT);
  pinMode(echoPinBack, INPUT);

  pinMode(lineSensorLeft, INPUT);
  pinMode(lineSensorRight, INPUT);

  digitalWrite(Motor1A, LOW);
  digitalWrite(Motor2A, LOW);
  digitalWrite(Motor1B, LOW);
  digitalWrite(Motor2B, LOW);
}

void stopMotors()
{
  digitalWrite(Motor1A, LOW);
  digitalWrite(Motor1B, LOW);
  digitalWrite(Motor2A, LOW);
  digitalWrite(Motor2B, LOW);
}

void moveForward()
{
  digitalWrite(Motor1A, HIGH);
  digitalWrite(Motor1B, LOW);
  digitalWrite(Motor2A, HIGH);
  digitalWrite(Motor2B, LOW);
}

void moveBackward()
{
  digitalWrite(Motor1A, LOW);
  digitalWrite(Motor1B, HIGH);
  digitalWrite(Motor2A, LOW);
  digitalWrite(Motor2B, HIGH);
}

void turnLeft()
{
  digitalWrite(Motor1A, LOW);
  digitalWrite(Motor1B, HIGH);
}

void turnRight()
{
  digitalWrite(Motor2A, LOW);
  digitalWrite(Motor2B, HIGH);
}

// Función para medir la distancia con el sensor HC-SR04.
int getDistance(int trigPin, int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;  // Calcula la distancia en centímetros.
  return distance;
}

boolean manualControl = false;  // Variable para control manual

void handleBluetoothCommands() {
  if (bluetooth.available() > 0) {
    manualControl = true;  // Activa el control manual
    char command = bluetooth.read();
    switch (command) {
      case 'F':
        moveForward();
        break;
      case 'B':
        moveBackward();
        break;
      case 'L':
        turnLeft();
        break;
      case 'R':
        turnRight();
        break;
      case 'S':
        stopMotors();
        break;
      default:
        break;
    }
  } else {
    manualControl = false;  // Si no hay comandos Bluetooth, activa el control automático
  }
}

void loop() {
  handleBluetoothCommands();

  if (!manualControl) {
    // Código automático aquí
    distanceFront = getDistance(trigPinFront, echoPinFront);
    distanceBack = getDistance(trigPinBack, echoPinBack);

    int leftLineValue = analogRead(lineSensorLeft);
    int rightLineValue = analogRead(lineSensorRight);

    if (distanceFront < 10 && distanceBack < 10) {
      stopMotors();
    } else if (distanceFront < 10) {
      stopMotors();
      moveBackward();
      delay(100);
      stopMotors();
    } else if (distanceBack < 10) {
      stopMotors();
      moveForward();
      delay(100);
      stopMotors();
    } else {
      if (leftLineValue < 500 && rightLineValue < 500) {
        moveForward();
      } else if (leftLineValue < 500) {
        turnLeft();
      } else if (rightLineValue < 500) {
        turnRight();
      } else {
        if (leftLineValue >= 500 && rightLineValue >= 500) {
          stopMotors();
        } else if (leftLineValue >= 500) {
          turnRight();
        } else if (rightLineValue >= 500) {
          turnLeft();
        }
      }
    }
  }
}
