import sys
import fitz

try:
    pdfPath = ""
    pngPath = ""
    x = ""
    y = ""

    print(sys.argv)

    if len(sys.argv) == 5:
        pdfPath = sys.argv[1]
        pngPath = sys.argv[2]
        x = sys.argv[3]
        y = sys.argv[4]
    else:
        print("no Input!!!")

    print(pdfPath + "\n" + pngPath)

    pdf = fitz.open(pdfPath)
    pdfPage = pdf.load_page(0)
    pix = pdfPage.get_pixmap()
    pix.set_dpi(int(x), int(y))
    pix.save(pngPath)

    print("success")
except:
    print("Py Fail")


