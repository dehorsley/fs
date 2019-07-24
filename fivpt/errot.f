      subroutine errot(lmess,mchars,eltpar,ltrchi,lbuf,isbuf) 
      real ltrchi 
      dimension eltpar(5)
      integer*2 lbuf(1),lmess(1) 
C 
C WRITE XXXERR LOG ENTRY
C 
       include '../include/fscom.i'
C 
C INPUT:
C 
C       ELTPAR = ARRAY OF ERRORS IN THE FIT PARAMETERS
C 
C       LTRCHI = REDUCED CHI OF THE FIT 
C 
C XXXERR LOG ENTRY IDENTIFIER 
C 
      icnext=1 
      icnext=ichmv(lbuf,icnext,lmess,1,mchars) 
      icnext=ichmv(lbuf,icnext,2H  ,1,1) 
C 
C SIGMA OFFSET
C 
      icnext=icnext+jr2as(eltpar(2)*180.0/pi,lbuf,icnext,-9,5,isbuf)   
      icnext=ichmv(lbuf,icnext,2H  ,1,1) 
C 
C SIGMA HALF-WIDTH
C 
      icnext=icnext+jr2as(eltpar(3)*180.0/pi,lbuf,icnext,-7,4,isbuf) 
      icnext=ichmv(lbuf,icnext,2H  ,1,1) 
C 
C TEMPERATURE PEAK SIGMA
C 
      icnext=icnext+jr2as(eltpar(1),lbuf,icnext,-7,4,isbuf)  
      icnext=ichmv(lbuf,icnext,2H  ,1,1) 
C 
C SIGMA TEMPERATURE OFFSET
C 
      icnext=icnext+jr2as(eltpar(4),lbuf,icnext,-7,4,isbuf)  
      icnext=ichmv(lbuf,icnext,2H  ,1,1) 
C 
C SIGMA TEMPERATURE SLOPE 
C 
      icnext=icnext+jr2as(eltpar(5),lbuf,icnext,-7,4,isbuf)  
      icnext=ichmv(lbuf,icnext,2H  ,1,1) 
C 
C REDUCED CHI 
C 
      icnext=icnext+jr2as(ltrchi,lbuf,icnext,-8,4,isbuf)     
      icnext=ichmv(lbuf,icnext,2H  ,1,1)  
C 
C CLEAN UP AND SEND DATA
C 
      nchars=icnext-1 
      if (1.ne.mod(icnext,2)) icnext=ichmv(lbuf,icnext,2H  ,1,1) 
      call logit2(lbuf,nchars) 

      return
      end 
