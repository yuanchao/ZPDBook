#ifndef ZPDG_H
#define ZPDG_H
#include "zpdgbase.h"

class ZPDG : public ZPDGBase
{ 
    Q_OBJECT

public:
    ZPDG( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~ZPDG();

public slots:
    void doSearch();
    void doSelect(int);
    void goDecay(QListBoxItem*);

};

typedef struct PTRECORD{
  int pid;
  double mass;
  double mass_errp;
  double mass_errm;
  double width;
  double width_errp;
  double width_errm;
  char name[32];
  char charge[4];
}PTRECORD;

#endif // ZPDG_H
