      program quikb
C  quick response commands     <910330.0053>
C
C QUIKR is the root for all quick-response applications
C              functions in the Field System
C
C     INPUT VARIABLES:
C         IP(1) - class number containing invocation line
C         IP(2) - branch number, encoded
C
C     OUTPUT VARIABLES:
C         IP(1) - class number, if any
C         IP(2) - number of records in class
C         IP(3) - IERR error code return
C         IP(4) - who caused the error
C
C     COMMON BLOCKS USED
      include '../include/fscom.i'
C
C 3.  LOCAL VARIABLES
      integer*4 ip(5)                     !  rmpar variables
      integer idum,fc_rte_prior
C
C 6.  PROGRAMMERS: NRV (1980), LEF (1987), LAR (1988)
C  WHO  WHEN    DESCRIPTION
C  GAG  910116  Added calls to WEH's new tape head calibration routines.
C  GAG  910124  Removed callS to LOWHI and PARTN.
C  GAG  910205  Rejoined QUIK1 and QUIK2 into this one file.
C
C     PROGRAM STRUCTURE :
C  Get RMPAR parameters, then call the subroutine whose number is in IP(2).
C
      call setup_fscom
      call read_fscom
      idum=fc_rte_prior(FS_PRIOR)
1     continue
      call wait_prog('quikb',ip)
      call read_quikr
      isub = ip(2)/100
      itask = ip(2) - 100*isub
      if (isub.eq.7) then
        if (itask.eq.1) then
          call reset(ip)
        else if (itask.eq.2) then
          call newtp(ip)
        else if (itask.eq.3) then
          call label(ip)
        else if (itask.eq.4) then
          call matld(ip)
        end if
      else if (isub.eq.8) then
        call ena(ip)
      else if (isub.eq.9) then
        if (itask.eq.1) then
          call de(ip)
        else if (itask.eq.2) then
          call pe(ip)
        else if (itask.eq.3) then
          call party(ip)
        endif
      else if (isub.eq.10) then
        call repro(ip)
      else if (isub.eq.11) then
        if (itask.eq.1) then
          call sorce(ip)
        else if (itask.eq.2) then
          call rdoff(ip)
        else if (itask.eq.3) then
          call aeoff(ip)
        else if (itask.eq.4) then
          call onsor(ip)
        else if (itask.eq.6) then
          call xyoff(ip)
        else if (itask.eq.7) then
          call track(ip)
        endif
      else if (isub.eq.12) then
        if (itask.eq.1.or.itask.eq.2) then
          call ctemp(ip,itask)
        else if (itask.eq.5.or.itask.eq.6) then
          call tsys(ip,itask)
        else
          call tpi(ip,itask)
        endif
      endif

      call write_quikr

      goto 1

      end
