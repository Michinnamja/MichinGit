from tkinter import *
from tkinter import messagebox
from tkinter.filedialog import *
from tkinter.simpledialog import *
import os.path
import math

#전역 변수부
window, canvas , paper = None, None , None
inImage, outImage = [], []
inH, inW , outH , outW =[0]*4
fullname = ""

### 함수부
# 공통 함수부
def malloc2D(h,w,initValue=0) :
    memory = [ [initValue for _ in range(w)] for _ in range(h)]
    return memory

def openImage():
    global window, canvas , paper , fullname
    global inImage, outImage , inH, inW , outH , outW
    fullname = askopenfilename(parent=window, filetypes=(('RAW파일', '*.raw'), ('모든파일', '*.*')))
    fsize=os.path.getsize(fullname)   # 파일크기
    inH = inW = int(math.sqrt(fsize))
    # 메모리 할당
    inImage = malloc2D(inH,inW)
    # 파일 --> 메모리
    rfp = open(fullname, 'rb')
    for i in range(inH):
        for k in range(inW):
            inImage[i][k] = ord(rfp.read(1))
    rfp.close()
    equalImage()

def saveImage() :
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    if (outImage == None or len(outImage)==0) :
        return
    wfp = asksaveasfile(parent=window, mode='wb', defaultextension='*.raw',
                        filetypes=(('RAW파일', '*.raw'), ('모든파일', '*.*'))  )
    import struct
    for i in range(outH) :
        for k in range(outW) :
            wfp.write( struct.pack('B', outImage[i][k]) )
    wfp.close()
    messagebox.showinfo('성공', wfp.name + ' 저장완료!')

def displayImage():
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    if(canvas !=None):
        canvas.destroy()

    window.geometry(str(outH)+"x"+str(outW))
    canvas = Canvas(window, height=outH, width=outW, bg='yellow')  # 칠판
    paper = PhotoImage(height=outH, width=outW)  # 종이
    canvas.create_image((outH // 2, outW // 2), image=paper, state='normal')

    # for i in range(inH):
    #     for k in range(inW):
    #         r = g = b = inImage[i][k]
    #         paper.put('#%02x%02x%02x' % (r, g, b), (k, i))
    # 더블 버퍼링과 비슷한 기법(모두 메모리 상에 출력형태로 생성한 후 , 한번에 출력)
    rgbString=""  # 전체에 대한 16진수 문자열
    for i in range(outH):
        oneString=""
        for k in range(outW):
            r = g = b = outImage[i][k]
            oneString += '#%02x%02x%02x ' % (r, g, b)
        rgbString += "{" + oneString + "} "
    paper.put(rgbString)

    canvas.pack()

def clampi(value, min, max):
    if(value > max):
        return max
    if(value < min):
        return min
    else:
        return value


#영상 처리 함수부
def equalImage(): # 동일 이미지
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    #출력 영상 크기 결정 -->
    outH = inH
    outW = inW
    #메모리 할당
    outImage = malloc2D(outH,outW)
    for i in range(inH):
        for k in range(inW):
            outImage[i][k]=inImage[i][k]
    displayImage()

def addImage(): # 밝기 조절
    value = askinteger("정수 입력","-255~255 입력",maxvalue=255 , minvalue=-255)

    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    #출력 영상 크기 결정 -->
    outH = inH
    outW = inW
    #메모리 할당
    outImage = malloc2D(outH,outW)
    for i in range(inH):
        for k in range(inW):
            px=inImage[i][k]+value
            if(px>255):
                px=255
            if(px<0):
                px=0
            outImage[i][k]=px

    displayImage()

def reverseImage():
    global inImage, outImage, inH, inW, outH, outW
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

    for i in range(inH):
        for k in range(inW):
            outImage[i][k] =255-inImage[i][k]
    displayImage()


def bwImage():  # 흑백 127 기준
    global inImage, outImage, inH, inW, outH, outW
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

    for i in range(inH):
        for k in range(inW):
            if(inImage[i][k]>127) :
                outImage[i][k] = 255
            else :
                outImage[i][k] = 0
    displayImage()


def bwImage2(): # 흑백 평균값 기준
    global inImage, outImage, inH, inW, outH, outW
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)
    hap = 0

    for i in range(inH) :
        for k in range(inW) :
            hap+=inImage[i][k]
    hap/=inH*inW

    for i in range(inH):
        for k in range(inW):
            if(inImage[i][k]>hap) :
                outImage[i][k] = 255
            else :
                outImage[i][k] = 0
    displayImage()


def bwImage3(): # 흑백 중앙값
    global inImage, outImage, inH, inW, outH, outW
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)
    count = [0 for _ in range(256)]
    sum , half = 0 , 0
    for i in range(inH) :
        for k in range(inW) :
            count[inImage[i][k]]+=1

    for i in range(256) :
        sum += count[i]
        if(sum>inH*inW/2) :
            half=i;
            break

    for i in range(inH):
        for k in range(inW):
            if(inImage[i][k]>half) :
                outImage[i][k]=255
            else :
                outImage[i][k]=0
    displayImage()


