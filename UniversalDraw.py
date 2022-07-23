import svgwrite
from svgwrite import cm, mm
from svgwrite.data.types import SVGAttribute
from FreeCADTemplate import FreeCADTemplateSVG

from KiCADTemplate import KiCAD5Template
from KiCADTemplate import KiCAD6Template
from KiCADTemplate import KiCAD7Template
1
import ezdxf
from ezdxf import units

class UniversalDraw:
    FILENAME = 'export'
    SIZE = (0, 0)
    KICAD5 = None
    KICAD6 = None
    KICAD7 = None
    FREECAD = FreeCADTemplateSVG()
    FREECAD_GROUP_SHEET_BORDER = None
    FREECAD_GROUP_TITLEBLOCK_STRUCTURE = None
    FREECAD_GROUP_TITLEBLOCK_TEXT_EDITABLE = None
    FREECAD_GROUP_TITLEBLOCK_TEXT_NON_EDITABLE = None
    SVG = None
    SVG_GROUP_SHEET_BORDER = None
    SVG_GROUP_TITLEBLOCK_STRUCTURE = None
    SVG_GROUP_TITLEBLOCK_TEXT_EDITABLE = None
    SVG_GROUP_TITLEBLOCK_TEXT_NON_EDITABLE = None
    DXF = None
    DXF_MSP = None
    def __init__(self, size = (100, 100), filename = 'export'):
        self.SIZE = size
        self.FILENAME = filename
        self.KICAD5 = KiCAD5Template(filename = filename + '_5.kicad_wks', size = size, linewidth = 0.35, left_margin = 0, right_margin = 0, top_margin = 0, bottom_margin = 0)  # No margins so that the 0 is at the same point as the others
        self.KICAD6 = KiCAD6Template(filename = filename + '_6.kicad_wks', size = size, linewidth = 0.35, left_margin = 0, right_margin = 0, top_margin = 0, bottom_margin = 0)  # No margins so that the 0 is at the same point as the others
        self.KICAD7 = KiCAD7Template(filename = filename + '_7.kicad_wks', size = size, linewidth = 0.35, left_margin = 0, right_margin = 0, top_margin = 0, bottom_margin = 0)  # No margins so that the 0 is at the same point as the others
        self.FREECAD = FreeCADTemplateSVG(filename + '.freecad.svg', profile='full', size=(size[0]*mm, size[1]*mm), debug=False)
        self.SVG = svgwrite.Drawing(filename= filename + '.svg', size=(size[0]*mm, size[1]*mm), debug=False)

        self.FREECAD_GROUP_SHEET_BORDER = self.FREECAD.g(id='sheet-border')
        self.FREECAD_GROUP_TITLEBLOCK_STRUCTURE = self.FREECAD.g(id='titleblock-structure')
        self.FREECAD_GROUP_TITLEBLOCK_TEXT_EDITABLE = self.FREECAD.g(id='titleblock-text-editable')
        self.FREECAD_GROUP_TITLEBLOCK_TEXT_NON_EDITABLE = self.FREECAD.g(id='titleblock-text-non-editable')

        self.SVG_GROUP_SHEET_BORDER = self.SVG.g(id='sheet-border')
        self.SVG_GROUP_TITLEBLOCK_STRUCTURE = self.SVG.g(id='titleblock-structure')
        self.SVG_GROUP_TITLEBLOCK_TEXT_EDITABLE = self.SVG.g(id='titleblock-text-editable')
        self.SVG_GROUP_TITLEBLOCK_TEXT_NON_EDITABLE = self.SVG.g(id='titleblock-text-non-editable')


        # Create a new DXF document.
        self.DXF = ezdxf.new('R2010', setup=True)
        # Set centimeter as document/modelspace units
        self.DXF.units = units.MM
        # which is a shortcut (including validation) for
        self.DXF.header['$INSUNITS'] = units.MM

        self.DXF_MSP = self.DXF.modelspace();
        self.DXF.styles.new('osifont', dxfattribs={'font' : 'osifont.ttf'})

    def __del__(self):
        self.FREECAD.add(self.FREECAD_GROUP_SHEET_BORDER)
        self.FREECAD.add(self.FREECAD_GROUP_TITLEBLOCK_STRUCTURE)
        self.FREECAD.add(self.FREECAD_GROUP_TITLEBLOCK_TEXT_EDITABLE)
        self.FREECAD.add(self.FREECAD_GROUP_TITLEBLOCK_TEXT_NON_EDITABLE)
        self.FREECAD.save()

        self.SVG.add(self.SVG_GROUP_SHEET_BORDER)
        self.SVG.add(self.SVG_GROUP_TITLEBLOCK_STRUCTURE)
        self.SVG.add(self.SVG_GROUP_TITLEBLOCK_TEXT_EDITABLE)
        self.SVG.add(self.SVG_GROUP_TITLEBLOCK_TEXT_NON_EDITABLE)
        self.SVG.save()
        self.DXF.saveas(self.FILENAME + '.dxf')

    def line(self, start=(0, 0), end=(10, 0), linewidth = 0.15, color = '#000000', group = "nogroupe"):
        self.KICAD5.line(start = start, end = end, linewidth = linewidth);
        self.KICAD6.line(start = start, end = end, linewidth = linewidth);
        self.KICAD7.line(start = start, end = end, linewidth = linewidth);
        fObj = self.FREECAD.line(start = (start[0], start[1]), end = (end[0], end[1]), stroke_width = linewidth*mm, style = 'stroke:' + color + ';stroke-linecap:miter;stroke-miterlimit:4;fill:none')
        sObj = self.SVG.line(start = (start[0]*mm, start[1]*mm), end = (end[0]*mm, end[1]*mm), stroke_width = linewidth*mm, style = 'stroke:' + color + ';stroke-linecap:miter;stroke-miterlimit:4;fill:none')
        self.DXF_MSP.add_line((start[0], (self.SIZE[1] - start[1])), (end[0], (self.SIZE[1] - end[1])), dxfattribs={"color": 7, "lineweight":(linewidth*100)});

        if group == 'sheet-border':
            self.FREECAD_GROUP_SHEET_BORDER.add(fObj)
            self.SVG_GROUP_SHEET_BORDER.add(sObj)
        elif group == 'titleblock-structure':
            self.FREECAD_GROUP_TITLEBLOCK_STRUCTURE.add(fObj)
            self.SVG_GROUP_TITLEBLOCK_STRUCTURE.add(sObj)
        elif group == 'titleblock-text-editable':
            self.FREECAD_GROUP_TITLEBLOCK_TEXT_EDITABLE.add(fObj)
            self.SVG_GROUP_TITLEBLOCK_TEXT_EDITABLE.add(sObj)
        elif group == 'titleblock-text-non-editable':
            self.FREECAD_GROUP_TITLEBLOCK_TEXT_NON_EDITABLE.add(fObj)
            self.SVG_GROUP_TITLEBLOCK_TEXT_NON_EDITABLE.add(sObj)
        else:
            self.FREECAD.add(fObj)
            self.SVG.add(sObj)



    def rect(self, start=(0, 0), end=(0, 0), linewidth = 0.15, color = '#000000', group = "nogroupe"):
        self.KICAD5.rect(start = start, end = end, linewidth = linewidth)
        self.KICAD6.rect(start = start, end = end, linewidth = linewidth)
        self.KICAD7.rect(start = start, end = end, linewidth = linewidth)
        fObj = self.FREECAD.rect(insert = (start[0], start[1]), size = ((end[0]-start[0]), (end[1]-start[1])), style = 'stroke:' + color + ';stroke-linecap:miter;stroke-width:' + str(linewidth) + 'mm;stroke-miterlimit:4;fill:none')
        sObj = self.SVG.rect(insert = (start[0]*mm, start[1]*mm), size = ((end[0]-start[0])*mm, (end[1]-start[1])*mm), style = 'stroke:' + color + ';stroke-linecap:miter;stroke-width:' + str(linewidth) + 'mm;stroke-miterlimit:4;fill:none')

        self.DXF_MSP.add_line((start[0], (self.SIZE[1] - start[1])), (start[0], (self.SIZE[1] - end[1])), dxfattribs={"color": 7, "lineweight":(linewidth*100)});
        self.DXF_MSP.add_line((start[0], (self.SIZE[1] - end[1])),   (end[0], (self.SIZE[1] - end[1])), dxfattribs={"color": 7, "lineweight":(linewidth*100)});
        self.DXF_MSP.add_line((end[0], (self.SIZE[1] - end[1])),     (end[0], (self.SIZE[1] - start[1])), dxfattribs={"color": 7, "lineweight":(linewidth*100)});
        self.DXF_MSP.add_line((end[0], (self.SIZE[1] - start[1])),   (start[0], (self.SIZE[1] - start[1])), dxfattribs={"color": 7, "lineweight":(linewidth*100)});

        if group == 'sheet-border':
            self.FREECAD_GROUP_SHEET_BORDER.add(fObj)
            self.SVG_GROUP_SHEET_BORDER.add(sObj)
        elif group == 'titleblock-structure':
            self.FREECAD_GROUP_TITLEBLOCK_STRUCTURE.add(fObj)
            self.SVG_GROUP_TITLEBLOCK_STRUCTURE.add(sObj)
        elif group == 'titleblock-text-editable':
            self.FREECAD_GROUP_TITLEBLOCK_TEXT_EDITABLE.add(fObj)
            self.SVG_GROUP_TITLEBLOCK_TEXT_EDITABLE.add(sObj)
        elif group == 'titleblock-text-non-editable':
            self.FREECAD_GROUP_TITLEBLOCK_TEXT_NON_EDITABLE.add(fObj)
            self.SVG_GROUP_TITLEBLOCK_TEXT_NON_EDITABLE.add(sObj)
        else:
            self.FREECAD.add(fObj)
            self.SVG.add(sObj)

    def polygon(self, position = (0, 0), linewidth = 0, points = [(0, 0), (10, 0), (10, 5), (5, 5), (5, 10), (0, 10), (0, 0)], color = '#000000', fill = 'none', group = "nogroupe"):
        points_offset = []
        for p in points:
            x = (p[0] + position[0])
            y = (p[1] + position[1])
            points_offset.append((x, y))

        points_offset_svg = []
        for p in points:
            x = (p[0] + position[0])*mm
            y = (p[1] + position[1])*mm
            points_offset_svg.append((x, y))

        points_offset_dxf = []
        for p in points:
            x = (p[0] + position[0])
            y = (self.SIZE[1] - (p[1] + position[1]))
            points_offset_dxf.append((x, y))

        hatch = self.DXF_MSP.add_hatch(dxfattribs={"color": 7});
        hatch.paths.add_polyline_path(points_offset_dxf, is_closed=True)
        self.KICAD5.polygon(position = (0, 0), rotation = 0, linewidth = linewidth, points = points_offset)
        self.KICAD6.polygon(position = (0, 0), rotation = 0, linewidth = linewidth, points = points_offset)
        self.KICAD7.polygon(position = (0, 0), rotation = 0, linewidth = linewidth, points = points_offset)
        fObj = self.FREECAD.polygon(points = points_offset, style = 'stroke:' + color + ';stroke-width:' + str(linewidth) + 'mm;stroke-linecap:miter;stroke-miterlimit:4;fill:' + fill + '')
        sObj = self.SVG.polygon(points = points_offset, style = 'stroke:' + color + ';stroke-width:' + str(linewidth) + 'mm;stroke-linecap:miter;stroke-miterlimit:4;fill:' + fill + '', transform="scale(3.7795)")

        if group == 'sheet-border':
            self.FREECAD_GROUP_SHEET_BORDER.add(fObj)
            self.SVG_GROUP_SHEET_BORDER.add(sObj)
        elif group == 'titleblock-structure':
            self.FREECAD_GROUP_TITLEBLOCK_STRUCTURE.add(fObj)
            self.SVG_GROUP_TITLEBLOCK_STRUCTURE.add(sObj)
        elif group == 'titleblock-text-editable':
            self.FREECAD_GROUP_TITLEBLOCK_TEXT_EDITABLE.add(fObj)
            self.SVG_GROUP_TITLEBLOCK_TEXT_EDITABLE.add(sObj)
        elif group == 'titleblock-text-non-editable':
            self.FREECAD_GROUP_TITLEBLOCK_TEXT_NON_EDITABLE.add(fObj)
            self.SVG_GROUP_TITLEBLOCK_TEXT_NON_EDITABLE.add(sObj)
        else:
            self.FREECAD.add(fObj)
            self.SVG.add(sObj)

    #                                                                                                                          middle                middle
    def text(self, text = "Dummy text", position = (0, 0), tsize = 0, linewidth = 0.15, color = '#000000', heightAnchor = 'start', widthAnchor = 'start', group = "nogroupe"):
        if heightAnchor == 'middle':
            posHeightSVG = position[1] + ((tsize*(3/10))/3)
        elif heightAnchor == 'top':
            posHeightSVG = position[1] + tsize
        else:
            posHeightSVG = position[1]

        if heightAnchor == 'middle':
            posHeightFeecad = position[1] + ((tsize*(3/10))) + ((tsize*(3/10))/3)
        elif heightAnchor == 'top':
            posHeightFeecad = position[1] + tsize
        else:
            posHeightFeecad = position[1]


        anchor = ''
        anchorI = 0
        posDXF = (position[0], (self.SIZE[1] - (position[1])))
        if heightAnchor == 'start' and widthAnchor == 'start':
            posDXF = ((position[0] + .6), (self.SIZE[1] - (position[1] + 1.12)))
            anchor = 'BOTTOM_LEFT'
            anchorI = 7
        elif heightAnchor == 'middle' and widthAnchor == 'start':
            posDXF = ((position[0] + .6), (self.SIZE[1] - (position[1] + 1.12)))
            anchor = 'MIDDLE_LEFT'
            anchorI = 4
        elif heightAnchor == 'start' and widthAnchor == 'middle':
            anchor = ' BOTTOM_CENTER'
            anchorI = 8
        elif heightAnchor == 'middle' and widthAnchor == 'middle':
            anchor = 'MIDDLE_CENTER'
            anchorI = 5

        if text.find('\n') >= 0:
            letters =  text.split('\n')
            sObj = self.SVG.text('', insert=(position[0]*mm, posHeightSVG*mm), font_size=str((tsize + (tsize*(3/10)))*mm), fill=color, style='text-anchor:' + widthAnchor + ';dominant-baseline:' + heightAnchor + ';font-family:osifont')
            lIndex = 0
            for l in letters:
                #sObj = self.SVG.text(text, insert=(position[0]*mm, posHeightSVG*mm), font_size=str((tsize + (tsize*(3/10)))*mm), fill=color, style='text-anchor:' + widthAnchor + ';dominant-baseline:' + heightAnchor + ';font-family:osifont')
                if lIndex < len(letters)/2:
                    sObj.add(self.SVG.tspan(l.replace('\n', ''), insert=(position[0]*mm, (posHeightSVG - (tsize*(3/10) + tsize/2))*mm)))
                elif lIndex >= (len(letters)/2):
                    sObj.add(self.SVG.tspan(l.replace('\n', ''), insert=(position[0]*mm, (posHeightSVG + (tsize*(3/10) + tsize/2))*mm)))
                lIndex += 1
        else:
            sObj = self.SVG.text(text, insert=(position[0]*mm, posHeightSVG*mm), font_size=str((tsize + (tsize*(3/10)))*mm), fill=color, style='text-anchor:' + widthAnchor + ';dominant-baseline:' + heightAnchor + ';font-family:osifont')

        if text != '%D':
            self.KICAD5.text(text = text, position = (position[0] - 0.3, position[1]), size = (tsize - 0.5, tsize - 0.5), linewidth = linewidth, heightAnchor = heightAnchor, widthAnchor = widthAnchor)
            self.KICAD6.text(text = text, position = (position[0] - 0.3, position[1]), size = (tsize - 0.5, tsize - 0.5), linewidth = linewidth, heightAnchor = heightAnchor, widthAnchor = widthAnchor)
        else:
            self.KICAD5.text(text = text, position = (position[0] - 0.3, position[1]), size = (tsize - 1, tsize - 1), linewidth = linewidth, heightAnchor = heightAnchor, widthAnchor = widthAnchor)
            self.KICAD6.text(text = text, position = (position[0] - 0.3, position[1]), size = (tsize - 1, tsize - 1), linewidth = linewidth, heightAnchor = heightAnchor, widthAnchor = widthAnchor)
        
        self.KICAD7.text(text = text, position = (position[0], position[1]), size = (tsize,tsize), linewidth = linewidth, heightAnchor = heightAnchor, widthAnchor = widthAnchor)
        
        self.DXF_MSP.add_mtext(text, dxfattribs={"color": 7, "lineweight":(linewidth*100), 'char_height': (tsize),'style': 'iso', 'insert': posDXF, 'attachment_point': anchorI})#.set_pos(posDXF, align=anchor)

        if group == 'titleblock-text-editable':
            if text.find('\n') >= 0:
                letters =  text.split('\n')
                #fObj = self.FREECAD.text_editable('', insert=(position[0], posHeightFeecad), font_size=str((tsize + (tsize*(3/10)))), fill=color, style='text-anchor:' + widthAnchor + ';dominant-baseline:' + heightAnchor + ';font-family:osifont')
                fObj = self.FREECAD.g()
                lIndex = 0
                for l in letters:
                    #sObj = self.SVG.text(text, insert=(position[0]*mm, posHeightSVG*mm), font_size=str((tsize + (tsize*(3/10)))*mm), fill=color, style='text-anchor:' + widthAnchor + ';dominant-baseline:' + heightAnchor + ';font-family:osifont')
                    if lIndex < len(letters)/2:
                        fObj.add(self.FREECAD.text_editable(l, insert=(position[0], (posHeightFeecad - (tsize*(3/10) + tsize/2))), font_size=str((tsize + (tsize*(3/10)))), fill=color, style='text-anchor:' + widthAnchor + ';dominant-baseline:' + heightAnchor + ';font-family:osifont'))#self.SVG.tspan(l.replace('\n', ''), insert=(position[0], (posHeightFeecad - (tsize*(3/10) + tsize/2)))))
                    elif lIndex >= (len(letters)/2):
                        fObj.add(self.FREECAD.text_editable(l, insert=(position[0], (posHeightFeecad + (tsize*(3/10) + tsize/2))), font_size=str((tsize + (tsize*(3/10)))), fill=color, style='text-anchor:' + widthAnchor + ';dominant-baseline:' + heightAnchor + ';font-family:osifont'))
                    lIndex += 1
            else:
                fObj = self.FREECAD.text_editable(text, insert=(position[0], posHeightFeecad), font_size=str(tsize + (tsize*(3/10))), fill=color, style='text-anchor:' + widthAnchor + ';dominant-baseline:' + heightAnchor + ';font-family:osifont')
        else:
            if text.find('\n') >= 0:
                letters =  text.split('\n')
                #fObj = self.FREECAD.text('', insert=(position[0], posHeightFeecad), font_size=str((tsize + (tsize*(3/10)))), fill=color, style='text-anchor:' + widthAnchor + ';dominant-baseline:' + heightAnchor + ';font-family:osifont')
                fObj = self.FREECAD.g()
                lIndex = 0
                for l in letters:
                    #sObj = self.SVG.text(text, insert=(position[0]*mm, posHeightSVG*mm), font_size=str((tsize + (tsize*(3/10)))*mm), fill=color, style='text-anchor:' + widthAnchor + ';dominant-baseline:' + heightAnchor + ';font-family:osifont')
                    if lIndex < len(letters)/2:
                        fObj.add(self.FREECAD.text(l, insert=(position[0], (posHeightFeecad - (tsize*(3/10) + tsize/2))), font_size=str((tsize + (tsize*(3/10)))), fill=color, style='text-anchor:' + widthAnchor + ';dominant-baseline:' + heightAnchor + ';font-family:osifont'))#self.SVG.tspan(l.replace('\n', ''), insert=(position[0], (posHeightFeecad - (tsize*(3/10) + tsize/2)))))
                    elif lIndex >= (len(letters)/2):
                        fObj.add(self.FREECAD.text(l, insert=(position[0], (posHeightFeecad + (tsize*(3/10) + tsize/2))), font_size=str((tsize + (tsize*(3/10)))), fill=color, style='text-anchor:' + widthAnchor + ';dominant-baseline:' + heightAnchor + ';font-family:osifont'))
                    lIndex += 1
            else:
                fObj = self.FREECAD.text(text, insert=(position[0], posHeightFeecad), font_size=str(tsize + (tsize*(3/10))), fill=color, style='text-anchor:' + widthAnchor + ';dominant-baseline:' + heightAnchor + ';font-family:osifont')

        if group == 'sheet-border':
            self.FREECAD_GROUP_SHEET_BORDER.add(fObj)
            self.SVG_GROUP_SHEET_BORDER.add(sObj)
        elif group == 'titleblock-structure':
            self.FREECAD_GROUP_TITLEBLOCK_STRUCTURE.add(fObj)
            self.SVG_GROUP_TITLEBLOCK_STRUCTURE.add(sObj)
        elif group == 'titleblock-text-editable':
            self.FREECAD_GROUP_TITLEBLOCK_TEXT_EDITABLE.add(fObj)
            self.SVG_GROUP_TITLEBLOCK_TEXT_EDITABLE.add(sObj)
        elif group == 'titleblock-text-non-editable':
            self.FREECAD_GROUP_TITLEBLOCK_TEXT_NON_EDITABLE.add(fObj)
            self.SVG_GROUP_TITLEBLOCK_TEXT_NON_EDITABLE.add(sObj)
        else:
            self.FREECAD.add(fObj)
            self.SVG.add(sObj)
