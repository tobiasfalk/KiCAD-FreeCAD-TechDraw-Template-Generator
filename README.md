# KiCAD FreeCAD TechDraw Template Generator

This small and crudely programmed Qt Program creates drawing sheet templates for [FreeCAD](https://freecad.org) and [KiCAD](https://kicad.org) that are mostly identical.

## Aims

The aim of this Project was to create a unified template for KiCAD and FreeCAD TechDraw. The template is similar to the ISO 5457 standard for the general layout; ISO 7200 for the Titelblock; ASME Y14.35 for the optional revision history; and DIN 824 for the optional folding lines. 

For the font [osifont](https://github.com/hikikomori82/osifont) was used. ISO font was used for DXF.

## Prerequisites

* Qt 6.5 or newer
* [Osifont](https://github.com/hikikomori82/osifont)

# Features

## Styles

### Frames

* Plain
![Plain Frame](/Doc/Img/Frame_Plain.png)

## Limitations

### KiCAD 8

* No Circlys(Used for Projektion)

### FreeCAD

* SVG text height is not the same as the real height

### PDF
This is mostly meant for printing as a template for hand drawing.

* Qt includes random spaces under Windows


## Variable Docu

## Reference/Link Colection

* [FreeCAD Templates Src on Git](https://github.com/FreeCAD/FreeCAD/tree/main/src/Mod/TechDraw/Templates)
* [FreeCAD Template HowTo](https://wiki.freecad.org/TechDraw_TemplateHowTo#Remove_transformans_on_the_SVG)
* [KiCAD PI Editor Doc](https://docs.kicad.org/8.0/en/pl_editor/pl_editor.html)
* [KiCAD Work Sheet File Format](https://dev-docs.kicad.org/en/file-formats/sexpr-worksheet/)
* [KiCAD EESchema Doc Sheet Titleblock](https://docs.kicad.org/8.0/en/eeschema/eeschema.html#sheet-title-block)
* [KiCAD EESchema Doc Text Variables](https://docs.kicad.org/8.0/en/eeschema/eeschema.html#text-variables)
* [KiCAD Doc Schematic Sheet Setup](https://docs.kicad.org/8.0/en/getting_started_in_kicad/getting_started_in_kicad.html#schematic_sheet_setup)
* [KiCAD Doc Board Setup and Stackup](https://docs.kicad.org/8.0/en/getting_started_in_kicad/getting_started_in_kicad.html#board_setup_and_stackup)


### Titleblock
* [FreeCAD Forum Thread "TechDraw's ISO 7200 templates don't conform to ISO 7200 (or ISO 5457)"](https://forum.freecad.org/viewtopic.php?t=85519)
* (done, and example out of the standard)Leiterplatten Stromlaufplan, Layout und Fertigung from Geral Zickert, Publisht from Hanser Fachbuch, page:29(ISBN: 978-3-446-47583-0)
* Tabellenbuch für Metalltechnik from ing. Adof Frischherz, Publisht from Jugend & Volk, page: 46(ISBN: 978-3-7100-2503-7)
* (done, and example out of the standard)Mechanical and metal trades handbook from Gomeringer Roland, Heinzler Max, .., Published from Euro-Lehrmittle, page: 66 (ISBN: 978-3-8085-1915-8)
* Friedrich Tabellenbuch Metall- und Maschinentechnik from Barthel Maria, ..., Published from Bildungsverlag EINS - westermann, page 5-11(ISBN: 978-3-427-51033-8)
* [Wikipedia ISO 7200 Titleblock](https://en.wikipedia.org/wiki/File:Title_block_EN_ISO_7200.svg)
* [Wikipedia ISO 7200 German](https://de.wikipedia.org/wiki/ISO_7200)
* [Wikipedia DIN 6771 German](https://de.wikipedia.org/wiki/DIN_6771)
* [Newton World, basic elements of engineering drawings](https://newtonianworld.com/mechanical-design-engineering-topics/engineering-drawings/basic-elements-of-engineering-drawings/#elementor-toc__heading-anchor-7)(may relode/reenter the link to jump to the rigth chapter)

## Logo (Branding)

## Icon Source
The Icon for the app was downloaded from: https://www.flaticon.com/de/kostenloses-icon/layout_7973492

## To do
