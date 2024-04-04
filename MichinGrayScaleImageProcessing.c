#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <Windows.h> 
#include <math.h>

////////
//진행 개념 raw 파일만 가능합니다 the only .raw file
//raw 파일 받아서 각 화소 값에 대해 알고리즘 적용해 출력하는 방식입니다.
//메뉴 부분은 중요한게 아니고 뒤에 화소점처리, 기하학처리 , 화소영역처리 부분이 영상처리 알고리즘 부분입니다.
///////

// 전역 변수부
HWND hwnd; // 윈도 화면(외부, 물리적)
HDC hdc; // 윈도 화면 (내부, 논리적)
FILE* rfp, * wfp;
char fileName[200];
int inH, inW, outH, outW;

// 메모리 확보
unsigned char** inImage = NULL, ** outImage = NULL;

// 함수 선언부
void loadImage(); int getIntValue(); void printImage(); void printMenu(); void printMenu2(); void printMenu3(); void printMenu4();
void saveImage(); void freeInputMemory(); void freeOutputMemory();
void mallocInputMemory(); void mallocOutputMemory();
double** mallocDoubleMemory(int, int); void freeDoubleMemory(double**, int);
void imageLog();
//화소점처리
void equalImage(); void addImage(); void subImage(); void reverseImage();
void bwImage(); void bwImage2(); void bwImage3(); void gamma(); void highLight(); void posterize();
void histoImage(); void endIn(); void histoEqual();
//화소 영역처리
void emboss(); void blr(); void sharp(); void edge1(); void edge2(); void edge3(); void edge4(); void edge5();
void edge6(); void edge7(); void edge8(); void edge9(); void edge10(); void edge11(); void dog1(); void dog2();
//기하적처리
void zoomOut(); void zoomOut2(); void zoomOut3(); void zoomIn(); void zoomIn2();
void rotate(); void rotate2(); void moveImage(); void lrudImage();



void main() {
	hwnd = GetForegroundWindow();
	hdc = GetWindowDC(NULL);  // Windows 10 : hwnd

	char inKey = 0;
	while (inKey != '9') {
		printMenu();
		inKey = _getch();
		//system("cls");
		switch (inKey)
		{
		case '0': loadImage(); break;
		case '1': saveImage(); break;
		case '9': break;
		case 'a': case'A':printMenu2(); break;
		case 'b': case'B':printMenu3(); break;
		case 'c': case'C':printMenu4(); break;
		}
	}
	freeInputMemory();
	freeOutputMemory();
}


// 함수 정의부

