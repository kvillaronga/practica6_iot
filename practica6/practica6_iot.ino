// --- Datos del proyecto en Blynk ---
#define BLYNK_TEMPLATE_ID "TMPL2bDABVplu"
#define BLYNK_TEMPLATE_NAME "Practica5"
#define BLYNK_AUTH_TOKEN "KJHVAAsm0L35E6YxiPLvJNDa_u8xmJlO"

// --- Librerías para WiFi, Blynk y HTTP ---
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <HTTPClient.h>  // Para enviar datos al webhook de Google

// --- Credenciales WiFi ---
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "iPhone de Shadows";
char pass[] = "123456789";

// --- Pines físicos ---
#define SW420_PIN 23
#define LED_PIN 18
#define BUZZER_PIN 19

// --- Pines virtuales en Blynk ---
#define VIRTUAL_SW420 V0
#define VIRTUAL_LED V1
#define VIRTUAL_BUZZER V2
#define VIRTUAL_CONTADOR V3   // Contador de vibraciones

// --- Variables de estado ---
bool ledActivo = false;
bool buzzerActivo = false;
bool vibracionDetectada = false;
int contadorVibraciones = 0;

// --- URL del Webhook (Google Apps Script) ---
const char* webhookURL = "https://script.google.com/macros/s/AKfycbz9I2ZR1swnE_GDSLydxqXD8zeNOyJA9hZUn-w5SzFXRWpvauFPWjrP9viWsYpQogci/exec";

// --- Función para enviar los datos al Google Sheets ---
void enviarGoogleSheets(String mensaje) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(webhookURL) + "?vibraciones=" + mensaje;
    http.begin(url);
    int httpResponseCode = http.GET();
    Serial.println(url);

    if (httpResponseCode > 0) {
      Serial.print("Datos enviados a Google Sheets. Respuesta: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Error al enviar datos. Código: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("WiFi desconectado. No se pudo enviar a Google Sheets.");
  }
}

// --- Función para enviar notificación push en Blynk ---
void enviarNotificacion() {
  Blynk.logEvent("vibracion_detectada", "¡Se detectó una vibración!");
}

// --- Lectura del estado del LED desde la app ---
BLYNK_WRITE(VIRTUAL_LED) {
  ledActivo = param.asInt();
  Serial.println(ledActivo ? "LED activado desde app" : "LED desactivado desde app");
}

// --- Lectura del estado del buzzer desde la app ---
BLYNK_WRITE(VIRTUAL_BUZZER) {
  buzzerActivo = param.asInt();
  Serial.println(buzzerActivo ? "Buzzer activado desde app" : "Buzzer desactivado desde app");
}

void setup() {
  Serial.begin(115200);

  pinMode(SW420_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  Serial.println("Conectando a WiFi...");
  WiFi.begin(ssid, pass);
  int intentos = 0;
  while (WiFi.status() != WL_CONNECTED && intentos < 20) {
    delay(500);
    Serial.print(".");
    intentos++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi conectado correctamente.");
    Serial.print("IP local: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nError: no se pudo conectar al WiFi.");
  }

  Serial.println("Conectando a Blynk...");
  Blynk.begin(auth, ssid, pass);
  Serial.println("Conectado a Blynk exitosamente.");

  // Sincronizar estados iniciales
  Blynk.syncVirtual(VIRTUAL_LED);
  Blynk.syncVirtual(VIRTUAL_BUZZER);
}

void loop() {
  Blynk.run();

  int valorSW420 = digitalRead(SW420_PIN);
  Blynk.virtualWrite(VIRTUAL_SW420, valorSW420);
  
  delay(200);

  if (valorSW420 == HIGH) {
    if (!vibracionDetectada) {
      vibracionDetectada = true;
      contadorVibraciones++;
      Blynk.virtualWrite(VIRTUAL_CONTADOR, contadorVibraciones);

      Serial.println("-----");
      Serial.print("Vibración detectada. Total: ");
      Serial.println(contadorVibraciones);

      String mensaje = "detectada";
      enviarGoogleSheets(mensaje);   // Guarda en Sheets con texto descriptivo
      enviarNotificacion();          // Envía la notificación push
    }

    if (ledActivo) digitalWrite(LED_PIN, HIGH);
    if (buzzerActivo) digitalWrite(BUZZER_PIN, HIGH);

  } else {
    if (vibracionDetectada) {
      vibracionDetectada = false;
      Serial.println("Sin vibración...");

      String mensaje = "no_detectada";
      enviarGoogleSheets(mensaje);   // También envía a Sheets el estado actual
    }

    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }

}
