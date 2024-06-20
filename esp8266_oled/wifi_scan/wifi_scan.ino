#include <ESP8266WiFi.h>

#define __DEBUG__

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Definir constantes
#define ANCHO_PANTALLA 128  // ancho pantalla OLED
#define ALTO_PANTALLA 64    // alto pantalla OLED
#define SCL 12
#define SDA 14

// Objeto de la clase Adafruit_SSD1306
Adafruit_SSD1306 display(ANCHO_PANTALLA, ALTO_PANTALLA, &Wire, -1);

void printText(String text, int size = 2, int color = SSD1306_WHITE) {
  // Limpiar buffer
  display.clearDisplay();

  // Tamaño del texto
  display.setTextSize(size);
  // Color del texto
  display.setTextColor(color);
  // Posición del texto
  display.setCursor(0, 25);
  // Escribir texto
  display.println(text);

  // Enviar a pantalla
  display.display();
}

void setup() {
  Serial.begin(115200);  // Inicia la comunicación serial a 115200 baudios
  Wire.begin(SDA, SCL);
  WiFi.mode(WIFI_STA);  // Configura el ESP8266 como cliente
  WiFi.disconnect();    // Desconecta cualquier conexión WiFi previa
  delay(100);

  Serial.println("Iniciando pantalla OLED");

  // Iniciar pantalla OLED en la dirección 0x3C
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
#ifdef __DEBUG__
    Serial.println("No se encuentra la pantalla OLED");
#endif
    for (;;)
      ;
  }
  Serial.println("Iniciando escaneo de redes WiFi...");
}

void loop() {
  int numberOfNetworks = WiFi.scanNetworks();  // Escanea las redes WiFi disponibles

  if (numberOfNetworks == 0) {
    Serial.println("No se encontraron redes WiFi");
  } else {
    Serial.printf("Se encontraron %d redes WiFi:\n", numberOfNetworks);
    for (int i = 0; i < numberOfNetworks; i++) {
      printText(WiFi.SSID(i).c_str());
      Serial.printf("Red %d: %s (RSSI: %d) Canal: %d %s\n",
                    i + 1,
                    WiFi.SSID(i).c_str(),
                    WiFi.RSSI(i),
                    WiFi.channel(i),
                    WiFi.encryptionType(i) == ENC_TYPE_NONE ? "Abierta" : "Cifrada");
      delay(1000);
    }
  }

  Serial.println("");
  //delay(10000);  // Espera 10 segundos antes de escanear nuevamente
}
