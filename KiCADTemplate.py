# This Python file uses the following encoding: utf-8

# All coordinats ar(width, heigth)
# All units are in mm
# the polygon rotation is counterclockwise

class KiCAD5Template:
    FILE = None
    SEGM_COUNTER = 1
    RECT_COUNTER = 1
    POLY_COUNTER = 1
    TEXT_COUNTER = 1
    def __init__(self,filename = 'noname_5.kicad_wks', size = ('100%', '100%'), linewidth = 0.15, left_margin = 20, right_margin = 10, top_margin = 10, bottom_margin = 10):
        self.FILE = open(filename, 'w')
        self.FILE.write('(page_layout\n')
        self.FILE.write('  (setup (textsize 1.5 1.5)(linewidth ' + str(linewidth) + ')(textlinewidth 0.15)\n')
        self.FILE.write('  (left_margin ' + str(left_margin) + ')(right_margin ' + str(right_margin) + ')(top_margin ' + str(top_margin) + ')(bottom_margin ' + str(bottom_margin) + '))\n')
        pass

    def __del__(self):
        self.FILE.write(')')
        self.FILE.close

    def line(self, name = 'noName', start=(0, 0), end=(0, 0), linewidth = 0.15):
        if(name == 'noName'):
            name = 'segm' + str(self.SEGM_COUNTER) + ':Line'
            self.SEGM_COUNTER += 1
        self.FILE.write('  (line (name ' + name + ') (start ' + str(start[0]) + ' ' + str(start[1]) + ' ltcorner) (end ' + str(end[0]) + ' ' + str(end[1]) + ' ltcorner) (linewidth ' + str(linewidth) + '))\n')

    def rect(self, name = 'noName', start=(0, 0), end=(0, 0), linewidth = 0.15):
        if(name == 'noName'):
            name = 'rect' + str(self.RECT_COUNTER) + ':Rect'
            self.RECT_COUNTER += 1
        self.FILE.write('  (rect (name ' + name + ') (start ' + str(start[0]) + ' ' + str(start[1]) + ' ltcorner) (end ' + str(end[0]) + ' ' + str(end[1]) + ' ltcorner) (linewidth ' + str(linewidth) + '))\n')

    def polygon(self, name = 'noname', position = (0, 0), rotation = 0, linewidth = 0.15, points = [(0, 0), (10, 0), (10, 5), (5, 5), (5, 10), (0, 10), (0, 0)]):
        if(name == 'noName'):
            name = 'poly' + str(self.POLY_COUNTER) + ':Poly'
            self.POLY_COUNTER += 1
        self.FILE.write('  (polygon (name ' + name + ') (pos ' + str(position[0]) + ' ' + str(position[1]) + ' ltcorner) (rotate ' + str(rotation) + ') (linewidth ' + str(linewidth) + ')\n')

        #points
        self.FILE.write('    (pts')
        #loop
        for p in points:
            self.FILE.write(' (xy ' + str(p[0]) + ' ' + str(p[1]) + ')')
        self.FILE.write(')\n')

        self.FILE.write('  )\n')

    #                                                                                                                        middle                 middle
    def text(self, text = "Dummy text", name = 'noname', position = (0, 0), size = (0, 0), linewidth = 0.15, heightAnchor = 'start', widthAnchor = 'start'):
        if(name == 'noName'):
            name = 'text' + str(self.TEXT_COUNTER) + ':Text'
            self.TEXT_COUNTER += 1

        if heightAnchor == 'start' and widthAnchor == 'start':
            anchor = '(justify bottom)'
        elif heightAnchor == 'top' and widthAnchor == 'start':
            anchor = '(justify top)'
        elif heightAnchor == 'middle' and widthAnchor == 'start':
            anchor = ''
        elif heightAnchor == 'start' and widthAnchor == 'middle':
            anchor = '(justify center bottom)'
        elif heightAnchor == 'middle' and widthAnchor == 'middle':
            anchor = '(justify center)'
        self.FILE.write('  (tbtext "' + text + '" (name ' + name + ') (pos ' + str(position[0]) + ' ' + str(position[1]) + ' ltcorner) (font (linewidth ' + str(linewidth) + ') (size ' + str(size[0]) + ' ' + str(size[1]) + ')) ' + anchor + ')\n')

