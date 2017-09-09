// MyCEdit.h : header file
//

#pragma once

#define UPPER_LIMIT_UNDEFINED -1

class CMyCEdit : public CEdit
{
public:
  CMyCEdit();

public:
  void SetUpperLimit (int HighVal);
  void SendNotifyOnChange ();

public:
  virtual void SetSpunValue (int val);
  virtual void SetTypedValue (LPCTSTR current_string);
  virtual void SetProgrammaticValue (LPTSTR current_string);

public:
  virtual ~CMyCEdit ();

protected:
  virtual void PostNcDestroy();

protected:
  afx_msg void OnSetFocus (CWnd *pOldWnd);
  afx_msg void OnUpdate ();
  afx_msg void OnKillFocus (CWnd *pNewWnd);
  DECLARE_MESSAGE_MAP()

private:
  int m_upper_limit;
  long m_last_value;
};
