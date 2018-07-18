# Configuration and Booting

## Objectives

After completing this lab, you will be able to:

* Create a bootable system capable of booting from the SD card
* Create a bootable system capable of booting from the QSPI flash
* Load the bitstream stored on the SD card or in the QSPI flash memory
* Configure the PL section using the stored bitstream through the PCAP resource
* Execute the corresponding application

## Steps
## Create a Vivado Project
### Launch Vivado and create an empty project, called lab5, using the Verilog language.
1. Open Vivado and click **Create New Project** and click **Next**.
1. Click the Browse button of the _Project Location_ field of the **New Project** form, browse to { **labs}** , and click **Select**.
1. Enter **lab5** in the _Project Name_ field.  Make sure that the _Create Project Subdirectory_ box is checked.  Click **Next**.
1. Select the **RTL Project** option in the _Project Type_ form, and click **Next**.
1. Select **Verilog** as the _Target Language_ in the _Add Sources_ form, and click **Next**.
1. Click **Next** two times.
1. Select **www.digilentinc.com** for the _PYNQ-Z1_ board, **tul.com.tw** for the _PYNQ-Z2_ board in the Vendor field, select _PYNQ-Z1__or pynq-z2_, and click **Next**.
1. Click **Finish** to create an empty Vivado project.
## Creating the Hardware System Using IP Integrator
### Create a block design in the Vivado project using IP Integrator to generate the ARM Cortex-A9 processor based hardware system.
1. In the Flow Navigator, click **Create Block Design** under IP Integrator.
1. Name the block **system** and click **OK**.
1. Click the ![alt tag](./images/add_ip.png) button.
1. Once the IP Catalog is open, type zy into the Search bar, and double click on **ZYNQ7 Processing System** entry to add it to the design.
1. Click on _Run Block Automation_ in the message at the top of the _Diagram_ panel. Leave the default option of _Apply Board Preset_ checked, and click **OK**.
1. Double click on the Zynq block to open the _Customization_ window.

    A block diagram of the Zynq should now be open, showing various configurable blocks of the Processing System.

### Configure the I/O Peripherals block to only have QSPI, UART 0, and SD 0 support.
1. Click on the _MIO Configuration_ panel to open its configuration form.
1. Expand the _IO Peripherals_ on the right.
1. Uncheck _ENET 0_, _USB 0_, and _GPIO &gt; GPIO MIO,_ leaving _UART 0_ and _SD 0_ selected.
1. Click **OK**.

    The configuration form will close and the block diagram will be updated.

1. Using wiring tool, connect FCLK\_CLK0 to M\_AXI\_GP0\_ACLK.
1. Select the _Diagram_ tab, and click on the ![alt tag](./images/validate.png) (Validate Design) button to make sure that there are no errors.
## Export the Design to the SDK and create the software projects        
### Create the top-level HDL of the embedded system, and generate the bitstream.
1. In Vivado, select the _Sources tab_, expand the _Design Sources,_ right-click the _system.bd_ and select **Create HDL Wrapper** and click **OK.**
1. Click on **Generate Bitstream** and click **Generate**. Click **Save** to save the project, and **Yes** if prompted to run the processes. Click **OK** to launch the runs.
1. When the bitstream generation process has completed successfully, click **Cancel**.
### Export the design to the SDK and create the Hello World application.
1. Export the hardware configuration by clicking **File &gt; Export &gt; Export Hardware…**
1. Click the box to _Include Bitstream_, then click **OK**
1. Launch SDK by clicking **File &gt; Launch SDK** and click **OK**
1. In SDK, select **File** &gt; **New** &gt; **Application Project.**
1. Enter **hello\_world** in the project name field, and leave all other settings as default.
1. Click **Next** and make sure that the _Hello World_ application template is selected, and click **Finish** to generate the application.
1. Right click on hello\_world\_bsp and click **Board Support Package Settings**
1. Tick to include _xilffs_ click **OK** (This is required for the next step to create the FSBL).
### Create a first stage bootloader (FSBL).
1. Select **File** &gt; **New &gt; Application Project.**
1. Enter **zynq\_fsbl** as the project name, select the _Use existing_ standalone Board Support Package option with **hello\_world\_bsp** , and click **Next**.
    <p align="center">
    <img src ="./images/lab5/Fig2.png" width="60%" height="80%"/>
    </p>
    <p align = "center">
    <i>Creating the FSBL Application</i>
    </p>
