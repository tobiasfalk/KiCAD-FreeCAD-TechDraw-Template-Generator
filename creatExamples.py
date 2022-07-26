#!/usr/bin/python

import multiprocessing

from StandardDraw import StandardDraw

SHEET_SIZES =  [#["ISO 216 4A0",            (2378, 1682)],
                #["ISO 216 2A0",            (1682, 1189)],
                #["ISO 216 A0",             (1189, 841)],
                ["ISO 216 A1",             (841,  594)],
                ["ISO 216 A2",             (594,  420)],
                ["ISO 216 A3",             (420,  297)],
                ["ISO 216 A4L",            (297,  210)],
                ["ISO 216 A4P",            (210,  297)],
                #["ISO 216 B0",             (1414, 1000)],
                #["ISO 216 B1",             (1000, 707)],
                #["ISO 216 B2",             (707,  500)],
                #["ISO 216 B3",             (500,  353)],
                #["ISO 216 B4",             (353,  250)],
                #["ISO 216 B3",             (250,  176)],
                ["ANSI Y14.1 AL (Letter)", (279,  216)],
                ["ANSI Y14.1 AP (Letter)", (216,  279)],
                ["ANSI Y14.1 B",           (432,  279)],
                ["ANSI Y14.1 C",           (559,  432)],
                #["ANSI Y14.1 D",           (864,  559)],
                #["ANSI Y14.1 E",           (1118, 864)],
                #["ANSI Y14.1 F",           (1016, 711)],
                #["Legal",                  (356,  216)],
                #["Tabloid (Ledger)",       (432,  279)],
                ["Arch AL",                (305,  229)],
                ["Arch AP",                (229,  305)],
                ["Arch B",                 (457,  305)],
                ["Arch C",                 (610,  457)],
                #["Arch D",                 (914,  610)],
                #["Arch E",                 (1219, 914)],
                #["Arch E1",                (1067, 726)],
                #["Arch E2",                (965,  660)],
                #["Arch E3",                (991,  686)],
                ]

def createSheet(size, sizeString, color, numOptLines, revHistory, numRevisions, foldLinesDIN824_A, fullPartsList, fullPartsListSmallLines, fullPartsListNumSheets, smallPartsList, smallPartsListNumLines):
    print("Generate:")
    print("Size: " + str(size))
    print("Size String: " + sizeString)
    print("Color: " + color)
    print("Num. Opt. Lines: " + str(numOptLines))
    print("Rev. History: " + str(revHistory))
    print("Num Rev.: " + str(numRevisions))
    print("Folding Lines: " + str(foldLinesDIN824_A))
    print("Full Parts List: " + str(fullPartsList))
    print("Full Parts List Small Felds: " + str(fullPartsListSmallLines))
    print("Full Parts List Num. Sheets: " + str(fullPartsListNumSheets))
    print("Small Parts List: " + str(smallPartsList))
    print()
    print('-----------------------------------------------------------------------')
    print()

    stdDraw = StandardDraw(size = size, sizeString = sizeString, color = color, numOptLines = numOptLines, revHistory = revHistory, numRevisions = numRevisions, foldLinesDIN824_A = foldLinesDIN824_A, fullPartsList = fullPartsList, fullPartsListSmallLines = fullPartsListSmallLines, fullPartsListNumSheets = fullPartsListNumSheets, smallPartsList = smallPartsList, smallPartsListNumLines = smallPartsListNumLines)

    stdDraw.drawISO5457_ISO700_A()
    
