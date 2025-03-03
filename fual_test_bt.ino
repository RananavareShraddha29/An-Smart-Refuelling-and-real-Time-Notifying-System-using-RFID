// Example sketch to read the ID from an Addicore 13.56MHz RFID tag
// as found in the RFID AddiKit found at:
// http://www.addicore.com/RFID-AddiKit-with-RC522-MIFARE-Module-RFID-Cards-p/126.htm

#include <AddicoreRFID.h>
#include <SPI.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h> // Library for using serial communication
//SoftwareSerial Serial1(2, 3); // Pins 7, 8 are used as used as software serial pins
LiquidCrystal lcd(8, 7, 6, 5, 4, A0);
#define PIN_RELAY_1  3
int I1 = A1;
int I2 = A2   ;
//String incomingData;   // for storing incoming serial data
//String message = "";   // A String for storing the message
#define  uchar unsigned char
#define uint  unsigned int
char input[12];
int count = 0;
uchar fifobytes;
uchar fifoValue;

AddicoreRFID myRFID; // create AddicoreRFID object to control the RFID module

/////////////////////////////////////////////////////////////////////
//set the pins
/////////////////////////////////////////////////////////////////////
const int chipSelectPin = 10;
const int NRSTPD = 5;

//Maximum length of the array
#define MAX_LEN 16
int a;
int p1 = 0, p2 = 0, p3 = 0, p4 = 0, val = 0;;
int c1 = 0, c2 = 0, c3 = 0, c4 = 0;

double total = 0;
int count_prod = 0;
int state;
int data;
int pet = 0;
int pet1 = 0;
int pet2 = 0;
int val1 = 0;
int rech = 0;
int flag = 0;
int flag1 = 0;
int flag2 = 0;
int flag3 = 0;
int totaldata = 200;
int totaldata1 = 500;
//int rech = 0;

