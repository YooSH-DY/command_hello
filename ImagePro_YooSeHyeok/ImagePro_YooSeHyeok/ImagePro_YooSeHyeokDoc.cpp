
// ImagePro_YooSeHyeokDoc.cpp: CImageProYooSeHyeokDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImagePro_YooSeHyeok.h"
#endif

#include "ImagePro_YooSeHyeokDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageProYooSeHyeokDoc

IMPLEMENT_DYNCREATE(CImageProYooSeHyeokDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageProYooSeHyeokDoc, CDocument)
END_MESSAGE_MAP()


// CImageProYooSeHyeokDoc 생성/소멸

CImageProYooSeHyeokDoc::CImageProYooSeHyeokDoc() noexcept // 이름이 같은 함수는 생성자 맨 처음에 불러와진다.
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
	inputImg = NULL;
	inputImg2 = NULL;
	resultImg = NULL;

	gResultImg = NULL;     // 추가되는 코드 


}

CImageProYooSeHyeokDoc::~CImageProYooSeHyeokDoc() // ~가 붙은건 소멸자
{
}

BOOL CImageProYooSeHyeokDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CImageProYooSeHyeokDoc serialization

void CImageProYooSeHyeokDoc::Serialize(CArchive& ar) //&는 원본을 읽는다.
{
	if (ar.IsStoring() /*== TRUE*/)
	{
		// ar.Write(resultImg, 256 * 256); 수정전
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		/*CFile *fp = ar.GetFile();
		if (fp->GetLength() == 256 * 256) ar.Read(inputImg, 256 * 256);
		else AfxMessageBox("256x256 크기의 파일만 사용가능합니다.");*/
		LoadImageFile(ar);

		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CImageProYooSeHyeokDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CImageProYooSeHyeokDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImageProYooSeHyeokDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CImageProYooSeHyeokDoc 진단

#ifdef _DEBUG
void CImageProYooSeHyeokDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageProYooSeHyeokDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageProYooSeHyeokDoc 명령


void CImageProYooSeHyeokDoc::PixelAdd() //덧셈
{
	int value = 0;
	/*
	for (int x = 0; x < 256; x++)
		for (int y = 0; y < 256; y++) {
			value = inputImg[x][y] + 100;          //원 이미지 + 100
			if (value > 255) resultImg[x][y] = 255;
			else resultImg[x][y] = value;
		} 수정전 */
	for (int y = 0; y < imageHeight; y++)
		for (int x = 0; x < imageWidth * depth; x++) {
			value = inputImg[y][x] + 100;
			if (value > 255) resultImg[y][x] = 255;
			else resultImg[y][x] = value;
		}

	// TODO: 여기에 구현 코드 추가.
}


void CImageProYooSeHyeokDoc::PixelReverse() //역상
{
	// 컬러이미지의 역상 공식 : r`=255-r g`=255-g b`=255-b
	int value = 0;

	/*for (int x = 0; x < 256; x++)
		for (int y = 0; y < 256; y++) {
			value = 255 - inputImg[x][y];          //255 - 원이미지
			/*if (value < 0) resultImg[x][y] = 255;
			else resultImg[x][y] = value; //수정전
		}*/
	for (int y = 0; y < imageHeight; y++)
		for (int x = 0; x < imageWidth * depth; x++) {
			value = 255 -  inputImg[y][x];
			if (value > 255) resultImg[y][x] = 255;
			else resultImg[y][x] = value;
		}

	// TODO: 여기에 구현 코드 추가.
}


void CImageProYooSeHyeokDoc::PixelMinus() //뺄셈
{
	int value = 0;

	/*for (int x = 0; x < 256; x++)
		for (int y = 0; y < 256; y++) {
			value = inputImg[x][y] - 100;          //원 이미지 - 100
			if (value < 0) resultImg[x][y] = 0;
			else resultImg[x][y] = value;
		} 수정전 */
	for (int y = 0; y < imageHeight; y++)
		for (int x = 0; x < imageWidth * depth; x++) {
			value = inputImg[y][x] - 100;
			if (value < 0) resultImg[y][x] = 0;
			else resultImg[y][x] = value;
		}
	// TODO: 여기에 구현 코드 추가.
}


void CImageProYooSeHyeokDoc::PixelMultiple() //곱셈
{
	int value = 0;

	/*for (int x = 0; x < 256; x++)
		for (int y = 0; y < 256; y++) {
			value = inputImg[x][y] * 1.5;          //원 이미지 * 1.5
			if (value > 255) resultImg[x][y] = 255;
			else resultImg[x][y] = value;
		} 수정전 */
	for (int y = 0; y < imageHeight; y++)
		for (int x = 0; x < imageWidth * depth; x++) {
			value = inputImg[y][x] * 1.5;
			if (value > 255) resultImg[y][x] = 255;
			else resultImg[y][x] = value;
		}
	// TODO: 여기에 구현 코드 추가.
}


void CImageProYooSeHyeokDoc::PixelDiv() //나눗셈
{
	int value = 0;

	/*for (int x = 0; x < 256; x++)
		for (int y = 0; y < 256; y++) {
			value = inputImg[x][y] / 1.5;          //원 이미지 / 1.5
			if (value < 0) resultImg[x][y] = 0;
			else resultImg[x][y] = value;
		} 수정전 */
	for (int y = 0; y < imageHeight; y++)
		for (int x = 0; x < imageWidth * depth; x++) {
			value = inputImg[y][x] / 1.5;
			if (value > 255) resultImg[y][x] = 255;
			else resultImg[y][x] = value;
		}
	// TODO: 여기에 구현 코드 추가.
}


void CImageProYooSeHyeokDoc::PixelRe() //이진화
{
	// 컬러의 이진화는 I=(r+g+b)/3
	for (int x = 0; x < 256; x++)
		for (int y = 0; y < 256; y++) {
			if (inputImg[x][y] > 128) resultImg[x][y] = 255;
			else resultImg[x][y] = 0;
		}
	// TODO: 여기에 구현 코드 추가.
}


void CImageProYooSeHyeokDoc::PixelHistoEq() //픽셀히스토그램
{
	
	int x, y, i, k;
	int acc_hist = 0;      // 히스토그램의 합을 누적하는 변수 
	float N = 256 * 256;   // 영상의 전체 픽셀 수 
	int hist[256], sum[256];

	for (k = 0; k < 256; k++) hist[k] = 0;

	// 명암값의 빈도수 조사 
	for (y = 0; y < 256; y++)
		for (x = 0; x < 256; x++) {
			k = inputImg[y][x];
			hist[k] = hist[k] + 1;
		}
	// 누적된 히스토그램 합 계산 
	for (i = 0; i < 256; i++) {
		acc_hist = acc_hist + hist[i];
		sum[i] = acc_hist;
	}
	for (y = 0; y < 256; y++)
		for (x = 0; x < 256; x++) {
			k = inputImg[y][x];
			resultImg[y][x] = sum[k] / N * 255;
		}

	// TODO: 여기에 구현 코드 추가.
}


void CImageProYooSeHyeokDoc::ContrastSt() //스트레칭
{
	// 컬러영상의 경우 rgb 값을 HSI로 변환후 그 값을 스트레칭하여 그 값을 다시 rgb로 변환한다.
	int x, y;
	float max = 0;
	float value = 0;
	float min = 256;

	for (x = 0; x < 256; x++) {
		for (y = 0; y < 256; y++) {
			if(inputImg[x][y] > max) max = inputImg[x][y];
		
		}
	}
	for (x = 0; x < 256; x++) {
		for (y = 0; y < 256; y++) {
			if (inputImg[x][y] < min) min = inputImg[x][y];

		}
	}
	for (x = 0; x < 256; x++) {
		for (y = 0; y < 256; y++) {
			value = ((inputImg[x][y] - min) / (max - min)) * 255; // value는 실수값을 받아야한다.
			resultImg[x][y] = value;
		}
	}
	// TODO: 여기에 구현 코드 추가.
}


void CImageProYooSeHyeokDoc::PixelTwoImageAdd() //두 이미지의 산술 덧셈
{
	int value = 0;

	LoadTwoImages();
	
	for (int x = 0; x < imageHeight; x++)
		for (int y = 0; y < imageWidth * depth; y++) {
			value = inputImg[x][y] + inputImg2[x][y];
			if (value > 255) resultImg[x][y] = 255;
			else resultImg[x][y] = value;
		}
	/*for (int y = 0; y < imageHeight; y++)
		for (int x = 0; x < imageWidth * depth; x++) {
			value = inputImg[y][x] + inputImg2[y][x];
			if (value > 255) resultImg[y][x] = 255;
			else resultImg[y][x] = value;
		} 원본
		*/
	// TODO: 여기에 구현 코드 추가.
}


void CImageProYooSeHyeokDoc::LoadTwoImages() //두 이미지 불러오기
{
	CFile file;      // CFile 객체 선언 
	CFileDialog dlg(TRUE);   // 파일 선택 대화상자 객체 선언
												 //        TRUE : 파일 열기
												 //         FLASE : 파일 저장
	AfxMessageBox("Select the First Image");

	/*if (dlg.DoModal() == IDOK) {   // 파일 선택 대화 상자 실행 
		file.Open(dlg.GetPathName(), CFile::modeRead);    // 파일 열기 
		file.Read(inputImg, 256 * 256);         // 영상 읽기 
		file.Close();               // 파일 닫기 
	}

	AfxMessageBox("Select the Second Image");

	if (dlg.DoModal() == IDOK) {   // 파일 선택 대화 상자 실행 
			file.Open(dlg.GetPathName(), CFile::modeRead);   // 파일 열기 
			file.Read(inputImg2, 256 * 256);         // 영상 읽기 
			file.Close();               // 파일 닫기 
	} 수정전*/
	if (dlg.DoModal() == IDOK) {
		file.Open(dlg.GetPathName(), CFile::modeRead);
		CArchive ar(&file, CArchive::load);
		LoadImageFile(ar);
		file.Close();
	}

	AfxMessageBox("Select the Second Image");
	if (dlg.DoModal() == IDOK) {
		file.Open(dlg.GetPathName(), CFile::modeRead);
		CArchive ar(&file, CArchive::load);
		LoadSecondImageFile(ar);
		file.Close();
	}
	



		// TODO: 여기에 구현 코드 추가.
}


void CImageProYooSeHyeokDoc::LoadImageFile(CArchive& ar) //파일 불러오기 
{
	int i, maxValue;
	CString type, buf;
	CFile *fp = ar.GetFile();
	CString fname = fp->GetFilePath();
	// 파일의 헤더 읽기 
  // 파일 주소의 뒤에서부터 읽다가 확장자 앞의'.'을 만나면 포인터로 저장한다.
	if (strcmp(strrchr(fname, '.'), ".ppm") == 0 || strcmp(strrchr(fname, '.'), ".PPM") == 0 ||
		strcmp(strrchr(fname, '.'), ".PGM") == 0 || strcmp(strrchr(fname, '.'), ".pgm") == 0)
	{
		ar.ReadString(type);

		do {
			ar.ReadString(buf);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d %d", &imageWidth, &imageHeight);
		//s(tring)scanf :문자를 스캔하라 _s는 세이프모드      
		do {
			ar.ReadString(buf);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d", &maxValue);
		if (strcmp(type, "P5") == 0) depth = 1;
		else depth = 3;
	}
	else if (strcmp(strrchr(fname, '.'), ".raw") == 0 ||
	strcmp(strrchr(fname, '.'), ".RAW") == 0)
   {
   if (fp->GetLength() != 256 * 256) {
	   AfxMessageBox("256x256 크기의 파일만 사용가능합니다.");
	   return;
   }
   imageWidth = 256;
   imageHeight = 256;
   depth = 1;
   }
   // 기억장소 할당 
   inputImg = (unsigned char **)malloc(imageHeight * sizeof(unsigned char *));
   resultImg = (unsigned char **)malloc(imageHeight * sizeof(unsigned char *));
   //sizeof() ()안의 메모리크기 계산 malloc(memoryallocation)   
   for (i = 0; i < imageHeight; i++) { 
   inputImg[i] = (unsigned char *)malloc(imageWidth * depth);
   resultImg[i] = (unsigned char *)malloc(imageWidth * depth);
   }
   // 영상 데이터 읽기 
   for (i = 0; i < imageHeight; i++)
	   ar.Read(inputImg[i], imageWidth*depth);


	// TODO: 여기에 구현 코드 추가.
}


void CImageProYooSeHyeokDoc::LoadSecondImageFile(CArchive& ar) //두번째 이미지 불러오기
{
	int i, maxValue;
	CString type, buf;
	CFile *fp = ar.GetFile();
	CString fname = fp->GetFilePath();


	// 파일의 헤더 읽기 
	if (strcmp(strrchr(fname, '.'), ".ppm") == 0 ||
		strcmp(strrchr(fname, '.'), ".PPM") == 0 ||
		strcmp(strrchr(fname, '.'), ".PGM") == 0 ||
		strcmp(strrchr(fname, '.'), ".pgm") == 0)
	{
		ar.ReadString(type);

		do {
			ar.ReadString(buf);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d %d", &imageWidth, &imageHeight);

		do {
			ar.ReadString(buf);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d", &maxValue);

		if (strcmp(type, "P5") == 0) depth = 1;
		else depth = 3;
	}
	else if (strcmp(strrchr(fname, '.'), ".raw") == 0 ||
		strcmp(strrchr(fname, '.'), ".RAW") == 0)
	{
		if (fp->GetLength() != 256 * 256) {
			AfxMessageBox("256x256 크기의 파일만 사용가능합니다.");
			return;
		}
		imageWidth = 256;
		imageHeight = 256;
		depth = 1;
	}

	// 기억장소 할당
	inputImg2 = (unsigned char **)malloc(imageHeight * sizeof(unsigned char *));

	for (i = 0; i < imageHeight; i++) {
		inputImg2[i] = (unsigned char *)malloc(imageWidth * depth);
	}

	// 영상 데이터 읽기 
	for (i = 0; i < imageHeight; i++)
		ar.Read(inputImg2[i], imageWidth*depth);


	// TODO: 여기에 구현 코드 추가.
}

void CImageProYooSeHyeokDoc::PixelTwoImageMinus() //두 이미지의 뺄셈
{
	int value = 0;

	LoadTwoImages();

	for (int x = 0; x < imageHeight; x++)
		for (int y = 0; y < imageWidth * depth; y++) {
			value = inputImg[x][y] - inputImg2[x][y];
			if (value < 0) resultImg[x][y] = 0;
			else resultImg[x][y] = value;
		}
	/*for (int y = 0; y < imageHeight; y++)
		for (int x = 0; x < imageWidth * depth; x++) {
			value = inputImg[y][x] + inputImg2[y][x];
			if (value > 255) resultImg[y][x] = 255;
			else resultImg[y][x] = value;
		} 원본
		*/
		// TODO: 여기에 구현 코드 추가.
}

void CImageProYooSeHyeokDoc::RegionSharpening() //이미지 선명화
{
	float kernel[3][3] = { {0, -1, 0}, {-1, 5, -1}, {0, -1, 0} };

	Convolve(inputImg, resultImg, imageWidth, imageHeight, kernel, 0, depth);

	// TODO: 여기에 구현 코드 추가.
}


void CImageProYooSeHyeokDoc::Convolve(unsigned char **inputImg,	unsigned char **resultImg, int cols, int rows, float mask[][3], int bias, int depth) //영역기반처리 작업
{
	int i, j, x, y;
	int red, green, blue;
	int sum;
	unsigned char **tmpImg;

	// 기억장소 할당 
	tmpImg = (unsigned char **)malloc((imageHeight + 2) * sizeof(unsigned char *));

	for (i = 0; i < imageHeight + 2; i++)
		tmpImg[i] = (unsigned char *)malloc((imageWidth + 2) * depth);
	// 0-삽입을 위해 0으로 초기화 
	for (y = 0; y < imageHeight + 2; y++)
		for (x = 0; x < (imageWidth + 2) * depth; x++)
			tmpImg[y][x] = 0;

	// 영상 복사 
	for (y = 1; y < imageHeight + 1; y++)
		for (x = 1; x < imageWidth + 1; x++)
			if (depth == 1) tmpImg[y][x] = inputImg[y - 1][x - 1];
			else if (depth == 3) {
				tmpImg[y][3 * x] = inputImg[y - 1][3 * (x - 1)];
				tmpImg[y][3 * x + 1] = inputImg[y - 1][3 * (x - 1) + 1];
				tmpImg[y][3 * x + 2] = inputImg[y - 1][3 * (x - 1) + 2];
			}
	for (y = 0; y < imageHeight; y++)
		for (x = 0; x < imageWidth; x++) {
			if (depth == 1) {
				sum = 0;
				for (i = 0; i < 3; i++)
					for (j = 0; j < 3; j++)
						sum += (int)(tmpImg[y + i][x + j] * mask[i][j]);

				sum = sum + bias;

				if (sum > 255) sum = 255;
				if (sum < 0) sum = 0;
				resultImg[y][x] = (unsigned char)sum;
			}
			else if (depth == 3) {
				red = 0;
				green = 0;
				blue = 0;
				for (i = 0; i < 3; i++)
					for (j = 0; j < 3; j++) {
						red += (int)(tmpImg[y + i][3 * (x + j)] * mask[i][j]);
						green += (int)(tmpImg[y + i][3 * (x + j) + 1] * mask[i][j]);
						blue += (int)(tmpImg[y + i][3 * (x + j) + 2] * mask[i][j]);
					}
				red = red + bias;
				green = green + bias;
				blue = blue + bias;

				if (red > 255) red = 255;
				if (red < 0) red = 0;
				if (green > 255) green = 255;
				if (green < 0) green = 0;
				if (blue > 255) blue = 255;
				if (blue < 0) blue = 0;
				resultImg[y][3 * x] = (unsigned char)red;
				resultImg[y][3 * x + 1] = (unsigned char)green;
				resultImg[y][3 * x + 2] = (unsigned char)blue;
			}
		}

	// 기억장소 반환 
	for (i = 0; i < imageHeight + 2; i++) free(tmpImg[i]);
	free(tmpImg);

	// TODO: 여기에 구현 코드 추가.
}


void CImageProYooSeHyeokDoc::RegionBluring() // 블러
{
	float kernel[3][3] = { {1.0/9, 1.0/9, 1.0/9}, {1/9.0, 1/9.0, 1/9.0}, {1.0/9, 1.0/9, 1.0/9} };

	ConvolveB(inputImg, resultImg, imageWidth, imageHeight, kernel, 0, depth);
	// TODO: 여기에 구현 코드 추가.
}


void CImageProYooSeHyeokDoc::ConvolveB(unsigned char **inputImg, unsigned char **resultImg, int cols, int rows, float mask[][3], int bias, int depth) //블러 작업
{
	int i, j, x, y;
	int red, green, blue;
	int sum;
	unsigned char **tmpImg;

	// 기억장소 할당 
	tmpImg = (unsigned char **)malloc((imageHeight + 2) * sizeof(unsigned char *));

	for (i = 0; i < imageHeight + 2; i++)
		tmpImg[i] = (unsigned char *)malloc((imageWidth + 2) * depth);
	// 0-삽입을 위해 0으로 초기화 
	for (y = 0; y < imageHeight + 2; y++)
		for (x = 0; x < (imageWidth + 2) * depth; x++)
			tmpImg[y][x] = 0;

	// 영상 복사 
	for (y = 1; y < imageHeight + 1; y++)
		for (x = 1; x < imageWidth + 1; x++)
			if (depth == 1) tmpImg[y][x] = inputImg[y - 1][x - 1];
			else if (depth == 3) {
				tmpImg[y][3 * x] = inputImg[y - 1][3 * (x - 1)];
				tmpImg[y][3 * x + 1] = inputImg[y - 1][3 * (x - 1) + 1];
				tmpImg[y][3 * x + 2] = inputImg[y - 1][3 * (x - 1) + 2];
			}
	for (y = 0; y < imageHeight; y++)
		for (x = 0; x < imageWidth; x++) {
			if (depth == 1) {
				sum = 0;
				for (i = 0; i < 3; i++)
					for (j = 0; j < 3; j++)
						sum += (int)(tmpImg[y + i][x + j] * mask[i][j]);

				sum = sum + bias;

				if (sum > 255) sum = 255;
				if (sum < 0) sum = 0;
				resultImg[y][x] = (unsigned char)sum;
			}
			else if (depth == 3) {
				red = 0;
				green = 0;
				blue = 0;
				for (i = 0; i < 3; i++)
					for (j = 0; j < 3; j++) {
						red += (int)(tmpImg[y + i][3 * (x + j)] * mask[i][j]);
						green += (int)(tmpImg[y + i][3 * (x + j) + 1] * mask[i][j]);
						blue += (int)(tmpImg[y + i][3 * (x + j) + 2] * mask[i][j]);
					}
				red = red + bias;
				green = green + bias;
				blue = blue + bias;

				if (red > 255) red = 255;
				if (red < 0) red = 0;
				if (green > 255) green = 255;
				if (green < 0) green = 0;
				if (blue > 255) blue = 255;
				if (blue < 0) blue = 0;
				resultImg[y][3 * x] = (unsigned char)red;
				resultImg[y][3 * x + 1] = (unsigned char)green;
				resultImg[y][3 * x + 2] = (unsigned char)blue;
			}
		}

	// 기억장소 반환 
	for (i = 0; i < imageHeight + 2; i++) free(tmpImg[i]);
	free(tmpImg);
	// TODO: 여기에 구현 코드 추가.
}


void CImageProYooSeHyeokDoc::Erosion() //침식 연산 침식 한번당 2픽셀씩 줄어든다.
{
	int x, y, min, i, j;

	for (y = 1; y < imageHeight - 1; y++)
		for (x = 1; x < imageWidth - 1; x++) {
			min = 255;
			if (inputImg[y - 1][x - 1] < min) min = inputImg[y - 1][x - 1]; 
			if (inputImg[y - 1][x] < min) min = inputImg[y - 1][x];
			if (inputImg[y - 1][x + 1] < min) min = inputImg[y - 1][x + 1];
			if (inputImg[y][x - 1] < min) min = inputImg[y][x - 1];
			if (inputImg[y][x] < min) min = inputImg[y][x];
			if (inputImg[y][x + 1] < min) min = inputImg[y][x + 1];
			if (inputImg[y + 1][x - 1] < min) min = inputImg[y + 1][x - 1];
			if (inputImg[y + 1][x] < min) min = inputImg[y + 1][x];
			if (inputImg[y + 1][x + 1] < min) min = inputImg[y + 1][x + 1];

			resultImg[y][x] = min;   // 최소값을 결과 영상에 저장 
		}
	/* 연산 방식
		y-1,x-1 | y-1,x | y-1,x+1
		y,  x-1 | y,  x | y,  x+1	
		y+1,x-1 | y+1,x | y+1, x
	*/
	// TODO: 여기에 구현 코드 추가.
}


void CImageProYooSeHyeokDoc::Dilation() //팽창 연산 팽창 한번당 2픽셀씩 증가한다.
{
	int x, y, max, i, j;
	for (y = 1; y < imageHeight - 1; y++)
		for (x = 1; x < imageWidth - 1; x++) {
			max = 0;
			if (inputImg[y - 1][x - 1] > max) max = inputImg[y - 1][x - 1];
			if (inputImg[y - 1][x] > max) max = inputImg[y - 1][x];
			if (inputImg[y - 1][x + 1] > max) max = inputImg[y - 1][x + 1];
			if (inputImg[y][x - 1] > max) max = inputImg[y][x - 1];
			if (inputImg[y][x] > max) max = inputImg[y][x];
			if (inputImg[y][x + 1] > max) max = inputImg[y][x + 1];
			if (inputImg[y + 1][x - 1] > max) max = inputImg[y + 1][x - 1];
			if (inputImg[y + 1][x] > max) max = inputImg[y + 1][x];
			if (inputImg[y + 1][x + 1] > max) max = inputImg[y + 1][x + 1];

			resultImg[y][x] = max;   // 최대값을 결과 영상에 저장 
		}

	// TODO: 여기에 구현 코드 추가.
}


void CImageProYooSeHyeokDoc::Opening() //열림 연산
{
	//열림 연산은 침식 연산을 n번한 뒤 팽창을 n번하여 크기를 유지시켜주어야한다.
	Erosion();
	CopyResultToInput();
	Erosion();
	CopyResultToInput();
	Erosion();
	CopyResultToInput();
	Dilation();
	CopyResultToInput();
	Dilation();
	CopyResultToInput();
	Dilation();

	// TODO: 여기에 구현 코드 추가.
}


void CImageProYooSeHyeokDoc::CopyResultToInput()  //반복
{
/* 침식 또는 팽창을 한 뒤 'resultImg'에 저장된 값으로 
   반복 작업을 하기 위하여 'inputImg'로 옮겨주는 작업*/
	int x, y;
	for (y = 0; y < imageHeight; y++)
		for (x = 0; x < imageWidth; x++)
			inputImg[y][x] = resultImg[y][x];
	// TODO: 여기에 구현 코드 추가.
}


void CImageProYooSeHyeokDoc::Closing() //닫힘 연산
{
	Dilation();
	CopyResultToInput();
	Dilation();
	CopyResultToInput();
	Dilation();
	CopyResultToInput();
	Erosion();
	CopyResultToInput();
	Erosion();
	CopyResultToInput();
	Erosion();
	// TODO: 여기에 구현 코드 추가.
}


void CImageProYooSeHyeokDoc::RegionEdge() //경계선 검출식 _Sobel
{
	float mask[3][3] = { {-1, -2, -1}, {0, 0, 0}, {1, 2, 1} }; //수평 경계선 마스크값
	float mask2[3][3] = { {1, 0, -1}, {2, 0, -2}, {1, 0, -1} }; //수직 경계선 마스크값
	
	double resultImg1;

	// 기억장소 할당 
	/*resultImg1 = (unsigned char **)malloc((imageHeight + 2) * sizeof(unsigned char *));

	//메모리를 resultImg1,2 선언해서 수평과 수직 결과 값을 저장한 뒤 sqrt로 계산하여 출력
	resultImg1 = Convolve(inputImg, resultImg, imageWidth, imageHeight, mask, 0, depth); //수평 계산
	 resultImg2 = Convolve(inputImg, resultImg, imageWidth, imageHeight, mask2, 0, depth); //수직 계산
	
	sqrt((resultImg1*resultImg1) + (resultImg2*resultImg2);
	*/
	// TODO: 여기에 구현 코드 추가.
}


void CImageProYooSeHyeokDoc::GeometryZoominPixelCopy() //확대(픽셀 복제)
{
	int i, y, x;
	gImageWidth = imageWidth * 3;
	gImageHeight = imageHeight * 3;
	gResultImg = (unsigned char **)malloc(gImageHeight *sizeof(unsigned char *));

	for (i = 0; i < gImageHeight; i++) {
		gResultImg[i] = (unsigned char *)malloc(gImageWidth * depth);
	}
	if (depth == 1)
	{
		for (y = 0; y < gImageHeight; y++) {
			for (x = 0; x < gImageWidth; x++) {
				gResultImg[y][x] = inputImg[y / 3][x / 3];
			}

		}
	}
	else if (depth == 3)
	{
		for (y = 0; y < gImageHeight; y++) {
			for (x = 0; x < gImageWidth; x++) {
				gResultImg[y][3 * x] = inputImg[y / 3][(x / 3) * 3];
				gResultImg[y][3 * x + 1] = inputImg[y / 3][(x / 3) * 3 + 1];
				gResultImg[y][3 * x + 2] = inputImg[y / 3][(x / 3) * 3 + 2];
			}
		}
	}
	// TODO: 여기에 구현 코드 추가.
}


void CImageProYooSeHyeokDoc::GeometryZoominInterpolation() //확대 (양선형 보간법)
{
	int i, y, x;
	float src_x, src_y;      // 원시 화소 위치  
	float alpha, beta;
	int scale_x, scale_y;       // float  scale_x, scale_y; 
	int E, F;              // x 방향으로 보간된 결과 값 
	int Ax, Ay, Bx, By, Cx, Cy, Dx, Dy; // 보간에 사용될 4개 픽셀의 좌표 
	scale_x = 3;
	scale_y = 3;

	// 결과 영상의 크기 설정 
	gImageWidth = imageWidth * scale_x;
	gImageHeight = imageHeight * scale_y;

	// 결과 영상을 저장할 기억장소 공간 할당 
	gResultImg = (unsigned char **)malloc(gImageHeight * sizeof(unsigned char *));
	for (i = 0; i < gImageHeight; i++) {
		gResultImg[i] = (unsigned char *)malloc(gImageWidth * depth);
	}

	for (y = 0; y < gImageHeight; y++)
		for (x = 0; x < gImageWidth; x++) {
			// 원시 영상에서의 픽셀 좌표 계산 
			src_x = x / (float)scale_x;        // src_x = x / scale_x; 
			src_y = y / (float)scale_y;        // src_y = y / scale_y; 
			alpha = src_x - x / scale_x;      // alpha = src_x – (int) src_x; 
			beta = src_y - y / scale_y;       // beta = src_y – (int) src_y; 
			 // 보간에 사용된 4 픽셀의 좌표 계산 
			Ax = x / scale_x;
			Ay = y / scale_y;
			Bx = Ax + 1;
			By = Ay;
			Cx = Ax;
			Cy = Ay + 1;
			Dx = Ax + 1;
			Dy = Ay + 1;

			// 픽셀 위치가 영상의 경계를 벗어나는지 검사 
			if (Bx > imageWidth - 1) Bx = imageWidth - 1;
			if (Dx > imageWidth - 1) Dx = imageWidth - 1;
			if (Cy > imageHeight - 1) Cy = imageHeight - 1;
			if (Dy > imageHeight - 1) Dy = imageHeight - 1;
			// x 방향으로 보간 
			E = (int)(inputImg[Ay][Ax] * (1 - alpha) + inputImg[By][Bx] * alpha);
			F = (int)(inputImg[Cy][Cx] * (1 - alpha) + inputImg[Dy][Dx] * alpha);
			// y 방향으로 보간 
			gResultImg[y][x] = (unsigned char)(E * (1 - beta) + F * beta);
		}
	// TODO: 여기에 구현 코드 추가.
}


void CImageProYooSeHyeokDoc::GeometryZoomoutSubsampling() //축소_서브샘플링
{
	int i, y, x;
	int src_x, src_y;
	int scale_x = 3, scale_y = 3;

	// 결과 영상의 크기 계산 
	gImageWidth = (imageWidth % scale_x == 0) ? imageWidth / scale_x : imageWidth / scale_x + 1;
	gImageHeight = (imageHeight % scale_y == 0) ? imageHeight / scale_y : imageHeight / scale_y + 1;

	// 결과 영상 저장을 위한 기억장소 할당 
	gResultImg = (unsigned char **)malloc(gImageHeight * sizeof(unsigned char *));
	for (i = 0; i < gImageHeight; i++) {
		gResultImg[i] = (unsigned char *)malloc(gImageWidth * depth);
	}

	for (y = 0; y < gImageHeight; y++)
		for (x = 0; x < gImageWidth; x++) {
			src_y = y * scale_y;
			src_x = x * scale_x;

			// gResultImg[y][x] = inputImg[src_y][src_x]; 흑백만할경우

			if (depth == 1)					
				gResultImg[y][x] = inputImg[src_y][src_x];

			else if (depth == 3){
				gResultImg[y][3 * x] = inputImg[src_y][src_x * 3];
				gResultImg[y][3 * x + 1] = inputImg[src_y][src_x * 3 + 1];
				gResultImg[y][3 * x + 2] = inputImg[src_y][src_x * 3 + 2];
			}
		}
	

	// TODO: 여기에 구현 코드 추가.
}


void CImageProYooSeHyeokDoc::GeometryZoomoutAvg() //축소_평균값필터링
{
	int i, j, x, y;
	int sum;
	int src_x, src_y;
	int scale_x = 3, scale_y = 3;
	int sumr, sumg, sumb;

	// 결과 영상의 크기 계산 
	gImageWidth = (imageWidth % scale_x == 0) ? imageWidth / scale_x : imageWidth / scale_x + 1;
	gImageHeight = (imageHeight % scale_y == 0) ? imageHeight / scale_y : imageHeight / scale_y + 1;
	// 결과 영상을 저장할 기억장소 할당 
	gResultImg = (unsigned char **)malloc(gImageHeight * sizeof(unsigned char *));
	for (i = 0; i < gImageHeight; i++) {
		gResultImg[i] = (unsigned char *)malloc(gImageWidth * depth);
	}

	for (y = 0; y < imageHeight; y = y + scale_y)
		for (x = 0; x < imageWidth; x = x + scale_x) {
			// 필터 윈도우 내의 픽셀값 합계 계산 
			sum = 0;
			sumr = 0;
			sumg = 0;
			sumb = 0;
			for (i = 0; i < scale_y; i++)
				for (j = 0; j < scale_x; j++) {
					src_x = x + j;
					src_y = y + i;
					if (src_x > imageWidth - 1) src_x = imageWidth - 1;    // 영상의 경계  검사 
					if (src_y > imageHeight - 1) src_y = imageHeight - 1;

					if(depth == 1)
						sum += inputImg[src_y][src_x];
					else if(depth == 3)
					{
						sumr += inputImg[src_y][src_x * 3];
						sumg += inputImg[src_y][src_x * 3 + 1];
						sumb += inputImg[src_y][src_x * 3 + 2];
					}
				}
			if(depth == 1) //흑백
				sum = sum / (scale_x * scale_y);  // 평균값 계산 
			else if (depth == 3) { //컬러
				sumr = sumr / (scale_x *scale_y);
				sumg = sumg / (scale_x *scale_y);
				sumb = sumb / (scale_x *scale_y);
			}
			if (depth == 1)
				gResultImg[y / scale_y][x / scale_x] = (unsigned char)sum; // 결과 값 저장 

			else if (depth == 3) {
				gResultImg[y / scale_y][(x / scale_x)*3] = (unsigned char)sumr;
				gResultImg[y / scale_y][(x / scale_x)*3+1] = (unsigned char)sumg;
				gResultImg[y / scale_y][(x / scale_x)*3+2] = (unsigned char)sumb;
			}
		}
	// TODO: 여기에 구현 코드 추가.
}

#define PI 3.14159 

void CImageProYooSeHyeokDoc::GeometryRotate() //회전
{
	int y, x, x_source, y_source, Cx, Cy;
	float angle;
	int Oy;
	int i, xdiff, ydiff;

	Oy = imageHeight - 1;

	// 'PI(π) : 180 = X(라디안) : 30' 가 아래식으로 변환된다. 
	// π= 180도 이다.
	angle = PI / 180.0 * 30.0;   // 30도를 라디안 값의 각도로 변환 

	Cx = imageWidth / 2;   // 회전 중심의 x좌표 
	Cy = imageHeight / 2;   // 회전 중심의 y좌표 

	// 결과 영상 크기 계산 
	gImageWidth = (int)(imageHeight * cos(PI / 2.0 - angle) + imageWidth * cos(angle));
	gImageHeight = (int)(imageHeight * cos(angle) + imageWidth * cos(PI / 2.0 - angle));

	// 결과 영상을 저장할 기억장소 할당 
	gResultImg = (unsigned char **)malloc(gImageHeight * sizeof(unsigned char *));
	for (i = 0; i < gImageHeight; i++) {
		gResultImg[i] = (unsigned char *)malloc(gImageWidth * depth);
	}

	// 결과 영상의 x 좌표 범위 : -xdiff ~ gImageWidth - xdiff - 1 
	// 결과 영상의 y 좌표 범위 : -ydiff ~ gImageHeight - ydiff - 1 
	xdiff = (gImageWidth - imageWidth) / 2;
	ydiff = (gImageHeight - imageHeight) / 2;

	for (y = -ydiff; y < gImageHeight - ydiff; y++)
		for (x = -xdiff; x < gImageWidth - xdiff; x++)
		{
			// 변환 단계 
			//     1 단계 : 원점이 영상의 좌측 하단에 오도록 y 좌표 변환 
			//     2 단계 : 회전 중심이 원점에 오도록 이동 
			//     3 단계 : 각도 angle 만큼 회전 
			//     4 단계 : 회전 중심이 원래 위치로 돌아가도록 이동  (원점을 이동하여 회전시 좌표들중 음수가 생성되기에 원 위치로 작업 완료된 영상을 옮겨주는것)
			x_source = (int)(((Oy - y) - Cy) * sin(angle) + (x - Cx) * cos(angle) + Cx);
			y_source = (int)(((Oy - y) - Cy) * cos(angle) - (x - Cx) * sin(angle) + Cy);

			//     5 단계 : 원점이 영상의 좌측 상단에 오도록 y 좌표 변환 
			y_source = Oy - y_source;

			if (depth == 1) {

				if (x_source < 0 || x_source > imageWidth - 1 ||
					y_source < 0 || y_source > imageHeight - 1)
					gResultImg[y + ydiff][x + xdiff] = 255;
				else
					gResultImg[y + ydiff][x + xdiff] = inputImg[y_source][x_source];

			}
			else if (depth == 3) 
				if (x_source < 0 || x_source > imageWidth - 1 || y_source < 0 || y_source > imageHeight - 1) {
					gResultImg[y + ydiff][(x + xdiff) * 3] = 255;
					gResultImg[y + ydiff][(x + xdiff) * 3 + 1] = 255;
					gResultImg[y + ydiff][(x + xdiff) * 3 + 2] = 255;
				}
			
			else {
				gResultImg[y + ydiff][(x + xdiff) * 3] = inputImg[y_source][x_source * 3];
				gResultImg[y + ydiff][(x + xdiff) * 3 + 1] = inputImg[y_source][x_source * 3 + 1];
				gResultImg[y + ydiff][(x + xdiff) * 3 + 2] = inputImg[y_source][x_source * 3 + 2];
			}
		}
}
	/*
	if (depth == 1)
		gResultImg[y / scale_y][x / scale_x] = (unsigned char)sum; // 결과 값 저장 

	else if (depth == 3) {
		gResultImg[y / scale_y][(x / scale_x) * 3] = (unsigned char)sumr;
		gResultImg[y / scale_y][(x / scale_x) * 3 + 1] = (unsigned char)sumg;
		gResultImg[y / scale_y][(x / scale_x) * 3 + 2] = (unsigned char)sumb;
	}*/
	// TODO: 여기에 구현 코드 추가.

typedef struct
{
	int Px;
	int Py;
	int Qx;
	int Qy;
} control_line;

#include <math.h>

void CImageProYooSeHyeokDoc::GeometryWarping() //워핑
{ //156 195 157 231 155 269
	control_line source_lines[5] = { {0,0,299,0},{299,0,299,339},{299,339,0,339},{0,339,0,0},{156,195,157,231} };
	/*{ {116,7,207,5},{34,109,90,21},{55,249,30,128},{118,320,65,261},
	 {123,321,171,321},{179,319,240,264},{247,251,282,135},{281,114,228,8},
	 {78,106,123,109},{187,115,235,114},{72,142,99,128},{74,150,122,154},
	 {108,127,123,146},{182,152,213,132},{183,159,229,157},{219,131,240,154},
	 {80,246,117,212},{127,222,146,223},{154,227,174,221},{228,252,183,213},
	 {114,255,186,257},{109,258,143,277},{152,278,190,262} };*/

	control_line dest_lines[5] = { {0,0,299,0},{299,0,299,339},{299,339,0,339},{0,339,0,0},{156,195,155,269} };
	/*{ {120,8,200,6},{12,93,96,16},{74,271,16,110},{126,336,96,290},
	 {142,337,181,335},{192,335,232,280},{244,259,288,108},{285,92,212,13},
	 {96,135,136,118},{194,119,223,125},{105,145,124,134},{110,146,138,151},
	 {131,133,139,146},{188,146,198,134},{189,153,218,146},{204,133,221,140},
	 {91,268,122,202},{149,206,159,209},{170,209,181,204},{235,265,208,199},
	 {121,280,205,284},{112,286,160,301},{166,301,214,287} };*/

	double u;       // 수직 교차점의 위치   
	double h;       // 제어선으로부터 픽셀의 수직 변위 
	double d;       // 제어선과 픽셀 사이의 거리 
	double tx, ty;   // 결과영상 픽셀에 대응되는 입력 영상 픽셀 사이의 변위의 합  
	double xp, yp;  // 각 제어선에 대해 계산된 입력 영상의 대응되는 픽셀 위치   
	double weight;      // 각 제어선의 가중치       
	double totalWeight;  // 가중치의 합          
	double a = 0.001;
	double b = 2.0;
	double p = 0.75;

	int x1, x2, y1, y2;
	int src_x1, src_y1, src_x2, src_y2;
	double src_line_length, dest_line_length;

	int num_lines = 5;         // 제어선의 수 
	int line;
	int x, y;
	int source_x, source_y;
	int last_row, last_col;

	last_row = imageHeight - 1;
	last_col = imageWidth - 1;

	// 출력 영상의 각 픽셀에 대하여 
	for (y = 0; y < imageHeight; y++)
	{
		for (x = 0; x < imageWidth; x++)
		{
			totalWeight = 0.0;
			tx = 0.0;
			ty = 0.0;

			// 각 제어선에 대하여 
			for (line = 0; line < num_lines; line++)
			{
				x1 = dest_lines[line].Px;
				y1 = dest_lines[line].Py;
				x2 = dest_lines[line].Qx;
				y2 = dest_lines[line].Qy;

				dest_line_length = sqrt((double)(x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));

				// 수직교차점의 위치 및 픽셀의 수직 변위 계산 
				u = (double)((x - x1)*(x2 - x1) + (y - y1)*(y2 - y1)) /
					(double)((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
				h = (double)((y - y1)*(x2 - x1) - (x - x1)*(y2 - y1)) / dest_line_length;

				// 제어선과 픽셀 사이의 거리 계산 
				if (u < 0) d = sqrt((double)(x - x1) * (x - x1) + (y - y1) * (y - y1));
				else if (u > 1) d = sqrt((double)(x - x2) * (x - x2) + (y - y2) * (y - y2));
				else d = fabs(h);

				src_x1 = source_lines[line].Px;
				src_y1 = source_lines[line].Py;
				src_x2 = source_lines[line].Qx;
				src_y2 = source_lines[line].Qy;
				src_line_length = sqrt((double)(src_x2 - src_x1)*(src_x2 - src_x1) +
					(src_y2 - src_y1)*(src_y2 - src_y1));

				// 입력 영상에서의 대응 픽셀 위치 계산 
				xp = src_x1 + u * (src_x2 - src_x1) -
					h * (src_y2 - src_y1) / src_line_length;
				yp = src_y1 + u * (src_y2 - src_y1) +
					h * (src_x2 - src_x1) / src_line_length;

				// 제어선에 대한 가중치 계산 
				weight = pow((pow((double)(dest_line_length), p) / (a + d)), b);

				// 대응 픽셀과의 변위 계산 
				tx += (xp - x) * weight;
				ty += (yp - y) * weight;
				totalWeight += weight;
			}
			source_x = x + (int)(tx / totalWeight + 0.5);
			source_y = y + (int)(ty / totalWeight + 0.5);

			// 영상의 경계를 벗어나는지 검사 
			if (source_x < 0) source_x = 0;
			if (source_x > last_col) source_x = last_col;
			if (source_y < 0) source_y = 0;
			if (source_y > last_row) source_y = last_row;

			resultImg[y][x] = inputImg[source_y][source_x];
		}
	}
	// TODO: 여기에 구현 코드 추가.
}

#define NUM_FRAMES 10 

void CImageProYooSeHyeokDoc::GeometryMorphing() //모핑
{
	control_line source_lines[23] =
	{ {83,95,208,95},{200,33,76,99},//{34,199,76,99},{76,300,37,212},
	 {125,138,83,308},{131,338,179,339},{188,336,236,303},{248,290,281,8},
	 {78,106,123,109},{187,115,235,114},{72,142,99,128},{74,150,122,154},
	 {108,127,123,146},{182,152,213,132},{183,159,229,157},{219,131,240,154},
	 {80,246,117,212},{127,222,146,223},{154,227,174,221},{228,252,183,213},
	 {114,255,186,257},{109,258,143,277},{152,278,190,262} };

	control_line dest_lines[23] =
	{ {120,8,200,6},{12,93,96,16},{74,271,16,110},{126,336,96,290},
	 {142,337,181,335},{192,335,232,280},{244,259,288,108},{285,92,212,13}, //~머리윤곽선
	 {96,135,136,118},{194,119,223,125}, //눈썹
	{105,145,124,134},{110,146,138,151}, {131,133,139,146}, //왼쪽눈 반시계방향
	{188,146,198,134},{189,153,218,146},{204,133,221,140}, //오른쪽눈 반시계방향
	 {91,268,122,202},{149,206,159,209},{170,209,181,204},{235,265,208,199}, // 코-입가 사이라인 왼쪽 ,왼쪽코,오른쪽코,코-입가사이라인 오른쪽
	 {121,280,205,284},{112,286,160,301},{166,301,214,287} }; //왼쪽부터 입 반시계방향

	double u;       // 수직 교차점의 위치   
	double h;       // 제어선으로부터 픽셀의 수직 변위 
	double d;       // 제어선과 픽셀 사이의 거리 
	double tx, ty;   // 결과영상 픽셀에 대응되는 입력 영상 픽셀 사이의 변위의 합  
	double xp, yp;  // 각 제어선에 대해 계산된 입력 영상의 대응되는 픽셀 위치     
	double weight;     // 각 제어선의 가중치       
	double totalWeight; // 가중치의 합          
	double a = 0.001, b = 2.0, p = 0.75;
	unsigned char **warpedImg;
	unsigned char **warpedImg2;
	int frame;
	double fweight;
	control_line warp_lines[23];
	double tx2, ty2, xp2, yp2;
	int dest_x1, dest_y1, dest_x2, dest_y2, source_x2, source_y2;
	int x1, x2, y1, y2, src_x1, src_y1, src_x2, src_y2;
	double src_line_length, dest_line_length;
	int i, j;
	int num_lines = 23;         // 제어선의 수 
	int line, x, y, source_x, source_y, last_row, last_col;

	// 두 입력 영상을 읽어들임 
	LoadTwoImages();

	// 중간 프레임의 워핑 결과를 저장을 위한 기억장소 할당 
	warpedImg = (unsigned char **)malloc(imageHeight * sizeof(unsigned char *));
	for (i = 0; i < imageHeight; i++) {
		warpedImg[i] = (unsigned char *)malloc(imageWidth * depth);
	}

	warpedImg2 = (unsigned char **)malloc(imageHeight * sizeof(unsigned char *));
	for (i = 0; i < imageHeight; i++) {
		warpedImg2[i] = (unsigned char *)malloc(imageWidth * depth);
	}
	for (i = 0; i < NUM_FRAMES; i++) {
		morphedImg[i] = (unsigned char **)malloc(imageHeight * sizeof(unsigned char *));
		for (j = 0; j < imageHeight; j++) {
			morphedImg[i][j] = (unsigned char *)malloc(imageWidth * depth);
		}
	}
	last_row = imageHeight - 1;
	last_col = imageWidth - 1;

	// 각 중간 프레임에 대하여 
	for (frame = 1; frame <= NUM_FRAMES; frame++)
	{
		// 중간 프레임에 대한 가중치 계산 
		fweight = (double)(frame) / NUM_FRAMES;

		// 중간 프레임에 대한 제어선 계산 
		for (line = 0; line < num_lines; line++)
		{
			warp_lines[line].Px = (int)(source_lines[line].Px +
				(dest_lines[line].Px - source_lines[line].Px)*fweight);
			warp_lines[line].Py = (int)(source_lines[line].Py +
				(dest_lines[line].Py - source_lines[line].Py)*fweight);
			warp_lines[line].Qx = (int)(source_lines[line].Qx +
				(dest_lines[line].Qx - source_lines[line].Qx)*fweight);
			warp_lines[line].Qy = (int)(source_lines[line].Qy +
				(dest_lines[line].Qy - source_lines[line].Qy)*fweight);
		}

		// 출력 영상의 각 픽셀에 대하여 
		for (y = 0; y < imageHeight; y++)
		{
			for (x = 0; x < imageWidth; x++)
			{
				totalWeight = 0.0;
				tx = 0.0;
				ty = 0.0;
				tx2 = 0.0;
				ty2 = 0.0;
				// 각 제어선에 대하여 
				for (line = 0; line < num_lines; line++)
				{
					x1 = warp_lines[line].Px;
					y1 = warp_lines[line].Py;
					x2 = warp_lines[line].Qx;
					y2 = warp_lines[line].Qy;
					dest_line_length = sqrt((double)(x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));

					// 수직교차점의 위치 및 픽셀의 수직 변위 계산 
					u = (double)((x - x1)*(x2 - x1) + (y - y1)*(y2 - y1)) /
						(double)((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
					h = (double)((y - y1)*(x2 - x1) - (x - x1)*(y2 - y1)) / dest_line_length;

					// 제어선과 픽셀 사이의 거리 계산 
					if (u < 0) d = sqrt((double)(x - x1) * (x - x1) + (y - y1) * (y - y1));
					else if (u > 1) d = sqrt((double)(x - x2) * (x - x2) + (y - y2) * (y - y2));
					else d = fabs(h);

					src_x1 = source_lines[line].Px;
					src_y1 = source_lines[line].Py;
					src_x2 = source_lines[line].Qx;
					src_y2 = source_lines[line].Qy;
					src_line_length = sqrt((double)(src_x2 - src_x1)*(src_x2 - src_x1) +
						(src_y2 - src_y1)*(src_y2 - src_y1));
					dest_x1 = dest_lines[line].Px;
					dest_y1 = dest_lines[line].Py;
					dest_x2 = dest_lines[line].Qx;
					dest_y2 = dest_lines[line].Qy;
					dest_line_length = sqrt((double)(dest_x2 - dest_x1)*(dest_x2 - dest_x1) +
						(dest_y2 - dest_y1)*(dest_y2 - dest_y1));

					// 입력 영상 1에서의 대응 픽셀 위치 계산 
					xp = src_x1 + u * (src_x2 - src_x1) -
						h * (src_y2 - src_y1) / src_line_length;
					yp = src_y1 + u * (src_y2 - src_y1) +
						h * (src_x2 - src_x1) / src_line_length;

					// 입력 영상 2에서의 대응 픽셀 위치 계산 
					xp2 = dest_x1 + u * (dest_x2 - dest_x1) -
						h * (dest_y2 - dest_y1) / dest_line_length;
					yp2 = dest_y1 + u * (dest_y2 - dest_y1) +
						h * (dest_x2 - dest_x1) / dest_line_length;

					// 제어선에 대한 가중치 계산 
					weight = pow((pow((double)(dest_line_length), p) / (a + d)), b);

					// 입력 영상 1의 대응 픽셀과의 변위 계산 
					tx += (xp - x) * weight;
					ty += (yp - y) * weight;

					// 입력 영상 2의 대응 픽셀과의 변위 계산 
					tx2 += (xp2 - x) * weight;
					ty2 += (yp2 - y) * weight;

					totalWeight += weight;
				}

				// 입력 영상 1의 대응 픽셀 위치 계산     
				source_x = x + (int)(tx / totalWeight + 0.5);
				source_y = y + (int)(ty / totalWeight + 0.5);

				// 입력 영상 2의 대응 픽셀 위치 계산 
				source_x2 = x + (int)(tx2 / totalWeight + 0.5);
				source_y2 = y + (int)(ty2 / totalWeight + 0.5);

				// 영상의 경계를 벗어나는지 검사 
				if (source_x < 0) source_x = 0;
				if (source_x > last_col) source_x = last_col;
				if (source_y < 0) source_y = 0;
				if (source_y > last_row) source_y = last_row;

				if (source_x2 < 0) source_x2 = 0;
				if (source_x2 > last_col) source_x2 = last_col;
				if (source_y2 < 0) source_y2 = 0;
				if (source_y2 > last_row) source_y2 = last_row;

				// 워핑 결과 저장 
				warpedImg[y][x] = inputImg[source_y][source_x];
				warpedImg2[y][x] = inputImg2[source_y2][source_x2];
			}
		}

		// 모핑 결과 합병 
		for (y = 0; y < imageHeight; y++)
			for (x = 0; x < imageWidth; x++) {
				int val = (int)((1.0 - fweight) * warpedImg[y][x] +
					fweight * warpedImg2[y][x]);
				if (val < 0) val = 0;
				if (val > 255) val = 255;
				morphedImg[frame - 1][y][x] = val;
			}
	}
}
