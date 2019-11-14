
// ImagePro_YooSeHyeokView.cpp: CImageProYooSeHyeokView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImagePro_YooSeHyeok.h"
#endif

#include "ImagePro_YooSeHyeokDoc.h"
#include "ImagePro_YooSeHyeokView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TWO_IMAGES      1 
#define THREE_IMAGES    2 
#define TWO_IMAGES_SCALED 4
#define MORPHING 8


// CImageProYooSeHyeokView

IMPLEMENT_DYNCREATE(CImageProYooSeHyeokView, CScrollView)

BEGIN_MESSAGE_MAP(CImageProYooSeHyeokView, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CImageProYooSeHyeokView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_PIXEL_ADD, &CImageProYooSeHyeokView::OnPixelAdd)
	ON_COMMAND(ID_PIXEL_REVERSE, &CImageProYooSeHyeokView::OnPixelReverse)
	ON_COMMAND(ID_PIXEL_MINUS, &CImageProYooSeHyeokView::OnPixelMinus)
	ON_COMMAND(ID_PIXEL_MULTIPLE, &CImageProYooSeHyeokView::OnPixelMultiple)
	ON_COMMAND(ID_PIXEL_DIV, &CImageProYooSeHyeokView::OnPixelDiv)
	ON_COMMAND(ID_PIXEL_Re, &CImageProYooSeHyeokView::OnPixelRe)
	ON_COMMAND(ID_PIXEL_HISTO_EQ, &CImageProYooSeHyeokView::OnPixelHistoEq)
	ON_COMMAND(ID_CONTRAST_ST, &CImageProYooSeHyeokView::OnContrastSt)
	ON_COMMAND(ID_PIXEL_TWO_IMAGE_ADD, &CImageProYooSeHyeokView::OnPixelTwoImageAdd)
	ON_COMMAND(On_Pixel_Two_Image_Minus, &CImageProYooSeHyeokView::OnPixelTwoImageMinus)
	ON_COMMAND(ID_REGION_SHARPENING, &CImageProYooSeHyeokView::OnRegionSharpening)
	ON_COMMAND(ID_REGION_BLURING, &CImageProYooSeHyeokView::OnRegionBluring)
	ON_COMMAND(ID_EROSION, &CImageProYooSeHyeokView::OnErosion)
	ON_COMMAND(ID_DILATION, &CImageProYooSeHyeokView::OnDilation)
	ON_COMMAND(ID_OPENING, &CImageProYooSeHyeokView::OnOpening)
	ON_COMMAND(ID_CLOSING, &CImageProYooSeHyeokView::OnClosing)
	ON_COMMAND(ID_REGION_EDGE, &CImageProYooSeHyeokView::OnRegionEdge)
	ON_COMMAND(ID_GEOMETRY_ZOOMIN_PIXEL_COPY, &CImageProYooSeHyeokView::OnGeometryZoominPixelCopy)
	ON_COMMAND(ID_GEOMETRY_ZOOMIN_INTERPOLATION, &CImageProYooSeHyeokView::OnGeometryZoominInterpolation)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_SUBSAMPLING, &CImageProYooSeHyeokView::OnGeometryZoomoutSubsampling)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_AVG, &CImageProYooSeHyeokView::OnGeometryZoomoutAvg)
	ON_COMMAND(ID_GEOMETRY_ROTATE, &CImageProYooSeHyeokView::OnGeometryRotate)
	ON_COMMAND(ID_GEOMETRY_WARPING, &CImageProYooSeHyeokView::OnGeometryWarping)
	ON_COMMAND(ID_GEOMETRY_MORPHING, &CImageProYooSeHyeokView::OnGeometryMorphing)
END_MESSAGE_MAP()

// CImageProYooSeHyeokView 생성/소멸

CImageProYooSeHyeokView::CImageProYooSeHyeokView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CImageProYooSeHyeokView::~CImageProYooSeHyeokView()
{
}

BOOL CImageProYooSeHyeokView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CImageProYooSeHyeokView 그리기

