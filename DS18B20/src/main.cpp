#include <Arduino.h>

// ****************************************************************** 
// Luca Quacquarelli
// 000838997
// 2022-09-26
// Mohawk College - COMP-10184 
// Statement of authorship: I Luca Quacqarelli, 000838997 certify that this material is my original work.
//No other person's work has been used without due acknowledgement. 
 
// library for Arduino framework  
#include <Arduino.h> 
// 1-Wire sensor communication libary 
#include <OneWire.h> 
// DS18B20 sensor library 
#include <DallasTemperature.h> 
 
// Pin that the  DS18B20 is connected to 
const int oneWireBus = D3;      
 
// Setup a oneWire instance to communicate with any OneWire devices 
OneWire oneWire(oneWireBus); 
 
// Pass our oneWire reference to Dallas Temperature sensor  
DallasTemperature DS18B20(&oneWire); 
 
int numberOfDevices; // Number of temperature devices found

DeviceAddress tempDeviceAddress; // We'll use this variable to store a found device address



void setup() { 
  // configure the USB serial monitor 
  Serial.begin(115200); 
 
  // Start the DS18B20 sensor 
  DS18B20.begin(); 
  
  numberOfDevices = DS18B20.getDeviceCount();// Getting the number of devices
  

  Serial.println("Temperature Application");
 
  // if no devices are found print out one error message
  if(numberOfDevices == 0) 
  {
    Serial.print("No DS18B20 temperature sensors are installed!");
    Serial.println();
  }// end if
  else // else a device is found 
  {
    // Loop through each device, print out address
    for(int i = 0; i < numberOfDevices; i++) {
      // Search the wire for address
    	
      if(DS18B20.getAddress(tempDeviceAddress, i)) // Finding the Temperature device that was found 
      {
        Serial.print("Found DS18B20 sensor with address: ");
        // print a device address
        for (uint8_t i = 0; i < 8; i++)
        {
          Serial.print(tempDeviceAddress[i], HEX);// Printing the device in hexadecimal
        }// end for loop #2
        Serial.println();
      }// end if
    }// end for loop #1

  }// end else

}// end setup()
 
void loop() { 
  float fTemp; 
 
  // ask DS18B20 for the current temperature 
  DS18B20.requestTemperatures(); 
  
  // fetch the temperature.  We only have 1 sensor, so the index is 0. 
  fTemp = DS18B20.getTempCByIndex(0); 
  
  // If the device is unplugged the program will not continue with the if statements 
  if(fTemp != -127.00) // -127.00 is bad number 
  {
    // Checking the temperature through if statements
    String temptext;
    if (fTemp <= 10.00)
    {
      temptext = "Cold!";
    } else if(fTemp <= 15.00)
    {
      temptext = "Cool";
    } else if (fTemp <= 25.00)
    {
      temptext = "Perfect!";
    } else if (fTemp <= 30.00)
    {
      temptext = "Warm!";
    } else if (fTemp <= 35.00)
    {
      temptext = "Hot!";
    } else if (fTemp >= 35.00)
    {
      temptext = "Too Hot!";
    }

    // print the temp to the USB serial monitor 
    Serial.println("Current temperature is: " + String(fTemp) + "° C or " + temptext);
  }

  

  // wait 2s (2000ms) before doing this again 
  delay(2000); 
}  
