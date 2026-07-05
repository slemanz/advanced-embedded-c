# Bootloader

### What is a bootloader?

A bootloader is a small piece of software that is responsible for loading and
initializing the main application program on a microcontroller or other embedded
device.

The bootloader is usually stored in a special area of memory that is reserved
for boot code, and it runs immediately after the device is powered on or reset.

### The need for a Bootloader

The main purpose of a bootloader is to provide a way to update the firmware on
the device without requiring specialized hardware or tools.

This is especially useful for devices that are deployed in the field, where it
may not be practical or cost-effective to physically connect to the device and
program it using traditional methods.

With a bootloader, the firmware can be updated over the air, via a wired or
wireless connection, or even by the end-user themselves using a simple
interface.

### Main uses of a bootloader

- **Firmware updates:** A bootloader allows for easy and convenient firmware
updates to the device, without requiring specialized hardware or tools.

- **Recovery mode:** In case the main firmware becomes corrupted or fails, a
bootloader can provide a recovery mode that allows for the device to be restored
to a working state. This is especially useful for critical applications where
downtime can be costly.

- **Security:** Bootloaders can provide an added layer of security by allowing
for firmware updates to be performed only by authorized personnel or devices.
This can help prevent unauthorized access or tampering with the device.

--- 

- [Linker Script](linkerscript/)
- [Bootloader v1](bootloader-v1/)
- [Multi Slot Bootloader System](multi-slot/)