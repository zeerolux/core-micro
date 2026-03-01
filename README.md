# Zeerolux Core-Micro

A lighting controller, control surface with 5 faders and 2 encoders, a USB DMX interface, an ARTNET node, and a standalone DMX generator. The Core-Micro system consists or 4 modules; the logic processor, the control surface, the DMX interface, and the redundant USB-C power supply. These modules are designed in a way that allows them to be iterated on separetly and allow for a limitless amount of configuration. How do you use Core-Micro? It depends on how YOU need to use it. Core-Micro can be used as a midi controller for On-PC lighting softwares, it can be used in a standalone mode where it acts like an all in one system for controlling stage lighting, and eventually it will be able to run in conjuction with other Zeerolux hardware and software as either the main controller or as a programming wing. It can also be used as an ARTNET node, this means that you can connect to it over the network and output DMX out its outputs.

### Defintions:
- DMX: Digital Multiplex is an RS485 based communication standard for controlling stage lights and equipment.
- ARTNET: DMX over IP
- On-PC: A standard term used by lighting consoles to describe control systems that require a laptop or PC to operate as opposed to all processing running on console.
- Avolites Quartz: A 

<img width="1600" height="1200" alt="image" src="https://github.com/user-attachments/assets/a203856b-5387-4f76-ac0a-76d043b33ba2" />

### Why?
I decided to take on this project after I realised how incredibly expensive lighting consoles are. Out of curiosity, I wanted to see whether I could build my own console and what price it would turn out at. Another inspiration was my experience with the Avolites Quartz which to say the least was... frustrating, so naturally, I was fresh with ideas on what not to do.

<img width="1600" height="1200" alt="image" src="https://github.com/user-attachments/assets/09d99a7a-2156-47d1-b991-dae4e0aa9a78" />

## The Hardware
Core-Micro has four PCBs; one for each module. 

### Logic PCB:
<img width="600" height="500" alt="image" src="https://github.com/user-attachments/assets/57931873-9b58-4215-b7a1-41d606c71b7a" />

The Logic PCB does a few main things:
- Connects to PC over USB
- Processes DMX signals and distrobutes them to DMX PCB(s)
- Runs ARTNET
- Interfaces with Surface PCB
All the main processing is powered by an RP2040 and the ethernet controller is a W5500.

<img width="600" height="500" alt="image" src="https://github.com/user-attachments/assets/17de5a51-9f6d-4434-b32e-9e0a0328d4a4" />


### Control Surface PCB
<img width="600" height="500" alt="image" src="https://github.com/user-attachments/assets/27b2eaf2-a91c-425c-9260-e956d14383b9" />

This PCB's purpose is as follows:
- To have enough buttons to comfortably program lights
- To have enough faders for basic theatre applications
- To interface with the Logic board and passthrough control to PC applications or standalone mode.
Like the Logic PCB, the Control Surface is powered by an RP2040 and sends commands to other components via UART.

<img width="600" height="500" alt="image" src="https://github.com/user-attachments/assets/02779e29-b142-46ea-8f19-cc8e989d272d" />

### Power PCB
<img width="500" height="600" alt="image" src="https://github.com/user-attachments/assets/18bed14b-2d32-436d-a761-7beee57d8125" />

Why do we need a separate PCB for power? Redundancy. In a live production environment, we cannot tolerate any power cuts or flaky USB connections. Therefore, I designed a board that has two inputs that can automatically be switched between if one cuts out. This allows for:
- Usage of independant power supplies for redundancy
- Automatic switch over to battery power during power cuts or brownouts
There is also a Superviser IC on this PCB in case I want to add that functionality in the future to other modules.

<img width="600" height="500" alt="image" src="https://github.com/user-attachments/assets/9abccac9-71fe-4df6-9382-c6a26e50b408" />

### DMX Interface PCB
<img width="500" height="600" alt="image" src="https://github.com/user-attachments/assets/4d3b3220-f426-4dcb-b4c4-ce2fd4255fa5" />

This simple PCB converts the PIO DMX signal into RS485 signal that can be sent to DMX fixtures. This board also has both 3-pin and 5-pin XLR to ensure you can connect to any light.

<img width="600" height="500" alt="image" src="https://github.com/user-attachments/assets/f866f6a3-5730-474e-8580-6e9f9c985916" />

## The Software

At this current moment, the software is a minimal version designed for testing DMX and ARTNET in a standalone mode. Here is the ideal list of software features I would like to implement:
- Standalone mode
- ARTNET node mode
- Midi Mode
- Custom serial driver for control via custom software

## BOM

## Bill of Materials (BOM)

| Item                          | Qty | Link / Supplier | List Price  | Actual  | Location    | Shipping  |
|--------------------------------|-----|-----------------|------------------|--------------|------------|----------------|
| Surface PCB                    | 5   | JLCPCB          | 17.90            | 190.94       | JLCPCB     | 33.14          |
| Surface PCB Assembly           | 2   | JLCPCB          | 39.89            | —            | aliexpress | —              |
| Logic PCB                      | 5   | JLCPCB          | 4.00             | —            | mouser     | 20.00          |
| Logic PCB Assembly             | 2   | JLCPCB          | 48.14            | —            | beekeeb    | 15.64          |
| DMX PCB                        | 5   | JLCPCB          | 4.00             | —            | —          | —              |
| DMX PCB Assembly               | 2   | JLCPCB          | 18.58            | —            | —          | —              |
| Power PCB                      | 5   | JLCPCB          | 2.00             | —            | —          | —              |
| Power PCB Assembly             | 2   | JLCPCB          | 43.29            | —            | —          | —              |
| Encoders                       | 3   | Mouser          | 5.07             | 5.07         | —          | —              |
| Faders                         | 5   | Mouser          | 9.60             | 9.60         | —          | —              |
| USB B Socket                   | 1   | Mouser          | 0.95             | 0.95         | —          | —              |
| Threaded Inserts M3            | 100 | AliExpress      | 5.00             | 5.00         | —          | —              |
| Threaded Inserts M2            | 100 | AliExpress      | 5.00             | 5.00         | —          | —              |
| Screws M3                      | 50  | AliExpress      | 3.00             | 3.00         | —          | —              |
| Screws M2                      | 50  | AliExpress      | 3.00             | 3.00         | —          | —              |
| Key Switches                   | 50  | Beekeeb         | 49.00            | 49.00        | —          | —              |
| Neutrik 3 Pin XLR              | 2   | Mouser          | 5.64             | 5.64         | —          | —              |
| Neutrik 5 Pin XLR              | 2   | Mouser          | 7.74             | 7.74         | —          | —              |
| Shipping (overall products)    | —   | —               | 68.78            | —            | —          | —              |
| **Total Cost**                 | —   | —               | **284.94**       | —            | —          | —              |




