# Documents

## Problems

### Why MPLAB X doesn't support ICD 2 ?

<https://www.microchip.com/forums/m581917.aspx#615401>

### How to move a project to another place ?

The best way to 'copy' a project as complex as the MLA TCP/IP stack demo app is to right click on the project, select Package. MPLAB X will build the project, open the generated code and make sure there are not any references to missing .h files (not in the project). If there are (there should not be in an MLA project) you will have a chance to add them to the project via a dialog. Then MPLAB X will create a .zip file in the project directory with all the files needed to recreate the project.. It will also show the absolute path to this zip file in the output window. Copy that .zip file and put it wherever you want to have your project. Unzip it. open the project in MPLAB X, and build it...
<https://www.microchip.com/forums/m836451.aspx>

### Links

Compiler XC16, XC32:
<https://www.microchip.com/mplab/compilers>

Example:
<https://github.com/rbuj/explorer16>

Microchip libraries for application
<https://www.microchip.com/mplab/microchip-libraries-for-applications#>

TCP/IP project with Explorer 16 + PICTail Plus Ethernet
<http://www.ljcv.net/projects/exp16/index.html>

Setting MCC Code Configurator
<https://microchipdeveloper.com/mplabx:mcc>
