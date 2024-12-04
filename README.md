# problem_statement1:
A Solar panel is having a spec of maximum voltage rating of 100V and Current of 20A. With a micro-controller with maximum ADC voltage of 3.3V, and considering the required voltage and current sensors connected, calculate the total earnings possible from the generated energy. Assume Rs.6 is paid per unit (kWh). Implement a program to display the daily energy generated and the associated earnings.

#solution:
To implement the solution, we'll use an Arduino connected to voltage and current sensors, which measure the output of the solar panel. The program calculates the power, integrates it over time to find energy, and computes the earnings based on the given rate of Rs.6 per kWh. The results are displayed on an OLED display.

1.Hardware Requirements:
  -->Arduino (e.g., Uno or Nano)
  -->Voltage sensor (e.g., Voltage Divider Circuit or Analog Voltage Sensor like ZMPT101B)
  -->Current sensor (e.g., ACS712 or similar)
  -->OLED Display Module (e.g., SSD1306 128x64)
  -->Solar Panel with the given specifications
  -->Connecting wires, resistors for the voltage divider, etc.

2.Implementation :
  Voltage Divider Circuit for Voltage Measurement:
  Reduce the maximum solar panel voltage (100V) to the Arduino ADC range (0-3.3V).
  Use two resistors  R1 and 𝑅2 in series.
  The scaling factor:
  “Vout​<=Vin​× { R2 / (R1+​R2) }​​”
  Ensure  that  𝑉𝑜𝑢𝑡 ≤ 3.3𝑉 for 𝑉𝑖𝑛=100*𝑉

3.Current Measurement:
  Use a current sensor like ACS712 (20A variant).
  The output voltage of ACS712 is directly proportional to the current.
  Power Calculation:
  P(t)=V(t)×I(t)

4.Energy Calculation:
  Energy is calculated by summing power over time:
  E = ∫P(t).dt
  Implemented as:
  E+=P(t)×Δt
  
5.Earnings Calculation:

  Earnings = E×6 (in Rs.)

6.Steps to Use:

  Calibrate the voltage divider and current sensor.
  Connect the sensors to the Arduino in Proteus software or in physically.
  Write the code to the ArduinoIDE and upload to the Arduino board.
  To run the connected circuit in proteus, copy the .hex file path in ArduinoIDE after compailing.
  Paste the .hex file path in the board's program file box in the proteus software and run it. 
  Observe the energy and earnings data on the OLED display.
  This program calculates daily energy generation and displays for it's earnings accurately.
