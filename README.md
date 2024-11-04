# BeagleBone PTP Master Clock Setup

This document provides a step-by-step guide to setting up a Precision Time Protocol (PTP) master clock on a BeagleBone platform. It covers kernel support verification, device tree overlay setup, initial configuration, and how to monitor the system’s operation. This setup achieves high-accuracy time synchronization on a cost-effective platform.

## Table of Contents
1. [Kernel Support Verification](#kernel-support-verification)
2. [Building and Loading Device Tree Overlays](#building-and-loading-device-tree-overlays)
3. [Initial Setup](#initial-setup)
4. [Monitoring Operation](#monitoring-operation)

## 1. Kernel Support Verification
To start, verify that the Linux kernel on the BeagleBone includes the necessary support for CPTS (Common Platform Time Sync). This feature is crucial for enabling PTP functionality.

1. After building the kernel, run the following command on the BeagleBone to confirm CPTS support is enabled:
    ```bash
    zcat /proc/config.gz | grep CONFIG_TI_CPTS
    ```
   - If the output includes `CONFIG_TI_CPTS=y`, CPTS support is active. Otherwise, additional kernel configuration may be required.

## 2. Building and Loading Device Tree Overlays
Device tree overlays are used to enable additional functionality on the BeagleBone hardware, such as an external clock input.

### Steps
1. **Clone the Project Repository**: On the BeagleBone, clone the project’s source code repository. Ensure that the BeagleBone has an active internet connection.
    ```bash
    git clone <repository_url>
    ```

2. **Navigate to the Overlays Directory**: Enter the `Overlays` directory within the cloned repository.
    ```bash
    cd Overlays
    ```
   - This folder contains device tree source files and additional instructions in its `README.md` file.
   - Notably, a custom DTS file (device tree source) is included, adding support for the external clock through the TCLKIN pin.

3. **Load the Device Tree Overlay**:
   - Open the `/boot/uEnv.txt` file, and add the line to load the `BB-TCLKIN-00A0.dtbo` overlay:
      ```plaintext
      dtb_overlay=/lib/firmware/BB-TCLKIN-00A0.dtbo
      ```
   - Save the file, then reboot the BeagleBone to apply the overlay:
      ```bash
      sudo reboot
      ```

## 3. Initial Setup
With the kernel and device tree overlays in place, configure the necessary GPIO pins and compile the main program.

### Steps
1. **Configure GPIO Pins**: Set the required GPIO pins using the `config-pin` command:
    ```bash
    config-pin p8.10 timer   # Set P8.10 to timer mode for DMTIMER 6
    config-pin p9.19 i2c     # Set P9.19 for I2C - SCL
    config-pin p9.20 i2c     # Set P9.20 for I2C - SDA
    ```

2. **Compile the Main Program**:
    - In the project’s root directory, use the provided Makefile to compile the main program:
      ```bash
      make
      ```

3. **Run the Main Program**:
    - After compiling, execute the main program to initialize the PTP master clock.
      ```bash
      ./main
      ```

4. **Run `ts2phc` for Clock Synchronization**:
    - In a separate terminal window, run `ts2phc` with the following command to synchronize the PTP Hardware Clock (PHC) on `/dev/ptp0`:
      ```bash
      ts2phc -c /dev/ptp0 -s generic --ts2phc.extts_correction -2500 --ts2phc.extts_polarity "rising" --ts2phc.pin_index 0 --leapfile /usr/share/zoneinfo/leap-seconds.list --ts2phc.channel 2 -l 7 -m
      ```
   - This command sets the clock on `/dev/ptp0` and applies a timestamp correction for accurate synchronization.

## 4. Monitoring Operation
Once the setup is complete, use `ts2phc` output to monitor the PTP clock's performance. 

### Output Example
The following output format from `ts2phc` illustrates key details of the synchronization status:
```plaintext
ts2phc[80403.557]: adding tstamp 1727879618.999999999 to clock /dev/ptp0
ts2phc[80403.557]: /dev/ptp0 offset         -1 s2 freq  +45529
ts2phc[80404.557]: adding tstamp 1727879619.999999997 to clock /dev/ptp0
ts2phc[80404.557]: /dev/ptp0 offset         -3 s2 freq  +45527

The output format from main program illustrates the D/A values, raw timestamp value
```plaintext
Event low register:ebbccd5
Event high register:3300000
Counter differences: 10000000
PID out value(D/A): 2460
