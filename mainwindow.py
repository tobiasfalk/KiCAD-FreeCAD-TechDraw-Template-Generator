#!/usr/bin/python

import thread

# This Python file uses the following encoding: utf-8
import os
from pathlib import Path
#from socket import SOL_NETROM
import sys

import PySide2

from PySide2.QtWidgets import QApplication
from PySide2.QtCore import QFile, QObject, SIGNAL, Slot, QEvent
from PySide2.QtUiTools import QUiLoader

from StandardDraw import StandardDraw


class MainWindow(QObject):
    # Sizes in mm    Designation               width  height
    SHEET_SIZES =  [["User defined",           (0,    0)],
                    ["ISO 216 4A0",            (2378, 1682)],
                    ["ISO 216 2A0",            (1682, 1189)],
                    ["ISO 216 A0",             (1189, 841)],
                    ["ISO 216 A1",             (841,  594)],
                    ["ISO 216 A2",             (594,  420)],
                    ["ISO 216 A3",             (420,  297)],
                    ["ISO 216 A4L",            (297,  210)],
                    ["ISO 216 A4P",            (210,  297)],
                    ["ISO 216 B0",             (1414, 1000)],
                    ["ISO 216 B1",             (1000, 707)],
                    ["ISO 216 B2",             (707,  500)],
                    ["ISO 216 B3",             (500,  353)],
                    ["ISO 216 B4",             (353,  250)],
                    ["ISO 216 B3",             (250,  176)],
                    ["ANSI Y14.1 AL (Letter)", (279,  216)],
                    ["ANSI Y14.1 AP (Letter)", (216,  279)],
                    ["ANSI Y14.1 B",           (432,  279)],
                    ["ANSI Y14.1 C",           (559,  432)],
                    ["ANSI Y14.1 D",           (864,  559)],
                    ["ANSI Y14.1 E",           (1118, 864)],
                    ["ANSI Y14.1 F",           (1016, 711)],
                    ["Legal",                  (356,  216)],
                    ["Tabloid (Ledger)",       (432,  279)],
                    ["Arch AL",                (305,  229)],
                    ["Arch AP",                (229,  305)],
                    ["Arch B",                 (457,  305)],
                    ["Arch C",                 (610,  457)],
                    ["Arch D",                 (914,  610)],
                    ["Arch E",                 (1219, 914)],
                    ["Arch E1",                (1067, 726)],
                    ["Arch E2",                (965,  660)],
                    ["Arch E3",                (991,  686)],]
    
    SHEET_STYLES =  [['ISO5457 ISO700 A',      0],
                     ['ISO5457 ISO700 B',      1]]
    
    FOLD_LINES =    [['None',          0],
                     ['DIN824 A',      1],
                     ['200mm x 290mm', 2]]

    CURRENT_SIZE = SHEET_SIZES[0][1]
    CURREN_SIZE_STRING = 'User defined'
    CURRENT_FULL_PAGE_PARTS_LIST = False

    def __init__(self):
        super(MainWindow, self).__init__()
        self.load_ui()
        self.window.setWindowTitle("KiCAD & FreeCAD TechDraw Template Generator")
        self.load_sheet_sizes()
        self.load_sheet_styles()
        self.load_fold_lines()
        self.init_sheet_spinBox()
        QObject.connect(self.window.SheetSizeComboBox, SIGNAL ('currentIndexChanged(int)'), self.SheetComboBoxChanged)
        QObject.connect(self.window.FullPartsListCheckBox, SIGNAL ('stateChanged(int)'), self.FullPartsListChanged)
        QObject.connect(self.window.GeneratePushButton, SIGNAL ('clicked()'), self.OnGenerateButtonClicked)
        self.connectSheetSpinBoxSignal()

    def load_ui(self):
        loader = QUiLoader()
        path = os.fspath(Path(__file__).resolve().parent / "form.ui")
        ui_file = QFile(path)
        ui_file.open(QFile.ReadOnly)
        self.window = loader.load(ui_file)
        ui_file.close()

    def load_sheet_sizes(self):
        for s in self.SHEET_SIZES:
            self.window.SheetSizeComboBox.addItem(s[0], userData=s[1])
            
    def load_sheet_styles(self):
        for s in self.SHEET_STYLES:
            self.window.SheetStyleComboBox.addItem(s[0], userData=s[1])

    def init_sheet_spinBox(self):
        self.window.sheetWidthDoubleSpinBox.setSuffix(" mm")
        self.window.sheetHeightDoubleSpinBox.setSuffix(" mm")
        
    def load_fold_lines(self):
        for f in self.FOLD_LINES:
            self.window.foldingLinesComboBox.addItem(f[0], userData=f[1])

    def show(self):
        self.window.show()

    def SheetComboBoxChanged(self, index):
        self.disconnectSheetSpinBoxSignal()
        CURRENT_SIZE = self.window.SheetSizeComboBox.itemData(index)
        print(str(CURRENT_SIZE))
        if CURRENT_SIZE == (210,  297) and self.window.FullPartsListCheckBox.isEnabled() == False:# A4P
            self.window.FullPartsListCheckBox.setEnabled(True)
        else:
            self.CURRENT_FULL_PAGE_PARTS_LIST = False
            self.window.FullPartsListCheckBox.setChecked(False)
            self.window.FullPartsListCheckBox.setEnabled(False)
            self.window.FullPartsListSmallCheckBox.setEnabled(False)
            self.window.FullPartsListNumSheetsLabel.setEnabled(False)
            self.window.FullPartsListNumSheetsSpinBox.setEnabled(False)
            self.window.SmallPartsListCheckBox.setEnabled(True)
            self.window.RevHistoryCheckBox.setEnabled(True)
        self.window.sheetWidthDoubleSpinBox.setValue(CURRENT_SIZE[0])
        self.window.sheetHeightDoubleSpinBox.setValue(CURRENT_SIZE[1])
        if self.window.SheetSizeComboBox.currentText() == 'User defined':
            self.window.NameLineEdit.setEnabled(True)
        else:
            self.window.NameLineEdit.setEnabled(False)

        self.connectSheetSpinBoxSignal()

    def FullPartsListChanged(self, val):
        if val != 0:
            self.CURRENT_FULL_PAGE_PARTS_LIST = True
            self.window.FullPartsListSmallCheckBox.setEnabled(True)
            self.window.FullPartsListNumSheetsLabel.setEnabled(True)
            self.window.FullPartsListNumSheetsSpinBox.setEnabled(True)
            self.window.SmallPartsListCheckBox.setEnabled(False)
            self.window.RevHistoryCheckBox.setEnabled(False)
        else:
            self.CURRENT_FULL_PAGE_PARTS_LIST = False
            self.window.FullPartsListSmallCheckBox.setEnabled(False)
            self.window.FullPartsListNumSheetsLabel.setEnabled(False)
            self.window.FullPartsListNumSheetsSpinBox.setEnabled(False)
            self.window.SmallPartsListCheckBox.setEnabled(True)
            self.window.RevHistoryCheckBox.setEnabled(True)

    def connectSheetSpinBoxSignal(self):
        QObject.connect(self.window.sheetWidthDoubleSpinBox, SIGNAL ('valueChanged(double)'), self.SheetSpinBoxWidthChanged)
        QObject.connect(self.window.sheetHeightDoubleSpinBox, SIGNAL ('valueChanged(double)'), self.SheetSpinBoxHeightChanged)

    def disconnectSheetSpinBoxSignal(self):
        QObject.disconnect(self.window.sheetWidthDoubleSpinBox, SIGNAL ('valueChanged(double)'), self.SheetSpinBoxWidthChanged)
        QObject.disconnect(self.window.sheetHeightDoubleSpinBox, SIGNAL ('valueChanged(double)'), self.SheetSpinBoxHeightChanged)

    def SheetSpinBoxWidthChanged(self, value):
        if value != self.CURRENT_SIZE[0]:
            QObject.disconnect(self.window.SheetSizeComboBox, SIGNAL ('currentIndexChanged(int)'), self.SheetComboBoxChanged)
            self.window.SheetSizeComboBox.setCurrentIndex(0)
            QObject.connect(self.window.SheetSizeComboBox, SIGNAL ('currentIndexChanged(int)'), self.SheetComboBoxChanged)

    def SheetSpinBoxHeightChanged(self, value):
        if value != self.CURRENT_SIZE[1]:
            QObject.disconnect(self.window.SheetSizeComboBox, SIGNAL ('currentIndexChanged(int)'), self.SheetComboBoxChanged)
            self.window.SheetSizeComboBox.setCurrentIndex(0)
            QObject.connect(self.window.SheetSizeComboBox, SIGNAL ('currentIndexChanged(int)'), self.SheetComboBoxChanged)

    def OnGenerateButtonClicked(self):
        size = self.window.SheetSizeComboBox.itemData(self.window.SheetSizeComboBox.currentIndex())
        style = self.window.SheetStyleComboBox.itemData(self.window.SheetStyleComboBox.currentIndex())
        if self.window.SheetSizeComboBox.currentText() == 'User defined':
            sizeString = self.window.NameLineEdit.text()
            size = (self.window.sheetWidthDoubleSpinBox.value(), self.window.sheetHeightDoubleSpinBox.value())
        else:
            sizeString = self.window.SheetSizeComboBox.currentText()
        cuttingMarks = self.window.cuttingMarksCheckBox.isChecked()
        color = self.window.ColorLineEdit.text()
        numOptLin = self.window.OptLinesSpinBox.value()
        revHistory = self.window.RevHistoryCheckBox.isChecked()
        foldLinesValue = self.window.foldingLinesComboBox.itemData(self.window.foldingLinesComboBox.currentIndex())
        foldLinesText = self.window.foldingLinesComboBox.currentText()
        fullPartsList = self.window.FullPartsListCheckBox.isChecked()
        fullPartsListSmall = self.window.FullPartsListSmallCheckBox.isChecked()
        fullPartsListNumSheets = self.window.FullPartsListNumSheetsSpinBox.value()
        smallPartsList = self.window.SmallPartsListCheckBox.isChecked()
        smallPartsListNumLines = self.window.SmallPartsListSpinBox.value()
        numRevisions = self.window.numRevSpinBox.value()
        
        if foldLinesValue == 0:
            foldLinesDIN824_A = False
            foldLines200x290 = False
        elif foldLinesValue == 1:
            foldLinesDIN824_A = True
            foldLines200x290 = False
        elif foldLinesValue == 2:
            foldLinesDIN824_A = False
            foldLines200x290 = True

        print("Generate:")
        print("Size: " + str(size))
        print("Size String: " + sizeString)
        print('Cutting marks: ' + str(cuttingMarks))
        print("Color: " + color)
        print("Num. Opt. Lines: " + str(numOptLin))
        print("Rev. History: " + str(revHistory))
        print("Num Rev.: " + str(numRevisions))
        print("Folding Lines: " + str(foldLinesText) + ', ' + str(foldLinesValue))
        print("Full Parts List: " + str(fullPartsList))
        print("Full Parts List Small Felds: " + str(fullPartsListSmall))
        print("Full Parts List Num. Sheets: " + str(fullPartsListNumSheets))
        print("Small Parts List: " + str(smallPartsList))

        stdDraw = StandardDraw(size = size, sizeString = sizeString, cuttingMarks = cuttingMarks, color = color, numOptLines = numOptLin, revHistory = revHistory, numRevisions = numRevisions, foldLinesDIN824_A = foldLinesDIN824_A, foldLines200x290 = foldLines200x290, fullPartsList = fullPartsList, fullPartsListSmallLines = fullPartsListSmall, fullPartsListNumSheets = fullPartsListNumSheets, smallPartsList = smallPartsList, smallPartsListNumLines = smallPartsListNumLines)
        if style == 0:
            stdDraw.drawISO5457_ISO700_A()
        elif style == 1:
            stdDraw.drawISO5457_ISO700_B()
        else:
            stdDraw.drawISO5457_ISO700_A()


if __name__ == "__main__":
    app = QApplication([])
    widget = MainWindow()
    widget.show()
    sys.exit(app.exec_())

# foldingLinesComboBox