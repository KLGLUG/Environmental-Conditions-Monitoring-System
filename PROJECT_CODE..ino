#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "vivo 1713";
const char* password = "rstgbg7842";
const char* mqtt_server = "192.168.43.153";  
const char* clientID = "esp8266";
const char* outTopic = "output";

char ldr[20];
float Temp;
float R1=10000,R2;
float logR2 ;
float c1=1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
int gate=D0; 
volatile unsigned long duration=0;
unsigned char i[5];
unsigned int j[40];
unsigned char value=0;
unsigned answer=0;
int z=0;
int b=1;



 WiFiClient espClient;
PubSubClient client(espClient);



void setup_wifi() {
 delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
   delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() 
{
  Serial.begin(115200);
  setup_wifi();
 client.setServer(mqtt_server, 1883);
 pinMode(D2,OUTPUT);
pinMode(D3,OUTPUT);
pinMode(D4,OUTPUT);
Serial.begin(9600);
  // put your setup code here, to run once:

}
void reconnect() {
  while (!client.connected())
 {
    Serial.print("Attempting MQTT connection...");
     if (client.connect(clientID)) {
      Serial.println("connected");
     //  client.publish(outTopic, clientID);
     
    }
 else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
} 

void loop() 
{
  if (!client.connected())
  {
    reconnect();
  } 

  publishldr();
  publishsensorvoltage();
  publishTemp();

}

void publishldr()
{ 
  String d="";
  digitalWrite(D2,HIGH);
  digitalWrite(D3,LOW);
  digitalWrite(D4,LOW);
 int l = analogRead(A0);
 d=d+"light intensity " +String(l);
 int z=d.length() + 1;
 d.toCharArray(ldr,z);
 Serial.print("");
  Serial.println(ldr);
  client.publish(outTopic,ldr);
  delay(1000);
}

void publishTemp()
{
  digitalWrite(D2,LOW);
  digitalWrite(D3,HIGH);
  
  digitalWrite(D4,LOW);
  String te = ""; 
  int Vo = analogRead(A0);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  Temp = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
Temp = Temp - 273.15;
  Temp = ((Temp * 5.0)/ 9.0 - 70.0); 
  te=te+"temperature " + String (Temp);
  char charBuf[50]; 
  
 float y=te.length() +1;
  String(te).toCharArray(charBuf,y);
    Serial.print("Temperature= ");
  Serial.println(Temp);
  client.publish (outTopic,charBuf);
}


  void publishsensorvoltage()
  {
    digitalWrite(D2,LOW);
  digitalWrite(D3,LOW);
  digitalWrite(D4,HIGH); 
  float sensorValue;
  
  sensorValue = analogRead(A0);
float   sensorVoltage = sensorValue/1024*5.0;
   String se="";
  se=se+"pollutant gas  equivalent voltage values "+ String ( sensorVoltage);
  float x= se.length()+1;
  char charbuf1[50];
  String(se).toCharArray(charbuf1,x);
  Serial.print("sensor voltage = ");
  Serial.print(sensorVoltage);
  Serial.println(" V");
   delay(1000);
  client.publish (outTopic,charbuf1);
  }
  
  
  // put your main code here, to run repeatedly:


