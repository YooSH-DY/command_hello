
// ImagePro_YooSeHyeokView.h: CImageProYooSeHyeokView 클래스의 인터페이스
//


#pragma once


class CImageProYooSeHyeokView : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CImageProYooSeHyeokView() noexcept;
	DECLARE_DYNCREATE(CImageProYooSeHyeokView)

// 특성입니다.
public:
	CImageProYooSeHyeokDoc* GetDocument() const;
	int viewMode; //영상출력모드 

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CImageProYooSeHyeokView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPixelAdd();
	afx_msg void OnPixelReverse();
	afx_msg void OnPixelMinus();
	afx_msg void OnPixelMultiple();
	afx_msg void OnPixelDiv();
	afx_msg void OnPixelRe();
	afx_msg void OnPixelHistoEq();
	afx_msg void OnContrastSt();
	afx_msg void OnPixelTwoImageAdd();
	afx_msg void OnPixelTwoImageMinus();
	afx_msg void OnRegionSharpening();
	afx_msg void OnImageBluring();
	afx_msg void OnRegionBluring();
	afx_msg void OnErosion();
	afx_msg void OnDilation();
	afx_msg void OnOpening();
	afx_msg void OnClosing();
	afx_msg void OnRegionEdge();
	afx_msg void OnGeometryZoominPixelCopy();
	afx_msg void OnGeometryZoominInterpolation();
	afx_msg void OnGeometryZoomoutSubsampling();
	afx_msg void OnGeometryZoomoutAvg();
	afx_msg void OnGeometryRotate();
	afx_msg void OnGeometryWarping();
	afx_msg void OnGeometryMorphing();
};

#ifndef _DEBUG  // ImagePro_YooSeHyeokView.cpp의 디버그 버전
inline CImageProYooSeHyeokDoc* CImageProYooSeHyeokView::GetDocument() const
   { return reinterpret_cast<CImageProYooSeHyeokDoc*>(m_pDocument); }
#endif

