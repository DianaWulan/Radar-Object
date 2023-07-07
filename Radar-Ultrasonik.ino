//library
#include <Servo.h>
#include <HCSR04.h> 

//buat sebuah objek untuk servo
Servo myservo;

// Ultrasonik
//ultrasonik pin D5 sebagai Trig dan D6 sebagai Echo
HCSR04 hc(D5,D6);

int Buzzer = D3;
int led = D4;

// variable
float jarak; 

//setup
void setup() {
  Serial.begin(115200); 
  myservo.attach(D2);
  pinMode (Buzzer, OUTPUT);
  pinMode (led, OUTPUT);

  //koneksi ke wifi
  //masukan (NamaWifi, password)
  WiFi.begin("", "");
  //uji apakah wifi terkonek
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println("Wifi terkoneksi");
}

//pebacaan sensor ultrasonik
void ultrasonik(){
  jarak = hc.dist(); //Memasukkan pembacaan sensor ke variabel jarak
  //jarak < 10 = led dan buzzer menyala
  if(jarak < 10){
    digitalWrite(led, HIGH);
    digitalWrite(Buzzer,HIGH); 
    delay(100); 
  //jarak < 10 = led dan buzzer mati
  }else if(jarak >= 10){
    digitalWrite(led, LOW);
    digitalWrite(Buzzer,LOW); 
    delay(100); 
  }
  Serial.print("Jarak(cm): ");
  Serial.println(jarak);

  Blynk.virtualWrite(V5, jarak);
}

void gerakanServo(){
  //servo
  int pos;
  //servo berputar ke kiri (0-180), pos = posisi derajat
  for (pos = 0; pos <= 180; pos += 1) { 
    myservo.write(pos);              
    ultrasonik(); //baca ultrasonik
    delay(1000); //delay gerakan servo 1 detik                      
  }
  //servo berputar ke kanan (180-0)
  for (pos = 180; pos >= 0; pos -= 1) { 
    myservo.write(pos);              
    ultrasonik();//baca ultrasonik
    delay(1000); //delay gerakan servo 1 detik                         
  }
  ultrasonik();//baca ultrasonik
}

//loop
void loop() {
  //jalankan servo
  gerakanServo();
}
