#define __DEBUG__

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Definir constantes
#define ANCHO_PANTALLA 128  // ancho pantalla OLED
#define ALTO_PANTALLA 64    // alto pantalla OLED

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
  Serial.begin(9600);
  delay(100);
  Serial.println("Iniciando pantalla OLED");

  // Iniciar pantalla OLED en la dirección 0x3C
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
#ifdef __DEBUG__
    Serial.println("No se encuentra la pantalla OLED");
#endif
    while (true)
      ;
  }
  printText("Hola Mundo");
}

void loop() {}
