#include <TimerOne.h>
#include <LiquidCrystal.h>

//pines LCD
int v0 = 3;
int rs = 4;
int e = 5;
int d4 = 6;
int d5 = 7;
int d6 = 8;
int d7 = 9;
//LCD
LiquidCrystal lcd (rs, e, d4, d5, d6, d7);

//Servomotor
int servo = 11;
float pausa;

//Melodias
long DO = 523.25, FA = 698.46; //frecuencia de notas
long alarma[] = {DO, FA, DO, FA, DO, FA, DO, FA, DO, FA}; //alarma
long alarma_vacio[] = {DO, DO, DO, DO, DO, DO, DO, DO, DO, DO}; //alarma vacio
long d = 1000;
long duracion_alarma[] = {d, d, d, d, d, d, d, d, d, d};

//pines pulsadores, buzzer y led
const int pulsador_modo = 12;
const int pulsador_incrementar = 13;
const int buzzer = 2;
const int led_verde = 10;

int contador_dias = 0;
int horas = 0;
int minutos = 0;
volatile int segundos = 0;
volatile boolean actualizar = true;

int horas_alarma = 0;
int minutos_alarma = 0;
boolean alarma_on = false;
char texto[10];
int modo = 0;
const int n_modos = 6;

/*
    modos posibles:
    0: modo normal
    1: cambiar hora reloj
    2: cambiar minutos reloj
    3: cambiar hora alarma
    4: cambiar minutos alarma
    5: cambiar ON/OFF alarma
*/
void setup() {
  pinMode(servo, OUTPUT);
  analogWrite(v0, 10);
  lcd.begin(16, 2);
  lcd.clear();
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

  if (actualizar == true) { //actualizar hace que el reloj se actualice cada segundo
    actualizarReloj();
    lcd.clear();
    lcd.noBlink();
    //RELOJ
    lcd.setCursor(0, 0);
    sprintf(texto, "%02d:%02d:%02d", horas, minutos, segundos);
    lcd.print(texto);
    //ALARMA
    lcd.setCursor(0, 1);
    sprintf(texto, "%02d:%02d", horas_alarma, minutos_alarma);
    lcd.print(texto);
    //alarma encendida
    if (alarma_on == true) {
      if (segundos == 0 && horas == horas_alarma && minutos == minutos_alarma && contador_dias != 7) {
        contador_dias += 1;
        girarServo(45);
        for (int nota_actual = 0; nota_actual < 10; nota_actual++) {
          digitalWrite(led_azul, HIGH);
          tone(buzzer, alarma[nota_actual]);
          delay(duracion_alarma[nota_actual]);
          noTone(buzzer);
          digitalWrite(led_azul, LOW);
        }
      } else if (segundos == 0 && horas == horas_alarma && minutos == minutos_alarma && contador_dias == 7) {
        //han transcurrido 7 dias, alarma diferente para indicar que el dispensador esta vacio
        contador_dias = 0;
        girarServo(45);
        for (int nota_actual = 0; nota_actual < 10; nota_actual++) {
          tone(buzzer, alarma_vacio[nota_actual]);
          delay(duracion_alarma[nota_actual]);
          noTone(buzzer);
        }
        for (int n = 0; n < 10; n++) {
          digitalWrite(led_azul, HIGH);
          delay(1000);
          digitalWrite(led_azul, LOW);
          delay(1000);
        }
      }
      lcd.print(" ON");
    } else {
      lcd.print(" OFF");
    }
    actualizar = false; //esta línea permite que sea controladorTiempo() quien actualice el reloj cada segundo
    fijarCursorModo();
  }
}
/*** metodos ***/
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
  horas ++;
  horas = horas % 24;
  actualizar = true;
}
void incrementarHorasAlarma() {
  horas_alarma++;
  horas_alarma = horas_alarma % 24;
  actualizar = true;
}
void incrementarMinutosAlarma() {
  minutos_alarma ++;
  minutos_alarma = minutos_alarma % 60;
  actualizar = true;
}
void incrementarMinutos() {
  minutos ++;
  minutos = minutos % 60;
  actualizar = true;
}
void fijarCursorModo() {
  switch (modo) {
    case 0:
      lcd.noBlink();
      break;
    case 1:
      lcd.setCursor(0, 0); //situa el cursor en las horas del reloj
      lcd.blink();
      break;
    case 2:
      lcd.setCursor(3, 0); //situa el cursor en los minutos del reloj
      lcd.blink();
      break;
    case 3:
      lcd.setCursor(0, 1); //situa el cursor en las horas de la alarma
      lcd.blink();
      break;
    case 4:
      lcd.setCursor(3, 1); //situa el cursor en los minutos de la alarma
      lcd.blink();
      break;
    case 5:
      lcd.setCursor(6, 1); //situa el cursor en ON/OFF de la alarma
      lcd.blink();
      break;
  }
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
/*** fin metodos ***/