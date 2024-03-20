#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <Windows.h> 
#include <math.h>

// ���� ������
HWND hwnd; // ���� ȭ��(�ܺ�, ������)
HDC hdc; // ���� ȭ�� (����, ����)
FILE* rfp, * wfp;
char fileName[200];
int inH, inW, outH, outW;

// �޸� Ȯ��
unsigned char** inImage = NULL, ** outImage = NULL;

// �Լ� �����
void loadImage(); int getIntValue(); void printImage(); void printMenu(); void printMenu2(); void printMenu3(); void printMenu4();
void saveImage(); void freeInputMemory(); void freeOutputMemory();
void mallocInputMemory(); void mallocOutputMemory();
double** mallocDoubleMemory(int, int); void freeDoubleMemory(double**, int);
void imageLog();
//ȭ����ó��
void equalImage(); void addImage(); void subImage(); void reverseImage();
void bwImage(); void bwImage2(); void bwImage3(); void gamma(); void highLight(); void posterize();
void histoImage(); void endIn(); void histoEqual();
//ȭ�� ����ó��
void emboss(); void blr(); void sharp(); void edge1(); void edge2(); void edge3(); void edge4(); void edge5();
void edge6(); void edge7(); void edge8(); void edge9(); void edge10(); void edge11(); void dog1(); void dog2();
//������ó��
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


// �Լ� ���Ǻ�

