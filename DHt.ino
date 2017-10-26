void setup() {            //This function gets called when the Arduino starts
  Serial.begin(9600);   //This code sets up the Serial port at 115200 baud rate
}
 
void loop() {             //This function loops while the arduino is powered
  int val;                
  val=analogRead(0);      
  Serial.println(val);    
  delay(1000);            
}
