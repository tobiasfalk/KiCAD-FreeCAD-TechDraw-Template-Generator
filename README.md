# KiCAD FreeCAD TechDraw Template Generator

This small and crudely programmed Qt Program creates drawing sheet templates for [FreeCAD](https://freecad.org) and [KiCAD](https://kicad.org) that are mostly identical.

## Aims

The aim of this Project was to create a unified template for KiCAD and FreeCAD TechDraw. The template is similar to the ISO 5457 standard for the general layout; ISO 7200 for the Titelblock; ASME Y14.35 for the optional revision history; and DIN 824 for the optional folding lines. 

For the font [osifont](https://github.com/hikikomori82/osifont) was used. ISO font was used for DXF.

## Prerequisites

* Qt 5.12 or newer
* [Osifont](https://github.com/hikikomori82/osifont)

# Features

* ISO 5457 style border and ISO 7200 style Titelblock

![ISO 5457 & ISO 7200 image](Images/ISO5457_ISO7200_Demo.freecad.svg)


* ASME Y14.35 style revision history

![ASME Y14.35 image](Images/ASME_Y14-35_Demo.svg)


* Description field

![Description field image](Images/Description_Demo.svg)


* Folding liens to A4 and 200mmx290mm

* Full Sheet Parts list

![Full Sheet list image](Images/FullPartsList_Demo.svg)

* Full Sheet Parts list from CSV

![Full Sheet list image CSV ](Images/CSV_Partslist_Demo.svg)


* Small Parts list directly over the Titelblock

![Small Parts list image](Images/SmallPartsList_Demo.svg)


* Logo inclusion in to the Legal owner field

![Logo image](Images/Logo_Demo.svg)

* CSV inclusion, KiCAD with bom_csv_grouped_by_value_with_fp or Standard where in the first line the size in percentage to the drawing with(0.1 for 10% or 0.5 for 50%). The second line defines the Titel of the column,
all the lines below that are the Parts that are to be drawn


## Usage

![Gui image](Images/Gui.png)

1. Combobox to select presented Sheet sizes
1. The width of the sheet(if preset is selected value is fixed)
1. The height of the sheet(if preset is selected value is fixed)
1. The name of the sheet(if preset is selected value is fixed)
1. Save and load buttons for selected options, like Sheet size field Textes and so on
1. Titelblock style and the button to change the text in the fields
1. Select a SVG for Logo inclusion in to the Legal Owner field, the checkbox is for selecting that it is included, will be toggled automatically when a Logo is selected
1. Color, is not used
1. Trimming marks check box, this activates and deactivates the trimming marks that are drawn in the corners
1. Here you can select how many optional lines you want in the Titelblock
1. Here you can select to draw a description field with a number of specified lines
1. Revision History, hre you can select the Rev. History and select how many revisions you have, you can also change the field text with the button on the right
1. Here you can select to draw folding lines in along the border
1. Full Sheet Part list, this Aktivatem the Full sheet part list and changes the field text,

    in 14a you can set the number of lines on field should have
    
    in 14b you can select a CSV file, select its style and put the text of it in the BOM, the "Standard" style can be found in the examples(Examples/Std_BOM_Example_1.csv), for the KiCAD Style you need to export your BOM with the "bom_csv_grouped_by_value_with_fp" script
1. Small Parts list, same as Full Sheet Parts list with the extra option of 15b that sets the number of parts
1. Generate Button, this opens a file dialog where you select the saving destination of the multiple templates
1. KiCAD scaler, this is a small function which helps to scale a KiCAD Symbol Library
1. Is for manually updating the preview and is in normal use not needed, you could also say it is a relict of the development of the preview
1. Is the Preview, it updates every time you change a property of the sheet

## Styles
- ISO5457 ISO700

## Limitations

### KiCAD 5

* Not able to change the font (with 7(6.99) possible)
* No Circlys(Used for Projektion)

### KiCAD 6

* Not able to change the font (with 7(6.99) possible)
* No Circlys(Used for Projektion)

### KiCAD 7

* No Circlys(Used for Projektion)

### FreeCAD

* SVG text height is not the same as the real height

### PDF
This is mostly meant for printing as a template for hand drawing.

* The text in the "editable fields" is not editable
* The logo inclusion si not working(it draws a rectangle there where the logo should be)
* Qt includes random spaces under Windows

### Eagle 6.5 

* No logo inclusion.
* The text in the "editable fields" is not editable and need to be set before generation(in the FreeCAD Fileds)
* No osifont

## Variable Docu

* `&{N}` Number of repetition, see Rev. History
* `&{F}` Field number, see the partslists

## Logo (Branding)

It is possible to include a Logo in the Legal owner Field (name can be modified). This is meant for a company logo or brand. The specification for the logo: 

* SVG format
* maximum width is 24mm
* the checkbox on the right side of the button needs to be checked (will be checked after clicking it). 
* the location is on the right bottom side of the Legal owner field of the Titleblock 
 
**Notes**  
Once the logo gets reaches a height of 30mm the width is reduced (the ratio will be kept). If text is included in the SVG it may create problems, so convert that to path.

## Icon Source
The Icon for the app was downloaded from: https://www.flaticon.com/de/kostenloses-icon/layout_7973492

## To do

* Complete Doxygen Documentation
* PDF Text problems
