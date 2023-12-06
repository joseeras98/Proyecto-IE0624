# Proyecto-IE0624
Reporsitorio para el proyecto del curso IE-0624

markdown
Copy code
# Dispensador de Pastillas con Microcontroladores

Este proyecto implementa un dispensador de pastillas utilizando el microcontrolador Arduino UNO. El código está diseñado para funcionar con un Arduino y utiliza diversas funciones para controlar la dispensación de pastillas, configurar la alarma y gestionar el tiempo.

## Configuración Inicial

La configuración utilizada es la siguiente:

1. **Conexiones de Hardware:**
   - Conectar el servo al pin 11.
   - Conectar el pulsador de modo al pin 12.
   - Conectar el pulsador de incremento al pin 13.
   - Conectar el buzzer al pin 2.
   - Conectar el LED azul al pin 10.

2. **Librerías Necesarias:**
   - La librería TimerOne, que se utiliza para gestionar interrupciones de temporizador.

## Uso del Dispensador de Pastillas

El programa principal (\texttt{loop()}) controla el dispensador de pastillas y realiza las siguientes acciones según el modo actual:
- **Modo 0**: Modo Default.
- **Modo 1 (Incrementar Horas):** Incrementa las horas del reloj.
- **Modo 2 (Incrementar Minutos):** Incrementa los minutos del reloj.
- **Modo 3 (Incrementar Horas de Alarma):** Incrementa las horas de la alarma.
- **Modo 4 (Incrementar Minutos de Alarma):** Incrementa los minutos de la alarma.
- **Modo 5 (Alternar Alarma):** Alterna el estado de la alarma (encendido/apagado).

El dispensador de pastillas dispensará pastillas y activará el buzzer cuando la alarma esté configurada y se alcance la hora y minutos programados.

## Funciones Adicionales

- **\texttt{controladorTiempo}:** Actualiza el tiempo cada segundo mediante un temporizador.
- **\texttt{actualizarReloj}:** Actualiza las horas y minutos del reloj.
- **\texttt{incrementarHoras, incrementarMinutos, incrementarHorasAlarma, incrementarMinutosAlarma}:** Incrementan las horas o minutos según el modo.
- **\texttt{girarServo}:** Controla el servo para dispensar pastillas.



## Licencia
NA