void CImageProYooSeHyeokView::OnDraw(CDC* pDC)
{
	CImageProYooSeHyeokDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	/*
	for (int y = 0; y < 256; y++)       // 입력 영상 출력 
		for (int x = 0; x < 256; x++)
			pDC->SetPixel(x, y, RGB(pDoc->inputImg[y][x],
				pDoc->inputImg[y][x],
				pDoc->inputImg[y][x]));

	if (viewMode == THREE_IMAGES) {
		for (int y = 0; y < 256; y++)       // 두번째 입력 영상 출력 
			for (int x = 0; x < 256; x++)
				pDC->SetPixel(x + 300, y, RGB(pDoc->inputImg2[y][x],
					pDoc->inputImg2[y][x],
					pDoc->inputImg2[y][x]));

		for (int y = 0; y < 256; y++)       // 결과 영상 출력 
			for (int x = 0; x < 256; x++)
				pDC->SetPixel(x + 600, y, RGB(pDoc->resultImg[y][x],
					pDoc->resultImg[y][x],
					pDoc->resultImg[y][x]));
	}
	else {
		for (int y = 0; y < 256; y++)       // 결과 영상 출력 
			for (int x = 0; x < 256; x++)
				pDC->SetPixel(x + 300, y, RGB(pDoc->resultImg[y][x],
					pDoc->resultImg[y][x],
					pDoc->resultImg[y][x]));
				수정전	*/
	if (pDoc->inputImg == NULL) return; // 입력 영상이 읽히지 않았으면 종료 

	if (pDoc->depth == 1) { // 흑백 영상 출력 
		for (int y = 0; y < pDoc->imageHeight; y++)       // 입력 영상 출력 
			for (int x = 0; x < pDoc->imageWidth; x++)
				pDC->SetPixel(x, y, RGB(pDoc->inputImg[y][x],
					pDoc->inputImg[y][x], pDoc->inputImg[y][x]));



		if (viewMode == THREE_IMAGES) {
			for (int y = 0; y < pDoc->imageHeight; y++)   // 두번째 입력 영상 출력 
				for (int x = 0; x < pDoc->imageWidth; x++)
					pDC->SetPixel(x + pDoc->imageWidth + 30, y,
						RGB(pDoc->inputImg2[y][x],
							pDoc->inputImg2[y][x],
							pDoc->inputImg2[y][x]));
			for (int y = 0; y < pDoc->imageHeight; y++)       // 결과 영상 출력 
				for (int x = 0; x < pDoc->imageWidth; x++)
					pDC->SetPixel(x + pDoc->imageWidth * 2 + 60, y,
						RGB(pDoc->resultImg[y][x],
							pDoc->resultImg[y][x],
							pDoc->resultImg[y][x]));
		}

		else if (viewMode == TWO_IMAGES_SCALED) {
			for (int y = 0; y < pDoc->gImageHeight; y++)   // 크기가 변한 결과 영상 출력 
				for (int x = 0; x < pDoc->gImageWidth; x++)
					pDC->SetPixel(x + pDoc->imageWidth + 30, y,
						RGB(pDoc->gResultImg[y][x],
							pDoc->gResultImg[y][x],
							pDoc->gResultImg[y][x]));
		}

		else if (viewMode == MORPHING) {
			for (int y = 0; y < pDoc->imageHeight; y++)       // 두번째 입력 영상 출력 
				for (int x = 0; x < pDoc->imageWidth; x++)
					pDC->SetPixel(x + pDoc->imageWidth + 30, y,
						RGB(pDoc->inputImg2[y][x],
							pDoc->inputImg2[y][x],
							pDoc->inputImg2[y][x]));
			for (int i = 0; i < 10; i++)
				for (int y = 0; y < pDoc->imageHeight; y++)       // 모핑 결과 출력 
					for (int x = 0; x < pDoc->imageWidth; x++)
						pDC->SetPixel(x + pDoc->imageWidth * 2 + 60, y,
							RGB(pDoc->morphedImg[i][y][x],
								pDoc->morphedImg[i][y][x],
								pDoc->morphedImg[i][y][x]));
		}

		else {
			for (int y = 0; y < pDoc->imageHeight; y++)       // 결과 영상 출력 
				for (int x = 0; x < pDoc->imageWidth; x++)
					pDC->SetPixel(x + pDoc->imageWidth + 30, y,
						RGB(pDoc->resultImg[y][x],
							pDoc->resultImg[y][x],
							pDoc->resultImg[y][x]));
		}
	}
	else if (pDoc->depth == 3) { // 컬러 영상 출력 
		for (int y = 0; y < pDoc->imageHeight; y++)       // 입력 영상 출력 
			for (int x = 0; x < pDoc->imageWidth; x++)
				pDC->SetPixel(x, y, RGB(pDoc->inputImg[y][3 * x],
					pDoc->inputImg[y][3 * x + 1], pDoc->inputImg[y][3 * x + 2]));
		if (viewMode == THREE_IMAGES) {
			for (int y = 0; y < pDoc->imageHeight; y++)   // 두번째 입력 영상 출력 
				for (int x = 0; x < pDoc->imageWidth; x++)
					pDC->SetPixel(x + pDoc->imageWidth + 30, y,
						RGB(pDoc->inputImg2[y][3 * x],
							pDoc->inputImg2[y][3 * x + 1],
							pDoc->inputImg2[y][3 * x + 2]));
			for (int y = 0; y < pDoc->imageHeight; y++)       // 결과 영상 출력 
				for (int x = 0; x < pDoc->imageWidth; x++)
					pDC->SetPixel(x + pDoc->imageWidth * 2 + 60, y,
						RGB(pDoc->resultImg[y][3 * x],
							pDoc->resultImg[y][3 * x + 1],
							pDoc->resultImg[y][3 * x + 2]));
		}

		else if (viewMode == TWO_IMAGES_SCALED) {
			for (int y = 0; y < pDoc->gImageHeight; y++)   // 크기가 변한 결과 영상 출력 
				for (int x = 0; x < pDoc->gImageWidth; x++)
					pDC->SetPixel(x + pDoc->imageWidth + 30, y,
						RGB(pDoc->gResultImg[y][3 * x],
							pDoc->gResultImg[y][3 * x + 1],
							pDoc->gResultImg[y][3 * x + 2]));
		}

		else {
			for (int y = 0; y < pDoc->imageHeight; y++)       // 결과 영상 출력 
				for (int x = 0; x < pDoc->imageWidth; x++)
					pDC->SetPixel(x + pDoc->imageWidth + 30, y,
						RGB(pDoc->resultImg[y][3 * x],
							pDoc->resultImg[y][3 * x + 1],
							pDoc->resultImg[y][3 * x + 2]));
		}
	}
}



	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.