/// 공통 함수
void printMenu() {
	system("cls");
	puts("\n ## GrayScale Image Processing (Beta 4) ##");
	puts("0.열기  1.저장  9. 종료");
	puts("A. 화소점 처리 B. 기하학 처리 C.화소 영역 처리");
}
// 화소점 처리
void printMenu2() {
	char inKey = 0;
	while (inKey != '9') {
		system("cls");
		puts("\n ## GrayScale Image Processing (Beta 4) ##");
		puts("9. 뒤로");
		puts("A.동일 B.밝게 C.어둡게 D.반전");
		puts("E.흑백 F.흑백(평균값) G.흑백(중앙값)");
		puts("H.감마 I.포스터라이즈 J.하이라이트");
		puts("K.히스토1 L.히스토2 M.평활화");
		inKey = _getch();
		switch (inKey) {
		case 'a':case 'A':equalImage(); break;
		case 'b':case 'B':addImage(); break;
		case 'c':case 'C':subImage(); break;
		case 'd':case 'D':reverseImage(); break;
		case 'f':case 'F':bwImage(); break;
		case 'e':case 'E':bwImage2(); break;
		case 'g':case 'G':bwImage3(); break;
		case 'h':case 'H':gamma(); break;
		case 'i':case 'I':posterize(); break;
		case 'j':case 'J':highLight(); break;
		case 'k':case 'K':histoImage(); break;
		case 'l':case 'L':histoEqual(); break;
		case 'm':case 'M':endIn(); break;
		case '9':break;
		}
	}
}
// 기하적 처리
void printMenu3() {
	char inKey = 0;
	while (inKey != '9') {
		system("cls");
		puts("\n ## GrayScale Image Processing (Beta 4) ##");
		puts("9. 뒤로");
		puts("A.축소 B.확대 C.확대2 D.회전 E.회전2");
		puts("F.이동 G.반전 H.축소(평균값) I.축소(중앙값)");
		inKey = _getch();
		switch (inKey) {
		case 'a':case 'A':zoomOut(); break;
		case 'b':case 'B':zoomIn(); break;
		case 'c':case 'C':zoomIn2(); break;
		case 'd':case 'D':rotate();; break;
		case 'e':case 'E':rotate2();; break;
		case 'f':case 'F':moveImage();; break;
		case 'g':case 'G':lrudImage();; break;
		case 'h':case 'H':zoomOut2(); break;
		case 'i':case 'I':zoomOut3(); break;
		case '9':break;
		}
	}
}
//화소영역 처리
void printMenu4() {
	char inKey = 0;
	while (inKey != '9') {
		system("cls");
		puts("\n ## GrayScale Image Processing (Beta 4) ##");
		puts("9. 뒤로");
		puts("A.엠보싱 B.블러링 C.샤프닝 D.수직엣지 E.수평엣지 F.유사연산자엣지 G.차연산자엣지");
		puts("H.로버츠엣지 I.프리윗엣지 K.소벨엣지");
		puts("J.라플라시안1 L.라플라시안2 M.라플라시안3 N.라플라시안4");
		puts("O.도그1 P.도그2");
		inKey = _getch();
		switch (inKey) {
		case 'a':case 'A':emboss(); break;
		case 'b':case 'B':blr(); break;
		case 'c':case 'C':sharp(); break;
		case 'd':case 'D':edge1(); break;
		case 'e':case 'E':edge2(); break;
		case 'f':case 'F':edge3(); break;
		case 'g':case 'G':edge4(); break;
		case 'h':case 'H':edge5(); break;
		case 'i':case 'I':edge6(); break;
		case 'k':case 'K':edge7(); break;
		case 'j':case 'J':edge8(); break;
		case 'l':case 'L':edge9(); break;
		case 'm':case 'M':edge10(); break;
		case 'n':case 'N':edge11(); break;
		case 'o':case 'O':dog1(); break;
		case 'p':case 'P':dog2(); break;
		case '9':break;
		}
	}
}

void printImage() {

	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			int px = outImage[i][k];
			SetPixel(hdc, k + 50, i + 250, RGB(px, px, px));
		}
	}
}

//// 파일 읽어오는 부분입니다
//// raw 파일이라 정사각형이므로 파일 크기로 가로세로폭 파악하구 그걸로 메모리 크기 정합니다다


void loadImage() {
	char fullName[200] = "D:/RAW/Etc_Raw(squre)/";
	char tmpName[50];
	printf("파일명-->");
	scanf("%s", tmpName);
	strcat(fullName, tmpName);
	strcat(fullName, ".raw");
	strcpy(fileName, fullName);

	// 이미지의 폭과 높이를 결정
	rfp = fopen(fileName, "rb");
	fseek(rfp, 0L, SEEK_END); // 파일의 끝으로 이동
	long long fsize = ftell(rfp); // 위치가 끝이면 그게 파일 크기
	fclose(rfp);

	freeInputMemory();

	// 높이, 폭 구하기
	inH = inW = (int)sqrt(fsize);

	// 메모리 할당
	mallocInputMemory();

	// 파일 --> 메모리
	rfp = fopen(fileName, "rb");
	for (int i = 0; i < inH; i++)
		fread(inImage[i], sizeof(unsigned char), inW, rfp);
	fclose(rfp);

	equalImage();
}

//입력 파일 있는지 확인하는 함수

void imageLog() {
	if (inImage == NULL) {
		printf("파일 없음\n");
		return;
	}
}

// 저장하는 함수입니다. 파일이름 받아서 원래 위치에 저장해요요

void saveImage() {
	if (outImage == NULL)
		return;
	char fullName[200] = "D:/RAW/Etc_Raw(squre)/";
	char tmpName[50];
	printf("파일명-->"); // out01, out02......
	scanf("%s", tmpName);
	strcat(fullName, tmpName);
	strcat(fullName, ".raw");
	strcpy(fileName, fullName);

	wfp = fopen(fileName, "wb");

	// 메모리 --> 파일 (한행씩)
	for (int i = 0; i < outH; i++)
		fwrite(outImage[i], sizeof(unsigned char), outW, wfp);
	fclose(wfp);
	// MessageBox(hwnd, L"저장 완료", L"저장 창", NULL);
	printf("저장 완료");
}

