import wget
from os.path import exists

from reportlab.pdfgen import canvas
from reportlab.pdfbase import pdfform
from reportlab.lib.colors import *

from reportlab.lib.units import mm
from reportlab.lib.pagesizes import letter, A4

from reportlab.pdfbase import pdfmetrics
from reportlab.pdfbase.ttfonts import TTFont

from reportlab.lib import colors
from reportlab.graphics.shapes import *
from reportlab.graphics import renderPDF

class PDFTemplate:
    FILE = None
    SIZE = (0,0)
    #                                                  With   Height
    def __init__(self,filename = 'noname.pdf', size = (100, 200), linewidth = 0.15, left_margin = 20, right_margin = 10, top_margin = 10, bottom_margin = 10):
        # get osifont from:
        url = 'https://github.com/hikikomori82/osifont/raw/master/osifont.ttf'
        if not exists('osifont.ttf'):
            wget.download(url)
            print()
        else:
            pass
        
        self.SIZE = size
        
        self.FILE = canvas.Canvas(filename)
        #             With       Height
        self.FILE.setPageSize((float(size[0]) * mm, float(size[1]) * mm))
        # include osifont
        pdfmetrics.registerFont(TTFont('osifont', 'osifont.ttf'))
        
        self.FILE.setLineWidth(linewidth * mm)
        
        pass

    def __del__(self):
        self.FILE.save()

    def line(self, start=(0, 0), end=(0, 0), linewidth = 0.15):
        start = (start[0] * mm, start[1] * mm)
        end = (end[0]* mm, end[1]* mm)
        self.FILE.setLineWidth(linewidth * mm)
        self.FILE.line(start[0], start[1], end[0], end[1])
        pass

    def rect(self, start=(0, 0), end=(0, 0), linewidth = 0.15):
        length = (end[0] - start[0], end[1] - start[1])
        start = (start[0] * mm, start[1] * mm)
        length = (length[0] * mm, length[1] * mm)
        self.FILE.setLineWidth(linewidth * mm)
        self.FILE.rect(start[0], start[1], length[0], length[1])
        pass

    def polygon(self, position = (0, 0), rotation = 0, linewidth = 0.15, points = [(0, 0), (10, 0), (10, 5), (5, 5), (5, 10), (0, 10), (0, 0)]):
        print('polygon dose not exist!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!')
        pass
    
    def drawCorners(self):
        self.FILE.setLineWidth(0 * mm)
        
        # Bottom Left
        self.FILE.rect(0, 0, 5 * mm, 10 * mm, fill = 1)
        self.FILE.rect(0, 0, 10 * mm, 5 * mm, fill = 1)
        
        # Bottom Right
        self.FILE.rect(self.SIZE[0] * mm, 0, -5 * mm, 10 * mm, fill = 1)
        self.FILE.rect(self.SIZE[0] * mm, 0, -10 * mm, 5 * mm, fill = 1)
        
        # Top Left
        self.FILE.rect(0, self.SIZE[1] * mm, 5 * mm, -10 * mm, fill = 1)
        self.FILE.rect(0, self.SIZE[1] * mm, 10 * mm, -5 * mm, fill = 1)
        
        # Top Right
        self.FILE.rect(self.SIZE[0] * mm, self.SIZE[1] * mm, -5 * mm, -10 * mm, fill = 1)
        self.FILE.rect(self.SIZE[0] * mm, self.SIZE[1] * mm, -10 * mm, -5 * mm, fill = 1)

    #                                                                                                                        
    def text(self, text = "Dummy text", name = 'dummy', position = (0, 0), size = 5, linewidth = 0.15, heightAnchor = 'start', widthAnchor = 'start', editable = False, width=30):
        self.FILE.setLineWidth(linewidth * mm)
        
        #if not editable:
        bSize = size
        size = size * (10 / 7)
            
        if heightAnchor == 'middle':
            hpos = position[1] - bSize/2  - bSize * (7 / 250)
        elif heightAnchor == 'top':
            hpos = position[1] - size
        else:
            hpos = position[1]
        
        if not editable and widthAnchor == 'start':
            self.FILE.setLineWidth(linewidth * mm)
            self.FILE.setFont("osifont", size*mm)
            self.FILE.drawString(position[0] * mm, hpos * mm, text)
        elif not editable and widthAnchor == 'middle':
            self.FILE.setLineWidth(linewidth * mm)
            self.FILE.setFont("osifont", size*mm)
            self.FILE.drawCentredString(position[0] * mm, hpos * mm, text)
        pass
        
        if editable:
            if widthAnchor == 'start':
                wpos = position[0]
            elif widthAnchor == 'middle':
                wpos = position[0] - width / 2
            else:
                wpos = position[0]
            form = self.FILE.acroForm
            form.textfieldRelative(name=name, tooltip='',
                   value = text,
                   fontName='Helvetica', fontSize= size*mm,
                   height=size * mm,
                   x=wpos * mm, y=hpos * mm, 
                   borderStyle='solid', borderWidth=0,
                   borderColor=black, fillColor=transparent, 
                   width = width * mm,
                   textColor=black)
    