#include <TinyGPS.h>

#include <TinyGPS.h>

#include <SoftwareSerial.h>

#include <TinyGPS.h>

/* This sample code demonstrates the normal use of a TinyGPS object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/

TinyGPS gps;
SoftwareSerial ss(4, 3);

static void smartdelay(unsigned long ms);
static void print_float(float val, float invalid, int len, int prec);
static void print_int(unsigned long val, unsigned long invalid, int len);
static void print_date(TinyGPS &gps);
static void print_str(const char *str, int len);
String s = " ";
void setup()
{
  
  
//  Serial.print("Testing TinyGPS library v. "); Serial.println(TinyGPS::library_version());
//  Serial.println("by Mikal Hart");
//  Serial.println();
//  Serial.println("Sats HDOP Latitude  Longitude  Fix  Date       Time     Date Alt    Course Speed Card  Distance Course Card  Chars Sentences Checksum");
//  Serial.println("          (deg)     (deg)      Age                      Age  (m)    --- from GPS ----  ---- to London  ----  RX    RX        Fail");
//  Serial.println("-------------------------------------------------------------------------------------------------------------------------------------");
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
    ss.begin(9600);
}

void loop()
{
  float flat, flon;
  unsigned long age, date, time, chars = 0;
  unsigned short sentences = 0, failed = 0;
  static const double LONDON_LAT = 51.508131, LONDON_LON = -0.128002;
  
//  print_int(gps.satellites(), TinyGPS::GPS_INVALID_SATELLITES, 5);
//  print_int(gps.hdop(), TinyGPS::GPS_INVALID_HDOP, 5);
  gps.f_get_position(&flat, &flon, &age);
//  print_float(flat, TinyGPS::GPS_INVALID_F_ANGLE, 10, 6);
//  print_float(flon, TinyGPS::GPS_INVALID_F_ANGLE, 11, 6);
//  print_int(age, TinyGPS::GPS_INVALID_AGE, 5);
//  print_date(gps);
//  print_float(gps.f_altitude(), TinyGPS::GPS_INVALID_F_ALTITUDE, 7, 2);
//  print_float(gps.f_course(), TinyGPS::GPS_INVALID_F_ANGLE, 7, 2);
//  print_float(gps.f_speed_kmph(), TinyGPS::GPS_INVALID_F_SPEED, 6, 2);
//  print_str(gps.f_course() == TinyGPS::GPS_INVALID_F_ANGLE ? "*** " : TinyGPS::cardinal(gps.f_course()), 6);
//  print_int(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0xFFFFFFFF : (unsigned long)TinyGPS::distance_between(flat, flon, LONDON_LAT, LONDON_LON) / 1000, 0xFFFFFFFF, 9);
//  print_float(flat == TinyGPS::GPS_INVALID_F_ANGLE ? TinyGPS::GPS_INVALID_F_ANGLE : TinyGPS::course_to(flat, flon, LONDON_LAT, LONDON_LON), TinyGPS::GPS_INVALID_F_ANGLE, 7, 2);
//  print_str(flat == TinyGPS::GPS_INVALID_F_ANGLE ? "*** " : TinyGPS::cardinal(TinyGPS::course_to(flat, flon, LONDON_LAT, LONDON_LON)), 6);

  gps.stats(&chars, &sentences, &failed);
//  print_int(chars, 0xFFFFFFFF, 6);
//  print_int(sentences, 0xFFFFFFFF, 10);
//  print_int(failed, 0xFFFFFFFF, 9);
//  Serial.println();
  
  smartdelay(1000);
  Serial.print("AT+SEND=2,36,");
  Serial.print("v0:");
  Serial.print(flat,DEC);
//  delay(200);
//   if(Serial.available() > 0)
//    {
//        char c = Serial.read();
//        if(c != '\n')
//        {
//            s += c;
//        }
//        else
//        {
//            Serial.println(s);   
//        }
//    }
//  delay(200);
//  Serial.print("AT+SEND=2,18,");
  Serial.print("v1:");
  Serial.println(flon,DEC);
  delay(1200);
  //Serial.print("AT+SEND=2,15,");
  //Serial.println(age, DEC);
  delay(30);
  
  Serial.print("AT+SEND?\r\n");
  delay(100);
   if(Serial.available() > 0)
    {
        char c = Serial.read();
        if(c != '\n')
        {
            s += c;
        }
        else
        {
            Serial.println(s);   
        }
    }
//  Serial.print("AT+SEND=2,1,L\r\n");
  delay(100);
//  smartdelay(500);
}

static void smartdelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}

static void print_float(float val, float invalid, int len, int prec)
{
  if (val == invalid)
  {
    while (len-- > 1)
      Serial.print('*');
    Serial.print(' ');
  }
  else
  {
    Serial.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
      Serial.print(' ');
  }
  smartdelay(0);
}

static void print_int(unsigned long val, unsigned long invalid, int len)
{
  char sz[32];
  if (val == invalid)
    strcpy(sz, "*******");
  else
    sprintf(sz, "%ld", val);
  sz[len] = 0;
  for (int i=strlen(sz); i<len; ++i)
    sz[i] = ' ';
  if (len > 0) 
    sz[len-1] = ' ';
  Serial.print(sz);
  smartdelay(0);
}

static void print_date(TinyGPS &gps)
{
  int year;
  byte month, day, hour, minute, second, hundredths;
  unsigned long age;
  gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
  if (age == TinyGPS::GPS_INVALID_AGE)
    Serial.print("********** ******** ");
  else
  {
    char sz[32];
    sprintf(sz, "%02d/%02d/%02d %02d:%02d:%02d ",
        month, day, year, hour, minute, second);
    Serial.print(sz);
  }
  print_int(age, TinyGPS::GPS_INVALID_AGE, 5);
  smartdelay(0);
}

static void print_str(const char *str, int len)
{
  int slen = strlen(str);
  for (int i=0; i<len; ++i)
    Serial.print(i<slen ? str[i] : ' ');
  smartdelay(0);
}
