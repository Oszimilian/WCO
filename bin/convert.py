import sys
import fitz

try:
    pdfPath = ""
    pngPath = ""
    x = ""
    y = ""

    if len(sys.argv) == 5:
        pdfPath = sys.argv[1]
        pngPath = sys.argv[2]
        x = sys.argv[3]
        y = sys.argv[4]
    else:
        print("---> Error: PyConvert no Input")

    pdf = fitz.open(pdfPath)
    pdfPage = pdf.load_page(0)
    pix = pdfPage.get_pixmap()
    pix.set_dpi(int(x), int(y))
    pix.save(pngPath)

    print("-> PyConvert Succeeded")
except:
    print("-> PyConvert Failed")


