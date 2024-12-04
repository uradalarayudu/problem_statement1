#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>       //include these libraries nessessary for OLED  display module
#define SCREEN_WIDTH 128           //define screen size of oled that we use(i am using full sixe i.e 64*128)
#define SCREEN_HEIGHT 64

//OLED Reset pin (not using reset)                 
#define OLED_RESET -1                     //}define only if we use reset pin
Adafruit_SH1106 display(OLED_RESET);      //}
           
const int voltagePin = A0;                // Voltage sensor connected to A0 pin
const int currentPin = A1;                // Current sensor connected to A1 pin on Arduino board

const float voltageDividerRatio = 0.0325; // Vout = Vin*{R2/(R1+R2)} Adjust based on your voltage divider (to read both vol. and Amp. single current sensor enough )
                                          // in our problem statement vout=100V; Vin=3.3V: suppose if R1=1K_Ohm then R2=31K_Ohm; Vol_Divide_Ratio = R1 / R2
const float currentSensitivity = 0.1;     // ACS712 (current sensor) sensitivity (V/A) 

unsigned long previous_time = 86400000;   // (normally set to 0 ) this defines previous completed time period, now defined as one compleated day
const unsigned long interval_time = 86400000;  // This is set for 1 Day (to calculate earnings for every new day )
                                          // desfine and assign Energy and earnings value
float TotalEnergy = 0;                    // Enevgy should be calculated in kWh
float TotalEarnings = 0;                  // No.of kWhs*Cost per kWh

void setup() {                            // Initialize Serial OLED
  Serial.begin(9600);
  display.begin(SH1106_I2C_ADDRESS, 0x3C);    //use I2C address as  0x3C or 0x3D 
  display.clearDisplay();
  display.display();
                                          // Display welcome message
  display.setTextSize(1);                 //}
  display.setTextColor(WHITE);            //} set text color and text size
  display.setCursor(15, 0);                 
  display.println("ENERGY CALCULATOR");   //} mention
  display.setCursor(15, 10);              //} co-ordinates 
  display.println("for SOLAR GRID");      //} from
  display.setCursor(60, 20);              //} where
  display.println("BY");                  //} textshould be 
  display.setCursor(20, 30);              //} printed on
  display.println("RAYUDU URADALA");      //} OLED
  display.display();                      //} Display
  delay(3500);
}

void loop() {
  unsigned long current_time = millis();  // "millis" is built in Arduino function to calculate time, used instaed of delay function 
  if (current_time - previous_time >= interval_time) {
    previous_time = current_time;         // calculate Vol. Current power and energy for time period of a day
                                          // Read voltage and current
    float PanelVoltage = analogRead(voltagePin) * (3.3 / 1023.0) / voltageDividerRatio;
    float PanelCurrent = (analogRead(currentPin) * (3.3 / 1023.0) - 2.5) / currentSensitivity;
                                          
    float Power = PanelVoltage * PanelCurrent;                   // Calculate power in WTs

    TotalEnergy += Power / 1000.0 * (interval_time / 3600000.0); // Calculate Energy in kWh


    TotalEarnings = TotalEnergy * 6;                             // Calculate earnings in Rs
    // Display values on OLED
    display.clearDisplay();           // Clear the previous display buffer
    display.setTextSize(0.8);         // set Small text size
    display.setCursor(0, 0);          // Start text at the top-left corner
    display.println("Energy and Earnings  Calculation per Day");
    
    display.setCursor(0, 20);       
    display.print("Voltage: ");
    display.print(PanelVoltage, 3);   // Display Vol. upto 3 decimal points
    display.println(" V");

    display.print("Current: ");
    display.print(PanelCurrent, 3);   // Display PanelCurrent upto 3 decimal points in Amps
    display.println(" A");

    display.print("Power  : ");
    display.print(Power, 3);          // Display Power upto 3 decimal points Whats
    display.println(" W");

    display.print("Energy: ");
    display.print(TotalEnergy, 2);    // Display TotalEnergy upto 3 decimal points in kWTs
    display.println(" kWh/Day");

    display.print("Earnings: Rs.");
    display.print(TotalEarnings, 2);  // Display TotalEarnings upto 3 decimal points in Rs
    display.display();
  }
}