1. Select _Zynq FSBL_ in the **Available Templates** pane and click **Finish**.

    A zynq\_fsbl project will be created which will be used in creating the BOOT.bin file.  The BOOT.bin file will be stored on the SD card which will be used to boot the board.

## Create the Boot Images and Test
### Using the Windows Explorer, create a directory called _image_ under the lab5 directory. You will create the BOOT.bin file using the FSBL, system\_wrapper.bit and hello\_world.elf files.
1. Using the Windows Explorer, create a directory under the _lab5_ directory and call it **image**.
1. In the SDK, select **Xilinx &gt; Create Boot Image**.

    Click on the Browse button of the **Output BIF** field, browse to **{labs}\lab5\image** and click **Save** (leaving the default name of output.bif)

1. Click on the **Add** button of the _Boot image partitions,_ click the Browse button in the Add Partition form, browse to **{labs}\lab5\lab5.sdk\zynq\_fsbl\Debug** directory (this is where the FSBL was created), select _zynq\_fsbl.elf_ and click **Open**.

    Note the partition type is bootloader, then click **OK.**

    <p align="center">
    <img src ="./images/lab5/Fig3.png" width="60%" height="80%"/>
    </p>
    <p align = "center">
    <i>Adding FSBL partition</i>
    </p>
1. Click on the **Add** button of the _Boot image partitions_ and add the bitstream, **system\_wrapper.bit** , from **{labs}\lab5\lab5.sdk\system\_wrapper\_hw\_platform\_0** and click **OK**.
1. Click on the **Add** button of the _Boot image partitions_ and add the software application, **hello\_world.elf** , from **{labs}\lab5\lab5.sdk\hello\_world\Debug** and click **OK**.
1. Click the **Create Image** button.

    The BOOT.bin and the output.bif files will be created in the **{labs}\lab5\image** directory.  We will use the BOOT.bin for the SD card boot up.

    <p align="center">
    <img src ="./images/lab5/Fig4.png" width="60%" height="80%"/>
    </p>
    <p align = "center">
    <i>Creating BOOT.bin image file</i>
    </p>
1. Insert a blank SD/MicroSD card (FAT32 formatted) in a Card reader, and using the Windows Explorer, copy the BOOT.bin file from the **image** folder in to the SD/MicroSD card.
### Set the board in SD card boot mode. Test the functionality by starting a Terminal emulator program and powering ON the board.
1. Set the board in the SD card boot mode.
1. Insert the SD/MicroSD card into the board.
1. Power ON the board.
1. Connect your PC to the UART port with the provided micro-USB cable, and start Terminal or SDK Terminal in SDK or a Terminal emulator program setting it to the current COM port and 115200 baudrate.
1. You should see the **Hello World** message in the terminal emulator window.  If you don&#39;t see it, then press the PS\_RST/PS\_SRST button on the board.
1. Once satisfied power OFF the board and remove the SD card.
### Set the board in the QSPI boot mode.  Power ON the board, Program the QSPI using the Flash Writer utility, and test by pressing PS-RST button.
1. Set the board in the QSPI mode.
1. Power ON the board.
1. Connect your PC to the UART port with the provided micro-USB cable, and start a Terminal emulator program setting it to the current COM port and an 115200 baud rate.
1. Select **Xilinx &gt; Program Flash**.
1. In the _Program Flash Memory_ form, click the **Browse** button of the Image File field, browse to the **{labs}\lab5\image** directory, select **BOOT.bin** file, and click **Open**.
1. Click on the FSBL File Browse button, browse to **{labs}\lab5\lab5.sdk\zynq\_fsbl\Debug** directory (this is where the FSBL was created), select _zynq\_fsbl.elf_ and click **Open**.
1. In the _Offset_ field enter **0** as the offset and click the **Program** button.

    The QSPI flash will be programmed.

    <p align="center">
    <img src ="./images/lab5/Fig5.png" width="60%" height="80%"/>
    </p>
    <p align = "center">
    <i>Program Flash Memory form</i>
    </p>
