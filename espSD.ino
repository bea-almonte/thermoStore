#include <SPI.h>
#include <SD.h>

#define SD_SC_PIN 5
int count = 1;

void setup() {
  
  Serial.begin(115200);

  Serial.print("Initializing SD card...");
  
  while (!SD.begin(SD_SC_PIN)) 
    {
      Serial.println("Card failed, or not present");
      delay(2000); // wait 2 secs and reinitialize
    }
  
  Serial.println("Card initialized.");

  SPI.setClockDivider(SPI_CLOCK_DIV128);

  uint8_t cardType = SD.cardType();
  
  if(cardType == CARD_NONE)
    {
      Serial.println("No card attached");
    return;
    }

  Serial.print("Card type: ");
    if(cardType == CARD_MMC)
    {
      Serial.println("MMC");
    } else if(cardType == CARD_SD){
      Serial.println("SDSC");
    } else if(cardType == CARD_SDHC){
      Serial.println("SDHC");
    } else {
      Serial.println("UNKNOWN");
    }
    
// Card Information
Serial.print("Card size (Mb): ");
Serial.println((int)(SD.cardSize()/1048576));
Serial.print(" Available (Mb):");
Serial.println((int)(SD.totalBytes()/1048576));
Serial.print(" Used (Mb):");
Serial.println((int)(SD.usedBytes()/1048576));
}

const char *fileName = ("/Test_write_", scount,".txt");

void loop() {
  Serial.println(scount);
  File dataFile = SD.open("/newTest.txt",FILE_APPEND); // OPENS AND APPENDS TO THE FILE
  //File dataFile = SD.open(fileName,FILE_READ); //OVERWRITES THE FILE
  //File dataFile = SD.open(fileName,FILE_READ); //READS THE FILE
  if(dataFile){
    Serial.print("Opened file:");
    Serial.println(fileName);
    
      if (count <= 3){
  
      //PRINTING TO SCREEN
      Serial.print(" :Celcius Temperature is ");
      Serial.print("56");
      Serial.println("ºC");
      // WRITING TO THE CARD
      dataFile.print(count);
      dataFile.print(" :Celcius Temperature is ");
      dataFile.print("56");
      dataFile.println("ºC");
      dataFile.close();
      //delay(5000);
      count++;
      }
      //dataFile.close();
      Serial.println("data file closed");
      delay(10000);
      //exit(0);
  }else{
    Serial.print("Can't create file: "); 
    Serial.println(fileName);
    exit(0);
  } 
  delay(3000);
  
}
