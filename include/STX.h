#pragma once
#ifndef _STX_H_
#define _STX_H_


#ifdef _STXDLL_
#define STX_EXT_CLASS _declspec(dllexport) 
#else	
#define STX_EXT_CLASS _declspec(dllimport) 
#endif


#endif