def revHist(size, sizeString, numOptLines, foldLinesDIN824_A, fullPartsList, fullPartsListSmallLines, fullPartsListNumSheets, smallPartsList, smallPartsListNumLines):
    try:
        #False
        p1 = multiprocessing.Process(target=createSheet, args=(size, sizeString,'#000000', numOptLines, False, 0, foldLinesDIN824_A, fullPartsList, fullPartsListSmallLines, fullPartsListNumSheets, smallPartsList, smallPartsListNumLines))
        p2 = multiprocessing.Process(target=createSheet, args=(size, sizeString, '#000000', numOptLines, False, 0, foldLinesDIN824_A, fullPartsList, fullPartsListSmallLines, fullPartsListNumSheets, smallPartsList, smallPartsListNumLines))
        p3 = multiprocessing.Process(target=createSheet, args=(size, sizeString, '#000000', numOptLines, False, 0, foldLinesDIN824_A, fullPartsList, fullPartsListSmallLines, fullPartsListNumSheets, smallPartsList, smallPartsListNumLines))
        p4 = multiprocessing.Process(target=createSheet, args=(size, sizeString, '#000000', numOptLines, False, 0, foldLinesDIN824_A, fullPartsList, fullPartsListSmallLines, fullPartsListNumSheets, smallPartsList, smallPartsListNumLines))
        p1.start()
        p2.start()
        p3.start()
        p4.start()
        #True
        if not fullPartsList:
            p5 = multiprocessing.Process(target=createSheet, args=(size, sizeString, '#000000', numOptLines, True, 1, foldLinesDIN824_A, fullPartsList, fullPartsListSmallLines, fullPartsListNumSheets, smallPartsList, smallPartsListNumLines))
            p6 = multiprocessing.Process(target=createSheet, args=(size, sizeString, '#000000', numOptLines, True, 1, foldLinesDIN824_A, fullPartsList, fullPartsListSmallLines, fullPartsListNumSheets, smallPartsList, smallPartsListNumLines))
            p7 = multiprocessing.Process(target=createSheet, args=(size, sizeString, '#000000', numOptLines, True, 1, foldLinesDIN824_A, fullPartsList, fullPartsListSmallLines, fullPartsListNumSheets, smallPartsList, smallPartsListNumLines))
            p8 = multiprocessing.Process(target=createSheet, args=(size, sizeString, '#000000', numOptLines, True, 1, foldLinesDIN824_A, fullPartsList, fullPartsListSmallLines, fullPartsListNumSheets, smallPartsList, smallPartsListNumLines))
            p5.start()
            p6.start()
            p7.start()
            p8.start()
            
            p9 = multiprocessing.Process(target=createSheet, args=(size, sizeString, '#000000', numOptLines, True, 2, foldLinesDIN824_A, fullPartsList, fullPartsListSmallLines, fullPartsListNumSheets, smallPartsList, smallPartsListNumLines))
            p10 = multiprocessing.Process(target=createSheet, args=(size, sizeString, '#000000', numOptLines, True, 2, foldLinesDIN824_A, fullPartsList, fullPartsListSmallLines, fullPartsListNumSheets, smallPartsList, smallPartsListNumLines))
            p11 = multiprocessing.Process(target=createSheet, args=(size, sizeString, '#000000', numOptLines, True, 2, foldLinesDIN824_A, fullPartsList, fullPartsListSmallLines, fullPartsListNumSheets, smallPartsList, smallPartsListNumLines))
            p12 = multiprocessing.Process(target=createSheet, args=(size, sizeString, '#000000', numOptLines, True, 2, foldLinesDIN824_A, fullPartsList, fullPartsListSmallLines, fullPartsListNumSheets, smallPartsList, smallPartsListNumLines))
            p9.start()
            p10.start()
            p11.start()
            p12.start()
            
            p13 = multiprocessing.Process(target=createSheet, args=(size, sizeString, '#000000', numOptLines, True, 3, foldLinesDIN824_A, fullPartsList, fullPartsListSmallLines, fullPartsListNumSheets, smallPartsList, smallPartsListNumLines))
            p14 = multiprocessing.Process(target=createSheet, args=(size, sizeString, '#000000', numOptLines, True, 3, foldLinesDIN824_A, fullPartsList, fullPartsListSmallLines, fullPartsListNumSheets, smallPartsList, smallPartsListNumLines))
            p15 = multiprocessing.Process(target=createSheet, args=(size, sizeString, '#000000', numOptLines, True, 3, foldLinesDIN824_A, fullPartsList, fullPartsListSmallLines, fullPartsListNumSheets, smallPartsList, smallPartsListNumLines))
            p16 = multiprocessing.Process(target=createSheet, args=(size, sizeString, '#000000', numOptLines, True, 3, foldLinesDIN824_A, fullPartsList, fullPartsListSmallLines, fullPartsListNumSheets, smallPartsList, smallPartsListNumLines))
            p13.start()
            p14.start()
            p15.start()
            p16.start()

        p1.join()
        p2.join()
        p3.join()
        p4.join()
        
        p5.join()
        p6.join()
        p7.join()
        p8.join()
        
        p9.join()
        p10.join()
        p11.join()
        p12.join()
        
        p13.join()
        p14.join()
        p15.join()
        p16.join()
    
    except:
        print( "Error: unable to start thread")

def optLines(size, sizeString, foldLinesDIN824_A, fullPartsList, fullPartsListSmallLines, fullPartsListNumSheets, smallPartsList, smallPartsListNumLines):
    revHist(size, sizeString, 0, foldLinesDIN824_A, fullPartsList, fullPartsListSmallLines, fullPartsListNumSheets, smallPartsList, smallPartsListNumLines)
    revHist(size, sizeString, 1, foldLinesDIN824_A, fullPartsList, fullPartsListSmallLines, fullPartsListNumSheets, smallPartsList, smallPartsListNumLines)
    revHist(size, sizeString, 2, foldLinesDIN824_A, fullPartsList, fullPartsListSmallLines, fullPartsListNumSheets, smallPartsList, smallPartsListNumLines)
    revHist(size, sizeString, 3, foldLinesDIN824_A, fullPartsList, fullPartsListSmallLines, fullPartsListNumSheets, smallPartsList, smallPartsListNumLines)
    
def foldLines(size, sizeString, fullPartsList, fullPartsListSmallLines, fullPartsListNumSheets, smallPartsList, smallPartsListNumLines):
    optLines(size, sizeString, False, fullPartsList, fullPartsListSmallLines, fullPartsListNumSheets, smallPartsList, smallPartsListNumLines)
    optLines(size, sizeString, True, fullPartsList, fullPartsListSmallLines, fullPartsListNumSheets, smallPartsList, smallPartsListNumLines)

def fullPartsList(size, sizeString, smallPartsList, smallPartsListNumLines):
    foldLines(size, sizeString, False, False, 1, smallPartsList, smallPartsListNumLines)
    
    if size == (210,  297) and not smallPartsList:
        foldLines(size, sizeString, True, False, 1, smallPartsList, smallPartsListNumLines)
        foldLines(size, sizeString, True, True, 1, smallPartsList, smallPartsListNumLines)
        
        foldLines(size, sizeString, True, False, 2, smallPartsList, smallPartsListNumLines)
        foldLines(size, sizeString, True, True, 2, smallPartsList, smallPartsListNumLines)
        
        foldLines(size, sizeString, True, False, 3, smallPartsList, smallPartsListNumLines)
        foldLines(size, sizeString, True, True, 3, smallPartsList, smallPartsListNumLines)
    
def smallPartsList(size, sizeString):
    # False
    fullPartsList(size, sizeString, False, 0)
    
    # True
    fullPartsList(size, sizeString, True, 1)
    fullPartsList(size, sizeString, True, 2)
    fullPartsList(size, sizeString, True, 3)
    
def createExamples():
    for s in SHEET_SIZES:
        smallPartsList(s[1], s[0])
        pass
    pass

if __name__ == "__main__":
    createExamples()