int pin_resistencia_l = 0;
int pin_resistencia_r = 1;
int pin_bocina_l = 3;
int pin_bocina_r = 5;
byte opcion = 0;
boolean encendido = false;
int tono_l;
int tono_r;
int min_f_l = 0;
int max_f_l = 2000;
int min_f_r = 2000;
int max_f_r = 4000;

void setup() {
  pinMode(pin_bocina_l, OUTPUT);
  pinMode(pin_bocina_r, OUTPUT);
  Serial.begin(9600);
  Serial.println("\t\tINSTRUMENTO THEREMÍN");
  Serial.println("Hecho por Alan Castillo Montes y Daniel Vargas Castro");
  Serial.println("como proyecto final para el laboratorio de microcomputadoras.");
  Serial.println("Facultad de Ingeniería, UNAM. Semestre 2017-2.");
  instrucciones();
}

void loop() {
  if (Serial.available() > 0) {
    opcion = Serial.read();
    switch (opcion) {
      case '0':
        encendido = false;
        noTone(pin_bocina_l);
        noTone(pin_bocina_r);
        Serial.println("Bocinas apagadas.");
        break;
      case '1':
        encendido = true;
        Serial.println("Bocinas encendidas.");
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
    tono_l = map (analogRead(pin_resistencia_l), 0, 1023, min_f_l, max_f_l);
    tono_r = map (analogRead(pin_resistencia_r), 0, 1023, min_f_r, max_f_r);
    tone(pin_bocina_l, tono_l);
    delay(8);
    noTone(pin_bocina_l);
    tone(pin_bocina_r, tono_r);
    delay(8);
    noTone(pin_bocina_r);
  }

}

void instrucciones() {
  Serial.println("\nINSTRUCCIONES:");
  Serial.println("Teclea el número que corresponda a la acción que deseas realizar:");
  Serial.println("\t0: para apagar las bocinas.");
  Serial.println("\t1: para prender las bocinas.");
  Serial.println("\t2: para establecer el rango de tonos.");
  Serial.println("\t3: para mostrar de nuevo las instrucciones.");
  Serial.println("Utiliza las perillas para controlar el volumen de cada bocina.");
}

void cambiar_tonos() {
  Serial.println("NOTA: Consulta el archivo 'notas.h' para ver cada nota y su frecuencia.");
  Serial.println("NOTA: Escribe ',' al final de cada valor ingresado.");
  Serial.println("Configurando bocina izquierda...");
  Serial.print("\tIngresa la frecuencia más baja: ");
  min_f_l = leerTono();
  Serial.print("\tIngresa la frecuencia más alta: ");
  max_f_l = leerTono();
  Serial.println("Configurando bocina derecha...");
  Serial.print("\tIngresa la frecuencia más baja: ");
  min_f_r = leerTono();
  Serial.print("\tIngresa la frecuencia más alta: ");
  max_f_r = leerTono();
  instrucciones();
}

int leerTono(){
  int charCatcher=0;
  String inputStr="";
  while (charCatcher != ',') {
    if (Serial.available() > 0) {
      charCatcher = Serial.read();
      inputStr += (char)charCatcher;
    }
  }
  inputStr.remove(inputStr.length()-1);
  charCatcher = (int)round(inputStr.toFloat());
  Serial.println(charCatcher);
  inputStr = "";
  
  return charCatcher;
}