void setup() {
  Serial.begin(9600);
  pinMode(I1, OUTPUT);
  pinMode(I2, OUTPUT);
  pinMode(PIN_RELAY_1, OUTPUT);
  //  Serial1.begin(9600); // baudrate for GSM shield
  // RFID reader SOUT pin connected to Serial RX pin at 9600bps
  // start the SPI library:
  //  lcd.clear();
  lcd.begin(16, 2);
  //    Wire.begin();
  //  Serial.begin(9600);
  //  lcd.setCursor(0, 0);
  //  lcd.print(" AUTOMATIC BILL");
  //  delay (2000);
  //  lcd.setCursor(0, 1);
  //  lcd.print(" SHOPPING CART ");
  //  delay (2000);
  //  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WELCOME TO");
  delay (2000);
  lcd.setCursor(2 , 1);
  lcd.print("BE Petrolium");
  delay (2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Plz Swap Card");
  SPI.begin();
  pinMode(chipSelectPin, OUTPUT);             // Set digital pin 10 as OUTPUT to connect it to the RFID /ENABLE pin
  digitalWrite(chipSelectPin, LOW);         // Activate the RFID reader
  pinMode(NRSTPD, OUTPUT);                    // Set digital pin 10 , Not Reset and Power-down
  digitalWrite(NRSTPD, HIGH);

  myRFID.AddicoreRFID_Init();
  pinMode(A4, INPUT_PULLUP);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  digitalWrite(PIN_RELAY_1, LOW);

 
}

void loop()
{

  while (Serial.available() > 0)
  {
    data = Serial.read();
    //    Serial.println(data);
    if (data == '1')
    {
      pet = 100;
      flag = 1;
      digitalWrite(PIN_RELAY_1, HIGH);
      delay(5000);
      digitalWrite(PIN_RELAY_1, LOW);
      Serial.println("Fuel Dispensing >>>");
    }
    else if (data == '2')
    {
      pet1 = 200;
      flag1 = 1;
      digitalWrite(PIN_RELAY_1, HIGH);
      delay(5000);
      digitalWrite(PIN_RELAY_1, LOW);
      Serial.println("Fuel Dispensing >>>");

    }
    else if (data == '3')
    {
      pet2 = 105;
      flag2 = 1;
      digitalWrite(PIN_RELAY_1, HIGH);
      delay(5000);
      digitalWrite(PIN_RELAY_1, LOW);
      Serial.println("Fuel Dispensing >>>");
    }
    else if (data == '4')
    {
      rech = 100;
      flag3 = 1;
    }
    else if (data == '6')
    {
      flag = 0;
      flag1 = 0;
      flag2 = 0;
      flag3 = 0;
      totaldata = 200;
      totaldata1 = 500;

    }
    //    delay(5);
  }
  
  
  int a = digitalRead(A4);
  //  Serial.print(a);
  uchar i, tmp, checksum1;
  uchar status;
  uchar str[MAX_LEN];
  uchar RC_size;
  uchar blockAddr;  //Selection operation block address 0 to 63
  String mynum = "";

  str[1] = 0x4400;
  //Find tags, return tag type
  status = myRFID.AddicoreRFID_Request(PICC_REQIDL, str);
  if (status == MI_OK)
  {
    //    Serial.println("RFID tag detected");
    //    Serial.print("Tag Type:\t\t");
    uint tagType = str[0] << 8;
    tagType = tagType + str[1];
    switch (tagType) {
      case 0x4400:
        //        Serial.println("Mifare UltraLight");
        break;
      case 0x400:
        //        Serial.println("Mifare One (S50)");
        break;
      case 0x200:
        //        Serial.println("Mifare One (S70)");
        break;
      case 0x800:
        //        Serial.println("Mifare Pro (X)");
        break;
      case 0x4403:
        //        Serial.println("Mifare DESFire");
        break;
      default:
        //        Serial.println("Unknown");
        break;
    }
  }

  //Anti-collision, return tag serial number 4 bytes
  status = myRFID.AddicoreRFID_Anticoll(str);
  if (status == MI_OK)
  {
    checksum1 = str[0] ^ str[1] ^ str[2] ^ str[3];
    

    if ((str[0] == 51) && (a == 1))
    { //You can change this to the first byte of your tag by finding the card's ID through the Serial Monitor
      lcd.setCursor(0, 0);
      lcd.print("Shraddha      ");
      Serial.println("Shraddha       ");
      lcd.setCursor(0, 1);
      lcd.print("TotalBAL: 200.00      ");
      Serial.println("Total BAL : 200.00      ");
      p2++;
    }
    if ((flag == 1) && (str[0] == 51) && (a == 1))
    {
      //      val++;
      //      Serial.println("Total itom");
      //      Serial.println(val);
      delay(2000);
      Serial.println("Petrol Rs : 100      ");
      //      total = totaldata;
      totaldata = totaldata - pet;
      count_prod--;
      lcd.clear();
      lcd.print("Total BAl :");
      Serial.println("Total BAl:");
      lcd.setCursor(0, 1);
      lcd.print(totaldata);
      Serial.println(totaldata);
    }
    if ((str[0] == 51) && (a == 1) && (flag1 == 1))
    {
      delay(2000);
      Serial.println("Petrol Rs : 200      ");
      //      total = 200;
      totaldata = totaldata - pet1;
      count_prod--;
      lcd.clear();
      lcd.print("Total BAl :");
      Serial.println("Total BAl:");
      lcd.setCursor(0, 1);
      lcd.print(totaldata);
      Serial.println(totaldata);
    }
    if ((str[0] == 51) && (a == 1) && (flag2 == 1))
    {
      delay(2000);
      Serial.println("Petrol Rs : 105      ");
      //      total = 200;
      totaldata = totaldata - pet2;
      count_prod--;
      lcd.clear();
      lcd.print("Total BAl : ");
      Serial.println("Total BAl: ");
      lcd.setCursor(0, 1);
      lcd.print(totaldata);
      Serial.println(totaldata);
    }

    if ((str[0] == 51) && (a == 0) && (flag3 == 1))
    {
      flag = 0;
      flag1 = 0;
      flag2 = 0;
      delay(2000);
      Serial.println("Recharged 100rs      ");

      totaldata = totaldata + rech;
      count_prod--;
      lcd.clear();
      lcd.print("Total BAl : ");
      Serial.println("Total BAl: ");
      lcd.setCursor(0, 1);
      lcd.print(totaldata);
      Serial.println(totaldata);
    }
    //2nd card
    if ((str[0] == 115) && (a == 1))
    { //You can change this to the first byte of your tag by finding the card's ID through the Serial Monitor
      lcd.setCursor(0, 0);
      lcd.print("Gaurav      ");
      Serial.println("Gaurav       ");
      lcd.setCursor(0, 1);
      lcd.print("TotalBAL: 500.00      ");
      Serial.println("Total BAL : 500.00      ");
      p2++;
    }
    if ((flag == 1) && (str[0] == 115) && (a == 1))
    {
      //      val++;
      //      Serial.println("Total itom");
      //      Serial.println(val);
      delay(2000);
      Serial.println("Petrol Rs : 100      ");
      //      total = totaldata;
      totaldata1 = totaldata1 - pet;
      count_prod--;
      lcd.clear();
      lcd.print("Total BAl : ");
      Serial.println("Total BAl: ");
      lcd.setCursor(0, 1);
      lcd.print(totaldata1);
      Serial.println(totaldata1);
    }
    if ((str[0] == 115) && (a == 1) && (flag1 == 1))
    {
      delay(2000);
      Serial.println("Petrol Rs : 200      ");
      //      total = 200;
      totaldata1 = totaldata1 - pet1;
      count_prod--;
      lcd.clear();
      lcd.print("Total BAl : ");
      Serial.println("Total BAl: ");
      lcd.setCursor(0, 1);
      lcd.print(totaldata1);
      Serial.println(totaldata1);
    }
    if ((str[0] == 115) && (a == 1) && (flag2 == 1))
    {
      delay(2000);
      Serial.println("Petrol Rs : 105      ");
      //      total = 200;
      totaldata1 = totaldata1 - pet2;
      count_prod--;
      lcd.clear();
      lcd.print("Total BAl : ");
      Serial.println("Total BAl: ");
      lcd.setCursor(0, 1);
      lcd.print(totaldata1);
      Serial.println(totaldata1);
    }

    if ((str[0] == 115) && (a == 0) && (flag3 == 1))
    {
      flag = 0;
      flag1 = 0;
      flag2 = 0;
      delay(2000);
      Serial.println("Recharged 100rs      ");

      totaldata1 = totaldata1 + rech;
      count_prod--;
      lcd.clear();
      lcd.print("Total BAl : ");
      Serial.println("Total BAl: ");
      lcd.setCursor(0, 1);
      lcd.print(totaldata1);
      Serial.println(totaldata1);
    }
    //      else
    //    {
    //      Serial.println("Not Ragisterd!!! ");
    //    }

    Serial.println();
    delay(1000);
  }

  myRFID.AddicoreRFID_Halt();      //Command tag into hibernation
  //Function for receiving sms

}