1. Disconnect and reconnect the Terminal window.
1. Press the PS-RST to see the **Hello World** message in the terminal emulator window.
1. Once satisfied, power OFF the board.
## Prepare for the Multi-Applications Boot Using SD Card        
### The lab1 and lab3 executable files are required in the .bin format before copying to the SD card. The area in memory allocated for each application need to be modified so that they do not overlap each other, or with the main application. The prepared bin files provided in the directory: {sources}\lab5\[pynqz1 or pynqz2]\SDCard can be used for copying to the SD card. Follow steps in Appendix A-1 and A-2 if you want to generate by yourself.

### Create the lab5\_sd application using the provided lab5\_sd.c and devcfg.c, devcgf.h, load\_elf.s files.
1. Select **File** &gt; **New** &gt; **Application Project.**
1. Enter **lab5\_sd** as the project name, click the _Use existing_ option in the _Board Support Package_ (BSP) field and select _hello\_world\_bsp_, and then click **Next.**
1. Select _Empty Application_ in the **Available Templates** pane and click **Finish**.
1. Select **lab5\_sd &gt; src** in the project view, right-click, and select **Import.**
1. Expand the General folder and double-click on **File system,** and browse to the **{sources}\lab5** directory.
1. Select **devcfg.c, devcfg.h, load\_elf.s** , and **lab5\_sd.c,** and click **Finish.**
1. Change, if necessary, LAB1\_ELFBINFILE\_LEN, LAB3\_ELFBINFILE\_LEN, LAB1\_ELF\_EXEC\_ADDR, LAB3\_ELF\_EXEC\_ADDRvalues and save the file.
## Create the SD Card Image and Test
### Using the Windows Explorer, create the SD\_image directory under the lab5 directory. You will first need to create the bin files from lab1 and lab3.
1. Using the Windows Explorer, create directory called **SD\_image** under the **lab5** directory.
1. In Windows Explorer, copy the **system\_wrapper.bit** of the lab1 project into the _SD\_image_ directory and rename it _lab1.bit_, and do similar for lab3

    {labs}/lab1/lab1.runs/impl\_1/system\_wrapper.bit -&gt; SD\_image /lab1.bit{labs}/lab3/lab3.runs/impl\_1/system\_wrapper.bit -&gt; SD\_image /lab3.bit

    #### The XSDK _bootgen_ command will be used to convert the bit files into the required binary format. bootgen requires a .bif file which has been provided in the sources/lab5 directory. The .bif file specifies the target .bit files.

1. Open a command prompt by selecting **Xilinx &gt; Launch Shell.**
1. In the command prompt window, change the directory to the bitstreams directory.

    cd {labs}/lab5/SD\_image

1. Generate the partial bitstream files in the BIN format using the provided &quot;.bif&quot; file located in the _sources_ directory. Use the following command:

    bootgen -image ..\..\..\2018\_2\_zynq\_sources\lab5\bit\_files.bif -w -process\_bitstream bin

1. Rename the files _lab1.bit.bin_ and _lab3.bit.bin_ to _lab1.bin_ and _lab3.bin_
1. The size of the file needs to match the size specified in the **lab5\_sd.c** file. The size can be determined by checking the file&#39;s properties. If the sizes do not match, then make the necessary change to the source code and save it (The values are defined as LAB1\_BITFILE\_LEN and LAB3\_BITFILE\_LEN).

    <p align="center">
    <img src ="./images/lab5/Fig8.png" width="60%" height="80%"/>
    </p>
    <p align = "center">
    <i>Checking the size of the generate bin file</i>
    </p>
    Note that the lab1.bin and lab3.bin files should be the same size.

