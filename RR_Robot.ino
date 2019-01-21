// Roberto de Figueiredo Minelli
// UGR - 2016
// SISTEMAS ROBÓTICOS INDUSTRIALES
// Cinemática inversa
// Modelo de Robot RR


#include <Servo.h>


double L1;        //  Geometria del robot
double L2;        //  Geometria del robot
double Px;        //  Punto Final X del Manipulador
double Py;        //  Punto Final Y del Manipulador
double M;         //  La distancia de Manipulador
double S2;
double ThetaR1;   // Resultado Theta 1
double ThetaR2;   // Resultado Theta 2
double Theta_1;
double Theta_2;
double c1;
double c2;


int Artic_1Pin = 10;  // Referencia usada para el servo - Articulación 1
int Artic_2Pin = 11;  // Referencia usada para el servo - Articulación 2
Servo Artic_1Servo;   // Referencia usada para el servo motor - Articulación 1
Servo Artic_2Servo;   // Referencia usada para el servo motor - Articulación 2



void cin_inversa(double Px, double Py){
    M = (Px*Px+Py*Py-L1*L1-L2*L2)/(2*L1*L2);
    S2 = sqrt(1-M*M);
    Theta_2 = atan2(S2,M);
    c1 = L1+L2*M;
    c2 = L2*S2;
    Theta_1 = atan2(Py,Px)-atan2(c2,c1);
    
    ThetaR1 = (180/M_PI) * Theta_1;
    ThetaR2 = (180/M_PI) * Theta_2;

}

// Ejecutando
void setup()
{  
   // Prepárese para escribir en los servos
   pinMode(Artic_1Pin, OUTPUT);
   pinMode(Artic_2Pin, OUTPUT);
   
   // Dónde están conectados los servos
   Artic_1Servo.attach(Artic_1Pin);
   Artic_2Servo.attach(Artic_2Pin);
   
   // Iniciar la comunicación a través del puerto serie (USB) para supervisar la salida
   Serial.begin(9600);
   
   // Geometria del robot
   L1 = 100;
   L2 = 50;
   
   // Punto Final
   Px = 0;
   Py = 150; 
   
   // Calcular la cinematica inversa
   cin_inversa(Px,Py); 

   //Imprimir los valores de salida
   Serial.println("Grado de la Articulacion 1 : ");
   Serial.print(ThetaR1); 
   Serial.println(" Grados");
   Serial.println("Grado de la Articulacion 2 : "); 
   Serial.print(ThetaR2);
   Serial.println(" Grados");
  
  //Escribe un valor en el servo en grados
   Artic_1Servo.write(ThetaR1);
   Artic_2Servo.write(ThetaR2);

}

// function which runs over and over forever
void loop(){
  

}
