 /*
  
Ejemplo sobre uso de libreria ethernet 
para controlar un rele desde página web.
  
*/
  
#include <SPI.h>
#include <Ethernet.h>
#include "HX711.h"

#define DOUT  A1
#define CLK  A0
#define DOUT1 A3
#define CLK1 A2

HX711 balanza(DOUT, CLK);
HX711 balanza1(DOUT1, CLK1);
  
//Ponemos la dirección MAC e IP que queremos que use nuestro Arduino para conectarse al Router
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,1, 180);
  
String readString;
  
//Definimos que el puerto HTTP sera el 81
EthernetServer server2(80);
  
//Variables de control

int valorMandar;
  
void setup()
{
  //Iniciar la conexión de red y serie
  Ethernet.begin(mac, ip);
  server2.begin();
  Serial.begin(9600);
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(5,INPUT_PULLUP);
  pinMode(6,INPUT_PULLUP);

  Serial.begin(9600);
  Serial.print("Lectura del valor del ADC:  ");
  Serial.println(balanza.read());
  Serial.println("No ponga ningun  objeto sobre la balanza");
  Serial.println("Destarando...");
  Serial.println("...");
  balanza.set_scale(439430.25); // Establecemos la escala
  balanza.tare(20);  //El peso actual es considerado Tara.
  
  Serial.println("Listo para pesar");  

  
    Serial.print("Lectura del valor del ADC:  ");
  Serial.println(balanza1.read());
  Serial.println("No ponga ningun  objeto sobre la balanza");
  Serial.println("Destarando...");
  Serial.println("...");
  balanza1.set_scale(439430.25); // Establecemos la escala
  balanza1.tare(20);  //El peso actual es considerado Tara.
  
  Serial.println("Listo para pesar");  
}
  

  
void loop()
{

  
  // Esperamos que venga algún cliente web al puerto 81
  EthernetClient cliente = server2.available();
  if (cliente) {
    boolean currentLineIsBlank = true;
    while (cliente.connected()) {
      if (cliente.available()) {
        char c = cliente.read();
        if (readString.length() < 100) {
          //Almacenar caracteres en un string
          readString += c;
        }
     
        
          //Enviamos la cabecera web
          cliente.println("HTTP/1.1 200 OK");
          cliente.println("Content-Type: text/html");
          cliente.println();
  
            //Mostramos la web de control
            /*
            cliente.println("<center> <h5>Bienvenido al control de reles</h5> "); 
            cliente.println("<br> Clic en los enlace para encender o apagar:");            
            cliente.println("<br> <a href='./?activar'>Encender</a> - <a href='./?apagar'>Apagar</a>");            
            cliente.println(" </center>");             
            cliente.println("<br />");
            */
/*
            if (digitalRead(2)==LOW){
              //valorMandar=1;
              cliente.print("1,");
            }

              
            if (digitalRead(3)==LOW){
             // valorMandar=2;
             cliente.print("1,");
              }

               
            if (digitalRead(5)==LOW){
              //valorMandar=3;
              cliente.print("1,");
            }

                   
            if (digitalRead(6)==LOW){
              //valorMandar=4;
              cliente.print("1,");
            }
            ^*/

  Serial.print("Valor de lectura:  ");
  float valorLeido=balanza.get_value(10);

  int caidaCama=1;

  if (valorLeido>50000.00){
    caidaCama=0;
    }

    Serial.println(caidaCama);

                 
  Serial.print("Valor de lectura:  ");
  float valorLeido1=balanza1.get_value(10);

  int caidaCama1=1;

  if (valorLeido1>50000.00){
    caidaCama1=0;
    }

    Serial.println(caidaCama1);

            cliente.print(digitalRead(2));
            cliente.print("?");
             cliente.print(digitalRead(3));
            cliente.print("?");
             cliente.print(digitalRead(5));
            cliente.print("?");
             cliente.print(digitalRead(6));
             cliente.print("?");
             cliente.print (caidaCama);
             cliente.print("?");
             cliente.print(caidaCama1);
             
            
            
            
            //cliente.println(valorMandar);
            valorMandar=0;


            Serial.print (digitalRead(2));
            Serial.print (", ");
             Serial.print (digitalRead(3));
            Serial.print (", ");
             Serial.print (digitalRead(5));
            Serial.print (", ");
             Serial.println (digitalRead(6));
        
           
            
          break;
        }
          
      }
    }
    // Darle un respiro al navegador web para recibir los datos
    delay(1);
    //Limpiar String para proxima etición HTTP
    readString="";
    //Cerrar conexión
    cliente.stop();
  }
