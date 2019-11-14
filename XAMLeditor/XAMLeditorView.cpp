
// XAMLeditorView.cpp: реализация класса CXAMLeditorView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "XAMLeditor.h"
#endif

#include "XAMLeditorDoc.h"
#include "XAMLeditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CXAMLeditorView

IMPLEMENT_DYNCREATE(CXAMLeditorView, CView)

BEGIN_MESSAGE_MAP(CXAMLeditorView, CView)
END_MESSAGE_MAP()

// Создание или уничтожение CXAMLeditorView

CXAMLeditorView::CXAMLeditorView() noexcept
{
	// TODO: добавьте код создания
}

CXAMLeditorView::~CXAMLeditorView()
{
}

BOOL CXAMLeditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование CXAMLeditorView

void CXAMLeditorView::OnDraw(CDC* /*pDC*/)
{
	CXAMLeditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: добавьте здесь код отрисовки для собственных данных
}


// Диагностика CXAMLeditorView

#ifdef _DEBUG
void CXAMLeditorView::AssertValid() const
{
	CView::AssertValid();
}

void CXAMLeditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CXAMLeditorDoc* CXAMLeditorView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CXAMLeditorDoc)));
	return (CXAMLeditorDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CXAMLeditorView