def gamma():
    global inImage, outImage, inH, inW, outH, outW
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

    print("감마",end=" ")
    val = askfloat("실수 입력","0.0001보다 큰 값",minvalue=0.0001)

    for i in range(inH):
        for k in range(inW):
            tmp =int(pow(inImage[i][k], 1/val))

            if(tmp>255):
                outImage[i][k]=255
            elif(tmp<0):
                outImage[i][k]:0
            else:
                outImage[i][k]=tmp
    displayImage()

def posterize():
    global inImage, outImage, inH, inW, outH, outW
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

    print("2~256 사이의 값 중 입력할",end=" ")
    level = askinteger("정수 입력","2~256",maxvalue=256,minvalue=2)
    if(level<2):
        return
    if(level>256):
        return
    border = 256/level
    interval = 256/(level-1)

    for i in range(inH):
        for k in range(inW):
            tmp =int((inImage[i][k]/border) * interval)
            outImage[i][k]=clampi(tmp,0,255)


            if(tmp>255):
                outImage[i][k]=255
            if(tmp<0):
                outImage[i][k]=0
            else:
                outImage[i][k]=tmp
    displayImage()

def highlight() :
    global inImage , outImage , inH , inW , outH , outW
    outH = inH
    outW = inW
    outImage = malloc2D(outH,outW)

    start = askinteger("시작값 입력","0~255",maxvalue=255,minvalue=0)
    end = askinteger("종료값 입력",str(start)+"~255",maxvalue=255,minvalue=start)

    for i in range(inH) :
        for k in range(inW) :
            if(inImage[i][k]<=start):
                outImage[i][k]=0
            if(inImage[i][k]>=end):
                outImage[i][k]=255
            else:
                outImage[i][k]=inImage[i][k]
    displayImage()


def histoImage():
    global inImage, outImage, inH, inW, outH, outW
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

    high = inImage[0][0]
    low = inImage[0][0]
    for i in range(inH):
        for k in range(inW):
            if(inImage[i][k]<low):
                low=inImage[i][k]
            if(inImage[i][k]>high):
                high=inImage[i][k]

    for i in range(inH):
        for k in range(inW):
            old=inImage[i][k]
            new=int((old-low)/(high-low)*255)
            if(new>255):
                new=255
            if(new<0):
                new=0
            outImage[i][k]=new
    displayImage()

def endIn():
    global inImage, outImage, inH, inW, outH, outW
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

    high = inImage[0][0]
    low = inImage[0][0]
    for i in range(inH):
        for k in range(inW):
            if (inImage[i][k] < low):
                low = inImage[i][k]
            if (inImage[i][k] > high):
                high = inImage[i][k]
    high-=50
    low+=50

    for i in range(inH):
        for k in range(inW):
            old = inImage[i][k]
            new =int(((old - low) / (high - low)) * 255)
            if (new > 255):
                new = 255
            if (new < 0):
                new = 0
            outImage[i][k] = new
    displayImage()

def histoEqual():
    global inImage, outImage, inH, inW, outH, outW
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

    normalHisto = [0 for _ in range(256)]
    sumHisto = [0 for _ in range(256)]
    histo = [0 for _ in range(256)]
    for i in range(256):
        histo[i]=i

    for i in range(256):
        sumHisto[i]=sumHisto[i-1]+histo[i]

    for i in range(256):
        normalHisto[i]=sumHisto[i]*(1/(inH*inW)*255)

    for i in range(inH):
        for k in range(inW):
            outImage[i][k]=int(normalHisto[inImage[i][k]])
    displayImage()