### You will create the BOOT.bin file using the first stage bootloader, system\_wrapper.bit and lab5\_sd.elf files.
1. In the SDK, select **Xilinx &gt; Create Boot Image**.
1. For the Output BIF file path, click on the Browse button and browse to **{labs}\lab5\SD\_image** directory and click **Save**.
1. Click on the **Add** button and browse to **{labs}\lab5\lab5.sdk\zynq\_fsbl\debug** , select **zynq\_fsbl.elf** , click **Open** , and click **OK**.
1. Click on the **Add** button of the _boot image partitions_ field and add the bitstream file, **system\_wrapper.bit** , from **{labs}\lab5\lab5.sdk\system\_wrapper\_hw\_platform\_0** and click **OK**
1. Click on the **Add** button of the _boot image partitions_ field and add the software application, **lab5\_sd.elf** , from the **{labs}\lab5\lab5.sdk\lab5\_sd\Debug** directory and click **OK**
1. Click the **Create Image** button.

    The BOOT.bin file will be created in the **lab5\SD\_image** directory.

### Either copy the labxelf.bin files (two) from the sources directory or from the individual directories (if you did the optional part in the previous step and place them in the SD\_image directory. Copy all the bin files to the SD card. Configure the board to boot from SD card. Power ON the board. Test the design functionality
1. In Windows explorer, copy the **lab1elf.bin** and **lab3elf.bin** files either from the **{sources}\lab5\ [pynqz1 or pynz2]\SDCard** directory or from the individual directories (if you did the optional parts in the previous step) and place them in the **SD\_image** directory.

    {labs}\lab1\lab1.sdk\lab1\Debug\lab1elf.bin -&gt; SD\_image
    {labs}\lab3\lab3.sdk\lab3\Debug\lab3elf.bin -&gt; SD\_image

1. Insert a blank SD/MicroSD card (FAT32 formatted) in an SD Card reader, and using the Windows Explorer, copy the two bin files, the two elfbin files, and BOOT.bin from the **SD\_image** folder in to the SD card.
1. Place the SD/MicroSD card in the board, and set the mode pins to boot the board from the SD card. Connect your PC to the UART port with the provided micro-USB cable.
1. Power ON the board.
1. Start the terminal emulator program and follow the menu.  Press the PS\_RST/PS\_SRST button if you don&#39;t see the menu.
1. When finished testing one application, either power cycle the board and verify the second application&#39;s functionality, or press the PS\_RST/PS\_SRST button on the board to display the menu again.
1. When done, power OFF the board.

## Create the QSPI application and image 
### The prepared bin files provided in the directory: {sources}\lab5\[pynqz1 or pynqz2]\QSPI can be used for creating the MCS. Appendix B-1 and B-2 lists the steps of how to create such BIN files.

### Create the lab5\_qspi application using the provided lab5\_qspi.c file.
1. Select **File** &gt; **New** &gt; **Application Project.**
1. Enter **lab5\_qspi** as the project name, select the _Use existing_ option for the Board Support Package, and using the drop-down button select _hello\_world\_bsp_, and click **Next**.
1. Select _Empty Application_ in the **Available Templates** pane and click **Finish**.
1. Select **lab5\_qspi&gt;src** in the project view, right-click, and select **Import.**
1. Expand General folder and double-click on **File system,** and browse to the **{sources}\lab5** directory.
1. Select **lab5\_qspi.c** and click **Finish.**

    The program should compile successfully and generate the lab5\_qspi.elf file.

