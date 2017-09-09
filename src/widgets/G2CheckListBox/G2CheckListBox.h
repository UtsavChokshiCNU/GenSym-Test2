#include <afxwin.h>
#include "dyndlgs.h"

class CG2CheckListBox : public CCheckListBox
{

  // Construction
public:


  void set_up_check_listbox(CG2CheckListBox *pListBox, CONTROLITEM *pcontrol, int update_type);

protected:
	virtual void PostNcDestroy();

};