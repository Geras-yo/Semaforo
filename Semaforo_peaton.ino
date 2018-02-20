/*Castillo Hernandez Gerardo
 *Sistemas programables 
*/

// Definición de pines
const int auto_verde = 8;
const int auto_amarillo = 9;
const int auto_rojo = 10;
const int peaton_verde = 11;
const int peaton_rojo = 12;
const int pin_pulsador = 13;
const int tiempo_minimo_verde_auto = 12000;// Tiempo mínimo que permanecerá en verde el semáforo para automóviles
 
// Inicializa semáforo. Verde para automóviles, rojo para peatones
void semaforo_ini(void) {
   digitalWrite(auto_verde, HIGH);
   digitalWrite(auto_rojo, LOW);
   digitalWrite(auto_amarillo, LOW);
   digitalWrite(peaton_rojo, HIGH);
   digitalWrite(peaton_verde, LOW);
}
 
// Inicialización del programa
void setup() {
   // Define las salidas de Arduino
   pinMode(auto_verde, OUTPUT);
   pinMode(auto_amarillo, OUTPUT);
   pinMode(auto_rojo, OUTPUT);
   pinMode(peaton_verde, OUTPUT);
   pinMode(peaton_rojo, OUTPUT);
 
   // Define las entradas con resistencia de Pull-up
   pinMode(pin_pulsador, INPUT_PULLUP);
   
   // Inicializa el puerto de comunicaciones
   Serial.begin(9600);
   Serial.println("Semaforo en marcha");
}
// hace una transicion para cambiar el semáforo de automóviles a rojo
void semaforo_auto_rojo(void) {
   
   
   digitalWrite(auto_verde,  LOW);// Apaga el led verde para coches
   for(int i=4; i>0; i--) {// Enciende el led ambar para coches y parpadea 3 veces
      delay(500);
      digitalWrite(auto_amarillo, HIGH);
      delay(500);
      digitalWrite(auto_amarillo, LOW);
   }
 
   
   digitalWrite(auto_rojo, HIGH);// Enciende el led rojo para coches
}
 
//  pulsador
void semaforo_pulsador(void) {
   int presionado;
   long time;
   
   // Espera a que se presione el pulsador
   time = millis() + tiempo_minimo_verde_auto; 
   presionado = 0;
   while(1) {
      // Lee el estado del pulsador
      if (digitalRead(pin_pulsador) == LOW)
         presionado = 1;
         
      // Si ha pasado el tiempo de verde para coches
      // y se ha presionado el pulsador, salir
      if ((millis() > time) && (presionado == 1))
         break;
   }
}
 
//Tiempo para el potenciómetro
void semaforo_espera(void) {
   int tiempo_peatones;
   
   // 2 segundos más el tiempo que añada el potenciómetro
   tiempo_peatones = 2000 + 5 * analogRead(A0);
   
   // Envía por el puerto serie el tiempo de espera
   Serial.print("Tiempo peatones=");
   Serial.println(tiempo_peatones);
 
   // Espera
   delay(tiempo_peatones);
}
 
// Cambia el semáforo de peatones a rojo
void semaforo_peatones_rojo(void) {
 
   // Parpadea el led verde 3 veces
   for(int i=3; i>0; i--) {
      digitalWrite(peaton_verde, LOW);
      delay(500);
      digitalWrite(peaton_verde, HIGH);
      delay(500);
   }
 
   // Enciende el led rojo para peatones y apaga el verde
   digitalWrite(peaton_verde, LOW);
   digitalWrite(peaton_rojo, HIGH);
}
 
// Programa principal
void loop() {
   
   semaforo_ini();//Verde para automóviles
   semaforo_pulsador();// Espera a que se presione el pulsador
   semaforo_auto_rojo();// Cambia el semáforo de automóviles a rojo

   delay(1500);// Espera antes de permitir paso a peatones
 
   // Enciende el led verde para peatones
   digitalWrite(peaton_rojo, LOW);
   digitalWrite(peaton_verde, HIGH);
 
   semaforo_espera();// Espera un tiempo que depende del potenciómetro

   semaforo_peatones_rojo();  // Cambia el semáforo de peatones a rojo
   delay(2000);// Espera antes de permitir el paso a los automóviles
}
 

