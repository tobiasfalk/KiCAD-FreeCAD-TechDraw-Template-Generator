# KiCAD FreeCAD TechDraw Template Generator
This small and crudely programmed Python script creates drawing sheet templates for FreeCAD and KiCAD that are mostly identical.
## Aims
The aim of this Projekt was to create a unified template for KiCAD and FreeCAD TechDraw. The template is near the Standrats of ISO 5457 for the general Layout, ISO 7200 for the Titelblock, ASME Y14.35 for the optional Revision history and DIN 824 for the optional folding lines. For the font the osifont (https://github.com/hikikomori82/osifont) and for the DXF the iso font was used.
##  Usage
- Qt
You also should install the osifont: https://github.com/hikikomori82/osifont
## Styles
- ISO5457 ISO700
## Limitations
### KiCAD 5
- Not able to change the font(with 7(6.99) posable)

### KiCAD 6
- Not able to change the font(with 7(6.99) posable)

### KiCAD 7(6.99)

### FreeCAD(To be done)
- SVG text height is not he same as the real height

### PDF(To be done)
- The text in the editable(form) is not centered if needed and a other font

### Eagle 6.5(To be done)

## Variable Docu
- &{N} Number of repition, see Rev. History
- &{F} Field number, see the partslists

## Logo inclutions
It is posible to include a Logo in the Legal owner Field(name can be changed), this is ment for a Company Logo or somthing like this. The logo needs to be provided as SVG and the checkbox on the right site of the button needs to be checkt(will be checket after clicking it). The location is on the right bottom site of the Legal owner field of the Titelblock and th maximum width is 24mm, the moment the logo gets to a height of 30mm the width is reduced(the ratio will be keept).
