*
* Copyright (c) 2020 NVI, Inc.
*
* This file is part of VLBI Field System
* (see http://github.com/nvi-inc/fs).
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
      integer function jr2as(re,lbuf,icn,it,id,isbuf)

      real re
      integer*2 lbuf(1)
      integer icn,it,id,isbuf
      integer ir2as
C
      jr2as=ir2as(re,lbuf,icn,it,id)
      if (.not.jchar(lbuf,icn).eq.36) return
      ita=min0(iabs(it)+iabs(id)+1,isbuf*2-icn+1)
      jr2as=ir2as(re,lbuf,icn,ita,id) 
      jr2as=iabs(it)

      return
      end 
