#ifndef _OFET_CTRL_H_
#define _OFET_CTRL_H_


BOOL  StartControlModule( );

BOOL  SetEventReportValue(BOOL  bValue);
BOOL  GetEventReportValue(BOOL* bValue);

BOOL  SetPrivilegeControlValue(BOOL  bValue);
BOOL  GetPrivilegeControlValue(BOOL* bValue);

BOOL  SetFakedExeCheckValue(BOOL  bValue);
BOOL  GetFakedExeCheckValue(BOOL* bValue);

BOOL  StopControlModule( );

#endif

