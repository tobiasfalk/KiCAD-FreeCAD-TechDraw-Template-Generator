from UniversalDraw import UniversalDraw
import os

def numToABC(num):
    retStr = "";
    num -= 1
    #       1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16   17   18   21  20   21   22   23   24
    abc = ["A", "B", "C", "D", "E", "F", "G", "H", "J", "K", "L", "M", "N", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"];
    ABC = [0];
    for i in range(num):
        ABC[0] = ABC[0] + 1;
        for x in range(len(ABC)):
            if ABC[x] == 24 and x  != len(ABC) - 1:
                ABC[x] = 0;
                ABC[x+1] = ABC[x+1] + 1;
            elif ABC[x] == 24 and x ==len(ABC) - 1:
                ABC[x] = 0;
                ABC.append(0);

    for i in range(len(ABC)):
        retStr = retStr + abc[ABC[len(ABC) - 1 -i]]
        if len(ABC) > 1 and i != len(ABC)-1:
            retStr += '\n'

    return retStr;

class StandardDraw:
    SIZE = None
    SIZE_STRING = None
    CUTTING_MARKS = True
    COLOR = '#000000'
    NUM_OPT_LINES = 0
    REV_HISTORY = False
    NUMREVISIONS = 0
    FOLD_LINES_DIN824_A = False
    FOLD_LINES_200_X_290 = False
    FULL_PARTS_LIST = False
    FULL_PARTS_LIST_SMALL_LINES = False
    FULL_PARTS_LIST_NUM_SHEETS = 1
    SMALL_PARTS_LIST = False
    SMALL_PARTS_LIST_NUM_LINES = 1
    NUM_PAGES = 1
    
    SHEET_SIZES_ISO_216_A =[(1682, 1189),
                            (1189, 841),
                            (841,  594),
                            (594,  420),
                            (420,  297),
                            (297,  210),
                            (210,  297)]

    FIELD_LETTERS = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X']

    DWG = None

    def __init__(self, size = (100, 100), sizeString = 'User defined', cuttingMarks = True, color = '#000000', numOptLines = 0, revHistory = False, numRevisions = 0, foldLinesDIN824_A = False, foldLines200x290 = False, fullPartsList = False, fullPartsListSmallLines = False, fullPartsListNumSheets = 1, smallPartsList = False, smallPartsListNumLines = 1):
        self.SIZE = size
        self.SIZE_STRING = sizeString
        self.CUTTING_MARKS = cuttingMarks
        self.COLOR = color
        self.NUM_OPT_LINES = numOptLines
        self.REV_HISTORY = revHistory
        self.NUMREVISIONS = numRevisions
        self.FOLD_LINES_DIN824_A = foldLinesDIN824_A
        self.FOLD_LINES_200_X_290 = foldLines200x290
        self.FULL_PARTS_LIST = fullPartsList
        self.FULL_PARTS_LIST_SMALL_LINES = fullPartsListSmallLines
        self.FULL_PARTS_LIST_NUM_SHEETS = fullPartsListNumSheets
        self.SMALL_PARTS_LIST = smallPartsList
        self.SMALL_PARTS_LIST_NUM_LINES = smallPartsListNumLines

        if self.NUM_OPT_LINES > 3:
            self.NUM_OPT_LINES = 3
            print('More than 3 optinal lines are not allowed, the value was set to 3')
        if self.FULL_PARTS_LIST and (self.SIZE != (210,  297) or self.REV_HISTORY or self.SMALL_PARTS_LIST):
            self.SIZE = (210,  297)
            self.SIZE_STRING = 'ISO 216 A4P'
            self.REV_HISTORY = False
            self.SMALL_PARTS_LIST = False
            print('The full sheet parts list(fullPartsList) is not compatible with: ')
            print('\tOther page sizes then ISO 216 A4P(210x297)')
            print('\tRevision History(revHistory)')
            print('\tSmall Parts list abouv the header(smallPartsList)')
            print('The mentined complications ver set to false or to the right value')
        if (self.FOLD_LINES_DIN824_A or self.FOLD_LINES_200_X_290) and not self.SIZE in self.SHEET_SIZES_ISO_216_A:
            self.FOLD_LINES_DIN824_A = False
            self.FOLD_LINES_200_X_290 = False
            print('Sheet szise not in DIN 824-A present, option was disabled')

    def __del__(self):
        pass

    def drawISO5457_ISO700_A(self):
        sizeStringFile = self.SIZE_STRING.replace(' ', '_')
        filename = sizeStringFile + '_ISO5457_ISO7200_A'
        if not self.CUTTING_MARKS:
            filename += '_ncm'
        if self.NUM_OPT_LINES > 0:
            filename += '+' + str(self.NUM_OPT_LINES)
        if self.REV_HISTORY:
            filename +='_rh+' + str(self.NUMREVISIONS)
        if self.FOLD_LINES_DIN824_A:
            filename += '_fl_DIN824_A'
        if self.FOLD_LINES_200_X_290:
            filename += '_fl_200x290'
        if self.FULL_PARTS_LIST:
            filename += '_fspl'
            if self.FULL_PARTS_LIST_SMALL_LINES:
                filename += '_sl'
            if self.FULL_PARTS_LIST_NUM_SHEETS > 1:
                filename += '_' + str(self.FULL_PARTS_LIST_NUM_SHEETS) + '_sh'
        if self.SMALL_PARTS_LIST:
            filename += '_spl+' + str(self.SMALL_PARTS_LIST_NUM_LINES)
        if self.COLOR != '#000000':
            filename += '_c_' + self.COLOR.replace('#', '')

        
        if self.DWG == None:
            print(filename)
            try:
                os.mkdir("./out/");
            except OSError as error:
                pass

            try:
                os.mkdir("./out/" + filename);
            except OSError as error:
                pass
        
            self.DWG = UniversalDraw(size = self.SIZE, filename = "./out/" + filename + '/' + filename)
        
            
        size = self.SIZE
        sizeString = self.SIZE_STRING
        color = self.COLOR
        height = size[1];
        width = size[0];

        # Cutting marks
        if self.CUTTING_MARKS:
            # Top Left
            self.DWG.polygon(linewidth = 0.0, points = [(0, 0), (10, 0), (10, 5), (5, 5), (5, 10), (0, 10), (0, 0)], color = color, fill = color, group = "sheet-border")
            # Top Right
            self.DWG.polygon(linewidth = 0.0, points = [(0+width, 0), (-10+width, 0), (-10+width, 5), (-5+width, 5), (-5+width, 10), (0+width, 10), (0+width, 0)], color = color, fill = color, group = "sheet-border")
            # Bottom Right
            self.DWG.polygon(linewidth = 0.0, points = [(0+width, 0+height), (-10+width, 0+height), (-10+width, -5+height), (-5+width, -5+height), (-5+width, -10+height), (0+width, -10+height), (0+width, -0+height)], color = color, fill = color, group = "sheet-border")
            # Bottom Left
            self.DWG.polygon(linewidth = 0.0, points = [(0, 0+height), (10, 0+height), (10, -5+height), (5, -5+height), (5, -10+height), (0, -10+height), (0, -0+height)], color = color, fill = color, group = "sheet-border")
            
            # the PDF lib has no polygons so i made a custom way to draw the cuting marks
            self.DWG.drawCorners()

        # Sheet border
        self.DWG.rect(start=(0, 0), end=(width, height), linewidth = 0.35, color = color, group = "sheet-border")
        self.DWG.rect(start=(15, 5), end=(width - 5, height - 5), linewidth = 0.35, color = color, group = "sheet-border")
        self.DWG.rect(start=(20, 10), end=(width - 10, height - 10), linewidth = 0.7, color = color, group = "sheet-border")

        # Sheet border Top and Bottom
        halfWidth = width / 2
        if (width - 180) > halfWidth:
            self.DWG.line(start=(halfWidth, height-5), end=(halfWidth, height-20), linewidth = 0.7, color = color, group = "sheet-border")
            self.DWG.line(start=(halfWidth, 5), end=(halfWidth, 20), linewidth = 0.7, color = color, group = "sheet-border")
        else:
            self.DWG.line(start=(halfWidth, height-5), end=(halfWidth, height-10), linewidth = 0.7, color = color, group = "sheet-border")
            self.DWG.line(start=(halfWidth, 5), end=(halfWidth, 10), linewidth = 0.7, color = color, group = "sheet-border")

        widthIndexLeft = halfWidth
        widthIndexRight = halfWidth

        letterPlaceWidth = []

        letterPlaceWidth.append(widthIndexLeft - 25)
        widthIndexLeft -= 50
        while widthIndexLeft > 0 + 20 :
            self.DWG.line(start=(widthIndexLeft, 5), end=(widthIndexLeft, 10), linewidth = 0.35, color = color, group = "sheet-border")
            self.DWG.line(start=(widthIndexLeft, height-5), end=(widthIndexLeft, height-10), linewidth = 0.35, color = color, group = "sheet-border")
            if (widthIndexLeft - 25) > 0 + 20:
                letterPlaceWidth.append(widthIndexLeft - 25)
            widthIndexLeft -= 50

        letterPlaceWidth.append(widthIndexRight + 25)
        widthIndexRight += 50
        while widthIndexRight < width - 10:
            self.DWG.line(start=(widthIndexRight, 5), end=(widthIndexRight, 10), linewidth = 0.35, color = color, group = "sheet-border")
            self.DWG.line(start=(widthIndexRight, height-5), end=(widthIndexRight, height-10), linewidth = 0.35, color = color, group = "sheet-border")
            if (widthIndexRight + 25) < width - 10:
                letterPlaceWidth.append(widthIndexRight + 25)
            widthIndexRight += 50

        letterPlaceWidth.sort()
        letterIndex = 1
        for i in letterPlaceWidth:
            self.DWG.text(text = str(letterIndex), position = (i, 7.75), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "sheet-border")
            if width >= 300 and height >= 290 and not i == letterPlaceWidth[-1]:
                self.DWG.text(text = str(letterIndex), position = (i, height - 7.25), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "sheet-border")
            if i == letterPlaceWidth[-1]:
                x = (i - 25) + (((width - 10) - (i - 25)) / 2)
                self.DWG.text(text = sizeString, position = (x, height - 7.25), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "sheet-border")
            letterIndex += 1

        # Sheet border Left and Right
        heightHalf = height / 2
        headerHeight = 65 + (self.NUM_OPT_LINES *11)
        if self.SMALL_PARTS_LIST:
            headerHeight += 10 + (self.SMALL_PARTS_LIST_NUM_LINES * 11)

        if self.FULL_PARTS_LIST:
            self.DWG.line(start=(15, heightHalf), end=(20, heightHalf), linewidth = 0.7, color = color, group = "sheet-border")
        else:
            self.DWG.line(start=(15, heightHalf), end=(30, heightHalf), linewidth = 0.7, color = color, group = "sheet-border")
        
        if (height - headerHeight) < heightHalf or 20 + (self.NUMREVISIONS * 15) > heightHalf or self.FULL_PARTS_LIST:
            self.DWG.line(start=(width - 5, heightHalf), end=(width - 10, heightHalf), linewidth = 0.7, color = color, group = "sheet-border")
        else:
            self.DWG.line(start=(width - 5, heightHalf), end=(width - 20, heightHalf), linewidth = 0.7, color = color, group = "sheet-border")

        heightIndexTop = heightHalf
        heightIndexBottom = heightHalf

        letterPlaceHeight = []

        letterPlaceHeight.append(heightIndexTop - 25)
        heightIndexTop -= 50
        while heightIndexTop > 0 + 10 :
            self.DWG.line(start=(15, heightIndexTop), end=(20, heightIndexTop), linewidth = 0.35, color = color, group = "sheet-border")
            self.DWG.line(start=(width-5, heightIndexTop), end=(width-10, heightIndexTop), linewidth = 0.35, color = color, group = "sheet-border")
            if (heightIndexTop - 25) > 0 + 10:
                letterPlaceHeight.append(heightIndexTop - 25)
            heightIndexTop -= 50

        letterPlaceHeight.append(heightIndexBottom + 25)
        heightIndexBottom += 50
        while heightIndexBottom < height - 10:
            self.DWG.line(start=(15, heightIndexBottom), end=(20, heightIndexBottom), linewidth = 0.35, color = color, group = "sheet-border")
            self.DWG.line(start=(width-5, heightIndexBottom), end=(width-10, heightIndexBottom), linewidth = 0.35, color = color, group = "sheet-border")
            if (heightIndexBottom + 25) < height - 10:
                letterPlaceHeight.append(heightIndexBottom + 25)
            heightIndexBottom += 50

        letterPlaceHeight.sort()
        letterIndex = 1
        for i in letterPlaceHeight:
            self.DWG.text(text = numToABC(letterIndex), position = (17.25, i), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "sheet-border")
            if width >= 300 and height >= 290:
                self.DWG.text(text = numToABC(letterIndex), position = (width-7.75, i), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "sheet-border")
            letterIndex += 1

        # Main titelblock lines
        self.DWG.rect(start=(width - 190, height - 65 - (self.NUM_OPT_LINES * 11)), end=(width - 10, height - 10), linewidth = 0.7, color = color, group = "titleblock-structure")

        self.DWG.line(start=(width - 35, height - 10), end=(width - 35, height - 32), linewidth = 0.35, color = color, group = "titleblock-structure")
        self.DWG.line(start=(width - 50, height - 10), end=(width - 50, height - 65 - (self.NUM_OPT_LINES *11)), linewidth = 0.35, color = color, group = "titleblock-structure")
        self.DWG.line(start=(width - 110, height - 10), end=(width - 110, height - 65 - (self.NUM_OPT_LINES *11)), linewidth = 0.35, color = color, group = "titleblock-structure")

        self.DWG.line(start=(width - 10, height - 21), end=(width - 50, height - 21), linewidth = 0.35, color = color, group = "titleblock-structure")
        self.DWG.line(start=(width - 10, height - 32), end=(width - 50, height - 32), linewidth = 0.35, color = color, group = "titleblock-structure")
        self.DWG.line(start=(width - 10, height - 43), end=(width - 190, height - 43), linewidth = 0.35, color = color, group = "titleblock-structure")
        self.DWG.line(start=(width - 10, height - 54), end=(width - 190, height - 54), linewidth = 0.35, color = color, group = "titleblock-structure")

        # Main titelblock text
        self.DWG.text(text = 'Sheet', position = (width - 35 + 0.9, height - 21 + 1.8 + 0.9), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-non-editable")
        self.DWG.text(text = '%S/%N', position = (width - 35 + 0.9, height - 21 + 1.8 + 0.9 + 4.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 23)
        self.DWG.text(text = 'Lang.', position = (width - 50 + 0.9, height - 21 + 1.8 + 0.9), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-non-editable")
        self.DWG.text(text = 'EN', position = (width - 50 + 0.9, height - 21 + 1.8 + 0.9 + 4.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 13, id = 'lang')
        self.DWG.text(text = 'Rev.', position = (width - 50 + 0.9, height - 32 + 1.8 + 0.9), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-non-editable")
        self.DWG.text(text = '%R', position = (width - 50 + 0.9, height - 32 + 1.8 + 0.9 + 4.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 13, id = 'rev')
        self.DWG.text(text = 'Date of issue', position = (width - 35 + 0.9, height - 32 + 1.8 + 0.9), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-non-editable")
        self.DWG.text(text = '%D', position = (width - 35 + 0.9, height - 32 + 1.8 + 0.9 + 4.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 23, id = 'date')

        self.DWG.text(text = 'Document number', position = (width - 50 + 0.9, height - 43 + 1.8 + 0.9), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-non-editable")
        self.DWG.text(text = '%C6', position = (width - 50 + 0.9, height - 43 + 1.8 + 0.9 + 4.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 38, id = 'doc_num')
        self.DWG.text(text = 'Titel, Supplementary titel', position = (width - 110 + 0.9, height - 43 + 1.8 + 0.9), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-non-editable")
        self.DWG.text(text = '%T', position = (width - 110 + 0.9, height - 43 + 1.8 + 0.9 + 4.5), tsize = 5, linewidth = 0.35, color = color, heightAnchor = 'top', widthAnchor = 'start', group = "titleblock-text-editable", width = 58, id = 'titel_1')
        self.DWG.text(text = '', position = (width - 110 + 0.9, height - 43 + 1.8 + 0.9 + 4.5 + 7.5), tsize = 5, linewidth = 0.35, color = color, heightAnchor = 'top', widthAnchor = 'start', group = "titleblock-text-editable", width = 58, id = 'titel_2')
        self.DWG.text(text = '', position = (width - 110 + 0.9, height - 43 + 1.8 + 0.9 + 4.5 + 7.5 + 7.5), tsize = 5, linewidth = 0.35, color = color, heightAnchor = 'top', widthAnchor = 'start', group = "titleblock-text-editable", width = 58, id = 'titel_3')
        self.DWG.text(text = 'Legal owner', position = (width - 190 + 0.9, height - 43 + 1.8 + 0.9), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-non-editable")
        self.DWG.text(text = '%Y', position = (width - 190 + 0.9, height - 43 + 1.8 + 0.9 + 4.5), tsize = 5, linewidth = 0.35, color = color, heightAnchor = 'top', widthAnchor = 'start', group = "titleblock-text-editable", width = 78, id = 'legal_owner_1')
        self.DWG.text(text = '', position = (width - 190 + 0.9, height - 43 + 1.8 + 0.9 + 4.5 + 7.5), tsize = 5, linewidth = 0.35, color = color, heightAnchor = 'top', widthAnchor = 'start', group = "titleblock-text-editable", width = 78, id = 'legal_owner_2')
        self.DWG.text(text = '', position = (width - 190 + 0.9, height - 43 + 1.8 + 0.9 + 4.5 + 7.5 + 7.5), tsize = 5, linewidth = 0.35, color = color, heightAnchor = 'top', widthAnchor = 'start', group = "titleblock-text-editable", width = 78, id = 'legal_owner_3')
        self.DWG.text(text = 'Approved by', position = (width - 190 + 0.9, height - 54 + 1.8 + 0.9), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-non-editable")
        self.DWG.text(text = '%C1', position = (width - 190 + 0.9, height - 54 + 1.8 + 0.9 + 4.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 78, id = 'approved')
        self.DWG.text(text = 'Projekt', position = (width - 110 + 0.9, height - 54 + 1.8 + 0.9), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-non-editable")
        self.DWG.text(text = '%C3', position = (width - 110 + 0.9, height - 54 + 1.8 + 0.9 + 4.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 58, id = 'projekt')
        self.DWG.text(text = 'Document type', position = (width - 50 + 0.9, height - 54 + 1.8 + 0.9), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-non-editable")
        self.DWG.text(text = '%C5', position = (width - 50 + 0.9, height - 54 + 1.8 + 0.9 + 4.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 38, id = 'doc_type')
        self.DWG.text(text = 'Created by', position = (width - 190 + 0.9, height - 65 + 1.8 + 0.9), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-non-editable")
        self.DWG.text(text = '%C0', position = (width - 190 + 0.9, height - 65 + 1.8 + 0.9 + 4.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 78, id = 'created_by')
        self.DWG.text(text = 'Valid from to', position = (width - 110 + 0.9, height - 65 + 1.8 + 0.9), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-non-editable")
        self.DWG.text(text = '%C2', position = (width - 110 + 0.9, height - 65 + 1.8 + 0.9 + 4.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 58, id = 'valid_from_to')
        self.DWG.text(text = 'Document state', position = (width - 50 + 0.9, height - 65 + 1.8 + 0.9), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-non-editable")
        self.DWG.text(text = '%C4', position = (width - 50 + 0.9, height - 65 + 1.8 + 0.9 + 4.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 38, id = 'doc_state')


        # Optional titelblock
        for i in range(self.NUM_OPT_LINES):
            self.DWG.line(start=(width - 10, height - 65 - (11 * i)), end=(width - 190, height - 65 - (11 * i)), linewidth = 0.35, color = color, group = "titleblock-structure")
            if i == 0:
                self.DWG.text(text = 'A', position = (width - 190 + 0.9, height - 65 - (11 * (i + 1)) + 1.8 + 0.9), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 78, id = 'option_a')
                self.DWG.text(text = 'a_value', position = (width - 190 + 0.9, height - 65 - (11 * (i + 1)) + 1.8 + 0.9 + 4.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 78, id = 'option_a_value')
                self.DWG.text(text = 'Raw dimensions', position = (width - 110 + 0.9, height - 65 - (11 * (i + 1)) + 1.8 + 0.9), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 58, id = 'option_b')
                self.DWG.text(text = 'b_value', position = (width - 110 + 0.9, height - 65 - (11 * (i + 1)) + 1.8 + 0.9 + 4.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 58, id = 'option_b_value')
                self.DWG.text(text = 'Scale', position = (width - 50 + 0.9, height - 65 - (11 * (i + 1)) + 1.8 + 0.9), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 38, id = 'option_c')
                self.DWG.text(text = '1:1', position = (width - 50 + 0.9, height - 65 - (11 * (i + 1)) + 1.8 + 0.9 + 4.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 38, id = 'option_c_value')
            elif i == 1:
                self.DWG.text(text = 'Surface treatment', position = (width - 190 + 0.9, height - 65 - (11 * (i + 1)) + 1.8 + 0.9), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 78, id = 'option_d')
                self.DWG.text(text = 'Surface treatment', position = (width - 190 + 0.9, height - 65 - (11 * (i + 1)) + 1.8 + 0.9 + 4.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 78, id = 'option_d_value')
                self.DWG.text(text = 'Weight', position = (width - 110 + 0.9, height - 65 - (11 * (i + 1)) + 1.8 + 0.9), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 58, id = 'option_e')
                self.DWG.text(text = 'Weight', position = (width - 110 + 0.9, height - 65 - (11 * (i + 1)) + 1.8 + 0.9 + 4.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 58, id = 'option_e_value')
                self.DWG.text(text = 'Standard', position = (width - 50 + 0.9, height - 65 - (11 * (i + 1)) + 1.8 + 0.9), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 38, id = 'option_f')
                self.DWG.text(text = 'Standard', position = (width - 50 + 0.9, height - 65 - (11 * (i + 1)) + 1.8 + 0.9 + 4.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 38, id = 'option_f_value')
            elif i == 2:
                self.DWG.text(text = 'Option G', position = (width - 190 + 0.9, height - 65 - (11 * (i + 1)) + 1.8 + 0.9), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 78, id = 'option_g')
                self.DWG.text(text = 'Option G Value', position = (width - 190 + 0.9, height - 65 - (11 * (i + 1)) + 1.8 + 0.9 + 4.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 78, id = 'option_g_value')
                self.DWG.text(text = 'Option H', position = (width - 110 + 0.9, height - 65 - (11 * (i + 1)) + 1.8 + 0.9), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 58, id = 'option_h')
                self.DWG.text(text = 'Option H Value', position = (width - 110 + 0.9, height - 65 - (11 * (i + 1)) + 1.8 + 0.9 + 4.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 58, id = 'option_h_value')
                self.DWG.text(text = 'Option I', position = (width - 50 + 0.9, height - 65 - (11 * (i + 1)) + 1.8 + 0.9), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 38, id = 'option_i_value')
                self.DWG.text(text = 'Option I Value', position = (width - 50 + 0.9, height - 65 - (11 * (i + 1)) + 1.8 + 0.9 + 4.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 38, id = 'option_i_value')

        # Revision History
        if self.REV_HISTORY:
            self.DWG.rect(start=(width-190, 10), end=(width-10, 20 + (self.NUMREVISIONS * 15)), linewidth = 0.7, color = color, group = "sheet-border")
            self.DWG.line(start=(width-190, 15), end=(width-10, 15), linewidth = 0.35, color = color, group = "sheet-border")
            self.DWG.line(start=(width-190, 20), end=(width-10, 20), linewidth = 0.7, color = color, group = "sheet-border")
            self.DWG.line(start=(width-175, 15), end=(width-175, 20 + (self.NUMREVISIONS * 15)), linewidth = 0.35, color = color, group = "sheet-border")
            self.DWG.line(start=(width-155, 15), end=(width-155, 20 + (self.NUMREVISIONS * 15)), linewidth = 0.35, color = color, group = "sheet-border")
            self.DWG.line(start=(width-60, 15), end=(width-60, 20 + (self.NUMREVISIONS * 15)), linewidth = 0.35, color = color, group = "sheet-border")
            self.DWG.line(start=(width-40, 15), end=(width-40, 20 + (self.NUMREVISIONS * 15)), linewidth = 0.35, color = color, group = "sheet-border")

            self.DWG.text(text = 'Revision History', position = (width - 100, 12.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            self.DWG.text(text = 'Zone', position = (width - 182.5, 17.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            self.DWG.text(text = 'Rev.', position = (width - 165, 17.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            self.DWG.text(text = 'Description', position = (width - 107.5, 17.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            self.DWG.text(text = 'Date', position = (width - 50, 17.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            self.DWG.text(text = 'Created by', position = (width - 25, 17.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")

            for i in range(self.NUMREVISIONS):
                self.DWG.line(start=(width-190, 20 + (i * 15)), end=(width-10, 20 + (i * 15)), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.text(text = 'ZoneA', position = (width - 182.5, 17.75 + ((i + 1) * 15)), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 13, id = 'zone_a_' + str(i))
                self.DWG.text(text = 'Rev.A', position = (width - 165, 17.75 + ((i + 1) * 15)), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 18, id = 'rev_a_' + str(i))
                self.DWG.text(text = 'DescriptionA', position = (width - 107.5, 17.75 + ((i + 1) * 15)), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 93, id = 'desc_a_' + str(i))
                self.DWG.text(text = 'DateA', position = (width - 50, 17.75 + ((i + 1) * 15)), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 18, id = 'date_a_' + str(i))
                self.DWG.text(text = 'Created byA', position = (width - 25, 17.75 + ((i + 1) * 15)), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 28, id = 'created_by_a_' + str(i))
                
                self.DWG.text(text = 'ZoneB', position = (width - 182.5, 13 + ((i + 1) * 15)), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 13, id = 'zone_b_' + str(i))
                self.DWG.text(text = 'Rev.B', position = (width - 165, 13 + ((i + 1) * 15)), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 18, id = 'rev_b_' + str(i))
                self.DWG.text(text = 'DescriptionB', position = (width - 107.5, 13 + ((i + 1) * 15)), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 93, id = 'desc_c_' + str(i))
                self.DWG.text(text = 'DateB', position = (width - 50, 13 + ((i + 1) * 15)), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 18, id = 'date_d_' + str(i))
                self.DWG.text(text = 'Created byB', position = (width - 25, 13 + ((i + 1) * 15)), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 28, id = 'created_by_b_' + str(i))
                
                self.DWG.text(text = 'ZoneC', position = (width - 182.5, 8.25 + ((i + 1) * 15)), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 13, id = 'zone_c_' + str(i))
                self.DWG.text(text = 'Rev.C', position = (width - 165, 8.25 + ((i + 1) * 15)), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 18, id = 'rev_c_' + str(i))
                self.DWG.text(text = 'DescriptionC', position = (width - 107.5, 8.25 + ((i + 1) * 15)), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 93, id = 'desc_c_' + str(i))
                self.DWG.text(text = 'DateC', position = (width - 50, 8.25 + ((i + 1) * 15)), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 18, id = 'date_d_' + str(i))
                self.DWG.text(text = 'Created byC', position = (width - 25, 8.25 + ((i + 1) * 15)), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 28, id = 'created_by_c_' + str(i))



        # Folding Lines(DIN824 A), only for ISO 216 A sizes execpt for 4A0
        if self.FOLD_LINES_DIN824_A:
            if self.SIZE == (420, 297):
                # Vertical
                self.DWG.line(start=(125, 0), end=(125, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(125, height), end=(125, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(230, 0), end=(230, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(230, height), end=(230, height-5), linewidth = 0.35, color = color, group = "sheet-border")
            if self.SIZE == (594, 420):
                # Vertical
                self.DWG.line(start=(210, 0), end=(210, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(210, height), end=(210, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(402, 0), end=(402, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(402, height), end=(402, height-5), linewidth = 0.35, color = color, group = "sheet-border")

                self.DWG.line(start=(105, 0), end=(105, 5), linewidth = 0.35, color = color, group = "sheet-border")

                # Horizontal
                self.DWG.line(start=(0, height-297), end=(15, height-297), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(width, height-297), end=(width-5, height-297), linewidth = 0.35, color = color, group = "sheet-border")
            if self.SIZE == (841, 594):
                # Vertical
                self.DWG.line(start=(210, 0), end=(210, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(210, height), end=(210, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(400, 0), end=(400, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(400, height), end=(400, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(525.5, 0), end=(525.5, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(525.5, height), end=(525.5, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(651, 0), end=(651, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(651, height), end=(651, height-5), linewidth = 0.35, color = color, group = "sheet-border")

                self.DWG.line(start=(105, 0), end=(105, 5), linewidth = 0.35, color = color, group = "sheet-border")

                # Horizontal
                self.DWG.line(start=(0, height-297), end=(15, height-297), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(width, height-297), end=(width-5, height-297), linewidth = 0.35, color = color, group = "sheet-border")
            if self.SIZE == (1189, 841):
                # Vertical
                self.DWG.line(start=(210, 0), end=(210, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(210, height), end=(210, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(400, 0), end=(400, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(400, height), end=(400, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(590, 0), end=(590, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(590, height), end=(590, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(780, 0), end=(780, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(780, height), end=(780, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(889.5, 0), end=(889.5, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(889.5, height), end=(889.5, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(999, 0), end=(999, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(999, height), end=(999, height-5), linewidth = 0.35, color = color, group = "sheet-border")

                self.DWG.line(start=(105, 0), end=(105, 5), linewidth = 0.35, color = color, group = "sheet-border")

                # Horizontal
                self.DWG.line(start=(0, height-297), end=(15, height-297), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(width, height-297), end=(width-5, height-297), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(0, height-297-297), end=(15, height-297-297), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(width, height-297-297), end=(width-5, height-297-297), linewidth = 0.35, color = color, group = "sheet-border")
            if self.SIZE == (1682, 1189):
                # Vertical
                w = 0

                w += 186
                self.DWG.line(start=(w, 0), end=(w, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(w, height), end=(w, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                w += 83
                self.DWG.line(start=(w, 0), end=(w, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(w, height), end=(w, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                w += 83
                self.DWG.line(start=(w, 0), end=(w, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(w, height), end=(w, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                w += 190 #1
                self.DWG.line(start=(w, 0), end=(w, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(w, height), end=(w, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                w += 190 #2
                self.DWG.line(start=(w, 0), end=(w, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(w, height), end=(w, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                w += 190 #3
                self.DWG.line(start=(w, 0), end=(w, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(w, height), end=(w, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                w += 190 #4
                self.DWG.line(start=(w, 0), end=(w, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(w, height), end=(w, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                w += 190 #5
                self.DWG.line(start=(w, 0), end=(w, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(w, height), end=(w, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                w += 190 #6
                self.DWG.line(start=(w, 0), end=(w, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(w, height), end=(w, height-5), linewidth = 0.35, color = color, group = "sheet-border")

                self.DWG.line(start=(105, 0), end=(105, 5), linewidth = 0.35, color = color, group = "sheet-border")

                # Horizontal
                self.DWG.line(start=(0, height-297), end=(15, height-297), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(width, height-297), end=(width-5, height-297), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(0, height-297-297), end=(15, height-297-297), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(width, height-297-297), end=(width-5, height-297-297), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(0, height-297-297-297), end=(15, height-297-297-297), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(width, height-297-297-297), end=(width-5, height-297-297-297), linewidth = 0.35, color = color, group = "sheet-border")

        # Folding Lines(200x290), only for ISO 216 A sizes execpt for 4A0
        if self.FOLD_LINES_200_X_290:
            if self.SIZE == (420, 297):
                # Vertical
                self.DWG.line(start=(125, 0), end=(125, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(125, height), end=(125, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(230, 0), end=(230, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(230, height), end=(230, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(410, 0), end=(410, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(410, height), end=(410, height-5), linewidth = 0.35, color = color, group = "sheet-border")

                # Horizontal
                self.DWG.line(start=(0, height-290), end=(15, height-290), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(width, height-290), end=(width-5, height-290), linewidth = 0.35, color = color, group = "sheet-border")
            if self.SIZE == (594, 420):
                # Vertical
                self.DWG.line(start=(200, 0), end=(200, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(200, height), end=(200, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(380, 0), end=(380, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(380, height), end=(380, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(392, 0), end=(392, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(392, height), end=(392, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(404, 0), end=(404, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(404, height), end=(404, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(584, 0), end=(584, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(584, height), end=(584, height-5), linewidth = 0.35, color = color, group = "sheet-border")

                self.DWG.line(start=(105, 0), end=(105, 5), linewidth = 0.35, color = color, group = "sheet-border")

                # Horizontal
                self.DWG.line(start=(0, height-290), end=(15, height-290), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(width, height-290), end=(width-5, height-290), linewidth = 0.35, color = color, group = "sheet-border")
            if self.SIZE == (841, 594):
                # Vertical
                self.DWG.line(start=(200, 0), end=(200, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(200, height), end=(200, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(380, 0), end=(380, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(380, height), end=(380, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(515.5, 0), end=(515.5, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(515.5, height), end=(515.5, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(651, 0), end=(651, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(651, height), end=(651, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(831, 0), end=(831, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(831, height), end=(831, height-5), linewidth = 0.35, color = color, group = "sheet-border")

                self.DWG.line(start=(105, 0), end=(105, 5), linewidth = 0.35, color = color, group = "sheet-border")

                # Horizontal
                self.DWG.line(start=(0, height-290), end=(15, height-290), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(width, height-290), end=(width-5, height-290), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(0, height-290-290), end=(15, height-290-290), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(width, height-290-290), end=(width-5, height-290-290), linewidth = 0.35, color = color, group = "sheet-border")
            if self.SIZE == (1189, 841):
                # Vertical
                self.DWG.line(start=(200, 0), end=(200, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(200, height), end=(200, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(380, 0), end=(380, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(380, height), end=(380, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(560, 0), end=(560, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(560, height), end=(560, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(740, 0), end=(740, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(740, height), end=(740, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(869.5, 0), end=(869.5, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(869.5, height), end=(869.5, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(999, 0), end=(999, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(999, height), end=(999, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(1179, 0), end=(1179, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(1179, height), end=(1179, height-5), linewidth = 0.35, color = color, group = "sheet-border")

                self.DWG.line(start=(105, 0), end=(105, 5), linewidth = 0.35, color = color, group = "sheet-border")

                # Horizontal
                self.DWG.line(start=(0, height-290), end=(15, height-290), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(width, height-290), end=(width-5, height-290), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(0, height-290-290), end=(15, height-290-290), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(width, height-290-290), end=(width-5, height-290-290), linewidth = 0.35, color = color, group = "sheet-border")
            if self.SIZE == (1682, 1189):
                # Vertical
                w = 0

                w += 200
                self.DWG.line(start=(w, 0), end=(w, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(w, height), end=(w, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                w += 106
                self.DWG.line(start=(w, 0), end=(w, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(w, height), end=(w, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                w += 106
                self.DWG.line(start=(w, 0), end=(w, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(w, height), end=(w, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                w += 180 #1
                self.DWG.line(start=(w, 0), end=(w, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(w, height), end=(w, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                w += 180 #2
                self.DWG.line(start=(w, 0), end=(w, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(w, height), end=(w, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                w += 180 #3
                self.DWG.line(start=(w, 0), end=(w, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(w, height), end=(w, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                w += 180 #4
                self.DWG.line(start=(w, 0), end=(w, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(w, height), end=(w, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                w += 180 #5
                print('5:' + str(w))
                self.DWG.line(start=(w, 0), end=(w, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(w, height), end=(w, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                w += 180 #6
                print('6:' + str(w))
                self.DWG.line(start=(w, 0), end=(w, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(w, height), end=(w, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                w += 180 #7
                print('7:' + str(w))
                self.DWG.line(start=(w, 0), end=(w, 5), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(w, height), end=(w, height-5), linewidth = 0.35, color = color, group = "sheet-border")

                self.DWG.line(start=(105, 0), end=(105, 5), linewidth = 0.35, color = color, group = "sheet-border")

                # Horizontal
                self.DWG.line(start=(0, height-290), end=(15, height-290), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(width, height-290), end=(width-5, height-290), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(0, height-290-290), end=(15, height-290-290), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(width, height-290-290), end=(width-5, height-290-290), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(0, height-290-290-290), end=(15, height-290-290-290), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(width, height-290-290-290), end=(width-5, height-290-290-290), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(0, height-290-290-290-290), end=(15, height-290-290-290-290), linewidth = 0.35, color = color, group = "sheet-border")
                self.DWG.line(start=(width, height-290-290-290-290), end=(width-5, height-290-290-290-290), linewidth = 0.35, color = color, group = "sheet-border")

        # Full sheet parts list
        if self.FULL_PARTS_LIST:
            if self.FULL_PARTS_LIST_SMALL_LINES:
                lineHeight = 10
            else:
                lineHeight = 20
            
            self.DWG.line(start=(20, 15), end=(width - 10, 15), linewidth = 0.35, color = color, group = "sheet-border")
            self.DWG.line(start=(20, 20), end=(width - 10, 20), linewidth = 0.7, color = color, group = "sheet-border")
            
            self.DWG.line(start=(35, 10), end=(35, (height - 65 - (11 * self.NUM_OPT_LINES))), linewidth = 0.35, color = color, group = "sheet-border")
            self.DWG.line(start=(55, 10), end=(55, (height - 65 - (11 * self.NUM_OPT_LINES))), linewidth = 0.35, color = color, group = "sheet-border")
            self.DWG.line(start=(70, 10), end=(70, (height - 65 - (11 * self.NUM_OPT_LINES))), linewidth = 0.35, color = color, group = "sheet-border")
            self.DWG.line(start=(130, 10), end=(130, (height - 65 - (11 * self.NUM_OPT_LINES))), linewidth = 0.35, color = color, group = "sheet-border")
            self.DWG.line(start=(165, 10), end=(165, (height - 65 - (11 * self.NUM_OPT_LINES))), linewidth = 0.35, color = color, group = "sheet-border")
            
            self.DWG.text(text = '1', position = (27.5, 12.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            self.DWG.text(text = '2', position = (45, 12.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            self.DWG.text(text = '3', position = (62.5, 12.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            self.DWG.text(text = '4', position = (100, 12.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            self.DWG.text(text = '5', position = (147.5, 12.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            self.DWG.text(text = '6', position = (182.5, 12.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            
            self.DWG.text(text = 'Pos.', position = (27.5, 17.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            self.DWG.text(text = 'Qty.', position = (45, 17.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            self.DWG.text(text = 'Unit', position = (62.5, 17.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            self.DWG.text(text = 'Titel', position = (100, 17.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            self.DWG.text(text = 'Document number', position = (147.5, 17.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            self.DWG.text(text = 'Comment', position = (182.5, 17.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            
            numLines = int((height - 85 - (11 * self.NUM_OPT_LINES)) / lineHeight)
            for h in range(numLines):
                hPos = (h + 1) * lineHeight + 20
                self.DWG.line(start=(20, hPos), end=(width - 10, hPos), linewidth = 0.35, color = color, group = "sheet-border")
                
                if not self.FULL_PARTS_LIST_SMALL_LINES:
                    self.DWG.text(text = 'Pos.' + str(h) + 'A', position = (27.5, hPos + 1.8 + 0.9 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 13, id = 'pos_a_' + str(h) + '_' + str(self.FULL_PARTS_LIST_NUM_SHEETS))
                    self.DWG.text(text = 'Qty.' + str(h) + 'A', position = (45, hPos + 1.8 + 0.9 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 18, id = 'qty_a_' + str(h) + '_' + str(self.FULL_PARTS_LIST_NUM_SHEETS))
                    self.DWG.text(text = 'Unit' + str(h) + 'A', position = (62.5, hPos + 1.8 + 0.9 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 13, id = 'unit_a_' + str(h) + '_' + str(self.FULL_PARTS_LIST_NUM_SHEETS))
                    self.DWG.text(text = 'Titel' + str(h) + 'A', position = (100, hPos + 1.8 + 0.9 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 58, id = 'titel_a_' + str(h) + '_' + str(self.FULL_PARTS_LIST_NUM_SHEETS))
                    self.DWG.text(text = 'Doc. number' + str(h) + 'A', position = (147.5, hPos + 1.8 + 0.9 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 33, id = 'doc_num_a_' + str(h) + '_' + str(self.FULL_PARTS_LIST_NUM_SHEETS))
                    self.DWG.text(text = 'Comment' + str(h) + 'A', position = (182.5, hPos + 1.8 + 0.9 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 33, id = 'comment_a_' + str(h) + '_' + str(self.FULL_PARTS_LIST_NUM_SHEETS))
                
                    self.DWG.text(text = 'Pos.' + str(h) + 'B', position = (27.5, hPos + 9.65 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 13, id = 'pos_b_' + str(h) + '_' + str(self.FULL_PARTS_LIST_NUM_SHEETS))
                    self.DWG.text(text = 'Qty.' + str(h) + 'B', position = (45, hPos + 9.65 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 18, id = 'qty_b_' + str(h) + '_' + str(self.FULL_PARTS_LIST_NUM_SHEETS))
                    self.DWG.text(text = 'Unit' + str(h) + 'B', position = (62.5, hPos + 9.65 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 13, id = 'unit_b_' + str(h) + '_' + str(self.FULL_PARTS_LIST_NUM_SHEETS))
                    self.DWG.text(text = 'Titel' + str(h) + 'B', position = (100, hPos + 9.65 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 58, id = 'titel_b_' + str(h) + '_' + str(self.FULL_PARTS_LIST_NUM_SHEETS))
                    self.DWG.text(text = 'Doc. number' + str(h) + 'B', position = (147.5, hPos + 9.65 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 33, id = 'doc_num_b_' + str(h) + '_' + str(self.FULL_PARTS_LIST_NUM_SHEETS))
                    self.DWG.text(text = 'Comment' + str(h) + 'B', position = (182.5, hPos + 9.65 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 33, id = 'comment_c_' + str(h) + '_' + str(self.FULL_PARTS_LIST_NUM_SHEETS))
                    
                    self.DWG.text(text = 'Pos.' + str(h) + 'C', position = (27.5, hPos + 16.3 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 13, id = 'pos_c_' + str(h) + '_' + str(self.FULL_PARTS_LIST_NUM_SHEETS))
                    self.DWG.text(text = 'Qty.' + str(h) + 'C', position = (45, hPos + 16.3 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 18, id = 'qty_c_' + str(h) + '_' + str(self.FULL_PARTS_LIST_NUM_SHEETS))
                    self.DWG.text(text = 'Unit' + str(h) + 'C', position = (62.5, hPos + 16.3 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 13, id = 'unit_c_' + str(h) + '_' + str(self.FULL_PARTS_LIST_NUM_SHEETS))
                    self.DWG.text(text = 'Titel' + str(h) + 'C', position = (100, hPos + 16.3 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 58, id = 'titel_c_' + str(h) + '_' + str(self.FULL_PARTS_LIST_NUM_SHEETS))
                    self.DWG.text(text = 'Doc. number' + str(h) + 'C', position = (147.5, hPos + 16.3 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 33, id = 'doc_num_c_' + str(h) + '_' + str(self.FULL_PARTS_LIST_NUM_SHEETS))
                    self.DWG.text(text = 'Comment' + str(h) + 'C', position = (182.5, hPos + 16.3 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 33, id = 'comment_c_' + str(h) + '_' + str(self.FULL_PARTS_LIST_NUM_SHEETS))
                else:
                    self.DWG.text(text = 'Pos.' + str(h) + 'A', position = (27.5, hPos + 5 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 13, id = 'pos_a_' + str(h) + '_' + str(self.FULL_PARTS_LIST_NUM_SHEETS))
                    self.DWG.text(text = 'Qty.' + str(h) + 'A', position = (45, hPos + 5 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 18, id = 'qty_a_' + str(h) + '_' + str(self.FULL_PARTS_LIST_NUM_SHEETS))
                    self.DWG.text(text = 'Unit' + str(h) + 'A', position = (62.5, hPos + 5 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 13, id = 'unit_a_' + str(h) + '_' + str(self.FULL_PARTS_LIST_NUM_SHEETS))
                    self.DWG.text(text = 'Titel' + str(h) + 'A', position = (100, hPos + 5 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 58, id = 'titel_a_' + str(h) + '_' + str(self.FULL_PARTS_LIST_NUM_SHEETS))
                    self.DWG.text(text = 'Doc. number' + str(h) + 'A', position = (147.5, hPos + 5 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 33, id = 'doc_num_a_' + str(h) + '_' + str(self.FULL_PARTS_LIST_NUM_SHEETS))
                    self.DWG.text(text = 'Comment' + str(h) + 'A', position = (182.5, hPos + 5 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 33, id = 'comment_a_' + str(h) + '_' + str(self.FULL_PARTS_LIST_NUM_SHEETS))
        
        
        # Small parts list over the Titelblock
        if self.SMALL_PARTS_LIST:
            self.DWG.rect(start=(width - 190, height - 75 - (self.SMALL_PARTS_LIST_NUM_LINES * 11) - (self.NUM_OPT_LINES * 11)), end=(width - 10, height - 65 - (self.NUM_OPT_LINES * 11)), linewidth = 0.7, color = color, group = "titleblock-structure")
            # Horizontal
            self.DWG.line(start=(width - 190, height - 70 - self.NUM_OPT_LINES * 11 - (self.SMALL_PARTS_LIST_NUM_LINES * 11)), end=(width - 10, height - 70 - self.NUM_OPT_LINES * 11 - (self.SMALL_PARTS_LIST_NUM_LINES * 11)), linewidth = 0.35, color = color, group = "titleblock-structure")
            
            hPos = height - 75 - self.NUM_OPT_LINES * 11 - (self.SMALL_PARTS_LIST_NUM_LINES * 11)
            self.DWG.text(text = '1', position = (width - 182.5, hPos + 2.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-not-editable")
            self.DWG.text(text = '2', position = (width - 165, hPos + 2.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-not-editable")
            self.DWG.text(text = '3', position = (width - 147.5, hPos + 2.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-not-editable")
            self.DWG.text(text = '4', position = (width - 110, hPos + 2.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-not-editable")
            self.DWG.text(text = '5', position = (width - 62.5, hPos + 2.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-not-editable")
            self.DWG.text(text = '6', position = (width - 27.5, hPos + 2.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-not-editable")
            
            hPos = height - 70 - self.NUM_OPT_LINES * 11 - (self.SMALL_PARTS_LIST_NUM_LINES * 11)
            self.DWG.text(text = 'Pos.', position = (width - 182.5, hPos + 2.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-not-editable")
            self.DWG.text(text = 'Qty.', position = (width - 165, hPos + 2.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-not-editable")
            self.DWG.text(text = 'Unit', position = (width - 147.5, hPos + 2.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-not-editable")
            self.DWG.text(text = 'Titel', position = (width - 110, hPos + 2.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-not-editable")
            self.DWG.text(text = 'Doc. number', position = (width - 62.5, hPos + 2.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-not-editable")
            self.DWG.text(text = 'Comment', position = (width - 27.5, hPos + 2.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-not-editable")
            
            for h in range(self.SMALL_PARTS_LIST_NUM_LINES):
                hPos = height - 75 - self.NUM_OPT_LINES * 11 - ((h) * 11)
                if h == self.SMALL_PARTS_LIST_NUM_LINES - 1:
                    self.DWG.line(start=(width - 190, hPos), end=(width - 10, hPos), linewidth = 0.7, color = color, group = "titleblock-structure")
                else:
                    self.DWG.line(start=(width - 190, hPos), end=(width - 10, hPos), linewidth = 0.35, color = color, group = "titleblock-structure")
                    
                self.DWG.text(text = 'Pos.' + str(h) + 'A', position = (width - 182.5, hPos + 5.5), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 13, id = 'pos_' + str(h))
                self.DWG.text(text = 'Qty.' + str(h) + 'A', position = (width - 165, hPos + 5.5), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 18, id = 'qty_' + str(h))
                self.DWG.text(text = 'Unit' + str(h) + 'A', position = (width - 147.5, hPos + 5.5), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 13, id = 'unit_' + str(h))
                self.DWG.text(text = 'Titel' + str(h) + 'A', position = (width - 110, hPos + 5.5), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 58, id = 'titel_' + str(h))
                self.DWG.text(text = 'Doc. number' + str(h) + 'A', position = (width - 62.5, hPos + 5.5), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 33, id = 'doc_num_' + str(h))
                self.DWG.text(text = 'Comment' + str(h) + 'A', position = (width - 27.5, hPos + 5.5), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 33, id = 'comment_' + str(h))
            
            # Vertical
            self.DWG.line(start=(width - 175, height - 75 - self.NUM_OPT_LINES * 11 - (self.SMALL_PARTS_LIST_NUM_LINES * 11)), end=(width - 175, height - 65 - self.NUM_OPT_LINES * 11), linewidth = 0.35, color = color, group = "titleblock-structure")
            self.DWG.line(start=(width - 155, height - 75 - self.NUM_OPT_LINES * 11 - (self.SMALL_PARTS_LIST_NUM_LINES * 11)), end=(width - 155, height - 65 - self.NUM_OPT_LINES * 11), linewidth = 0.35, color = color, group = "titleblock-structure")
            self.DWG.line(start=(width - 140, height - 75 - self.NUM_OPT_LINES * 11 - (self.SMALL_PARTS_LIST_NUM_LINES * 11)), end=(width - 140, height - 65 - self.NUM_OPT_LINES * 11), linewidth = 0.35, color = color, group = "titleblock-structure")
            self.DWG.line(start=(width - 80, height - 75 - self.NUM_OPT_LINES * 11 - (self.SMALL_PARTS_LIST_NUM_LINES * 11)), end=(width - 80, height - 65 - self.NUM_OPT_LINES * 11), linewidth = 0.35, color = color, group = "titleblock-structure")
            self.DWG.line(start=(width - 45, height - 75 - self.NUM_OPT_LINES * 11 - (self.SMALL_PARTS_LIST_NUM_LINES * 11)), end=(width - 45, height - 65 - self.NUM_OPT_LINES * 11), linewidth = 0.35, color = color, group = "titleblock-structure")
            
        self.FULL_PARTS_LIST_NUM_SHEETS -= 1
        if self.FULL_PARTS_LIST_NUM_SHEETS > 0:
            self.DWG.newPage()
            self.drawISO5457_ISO700_A()
        else:
            self.DWG.__del__()

    def drawISO5457_ISO700_B(self):
        sizeStringFile = self.SIZE_STRING.replace(' ', '_')
        filename = sizeStringFile + '_ISO5457_ISO7200_B'
        if self.NUM_OPT_LINES > 0:
            filename += '+' + str(self.NUM_OPT_LINES)
        if self.REV_HISTORY:
            filename +='_rh+' + str(self.NUMREVISIONS)
        if self.FOLD_LINES_DIN824_A:
            filename += '_fl'
        if self.FULL_PARTS_LIST:
            filename += '_fspl'
            if self.FULL_PARTS_LIST_SMALL_LINES:
                filename += '_sl'
            if self.FULL_PARTS_LIST_NUM_SHEETS > 1:
                filename += '_' + str(self.FULL_PARTS_LIST_NUM_SHEETS) + '_sh'
        if self.SMALL_PARTS_LIST:
            filename += '_spl+' + str(self.SMALL_PARTS_LIST_NUM_LINES)
        if self.COLOR != '#000000':
            filename += '_c_' + self.COLOR.replace('#', '')
        print(filename)

        try:
            os.mkdir("./out/");
        except OSError as error:
            pass

        try:
            os.mkdir("./out/" + filename);
        except OSError as error:
            pass

        self.DWG = UniversalDraw(size = self.SIZE, filename = "./out/" + filename + '/' + filename)
        dwg = self.DWG
        size = self.SIZE
        sizeString = self.SIZE_STRING
        color = self.COLOR
        height = size[1];
        width = size[0];

        # Cutting marks
        # Top Left
        dwg.polygon(linewidth = 0.0, points = [(0, 0), (10, 0), (10, 5), (5, 5), (5, 10), (0, 10), (0, 0)], color = color, fill = color, group = "sheet-border")
        # Top Right
        dwg.polygon(linewidth = 0.0, points = [(0+width, 0), (-10+width, 0), (-10+width, 5), (-5+width, 5), (-5+width, 10), (0+width, 10), (0+width, 0)], color = color, fill = color, group = "sheet-border")
        # Bottom Right
        dwg.polygon(linewidth = 0.0, points = [(0+width, 0+height), (-10+width, 0+height), (-10+width, -5+height), (-5+width, -5+height), (-5+width, -10+height), (0+width, -10+height), (0+width, -0+height)], color = color, fill = color, group = "sheet-border")
        # Bottom Left
        dwg.polygon(linewidth = 0.0, points = [(0, 0+height), (10, 0+height), (10, -5+height), (5, -5+height), (5, -10+height), (0, -10+height), (0, -0+height)], color = color, fill = color, group = "sheet-border")

        # Sheet border
        dwg.rect(start=(0, 0), end=(width, height), linewidth = 0.35, color = color, group = "sheet-border")
        dwg.rect(start=(15, 5), end=(width - 5, height - 5), linewidth = 0.35, color = color, group = "sheet-border")
        dwg.rect(start=(20, 10), end=(width - 10, height - 10), linewidth = 0.7, color = color, group = "sheet-border")

        # Sheet border Top and Bottom
        halfWidth = width / 2
        if (width - 180) > halfWidth:
            dwg.line(start=(halfWidth, height-5), end=(halfWidth, height-20), linewidth = 0.7, color = color, group = "sheet-border")
            dwg.line(start=(halfWidth, 5), end=(halfWidth, 20), linewidth = 0.7, color = color, group = "sheet-border")
        else:
            dwg.line(start=(halfWidth, height-5), end=(halfWidth, height-10), linewidth = 0.7, color = color, group = "sheet-border")
            dwg.line(start=(halfWidth, 5), end=(halfWidth, 10), linewidth = 0.7, color = color, group = "sheet-border")

        widthIndexLeft = halfWidth
        widthIndexRight = halfWidth

        letterPlaceWidth = []

        letterPlaceWidth.append(widthIndexLeft - 25)
        widthIndexLeft -= 50
        while widthIndexLeft > 0 + 20 :
            dwg.line(start=(widthIndexLeft, 5), end=(widthIndexLeft, 10), linewidth = 0.35, color = color, group = "sheet-border")
            dwg.line(start=(widthIndexLeft, height-5), end=(widthIndexLeft, height-10), linewidth = 0.35, color = color, group = "sheet-border")
            if (widthIndexLeft - 25) > 0 + 20:
                letterPlaceWidth.append(widthIndexLeft - 25)
            widthIndexLeft -= 50

        letterPlaceWidth.append(widthIndexRight + 25)
        widthIndexRight += 50
        while widthIndexRight < width - 10:
            dwg.line(start=(widthIndexRight, 5), end=(widthIndexRight, 10), linewidth = 0.35, color = color, group = "sheet-border")
            dwg.line(start=(widthIndexRight, height-5), end=(widthIndexRight, height-10), linewidth = 0.35, color = color, group = "sheet-border")
            if (widthIndexRight + 25) < width - 10:
                letterPlaceWidth.append(widthIndexRight + 25)
            widthIndexRight += 50

        letterPlaceWidth.sort()
        letterIndex = 1
        for i in letterPlaceWidth:
            dwg.text(text = str(letterIndex), position = (i, 7.75), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "sheet-border")
            if width >= 300 and height >= 290 and not i == letterPlaceWidth[-1]:
                dwg.text(text = str(letterIndex), position = (i, height - 7.25), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "sheet-border")
            if i == letterPlaceWidth[-1]:
                x = (i - 25) + (((width - 10) - (i - 25)) / 2)
                dwg.text(text = sizeString, position = (x, height - 7.25), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "sheet-border")
            letterIndex += 1

        # Sheet border Left and Right
        heightHalf = height / 2
        headerHeight = 65 + (self.NUM_OPT_LINES *11)
        if self.SMALL_PARTS_LIST:
            headerHeight += 10 + (self.SMALL_PARTS_LIST_NUM_LINES * 11)

        if self.FULL_PARTS_LIST:
            dwg.line(start=(15, heightHalf), end=(20, heightHalf), linewidth = 0.7, color = color, group = "sheet-border")
        else:
            dwg.line(start=(15, heightHalf), end=(30, heightHalf), linewidth = 0.7, color = color, group = "sheet-border")
        
        if (height - headerHeight) < heightHalf or 20 + (self.NUMREVISIONS * 15) > heightHalf or self.FULL_PARTS_LIST:
            dwg.line(start=(width - 5, heightHalf), end=(width - 10, heightHalf), linewidth = 0.7, color = color, group = "sheet-border")
        else:
            dwg.line(start=(width - 5, heightHalf), end=(width - 20, heightHalf), linewidth = 0.7, color = color, group = "sheet-border")

        heightIndexTop = heightHalf
        heightIndexBottom = heightHalf

        letterPlaceHeight = []

        letterPlaceHeight.append(heightIndexTop - 25)
        heightIndexTop -= 50
        while heightIndexTop > 0 + 10 :
            dwg.line(start=(15, heightIndexTop), end=(20, heightIndexTop), linewidth = 0.35, color = color, group = "sheet-border")
            dwg.line(start=(width-5, heightIndexTop), end=(width-10, heightIndexTop), linewidth = 0.35, color = color, group = "sheet-border")
            if (heightIndexTop - 25) > 0 + 10:
                letterPlaceHeight.append(heightIndexTop - 25)
            heightIndexTop -= 50

        letterPlaceHeight.append(heightIndexBottom + 25)
        heightIndexBottom += 50
        while heightIndexBottom < height - 10:
            dwg.line(start=(15, heightIndexBottom), end=(20, heightIndexBottom), linewidth = 0.35, color = color, group = "sheet-border")
            dwg.line(start=(width-5, heightIndexBottom), end=(width-10, heightIndexBottom), linewidth = 0.35, color = color, group = "sheet-border")
            if (heightIndexBottom + 25) < height - 10:
                letterPlaceHeight.append(heightIndexBottom + 25)
            heightIndexBottom += 50

        letterPlaceHeight.sort()
        letterIndex = 1
        for i in letterPlaceHeight:
            dwg.text(text = numToABC(letterIndex), position = (17.25, i), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "sheet-border")
            if width >= 300 and height >= 290:
                dwg.text(text = numToABC(letterIndex), position = (width-7.75, i), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "sheet-border")
            letterIndex += 1

        # Main titelblock lines
        dwg.rect(start=(width - 190, height - 65 - (self.NUM_OPT_LINES * 11)), end=(width - 10, height - 10), linewidth = 0.7, color = color, group = "titleblock-structure")

        dwg.line(start=(width - 35, height - 10), end=(width - 35, height - 32), linewidth = 0.35, color = color, group = "titleblock-structure")
        dwg.line(start=(width - 50, height - 10), end=(width - 50, height - 65 - (self.NUM_OPT_LINES *11)), linewidth = 0.35, color = color, group = "titleblock-structure")
        dwg.line(start=(width - 110, height - 10), end=(width - 110, height - 65 - (self.NUM_OPT_LINES *11)), linewidth = 0.35, color = color, group = "titleblock-structure")

        dwg.line(start=(width - 10, height - 21), end=(width - 50, height - 21), linewidth = 0.35, color = color, group = "titleblock-structure")
        dwg.line(start=(width - 10, height - 32), end=(width - 50, height - 32), linewidth = 0.35, color = color, group = "titleblock-structure")
        dwg.line(start=(width - 10, height - 43), end=(width - 190, height - 43), linewidth = 0.35, color = color, group = "titleblock-structure")
        dwg.line(start=(width - 10, height - 54), end=(width - 190, height - 54), linewidth = 0.35, color = color, group = "titleblock-structure")

        # Main titelblock text
        dwg.text(text = 'Sheet', position = (width - 35 + 0.5, height - 21+ 3), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-non-editable")
        dwg.text(text = '%S/%N', position = (width - 35 + 0.5, height - 21+ 3 + 6.25), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable")
        dwg.text(text = 'Lang.', position = (width - 50 + 0.5, height - 21+ 3), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-non-editable")
        dwg.text(text = 'EN', position = (width - 50 + 0.5, height - 21+ 3 + 6.25), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable")
        dwg.text(text = 'Rev.', position = (width - 50 + 0.5, height - 32 + 3), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-non-editable")
        dwg.text(text = '%R', position = (width - 50 + 0.5, height - 32 + 3 + 6.25), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable")
        dwg.text(text = 'Date of issue', position = (width - 35 + 0.5, height - 32 + 3), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-non-editable")
        dwg.text(text = '%D', position = (width - 35 + 0.5, height - 32 + 3 + 6.25), tsize = 3, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable")

        dwg.text(text = 'Document number', position = (width - 50 + 0.5, height - 43 + 3), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-non-editable")
        dwg.text(text = '%C6', position = (width - 50 + 0.5, height - 43 + 3 + 6.25), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable")
        dwg.text(text = 'Titel, Supplementary titel', position = (width - 110 + 0.5, height - 43 + 3), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-non-editable")
        dwg.text(text = '%C8', position = (width - 110 + 0.5, height - 43 + 3 + 12.5), tsize = 7, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable")
        dwg.text(text = '%T', position = (width - 110 + 0.5, height - 43 + 3 + 12.5 + 12.5), tsize = 7, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable")
        dwg.text(text = 'Legal owner', position = (width - 190 + 0.5, height - 43 + 3), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-non-editable")
        dwg.text(text = '%C7', position = (width - 190 + 0.5, height - 43 + 3 + 12.5), tsize = 7, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable")
        dwg.text(text = '%Y', position = (width - 190 + 0.5, height - 43 + 3 + 12.5 + 12.5), tsize = 7, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable")
        dwg.text(text = 'Approved by', position = (width - 190 + 0.5, height - 54 + 3), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-non-editable")
        dwg.text(text = '%C1', position = (width - 190 + 0.5, height - 54 + 3 + 6.25), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable")
        dwg.text(text = 'Projekt', position = (width - 110 + 0.5, height - 54 + 3), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-non-editable")
        dwg.text(text = '%C3', position = (width - 110 + 0.5, height - 54 + 3 + 6.25), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable")
        dwg.text(text = 'Document type', position = (width - 50 + 0.5, height - 54 + 3), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-non-editable")
        dwg.text(text = '%C5', position = (width - 50 + 0.5, height - 54 + 3 + 6.25), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable")
        dwg.text(text = 'Created by', position = (width - 190 + 0.5, height - 65 + 3), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-non-editable")
        dwg.text(text = '%C0', position = (width - 190 + 0.5, height - 65 + 3 + 6.25), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable")
        dwg.text(text = 'Valid from to', position = (width - 110 + 0.5, height - 65 + 3), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-non-editable")
        dwg.text(text = '%C2', position = (width - 110 + 0.5, height - 65 + 3 + 6.25), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable")
        dwg.text(text = 'Document state', position = (width - 50 + 0.5, height - 65 + 3), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-non-editable")
        dwg.text(text = '%C4', position = (width - 50 + 0.5, height - 65 + 3 + 6.25), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable")


        # Optional titelblock
        for i in range(self.NUM_OPT_LINES):
            dwg.line(start=(width - 10, height - 65 - (11 * i)), end=(width - 190, height - 65 - (11 * i)), linewidth = 0.35, color = color, group = "titleblock-structure")
            if i == 0:
                dwg.text(text = 'A', position = (width - 190 + 0.5, height - 65 - (11 * (i + 1)) + 3), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable")
                dwg.text(text = 'B', position = (width - 190 + 0.5, height - 65 - (11 * (i + 1)) + 3 + 6.25), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable")
                dwg.text(text = 'Raw dimensions', position = (width - 110 + 0.5, height - 65 - (11 * (i + 1)) + 3), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable")
                dwg.text(text = 'C', position = (width - 110 + 0.5, height - 65 - (11 * (i + 1)) + 3 + 6.25), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable")
                dwg.text(text = 'Scale', position = (width - 50 + 0.5, height - 65 - (11 * (i + 1)) + 3), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable")
                dwg.text(text = '1:1', position = (width - 50 + 0.5, height - 65 - (11 * (i + 1)) + 3 + 6.25), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable")
            elif i == 1:
                dwg.text(text = 'Surface treatment', position = (width - 190 + 0.5, height - 65 - (11 * (i + 1)) + 3), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable")
                dwg.text(text = 'Surface treatment', position = (width - 190 + 0.5, height - 65 - (11 * (i + 1)) + 3 + 6.25), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable")
                dwg.text(text = 'Weight', position = (width - 110 + 0.5, height - 65 - (11 * (i + 1)) + 3), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable")
                dwg.text(text = 'Weight', position = (width - 110 + 0.5, height - 65 - (11 * (i + 1)) + 3 + 6.25), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable")
                dwg.text(text = 'Standard', position = (width - 50 + 0.5, height - 65 - (11 * (i + 1)) + 3), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable")
                dwg.text(text = 'Standard', position = (width - 50 + 0.5, height - 65 - (11 * (i + 1)) + 3 + 6.25), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable")
            elif i == 2:
                dwg.text(text = 'Option X', position = (width - 190 + 0.5, height - 65 - (11 * (i + 1)) + 3), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable")
                dwg.text(text = 'Option X', position = (width - 190 + 0.5, height - 65 - (11 * (i + 1)) + 3 + 6.25), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable")
                dwg.text(text = 'Option Y', position = (width - 110 + 0.5, height - 65 - (11 * (i + 1)) + 3), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable")
                dwg.text(text = 'Option Y', position = (width - 110 + 0.5, height - 65 - (11 * (i + 1)) + 3 + 6.25), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable")
                dwg.text(text = 'Option Z', position = (width - 50 + 0.5, height - 65 - (11 * (i + 1)) + 3), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable")
                dwg.text(text = 'Option Z', position = (width - 50 + 0.5, height - 65 - (11 * (i + 1)) + 3 + 6.25), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable")

        # Revision History
        if self.REV_HISTORY:
            dwg.rect(start=(width-190, 10), end=(width-10, 20 + (self.NUMREVISIONS * 15)), linewidth = 0.7, color = color, group = "sheet-border")
            dwg.line(start=(width-190, 15), end=(width-10, 15), linewidth = 0.35, color = color, group = "sheet-border")
            dwg.line(start=(width-190, 20), end=(width-10, 20), linewidth = 0.7, color = color, group = "sheet-border")
            dwg.line(start=(width-175, 15), end=(width-175, 20 + (self.NUMREVISIONS * 15)), linewidth = 0.35, color = color, group = "sheet-border")
            dwg.line(start=(width-155, 15), end=(width-155, 20 + (self.NUMREVISIONS * 15)), linewidth = 0.35, color = color, group = "sheet-border")
            dwg.line(start=(width-60, 15), end=(width-60, 20 + (self.NUMREVISIONS * 15)), linewidth = 0.35, color = color, group = "sheet-border")
            dwg.line(start=(width-40, 15), end=(width-40, 20 + (self.NUMREVISIONS * 15)), linewidth = 0.35, color = color, group = "sheet-border")

            dwg.text(text = 'Revision History', position = (width - 100, 12.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            dwg.text(text = 'Zone', position = (width - 182.5, 17.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            dwg.text(text = 'Rev.', position = (width - 165, 17.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            dwg.text(text = 'Description', position = (width - 107.5, 17.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            dwg.text(text = 'Date', position = (width - 50, 17.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            dwg.text(text = 'Created by', position = (width - 25, 17.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")

            for i in range(self.NUMREVISIONS):
                dwg.line(start=(width-190, 20 + (i * 15)), end=(width-10, 20 + (i * 15)), linewidth = 0.35, color = color, group = "sheet-border")
                dwg.text(text = 'ZoneA', position = (width - 182.5, 17.75 + ((i + 1) * 15)), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable")
                dwg.text(text = 'Rev.A', position = (width - 165, 17.75 + ((i + 1) * 15)), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable")
                dwg.text(text = 'DescriptionA', position = (width - 107.5, 17.75 + ((i + 1) * 15)), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable")
                dwg.text(text = 'DateA', position = (width - 50, 17.75 + ((i + 1) * 15)), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable")
                dwg.text(text = 'Created byA', position = (width - 25, 17.75 + ((i + 1) * 15)), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable")
                dwg.text(text = 'ZoneB', position = (width - 182.5, 13 + ((i + 1) * 15)), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable")
                dwg.text(text = 'Rev.B', position = (width - 165, 13 + ((i + 1) * 15)), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable")
                dwg.text(text = 'DescriptionB', position = (width - 107.5, 13 + ((i + 1) * 15)), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable")
                dwg.text(text = 'DateB', position = (width - 50, 13 + ((i + 1) * 15)), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable")
                dwg.text(text = 'Created byB', position = (width - 25, 13 + ((i + 1) * 15)), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable")
                dwg.text(text = 'ZoneC', position = (width - 182.5, 8.25 + ((i + 1) * 15)), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable")
                dwg.text(text = 'Rev.C', position = (width - 165, 8.25 + ((i + 1) * 15)), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable")
                dwg.text(text = 'DescriptionC', position = (width - 107.5, 8.25 + ((i + 1) * 15)), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable")
                dwg.text(text = 'DateC', position = (width - 50, 8.25 + ((i + 1) * 15)), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable")
                dwg.text(text = 'Created byC', position = (width - 25, 8.25 + ((i + 1) * 15)), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable")



        # Folding Lines, only for ISO 216 A sizes execpt for 4A0
        if self.FOLD_LINES_DIN824_A:
            if self.SIZE == (420, 297):
                # Vertical
                dwg.line(start=(125, 0), end=(125, 5), linewidth = 0.35, color = color, group = "sheet-border")
                dwg.line(start=(125, height), end=(125, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                dwg.line(start=(230, 0), end=(230, 5), linewidth = 0.35, color = color, group = "sheet-border")
                dwg.line(start=(230, height), end=(230, height-5), linewidth = 0.35, color = color, group = "sheet-border")
            if self.SIZE == (594, 420):
                # Vertical
                dwg.line(start=(210, 0), end=(210, 5), linewidth = 0.35, color = color, group = "sheet-border")
                dwg.line(start=(210, height), end=(210, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                dwg.line(start=(402, 0), end=(402, 5), linewidth = 0.35, color = color, group = "sheet-border")
                dwg.line(start=(402, height), end=(402, height-5), linewidth = 0.35, color = color, group = "sheet-border")

                dwg.line(start=(105, 0), end=(105, 5), linewidth = 0.35, color = color, group = "sheet-border")

                # Horizontal
                dwg.line(start=(0, height-297), end=(15, height-297), linewidth = 0.35, color = color, group = "sheet-border")
                dwg.line(start=(width, height-297), end=(width-5, height-297), linewidth = 0.35, color = color, group = "sheet-border")
            if self.SIZE == (841, 594):
                # Vertical
                dwg.line(start=(210, 0), end=(210, 5), linewidth = 0.35, color = color, group = "sheet-border")
                dwg.line(start=(210, height), end=(210, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                dwg.line(start=(400, 0), end=(400, 5), linewidth = 0.35, color = color, group = "sheet-border")
                dwg.line(start=(400, height), end=(400, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                dwg.line(start=(525.5, 0), end=(525.5, 5), linewidth = 0.35, color = color, group = "sheet-border")
                dwg.line(start=(525.5, height), end=(525.5, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                dwg.line(start=(651, 0), end=(651, 5), linewidth = 0.35, color = color, group = "sheet-border")
                dwg.line(start=(651, height), end=(651, height-5), linewidth = 0.35, color = color, group = "sheet-border")

                dwg.line(start=(105, 0), end=(105, 5), linewidth = 0.35, color = color, group = "sheet-border")

                # Horizontal
                dwg.line(start=(0, height-297), end=(15, height-297), linewidth = 0.35, color = color, group = "sheet-border")
                dwg.line(start=(width, height-297), end=(width-5, height-297), linewidth = 0.35, color = color, group = "sheet-border")
            if self.SIZE == (1189, 841):
                # Vertical
                dwg.line(start=(210, 0), end=(210, 5), linewidth = 0.35, color = color, group = "sheet-border")
                dwg.line(start=(210, height), end=(210, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                dwg.line(start=(400, 0), end=(400, 5), linewidth = 0.35, color = color, group = "sheet-border")
                dwg.line(start=(400, height), end=(400, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                dwg.line(start=(590, 0), end=(590, 5), linewidth = 0.35, color = color, group = "sheet-border")
                dwg.line(start=(590, height), end=(590, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                dwg.line(start=(780, 0), end=(780, 5), linewidth = 0.35, color = color, group = "sheet-border")
                dwg.line(start=(780, height), end=(780, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                dwg.line(start=(889.5, 0), end=(889.5, 5), linewidth = 0.35, color = color, group = "sheet-border")
                dwg.line(start=(889.5, height), end=(889.5, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                dwg.line(start=(999, 0), end=(999, 5), linewidth = 0.35, color = color, group = "sheet-border")
                dwg.line(start=(999, height), end=(999, height-5), linewidth = 0.35, color = color, group = "sheet-border")

                dwg.line(start=(105, 0), end=(105, 5), linewidth = 0.35, color = color, group = "sheet-border")

                # Horizontal
                dwg.line(start=(0, height-297), end=(15, height-297), linewidth = 0.35, color = color, group = "sheet-border")
                dwg.line(start=(width, height-297), end=(width-5, height-297), linewidth = 0.35, color = color, group = "sheet-border")
                dwg.line(start=(0, height-297-297), end=(15, height-297-297), linewidth = 0.35, color = color, group = "sheet-border")
                dwg.line(start=(width, height-297-297), end=(width-5, height-297-297), linewidth = 0.35, color = color, group = "sheet-border")
            if self.SIZE == (1682, 1189):
                # Vertical
                w = 0

                w += 186
                dwg.line(start=(w, 0), end=(w, 5), linewidth = 0.35, color = color, group = "sheet-border")
                dwg.line(start=(w, height), end=(w, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                w += 83
                dwg.line(start=(w, 0), end=(w, 5), linewidth = 0.35, color = color, group = "sheet-border")
                dwg.line(start=(w, height), end=(w, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                w += 83
                dwg.line(start=(w, 0), end=(w, 5), linewidth = 0.35, color = color, group = "sheet-border")
                dwg.line(start=(w, height), end=(w, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                w += 190
                dwg.line(start=(w, 0), end=(w, 5), linewidth = 0.35, color = color, group = "sheet-border")
                dwg.line(start=(w, height), end=(w, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                w += 190
                dwg.line(start=(w, 0), end=(w, 5), linewidth = 0.35, color = color, group = "sheet-border")
                dwg.line(start=(w, height), end=(w, height-5), linewidth = 0.35, color = color, group = "sheet-border")
                w += 190
                dwg.line(start=(w, 0), end=(w, 5), linewidth = 0.35, color = color, group = "sheet-border")
                dwg.line(start=(w, height), end=(w, height-5), linewidth = 0.35, color = color, group = "sheet-border")

                dwg.line(start=(105, 0), end=(105, 5), linewidth = 0.35, color = color, group = "sheet-border")

                # Horizontal
                dwg.line(start=(0, height-297), end=(15, height-297), linewidth = 0.35, color = color, group = "sheet-border")
                dwg.line(start=(width, height-297), end=(width-5, height-297), linewidth = 0.35, color = color, group = "sheet-border")
                dwg.line(start=(0, height-297-297), end=(15, height-297-297), linewidth = 0.35, color = color, group = "sheet-border")
                dwg.line(start=(width, height-297-297), end=(width-5, height-297-297), linewidth = 0.35, color = color, group = "sheet-border")
                dwg.line(start=(0, height-297-297-297), end=(15, height-297-297-297), linewidth = 0.35, color = color, group = "sheet-border")
                dwg.line(start=(width, height-297-297-297), end=(width-5, height-297-297-297), linewidth = 0.35, color = color, group = "sheet-border")

        # Full sheet parts list
        if self.FULL_PARTS_LIST:
            if self.FULL_PARTS_LIST_SMALL_LINES:
                lineHeight = 10
            else:
                lineHeight = 20
            
            dwg.line(start=(20, 15), end=(width - 10, 15), linewidth = 0.35, color = color, group = "sheet-border")
            dwg.line(start=(20, 20), end=(width - 10, 20), linewidth = 0.7, color = color, group = "sheet-border")
            
            dwg.line(start=(35, 10), end=(35, (height - 65 - (11 * self.NUM_OPT_LINES))), linewidth = 0.35, color = color, group = "sheet-border")
            dwg.line(start=(55, 10), end=(55, (height - 65 - (11 * self.NUM_OPT_LINES))), linewidth = 0.35, color = color, group = "sheet-border")
            dwg.line(start=(70, 10), end=(70, (height - 65 - (11 * self.NUM_OPT_LINES))), linewidth = 0.35, color = color, group = "sheet-border")
            dwg.line(start=(130, 10), end=(130, (height - 65 - (11 * self.NUM_OPT_LINES))), linewidth = 0.35, color = color, group = "sheet-border")
            dwg.line(start=(165, 10), end=(165, (height - 65 - (11 * self.NUM_OPT_LINES))), linewidth = 0.35, color = color, group = "sheet-border")
            
            dwg.text(text = '1', position = (27.5, 12.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            dwg.text(text = '2', position = (45, 12.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            dwg.text(text = '3', position = (62.5, 12.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            dwg.text(text = '4', position = (100, 12.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            dwg.text(text = '5', position = (147.5, 12.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            dwg.text(text = '6', position = (182.5, 12.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            
            dwg.text(text = 'Pos.', position = (27.5, 17.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            dwg.text(text = 'Qty.', position = (45, 17.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            dwg.text(text = 'Unit', position = (62.5, 17.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            dwg.text(text = 'Titel', position = (100, 17.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            dwg.text(text = 'Document number', position = (147.5, 17.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            dwg.text(text = 'Comment', position = (182.5, 17.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            
            numLines = int((height - 85 - (11 * self.NUM_OPT_LINES)) / lineHeight)
            for h in range(numLines):
                hPos = (h + 1) * lineHeight + 20
                dwg.line(start=(20, hPos), end=(width - 10, hPos), linewidth = 0.35, color = color, group = "sheet-border")
                
                if not self.FULL_PARTS_LIST_SMALL_LINES:
                    dwg.text(text = 'Pos.' + str(h) + 'A', position = (27.5, hPos + 3 - lineHeight), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable")
                    dwg.text(text = 'Qty.' + str(h) + 'A', position = (45, hPos + 3 - lineHeight), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable")
                    dwg.text(text = 'Unit' + str(h) + 'A', position = (62.5, hPos + 3 - lineHeight), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable")
                    dwg.text(text = 'Titel' + str(h) + 'A', position = (100, hPos + 3 - lineHeight), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable")
                    dwg.text(text = 'Doc. number' + str(h) + 'A', position = (147.5, hPos + 3 - lineHeight), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable")
                    dwg.text(text = 'Comment' + str(h) + 'A', position = (182.5, hPos + 3 - lineHeight), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable")
                
                    dwg.text(text = 'Pos.' + str(h) + 'B', position = (27.5, hPos + 9.65 - lineHeight), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable")
                    dwg.text(text = 'Qty.' + str(h) + 'B', position = (45, hPos + 9.65 - lineHeight), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable")
                    dwg.text(text = 'Unit' + str(h) + 'B', position = (62.5, hPos + 9.65 - lineHeight), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable")
                    dwg.text(text = 'Titel' + str(h) + 'B', position = (100, hPos + 9.65 - lineHeight), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable")
                    dwg.text(text = 'Doc. number' + str(h) + 'B', position = (147.5, hPos + 9.65 - lineHeight), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable")
                    dwg.text(text = 'Comment' + str(h) + 'B', position = (182.5, hPos + 9.65 - lineHeight), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable")
                    
                    dwg.text(text = 'Pos.' + str(h) + 'C', position = (27.5, hPos + 16.3 - lineHeight), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable")
                    dwg.text(text = 'Qty.' + str(h) + 'C', position = (45, hPos + 16.3 - lineHeight), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable")
                    dwg.text(text = 'Unit' + str(h) + 'C', position = (62.5, hPos + 16.3 - lineHeight), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable")
                    dwg.text(text = 'Titel' + str(h) + 'C', position = (100, hPos + 16.3 - lineHeight), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable")
                    dwg.text(text = 'Doc. number' + str(h) + 'C', position = (147.5, hPos + 16.3 - lineHeight), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable")
                    dwg.text(text = 'Comment' + str(h) + 'C', position = (182.5, hPos + 16.3 - lineHeight), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable")
                else:
                    dwg.text(text = 'Pos.' + str(h) + 'A', position = (27.5, hPos + 5 - lineHeight), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable")
                    dwg.text(text = 'Qty.' + str(h) + 'A', position = (45, hPos + 5 - lineHeight), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable")
                    dwg.text(text = 'Unit' + str(h) + 'A', position = (62.5, hPos + 5 - lineHeight), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable")
                    dwg.text(text = 'Titel' + str(h) + 'A', position = (100, hPos + 5 - lineHeight), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable")
                    dwg.text(text = 'Doc. number' + str(h) + 'A', position = (147.5, hPos + 5 - lineHeight), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable")
                    dwg.text(text = 'Comment' + str(h) + 'A', position = (182.5, hPos + 5 - lineHeight), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable")
        
        
        # Small parts list over the titelblock
        if self.SMALL_PARTS_LIST:
            dwg.rect(start=(width - 190, height - 75 - (self.SMALL_PARTS_LIST_NUM_LINES * 11) - (self.NUM_OPT_LINES * 11)), end=(width - 10, height - 65 - (self.NUM_OPT_LINES * 11)), linewidth = 0.7, color = color, group = "titleblock-structure")
            # Horizontal
            dwg.line(start=(width - 190, height - 70 - self.NUM_OPT_LINES * 11 - (self.SMALL_PARTS_LIST_NUM_LINES * 11)), end=(width - 10, height - 70 - self.NUM_OPT_LINES * 11- (self.SMALL_PARTS_LIST_NUM_LINES * 11)), linewidth = 0.35, color = color, group = "titleblock-structure")
            
            hPos = height - 75 - self.NUM_OPT_LINES * 11 - (self.SMALL_PARTS_LIST_NUM_LINES * 11)
            dwg.text(text = '1', position = (width - 182.5, hPos + 2.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-not-editable")
            dwg.text(text = '2', position = (width - 165, hPos + 2.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-not-editable")
            dwg.text(text = '3', position = (width - 147.5, hPos + 2.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-not-editable")
            dwg.text(text = '4', position = (width - 110, hPos + 2.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-not-editable")
            dwg.text(text = '5', position = (width - 62.5, hPos + 2.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-not-editable")
            dwg.text(text = '6', position = (width - 27.5, hPos + 2.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-not-editable")
            
            hPos = height - 70 - self.NUM_OPT_LINES * 11 - (self.SMALL_PARTS_LIST_NUM_LINES * 11)
            dwg.text(text = 'Pos.', position = (width - 182.5, hPos + 2.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-not-editable")
            dwg.text(text = 'Qty.', position = (width - 165, hPos + 2.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-not-editable")
            dwg.text(text = 'Unit', position = (width - 147.5, hPos + 2.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-not-editable")
            dwg.text(text = 'Titel', position = (width - 110, hPos + 2.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-not-editable")
            dwg.text(text = 'Doc. number', position = (width - 62.5, hPos + 2.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-not-editable")
            dwg.text(text = 'Comment', position = (width - 27.5, hPos + 2.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-not-editable")
            
            for h in range(self.SMALL_PARTS_LIST_NUM_LINES):
                hPos = height - 75 - self.NUM_OPT_LINES * 11 - ((h) * 11)
                if h == self.SMALL_PARTS_LIST_NUM_LINES - 1:
                    dwg.line(start=(width - 190, hPos), end=(width - 10, hPos), linewidth = 0.7, color = color, group = "titleblock-structure")
                else:
                    dwg.line(start=(width - 190, hPos), end=(width - 10, hPos), linewidth = 0.35, color = color, group = "titleblock-structure")
                    
                dwg.text(text = 'Pos.' + str(h) + 'A', position = (width - 182.5, hPos + 5.5), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable")
                dwg.text(text = 'Qty.' + str(h) + 'A', position = (width - 165, hPos + 5.5), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable")
                dwg.text(text = 'Unit' + str(h) + 'A', position = (width - 147.5, hPos + 5.5), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable")
                dwg.text(text = 'Titel' + str(h) + 'A', position = (width - 110, hPos + 5.5), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable")
                dwg.text(text = 'Doc. number' + str(h) + 'A', position = (width - 62.5, hPos + 5.5), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable")
                dwg.text(text = 'Comment' + str(h) + 'A', position = (width - 27.5, hPos + 5.5), tsize = 3.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable")
            
            # Vertical
            dwg.line(start=(width - 175, height - 75 - self.NUM_OPT_LINES * 11 - (self.SMALL_PARTS_LIST_NUM_LINES * 11)), end=(width - 175, height - 65 - self.NUM_OPT_LINES * 11), linewidth = 0.35, color = color, group = "titleblock-structure")
            dwg.line(start=(width - 155, height - 75 - self.NUM_OPT_LINES * 11 - (self.SMALL_PARTS_LIST_NUM_LINES * 11)), end=(width - 155, height - 65 - self.NUM_OPT_LINES * 11), linewidth = 0.35, color = color, group = "titleblock-structure")
            dwg.line(start=(width - 140, height - 75 - self.NUM_OPT_LINES * 11 - (self.SMALL_PARTS_LIST_NUM_LINES * 11)), end=(width - 140, height - 65 - self.NUM_OPT_LINES * 11), linewidth = 0.35, color = color, group = "titleblock-structure")
            dwg.line(start=(width - 80, height - 75 - self.NUM_OPT_LINES * 11 - (self.SMALL_PARTS_LIST_NUM_LINES * 11)), end=(width - 80, height - 65 - self.NUM_OPT_LINES * 11), linewidth = 0.35, color = color, group = "titleblock-structure")
            dwg.line(start=(width - 45, height - 75 - self.NUM_OPT_LINES * 11 - (self.SMALL_PARTS_LIST_NUM_LINES * 11)), end=(width - 45, height - 65 - self.NUM_OPT_LINES * 11), linewidth = 0.35, color = color, group = "titleblock-structure")     
                