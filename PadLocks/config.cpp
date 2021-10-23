class CfgPatches
{
  class PadLocks
  {
    requiredAddons[]={ "DZ_Data" }; 
  };
};

class CfgMods
{
  class PadLocks
  {
    name="PadLocks";
    type="mod"
	dependencies[]={ "Game", "World", "Mission" };
	class defs
	{
		class gameScriptModule
        {
			value = "";
            files[]={
				"PadLocks/scripts/3_Game"
			};
         };
		class worldScriptModule
        {
            value="";
            files[]={ 
				"PadLocks/scripts/4_World" 
			};
        };
	    class missionScriptModule
        {
            value="";
            files[]={
				"PadLocks/scripts/5_Mission" 
			};
        };
    };
  };
};