// 정수 입력 받는 함수입니다.

int getIntValue() {
	int retValue;
	printf("정수값-->"); scanf("%d", &retValue);
	return retValue;
}


void freeInputMemory() {
	if (inImage == NULL)
		return;
	else
		for (int i = 0; i < inH; i++)
			free(inImage[i]);
	free(inImage);
	inImage = NULL;
}

void mallocInputMemory() {
	inImage = (unsigned char**)malloc(sizeof(unsigned char*) * inH);
	for (int i = 0; i < inH; i++)
		inImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * inW);
}

void freeOutputMemory() {
	if (outImage == NULL)
		return;
	else
		for (int i = 0; i < outH; i++)
			free(outImage[i]);
	free(outImage);
	outImage = NULL;
}

void mallocOutputMemory() {
	outImage = (unsigned char**)malloc(sizeof(unsigned char*) * outH);
	for (int i = 0; i < outH; i++)
		outImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * outW);

}


//더블형 동적 메모리 할당과 프리
double** mallocDoubleMemory(int h, int w) {
	double** retMemory;
	retMemory = (double**)malloc(sizeof(double*) * h);
	for (int i = 0; i < h; i++)
		retMemory[i] = (double*)malloc(sizeof(double) * w);
	return retMemory;
}

void freeDoubleMemory(double** memory, int h) {
	if (memory == NULL)
		return;
	for (int i = 0; i < h; i++)
		free(memory[i]);
	free(memory);
	memory = NULL;
}
//  영상처리 함수

//화소점 처리

void equalImage() { // 동일영상 알고리즘
	imageLog();									//입력 이미지 있는지 확인
	freeOutputMemory();
	outH = inH;								    //출력 이미지의 크기를 결정-->알고리즘에 의존
	outW = inW;
	mallocOutputMemory();

	for (int i = 0; i < inH; i++) {             // 입력 배열 --> 출력 배열
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = inImage[i][k];
		}
	}
	printImage();
}

void addImage() { // 더하기 알고리즘
	imageLog();
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();

	int val = getIntValue();
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (inImage[i][k] + val < 255)
				outImage[i][k] = inImage[i][k] + val;
			else
				outImage[i][k] = 255;
		}
	}
	printImage();
}

void subImage() { // 빼기 알고리즘
	imageLog();
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();

	int val = getIntValue();
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (inImage[i][k] - val > 0)
				outImage[i][k] = inImage[i][k] - val;
			else
				outImage[i][k] = 0;
		}
	}
	printImage();
}

void reverseImage() { // 반전 알고리즘
	imageLog();
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = 255 - inImage[i][k];
		}
	}
	printImage();
}

void bwImage() { // 흑백 알고리즘
	imageLog();
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (inImage[i][k] > 127)
				outImage[i][k] = 255;
			else
				outImage[i][k] = 0;
		}
	}
	printImage();
}

void bwImage2() { // 흑백 알고리즘
	imageLog();
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();
	int hap = 0;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			hap += inImage[i][k];
		}
	}
	hap /= inH * inW;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (inImage[i][k] > hap)
				outImage[i][k] = 255;
			else
				outImage[i][k] = 0;
		}
	}
	printImage();
}

void bwImage3() {
	imageLog();
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();

	int count[256];
	int sum = 0; int half = 0;

	for (int i = 0; i < 256; i++)
		count[i] = 0;

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			count[inImage[i][k]] += 1;
		}
	}
	for (int i = 0; i < 256; i++) {
		sum += count[i];
		if (sum > inH * inW / 2) {
			half = i;
			break;
		}
	}
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (inImage[i][k] < half)
				outImage[i][k] = 0;
			else
				outImage[i][k] = 255;
		}
	}
	printImage();
}

void gamma() {
	imageLog();
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();

	float val;
	while (true) {

		printf("감마 값 입력:");
		scanf("%f", &val);
		if (val <= 0) {
			printf("오류");
		}
		else
			break;
	}

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			float tmp = pow(inImage[i][k], 1 / val);

			if (tmp > 255)
				outImage[i][k] = 255;
			else if (tmp < 0)
				outImage[i][k] = 0;
			else
				outImage[i][k] = tmp;
		}
	}
	printImage();
}

