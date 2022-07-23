# KiCAD FreeCAD TechDraw Template Generator
This small and crudely programmed Python script creates drawing sheet templates for FreeCAD and KiCAD that are mostly identical.
## Aims
The aim of this Projekt was to create a unified template for KiCAD and FreeCAD TechDraw. The template is near the Standrats of ISO 5457 for the general Layout, ISO 7200 for the titelblock, ASME Y14.35 for the optinal Revision history and DIN 824 for the optional folding lines. For the font the osifont (https://github.com/hikikomori82/osifont) and for the DXF the iso font was used.
##  Usage
For using this script you need the following python library's:
- pyside2
- svgwrite
- ezdxf
You also should install the osifont: https://github.com/hikikomori82/osifont
After you installed you run the mainwindow.py with python 3(I tested it with 3.6.15 on opensuse 15.2)
## Limitations
### KiCAD
- Not able to change the font(with 7(6.99) posable)
- text height is not he same as the real height(with 7(6.99) posable)

### FreeCAD
- SVG text height is not he same as the real height