### Using the Windows Explorer, create the QSPI\_image directory under the lab5 directory. Create the lab5.mcs file using the zynq\_fsbl.elf, system\_wrapper.bit, and lab5\_qspi.elf files (from the lab5 project), lab1.bin (from the lab1 project) and lab3.bin (from the lab3 project).
1. Using the Windows Explorer, create the **QSPI\_image** directory under the **lab5** directory.
1. In the SDK, select **Xilinx &gt; Create Boot Image**.
1. Select **Create new BIF file** option, click the _Browse_ button of the BIF file path field and browse to _{labs}\lab5\QSPI\_image_ directory, select _output.bif_, and click **Save**.
1. Click on the **Add** button of the _Boot image partitions_ window.
1. Click on the _Browse_ button of the _File Path_ field, browse to _{labs}\lab5\lab5.sdk\zynq\_fsbl\Debug, select zynq\_fsbl.elf_, click **Open** , and then click **OK**.
1. Click on the **Add** button of the _boot image partitions_ field and add the bitstream file, **system\_wrapper.bit** , from **{labs}\lab5\lab5.sdk\system\_wrapper\_hw\_platform\_0** and click **OK**
1. Click on the **Add** button again of the _Boot image partition_ field again and add the **lab1.bin** , either of created boot image of the lab1 project (in _{labs}\lab1)_ or from the provided _{sources}\lab5\(pynqz1or pynqz2)\QSPI_ directory. Click **Open**.
1. Enter **0x400000** in the _Offset_ field and click **OK**.
1. Similarly, click on the **Add** button again of the _Boot image partition_ field again and add the **lab3.bin** , either of the created boot image of the lab3 project (in _{labs}\lab3)_ or from the provided _{sources}\lab5\(pynqz1 or pynqz2)\QSPI_ directory. Click **Open**.
1. Enter **0x800000** in the _Offset_ field and click **OK**.
1. Make the window bigger (taller), if necessary, so that you can see the **Output**** path** field,
1. Change the output filename to **lab5.mcs** and the location to _{labs}\lab5\QSPI\_image (if necessary)._
1. Click the **Create Image** button.

    The lab5.mcs file will be created in the **lab5\QSPI\_image** directory.

### Set the board in the QSPI boot mode. Power ON the board.  Program the QSPI using the Flash Writer utility.
1. Set the board in the QSPI mode. Power ON the board.
1. Select **Xilinx &gt; Program Flash**.
1. In the _Program Flash Memory_ form, click the **Browse** button, and browse to the **{labs}\lab5\QSPI\_image** directory, select **lab5.mcs** file, and click **Open**.
    A solution mcs file is provided in the {sources}\lab5\{board}\QSPI directory as lab5.zip, unzip it and use it if you have skipped the previous step of generate QSPI image.
 
1. In the _Offset_ field enter **0** as the offset and click the **Program** button.

    The QSPI flash will be programmed. It may take up to 4 minutes.

## Test the QSPI Multi-Applications        
### Connect to the serial port. Press the PS-SRST button and test the functionality.
1. Start the terminal emulator session and press PS-SRST button to see the menu.
1. Follow the menu and test the functionality of each lab.

    Press 1 to load and execute lab1 or 2 to load and execute lab3.  After each lab is executed, the lab5 gets loaded displaying the menu. Note that lab1 execution terminates when all slide switches are ON (i.e. 0xF) and lab3 execution terminates after it counts from 0 to 15.

1. Once satisfied, power OFF the board.
1. Close SDK and Vivado programs by selecting **File &gt; Exit** in each program.
1. Turn OFF the power on the board.

## Conclusion

This lab led you through creating the boot images which can boot standalone applications from either the SD card or the QSPI flash memory.  You then created the design capable of booting multiple applications and configurations which you developed in the previous labs.

## Appendix A-1
### Start another instance of the SDK program. Open the lab1 project, change the ps7\_ddr\_0 to 0x00200000 and the Size to 0x1FE00000 in the lscript.ld (linker script) file.  Recompile the lab1.c file.  Use objcopy command to convert the elf file into the binary file and note the size of the binary file as well as the program entry point (main()).
1. Start the **SDK** program and browse to the workspace pointing to **{labs}\lab1\lab1.sdk\** and click **OK.**
1. Right-click on the **lab1** project, select the _Generate Linker Script_ option, change the _code, data, heap, and stack_ sections to use the _ps7\_ddr\_0_, and click **Generate**. Click **Yes** to overwrite the linker script.
1. Expand the **lab1 &gt; src** entry in the Project Explorer, and double-click on the **lscript.ld** to open it.

    <p align="center">
    <img src ="./images/lab6/Fig6.png" width="60%" height="80%"/>
    </p>
    <p align = "center">
    <i>Accessing the linker script to change the base address and the size</i>
    </p>