void posterize() {
	imageLog();
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();

	int level, border, interval;

	printf("2~256 사이의 값 입력:");
	scanf("%d", &level);
	if (level < 2 && level < 256) {
		printf("오류\n");
		return;
	}
	border = 256 / level;
	interval = 256 / (level - 1);

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			int tmp = (inImage[i][k] / border) * interval;

			if (tmp > 255)
				outImage[i][k] = 255;
			else if (tmp < 0)
				outImage[i][k] = 0;
			else
				outImage[i][k] = tmp;
		}
	}
	printImage();
}

void highLight() {
	imageLog();
	freeOutputMemory();
	outH = (int)inH;
	outW = (int)inW;
	mallocOutputMemory();

	int start, end;

	printf("시작");
	start = getIntValue();
	printf("종료");
	end = getIntValue();

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (inImage[i][k] >= start && inImage[i][k] <= end)
				outImage[i][k] = 255;
			else
				outImage[i][k] = inImage[i][k];

		}
		printImage();
	}
}

void histoImage() {

	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();

	// new=(old-low)/(high-low)*255.0
	int high = inImage[0][0], low = inImage[0][0];
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (inImage[i][k] < low)
				low = inImage[i][k];
			if (inImage[i][k] > high)
				high = inImage[i][k];
		}
	}


	int old, new;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			old = inImage[i][k];
			new = (int)((double)(old - low) / (high - low) * 255.0);
			if (new > 255)
				new = 255;
			if (new < 0)
				new = 0;
			outImage[i][k] = new;
		}
	}
	printImage();
}

void endIn() {

	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();
	// new=(old-low)/(high-low)*255.0
	int high = inImage[0][0], low = inImage[0][0];
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (inImage[i][k] < low)
				low = inImage[i][k];
			if (inImage[i][k] > high)
				high = inImage[i][k];
		}
	}

	high -= 50;
	low += 50;

	int old, new;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			old = inImage[i][k];
			new = (int)((double)(old - low) / (high - low) * 255.0);
			if (new > 255)
				new = 255;
			if (new < 0)
				new = 0;
			outImage[i][k] = new;
		}
	}
	printImage();
}

void histoEqual() {

	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();
	//1단계 빈도수 세기=히스토그램
	int histo[256] = { 0, };
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			histo[inImage[i][k]]++;

	//2단계 누적 히스토그램 생성
	int sumHisto[256] = { 0, };
	sumHisto[0] = histo[0];
	for (int i = 1; i < 256; i++) {
		sumHisto[i] = sumHisto[i - 1] + histo[i];
	}
	//3단계 정규화된 히스토그램 생성 normalHisto=sumHisto*(1.0/(inH*inW)*255.0)
	double normalHisto[256] = { 1.0, };
	for (int i = 0; i < 256; i++) {
		normalHisto[i] = sumHisto[i] * (1.0 / (inH * inW) * 255.0);
	}

	//4단계 inImage를 정규화된 값으로 치환
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = (unsigned char)normalHisto[inImage[i][k]];
		}
	}
	printImage();
}

//기하적 처리

void zoomOut() {
	imageLog();
	printf("분모는 :");
	int scale = getIntValue();
	if (scale < 1)
		return;
	freeOutputMemory();
	outH = (int)inH / scale;
	outW = (int)inW / scale;
	mallocOutputMemory();

	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			outImage[i][k] = inImage[i * scale][k * scale];
		}
	}
	printImage();
}

void zoomOut2() { //축소(평균값)
	imageLog();
	printf("분모는 :");
	int scale = getIntValue();
	freeOutputMemory();
	outH = (int)inH / scale;
	outW = (int)inW / scale;
	mallocOutputMemory();
	
	//합연산을 해야하므로 일단 0으로 초기화
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			outImage[i][k] = 0;
		}
	}
	//한점에 원본의 scale제곱으로 평균낸값을 넣기
	
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			for(int m=0;m<scale;m++)
				for(int n=0;n<scale;n++)
			        outImage[i][k] +=inImage[i*scale+m][k*scale+n];
		}
	}
	
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			outImage[i][k] /=(scale*scale);
		}
	}



	printImage();
}