## 기하학 처리


def zoomOut() :

    scale = askinteger("분모 입력","1보다 큰 값",minvalue=1)

    global inImage , outImage , inH , inW , outH , outW
    outH = int(inH/scale)
    outW = int(inW/scale)
    outImage = malloc2D(outH,outW)

    for i in range(outH) :
        for k in range(outW) :
           outImage[i][k]=inImage[i*scale][k*scale]
    displayImage()


def zoomOut2():  #축소 평균값

    scale = askinteger("분모 입력","1보다 큰 값",minvalue=1)

    global inImage, outImage, inH, inW, outH, outW
    outH = int(inH / scale)
    outW = int(inW / scale)
    outImage = malloc2D(outH, outW)

    for i in range(outH):
        for k in range(outW):
            outImage[i][k] = 0

    for i in range(outH*scale):
        for k in range(outW*scale):
            outImage[int(i/scale)][int(k/scale)]+=inImage[i][k]

    for i in range(outH):
        for k in range(outW):
            outImage[i][k]=int(outImage[i][k]/(scale*scale))

    displayImage()

def zoomOut3():

    scale = askinteger("분모 입력", "1보다 큰 값", minvalue=1)

    global inImage, outImage, inH, inW, outH, outW
    outH = int(inH / scale)
    outW = int(inW / scale)
    outImage = malloc2D(outH, outW)


    for i in range(outH):
        for k in range(outW):
            sum=0
            count = [0 for _ in range(256)]
            for m in range(scale):
                for n in range(scale):
                    count[inImage[(scale*i)+m][(scale*k)+n]]+=1
            for m in range(256):
                if(sum>(scale*scale)/2):
                    outImage[i][k]=m
                    break
                else:
                    sum+=count[m]

    displayImage()

def zoomIn():
    scale = askinteger("곱할 값 입력", "1보다 큰 값", minvalue=1)

    global inImage, outImage, inH, inW, outH, outW
    outH = inH*scale
    outW = inW*scale
    outImage = malloc2D(outH, outW)

    for i in range(inH):
        for k in range(inW):
            outImage[i*scale][k*scale]=inImage[i][k]

    displayImage()

def zoomIn2():
    scale = askinteger("곱할 값 입력", "1보다 큰 값", minvalue=1)

    global inImage, outImage, inH, inW, outH, outW
    outH = inH*scale
    outW = inW*scale
    outImage = malloc2D(outH, outW)

    for i in range(outH):
        for k in range(outW):
            outImage[i][k]=inImage[int(i/scale)][int(k/scale)]

    displayImage()

def rotate():

    degree = askinteger("각도 입력","0~360 도",maxvalue=360,minvalue=0)
    radian = degree *3.141592/180

    global inImage, outImage, inH, inW, outH, outW
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

    for i in range(inH):
        for k in range(inW):
            xs=i
            ys=k
            xd=int(math.cos(radian)*xs-math.sin(radian)*ys)
            yd=int(math.sin(radian)*xs+math.cos(radian)*ys)

            if((0<=xd<outH)&(0<=yd<outW)):
                outImage[xd][yd]=inImage[i][k]

    displayImage()


def rotate2():
    degree = askinteger("각도 입력", "0~360 도", maxvalue=360, minvalue=0)
    radian = degree * 3.141592 / 180

    global inImage, outImage, inH, inW, outH, outW
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

    cx=int(inH/2)
    cy=int(inW/2)

    for i in range(inH):
        for k in range(inW):
            xd = i
            yd = k
            xs =int(math.cos(radian) * (xd-cx) + math.sin(radian) * (yd-cy))
            ys =int(-math.sin(radian) * (xd-cx) + math.cos(radian) * (yd-cy))
            xs+=cx
            ys+=cy
            if ((0 <= xs < outH) & (0 <= ys < outW)):
                outImage[xd][yd] = inImage[xs][ys]

    displayImage()

