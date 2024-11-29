# Resource Monitor Project - Client

This project is an Arduino-based resource monitor that retrieves system data from an [RMP-Server](https://github.com/keshaParrot/RMP-server) via UART, 
parses it using the **ArduinoJson** library, and displays the information on a **TFT LCD screen** using the **TFT_eSPI** library.

## Features
- **Data Retrieval via UART**: The system fetches data from an external RMP server every few seconds.
- **Real-Time Display**: The parsed data is shown on different screens, including `CPUScreen`, `GPUScreen`, `HomeScreen`, and `RAMScreen`.
- **Customizable Graphs**: Users can customize which system resource data is displayed on the graphs for CPU, RAM, and GPU through a configuration file.

## Data Displayed

- **CPUScreen**: Displays information about CPU cores, including:
  - Load (percentage of CPU usage)
  - Temperature (in Celsius)
  - Frequency (in MHz)
  - Voltage (in Volts)

- **GPUScreen**: Shows GPU-related statistics, such as:
  - GPU Load (percentage of GPU usage)
  - Memory Load (percentage of GPU memory usage)
  - Temperature (in Celsius)
  - Fan Speed (in RPM)
  - Voltage (in Volts)
  - Frequency (in MHz)

- **RAMScreen**: Shows RAM usage statistics, including:
  - Load (percentage of RAM usage)
  - Total memory
  - Used memory
  - Available memory
  - Virtual memory usage

- **HomeScreen**: Provides a summary of system resource usage, allowing users to navigate between different screens.

**switching between screens is implemented using 4 button pins connected to microcontrollers (you can specify the ports to which the buttons are connected in config.h)**

## Installation Instructions

### 1. Download the Repository

- Click the **"Code"** button on the GitHub page and select **Download ZIP**,

**or**

- Use Git to clone the repository: git clone https://github.com/yourusername/repository-name.git

### 2. Open the Project in Arduino IDE

- Open the Arduino IDE.
- Go to **File > Open** and navigate to the folder where you downloaded/cloned the repository.
- Open the `.ino` file located in the project folder.

### 3. Install the Required Libraries

#### TFT_eSPI Library

- Download and install the **TFT_eSPI** library:
1. Go to **Sketch > Include Library > Manage Libraries**.
2. In the Library Manager, search for **TFT_eSPI** and click **Install**.

- **Important**: After installing the TFT_eSPI library, you must configure it for your specific display controller. Follow the configuration instructions on the [TFT_eSPI GitHub repository](https://github.com/Bodmer/TFT_eSPI) to set up the `User_Setup.h` file to match your screen's pinout and configuration.

#### ArduinoJson Library

- Download and install the **ArduinoJson** library:
1. Go to **Sketch > Include Library > Manage Libraries**.
2. In the Library Manager, search for **ArduinoJson** and click **Install**.

### 4. Upload the Sketch to Your Microcontroller

- Connect your microcontroller (e.g., Arduino Uno, ESP32, pi pico.) to your computer via USB.
- In the Arduino IDE, go to **Tools > Board** and select the correct board.
- Select the correct **Port** under **Tools > Port**.
- Click **Upload** to compile the sketch and upload it to your microcontroller.

Once uploaded, the system will start retrieving data from the [RMP-Server](https://github.com/keshaParrot/RMP-server) if server is running and wait data if not, then displaying it on the TFT LCD screen.

## Customization

Users can easily adjust which data elements are displayed on the graphs by modifying the configuration file (`config.h`).

## License

This project is open-source and distributed under the [MIT License](LICENSE). Feel free to contribute or modify it for your needs.

