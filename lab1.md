# Building a Complete Embedded System

## Objectives

After completing this lab, you will be able to:

* Create an embedded system design using Vivado and SDK flow
* Configure the Processing System (PS)
* Add Xilinx standard IP in the Programmable Logic (PL) section
* Use SDK to build a software project and verify the design functionality in hardware.

## Steps

## Create a Vivado Project
### Launch Vivado and create an empty project targeting the PYNQ-Z1 or PYNQ-Z2 board, selecting Verilog as a target language
1. Open Vivado by selecting **Start &gt; All Programs &gt;**  **Xilinx Design Tools**  **&gt; Vivado 2018.2 &gt; Vivado 2018.2**
1. Click **Create Project** to start the wizard. You will see the _Create A New Vivado Project_ wizard page. Click **Next**.
1. Click the Browse button of the _Project Location_ field of the **New Project** form, browse to **{labs}** , and click **Select**.
1. Enter **lab1** in the _Project Name_ field.  Make sure that the _Create Project Subdirectory_ box is checked.  Click **Next**.

    <p align="center">
    <img src ="./images/lab1/Fig2.png" width="60%" height="80%"/>
    </p>
    <p align = "center">
    <i>Project Name Entry</i>
    </p>

1. Select the **RTL Project** option in the _Project Type_ form, and click **Next**.
1. Select **Verilog** as the _Target Language_ and _Simulation Language_ in the _Add Sources_ form, and click **Next**.
1. Click **Next** to skip adding constraints.
1. In the _Default Part_ form, click **Boards** filter.
1. Select **www.digilentinc.com** for the _PYNQ-Z1_ board, **tul.com.tw** for the _PYNQ-Z2_ board in the Vendor field, select _PYNQ-Z1__or pynq-z2_, and click **Next**.

    <p align="center">
    <img src ="./images/lab1/Fig3.png" width="60%" height="80%"/>
    </p>
    <p align = "center">
    <i>Board Selection (pynq-z2)</i>
    </p>

1. Click **Finish** to create an empty Vivado project.

### Creating the Hardware System Using IP Integrator

1. Create a block design in the Vivado project using IP Integrator to generate the ARM Cortex-A9 processor based hardware system.
1. In the Flow Navigator, click **Create Block Design** under IP Integrator.
1. Name the block **system** and click **OK**.
1. Click on the  button.
1. Once the IP Catalog is open, type zy into the Search bar, and double click on the **ZYNQ7 Processing System** entry to add it to the design.
1. Click on **Run Block Automation** and click **OK** to automatically configure the board presets.

    <p align="center">
    <img src ="./images/lab1/Fig4.png" width="60%" height="80%"/>
    </p>
    <p align = "center">
    <i>Zynq Block Automation View (pynq-z2)</i>
    </p>

1. Double click on the Zynq block to open the _Customization_ window for the Zynq processing system.

    A block diagram of the Zynq PS should now be open, showing various configurable blocks of the Processing System.

1. At this stage, designer can click on various configurable blocks (highlighted in green) and change the system configuration.

    <p align="center">
    <img src ="./images/lab1/Fig5.png" width="60%" height="80%"/>
    </p>
    <p align = "center">
    <i>Zynq Processing System Configuration View (pynq-z2)</i>
    </p>

#### Configure the I/O Peripherals block to only have UART 0 support.
1. Click on the _MIO Configuration_ panel to open its configuration form.
1. Expand the I/O Peripherals (and GPIO).
1. Deselect all the peripherals except _UART 0_ (Deselect ENET 0, USB 0, SD 0, and GPIO).

    <p align="center">
    <img src ="./images/lab1/Fig6.png" width="60%" height="80%"/>
    </p>
    <p align = "center">
    <i>Selecting only UART 0 Peripheral of PS</i>
    </p>

1. Click **OK**.

    The configuration form will close and the block diagram will be updated as shown below.

    <p align="center">
    <img src ="./images/lab1/Fig7.png" width="60%" height="80%"/>
    </p>
    <p align = "center">
    <i>ZYNQ7 Processing System configured block</i>
    </p>

### Add one instance of GPIO, name it _buttons_, and configure for the board. Connect the block to the Zynq.

1. Click the ![alt tag](./images/add_ip.png) button and search for **AXI GPIO** in the catalog.
1. Double-click the **AXI GPIO** to add an instance of the core to the design.
1. Click on the **AXI GPIO** block to select it, and in the _Block properties_ tab, change the name to **buttons.**
1. Double click on the **AXI GPIO** block to open the customization window. Under _Board Interface_, for _GPIO_, click on **Custom** to view the drop down menu options, and select **btns 4Bits** for the PYNQ-Z2 or the PYNQ-Z1 board.

    As the board was selected during the project creation, and a board support package is available for these boards, Vivado has knowledge of available resources on the board.

