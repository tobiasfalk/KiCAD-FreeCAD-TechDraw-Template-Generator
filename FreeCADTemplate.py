# This Python file uses the following encoding: utf-8
import svgwrite
#from svgwrite import mm
from svgwrite.data.types import SVGAttribute

class FreeCADTemplateSVG(svgwrite.Drawing):
    """An svgwrite.Drawing subclass which supports FreeCAD layers"""
    FREECAD_NAMESPACE = 'http://www.freecadweb.org/wiki/index.php?title=Svg_Namespace'
    EDITABLE_INDEX = 0

    def __init__(self, filename="noname.svg", size=('100%', '100%'), *args, **kwargs):
        super(FreeCADTemplateSVG, self).__init__(filename, size, *args, **kwargs)

        view_box = '0 0 ' + str(size[0]) + ' ' + str(size[1]) + ''

        freecad_attributes = {
            'xmlns:freecad': SVGAttribute('xmlns:freecad',
                                          anim=False,
                                          types=[],
                                          const=frozenset([self.FREECAD_NAMESPACE])),
            'viewBox': SVGAttribute('viewBox',
                                    anim=False,
                                    types=[],
                                    const=frozenset([view_box])),
            'freecad:editable': SVGAttribute('freecad:editable',
                                             anim=False,
                                             types=[],
                                             const=frozenset(['True'])),
        }

        self.validator.attributes.update(freecad_attributes)

        elements = self.validator.elements

        svg_attributes = set(elements['svg'].valid_attributes)
        svg_attributes.add('xmlns:freecad')
        svg_attributes.add('viewBox')
        elements['svg'].valid_attributes = frozenset(svg_attributes)

        text_editable_attributes = set(elements['text'].valid_attributes)
        text_editable_attributes.add('freecad:editable')
        elements['text'].valid_attributes = frozenset(text_editable_attributes)

        self['xmlns:freecad'] = self.FREECAD_NAMESPACE
        self['viewBox'] = view_box

    def text_editable(self, text, insert=None, x=None, y=None, dx=None, dy=None, rotate=None, **extra):
        new_text = self.text('', insert, x, y, dx, dy, rotate, **extra)
        new_text.add(self.tspan(text))
        new_text['freecad:editable'] = str(self.EDITABLE_INDEX)
        self.EDITABLE_INDEX += 1

        return new_text