def moveImage():

    global inImage, outImage, inH, inW, outH, outW
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

    scale = askinteger("가로", "가로", maxvalue=1000,minvalue=-1000)
    scale2 = askinteger("세로", "세로", maxvalue=1000, minvalue=-1000)

    for i in range(inH):
        for k in range(inW):
            if((0<=i-scale<inH)&(0<=k+scale2<inW)):
                outImage[i-scale][k+scale2]=inImage[i][k]

    displayImage()

def lrImage():


    global inImage, outImage, inH, inW, outH, outW
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

    for i in range(inH):
        for k in range(inW):
            outImage[i][k]=inImage[i][inW-1-k]

    displayImage()
    pass

def udImage():


    global inImage, outImage, inH, inW, outH, outW
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

    for i in range(inH):
        for k in range(inW):
            outImage[i][k]=inImage[inH-1-i][k]

    displayImage()
    pass

def lrudImage():


    global inImage, outImage, inH, inW, outH, outW
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

    for i in range(inH):
        for k in range(inW):
            outImage[i][k]=inImage[inH-1-i][inW-1-k]

    displayImage()
    pass

# 화소 영역처리

def emboss():
    scale = askinteger("마스크", "홀수만", minvalue=3)
    mask = malloc2D(scale,scale)
    sc=scale-1
    sc2=int(sc/2)
    global inImage, outImage, inH, inW, outH, outW
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

    mask[0][0]=-1
    mask[sc][sc]=1

    tmpInImage=malloc2D(inH+sc,inW+sc,127)
    tmpOutImage=malloc2D(inH,inW)

    for i in range(inH):
        for k in range(inW):
            tmpInImage[i+sc2][k+sc2]=inImage[i][k]

    for i in range(inH):
        for k in range(inW):
            s=0
            for m in range(scale):
                for n in range(scale):
                    s+=tmpInImage[i+m][k+n]*mask[m][n]
            tmpOutImage[i][k]=s+127
    for i in range(outH):
        for k in range(outW):
            if(tmpOutImage[i][k]>255):
                outImage[i][k]=255
            if(tmpOutImage[i][k]<0):
                outImage[i][k]=0
            else:
                outImage[i][k]=int(tmpOutImage[i][k])

    displayImage()
    pass

def blr():
    scale = askinteger("마스크", "홀수만", minvalue=3)
    mask = malloc2D(scale, scale,1/(scale*scale))
    sc = scale - 1
    sc2=int(sc/2)
    global inImage, outImage, inH, inW, outH, outW
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)


    tmpInImage = malloc2D(inH + sc, inW + sc,127)
    tmpOutImage = malloc2D(inH, inW)

    for i in range(inH):
        for k in range(inW):
            tmpInImage[i +sc2][k +sc2] = inImage[i][k]

    for i in range(inH):
        for k in range(inW):
            s = 0
            for m in range(scale):
                for n in range(scale):
                    s += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = s

    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] > 255):
                outImage[i][k] = 255
            if (tmpOutImage[i][k] < 0):
                outImage[i][k] = 0
            else:
                outImage[i][k] = int(tmpOutImage[i][k])

    displayImage()
    pass

def sharp():
    scale = askinteger("마스크", "홀수만", minvalue=3)
    mask = malloc2D(scale, scale,-1)
    sc = scale - 1
    sc2 = int(sc / 2)
    global inImage, outImage, inH, inW, outH, outW
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

    mask[sc2][sc2]=scale*scale

    tmpInImage = malloc2D(inH + sc, inW + sc, 127)
    tmpOutImage = malloc2D(inH, inW)

    for i in range(inH):
        for k in range(inW):
            tmpInImage[i + sc2][k + sc2] = inImage[i][k]

    for i in range(inH):
        for k in range(inW):
            s = 0
            for m in range(scale):
                for n in range(scale):
                    s += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = s
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] > 255):
                outImage[i][k] = 255
            if (tmpOutImage[i][k] < 0):
                outImage[i][k] = 0
            else:
                outImage[i][k] = int(tmpOutImage[i][k])

    displayImage()
    pass

