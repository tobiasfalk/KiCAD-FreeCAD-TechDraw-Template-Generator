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
    COLOR = '#000000'
    NUM_OPT_LINES = 0
    REV_HISTORY = False
    NUMREVISIONS = 0
    FOLD_LINES = False
    FULL_PARTS_LIST = False
    FULL_PARTS_LIST_SMALL_LINES = False
    FULL_PARTS_LIST_NUM_SHEETS = 1
    SMALL_PARTS_LIST = False
    SMALL_PARTS_LIST_NUM_LINES = 1

    SHEET_SIZES_ISO_216_A =[(1682, 1189),
                            (1189, 841),
                            (841,  594),
                            (594,  420),
                            (420,  297),
                            (297,  210),
                            (210,  297)]

    FIELD_LETTERS = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X']

    DWG = None

    def __init__(self, size = (100, 100), sizeString = 'User defined', color = '#000000', numOptLines = 0, revHistory = False, numRevisions = 0, foldLines = False, fullPartsList = False, fullPartsListSmallLines = False, fullPartsListNumSheets = 1, smallPartsList = False, smallPartsListNumLines = 1):
        self.SIZE = size
        self.SIZE_STRING = sizeString
        self.COLOR = color
        self.NUM_OPT_LINES = numOptLines
        self.REV_HISTORY = revHistory
        self.NUMREVISIONS = numRevisions
        self.FOLD_LINES = foldLines
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
        if self.FOLD_LINES and not self.SIZE in self.SHEET_SIZES_ISO_216_A:
            self.FOLD_LINES = False
            print('Sheet szise not in DIN 824-A present, option was disabled')

    def __del__(self):
        pass

    def drawISO5457_ISO700_A(self):
        sizeStringFile = self.SIZE_STRING.replace(' ', '_')
        filename = sizeStringFile + '_ISO5457_ISO7200_A'
        if self.NUM_OPT_LINES > 0:
            filename += '+' + str(self.NUM_OPT_LINES)
        if self.REV_HISTORY:
            filename +='_rh+' + str(self.NUMREVISIONS)
        if self.FOLD_LINES:
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
        
        # the PDF lib has no polygons so i made a custom way to draw the cuting marks
        dwg.drawCorners()

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
        dwg.text(text = 'Sheet', position = (width - 35 + 0.9, height - 21 + 1.8 + 0.9), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-non-editable")
        dwg.text(text = '%S/%N', position = (width - 35 + 0.9, height - 21 + 1.8 + 0.9 + 4.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 23)
        dwg.text(text = 'Lang.', position = (width - 50 + 0.9, height - 21 + 1.8 + 0.9), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-non-editable")
        dwg.text(text = 'EN', position = (width - 50 + 0.9, height - 21 + 1.8 + 0.9 + 4.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 13)
        dwg.text(text = 'Rev.', position = (width - 50 + 0.9, height - 32 + 1.8 + 0.9), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-non-editable")
        dwg.text(text = '%R', position = (width - 50 + 0.9, height - 32 + 1.8 + 0.9 + 4.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 13)
        dwg.text(text = 'Date of issue', position = (width - 35 + 0.9, height - 32 + 1.8 + 0.9), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-non-editable")
        dwg.text(text = '%D', position = (width - 35 + 0.9, height - 32 + 1.8 + 0.9 + 4.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 23)

        dwg.text(text = 'Document number', position = (width - 50 + 0.9, height - 43 + 1.8 + 0.9), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-non-editable")
        dwg.text(text = '%C6', position = (width - 50 + 0.9, height - 43 + 1.8 + 0.9 + 4.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 38)
        dwg.text(text = 'Titel, Supplementary titel', position = (width - 110 + 0.9, height - 43 + 1.8 + 0.9), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-non-editable")
        dwg.text(text = '%T', position = (width - 110 + 0.9, height - 43 + 1.8 + 0.9 + 4.5), tsize = 5, linewidth = 0.35, color = color, heightAnchor = 'top', widthAnchor = 'start', group = "titleblock-text-editable", width = 58)
        dwg.text(text = '', position = (width - 110 + 0.9, height - 43 + 1.8 + 0.9 + 4.5 + 7.5), tsize = 5, linewidth = 0.35, color = color, heightAnchor = 'top', widthAnchor = 'start', group = "titleblock-text-editable", width = 58)
        dwg.text(text = '', position = (width - 110 + 0.9, height - 43 + 1.8 + 0.9 + 4.5 + 7.5 + 7.5), tsize = 5, linewidth = 0.35, color = color, heightAnchor = 'top', widthAnchor = 'start', group = "titleblock-text-editable", width = 58)
        dwg.text(text = 'Legal owner', position = (width - 190 + 0.9, height - 43 + 1.8 + 0.9), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-non-editable")
        dwg.text(text = '%Y', position = (width - 190 + 0.9, height - 43 + 1.8 + 0.9 + 4.5), tsize = 5, linewidth = 0.35, color = color, heightAnchor = 'top', widthAnchor = 'start', group = "titleblock-text-editable", width = 78)
        dwg.text(text = '', position = (width - 190 + 0.9, height - 43 + 1.8 + 0.9 + 4.5 + 7.5), tsize = 5, linewidth = 0.35, color = color, heightAnchor = 'top', widthAnchor = 'start', group = "titleblock-text-editable", width = 78)
        dwg.text(text = '', position = (width - 190 + 0.9, height - 43 + 1.8 + 0.9 + 4.5 + 7.5 + 7.5), tsize = 5, linewidth = 0.35, color = color, heightAnchor = 'top', widthAnchor = 'start', group = "titleblock-text-editable", width = 78)
        dwg.text(text = 'Approved by', position = (width - 190 + 0.9, height - 54 + 1.8 + 0.9), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-non-editable")
        dwg.text(text = '%C1', position = (width - 190 + 0.9, height - 54 + 1.8 + 0.9 + 4.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 78)
        dwg.text(text = 'Projekt', position = (width - 110 + 0.9, height - 54 + 1.8 + 0.9), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-non-editable")
        dwg.text(text = '%C3', position = (width - 110 + 0.9, height - 54 + 1.8 + 0.9 + 4.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 58)
        dwg.text(text = 'Document type', position = (width - 50 + 0.9, height - 54 + 1.8 + 0.9), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-non-editable")
        dwg.text(text = '%C5', position = (width - 50 + 0.9, height - 54 + 1.8 + 0.9 + 4.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 38)
        dwg.text(text = 'Created by', position = (width - 190 + 0.9, height - 65 + 1.8 + 0.9), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-non-editable")
        dwg.text(text = '%C0', position = (width - 190 + 0.9, height - 65 + 1.8 + 0.9 + 4.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 78)
        dwg.text(text = 'Valid from to', position = (width - 110 + 0.9, height - 65 + 1.8 + 0.9), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-non-editable")
        dwg.text(text = '%C2', position = (width - 110 + 0.9, height - 65 + 1.8 + 0.9 + 4.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 58)
        dwg.text(text = 'Document state', position = (width - 50 + 0.9, height - 65 + 1.8 + 0.9), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-non-editable")
        dwg.text(text = '%C4', position = (width - 50 + 0.9, height - 65 + 1.8 + 0.9 + 4.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 38)


        # Optional titelblock
        for i in range(self.NUM_OPT_LINES):
            dwg.line(start=(width - 10, height - 65 - (11 * i)), end=(width - 190, height - 65 - (11 * i)), linewidth = 0.35, color = color, group = "titleblock-structure")
            if i == 0:
                dwg.text(text = 'A', position = (width - 190 + 0.9, height - 65 - (11 * (i + 1)) + 1.8 + 0.9), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 78)
                dwg.text(text = 'B', position = (width - 190 + 0.9, height - 65 - (11 * (i + 1)) + 1.8 + 0.9 + 4.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 78)
                dwg.text(text = 'Raw dimensions', position = (width - 110 + 0.9, height - 65 - (11 * (i + 1)) + 1.8 + 0.9), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 58)
                dwg.text(text = 'C', position = (width - 110 + 0.9, height - 65 - (11 * (i + 1)) + 1.8 + 0.9 + 4.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 58)
                dwg.text(text = 'Scale', position = (width - 50 + 0.9, height - 65 - (11 * (i + 1)) + 1.8 + 0.9), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 38)
                dwg.text(text = '1:1', position = (width - 50 + 0.9, height - 65 - (11 * (i + 1)) + 1.8 + 0.9 + 4.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 38)
            elif i == 1:
                dwg.text(text = 'Surface treatment', position = (width - 190 + 0.9, height - 65 - (11 * (i + 1)) + 1.8 + 0.9), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 78)
                dwg.text(text = 'Surface treatment', position = (width - 190 + 0.9, height - 65 - (11 * (i + 1)) + 1.8 + 0.9 + 4.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 78)
                dwg.text(text = 'Weight', position = (width - 110 + 0.9, height - 65 - (11 * (i + 1)) + 1.8 + 0.9), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 58)
                dwg.text(text = 'Weight', position = (width - 110 + 0.9, height - 65 - (11 * (i + 1)) + 1.8 + 0.9 + 4.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 58)
                dwg.text(text = 'Standard', position = (width - 50 + 0.9, height - 65 - (11 * (i + 1)) + 1.8 + 0.9), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 38)
                dwg.text(text = 'Standard', position = (width - 50 + 0.9, height - 65 - (11 * (i + 1)) + 1.8 + 0.9 + 4.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 38)
            elif i == 2:
                dwg.text(text = 'Option X', position = (width - 190 + 0.9, height - 65 - (11 * (i + 1)) + 1.8 + 0.9), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 78)
                dwg.text(text = 'Option X', position = (width - 190 + 0.9, height - 65 - (11 * (i + 1)) + 1.8 + 0.9 + 4.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 78)
                dwg.text(text = 'Option Y', position = (width - 110 + 0.9, height - 65 - (11 * (i + 1)) + 1.8 + 0.9), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 58)
                dwg.text(text = 'Option Y', position = (width - 110 + 0.9, height - 65 - (11 * (i + 1)) + 1.8 + 0.9 + 4.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 58)
                dwg.text(text = 'Option Z', position = (width - 50 + 0.9, height - 65 - (11 * (i + 1)) + 1.8 + 0.9), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 38)
                dwg.text(text = 'Option Z', position = (width - 50 + 0.9, height - 65 - (11 * (i + 1)) + 1.8 + 0.9 + 4.75), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'start', widthAnchor = 'start', group = "titleblock-text-editable", width = 38)

        # Revision History
        if self.REV_HISTORY:
            dwg.rect(start=(width-190, 10), end=(width-10, 20 + (self.NUMREVISIONS * 15)), linewidth = 0.7, color = color, group = "sheet-border")
            dwg.line(start=(width-190, 15), end=(width-10, 15), linewidth = 0.35, color = color, group = "sheet-border")
            dwg.line(start=(width-190, 20), end=(width-10, 20), linewidth = 0.7, color = color, group = "sheet-border")
            dwg.line(start=(width-175, 15), end=(width-175, 20 + (self.NUMREVISIONS * 15)), linewidth = 0.35, color = color, group = "sheet-border")
            dwg.line(start=(width-155, 15), end=(width-155, 20 + (self.NUMREVISIONS * 15)), linewidth = 0.35, color = color, group = "sheet-border")
            dwg.line(start=(width-60, 15), end=(width-60, 20 + (self.NUMREVISIONS * 15)), linewidth = 0.35, color = color, group = "sheet-border")
            dwg.line(start=(width-40, 15), end=(width-40, 20 + (self.NUMREVISIONS * 15)), linewidth = 0.35, color = color, group = "sheet-border")

            dwg.text(text = 'Revision History', position = (width - 100, 12.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            dwg.text(text = 'Zone', position = (width - 182.5, 17.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            dwg.text(text = 'Rev.', position = (width - 165, 17.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            dwg.text(text = 'Description', position = (width - 107.5, 17.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            dwg.text(text = 'Date', position = (width - 50, 17.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            dwg.text(text = 'Created by', position = (width - 25, 17.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")

            for i in range(self.NUMREVISIONS):
                dwg.line(start=(width-190, 20 + (i * 15)), end=(width-10, 20 + (i * 15)), linewidth = 0.35, color = color, group = "sheet-border")
                dwg.text(text = 'ZoneA', position = (width - 182.5, 17.75 + ((i + 1) * 15)), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 13)
                dwg.text(text = 'Rev.A', position = (width - 165, 17.75 + ((i + 1) * 15)), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 18)
                dwg.text(text = 'DescriptionA', position = (width - 107.5, 17.75 + ((i + 1) * 15)), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 93)
                dwg.text(text = 'DateA', position = (width - 50, 17.75 + ((i + 1) * 15)), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 18)
                dwg.text(text = 'Created byA', position = (width - 25, 17.75 + ((i + 1) * 15)), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 28)
                dwg.text(text = 'ZoneB', position = (width - 182.5, 13 + ((i + 1) * 15)), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 13)
                dwg.text(text = 'Rev.B', position = (width - 165, 13 + ((i + 1) * 15)), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 18)
                dwg.text(text = 'DescriptionB', position = (width - 107.5, 13 + ((i + 1) * 15)), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 93)
                dwg.text(text = 'DateB', position = (width - 50, 13 + ((i + 1) * 15)), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 18)
                dwg.text(text = 'Created byB', position = (width - 25, 13 + ((i + 1) * 15)), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 28)
                dwg.text(text = 'ZoneC', position = (width - 182.5, 8.25 + ((i + 1) * 15)), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 13)
                dwg.text(text = 'Rev.C', position = (width - 165, 8.25 + ((i + 1) * 15)), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 18)
                dwg.text(text = 'DescriptionC', position = (width - 107.5, 8.25 + ((i + 1) * 15)), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 93)
                dwg.text(text = 'DateC', position = (width - 50, 8.25 + ((i + 1) * 15)), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 18)
                dwg.text(text = 'Created byC', position = (width - 25, 8.25 + ((i + 1) * 15)), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 28)



        # Folding Lines, only for ISO 216 A sizes execpt for 4A0
        if self.FOLD_LINES:
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
            
            dwg.text(text = '1', position = (27.5, 12.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            dwg.text(text = '2', position = (45, 12.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            dwg.text(text = '3', position = (62.5, 12.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            dwg.text(text = '4', position = (100, 12.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            dwg.text(text = '5', position = (147.5, 12.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            dwg.text(text = '6', position = (182.5, 12.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            
            dwg.text(text = 'Pos.', position = (27.5, 17.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            dwg.text(text = 'Qty.', position = (45, 17.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            dwg.text(text = 'Unit', position = (62.5, 17.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            dwg.text(text = 'Titel', position = (100, 17.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            dwg.text(text = 'Document number', position = (147.5, 17.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            dwg.text(text = 'Comment', position = (182.5, 17.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-non-editable")
            
            numLines = int((height - 85 - (11 * self.NUM_OPT_LINES)) / lineHeight)
            for h in range(numLines):
                hPos = (h + 1) * lineHeight + 20
                dwg.line(start=(20, hPos), end=(width - 10, hPos), linewidth = 0.35, color = color, group = "sheet-border")
                
                if not self.FULL_PARTS_LIST_SMALL_LINES:
                    dwg.text(text = 'Pos.' + str(h) + 'A', position = (27.5, hPos + 1.8 + 0.9 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 13)
                    dwg.text(text = 'Qty.' + str(h) + 'A', position = (45, hPos + 1.8 + 0.9 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 18)
                    dwg.text(text = 'Unit' + str(h) + 'A', position = (62.5, hPos + 1.8 + 0.9 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 13)
                    dwg.text(text = 'Titel' + str(h) + 'A', position = (100, hPos + 1.8 + 0.9 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 58)
                    dwg.text(text = 'Doc. number' + str(h) + 'A', position = (147.5, hPos + 1.8 + 0.9 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 33)
                    dwg.text(text = 'Comment' + str(h) + 'A', position = (182.5, hPos + 1.8 + 0.9 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 33)
                
                    dwg.text(text = 'Pos.' + str(h) + 'B', position = (27.5, hPos + 9.65 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 13)
                    dwg.text(text = 'Qty.' + str(h) + 'B', position = (45, hPos + 9.65 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 18)
                    dwg.text(text = 'Unit' + str(h) + 'B', position = (62.5, hPos + 9.65 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 13)
                    dwg.text(text = 'Titel' + str(h) + 'B', position = (100, hPos + 9.65 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 58)
                    dwg.text(text = 'Doc. number' + str(h) + 'B', position = (147.5, hPos + 9.65 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 33)
                    dwg.text(text = 'Comment' + str(h) + 'B', position = (182.5, hPos + 9.65 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 33)
                    
                    dwg.text(text = 'Pos.' + str(h) + 'C', position = (27.5, hPos + 16.3 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 13)
                    dwg.text(text = 'Qty.' + str(h) + 'C', position = (45, hPos + 16.3 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 18)
                    dwg.text(text = 'Unit' + str(h) + 'C', position = (62.5, hPos + 16.3 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 13)
                    dwg.text(text = 'Titel' + str(h) + 'C', position = (100, hPos + 16.3 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 58)
                    dwg.text(text = 'Doc. number' + str(h) + 'C', position = (147.5, hPos + 16.3 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 33)
                    dwg.text(text = 'Comment' + str(h) + 'C', position = (182.5, hPos + 16.3 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 33)
                else:
                    dwg.text(text = 'Pos.' + str(h) + 'A', position = (27.5, hPos + 5 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 13)
                    dwg.text(text = 'Qty.' + str(h) + 'A', position = (45, hPos + 5 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 18)
                    dwg.text(text = 'Unit' + str(h) + 'A', position = (62.5, hPos + 5 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 13)
                    dwg.text(text = 'Titel' + str(h) + 'A', position = (100, hPos + 5 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 58)
                    dwg.text(text = 'Doc. number' + str(h) + 'A', position = (147.5, hPos + 5 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 33)
                    dwg.text(text = 'Comment' + str(h) + 'A', position = (182.5, hPos + 5 - lineHeight), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 33)
        
        
        # Small parts list over the Titelblock
        if self.SMALL_PARTS_LIST:
            dwg.rect(start=(width - 190, height - 75 - (self.SMALL_PARTS_LIST_NUM_LINES * 11) - (self.NUM_OPT_LINES * 11)), end=(width - 10, height - 65 - (self.NUM_OPT_LINES * 11)), linewidth = 0.7, color = color, group = "titleblock-structure")
            # Horizontal
            dwg.line(start=(width - 190, height - 70 - self.NUM_OPT_LINES * 11 - (self.SMALL_PARTS_LIST_NUM_LINES * 11)), end=(width - 10, height - 70 - self.NUM_OPT_LINES * 11 - (self.SMALL_PARTS_LIST_NUM_LINES * 11)), linewidth = 0.35, color = color, group = "titleblock-structure")
            
            hPos = height - 75 - self.NUM_OPT_LINES * 11 - (self.SMALL_PARTS_LIST_NUM_LINES * 11)
            dwg.text(text = '1', position = (width - 182.5, hPos + 2.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-not-editable")
            dwg.text(text = '2', position = (width - 165, hPos + 2.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-not-editable")
            dwg.text(text = '3', position = (width - 147.5, hPos + 2.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-not-editable")
            dwg.text(text = '4', position = (width - 110, hPos + 2.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-not-editable")
            dwg.text(text = '5', position = (width - 62.5, hPos + 2.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-not-editable")
            dwg.text(text = '6', position = (width - 27.5, hPos + 2.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-not-editable")
            
            hPos = height - 70 - self.NUM_OPT_LINES * 11 - (self.SMALL_PARTS_LIST_NUM_LINES * 11)
            dwg.text(text = 'Pos.', position = (width - 182.5, hPos + 2.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-not-editable")
            dwg.text(text = 'Qty.', position = (width - 165, hPos + 2.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-not-editable")
            dwg.text(text = 'Unit', position = (width - 147.5, hPos + 2.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-not-editable")
            dwg.text(text = 'Titel', position = (width - 110, hPos + 2.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-not-editable")
            dwg.text(text = 'Doc. number', position = (width - 62.5, hPos + 2.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-not-editable")
            dwg.text(text = 'Comment', position = (width - 27.5, hPos + 2.75), tsize = 1.8, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-not-editable")
            
            for h in range(self.SMALL_PARTS_LIST_NUM_LINES):
                hPos = height - 75 - self.NUM_OPT_LINES * 11 - ((h) * 11)
                if h == self.SMALL_PARTS_LIST_NUM_LINES - 1:
                    dwg.line(start=(width - 190, hPos), end=(width - 10, hPos), linewidth = 0.7, color = color, group = "titleblock-structure")
                else:
                    dwg.line(start=(width - 190, hPos), end=(width - 10, hPos), linewidth = 0.35, color = color, group = "titleblock-structure")
                    
                dwg.text(text = 'Pos.' + str(h) + 'A', position = (width - 182.5, hPos + 5.5), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 13)
                dwg.text(text = 'Qty.' + str(h) + 'A', position = (width - 165, hPos + 5.5), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 18)
                dwg.text(text = 'Unit' + str(h) + 'A', position = (width - 147.5, hPos + 5.5), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 13)
                dwg.text(text = 'Titel' + str(h) + 'A', position = (width - 110, hPos + 5.5), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 58)
                dwg.text(text = 'Doc. number' + str(h) + 'A', position = (width - 62.5, hPos + 5.5), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 33)
                dwg.text(text = 'Comment' + str(h) + 'A', position = (width - 27.5, hPos + 5.5), tsize = 2.5, linewidth = 0.35, color = color, heightAnchor = 'middle', widthAnchor = 'middle', group = "titleblock-text-editable", width = 33)
            
            # Vertical
            dwg.line(start=(width - 175, height - 75 - self.NUM_OPT_LINES * 11 - (self.SMALL_PARTS_LIST_NUM_LINES * 11)), end=(width - 175, height - 65 - self.NUM_OPT_LINES * 11), linewidth = 0.35, color = color, group = "titleblock-structure")
            dwg.line(start=(width - 155, height - 75 - self.NUM_OPT_LINES * 11 - (self.SMALL_PARTS_LIST_NUM_LINES * 11)), end=(width - 155, height - 65 - self.NUM_OPT_LINES * 11), linewidth = 0.35, color = color, group = "titleblock-structure")
            dwg.line(start=(width - 140, height - 75 - self.NUM_OPT_LINES * 11 - (self.SMALL_PARTS_LIST_NUM_LINES * 11)), end=(width - 140, height - 65 - self.NUM_OPT_LINES * 11), linewidth = 0.35, color = color, group = "titleblock-structure")
            dwg.line(start=(width - 80, height - 75 - self.NUM_OPT_LINES * 11 - (self.SMALL_PARTS_LIST_NUM_LINES * 11)), end=(width - 80, height - 65 - self.NUM_OPT_LINES * 11), linewidth = 0.35, color = color, group = "titleblock-structure")
            dwg.line(start=(width - 45, height - 75 - self.NUM_OPT_LINES * 11 - (self.SMALL_PARTS_LIST_NUM_LINES * 11)), end=(width - 45, height - 65 - self.NUM_OPT_LINES * 11), linewidth = 0.35, color = color, group = "titleblock-structure")

    def drawISO5457_ISO700_B(self):
        sizeStringFile = self.SIZE_STRING.replace(' ', '_')
        filename = sizeStringFile + '_ISO5457_ISO7200_B'
        if self.NUM_OPT_LINES > 0:
            filename += '+' + str(self.NUM_OPT_LINES)
        if self.REV_HISTORY:
            filename +='_rh+' + str(self.NUMREVISIONS)
        if self.FOLD_LINES:
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
        if self.FOLD_LINES:
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
                