class KiCAD6Template:
    FILE = None
    SEGM_COUNTER = 1
    RECT_COUNTER = 1
    POLY_COUNTER = 1
    TEXT_COUNTER = 1
    def __init__(self,filename = 'noname_6.kicad_wks', size = ('100%', '100%'), linewidth = 0.15, left_margin = 20, right_margin = 10, top_margin = 10, bottom_margin = 10):
        self.FILE = open(filename, 'w')
        self.FILE.write('(kicad_wks (version 20210606) (generator pl_editor)\n')
        self.FILE.write('  (setup (textsize 1.5 1.5)(linewidth ' + str(linewidth) + ')(textlinewidth 0.15)\n')
        self.FILE.write('  (left_margin ' + str(left_margin) + ')(right_margin ' + str(right_margin) + ')(top_margin ' + str(top_margin) + ')(bottom_margin ' + str(bottom_margin) + '))\n')
        pass

    def __del__(self):
        self.FILE.write(')')
        self.FILE.close

    def line(self, name = 'noName', start=(0, 0), end=(0, 0), linewidth = 0.15):
        if(name == 'noName'):
            name = 'segm' + str(self.SEGM_COUNTER) + ':Line'
            self.SEGM_COUNTER += 1
        self.FILE.write('  (line (name "' + name + '") (start ' + str(start[0]) + ' ' + str(start[1]) + ' ltcorner) (end ' + str(end[0]) + ' ' + str(end[1]) + ' ltcorner) (linewidth ' + str(linewidth) + '))\n')

    def rect(self, name = 'noName', start=(0, 0), end=(0, 0), linewidth = 0.15):
        if(name == 'noName'):
            name = 'rect' + str(self.RECT_COUNTER) + ':Rect'
            self.RECT_COUNTER += 1
        self.FILE.write('  (rect (name "' + name + '") (start ' + str(start[0]) + ' ' + str(start[1]) + ' ltcorner) (end ' + str(end[0]) + ' ' + str(end[1]) + ' ltcorner) (linewidth ' + str(linewidth) + '))\n')

    def polygon(self, name = 'noname', position = (0, 0), rotation = 0, linewidth = 0.15, points = [(0, 0), (10, 0), (10, 5), (5, 5), (5, 10), (0, 10), (0, 0)]):
        if(name == 'noName'):
            name = 'poly' + str(self.POLY_COUNTER) + ':Poly'
            self.POLY_COUNTER += 1
        self.FILE.write('  (polygon (name "' + name + '") (pos ' + str(position[0]) + ' ' + str(position[1]) + ' ltcorner) (rotate ' + str(rotation) + ') (linewidth ' + str(linewidth) + ')\n')

        #points
        self.FILE.write('    (pts')
        #loop
        for p in points:
            self.FILE.write(' (xy ' + str(p[0]) + ' ' + str(p[1]) + ')')
        self.FILE.write(')\n')

        self.FILE.write('  )\n')

    #                                                                                                                        middle                 middle
    def text(self, text = "Dummy text", name = 'noname', position = (0, 0), size = (0, 0), linewidth = 0.15, heightAnchor = 'start', widthAnchor = 'start'):
        if(name == 'noName'):
            name = 'text' + str(self.TEXT_COUNTER) + ':Text'
            self.TEXT_COUNTER += 1

        if heightAnchor == 'start' and widthAnchor == 'start':
            anchor = '(justify bottom)'
        elif heightAnchor == 'top' and widthAnchor == 'start':
            anchor = '(justify top)'
        elif heightAnchor == 'middle' and widthAnchor == 'start':
            anchor = ''
        elif heightAnchor == 'start' and widthAnchor == 'middle':
            anchor = '(justify center bottom)'
        elif heightAnchor == 'middle' and widthAnchor == 'middle':
            anchor = '(justify center)'
        self.FILE.write('  (tbtext "' + text + '" (name "' + name + '") (pos ' + str(position[0]) + ' ' + str(position[1]) + ' ltcorner) (font (linewidth ' + str(linewidth) + ') (size ' + str(size[0]) + ' ' + str(size[1]) + ')) ' + anchor + ')\n')
        