/// ���� �Լ�
void printMenu() {
	system("cls");
	puts("\n ## GrayScale Image Processing (Beta 4) ##");
	puts("0.����  1.����  9. ����");
	puts("A. ȭ���� ó�� B. ������ ó�� C.ȭ�� ���� ó��");
}
// ȭ���� ó��
void printMenu2() {
	char inKey = 0;
	while (inKey != '9') {
		system("cls");
		puts("\n ## GrayScale Image Processing (Beta 4) ##");
		puts("9. �ڷ�");
		puts("A.���� B.��� C.��Ӱ� D.����");
		puts("E.��� F.���(��հ�) G.���(�߾Ӱ�)");
		puts("H.���� I.�����Ͷ����� J.���̶���Ʈ");
		puts("K.������1 L.������2 M.��Ȱȭ");
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
// ������ ó��
void printMenu3() {
	char inKey = 0;
	while (inKey != '9') {
		system("cls");
		puts("\n ## GrayScale Image Processing (Beta 4) ##");
		puts("9. �ڷ�");
		puts("A.��� B.Ȯ�� C.Ȯ��2 D.ȸ�� E.ȸ��2");
		puts("F.�̵� G.���� H.���(��հ�) I.���(�߾Ӱ�)");
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
//ȭ�ҿ��� ó��
void printMenu4() {
	char inKey = 0;
	while (inKey != '9') {
		system("cls");
		puts("\n ## GrayScale Image Processing (Beta 4) ##");
		puts("9. �ڷ�");
		puts("A.������ B.���� C.������ D.�������� E.������ F.���翬���ڿ��� G.�������ڿ���");
		puts("H.�ι������� I.���������� K.�Һ�����");
		puts("J.���ö�þ�1 L.���ö�þ�2 M.���ö�þ�3 N.���ö�þ�4");
		puts("O.����1 P.����2");
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

void loadImage() {
	char fullName[200] = "D:/RAW/Etc_Raw(squre)/";
	char tmpName[50];
	printf("���ϸ�-->");
	scanf("%s", tmpName);
	strcat(fullName, tmpName);
	strcat(fullName, ".raw");
	strcpy(fileName, fullName);

	// �̹����� ���� ���̸� ����
	rfp = fopen(fileName, "rb");
	fseek(rfp, 0L, SEEK_END); // ������ ������ �̵�
	long long fsize = ftell(rfp); // ��ġ�� ���̸� �װ� ���� ũ��
	fclose(rfp);

	freeInputMemory();

	// ����, �� ���ϱ�
	inH = inW = (int)sqrt(fsize);

	// �޸� �Ҵ�
	mallocInputMemory();

	// ���� --> �޸�
	rfp = fopen(fileName, "rb");
	for (int i = 0; i < inH; i++)
		fread(inImage[i], sizeof(unsigned char), inW, rfp);
	fclose(rfp);

	equalImage();
}

void imageLog() {
	if (inImage == NULL) {
		printf("���� ����\n");
		return;
	}
}

void saveImage() {
	if (outImage == NULL)
		return;
	char fullName[200] = "D:/RAW/Etc_Raw(squre)/";
	char tmpName[50];
	printf("���ϸ�-->"); // out01, out02......
	scanf("%s", tmpName);
	strcat(fullName, tmpName);
	strcat(fullName, ".raw");
	strcpy(fileName, fullName);

	wfp = fopen(fileName, "wb");

	// �޸� --> ���� (���྿)
	for (int i = 0; i < outH; i++)
		fwrite(outImage[i], sizeof(unsigned char), outW, wfp);
	fclose(wfp);
	// MessageBox(hwnd, L"���� �Ϸ�", L"���� â", NULL);
	printf("���� �Ϸ�");
}

int getIntValue() {
	int retValue;
	printf("������-->"); scanf("%d", &retValue);
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


//������ ���� �޸� �Ҵ�� ����
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
//  ����ó�� �Լ�

//ȭ���� ó��

void equalImage() { // ���Ͽ��� �˰���
	imageLog();									//�Է� �̹��� �ִ��� Ȯ��
	freeOutputMemory();
	outH = inH;								    //��� �̹����� ũ�⸦ ����-->�˰��� ����
	outW = inW;
	mallocOutputMemory();

	for (int i = 0; i < inH; i++) {             // �Է� �迭 --> ��� �迭
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = inImage[i][k];
		}
	}
	printImage();
}

void addImage() { // ���ϱ� �˰���
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

void subImage() { // ���� �˰���
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

void reverseImage() { // ���� �˰���
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

void bwImage() { // ��� �˰���
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

void bwImage2() { // ��� �˰���
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

		printf("���� �� �Է�:");
		scanf("%f", &val);
		if (val <= 0) {
			printf("����");
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

	printf("2~256 ������ �� �Է�:");
	scanf("%d", &level);
	if (level < 2 && level < 256) {
		printf("����\n");
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

	printf("����");
	start = getIntValue();
	printf("����");
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
	//1�ܰ� �󵵼� ����=������׷�
	int histo[256] = { 0, };
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			histo[inImage[i][k]]++;

	//2�ܰ� ���� ������׷� ����
	int sumHisto[256] = { 0, };
	sumHisto[0] = histo[0];
	for (int i = 1; i < 256; i++) {
		sumHisto[i] = sumHisto[i - 1] + histo[i];
	}
	//3�ܰ� ����ȭ�� ������׷� ���� normalHisto=sumHisto*(1.0/(inH*inW)*255.0)
	double normalHisto[256] = { 1.0, };
	for (int i = 0; i < 256; i++) {
		normalHisto[i] = sumHisto[i] * (1.0 / (inH * inW) * 255.0);
	}

	//4�ܰ� inImage�� ����ȭ�� ������ ġȯ
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = (unsigned char)normalHisto[inImage[i][k]];
		}
	}
	printImage();
}

//������ ó��

void zoomOut() {
	imageLog();
	printf("�и�� :");
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

void zoomOut2() { //���(��հ�)
	imageLog();
	printf("�и�� :");
	int scale = getIntValue();
	freeOutputMemory();
	outH = (int)inH / scale;
	outW = (int)inW / scale;
	mallocOutputMemory();
	
	//�տ����� �ؾ��ϹǷ� �ϴ� 0���� �ʱ�ȭ
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			outImage[i][k] = 0;
		}
	}
	//������ ������ scale�������� ��ճ����� �ֱ�
	
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

void zoomOut3() {  //��� �߾Ӱ�
	imageLog();
	printf("�и�� :");
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
				//�� �ʱ�ȭ
				sum = 0;
				for (int m = 0; m < 256; m++)
					count[m] = 0;
				//�� ����
				for (int m = 0; m < scale; m++)
					for (int n = 0; n < scale; n++)
						count[inImage[(scale * i) + m][(scale * k) + n]] += 1;

				//�ջ��ؼ� �߾Ӱ� ã��
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
				//�� �ʱ�ȭ
				sum = 0;
				for (int m = 0; m < 256; m++)
					count[m] = 0;
				//�� ����
				for (int m = 0; m < scale; m++)
					for (int n = 0; n < scale; n++)
						count[inImage[(scale * i) + m][(scale * k) + n]] += 1;

				//�ջ��ؼ� �߾Ӱ� ã��
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

void rotate() { // ȸ�� �⺻ �˰���
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

void rotate2() { // ȸ�� �˰��� + �߾�/�����
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
	printf("���η� �̵��� �Ÿ�:");
	int val2 = getIntValue();
	printf("���η� �̵��� �Ÿ�:");
	int val1 = getIntValue();

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (((0 <= (i - val1)) && ((i - val1) < inH)) && ((0 <= (k + val2)) && ((k + val2) < inW)))
				outImage[i - val1][k + val2] = inImage[i][k];
		}
	}
	printImage();
}

void lrudImage() {   //����
	imageLog();
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();
	puts("A.���� ���� B.���� ����. C.�߽��� ��Ī ����:");
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


//ȭ�� ����ó��

void emboss() {
	imageLog();
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();
	//���� ����
	double** mask;
	int scale;
	//����ũ�� ũ��:scale*scale
	puts("����ũ �� ���� ����:");
	scanf("%d", &scale);
	if (scale < 1) {
		printf("����");
		return;
	}
	else if (scale % 2 == 0) {
		printf("����");
		return;
	}

	int sc = scale - 1;
	//����ũ �����Ҵ�
	mask = (double**)malloc(sizeof(double*) * scale);
	for (int i = 0; i < scale; i++)
		mask[i] = (double*)malloc(sizeof(double) * scale);
	//�� 0���� �ʱ�ȭ
	for (int i = 0; i < scale; i++) {
		for (int k = 0; k < scale; k++) {
			mask[i][k] = 0.;
		}
	}

	//������ ����
	mask[0][0] = -1.;
	mask[sc][sc] = 1;

	//�ӽ� �޸� �Ҵ�
	double** tmpInImage = mallocDoubleMemory(inH + sc, inW + sc);
	double** tmpOutImage = mallocDoubleMemory(inH, inW);

	//���� �̹����� ũ�Ⱑ ���������� �������� �� ���� �κ��� 127
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

	// �ӽ� ��� ����--> ��� ����. 
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
	//���� ����
	double** mask;
	int scale;
	//����ũ�� ũ��:scale*scale
	puts("����ũ �� ���� ����:");
	scanf("%d", &scale);
	if (scale < 1) {
		printf("����");
		return;
	}
	else if (scale % 2 == 0) {
		printf("����");
		return;
	}

	int sc = scale - 1;
	//����ũ �����Ҵ�
	mask = (double**)malloc(sizeof(double*) * scale);
	for (int i = 0; i < scale; i++)
		mask[i] = (double*)malloc(sizeof(double) * scale);
	//�� 0���� �ʱ�ȭ
	for (int i = 0; i < scale; i++) {
		for (int k = 0; k < scale; k++) {
			mask[i][k] = 0.;
		}
	}

	//���� ����
	for (int i = 0; i < scale; i++)
		for (int k = 0; k < scale; k++)
			mask[i][k] = (double)1 / (scale * scale);


	//�ӽ� �޸� �Ҵ�
	double** tmpInImage = mallocDoubleMemory(inH + sc, inW + sc);
	double** tmpOutImage = mallocDoubleMemory(inH, inW);

	//���� �̹����� ũ�Ⱑ ���������� �������� �� ���� �κ��� 127
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

	// �ӽ� ��� ����--> ��� ����. 
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

	puts("����ũ �� ���� ����:");
	scanf("%d", &scale);
	if (scale < 1) {
		printf("����");
		return;
	}
	else if (scale % 2 == 0) {
		printf("����");
		return;
	}

	int sc = scale - 1;
	//����ũ �����Ҵ�
	mask = (double**)malloc(sizeof(double*) * scale);
	for (int i = 0; i < scale; i++)
		mask[i] = (double*)malloc(sizeof(double) * scale);
	//�� -1�� �ʱ�ȭ
	for (int i = 0; i < scale; i++) {
		for (int k = 0; k < scale; k++) {
			mask[i][k] = -1;
		}
	}

	//������ ���� �߾��� ���� scale*scale�� ���� why: �� ��Ⱑ 1�� �Ǿ���ϴϱ�
	mask[(sc / 2) + 1][(sc / 2) + 1] = scale * scale;


	//�ӽ� �޸� �Ҵ�
	double** tmpInImage = mallocDoubleMemory(inH + sc, inW + sc);
	double** tmpOutImage = mallocDoubleMemory(inH, inW);

	//���� �̹����� ũ�Ⱑ ���������� �������� �� ���� �κ��� 127
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

	// �ӽ� ��� ����--> ��� ����. 
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

void edge1() {     //���� ���� ���� ����ũ
	imageLog();
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();

	double mask[3][3] = { {0,-1,0}, // ���� ����ũ
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
			S = 0.0; // ����ũ 9���� �Է°� 9���� ���� ���ؼ� ���� ��.

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

void edge2() {     //���� ���� ���� ����ũ
	imageLog();
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();

	double mask[3][3] = { {0,0,0}, // ���� ����ũ
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
			S = 0.0; // ����ũ 9���� �Է°� 9���� ���� ���ؼ� ���� ��.

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

void edge3() {     // ���翬����
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

void edge4() {     // ��������
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

void edge5() {     //�ι��� ����
	imageLog();
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();

	double mask[3][3] = {{-1, 0,-1}, // ���� ����ũ
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

void edge6() {     //������ ����
	imageLog();
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();

	double mask[3][3] = {{ 0,-1,-2}, // ���� ����ũ
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

void edge7() {     //�Һ� ����
	imageLog();
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();

	double mask[3][3] = {{ 0,-2,-2}, // ���� ����ũ
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

void edge8() {     //���ö�þ� ����1
	imageLog();
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();

	double mask[3][3] = {{ 0,-1, 0}, // ���� ����ũ
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

void edge9() {     //���ö�þ� ���� 2
	imageLog();
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();

	double mask[3][3] = {{ 1, 1, 1}, // ���� ����ũ
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

void edge10() {     //���ö�þ� ����3
	imageLog();
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();

	double mask[3][3] = {{-1,-1,-1}, // ���� ����ũ
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

void edge11() {     //���ö�þ� ����4
	imageLog();
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();

	double mask[5][5] = {{ 0, 0,-1, 0, 0}, // ���� ����ũ
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

void dog1() {     //����1
	imageLog();
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();

	double mask[7][7] = {{ 0, 0,-1,-1,-1, 0, 0}, // ���� ����ũ
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

void dog2() {     //����1
	imageLog();
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();

	double mask[9][9] = {{ 0, 0, 0,-1,-1,-1, 0, 0, 0}, // ���� ����ũ
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