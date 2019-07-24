      subroutine scmd(lcmd,iwcmd,mcmd,ierr)
C
      integer it(5)
      integer*2 lcmd(1)
      integer*4 ip(5)
      logical kbreak,rn_test
C
      if (kbreak('aquir')) goto 200
      if (iwcmd.le.-2) goto 100
      nchars=iflch(lcmd,mcmd*2)
      if(iwcmd.eq.-1) call clear_prog('aquir')
      call copin(lcmd,nchars)
      if(iwcmd.eq.-1) goto 110
      call susp(2,2)
C
      call fc_rte_time(it,idum)
      tim=float(it(4))*3600.+float(it(3))*60.+float(it(2))
C
10    continue
      if (kbreak('aquir')) goto 200
      if(.not.rn_test('fs   ')) then
         ierr=-2
         return
      endif
C
      call fc_rte_time(it,idum)
      tim2=float(it(4))*3600.+float(it(3))*60.+float(it(2)) 
      if (tim2.lt.tim) tim2=tim2+86400.
      if (tim2.ge.tim+iwcmd) goto 100
      call susp(2,2)
      goto 10
C
100   continue
      ierr=0
      return
C
110   continue
      call wait_prog('aquir',ip)
      goto 100
c
200   continue
      ierr=-1
C
      return
      end
