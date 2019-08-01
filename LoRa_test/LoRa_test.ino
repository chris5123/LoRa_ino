void setup(){
    Serial.begin(9600);
    delay(1000);

    Serial.print("AT\r\n");
    delay(20);

//    Serial.println("AT+IPR=9600");
//    delay(20);

//    Serial.print("AT+PARAMETER=10,7,1,7\r\n");
//    delay(20);

    Serial.print("AT+PARAMETER=12,3,1,7\r\n");
    delay(20);

    Serial.print("AT+BAND=89600000\r\n");
    delay(20);

    Serial.print("AT+ADDRESS=1\r\n");
    delay(20);

    Serial.print("AT+NETWORKID=6\r\n");
    delay(20);

    Serial.print("AT+PARAMETER?\r\n");
    delay(20);

    Serial.print("AT+BAND?\r\n");
    delay(20);

    Serial.print("AT+NETWORKID?\r\n");
    delay(20);

    Serial.print("AT+ADDRESS?\r\n");
    delay(20);
}
void loop(){
    String x = "AT+SEND=2,1,H\r\n";
    Serial.print(x);
    delay(30);
    Serial.print("AT+SEND?\r\n");
//    Serial.read();
    Serial.print("AT+SEND=2,1,L\r\n");
    delay(30);
}
