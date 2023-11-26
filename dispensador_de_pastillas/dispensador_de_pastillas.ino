#include <TimerOne.h>

int servo = 11;
float pausa;

const int pulsador_modo = 12;
const int pulsador_incrementar = 13;
const int buzzer = 2;
const int led_azul = 10;

int contador_dias = 0;
int horas = 0;
int minutos = 0;
volatile int segundos = 0;
volatile boolean actualizar = true;

int horas_alarma = 0;
int minutos_alarma = 0;
boolean alarma_on = false;
int modo = 0;
const int n_modos = 6;

void setup() {
  pinMode(servo, OUTPUT);
  analogWrite(3, 10);
  pinMode(pulsador_modo, INPUT);
  pinMode(pulsador_incrementar, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(led_azul, OUTPUT);
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(controladorTiempo);
}

void loop() {
  if (digitalRead(pulsador_modo) == HIGH) {
    modo++;
    modo = modo % n_modos;
    while (digitalRead(pulsador_modo) == HIGH);
  }

  switch (modo) {
    case 1:
      if (digitalRead(pulsador_incrementar) == HIGH) {
        incrementarHoras();
        while (digitalRead(pulsador_incrementar) == HIGH);
      }
      break;
    case 2:
      if (digitalRead(pulsador_incrementar) == HIGH) {
        incrementarMinutos();
        while (digitalRead(pulsador_incrementar) == HIGH);
      }
      break;
    case 3:
      if (digitalRead(pulsador_incrementar) == HIGH) {
        incrementarHorasAlarma();
        while (digitalRead(pulsador_incrementar) == HIGH);
      }
      break;
    case 4:
      if (digitalRead(pulsador_incrementar) == HIGH) {
        incrementarMinutosAlarma();
        while (digitalRead(pulsador_incrementar) == HIGH);
      }
      break;
    case 5:
      if (digitalRead(pulsador_incrementar) == HIGH) {
        alarma_on = !alarma_on;
        actualizar = true;
        while (digitalRead(pulsador_incrementar) == HIGH);
      }
      break;
  }

  if (actualizar == true) {
    actualizarReloj();

    if (alarma_on == true) {
      if (segundos == 0 && horas == horas_alarma && minutos == minutos_alarma && contador_dias != 7) {
        contador_dias += 1;
        girarServo(45);
        for (int nota_actual = 0; nota_actual < 10; nota_actual++) {
          digitalWrite(led_azul, HIGH);
          tone(buzzer, 523.25);
          delay(1000);
          noTone(buzzer);
          digitalWrite(led_azul, LOW);
        }
      } else if (segundos == 0 && horas == horas_alarma && minutos == minutos_alarma && contador_dias == 7) {
        contador_dias = 0;
        girarServo(45);
        for (int nota_actual = 0; nota_actual < 10; nota_actual++) {
          tone(buzzer, 523.25);
          delay(1000);
          noTone(buzzer);
        }
        for (int n = 0; n < 10; n++) {
          digitalWrite(led_azul, HIGH);
          delay(1000);
          digitalWrite(led_azul, LOW);
          delay(1000);
        }
      }
    }

    actualizar = false;
  }
}

void controladorTiempo() {
  segundos++;
  actualizar = true;
}

void actualizarReloj() {
  minutos += segundos / 60;
  segundos = segundos % 60;

  horas += minutos / 60;
  minutos = minutos % 60;

  horas = horas % 24;
}

void incrementarHoras() {
  horas++;
  horas = horas % 24;
  actualizar = true;
}

void incrementarHorasAlarma() {
  horas_alarma++;
  horas_alarma = horas_alarma % 24;
  actualizar = true;
}

void incrementarMinutosAlarma() {
  minutos_alarma++;
  minutos_alarma = minutos_alarma % 60;
  actualizar = true;
}

void incrementarMinutos() {
  minutos++;
  minutos = minutos % 60;
  actualizar = true;
}

void girarServo(int x) {
  for (int hz = 1; hz <= 50; hz++) {
    pausa = (45 * 2000 / 180) + 500;
    digitalWrite(servo, HIGH);
    delayMicroseconds(pausa);
    digitalWrite(servo, LOW);
    delayMicroseconds(22000 - pausa);
  }
  delay(1000);
}