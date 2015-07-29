#include <ddraw.h>
#include <dinput.h>
#include <dsound.h>
#include <stdio.h>

#include "dxdecode.h"
/***************************************************************/

typedef struct tagERRORCODE
{
   HRESULT     hr;
   LPSTR       szError;
} ERRORCODE, * LPERRORCODE;

/***************************************************************/
static ERRORCODE    g_ErrorCode[] =
{
   {   DDERR_ALREADYINITIALIZED,           "DDERR_ALREADYINITIALIZED"},
   {   DDERR_CANNOTATTACHSURFACE,          "DDERR_CANNOTATTACHSURFACE"},
   {   DDERR_CANNOTDETACHSURFACE,          "DDERR_CANNOTDETACHSURFACE"},
   {   DDERR_CURRENTLYNOTAVAIL,            "DDERR_CURRENTLYNOTAVAIL"},
   {   DDERR_EXCEPTION,                    "DDERR_EXCEPTION"},
   {   DDERR_GENERIC,                      "DDERR_GENERIC"},
   {   DDERR_HEIGHTALIGN,                  "DDERR_HEIGHTALIGN"},
   {   DDERR_INCOMPATIBLEPRIMARY,          "DDERR_INCOMPATIBLEPRIMARY"},
   {   DDERR_INVALIDCAPS,                  "DDERR_INVALIDCAPS"},
   {   DDERR_INVALIDCLIPLIST,              "DDERR_INVALIDCLIPLIST"},
   {   DDERR_INVALIDMODE,                  "DDERR_INVALIDMODE"},
   {   DDERR_INVALIDOBJECT,                "DDERR_INVALIDOBJECT"},
   {   DDERR_INVALIDPARAMS,                "DDERR_INVALIDPARAMS"},
   {   DDERR_INVALIDPIXELFORMAT,           "DDERR_INVALIDPIXELFORMAT"},
   {   DDERR_INVALIDRECT,                  "DDERR_INVALIDRECT"},
   {   DDERR_LOCKEDSURFACES,               "DDERR_LOCKEDSURFACES"},
   {   DDERR_NO3D,                         "DDERR_NO3D"},
   {   DDERR_NOALPHAHW,                    "DDERR_NOALPHAHW"},
   {   DDERR_NOCLIPLIST,                   "DDERR_NOCLIPLIST"},
   {   DDERR_NOCOLORCONVHW,                "DDERR_NOCOLORCONVHW"},
   {   DDERR_NOCOOPERATIVELEVELSET,        "DDERR_NOCOOPERATIVELEVELSET"},
   {   DDERR_NOCOLORKEY,                   "DDERR_NOCOLORKEY"},
   {   DDERR_NOCOLORKEYHW,                 "DDERR_NOCOLORKEYHW"},
   {   DDERR_NODIRECTDRAWSUPPORT,          "DDERR_NODIRECTDRAWSUPPORT"},
   {   DDERR_NOEXCLUSIVEMODE,              "DDERR_NOEXCLUSIVEMODE"},
   {   DDERR_NOFLIPHW,                     "DDERR_NOFLIPHW"},
   {   DDERR_NOGDI,                        "DDERR_NOGDI"},
   {   DDERR_NOMIRRORHW,                   "DDERR_NOMIRRORHW"},
   {   DDERR_NOTFOUND,                     "DDERR_NOTFOUND"},
   {   DDERR_NOOVERLAYHW,                  "DDERR_NOOVERLAYHW"},
   {   DDERR_NORASTEROPHW,                 "DDERR_NORASTEROPHW"},
   {   DDERR_NOROTATIONHW,                 "DDERR_NOROTATIONHW"},
   {   DDERR_NOSTRETCHHW,                  "DDERR_NOSTRETCHHW"},
   {   DDERR_NOT4BITCOLOR,                 "DDERR_NOT4BITCOLOR"},
   {   DDERR_NOT4BITCOLORINDEX,            "DDERR_NOT4BITCOLORINDEX"},
   {   DDERR_NOT8BITCOLOR,                 "DDERR_NOT8BITCOLOR"},
   {   DDERR_NOTEXTUREHW,                  "DDERR_NOTEXTUREHW"},
   {   DDERR_NOVSYNCHW,                    "DDERR_NOVSYNCHW"},
   {   DDERR_NOZBUFFERHW,                  "DDERR_NOZBUFFERHW"},
   {   DDERR_NOZOVERLAYHW,                 "DDERR_NOZOVERLAYHW"},
   {   DDERR_OUTOFCAPS,                    "DDERR_OUTOFCAPS"},
   {   DDERR_OUTOFMEMORY,                  "DDERR_OUTOFMEMORY"},
   {   DDERR_OUTOFVIDEOMEMORY,             "DDERR_OUTOFVIDEOMEMORY"},
   {   DDERR_OVERLAYCANTCLIP,              "DDERR_OVERLAYCANTCLIP"},
   {   DDERR_OVERLAYCOLORKEYONLYONEACTIVE, "DDERR_OVERLAYCOLORKEYONLYONEACTIVE"},
   {   DDERR_PALETTEBUSY,                  "DDERR_PALETTEBUSY"},
   {   DDERR_COLORKEYNOTSET,               "DDERR_COLORKEYNOTSET"},
   {   DDERR_SURFACEALREADYATTACHED,       "DDERR_SURFACEALREADYATTACHED"},
   {   DDERR_SURFACEALREADYDEPENDENT,      "DDERR_SURFACEALREADYDEPENDENT"},
   {   DDERR_SURFACEBUSY,                  "DDERR_SURFACEBUSY"},
   {   DDERR_CANTLOCKSURFACE,              "DDERR_CANTLOCKSURFACE"},
   {   DDERR_SURFACEISOBSCURED,            "DDERR_SURFACEISOBSCURED"},
   {   DDERR_SURFACELOST,                  "DDERR_SURFACELOST"},
   {   DDERR_SURFACENOTATTACHED,           "DDERR_SURFACENOTATTACHED"},
   {   DDERR_TOOBIGHEIGHT,                 "DDERR_TOOBIGHEIGHT"},
   {   DDERR_TOOBIGSIZE,                   "DDERR_TOOBIGSIZE"},
   {   DDERR_TOOBIGWIDTH,                  "DDERR_TOOBIGWIDTH"},
   {   DDERR_UNSUPPORTED,                  "DDERR_UNSUPPORTED"},
   {   DDERR_UNSUPPORTEDFORMAT,            "DDERR_UNSUPPORTEDFORMAT"},
   {   DDERR_UNSUPPORTEDMASK,              "DDERR_UNSUPPORTEDMASK"},
   {   DDERR_VERTICALBLANKINPROGRESS,      "DDERR_VERTICALBLANKINPROGRESS"},
   {   DDERR_WASSTILLDRAWING,              "DDERR_WASSTILLDRAWING"},
   {   DDERR_XALIGN,                       "DDERR_XALIGN"},
   {   DDERR_INVALIDDIRECTDRAWGUID,        "DDERR_INVALIDDIRECTDRAWGUID"},
   {   DDERR_DIRECTDRAWALREADYCREATED,     "DDERR_DIRECTDRAWALREADYCREATED"},
   {   DDERR_NODIRECTDRAWHW,               "DDERR_NODIRECTDRAWHW"},
   {   DDERR_PRIMARYSURFACEALREADYEXISTS,  "DDERR_PRIMARYSURFACEALREADYEXISTS"},
   {   DDERR_NOEMULATION,                  "DDERR_NOEMULATION"},
   {   DDERR_REGIONTOOSMALL,               "DDERR_REGIONTOOSMALL"},
   {   DDERR_CLIPPERISUSINGHWND,           "DDERR_CLIPPERISUSINGHWND"},
   {   DDERR_NOCLIPPERATTACHED,            "DDERR_NOCLIPPERATTACHED"},
   {   DDERR_NOHWND,                       "DDERR_NOHWND"},
   {   DDERR_HWNDSUBCLASSED,               "DDERR_HWNDSUBCLASSED"},
   {   DDERR_HWNDALREADYSET,               "DDERR_HWNDALREADYSET"},
   {   DDERR_NOPALETTEATTACHED,            "DDERR_NOPALETTEATTACHED"},
   {   DDERR_NOPALETTEHW,                  "DDERR_NOPALETTEHW"},
   {   DDERR_BLTFASTCANTCLIP,              "DDERR_BLTFASTCANTCLIP"},
   {   DDERR_NOBLTHW,                      "DDERR_NOBLTHW"},
   {   DDERR_NODDROPSHW,                   "DDERR_NODDROPSHW"},
   {   DDERR_OVERLAYNOTVISIBLE,            "DDERR_OVERLAYNOTVISIBLE"},
   {   DDERR_NOOVERLAYDEST,                "DDERR_NOOVERLAYDEST"},
   {   DDERR_INVALIDPOSITION,              "DDERR_INVALIDPOSITION"},
   {   DDERR_NOTAOVERLAYSURFACE,           "DDERR_NOTAOVERLAYSURFACE"},
   {   DDERR_EXCLUSIVEMODEALREADYSET,      "DDERR_EXCLUSIVEMODEALREADYSET"},
   {   DDERR_NOTFLIPPABLE,                 "DDERR_NOTFLIPPABLE"},
   {   DDERR_CANTDUPLICATE,                "DDERR_CANTDUPLICATE"},
   {   DDERR_NOTLOCKED,                    "DDERR_NOTLOCKED"},
   {   DDERR_CANTCREATEDC,                 "DDERR_CANTCREATEDC"},
   {   DDERR_NODC,                         "DDERR_NODC"},
   {   DDERR_WRONGMODE,                    "DDERR_WRONGMODE"},
   {   DDERR_IMPLICITLYCREATED,            "DDERR_IMPLICITLYCREATED"},
   {   DDERR_NOTPALETTIZED,                "DDERR_NOTPALETTIZED"},
   {   DDERR_UNSUPPORTEDMODE,              "DDERR_UNSUPPORTEDMODE"},
   {   DDERR_NOMIPMAPHW,                   "DDERR_NOMIPMAPHW"},
   {   DDERR_INVALIDSURFACETYPE,           "DDERR_INVALIDSURFACETYPE"},
   
   {   DDERR_NOOPTIMIZEHW,                 "DDERR_NOOPTIMIZEHW"},
   {   DDERR_NOTLOADED,                    "DDERR_NOTLOADED"},
   
   {   DDERR_DCALREADYCREATED,             "DDERR_DCALREADYCREATED"},
   
   {   DDERR_NONONLOCALVIDMEM,             "DDERR_NONONLOCALVIDMEM"},
   {   DDERR_CANTPAGELOCK,                 "DDERR_CANTPAGELOCK"},
   {   DDERR_CANTPAGEUNLOCK,               "DDERR_CANTPAGEUNLOCK"},
   {   DDERR_NOTPAGELOCKED,                "DDERR_NOTPAGELOCKED"},
   
   {   DDERR_MOREDATA,                     "DDERR_MOREDATA"},
   {   DDERR_VIDEONOTACTIVE,               "DDERR_VIDEONOTACTIVE"},
   {   DDERR_DEVICEDOESNTOWNSURFACE,       "DDERR_DEVICEDOESNTOWNSURFACE"},
   {   DDERR_NOTINITIALIZED,               "DDERR_NOTINITIALIZED"},
   
   {   DIERR_OLDDIRECTINPUTVERSION,        "DIERR_OLDDIRECTINPUTVERSION" },
   {   DIERR_BETADIRECTINPUTVERSION,       "DIERR_BETADIRECTINPUTVERSION" },
   {   DIERR_BADDRIVERVER,                 "DIERR_BADDRIVERVER" },
   {   DIERR_DEVICENOTREG,                 "DIERR_DEVICENOTREG" },
   {   DIERR_NOTFOUND,                     "DIERR_NOTFOUND" },
   {   DIERR_OBJECTNOTFOUND,               "DIERR_OBJECTNOTFOUND" },
   {   DIERR_INVALIDPARAM,                 "DIERR_INVALIDPARAM" },
   {   DIERR_NOINTERFACE,                  "DIERR_NOINTERFACE" },
   {   DIERR_GENERIC,                      "DIERR_GENERIC" },
   {   DIERR_OUTOFMEMORY,                  "DIERR_OUTOFMEMORY" },
   {   DIERR_UNSUPPORTED,                  "DIERR_UNSUPPORTED" },
   {   DIERR_NOTINITIALIZED,               "DIERR_NOTINITIALIZED" },
   {   DIERR_ALREADYINITIALIZED,           "DIERR_ALREADYINITIALIZED" },
   {   DIERR_NOAGGREGATION,                "DIERR_NOAGGREGATION" },
   {   DIERR_OTHERAPPHASPRIO,              "DIERR_OTHERAPPHASPRIO" },
   {   DIERR_INPUTLOST,                    "DIERR_INPUTLOST" },
   {   DIERR_ACQUIRED,                     "DIERR_ACQUIRED" },
   {   DIERR_NOTACQUIRED,                  "DIERR_NOTACQUIRED" },
   {   DIERR_READONLY,                     "DIERR_READONLY" },
   {   DIERR_HANDLEEXISTS,                 "DIERR_HANDLEEXISTS" },
   {   E_PENDING,                          "E_PENDING" },
   {   DIERR_INSUFFICIENTPRIVS,            "DIERR_INSUFFICIENTPRIVS" },
   {   DIERR_DEVICEFULL,                   "DIERR_DEVICEFULL" },
   {   DIERR_MOREDATA,                     "DIERR_MOREDATA" },
   {   DIERR_NOTDOWNLOADED,                "DIERR_NOTDOWNLOADED" },
   {   DIERR_HASEFFECTS,                   "DIERR_HASEFFECTS" },
   {   DIERR_NOTEXCLUSIVEACQUIRED,         "DIERR_NOTEXCLUSIVEACQUIRED" },
   {   DIERR_INCOMPLETEEFFECT,             "DIERR_INCOMPLETEEFFECT" },
   {   DIERR_NOTBUFFERED,                  "DIERR_NOTBUFFERED" },
   {   DIERR_EFFECTPLAYING,                "DIERR_EFFECTPLAYING" },
   {   DIERR_UNPLUGGED,                    "DIERR_UNPLUGGED" },

   {   DSERR_ALLOCATED,                    "DSERR_ALLOCATED" },
   {   DSERR_CONTROLUNAVAIL,               "DSERR_CONTROLUNAVAIL" },
   {   DSERR_INVALIDPARAM,                 "DSERR_INVALIDPARAM" },
   {   DSERR_INVALIDCALL,                  "DSERR_INVALIDCALL" },
   {   DSERR_GENERIC,                      "DSERR_GENERIC" },
   {   DSERR_PRIOLEVELNEEDED,              "DSERR_PRIOLEVELNEEDED" },
   {   DSERR_OUTOFMEMORY,                  "DSERR_OUTOFMEMORY" },
   {   DSERR_BADFORMAT,                    "DSERR_BADFORMAT" },
   {   DSERR_UNSUPPORTED,                  "DSERR_UNSUPPORTED" },
   {   DSERR_NODRIVER,                     "DSERR_NODRIVER" },
   {   DSERR_ALREADYINITIALIZED,           "DSERR_ALREADYINITIALIZED" },
   {   DSERR_NOAGGREGATION,                "DSERR_NOAGGREGATION" },
   {   DSERR_BUFFERLOST,                   "DSERR_BUFFERLOST" },
   {   DSERR_OTHERAPPHASPRIO,              "DSERR_OTHERAPPHASPRIO" },
   {   DSERR_UNINITIALIZED,                "DSERR_UNINITIALIZED" },


   {   E_NOINTERFACE,                      "E_NOINTERFACE" },

};

/***************************************************************/

/*
   DirectXDecodeError:  Return a string description of the given DirectX
   error code.
*/

const char * DirectXDecodeError(HRESULT errorval)
{
    int i;
    static char tmp[64];
    
    for (i = 0; i < (sizeof(g_ErrorCode) / sizeof(g_ErrorCode[0])); i++)
    {
        if (g_ErrorCode[i].hr == errorval)
        {
            return g_ErrorCode[i].szError;
        }
    }
    sprintf(tmp, "UNKNOWN: 0x%x", errorval);
    return tmp;
}