1. Click the **IP Configuration** tab. Notice the GPIO Width is set to 4 (PYNQ-Z1 and PYNQ-Z2) and is greyed out.  If a board support package was not available, the width of the IP could be configured here.
1. Click **OK** to finish configuring the GPIO and to close the _Re-Customize IP_ window.
1. Click on **Run Connection Automation** , and select **buttons** (which will include GPIO and S\_AXI)

    Click on **GPIO** and **S\_AXI** to check the default connections for these interfaces.

    <p align="center">
    <img src ="./images/lab1/Fig8.png" width="60%" height="80%"/>
    </p>
    <p align = "center">
    <i>Connection Automation for the GPIO (PYNQ-Z2)</i>
    </p>

1. Click **OK** to automatically connect the _S\_AXI_ interface to the Zynq _GP0_ port (through the AXI interconnect block), and the GPIO port to an external interface.

    Notice that after block automation has been run, two additional blocks that are required to connect the blocks, _Processor System Reset_, and _AXI Interconnect_ have automatically been added to the design.

1. Add another instance of GPIO, name the instance _leds_, configure it and connect it to the Zynq.
1. Add another instance of the _GPIO_ peripheral **.**
1. Change the name of the block to **leds.**
1. Double click on the _leds_ block, and select **leds 4bits** (PYNQ-Z1 and PYNQ-Z2) for the _GPIO_ interface and click **OK.**
1. Click on **Run Connection Automation**
1. Click **leds** , and check the connections for _GPIO_ and _S\_AXI_ as before
1. Click **OK** to automatically connect the interfaces as before.

    Notice that the AXI Interconnect block has the second master AXI (M01\_AXI) port added and connected to the S\_AXI of the leds.

1. Add another instance of GPIO, name the instance _switches_, configure it and connect it to the Zynq.
1. Add another instance of the _GPIO_ peripheral **.**
1. Change the name of the block to **switches.**
1. Double click on the _switches_ block, and select **sws 2bits** (PYNQ-Z1 and PYNQ-Z2) for the _GPIO_ interface and click **OK.**
1. Click on **Run Connection Automation**
1. Click **switches** , and check the connections for _GPIO_ and _S\_AXI_ as before
1. Click **OK** to automatically connect the interfaces as before.

    Notice that the AXI Interconnect block has the third master AXI (M02\_AXI) port added and connected to the S\_AXI of the leds.

    At this stage the design should look like as shown below.

    <p align="center">
    <img src ="./images/lab1/Fig9.png" width="60%" height="80%"/>
    </p>
    <p align = "center">
    <i>Completed design</i>
    </p>

1. Verify that the addresses are assigned to the two GPIO instances and validate the design for no errors.
1. Select the **Address Editor** tab and see that the addresses are assigned to the three GPIO instances.  They should look like as follows.

    <p align="center">
    <img src ="./images/lab1/Fig10.png" width="60%" height="80%"/>
    </p>
    <p align = "center">
    <i>Assigned addresses</i>
    </p>

    The addresses should be in the 0x40000000 to 0xbfffffff range as the instances are connected to M\_AXI\_GP0 port of the processing system instance.

1. Select the _Diagram_ tab, and click on the ![alt tag](./images/validate.png)
 (Validate Design) button to make sure that there are no errors.
 
    Ignore warnings.

1. Select **File &gt; Save Block Design** to save the design.
1. Since all IO pins are board-aware no additional user constraints are need.

### Generate the Bitstream        
1. Create the top-level HDL of the embedded system.  Add the provided constraints file and generate the bitstream.
1. In Vivado, select the _Sources_ tab, expand the _Design Sources,_ right-click the _system.bd_ and select **Create HDL Wrapper…**

    <p align="center">
    <img src ="./images/lab1/Fig11.png" width="60%" height="80%"/>
    </p>
    <p align = "center">
    <i>Selecting the system design to create the wrapper file</i>
    </p>

1. Click **OK** when prompted to allow Vivado to automatically manage this file.

    The wrapper file, _system\_wrapper.v_, is generated and added to the hierarchy.  The wrapper file will be displayed in the Auxiliary pane.

    <p align="center">
    <img src ="./images/lab1/Fig12.png" width="60%" height="80%"/>
    </p>
    <p align = "center">
    <i>Design Hierarchy View</i>
    </p>

1. Click on the **Generate Bitstream** in the _Flow Navigator_ pane to synthesize and implement the design, and generate the bitstream. Click **Save** and **Yes** if prompted. Click **OK** to launch the runs.
1. When the bitstream generation is complete, click **Cancel**.