void zoomOut3() {  //축소 중앙값
	imageLog();
	printf("분모는 :");
	int scale = getIntValue();
	freeOutputMemory();
	outH = (int)inH / scale;
	outW = (int)inW / scale;
	mallocOutputMemory();
	int count[256];
	int sum;

	if (scale % 2 == 1) {
		for (int i = 0; i < outH; i++) {
			for (int k = 0; k < outW; k++) {
				//값 초기화
				sum = 0;
				for (int m = 0; m < 256; m++)
					count[m] = 0;
				//값 정렬
				for (int m = 0; m < scale; m++)
					for (int n = 0; n < scale; n++)
						count[inImage[(scale * i) + m][(scale * k) + n]] += 1;

				//합산해서 중앙값 찾기
				for (int m = 0; m < 256; m++) {
					if (sum > (scale * scale) / 2) {
						outImage[i][k] = m;
						break;
					}
					else
						sum += count[m];
				}

			}
		}
	}
	else
		for (int i = 0; i < outH; i++) {
			for (int k = 0; k < outW; k++) {
				//값 초기화
				sum = 0;
				for (int m = 0; m < 256; m++)
					count[m] = 0;
				//값 정렬
				for (int m = 0; m < scale; m++)
					for (int n = 0; n < scale; n++)
						count[inImage[(scale * i) + m][(scale * k) + n]] += 1;

				//합산해서 중앙값 찾기
				for (int m = 0; m < 256; m++) {
					if (sum >= (scale * scale) / 2) {
						outImage[i][k] = m;
						break;
					}
					else
						sum += count[m];
				}

			}
		}
	printImage();
}

void zoomIn() {
	imageLog();
	int scale = getIntValue();
	freeOutputMemory();
	outH = (int)inH * scale;
	outW = (int)inW * scale;
	mallocOutputMemory();


	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[(int)i * scale][(int)k * scale] = inImage[i][k];
		}
	}
	printImage();
}

void zoomIn2() {
	imageLog();
	int scale = getIntValue();
	freeOutputMemory();
	outH = (int)inH * scale;
	outW = (int)inW * scale;
	mallocOutputMemory();

	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			outImage[i][k] = inImage[i / scale][k / scale];
		}
	}
	printImage();
}

void rotate() { // 회전 기본 알고리즘
	imageLog();
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();

	int degree = getIntValue();                      
	double radian = degree * 3.141592 / 180.0;	     

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			int xs = i;               //xd=cos*xs-sin*ys
			int ys = k;               //yd=sin*xs+cos*ys
			int xd = (int)(cos(radian) * xs - sin(radian) * ys);
			int yd = (int)(sin(radian) * xs + cos(radian) * ys);

			if ((0 <= xd && xd < outH) && (0 <= yd && yd < outW))
				outImage[xd][yd] = inImage[i][k];
		}
	}
	printImage();
}

void rotate2() { // 회전 알고리즘 + 중앙/백워딩
	imageLog();
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();

	int degree = getIntValue();
	double radian = -degree * 3.141592 / 180.0;
	// xd = cos*xs - sin*ys
	// yd = sin*xs + cos*ys

	int cx = inH / 2;
	int cy = inW / 2;
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			int xd = i;
			int yd = k;

			int xs = (int)(cos(radian) * (xd - cx) + sin(radian) * (yd - cy));
			int ys = (int)(-sin(radian) * (xd - cx) + cos(radian) * (yd - cy));
			xs += cx;
			ys += cy;

			if ((0 <= xs && xs < outH) && (0 <= ys && ys < outW))
				outImage[xd][yd] = inImage[xs][ys];
		}
	}
	printImage();
}

void moveImage() {
	imageLog();
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();
	printf("가로로 이동할 거리:");
	int val2 = getIntValue();
	printf("세로로 이동할 거리:");
	int val1 = getIntValue();

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (((0 <= (i - val1)) && ((i - val1) < inH)) && ((0 <= (k + val2)) && ((k + val2) < inW)))
				outImage[i - val1][k + val2] = inImage[i][k];
		}
	}
	printImage();
}

