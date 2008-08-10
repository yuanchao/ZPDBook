#include "zpdg.h"
#include <qmessagebox.h>
#include <qstring.h>
#include <qlistbox.h>
#include <qlineedit.h>
#include <qmultilineedit.h>
#include <qlabel.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//std::List<PTRECORD> m_records;
struct PTRECORD m_records[512];

FILE *datafile;

int pids[4], last_pid, i, j;
int m_num_ptl=0;
char charges[16], *m_charge;
char buf1[256], buf2[256], m_name[32];
char buff[256*5]="";
double m_value, m_errp, m_errm;

/* 
 *  Constructs a ZPDG which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 */
ZPDG::ZPDG( QWidget* parent,  const char* name, WFlags fl )
    : ZPDGBase( parent, name, fl )
{
//    QMessageBox::about( this, "About",
//                              "<p>This program shows PDG data" );

  datafile=fopen("/home/QtPalmtop/pics/zpdg/mass_width.mc", "r");
  //datafile=fopen("/opt/Qtopia/share/zpdg/mass_width.mc", "r");
  //if(datafile==NULL){
  //  datafile=fopen("/mnt/card/opt/Qtopia/share/zpdg/mass_width.mc", "r");
  //}

  if(datafile!=NULL){
    while(!feof(datafile)){
      fgets(buff, 92, datafile);
      pids[0]=pids[1]=pids[2]=pids[3]=0;

      if(buff[0]=='M'||buff[0]=='W'){
        buff[33]='\0';
        sscanf(buff+1, "%8d%8d%8d%8d",
               &pids[0], &pids[1], &pids[2], &pids[3]);
        sscanf(buff+35, "%15lf %8lf %8lf", &m_value, &m_errp, &m_errm);
        sscanf(buff+68, "%s %s\n", m_name, charges);
        m_charge=strtok(charges, ",");
        if(pids[0]==last_pid && pids[0]!=0){
          i=m_num_ptl-j;
        }else{
          for(i=0;i<m_num_ptl&& pids[0]!=m_records[i].pid;i++);
        }

        if(i>=m_num_ptl){
          for(j=0; j<4&&pids[j]!=0; j++){
            m_records[i+j].pid=pids[j];
            strcpy(m_records[i+j].name, m_name);
            strcpy(m_records[i+j].charge, m_charge);
            m_records[i+j].mass=-1;
            m_records[i+j].width=-1;
            m_charge=strtok(NULL, ",");
          }
          last_pid=pids[0];
          m_num_ptl+=j;
        }
        if(buff[0]=='M'){
          for(j=0; j<4&&pids[j]!=0; j++){
            m_records[i+j].mass=m_value;
            m_records[i+j].mass_errp=m_errp;
            m_records[i+j].mass_errm=m_errm;
          }
        }else if(buff[0]=='W'){
          for(j=0; j<4&&pids[j]!=0; j++){
            m_records[i+j].width=m_value;
            m_records[i+j].width_errp=m_errp;
            m_records[i+j].width_errm=m_errm;
          }
        }

      }
    }
    m_num_ptl=i;

    fclose(datafile);
  }else{
    m_num_ptl=0;
    printf("Error opening data file...\n");
  }

    this->lb_particles->clear();
    for(int i=0; i<m_num_ptl; i++){
      //sprintf(buff, "%s%s", m_records[i].name, m_records[i].charge);
      QString qbuff(tr(m_records[i].name)+tr(m_records[i].charge));
      if(m_records[i].charge[0]=='0')
        qbuff=tr(m_records[i].name);
      
      this->lb_particles->insertItem(qbuff);
    }
    this->lb_particles->setSelected(0, TRUE);
    
}

/*  
 *  Destroys the object and frees any allocated resources
 */
ZPDG::~ZPDG()
{
    // no need to delete child widgets, Qt does it all for us
}

/* 
 * public slot
 */
void ZPDG::doSearch()
{
    //qWarning( "ZPDG::doSearch() not yet implemented!" ); 

    int i;
    int curr_idx=this->lb_particles->currentItem();
    double range1, range2;

    QString text=this->ed_particle->text();

    if(!text.isEmpty()){

      // Search mass range
      if( strstr(text.latin1(), "-") ){
        sscanf(text.latin1(), "%lf-%lf", &range1, &range2);
        if(range1>0 && range2>0){
          for(i=curr_idx+1; i<=m_num_ptl; i++){
            if( range1<=m_records[i].mass &&
                range2>=m_records[i].mass )
              break;
          }
          if(i>m_num_ptl){
            for(i=0; i<=m_num_ptl; i++){
              if( range1<=m_records[i].mass &&
                  range2>=m_records[i].mass )
                break;
            }
          }
        }
      }else if( text.toInt()>0 ){  // Search using PID
        for(i=0; i<=m_num_ptl; i++){
          if( text.toInt()==m_records[i].pid)
            break;
        }
      }else{	//Search using name
        for(i=curr_idx+1; i<=m_num_ptl; i++){
          if( strncasecmp(text.latin1(), m_records[i].name, text.length())==0)
              break;
        }
        if(i>m_num_ptl){
          for(i=0; i<=m_num_ptl; i++){
            if( strncasecmp(text.latin1(), m_records[i].name, text.length())==0)
              break;
          }
        }
      }
      if(i<=m_num_ptl){
        this->lb_particles->setCurrentItem(i);
        doSelect(i);
        this->ed_particle->setText(text);
      }else{
        this->ed_particle->setText(tr("Not Found!"));
      }
    }
    //SetFocus(GetDlgItem (hDlg, ID_EDIT_FIND));
    this->ed_particle->setFocus();

}
/* 
 * public slot
 */
