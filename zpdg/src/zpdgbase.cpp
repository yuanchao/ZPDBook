/****************************************************************************
** Form implementation generated from reading ui file 'zpdgbase.ui'
**
** Created: Thu Jul 20 01:18:11 2006
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "zpdgbase.h"

#include <qgroupbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qlistbox.h>
#include <qmultilineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qvariant.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/* 
 *  Constructs a ZPDGBase which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 */
ZPDGBase::ZPDGBase( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "ZPDGBase" );
    resize( 231, 314 ); 
    setCaption( tr( "ZPDBooklet" ) );
    ZPDGBaseLayout = new QGridLayout( this ); 
    ZPDGBaseLayout->setSpacing( 3 );
    ZPDGBaseLayout->setMargin( 3 );

    Layout16 = new QVBoxLayout; 
    Layout16->setSpacing( 0 );
    Layout16->setMargin( 0 );

    lb_particles = new QListBox( this, "lb_particles" );
    lb_particles->insertItem( tr( "None" ) );
    lb_particles->setHScrollBarMode( QListBox::AlwaysOff );
    Layout16->addWidget( lb_particles );

    ed_particle = new QLineEdit( this, "ed_particle" );
    Layout16->addWidget( ed_particle );

    bt_search = new QPushButton( this, "bt_search" );
    bt_search->setText( tr( "Search" ) );
    Layout16->addWidget( bt_search );

    ZPDGBaseLayout->addLayout( Layout16, 0, 0 );

    Layout18 = new QVBoxLayout; 
    Layout18->setSpacing( 0 );
    Layout18->setMargin( 0 );

    tl_pid = new QLabel( this, "tl_pid" );
    tl_pid->setText( tr( "PID: 000000 J: 0.5\n"
"Charges: 00" ) );
    Layout18->addWidget( tl_pid );

    gb_mass = new QGroupBox( this, "gb_mass" );
    gb_mass->setTitle( tr( "Mass:" ) );
    gb_mass->setColumnLayout(0, Qt::Vertical );
    gb_mass->layout()->setSpacing( 0 );
    gb_mass->layout()->setMargin( 0 );
    gb_massLayout = new QVBoxLayout( gb_mass->layout() );
    gb_massLayout->setAlignment( Qt::AlignTop );
    gb_massLayout->setSpacing( 0 );
    gb_massLayout->setMargin( 3 );

    ed_mass = new QLineEdit( gb_mass, "ed_mass" );
    gb_massLayout->addWidget( ed_mass );

    ed_massp = new QLineEdit( gb_mass, "ed_massp" );
    gb_massLayout->addWidget( ed_massp );

    ed_massm = new QLineEdit( gb_mass, "ed_massm" );
    gb_massLayout->addWidget( ed_massm );
    Layout18->addWidget( gb_mass );

    gb_width = new QGroupBox( this, "gb_width" );
    gb_width->setTitle( tr( "Width:" ) );
    gb_width->setColumnLayout(0, Qt::Vertical );
    gb_width->layout()->setSpacing( 0 );
    gb_width->layout()->setMargin( 0 );
    gb_widthLayout = new QVBoxLayout( gb_width->layout() );
    gb_widthLayout->setAlignment( Qt::AlignTop );
    gb_widthLayout->setSpacing( 0 );
    gb_widthLayout->setMargin( 3 );

    ed_width = new QLineEdit( gb_width, "ed_width" );
    gb_widthLayout->addWidget( ed_width );

    ed_widthp = new QLineEdit( gb_width, "ed_widthp" );
    gb_widthLayout->addWidget( ed_widthp );

    ed_widthm = new QLineEdit( gb_width, "ed_widthm" );
    gb_widthLayout->addWidget( ed_widthm );
    Layout18->addWidget( gb_width );

    ZPDGBaseLayout->addLayout( Layout18, 0, 1 );

    ed_memo = new QMultiLineEdit( this, "ed_memo" );
    ed_memo->setReadOnly( TRUE );

    ZPDGBaseLayout->addMultiCellWidget( ed_memo, 1, 1, 0, 1 );

    // signals and slots connections
    connect( bt_search, SIGNAL( clicked() ), this, SLOT( doSearch() ) );
    connect( ed_particle, SIGNAL( returnPressed() ), this, SLOT( doSearch() ) );
    connect( lb_particles, SIGNAL( selected(QListBoxItem*) ), this, SLOT( goDecay(QListBoxItem*) ) );
    connect( lb_particles, SIGNAL( highlighted(int) ), this, SLOT( doSelect(int) ) );
    connect( lb_particles, SIGNAL( clicked(QListBoxItem*) ), this, SLOT( goDecay(QListBoxItem*) ) );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
ZPDGBase::~ZPDGBase()
{
    // no need to delete child widgets, Qt does it all for us
}

void ZPDGBase::doSearch()
{
    qWarning( "ZPDGBase::doSearch(): Not implemented yet!" );
}

void ZPDGBase::doSelect(int)
{
    qWarning( "ZPDGBase::doSelect(int): Not implemented yet!" );
}

void ZPDGBase::goDecay(QListBoxItem*)
{
    qWarning( "ZPDGBase::goDecay(QListBoxItem*): Not implemented yet!" );
}