def edge1():  #수직 엣지

    global inImage, outImage, inH, inW, outH, outW
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

    scale=3
    sc=scale-1
    sc2 = int(sc / 2)
    mask = [[ 0,-1, 0],
            [ 0, 1, 0],
            [ 0, 0, 0]]

    tmpInImage = malloc2D(inH + sc, inW + sc, 127)
    tmpOutImage = malloc2D(inH, inW)

    for i in range(inH):
        for k in range(inW):
            tmpInImage[i + sc2][k + sc2] = inImage[i][k]

    for i in range(inH):
        for k in range(inW):
            s = 0
            for m in range(scale):
                for n in range(scale):
                    s += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = s + 127
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] > 255):
                outImage[i][k] = 255
            if (tmpOutImage[i][k] < 0):
                outImage[i][k] = 0
            else:
                outImage[i][k] = int(tmpOutImage[i][k])

    displayImage()
    pass

def edge2(): # 수평 엣지

    global inImage, outImage, inH, inW, outH, outW
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

    scale = 3
    sc = scale - 1
    sc2 = int(sc / 2)
    mask = [[0, 0, 0],
            [-1, 1, 0],
            [0, 0, 0]]

    tmpInImage = malloc2D(inH + sc, inW + sc, 127)
    tmpOutImage = malloc2D(inH, inW)

    for i in range(inH):
        for k in range(inW):
            tmpInImage[i + sc2][k + sc2] = inImage[i][k]

    for i in range(inH):
        for k in range(inW):
            s = 0
            for m in range(scale):
                for n in range(scale):
                    s += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = s + 127
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] > 255):
                outImage[i][k] = 255
            if (tmpOutImage[i][k] < 0):
                outImage[i][k] = 0
            else:
                outImage[i][k] = int(tmpOutImage[i][k])

    displayImage()
    pass

def edge3(): #유사연산자

    global inImage, outImage, inH, inW, outH, outW
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

    for i in range(1,inH-1,1):
        for k in range(1,inW-1,1):
            max=0
            for m in range(-1,2,1):
                for n in range(-1,2,1):
                    if(inImage[i][k]-inImage[i+m][k+n]>=max):
                        max=inImage[i][k]-inImage[i+m][k+n]
            outImage[i][k]=max

    for i in range(outH):
        for k in range(outW):
           if(outImage[i][k]<0):
               outImage[i][k]=0
           if(outImage[i][k]>255):
               outImage[i][k]=255

    displayImage()
    pass

def edge4(): #차연산자

    global inImage, outImage, inH, inW, outH, outW
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)


    for i in range(1,inH-1,1):
        for k in range(1,inW-1,1):
            max=0
            if(inImage[i-1][k-1]-inImage[i+1][k+1]>=max):
                max=inImage[i-1][k-1]-inImage[i+1][k+1]
            if (inImage[i - 1][k] - inImage[i + 1][k] >= max):
                max = inImage[i - 1][k] - inImage[i + 1][k]
            if (inImage[i - 1][k+1] - inImage[i + 1][k-1] >= max):
                max = inImage[i - 1][k+1] - inImage[i + 1][k-1]
            if (inImage[i][k-1] - inImage[i][k+1] >= max):
                max = inImage[i][k-1] - inImage[i][k+1]

            outImage[i][k]=max

    for i in range(outH):
        for k in range(outW):
            if (outImage[i][k] < 0):
                outImage[i][k] = 0
            if (outImage[i][k] > 255):
                outImage[i][k] = 255

    displayImage()
    pass

def edge5(): #로버츠엣지

    global inImage, outImage, inH, inW, outH, outW
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

    scale = 3
    sc = scale - 1
    sc2 = int(sc / 2)
    mask = [[-1, 0, -1],
            [0, 2, 0],
            [0, 0, 0]]

    tmpInImage = malloc2D(inH + sc, inW + sc, 127)
    tmpOutImage = malloc2D(inH, inW)

    for i in range(inH):
        for k in range(inW):
            tmpInImage[i + sc2][k + sc2] = inImage[i][k]

    for i in range(inH):
        for k in range(inW):
            s = 0
            for m in range(scale):
                for n in range(scale):
                    s += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = s
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] > 255):
                outImage[i][k] = 255
            if (tmpOutImage[i][k] < 0):
                outImage[i][k] = 0
            else:
                outImage[i][k] = tmpOutImage[i][k]

    displayImage()
    pass


