static const int PADLOCK_INTERFACE = 2064980851;
static const int PADLOCK_OPENREQUEST = 2064980849;
static const int PADLOCK_UNLOCKREQUEST = 2064980850;
static const int PADLOCK_RESETREQUEST = 2064980848;
static const int PADLOCK_CONFIG_REQUEST = 2064980852;
static const int PADLOCK_CONFIG_RESPONSE = 2064980853;
static const string PADLOCK_WARNINGIMAGE = "Padlocks/gui/images/warning.edds";


enum PadLockRespones
{
	SUCCESS,
	INVALIDPIN, 
	RATELIMITED,
	NEEDPIN
}