class KiCAD7Template:
    FILE = None
    SEGM_COUNTER = 1
    RECT_COUNTER = 1
    POLY_COUNTER = 1
    TEXT_COUNTER = 1
    def __init__(self,filename = 'noname_7.kicad_wks', size = ('100%', '100%'), linewidth = 0.15, left_margin = 20, right_margin = 10, top_margin = 10, bottom_margin = 10):
        self.FILE = open(filename, 'w')
        self.FILE.write('(kicad_wks (version 20220228) (generator pl_editor)\n')
        self.FILE.write('  (setup (textsize 1.5 1.5)(linewidth ' + str(linewidth) + ')(textlinewidth 0.15)\n')
        self.FILE.write('  (left_margin ' + str(left_margin) + ')(right_margin ' + str(right_margin) + ')(top_margin ' + str(top_margin) + ')(bottom_margin ' + str(bottom_margin) + '))\n')
        pass

    def __del__(self):
        self.FILE.write(')')
        self.FILE.close

    def line(self, name = 'noName', start=(0, 0), end=(0, 0), linewidth = 0.15):
        if(name == 'noName'):
            name = 'segm' + str(self.SEGM_COUNTER) + ':Line'
            self.SEGM_COUNTER += 1
        self.FILE.write('  (line (name "' + name + '") (start ' + str(start[0]) + ' ' + str(start[1]) + ' ltcorner) (end ' + str(end[0]) + ' ' + str(end[1]) + ' ltcorner) (linewidth ' + str(linewidth) + '))\n')

    def rect(self, name = 'noName', start=(0, 0), end=(0, 0), linewidth = 0.15):
        if(name == 'noName'):
            name = 'rect' + str(self.RECT_COUNTER) + ':Rect'
            self.RECT_COUNTER += 1
        self.FILE.write('  (rect (name "' + name + '") (start ' + str(start[0]) + ' ' + str(start[1]) + ' ltcorner) (end ' + str(end[0]) + ' ' + str(end[1]) + ' ltcorner) (linewidth ' + str(linewidth) + '))\n')

    def polygon(self, name = 'noname', position = (0, 0), rotation = 0, linewidth = 0.15, points = [(0, 0), (10, 0), (10, 5), (5, 5), (5, 10), (0, 10), (0, 0)]):
        if(name == 'noName'):
            name = 'poly' + str(self.POLY_COUNTER) + ':Poly'
            self.POLY_COUNTER += 1
        self.FILE.write('  (polygon (name "' + name + '") (pos ' + str(position[0]) + ' ' + str(position[1]) + ' ltcorner) (rotate ' + str(rotation) + ') (linewidth ' + str(linewidth) + ')\n')

        #points
        self.FILE.write('    (pts')
        #loop
        for p in points:
            self.FILE.write(' (xy ' + str(p[0]) + ' ' + str(p[1]) + ')')
        self.FILE.write(')\n')

        self.FILE.write('  )\n')

    #                                                                                                                        middle                 middle
    def text(self, text = "Dummy text", name = 'noname', position = (0, 0), size = (0, 0), font = 'osifont', linewidth = 0.15, heightAnchor = 'start', widthAnchor = 'start'):
        if(name == 'noName'):
            name = 'text' + str(self.TEXT_COUNTER) + ':Text'
            self.TEXT_COUNTER += 1

        if heightAnchor == 'start' and widthAnchor == 'start':
            anchor = '(justify bottom)'
            position= (position[0], position[1] + size[1]*(3/10))
        elif heightAnchor == 'top' and widthAnchor == 'start':
            anchor = '(justify top)'
        elif heightAnchor == 'middle' and widthAnchor == 'start':
            anchor = ''
        elif heightAnchor == 'start' and widthAnchor == 'middle':
            anchor = '(justify center bottom)'
            position= (position[0], position[1] + size[1]*(3/10))
        elif heightAnchor == 'middle' and widthAnchor == 'middle':
            anchor = '(justify center)'
        self.FILE.write('  (tbtext "' + text + '" (name "' + name + '") (pos ' + str(position[0]) + ' ' + str(position[1]) + ' ltcorner) (font (face "' + font + '") (linewidth ' + str(linewidth) + ') (size ' + str(size[0]) + ' ' + str(size[1]) + ')) ' + anchor + ')\n')

