# Sistema de Detección de Vibraciones con ESP32 y Google Sheets

Este repositorio contiene el código fuente de un **sistema de monitoreo de vibraciones** basado en el **sensor SW-420** y una **placa ESP32**.  
El sistema permite **detectar vibraciones físicas**, **enviar los datos a Google Sheets** mediante **HTTP requests**, y **visualizarlos en tiempo real** a través de **Blynk**.

---

## Contenido del repositorio

- **practica6_iot.ino** → Código principal para el ESP32, encargado de la lectura del sensor y la comunicación con Blynk y Google Sheets.  
- **google_app_script.js** → Script de **Google Apps Script** usado para recibir los datos enviados por el ESP32 y almacenarlos automáticamente en una hoja de cálculo.

---

## Tecnologías utilizadas

- ESP32  
- Sensor SW-420  
- Blynk IoT  
- Google Apps Script  
- Google Sheets  

---

## Funcionalidad general

1. El **sensor SW-420** detecta vibraciones y envía la señal al ESP32.  
2. El ESP32 procesa los datos y los envía a **Blynk** para su visualización.  
3. Los valores se almacenan en **Google Sheets** mediante una solicitud **HTTP GET** al script.  

---

## Objetivo

Desarrollar un sistema accesible y eficiente para **monitorear vibraciones físicas** y **registrar datos históricos** en la nube para su análisis posterior.