def edge6(): #프리윗 엣지

    global inImage, outImage, inH, inW, outH, outW
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

    scale = 3
    sc = scale - 1
    sc2 = int(sc / 2)
    mask = [[0, -1, -2],
            [1, 0, -1],
            [2, 1, 0]]

    tmpInImage = malloc2D(inH + sc, inW + sc, 127)
    tmpOutImage = malloc2D(inH, inW)

    for i in range(inH):
        for k in range(inW):
            tmpInImage[i + sc2][k + sc2] = inImage[i][k]

    for i in range(inH):
        for k in range(inW):
            s = 0
            for m in range(scale):
                for n in range(scale):
                    s += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = s
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] > 255):
                outImage[i][k] = 255
            if (tmpOutImage[i][k] < 0):
                outImage[i][k] = 0
            else:
                outImage[i][k] = tmpOutImage[i][k]

    displayImage()
    pass

def edge7(): #소벨 엣지
    global inImage, outImage, inH, inW, outH, outW
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

    scale = 3
    sc = scale - 1
    sc2 = int(sc / 2)
    mask = [[0, -2, -2],
            [2, 0, -2],
            [2, 2, 0]]

    tmpInImage = malloc2D(inH + sc, inW + sc, 127)
    tmpOutImage = malloc2D(inH, inW)

    for i in range(inH):
        for k in range(inW):
            tmpInImage[i + sc2][k + sc2] = inImage[i][k]

    for i in range(inH):
        for k in range(inW):
            s = 0
            for m in range(scale):
                for n in range(scale):
                    s += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = s
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] > 255):
                outImage[i][k] = 255
            if (tmpOutImage[i][k] < 0):
                outImage[i][k] = 0
            else:
                outImage[i][k] = tmpOutImage[i][k]

    displayImage()
    pass

def edge8(): #라플라시안 엣지1
    global inImage, outImage, inH, inW, outH, outW
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

    scale = 3
    sc = scale - 1
    sc2 = int(sc / 2)
    mask = [[0, -1, 0],
            [-1, 4, -1],
            [0, -1, 0]]

    tmpInImage = malloc2D(inH + sc, inW + sc, 127)
    tmpOutImage = malloc2D(inH, inW)

    for i in range(inH):
        for k in range(inW):
            tmpInImage[i + sc2][k + sc2] = inImage[i][k]

    for i in range(inH):
        for k in range(inW):
            s = 0
            for m in range(scale):
                for n in range(scale):
                    s += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = s
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] > 255):
                outImage[i][k] = 255
            if (tmpOutImage[i][k] < 0):
                outImage[i][k] = 0
            else:
                outImage[i][k] = tmpOutImage[i][k]

    displayImage()
    pass

def edge9():#라플라 2
    global inImage, outImage, inH, inW, outH, outW
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

    scale = 3
    sc = scale - 1
    sc2=int(sc/2)
    mask = [[1, 1, 1],
            [1, -8, 1],
            [1, 1, 1]]

    tmpInImage = malloc2D(inH + sc, inW + sc, 127)
    tmpOutImage = malloc2D(inH, inW)

    for i in range(inH):
        for k in range(inW):
            tmpInImage[i + sc2][k + sc2] = inImage[i][k]

    for i in range(inH):
        for k in range(inW):
            s = 0
            for m in range(scale):
                for n in range(scale):
                    s += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = s
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] > 255):
                outImage[i][k] = 255
            if (tmpOutImage[i][k] < 0):
                outImage[i][k] = 0
            else:
                outImage[i][k] = tmpOutImage[i][k]

    displayImage()
    pass

def edge10(): #라플라3
    global inImage, outImage, inH, inW, outH, outW
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

    scale = 3
    sc = scale - 1
    sc2 = int(sc / 2)
    mask = [[-1, -1, -1],
            [-1, 8, -1],
            [-1, -1, -1]]

    tmpInImage = malloc2D(inH + sc, inW + sc, 127)
    tmpOutImage = malloc2D(inH, inW)

    for i in range(inH):
        for k in range(inW):
            tmpInImage[i + sc2][k + sc2] = inImage[i][k]

    for i in range(inH):
        for k in range(inW):
            s = 0
            for m in range(scale):
                for n in range(scale):
                    s += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = s
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] > 255):
                outImage[i][k] = 255
            if (tmpOutImage[i][k] < 0):
                outImage[i][k] = 0
            else:
                outImage[i][k] = tmpOutImage[i][k]

    displayImage()
    pass