### Export the Design to the SDK
#### Exporting the design and launch SDK
1. Export the hardware configuration by clicking **File &gt; Export &gt; Export Hardware** … Tick the box to include the bitstream and click **OK**.

    <p align="center">
    <img src ="./images/lab1/Fig13.png" width="60%" height="80%"/>
    </p>
    <p align = "center">
    <i>Exporting the hardware</i>
    </p>

1. Launch SDK by clicking **File &gt; Launch SDK** and click **OK**

    (Launching SDK from Vivado will automatically load the SDK workspace associated with the current project. If launching SDK standalone, the workspace will need to be selected.)

## Generate an Application in SDK
### Generate a board support package project with default settings and default software project name.

SDK should open and automatically create a hardware platform project based on the configuration exported from Vivado. A board support package and software application will be created and associated with this hardware platform.

1. Select **File** &gt; **New** &gt; **Board Support Package**

    <p align="center">
    <img src ="./images/lab1/Fig14.png" width="60%" height="80%"/>
    </p>
    <p align = "center">
    <i>Create BSP</i>
    </p>

1. Click **Finish** with the default settings selected (using the Standalone operating system).

    This will open the Software Platform Settings form showing the OS and libraries selections.

1. Click **OK** to accept the default settings as we want to create a **standalone\_bsp\_0** software platform project without any additional libraries.
1. The library generator will run in the background and will create the **xparameters.h** file in the **lab1.sdk\standalone\_bsp\_0\ps7\_cortexa9\_0\include** directory.
1. Create an empty application project, named lab1, and import the provided lab1.c file.
1. Select **File &gt; New** &gt; **Application Project.**
1. In the _Project Name_ field, enter **lab1** as the project name.
1. Select the _Use existing_ option in the _Board Support Package_ field and then click **Next.**

    <p align="center">
    <img src ="./images/lab1/Fig15.png" width="60%" height="80%"/>
    </p>
    <p align = "center">
    <i>Create a Blank Application Project</i>
    </p>

1. Select the **Empty Application** template and click **Finish.**

    The lab1 project will be created in the Project Explorer window of SDK.

1. Select **lab1 &gt; src** directoryin the project view, right-click, and select **Import.**
1. Expand the **General** category and double-click on **File System.**
1. Browse to the **{sources}\lab1** folder.
1. Select the **lab1.c** source file and click **Finish.**

    A snippet of the source code is shown in the following figure. Note the greyed out code will be used in Lab5. The code reads from the switches, and writes to the LEDs. The BTN is read, and written to the LED.

    <p align="center">
    <img src ="./images/lab1/Fig16-1.png" width="60%" height="80%"/>
    </p>
    <p align="center">
    <img src ="./images/lab1/Fig16-2.png" width="60%" height="80%"/>
    </p>
    <p align = "center">
    <i>Snippet of Source Code</i>
    </p>

## Test in Hardware
### Connect and power up the board. Establish serial communications using the SDK&#39;s Terminal tab.  Verify the design functionality.
1. Connect and power up the board.
1. Select the ![alt tag](./images/terminal.png)
 tab.  If it is not visible then select **Window &gt; Show view &gt; Other &gt; Terminal &gt; Terminal**.
1. Click on ![alt tag](./images/connect.png) and select appropriate COM port (depending on your computer), and configure the terminal with the parameters as shown below.

    <p align="center">
    <img src ="./images/lab1/Fig17.png" width="60%" height="80%"/>
    </p>
    <p align = "center">
    <i>SDK Terminal Settings</i>
    </p>

1. Select **Xilinx** &gt; **Program FPGA** and then click the **Program** button.
1. Make sure that the **SW0-1** are not set to &quot;11&quot;.
1. Select the **lab1** project in the _Project Explorer_, right-click and select **Run As &gt; Launch on Hardware(System Debugger)** to download the application, execute ps7\_init, and execute lab1.elf.
1. You should see the following output on the Terminal console.


    <p align="center">
    <img src ="./images/lab1/Fig18.png" width="60%" height="80%"/>
    </p>
    <p align = "center">
    <i>SDK Terminal Output</i>
    </p>

1. Press the BTN0-BTN3 (PYNQ-Z1, PYNQ-Z2) and see the corresponding LED light up.
1. Set the two slide switches on PYNQ-Z1 or PYNQ-Z2 to the ON position to exit the program.
1. Close SDK and Vivado programs by selecting **File &gt; Exit** in each program.
1. Turn OFF the power to the board.

## Conclusion

In this lab, you created an ARM Cortex-A9 processor based embedded system using the Zynq device for the PYNQ-Z1/PYNQ-Z2 board.  You instantiated the Xilinx standard GPIO IP to provide input and output functionality.

You created the project in Vivado, created the hardware system using IPI, implemented the design in Vivado, exported the generated bitstream to the SDK, created a software application in the SDK, and verified the functionality in hardware after programming the PL section and running the application from the DDR memory.