void lrudImage() {   //반전
	imageLog();
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();
	puts("A.가로 반전 B.세로 반전. C.중심점 대칭 반전:");
	char inKey = 0;
	inKey = _getch();
	switch (inKey) {
	case 'a':case 'A': {
		for (int i = 0; i < inH; i++) {
			for (int k = 0; k < inW; k++) {
				outImage[i][k] = inImage[i][inW - k - 1];
			}
		}
	} break;
	case 'b':case 'B': {
		for (int i = 0; i < inH; i++) {
			for (int k = 0; k < inW; k++) {
				outImage[i][k] = inImage[inH - i - 1][k];
			}
		}
	} break;
	case 'c':case 'C': {
		for (int i = 0; i < inH; i++) {
			for (int k = 0; k < inW; k++) {
				outImage[i][k] = inImage[inH - i - 1][inW - k - 1];
			}
		}
	}break;
	}
	printImage();
}


//화소 영역처리

void emboss() {
	imageLog();
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();
	//변수 선언
	double** mask;
	int scale;
	//마스크의 크기:scale*scale
	puts("마스크 한 변의 길이:");
	scanf("%d", &scale);
	if (scale < 1) {
		printf("오류");
		return;
	}
	else if (scale % 2 == 0) {
		printf("오류");
		return;
	}

	int sc = scale - 1;
	//마스크 동적할당
	mask = (double**)malloc(sizeof(double*) * scale);
	for (int i = 0; i < scale; i++)
		mask[i] = (double*)malloc(sizeof(double) * scale);
	//값 0으로 초기화
	for (int i = 0; i < scale; i++) {
		for (int k = 0; k < scale; k++) {
			mask[i][k] = 0.;
		}
	}

	//엠보싱 조건
	mask[0][0] = -1.;
	mask[sc][sc] = 1;

	//임시 메모리 할당
	double** tmpInImage = mallocDoubleMemory(inH + sc, inW + sc);
	double** tmpOutImage = mallocDoubleMemory(inH, inW);

	//원본 이미지와 크기가 같은영역은 원본으로 그 외의 부분은 127
	for (int i = 0; i < inH + sc; i++) {
		for (int k = 0; k < inW + sc; k++) {
			tmpInImage[i][k] = 0;
		}
	}

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			tmpInImage[i + sc / 2][k + sc / 2] = inImage[i][k];
		}
	}

	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < outH; k++) {
			S = 0.0;

			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S + 127;
		}
	}

	// 임시 출력 영상--> 출력 영상. 
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + sc);
	freeDoubleMemory(tmpOutImage, outH);
	for (int i = 0; i < scale; i++)
		free(mask[i]);
	free(mask);

	printImage();
}

void blr() {
	imageLog();
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();
	//변수 선언
	double** mask;
	int scale;
	//마스크의 크기:scale*scale
	puts("마스크 한 변의 길이:");
	scanf("%d", &scale);
	if (scale < 1) {
		printf("오류");
		return;
	}
	else if (scale % 2 == 0) {
		printf("오류");
		return;
	}

	int sc = scale - 1;
	//마스크 동적할당
	mask = (double**)malloc(sizeof(double*) * scale);
	for (int i = 0; i < scale; i++)
		mask[i] = (double*)malloc(sizeof(double) * scale);
	//값 0으로 초기화
	for (int i = 0; i < scale; i++) {
		for (int k = 0; k < scale; k++) {
			mask[i][k] = 0.;
		}
	}

	//블러링 조건
	for (int i = 0; i < scale; i++)
		for (int k = 0; k < scale; k++)
			mask[i][k] = (double)1 / (scale * scale);


	//임시 메모리 할당
	double** tmpInImage = mallocDoubleMemory(inH + sc, inW + sc);
	double** tmpOutImage = mallocDoubleMemory(inH, inW);

	//원본 이미지와 크기가 같은영역은 원본으로 그 외의 부분은 127
	for (int i = 0; i < inH + sc; i++) {
		for (int k = 0; k < inW + sc; k++) {
			tmpInImage[i][k] = 0;
		}
	}

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			tmpInImage[i + sc / 2][k + sc / 2] = inImage[i][k];
		}
	}

	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < outH; k++) {
			S = 0.0;

			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}

	// 임시 출력 영상--> 출력 영상. 
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + sc);
	freeDoubleMemory(tmpOutImage, outH);
	for (int i = 0; i < scale; i++)
		free(mask[i]);
	free(mask);

	printImage();
}

