#include "notas.h" 

int pin_resistencia = 0;
int pin_bocina = 3;
byte opcion = 0;
boolean encendido = false;
int tono;
int min_f = LA4;
int max_f = LA7;

void setup() {
  pinMode(pin_bocina, OUTPUT);
  Serial.begin(9600);  
  instrucciones();
}

void loop() {
  if (Serial.available() > 0) {
    opcion = Serial.read();
    switch (opcion) {
      case '0':
        encendido = false;
        noTone(pin_bocina);
        Serial.println("Bocina apagada.");
        break;
      case '1':
        encendido = true;
        Serial.println("Bocina encendida.");
        break;
      case '2':
        cambiar_tonos();
        break;
      case '3':
        instrucciones();
        break;
      default:
        Serial.println("Esa opción no es válida.");
    }
  }
  if (encendido) {
    tono = map (analogRead(pin_resistencia), 0, 1023, min_f, max_f);
    tone(pin_bocina, tono);
  }

}

void instrucciones() {
  Serial.println("\nINSTRUCCIONES:");
  Serial.println("Teclea el número que corresponda a la acción que deseas realizar:");
  Serial.println("\t0: para apagar la bocina.");
  Serial.println("\t1: para prender la bocina.");
  Serial.println("\t2: para cambiar el rango de la escala.");
  Serial.println("\t3: para mostrar de nuevo las instrucciones");
}

void cambiar_tonos() {
  Serial.println("NOTA: Debes ingresar las notas en la siguiente notación: ");
  Serial.println("La mayor en la 4a octava = LA4");
  Serial.println("Do sostenido en la 2a octava = DOS2");  
  Serial.println("Ingresa la nota más baja: ");
}

