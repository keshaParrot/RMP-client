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

## Customization

Users can easily adjust which data elements are displayed on the graphs by modifying the configuration file (`config.h`).

## License

This project is open-source and distributed under the [MIT License](LICENSE). Feel free to contribute or modify it for your needs.

