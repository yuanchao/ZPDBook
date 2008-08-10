#include "zpdg.h"
#include <qpe/qpeapplication.h>

int main( int argc, char ** argv )
{
    QPEApplication a( argc, argv );

    ZPDG mw;
    a.showMainWidget( &mw );

    return a.exec();
}