void CImageProYooSeHyeokView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = 2048;     // 수정된 코드 
	sizeTotal.cy = 1024;     // 수정된 코드 

	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CImageProYooSeHyeokView 인쇄


void CImageProYooSeHyeokView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImageProYooSeHyeokView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CImageProYooSeHyeokView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CImageProYooSeHyeokView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CImageProYooSeHyeokView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CImageProYooSeHyeokView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CImageProYooSeHyeokView 진단

#ifdef _DEBUG
void CImageProYooSeHyeokView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImageProYooSeHyeokView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImageProYooSeHyeokDoc* CImageProYooSeHyeokView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProYooSeHyeokDoc)));
	return (CImageProYooSeHyeokDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageProYooSeHyeokView 메시지 처리기


void CImageProYooSeHyeokView::OnPixelAdd()
{
	CImageProYooSeHyeokDoc* pDoc = GetDocument();     // 문장 1 : pDoc 변수 선언 
	pDoc = GetDocument();   // 문장 2 : 문서 객체에 대한 포인터 획득 
	ASSERT_VALID(pDoc);    // 문장 3 : pDoc 변수의 오류 검증 

	if (pDoc->inputImg == NULL) return; // 추가된 문장: 입력 영상이 있는지 검사 


	pDoc->PixelAdd();     // 문장 4 : 문서 객체의 PointAdd() 함수 호출 

	viewMode = TWO_IMAGES;
	Invalidate(FALSE);     // 문장 5 : 화면을 다시 그림 


	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProYooSeHyeokView::OnPixelReverse()
{
	CImageProYooSeHyeokDoc* pDoc = GetDocument();    // 문장 1 : pDoc 변수 선언 
	pDoc = GetDocument();   // 문장 2 : 문서 객체에 대한 포인터 획득 
	ASSERT_VALID(pDoc);    // 문장 3 : pDoc 변수의 오류 검증 
	if (pDoc->inputImg == NULL) return; // 추가된 문장: 입력 영상이 있는지 검사
	pDoc->PixelReverse();     // 문장 4 : 문서 객체의 PointAdd() 함수 호출 

	viewMode = TWO_IMAGES;
	Invalidate(FALSE);     // 문장 5 : 화면을 다시 그림 



	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProYooSeHyeokView::OnPixelMinus()
{
	CImageProYooSeHyeokDoc* pDoc = GetDocument();// 문장 1 : pDoc 변수 선언 
	pDoc = GetDocument();   // 문장 2 : 문서 객체에 대한 포인터 획득 
	ASSERT_VALID(pDoc);    // 문장 3 : pDoc 변수의 오류 검증 
	if (pDoc->inputImg == NULL) return; // 추가된 문장: 입력 영상이 있는지 검사
	pDoc->PixelMinus();     // 문장 4 : 문서 객체의 PointAdd() 함수 호출 

	viewMode = TWO_IMAGES;
	Invalidate(FALSE);     // 문장 5 : 화면을 다시 그림 

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProYooSeHyeokView::OnPixelMultiple()
{
	CImageProYooSeHyeokDoc* pDoc = GetDocument();// 문장 1 : pDoc 변수 선언 
	pDoc = GetDocument();   // 문장 2 : 문서 객체에 대한 포인터 획득 
	ASSERT_VALID(pDoc);    // 문장 3 : pDoc 변수의 오류 검증 
	if (pDoc->inputImg == NULL) return; // 추가된 문장: 입력 영상이 있는지 검사
	pDoc->PixelMultiple();     // 문장 4 : 문서 객체의 PointAdd() 함수 호출 

	viewMode = TWO_IMAGES;
	Invalidate(FALSE);     // 문장 5 : 화면을 다시 그림 
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProYooSeHyeokView::OnPixelDiv()
{
	CImageProYooSeHyeokDoc* pDoc = GetDocument();// 문장 1 : pDoc 변수 선언 
	pDoc = GetDocument();   // 문장 2 : 문서 객체에 대한 포인터 획득 
	ASSERT_VALID(pDoc);    // 문장 3 : pDoc 변수의 오류 검증 
	if (pDoc->inputImg == NULL) return; // 추가된 문장: 입력 영상이 있는지 검사
	pDoc->PixelDiv();     // 문장 4 : 문서 객체의 PointAdd() 함수 호출 

	viewMode = TWO_IMAGES;
	Invalidate(FALSE);     // 문장 5 : 화면을 다시 그림 
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProYooSeHyeokView::OnPixelRe()
{
	CImageProYooSeHyeokDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);// 문장 1 : pDoc 변수 선언 
	pDoc = GetDocument();   // 문장 2 : 문서 객체에 대한 포인터 획득 
	ASSERT_VALID(pDoc);    // 문장 3 : pDoc 변수의 오류 검증 
	if (pDoc->inputImg == NULL) return; // 추가된 문장: 입력 영상이 있는지 검사
	pDoc->PixelRe();     // 문장 4 : 문서 객체의 PointAdd() 함수 호출 

	viewMode = TWO_IMAGES;
	Invalidate(FALSE);     // 문장 5 : 화면을 다시 그림 
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProYooSeHyeokView::OnPixelHistoEq()
{
	CImageProYooSeHyeokDoc* pDoc = GetDocument();// 문장 1 : pDoc 변수 선언 
	pDoc = GetDocument();   // 문장 2 : 문서 객체에 대한 포인터 획득 
	ASSERT_VALID(pDoc);    // 문장 3 : pDoc 변수의 오류 검증 
	if (pDoc->inputImg == NULL) return; // 추가된 문장: 입력 영상이 있는지 검사
	pDoc->PixelHistoEq();     // 문장 4 : 문서 객체의 PointAdd() 함수 호출 

	viewMode = TWO_IMAGES;
	Invalidate(FALSE);     // 문장 5 : 화면을 다시 그림 

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProYooSeHyeokView::OnContrastSt()
{
	CImageProYooSeHyeokDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->inputImg == NULL) return; // 추가된 문장: 입력 영상이 있는지 검사

	pDoc->ContrastSt();

	viewMode = TWO_IMAGES;
	Invalidate(FALSE);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProYooSeHyeokView::OnPixelTwoImageAdd()
{
	CImageProYooSeHyeokDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->inputImg == NULL) return; // 추가된 문장: 입력 영상이 있는지 검사

	pDoc->PixelTwoImageAdd();

	viewMode = THREE_IMAGES;

	Invalidate(FALSE);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProYooSeHyeokView::OnPixelTwoImageMinus()
{
	CImageProYooSeHyeokDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL) return; // 추가된 문장: 입력 영상이 있는지 검사
	
	pDoc->PixelTwoImageMinus();

	viewMode = THREE_IMAGES;

	Invalidate(FALSE);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProYooSeHyeokView::OnRegionSharpening() //선명화
{
	CImageProYooSeHyeokDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL) return; // 추가된 문장: 입력 영상이 있는지 검사

	pDoc->RegionSharpening();

	viewMode = TWO_IMAGES;

	Invalidate(FALSE);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CImageProYooSeHyeokView::OnRegionBluring()
{
	CImageProYooSeHyeokDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL) return; // 추가된 문장: 입력 영상이 있는지 검사

	pDoc->RegionBluring();

	viewMode = TWO_IMAGES;

	Invalidate(FALSE);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProYooSeHyeokView::OnErosion()
{
	CImageProYooSeHyeokDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL) return; // 추가된 문장: 입력 영상이 있는지 검사

	pDoc->Erosion();

	viewMode = TWO_IMAGES;

	Invalidate(FALSE);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProYooSeHyeokView::OnDilation()
{
	CImageProYooSeHyeokDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL) return; // 추가된 문장: 입력 영상이 있는지 검사

	pDoc->Dilation();

	viewMode = TWO_IMAGES;

	Invalidate(FALSE);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProYooSeHyeokView::OnOpening()
{
	CImageProYooSeHyeokDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL) return; // 추가된 문장: 입력 영상이 있는지 검사

	pDoc->Opening();

	viewMode = TWO_IMAGES;

	Invalidate(FALSE);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProYooSeHyeokView::OnClosing()
{
	CImageProYooSeHyeokDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL) return; // 추가된 문장: 입력 영상이 있는지 검사

	pDoc->Closing();

	viewMode = TWO_IMAGES;

	Invalidate(FALSE);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProYooSeHyeokView::OnRegionEdge()
{
	CImageProYooSeHyeokDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL) return; // 추가된 문장: 입력 영상이 있는지 검사

	pDoc->RegionEdge();

	viewMode = TWO_IMAGES;

	Invalidate(FALSE);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProYooSeHyeokView::OnGeometryZoominPixelCopy()
{
	CImageProYooSeHyeokDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL) return;

	pDoc->GeometryZoominPixelCopy();
	viewMode = TWO_IMAGES_SCALED;
	Invalidate(FALSE);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProYooSeHyeokView::OnGeometryZoominInterpolation()
{
	CImageProYooSeHyeokDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL) return;

	pDoc->GeometryZoominInterpolation();
	viewMode = TWO_IMAGES_SCALED;
	Invalidate(FALSE);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProYooSeHyeokView::OnGeometryZoomoutSubsampling()
{
	CImageProYooSeHyeokDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->inputImg == NULL) return;
	pDoc->GeometryZoomoutSubsampling();
	viewMode = TWO_IMAGES_SCALED;
	Invalidate(FALSE);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProYooSeHyeokView::OnGeometryZoomoutAvg()
{
	CImageProYooSeHyeokDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->inputImg == NULL) return;
	pDoc->GeometryZoomoutAvg();
	viewMode = TWO_IMAGES_SCALED;
	Invalidate(FALSE);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProYooSeHyeokView::OnGeometryRotate()
{
	CImageProYooSeHyeokDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->inputImg == NULL) return;
	pDoc->GeometryRotate();
	viewMode = TWO_IMAGES_SCALED;
	Invalidate(FALSE);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProYooSeHyeokView::OnGeometryWarping()
{
	CImageProYooSeHyeokDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->GeometryWarping();
	viewMode = TWO_IMAGES;
	Invalidate(FALSE);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProYooSeHyeokView::OnGeometryMorphing() 
{
	CImageProYooSeHyeokDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->GeometryMorphing();
	viewMode = MORPHING;
	Invalidate(FALSE);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}