def edge11(): #라플라4

    global inImage, outImage, inH, inW, outH, outW
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

    scale = 5
    sc = scale - 1
    sc2 = int(sc / 2)
    mask = [[ 0, 0,-1, 0, 0],
            [ 0,-1,-2,-1, 0],
            [-1,-2,16,-2,-1],
            [ 0,-1,-2,-1, 0],
            [ 0, 0,-1, 0, 0]]

    tmpInImage = malloc2D(inH + sc, inW + sc, 127)
    tmpOutImage = malloc2D(inH, inW)

    for i in range(inH):
        for k in range(inW):
            tmpInImage[i + sc2][k + sc2] = inImage[i][k]

    for i in range(inH):
        for k in range(inW):
            s = 0
            for m in range(scale):
                for n in range(scale):
                    s += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = s
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] > 255):
                outImage[i][k] = 255
            if (tmpOutImage[i][k] < 0):
                outImage[i][k] = 0
            else:
                outImage[i][k] = tmpOutImage[i][k]

    displayImage()
    pass

def dog(): #개 엣지1
    global inImage, outImage, inH, inW, outH, outW
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

    scale = 7
    sc = scale - 1
    sc2 = int(sc / 2)
    mask = [[ 0, 0,-1,-1,-1, 0, 0],
            [ 0,-2,-3,-3,-3,-2, 0],
            [-1,-3, 5, 5, 5,-3,-1],
            [-1,-3, 5,16, 5,-3,-1],
            [-1,-3, 5, 5, 5,-3,-1],
            [ 0,-2,-3,-3,-3,-2, 0],
            [ 0, 0,-1,-1,-1, 0, 0]]

    tmpInImage = malloc2D(inH + sc, inW + sc, 127)
    tmpOutImage = malloc2D(inH, inW)

    for i in range(inH):
        for k in range(inW):
            tmpInImage[i + sc2][k + sc2] = inImage[i][k]

    for i in range(inH):
        for k in range(inW):
            s = 0
            for m in range(scale):
                for n in range(scale):
                    s += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = s
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] > 255):
                outImage[i][k] = 255
            if (tmpOutImage[i][k] < 0):
                outImage[i][k] = 0
            else:
                outImage[i][k] = tmpOutImage[i][k]

    displayImage()
    pass

def dog2(): # 도그2
    global inImage, outImage, inH, inW, outH, outW
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

    scale = 9
    sc = scale - 1
    sc2 = int(sc / 2)
    mask = [[ 0, 0, 0,-1,-1,-1, 0, 0, 0],
            [ 0,-2,-3,-3,-3,-3,-3,-2, 0],
            [ 0,-3,-2,-1,-1,-1,-2,-3, 0],
            [-1,-3,-1, 9, 9, 9,-1,-3,-1],
            [-1,-3,-1, 9,19, 9,-1,-3,-1],
            [-1,-3,-1, 9, 9, 9,-1,-3,-1],
            [ 0,-3,-2,-1,-1,-1,-2,-3, 0],
            [ 0,-2,-3,-3,-3,-3,-3,-2, 0],
            [ 0, 0, 0,-1,-1,-1, 0, 0, 0]]
    tmpInImage = malloc2D(inH + sc, inW + sc, 127)
    tmpOutImage = malloc2D(inH, inW)

    for i in range(inH):
        for k in range(inW):
            tmpInImage[i + sc2][k + sc2] = inImage[i][k]

    for i in range(inH):
        for k in range(inW):
            s = 0
            for m in range(scale):
                for n in range(scale):
                    s += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = s
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] > 255):
                outImage[i][k] = 255
            if (tmpOutImage[i][k] < 0):
                outImage[i][k] = 0
            else:
                outImage[i][k] = tmpOutImage[i][k]

    displayImage()
    pass

### 메인 코드부
window = Tk() # 벽
window.geometry("500x500")
window.resizable(width=False, height=False)
window.title("영상처리(RC 1)")

mainMenu = Menu(window) # 메뉴의 틀
window.config(menu=mainMenu)

fileMenu = Menu(mainMenu, tearoff=0)  # 상위 메뉴 (파일)
mainMenu.add_cascade(label='파일', menu=fileMenu)
fileMenu.add_command(label='열기', command=openImage)
fileMenu.add_command(label='저장', command=saveImage)
fileMenu.add_separator()
fileMenu.add_command(label='종료', command=None)