1. In the lscript editor view, change the Base Address of the _ps7\_ddr\_0\_AXI\_BASEADDR_ from **0x00100000** to **0x00200000** , and the Size from **0x1FF00000** to **0x1FE00000**.

    <p align="center">
    <img src ="./images/lab6/Fig7.png" width="60%" height="80%"/>
    </p>
    <p align = "center">
    <i>Changing the Base address and the size</i>
    </p>
1. Press **Ctrl-S** to save the change.

    The program should compile.

1. In the SDK of the **lab1** project, select **Xilinx &gt; Launch Shell** to open the shell session.
1. In the shell window, change the directory to **lab1\Debug** using the **cd** command.
1. Convert the _lab1.elf_ file to _lab1elf.bin_ file by typing the following command.

     **arm-none-eabi-objcopy -O binary lab1.elf lab1elf.bin**

1. Type **ls –l** in the shell window and note the size of the file.  In this case, it is **32776** , which is equivalent to **0x8008** bytes.
1. Determine the entry point &quot;main()&quot; of the program using the following command in the shell window.

     **arm-none-eabi-objdump -S lab1.elf | grep main**

    It should be in the **0x002005b8**.

     **Make a note of these two numbers (length and entry point) as they will be used in the lab5\_sd application.**

1. Close the Shell window.
## Appendix A-2
### Switch the workspace to lab3&#39;s SDK project. Assign all sections to ps7\_ddr\_0 and generate the linker script.  Change the ps7\_ddr\_0 to 0x00600000 and the Size to 0x1FA00000 in the lscript.ld (linker script) file as you did in the previous step.  Recompile the lab3.c file.  Use the objcopy command to convert the elf file into the binary file and note the size of the binary file as well as the program entry point &quot;main()&quot;.

1. In the **SDK** program switch the workspace by selecting **File &gt; Switch Workspace &gt; Other…** and browse to the workspace pointing to **{labs}\lab3\lab3.sdk\** and click **OK.**
1. Right-click on the **lab3** entry, select the _Generate Linker Script_ option, change the _code, data, heap, and stack_ sections to use the _ps7\_ddr\_0_, and generate the linker script.
1. Change the loop bound from _999999_ back to **99999999** in _lab3.c_ and save the file.
1. Expand the **lab3 &gt; src** entry in the Project Explorer, and double-click on the **lscript.ld** to open it.
1. In the lscript editor view, change the Base Address of **ps7\_ddr\_0** from **0x00100000** to **0x00600000** , and the Size from **0x1FF00000** to **0x1FA00000**.
1. Press **Ctrl-S** to save the change.

    The program should compile.

1. In the SDK of the **lab3** project, select **Xilinx &gt; Launch Shell** to open the shell session.
1. In the shell window, change the directory to **lab3\Debug** using the **cd** command.
1. Convert the lab3.elf file to lab3elf.bin file by typing the following command.

     **arm-none-eabi-objcopy -O binary lab3.elf lab3elf.bin**

1. Type **ls –l** in the shell window and note the size of the file.  In this case, it is **32776** again which is equivalent to **0x8008**.
1. Determine the entry point (main()) of the program using the following command in the shell window.

     **arm-none-eabi-objdump -S lab3.elf | grep main**

    It should be in the **0x006005b8**.

     **Make a note of these two numbers (length and entry point) as they will be used in the lab5\_sd application.**

1. Close the shell window.
1. Exit the SDK of lab3.

## Appendix B-1
###This step bring in MULTIBOOT register related code in Lab1. It then convert the lab1  executable file to the required (.bin) format. 

