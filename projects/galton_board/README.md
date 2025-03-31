# Galton Board Digital

This project implements a digital version of a Galton Board (or Plinko), demonstrating how a series of random binary decisions leads to a **normal probability distribution**.

## Objective

Create an interactive visualization that simulates the behavior of a Galton Board using:

- OLED Display  
- Buttons to introduce imbalances to the model  

## Materials List:

| Component             | Connection on BitDogLab       |
|-----------------------|-------------------------------|
| BitDogLab (RP2040)    | -                             |
| WS2812B 5x5 Matrix    | GPIO7                         |
| OLED I2C Display      | SDA: GPIO14 / SCL: GPIO15      |

## Execution

1. Open the project in VS Code, using the environment with support for the Raspberry Pi Pico SDK (CMake + ARM compiler);  
2. Compile the project normally (Ctrl+Shift+B in VS Code or via terminal with cmake and make);  
3. Connect your BitDogLab via USB cable and put the Pico in boot mode (press the BOOTSEL button and connect the cable);  
4. Copy the generated .uf2 file to the storage unit that appears (RPI-RP2);  
5. The Pico will automatically restart and start executing the code;  
6. The histogram will be updated on the OLED display, and the simulated events will appear on the LED matrix.  

## Logic

- At each step, the "ball" moves to the left or right with a 50% probability;  
- The total number of steps defines the depth of the triangle;  
- The final position of the "ball" is counted in the frequency vector;  
- The OLED bars visually represent the frequency of each position.  

## Files

- `src/main.py`: Main project code;  
- `assets/galton_led.jpg`: Simulated paths;  
- `assets/galton_hist.jpg`: Distribution histogram.  

## 🖼️ Project Images

### LED Matrix during execution  
![galton_led](./assets/galton_led.jpg)  

### Histogram on OLED  
![galton_hist](./assets/galton_hist.jpg)  

---

## 📜 License  
MIT License - MIT GPL-3.0