void sharp() {
	imageLog();
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();

	double** mask;
	int scale;

	puts("마스크 한 변의 길이:");
	scanf("%d", &scale);
	if (scale < 1) {
		printf("오류");
		return;
	}
	else if (scale % 2 == 0) {
		printf("오류");
		return;
	}

	int sc = scale - 1;
	//마스크 동적할당
	mask = (double**)malloc(sizeof(double*) * scale);
	for (int i = 0; i < scale; i++)
		mask[i] = (double*)malloc(sizeof(double) * scale);
	//값 -1로 초기화
	for (int i = 0; i < scale; i++) {
		for (int k = 0; k < scale; k++) {
			mask[i][k] = -1;
		}
	}

	//샤프닝 조건 중앙의 값을 scale*scale로 설정 why: 총 밝기가 1이 되어야하니까
	mask[(sc / 2) + 1][(sc / 2) + 1] = scale * scale;


	//임시 메모리 할당
	double** tmpInImage = mallocDoubleMemory(inH + sc, inW + sc);
	double** tmpOutImage = mallocDoubleMemory(inH, inW);

	//원본 이미지와 크기가 같은영역은 원본으로 그 외의 부분은 127
	for (int i = 0; i < inH + sc; i++) {
		for (int k = 0; k < inW + sc; k++) {
			tmpInImage[i][k] = 0;
		}
	}

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			tmpInImage[i + sc / 2][k + sc / 2] = inImage[i][k];
		}
	}

	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < outH; k++) {
			S = 0.0;

			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}

	// 임시 출력 영상--> 출력 영상. 
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + sc);
	freeDoubleMemory(tmpOutImage, outH);
	for (int i = 0; i < scale; i++)
		free(mask[i]);
	free(mask);

	printImage();
}

void edge1() {     //수직 엣지 검출 마스크
	imageLog();
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();

	double mask[3][3] = { {0,-1,0}, // 엣지 마스크
						  {0,1,0},
						  {0,0,0} };


	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}

	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();
}

void edge2() {     //수평 엣지 검출 마스크
	imageLog();
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();

	double mask[3][3] = { {0,0,0}, // 엣지 마스크
						 {-1,1,0},
						 {0,0,0} };

	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}

	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();
}

void edge3() {     // 유사연산자
	imageLog();
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();

	for (int i = 1; i < inH - 1; i++) {
		for (int k = 1; k < inW - 1; k++) {
			int max = 0;
			for (int m = -1; m < 2; m++)
				for (int n = -1; n < 2; n++)
					if ((inImage[i][k] - inImage[i + m][k + n]) >= max)
						max = inImage[i][k] - inImage[i + m][k + n];

			outImage[i][k] = max;
		}
	}

	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (outImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (outImage[i][k] > 255.0)
				outImage[i][k] = 255;
		}
	}
	printImage();
}

void edge4() {     // 차연산자
	imageLog();
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();

	for (int i = 1; i < inH - 1; i++) {
		for (int k = 1; k < inW - 1; k++) {
			int max = 0;
			if ((inImage[i - 1][k - 1] - inImage[i + 1][k + 1]) >= max)
				max = (inImage[i - 1][k - 1] - inImage[i + 1][k + 1]);
			if ((inImage[i - 1][k] - inImage[i + 1][k]) >= max)
				max = (inImage[i - 1][k] - inImage[i + 1][k]);
			if ((inImage[i - 1][k + 1] - inImage[i + 1][k - 1]) >= max)
				max = (inImage[i - 1][k + 1] - inImage[i + 1][k - 1]);
			if ((inImage[i][k - 1] - inImage[i][k + 1]) >= max)
				max = (inImage[i][k - 1] - inImage[i][k + 1]);

			outImage[i][k] = max;
		}
	}

	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (outImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (outImage[i][k] > 255.0)
				outImage[i][k] = 255;
		}
	}
	printImage();
}

void edge5() {     //로버츠 엣지
	imageLog();
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();

	double mask[3][3] = {{-1, 0,-1}, // 엣지 마스크
						 { 0, 2, 0},
						 { 0, 0, 0} };

	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			S = 0.0;

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}

	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();
}

