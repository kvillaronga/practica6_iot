Sistema de Detección de Vibraciones con ESP32 y Blynk IoT

Este repositorio contiene el código fuente del proyecto "Sistema de Detección de Vibraciones", desarrollado con un ESP32, un sensor SW-420, y la plataforma Blynk IoT.
El sistema detecta vibraciones físicas, activa alertas visuales y sonoras, y registra los eventos en una hoja de cálculo de Google Sheets mediante un Webhook HTTP y un Google Apps Script.

Archivos del repositorio

esp32_vibraciones.ino → Código principal del ESP32.

google_app_script.js → Script de Google Apps Script que recibe los datos enviados desde Blynk y los guarda en la hoja de cálculo.

Funcionalidad general

El sensor SW-420 detecta una vibración y envía una señal digital al ESP32.

El microcontrolador activa el LED y el buzzer si están habilitados desde la app.

Los datos se envían a Blynk IoT y se registran automáticamente en Google Sheets.
