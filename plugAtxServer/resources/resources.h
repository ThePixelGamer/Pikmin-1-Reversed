//{{NO_DEPENDENCIES}}
// Microsoft Developer Studio generated include file.
// Used by sysbootup.rc
//
#include <windows.h>

// <MENUS>
	#define EDITOR_ICONS 115
	#define EDITOR_MENU 102
		#define EDITOR_MENU_NEW     40003
		#define EDITOR_MENU_OPEN    40011
		#define EDITOR_MENU_SAVE    40022
		#define EDITOR_MENU_CLOSE   40012
		#define EDITOR_MENU_EXPORT  40023
		#define EDITOR_MENU_EXIT    40004

	#define MODVIEW_MENU 113
		// POPUP "view type"
			#define MODVIEW_TYPE_WF 40017 // Wireframe
			#define MODVIEW_TYPE_SF 40018 // Solid Face
			#define MODVIEW_TYPE_TX 40019 // Textured
		
		#define MODVIEW_SHOW        65535
		#define MODVIEW_VISGRID     40020 // Grid Visible

	#define BLAH_MENU 111
		#define BLAH_MENU_NEWCMD    40005 // New Command
		// The name of these items are actually keyboard spam
		#define BLAH_MENU_A         40006
		#define BLAH_MENU_B         40007
		#define BLAH_MENU_C         40008
		#define BLAH_MENU_D         40009

	#define FOO_MENU 114
		#define FOO_BLAH1           40024
// </MENUS>

// <STRING TABLES>
	#define STRTBL_VEMODE 40001 // Vertex Editing Mode
	#define STRTBL_EEMODE 40003 // Edge Editing Mode
	#define STRTBL_FEMODE 40004 // Face Editing Mode

	#define STRTBL_LXAXIS 40002 // Lock/Unlock X Axis
	#define STRTBL_LYAXIS 40028 // Lock/Unlock Y Axis
	#define STRTBL_LZAXIS 40006 // Lock/Unlock Z Axis	
	
	#define STRTBL_SELOBJ 40011 // Select an object
	#define STRTBL_SELOBJS 40030 // Select objects
	
	#define STRTBL_UWCORD 40012 // Use world coordinates
	#define STRTBL_UOCORD 40013 // Use object coordinates
// </STRING TABLES>

// Next default values for new objects
//
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE 102
#define _APS_NEXT_COMMAND_VALUE 40001
#define _APS_NEXT_CONTROL_VALUE 1000
#define _APS_NEXT_SYMED_VALUE 101
#endif
#endif