void edge6() {     //프리윗 엣지
	imageLog();
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();

	double mask[3][3] = {{ 0,-1,-2}, // 엣지 마스크
						 { 1, 0,-1},
						 { 2, 1, 0} };

	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			S = 0.0;

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}

	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();
}

void edge7() {     //소벨 엣지
	imageLog();
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();

	double mask[3][3] = {{ 0,-2,-2}, // 엣지 마스크
						 { 2, 0,-2},
						 { 2, 2, 0} };

	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			S = 0.0;

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}

	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();
}

void edge8() {     //라플라시안 엣지1
	imageLog();
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();

	double mask[3][3] = {{ 0,-1, 0}, // 엣지 마스크
						 {-1, 4,-1},
						 { 0,-1, 0} };

	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			S = 0.0;

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}

	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();
}

void edge9() {     //라플라시안 엣지 2
	imageLog();
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();

	double mask[3][3] = {{ 1, 1, 1}, // 엣지 마스크
						 { 1,-8, 1},
						 { 1, 1, 1} };

	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			S = 0.0;

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}

	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();
}

void edge10() {     //라플라시안 엣지3
	imageLog();
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();

	double mask[3][3] = {{-1,-1,-1}, // 엣지 마스크
						 {-1, 8,-1},
						 {-1,-1,-1} };

	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			S = 0.0;

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}

	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();
}

void edge11() {     //라플라시안 엣지4
	imageLog();
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();

	double mask[5][5] = {{ 0, 0,-1, 0, 0}, // 엣지 마스크
						 { 0,-1,-2,-1, 0},
						 {-1,-2,16,-2,-1},
						 { 0,-1,-2,-1, 0},
						 { 0, 0,-1, 0, 0} };
	double** tmpInImage = mallocDoubleMemory(inH + 4, inW + 4);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	for (int i = 0; i < inH + 4; i++)
		for (int k = 0; k < inW + 4; k++)
			tmpInImage[i][k] = 127;

	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 2][k + 2] = inImage[i][k];

	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			S = 0.0;

			for (int m = 0; m < 5; m++)
				for (int n = 0; n < 5; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}

	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 4);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();
}

void dog1() {     //도그1
	imageLog();
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();

	double mask[7][7] = {{ 0, 0,-1,-1,-1, 0, 0}, // 엣지 마스크
						 { 0,-2,-3,-3,-3,-2, 0},
						 {-1,-3, 5, 5, 5,-3,-1},
						 {-1,-3, 5,16, 5,-3,-1},
						 {-1,-3, 5, 5, 5,-3,-1},
						 { 0,-2,-3,-3,-3,-2, 0},
						 { 0, 0,-1,-1,-1, 0, 0} };

	double** tmpInImage = mallocDoubleMemory(inH + 6, inW + 6);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	for (int i = 0; i < inH + 6; i++)
		for (int k = 0; k < inW + 6; k++)
			tmpInImage[i][k] = 127;

	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 3][k + 3] = inImage[i][k];

	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			S = 0.0;

			for (int m = 0; m < 7; m++)
				for (int n = 0; n < 7; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}

	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 6);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();
}

void dog2() {     //도그1
	imageLog();
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();

	double mask[9][9] = {{ 0, 0, 0,-1,-1,-1, 0, 0, 0}, // 엣지 마스크
						 { 0,-2,-3,-3,-3,-3,-3,-2, 0},
						 { 0,-3,-2,-1,-1,-1,-2,-3, 0},
						 {-1,-3,-1, 9, 9, 9,-1,-3,-1},
						 {-1,-3,-1, 9, 19, 9,-1,-3,-1},
						 {-1,-3,-1, 9, 9, 9,-1,-3,-1},
						 { 0,-3,-2,-1,-1,-1,-2,-3, 0},
						 { 0,-2,-3,-3,-3,-3,-3,-2, 0},
						 { 0, 0, 0,-1,-1,-1, 0, 0, 0} };

	double** tmpInImage = mallocDoubleMemory(inH + 8, inW + 8);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	for (int i = 0; i < inH + 8; i++)
		for (int k = 0; k < inW + 8; k++)
			tmpInImage[i][k] = 127;

	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 4][k + 4] = inImage[i][k];

	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			S = 0.0;

			for (int m = 0; m < 9; m++)
				for (int n = 0; n < 9; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}

	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 8);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();
}