void ZPDG::doSelect(int i)
{
  char buf[32];
//    qWarning( "ZPDG::doSelect(int) not yet implemented!" ); 
  this->ed_particle->setText(tr(m_records[i].name));

  sprintf(buf, "PID:%8d\nCharge: %2s", m_records[i].pid, m_records[i].charge);
  this->tl_pid->setText(QString(buf));

  sprintf(buf, "%G", m_records[i].mass);
  this->ed_mass->setText(QString(buf));

  sprintf(buf, "%G", m_records[i].mass_errp);
  this->ed_massp->setText(QString(buf));

  sprintf(buf, "%G", m_records[i].mass_errm);
  this->ed_massm->setText(QString(buf));

  sprintf(buf, "%G", m_records[i].width);
  this->ed_width->setText(QString(buf));

  sprintf(buf, "%G", m_records[i].width_errp);
  this->ed_widthp->setText(QString(buf));

  sprintf(buf, "%G", m_records[i].width_errm);
  this->ed_widthm->setText(QString(buf));

}
void ZPDG::goDecay(QListBoxItem* item)
{
//  qWarning( "ZPDG::goDecay(QListBoxItem*) not yet implemented!" );

  QString text;
  QString memo;

  char buff[256]="";
  char name[32]="";
  char dummy[128]="";

  int curr_idx=this->lb_particles->currentItem();

  this->ed_memo->clear();

  if( item ){
    text=item->text();
    this->ed_memo->setText("Searching");
  }else{
    return;
  }

  memo=memo+"        ID stable                                      min    max\n";
  memo=memo+"name   code code   mass  charge spin   c*tau    width  mass   mass\n";

  datafile=fopen("/home/QtPalmtop/pics/zpdg/decay.dec", "r");
  //datafile=fopen("/opt/Qtopia/share/zpdg/decay.dec", "r");
  //if(datafile==NULL){
  //  datafile=fopen("/mnt/card/opt/Qtopia/share/zpdg/decay.dec", "r");
  //}


  if(datafile!=NULL){
    fgets(buff, 92, datafile);

    while( !feof(datafile) && strncasecmp(buff, "PDG", 3)!=0 ){
      fgets(buff, 92, datafile);
    }

    while( !feof(datafile) && strncasecmp(buff, "DECAY", 5)!=0 ){
      if(strncasecmp(buff, "PDG", 3)==0 && name!=""){
        if(atoi(buff+17)==m_records[curr_idx].pid){
          sscanf(buff, "PDG       %s %s", name, dummy);
        }
      }
      fgets(buff, 92, datafile);
    }
 
    if(name[0]=='\0')
      return;

    rewind(datafile);

    while( !feof(datafile) && strncasecmp(buff, "PDG", 3)!=0 ){
      if(strncasecmp(buff, "PARTICLE", 8)==0 &&
         (strncasecmp(buff+9, name, strlen(name))==0 ||
          strncasecmp(buff+10, name, strlen(name))==0 ) ){
        memo=memo+QString(buff);
      }
      fgets(buff, 92, datafile);
    }

    while( !feof(datafile) && strncasecmp(buff, "DECAY", 5)!=0 ){
      fgets(buff, 92, datafile);
    }

    memo=memo+"\n";
    while( !feof(datafile) ){
      if( buff[0]!=';' && strncasecmp(buff+7, name, strlen(name))==0){
        memo=memo+QString(buff+7);
        while( !feof(datafile) && strncasecmp(buff, "ENDDECAY", 8)!=0){
          if( buff[0]!=';' )
            memo=memo+buff;
          fgets(buff, 92, datafile);
        }
        memo=memo+"\n";
      }
      fgets(buff, 92, datafile);
    }
  }else
    memo="File not found!";

  fclose(datafile);

  this->ed_memo->setText(memo);
  this->ed_memo->setCursorPosition(0, 0, FALSE);

}


