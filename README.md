# KiCAD FreeCAD TechDraw Template Generator
This small and crudely programmed Python script creates drawing sheet templates for FreeCAD and KiCAD that are mostly identical.
## Aims
The aim of this Projekt was to create a unified template for KiCAD and FreeCAD TechDraw. The template is near the Standrats of ISO 5457 for the general Layout, ISO 7200 for the Titelblock, ASME Y14.35 for the optional Revision history and DIN 824 for the optional folding lines. For the font the osifont (https://github.com/hikikomori82/osifont) and for the DXF the iso font was used.
##  Usage
For using this script you need the following python library's:
- pyside2
- svgwrite
- ezdxf
- reportlab
You also should install the osifont: https://github.com/hikikomori82/osifont
After you installed you run the mainwindow.py with python 3(I tested it with 3.6.15 on opensuse 15.2)
## Styles
- ISO5457 ISO700 A, the text height of the legend/field description is 1.8mm and the normal text of the fields is 2.5mm except for the Titel and Legal Owner those are 5mm
- ISO5457 ISO700 B, the text height of the legend/field description is 2.5mm and the normal text of the fields is 3.5mm except for the Titel and Legal Owner those are 7mm (only two Titel and Legal Owner lines except for 3 that are in the A version, the date and other field may not fit and in KICAD the standard field text size is 1.27mm and the 1.8 from the A version is closer to that)
## Limitations
### KiCAD
- Not able to change the font(with 7(6.99) posable)
- text height is not he same as the real height(with 7(6.99) posable)

### FreeCAD
- SVG text height is not he same as the real height

### PDF
- The text in the editable(form) is not centered if needed and a other font