#화소점 처리

pixelMenu = Menu(mainMenu, tearoff=0)  # 화소점 처리
mainMenu.add_cascade(label='화소점 처리', menu=pixelMenu)
pixelMenu.add_command(label='동일 이미지', command=equalImage)
pixelMenu.add_command(label='밝기 조절', command=addImage)
bwiMenu = Menu(pixelMenu,tearoff=0) # 흑백처리 메뉴
pixelMenu.add_cascade(label="흑백 처리",menu=bwiMenu)
bwiMenu.add_command(label='127 기준', command=bwImage)
bwiMenu.add_command(label='평균값 기준', command=bwImage2)
bwiMenu.add_command(label='중앙값 기준', command=bwImage3)
pixelMenu.add_command(label='감마 처리', command=gamma)
pixelMenu.add_command(label='포스터라이즈', command=posterize)
pixelMenu.add_command(label='하이라이트', command=highlight)
histoMenu = Menu(pixelMenu,tearoff=0) # 히스토 메뉴
pixelMenu.add_cascade(label="히스토그램",menu=histoMenu)
histoMenu.add_command(label='type1', command=histoImage)
histoMenu.add_command(label='type2', command=endIn)
histoMenu.add_command(label='type3', command=histoEqual)

#기하학처리

giaMenu = Menu(mainMenu,tearoff=0) # 기하학처리 메뉴
mainMenu.add_cascade(label="기하학 처리",menu=giaMenu)
zoomOutMenu = Menu(giaMenu,tearoff=0)
giaMenu.add_cascade(label="축소",menu=zoomOutMenu)
zoomOutMenu.add_command(label="기본",command=zoomOut)
zoomOutMenu.add_command(label="평균값",command=zoomOut2)
zoomOutMenu.add_command(label="중앙값",command=zoomOut3)
zoomInMenu = Menu(giaMenu,tearoff=0)
giaMenu.add_cascade(label="확대",menu=zoomInMenu)
zoomInMenu.add_command(label="기본",command=zoomIn)
zoomInMenu.add_command(label="평균값",command=zoomIn2)
rotateMenu = Menu(giaMenu,tearoff=0)
giaMenu.add_cascade(label="회전",menu=rotateMenu)
rotateMenu.add_command(label="기본",command=rotate)
rotateMenu.add_command(label="중앙+백워딩",command=rotate2)
giaMenu.add_command(label="이동",command=moveImage)
lrudMenu=Menu(giaMenu,tearoff=0)
giaMenu.add_cascade(label="반전",menu=lrudMenu)
lrudMenu.add_command(label="좌우",command=lrImage)
lrudMenu.add_command(label="상하",command=udImage)
lrudMenu.add_command(label="원점",command=lrudImage)

# 화소영역 처리
HSMenu=Menu(mainMenu,tearoff=0)
mainMenu.add_cascade(label="화소영역처리",menu=HSMenu)
HSMenu.add_command(label="엠보싱",command=emboss)
HSMenu.add_command(label="블러링",command=blr)
HSMenu.add_command(label="샤프닝",command=sharp)
edgeMenu=Menu(HSMenu,tearoff=0)
HSMenu.add_cascade(label="화소영역처리",menu=edgeMenu)
edgeMenu.add_command(label="수직 엣지",command=edge1)
edgeMenu.add_command(label="수평 엣지",command=edge2)
edgeMenu.add_command(label="유사연산자",command=edge3)
edgeMenu.add_command(label="차연산자",command=edge4)
edgeMenu.add_command(label="로버츠 엣지",command=edge5)
edgeMenu.add_command(label="프리윗 엣지",command=edge6)
edgeMenu.add_command(label="소벨엣지",command=edge7)
edgeMenu.add_command(label="라플라시안1",command=edge8)
edgeMenu.add_command(label="라플라시안2",command=edge9)
edgeMenu.add_command(label="라플라시안3",command=edge10)
edgeMenu.add_command(label="라플라시안4",command=edge11)
edgeMenu.add_command(label="도그",command=dog)
edgeMenu.add_command(label="도그2",command=dog2)



window.mainloop()