### Start a new SDK session and select lab1.sdk as the workspace. Define MULTIBOOT symbol, create Zynq\_fsbl application, and change the lab1 BSP reference to zynq\_fsbl\_bsp. Create the image using the zynq\_fsbl.elf, system\_wrapper.bit, and lab1.elf files.
1. Start the **SDK** program and browse to the workspace pointing to **{labs}\lab1\lab1.sdk\** and click **OK.**
1. Right-click on the **lab1** entry, select the _C/C++ Build Settings_ option.
1. Select _Symbols_ in the left pane under the _ARM gcc compiler_ group, click the _+_ button on the right, enter **MULTIBOOT** in open form, click **OK** and click **OK** again.

    The application will re-compile as the MULTIBOOT related code is now included.

    <p align="center">
    <img src ="./images/lab6/Fig9.png" width="60%" height="80%"/>
    </p>
    <p align = "center">
    <i>Setting user-defined symbol</i>
    </p>
1. Select **File** &gt; **New** &gt; **Application Project**
1. Enter **zynq\_fsbl** as the project name, select the _Create New_ option with **zynq\_fsbl\_bsp** , and click **Next**.
1. Select _Zynq FSBL_ in the **Available Templates** pane and click **Finish**.
1. Select _lab1_ in the Project Explorer pane, right-click, and select _Change Referenced BSP_.
1. In the displayed form, select _zynq\_fsbl\_bsp_ and click **OK**.

    The lab1 will be re-compiled using the zynq\_fsbl\_bsp.

1. In the SDK, select **Xilinx &gt; Create Boot Image**.
1. Select **Create new BIF file** option, click the _Browse_ button of the BIF file path field and browse to _{labs}\lab1_ directory, set filename as _lab1_, and click **Save**.
1. Add the three files, zynq\_fsbl.elf, system\_wrapper.bit, and lab1.elf with the correct path and order.
1. Change the output filename to **lab1.bin** making sure that the output directory is _lab1._
1. Click the **Create Image** button.

    The lab1.bin will be created in the lab1 directory.

## Appendix B-2
###This step bring in MULTIBOOT register related code in Lab3. It then convert the lab3  executable file to the required (.bin) format. 
### Switch workspace to lab3.sdk directory. Define MULTIBOOT symbol, create Zynq\_fsbl application, and change the lab3 BSP reference to zynq\_fsbl\_bsp. Create the image using the zynq\_fsbl.elf, system\_wrapper.bit, and lab3.elf files and naming it as lab3.bin in the lab3 directory.
1. In the **SDK** program switch the workspace by selecting **File &gt; Switch Workspace &gt; Other…** and browse to the workspace pointing to **{labs}\lab3\lab3.sdk\** and click **OK.**
1. Right-click on the **lab3** entry, select the _C/C++ Build Settings_ option.
1. Select _Symbols_ in the left pane under the _ARM gcc compiler_ group, click the _+_ button on the right, enter **MULTIBOOT** in open form, click **OK** , and click **OK** again.

    The application will re-compile as the MULTIBOOT related code is now included.

1. Select **File** &gt; **New** &gt; **Application Project**
1. Enter **zynq\_fsbl** as the project name, select the _Create New_ option with **zynq\_fsbl\_bsp** , and click **Next**.
1. Select _Zynq FSBL_ in the **Available Templates** pane and click **Finish**.
1. Select _lab3_ in the Project Explorer pane, right-click, and select _Change Referenced BSP_.
1. In the displayed form, select _zynq\_fsbl\_bsp_ and click **OK**.

    The lab3 will be re-compiled using the zynq\_fsbl\_bsp.

1. Select the **lab3** application in the _Project Explorer_ view.
1. In the SDK, select **Xilinx &gt; Create Boot Image**.
1. Select **Create new BIF file** option, click the _Browse_ button of the BIF file path field and browse to _{labs}\lab3_ directory, set filename as _lab3_, and click **Save**.
1. Make sure that the three files, **zynq\_fsbl.elf, system\_wrapper.bit** , and **lab3.elf** file entries are added with the correct path.  Change if necessary.
1. Change the output filename to **lab3.bin** making sure that the output directory is lab3_._
1. Click the **Create Image** button.

    The lab3.bin will be created in the lab3 directory.

1. Close the SDK session.