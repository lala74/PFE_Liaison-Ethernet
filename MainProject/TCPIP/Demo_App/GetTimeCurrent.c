 /****************************************************************************
   Function:
     DWORD   PIC24RTCCGetDate( void )
 
   Description:
     This routine reads the date from the RTCC module.
 
   Precondition:
     The RTCC module has been initialized.
 
 
   Parameters:
     None
 
   Returns:
     DWORD in the format <xx><YY><MM><DD>
 
   Remarks:
     To catch roll-over, we do two reads.  If the readings match, we return
     that value.  If the two do not match, we read again until we get two
     matching values.
 
     For the PIC32MX, we use library routines, which return the date in the
     PIC32MX format.
   ***************************************************************************/
 
 #if defined( __C30__ )
 DWORD PIC24RTCCGetDate( void ) {
   DWORD_VAL   date1;
   DWORD_VAL   date2;
 
   do {
     while (RCFGCALbits.RTCSYNC);
 
     RCFGCALbits.RTCPTR0 = 1;
     RCFGCALbits.RTCPTR1 = 1;
     date1.w[1] = RTCVAL;
     date1.w[0] = RTCVAL;
 
     RCFGCALbits.RTCPTR0 = 1;
     RCFGCALbits.RTCPTR1 = 1;
     date2.w[1] = RTCVAL;
     date2.w[0] = RTCVAL;
 
     } while (date1.Val != date2.Val);
 
   return date1.Val;
     }
 #endif
 
 
 /****************************************************************************
   Function:
     DWORD   PIC24RTCCGetTime( void )
 
   Description:
     This routine reads the time from the RTCC module.
 
   Precondition:
     The RTCC module has been initialized.
 
   Parameters:
     None
 
   Returns:
     DWORD in the format <xx><HH><MM><SS>
 
   Remarks:
     To catch roll-over, we do two reads.  If the readings match, we return
     that value.  If the two do not match, we read again until we get two
     matching values.
 
     For the PIC32MX, we use library routines, which return the time in the
     PIC32MX format.
   ***************************************************************************/
 
 #if defined( __C30__ )
 DWORD PIC24RTCCGetTime( void ) {
   DWORD_VAL   time1;
   DWORD_VAL   time2;
 
   do {
     while (RCFGCALbits.RTCSYNC);
 
     RCFGCALbits.RTCPTR0 = 1;
     RCFGCALbits.RTCPTR1 = 0;
     time1.w[1] = RTCVAL;
     time1.w[0] = RTCVAL;
 
     RCFGCALbits.RTCPTR0 = 1;
     RCFGCALbits.RTCPTR1 = 0;
     time2.w[1] = RTCVAL;
     time2.w[0] = RTCVAL;
 
     } while (time1.Val != time2.Val);
 
     return time1.Val;
     }
 #endif
 
 
 /****************************************************************************
   Function:
     void PIC24RTCCSetDate( WORD xx_year, WORD month_day )
 
   Description:
     This routine sets the RTCC date to the specified value.
 
 
   Precondition:
     The RTCC module has been initialized.
 
   Parameters:
     WORD xx_year    - BCD year in the lower byte
     WORD month_day  - BCD month in the upper byte, BCD day in the lower byte
 
   Returns:
     None
 
   Remarks:
     For the PIC32MX, we use library routines.
   ***************************************************************************/
 
 #if defined( __C30__ )
 void PIC24RTCCSetDate( WORD xx_year, WORD month_day ) {
   
     UnlockRTCC();
   RCFGCALbits.RTCPTR0 = 1;
   RCFGCALbits.RTCPTR1 = 1;
   RTCVAL = xx_year;
   RTCVAL = month_day;
     }
 #endif
 
 
 /****************************************************************************
   Function:
     void PIC24RTCCSetTime( WORD weekDay_hours, WORD minutes_seconds )
 
   Description:
     This routine sets the RTCC time to the specified value.
 
   Precondition:
     The RTCC module has been initialized.
 
   Parameters:
     WORD weekDay_hours      - BCD weekday in the upper byte, BCD hours in the
                                 lower byte
     WORD minutes_seconds    - BCD minutes in the upper byte, BCD seconds in
                                 the lower byte
 
   Returns:
     None
 
   Remarks:
     For the PIC32MX, we use library routines.
   ***************************************************************************/
 
 #if defined( __C30__ )
 void PIC24RTCCSetTime( WORD weekDay_hours, WORD minutes_seconds) {
 
   UnlockRTCC();
   RCFGCALbits.RTCPTR0 = 1;
   RCFGCALbits.RTCPTR1 = 0;
   RTCVAL = weekDay_hours;
   RTCVAL = minutes_seconds;
     }
 #endif
 
 /****************************************************************************
   Function:
     void UnlockRTCC( void )
 
   Description:
     This function unlocks the RTCC so we can write a value to it.
 
   Precondition:
     None
 
   Parameters:
     None
 
   Return Values:
     None
 
   Remarks:
     For the PIC32MX, we use library routines.
   ***************************************************************************/
 
 #define RTCC_INTERRUPT_REGISTER IEC3
 #define RTCC_INTERRUPT_VALUE    0x2000
 
 #if defined( __C30__ )
 void UnlockRTCC( void ) {
   BOOL interruptsWereOn;
 
   interruptsWereOn = FALSE;
   if((RTCC_INTERRUPT_REGISTER & RTCC_INTERRUPT_VALUE) == RTCC_INTERRUPT_VALUE) {
     interruptsWereOn = TRUE;
     RTCC_INTERRUPT_REGISTER &= ~RTCC_INTERRUPT_VALUE;
     }
 
   // Unlock the RTCC module
   __asm__ ("mov #NVMKEY,W0");
   __asm__ ("mov #0x55,W1");
   __asm__ ("mov #0xAA,W2");
   __asm__ ("mov W1,[W0]");
   __asm__ ("nop");
   __asm__ ("mov W2,[W0]");
   __asm__ ("bset RCFGCAL,#13");
   __asm__ ("nop");
   __asm__ ("nop");
 
   if(interruptsWereOn) {
     RTCC_INTERRUPT_REGISTER |= RTCC_INTERRUPT_VALUE;
     }
     }
 #endif