* logpl.ctl - Control file for LOGPL (originally named FREJA by Fredrik)
*
* 1. Command, the pattern logpl will grep the log file for.
* 2. Parameter, the number of comma-separated data field for the command,
*               a negative value means to take the value just after the
*               field with "String"
* 3. Description, the menu label logpl will use for the command.
* 4. String, a level-2 grep. This parameter is optional and may be left out,
*            for negative "Paramter" values, it is the string before the
*            data field
*
* NB! This file is space-separated, i.e., no field may contain spaces.
*
*
* 1:Command     2:Parameter   3:Description     4:String
* -------------------------------------------------------------------------
*
  wx/           1             Temperature
  wx/           2             Pressure
  wx/           3             Humidity
  cable/        1             Cable-length
  rx/           9             rx-9-front        (front)
  rx/           9             rx-9-lo           (lo)
  rx/           9             rx-9-pres         (pres)
  rx/           9             rx-9-20k          (20k)
  tsys/        -1             tsys-i1           i1
  tsys/        -1             tsys-i2           i2
  "             0             Comments
*
*
