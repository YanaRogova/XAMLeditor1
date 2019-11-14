
// XAMLeditorView.h: интерфейс класса CXAMLeditorView
//

#pragma once


class CXAMLeditorView : public CView
{
protected: // создать только из сериализации
	CXAMLeditorView() noexcept;
	DECLARE_DYNCREATE(CXAMLeditorView)

// Атрибуты
public:
	CXAMLeditorDoc* GetDocument() const;

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Реализация
public:
	virtual ~CXAMLeditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // версия отладки в XAMLeditorView.cpp
inline CXAMLeditorDoc* CXAMLeditorView::GetDocument() const
   { return reinterpret_cast<CXAMLeditorDoc*>(m_pDocument); }
#endif

